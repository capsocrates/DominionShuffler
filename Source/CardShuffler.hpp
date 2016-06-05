#ifndef CARD_SHUFFLER_HPP_INCLUDED
#define CARD_SHUFFLER_HPP_INCLUDED

/*
  ==============================================================================

    CardShuffler.hpp
    Created: 21 Sep 2015 1:51:09pm
    Author:  caps

  ==============================================================================
*/

#include "sm/utility_hash.hpp"
#include "sm/utility_make_unique.hpp"

#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/adaptor/indexed.hpp>
#include <boost/range/adaptor/indirected.hpp>
#include <boost/range/adaptor/copied.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/algorithm/find_if.hpp>
#include <boost/range/algorithm/random_shuffle.hpp>
#include <boost/range/sub_range.hpp>

#include <algorithm>
#include <deque>
#include <functional>   //for std::bind
#include <iterator>
#include <memory>
#include <random>
#include <unordered_map>

namespace SM
{
namespace Dominion
{

enum class Cardsets;
enum class Cardtypes;
class RandomizerCard;

class CardFilter    //an interface
{
/*
Seriously considering rewriting this class
to wrap all the polymorphism via templated
private members. I don't like having to
call make_unique all over the place when I
add new filters.
*/
public:
    auto operator()(const RandomizerCard& in) const -> bool
    {
        return checkFilter(in);
    };

    auto uniqueID() const -> std::wstring
    {
        return getUniqueID();
    };
private:
    virtual auto checkFilter(const RandomizerCard& in) const -> bool = 0;
    virtual auto getUniqueID() const->std::wstring = 0;
};

class CardShuffler
{
private:
    static constexpr int default_min{0};
    static constexpr int default_max{10};

    struct min_max
    {
        int min{default_min};
        int max{default_max};
        min_max(int min, int max) : min{min}, max{max} {};
    };

    template<typename KeyT>
    using min_max_mapT = std::unordered_map<KeyT, min_max, utility::enum_hash<KeyT>>;
public:
    CardShuffler();

    template<typename RangeT>
    auto shuffle(RangeT& in
                 , typename RangeT::size_type count) -> RangeT
    {
        using diff_t = typename std::iterator_traits<typename RangeT::iterator>::difference_type;
        using udiff_t = typename std::make_unsigned<diff_t>::type;
        using distr_t = std::uniform_int_distribution<udiff_t>;
        using param_t = typename distr_t::param_type;

        distr_t distr;
        using namespace std::placeholders;
        auto gen = [&distr, this](udiff_t i) -> udiff_t
        {
            return distr(this->generator, param_t{0, i - 1});
        };

        auto one_filter = [](const CardFilter& filter, const RandomizerCard& card) -> bool
        {
            //will return true if the card should be filtered out
            return !filter(card);
        };

        using namespace boost::adaptors;
        auto all_filters = [&one_filter, this](const RandomizerCard& card) -> bool
        {
            auto bind_one_filter = std::bind(one_filter, _1, std::ref(card));
            auto all_filters_indirected = this->pre_filters | indirected;
            return boost::find_if(all_filters_indirected, bind_one_filter) == std::end(all_filters_indirected);
        };

        /*
        generate a range of the filtered input
        shuffle that range
        create two temporary ranges to store cards that satisfy our filter
            requirements and also cards that DON'T satisfy them.
            These temporary ranges will record the order their elements were
            added (via boost::adaptors::indexed) even if they are rearranged
        step over the return range and put all the elements that satisfy filter
            criteria into the first temporary range, and all the others into
            the second temporary range
        check to see how many elements are required in the first temporary range
            in order to make that range satisfy all requirements
        if the requirements can not be satisfied by the entirety of the first temporary
            range, then no amount of re-ordering will suffice, and we must return
            with an unsatisfactory range
        if the required elements are less than count, we can "truncate" past the
            last required element, and then iterate over the first and second
            temporary ranges, appending whichever element has a lower index until we
            reach count
        if the required elements are greater than count, we perform some magic
            (perhaps using next_permutation?) to see if we can satisfy the requirements
            with only count or less elements. This could be expensive, so we need to be
            careful with it
        TODO: add post-shuffle filters
        return the first 10 elements of that range
        */
        auto filtered_range = boost::copy_range<RangeT>(in | filtered(all_filters));
        boost::random_shuffle(filtered_range, gen);

        auto sets_min_max_copy = sets_min_max;
        auto types_min_max_copy = types_min_max;

        auto dec_if_positive = [](int& val)
        {
            return val = std::max(val - 1, 0);
        };

        auto adjust_set_vals = [&sets_min_max_copy, dec_if_positive](const RandomizerCard& card)
        {
            auto sets_itr = sets_min_max_copy.find(card.set);
            if (sets_itr != sets_min_max_copy.end())
            {
                dec_if_positive(sets_itr->second.max);
                dec_if_positive(sets_itr->second.min);
            }
        };

        auto adjust_type_vals = [&types_min_max_copy, dec_if_positive](const RandomizerCard& card)
        {
            for (Cardtypes type : card.applicable_types)
            {
                auto types_itr = types_min_max_copy.find(type);
                if (types_itr != types_min_max_copy.end())
                {
                    dec_if_positive(types_itr->second.max);
                    dec_if_positive(types_itr->second.max);
                }
            }
        };

        auto set_is_not_at_max = [&sets_min_max_copy](const RandomizerCard& card)
        {
            auto sets_itr = sets_min_max_copy.find(card.set);
            if (sets_itr != sets_min_max_copy.end())
            {
                return sets_itr->second.max > 0;
            }
            return true;
        };

        auto type_is_not_at_max = [&types_min_max_copy](const RandomizerCard& card)
        {
            return std::all_of(std::begin(card.applicable_types),
                               std::end(card.applicable_types),
                               [&](Cardtypes type)
            {
                auto type_itr = types_min_max_copy.find(type);
                if (type_itr != types_min_max_copy.end())
                {
                    return type_itr->second.max > 0;
                }
                return true;
            }
            );
        };

        auto calculate_unfulfilled_requirements = [&]() -> int
        {
            auto accumulate_function = [](int left, const auto& value) -> int
            {
                return left + value.second.max;
            };
            return boost::accumulate(sets_min_max_copy, 0, accumulate_function)
                + boost::accumulate(types_min_max_copy, 0, accumulate_function);
        };

        auto return_val = RangeT{};
        auto extra_cards = std::deque<typename RangeT::value_type>{};

        auto room_for_extra_cards = [&return_val, count, calculate_unfulfilled_requirements]()
        {
            return return_val.size() < (count - calculate_unfulfilled_requirements());
        };

        auto add_card = [this
            , &return_val
            , adjust_set_vals
            , adjust_type_vals](const RandomizerCard& card)
        {
            adjust_set_vals(card);
            adjust_type_vals(card);
            return_val.emplace_back(card);
        };

        for (const RandomizerCard& card : filtered_range)
        {
            if (return_val.size() <= count && !room_for_extra_cards())
            {
                break;
            }
            /*
             *  if return_val.size() < (count - unfulfilled requirements) then add
             *  the current card, but also modify the unfulfilled requirements based
             *  on which ones the current card satisfies
             *
             *  otherwise, we don't have enough space (at present) for cards that don't
             *  satisfy our requirements, so put them in a secondary buffer to pull from
             *  if we satisfy the constraints later
             */

             //add the current card only if we haven't maxed out it's type or set already
            if (set_is_not_at_max(card)
                && type_is_not_at_max(card))
            {
                if (room_for_extra_cards())
                {
                    if (extra_cards.size())
                    {
                        /*
                         *  add any cards we skipped earlier because at the time there was
                         *  no room for them
                         */

                        while (!extra_cards.empty()
                               && room_for_extra_cards())
                        {
                            add_card(extra_cards.front());
                            return_val.emplace_back(extra_cards.front());
                            extra_cards.pop_front();
                        }
                    }
                    if (room_for_extra_cards())
                    {
                        add_card(card);
                    }
                }
                else
                {
                    extra_cards.emplace_back(card);
                }
            }
        }

        return return_val;
    }

    auto enable(Cardsets) -> void;
    auto disable(Cardsets) -> void;
    auto isEnabled(Cardsets) const -> bool;

    auto enable(Cardtypes) -> void;
    auto disable(Cardtypes) -> void;
    auto isEnabled(Cardtypes) const -> bool;

    auto setMin(Cardsets, int) -> void;
    auto setMax(Cardsets, int) -> void;
    auto getMin(Cardsets) const -> int;
    auto getMax(Cardsets) const -> int;

    auto setMin(Cardtypes, int) -> void;
    auto setMax(Cardtypes, int) -> void;
    auto getMin(Cardtypes) const -> int;
    auto getMax(Cardtypes) const -> int;
private:
    std::random_device engine;
    std::mt19937 generator;
    using filterT = std::unique_ptr<CardFilter>;
    using vec_filterT = std::vector<filterT>;
    vec_filterT pre_filters;
    using filter_itr = vec_filterT::iterator;
    using filter_citr = vec_filterT::const_iterator;

    min_max_mapT<Cardsets> sets_min_max;
    min_max_mapT<Cardtypes> types_min_max;

    template<typename Type>
    inline auto setMin(const Type in, const int new_min, min_max_mapT<Type>& min_max_map) -> void
    {
        assert(new_min >= default_min);

        auto location_itr(min_max_map.find(in));
        if (location_itr != std::end(min_max_map))
            location_itr->second.min = new_min;
        else
            min_max_map.emplace(in, min_max{new_min, default_max});
    }

    template<typename Type>
    inline auto setMax(const Type in, const int new_max, min_max_mapT<Type>& min_max_map) -> void
    {
        assert(new_max <= default_max);

        auto location_itr(min_max_map.find(in));
        if (location_itr != std::end(min_max_map))
            location_itr->second.max = new_max;
        else
            min_max_map.emplace(in, min_max{default_min, new_max});
    }

    template<typename Type>
    inline auto getMin(const Type in, const min_max_mapT<Type>& min_max) const -> int
    {
        auto location_itr(min_max.find(in));
        if (location_itr != std::end(min_max))
            return location_itr->second.min;
        else
            return default_min;
    }

    template<typename Type>
    inline auto getMax(const Type in, const min_max_mapT<Type>& min_max) const -> int
    {
        auto location_itr(min_max.find(in));
        if (location_itr != std::end(min_max))
            return location_itr->second.max;
        else
            return default_max;
    }

    template<typename FilterT>
    auto addPreFilter(const FilterT& new_filter) -> void
    {
        pre_filters.emplace_back(utility::make_unique<FilterT>(new_filter));
    }
    auto findFilter(const CardFilter& filter)->filter_itr;
    auto findFilter(const CardFilter& filter) const->filter_citr;
    auto filterExistsAlready(const CardFilter& filter) const -> bool;
};  //end class CardShuffler

}   //end namespace Dominion
}   //end namespace SM

#endif  // CARD_SHUFFLER_HPP_INCLUDED