#ifndef CARD_SHUFFLER_HPP_INCLUDED
#define CARD_SHUFFLER_HPP_INCLUDED

/*
  ==============================================================================

    CardShuffler.hpp
    Created: 21 Sep 2015 1:51:09pm
    Author:  caps

  ==============================================================================
*/

#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/adaptor/indexed.hpp>
#include <boost/range/adaptor/indirected.hpp>
#include <boost/range/adaptor/copied.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/algorithm/find_if.hpp>
#include <boost/range/algorithm/random_shuffle.hpp>
#include <boost/range/sub_range.hpp>

#include <functional>   //for std::bind
#include <unordered_map>
#include <memory>
#include <random>

namespace SM
{
namespace Dominion
{

enum class Cardsets;
enum class Cardtypes;
class RandomizerCard;

class CardFilter    //an interface
{
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
public:
    CardShuffler();

    template<typename RangeT>
    auto shuffle(RangeT& in
                 , typename RangeT::size_type count) -> RangeT
    {
        using diff_t = std::iterator_traits<typename RangeT::iterator>::difference_type;
        using udiff_t = std::make_unsigned<diff_t>::type;
        using distr_t = std::uniform_int_distribution<udiff_t>;
        using param_t = distr_t::param_type;

        distr_t distr;
        using namespace std::placeholders;
        auto gen{std::bind(
                    [](udiff_t i
                      , distr_t& distr
                      , std::mt19937& gtor) -> udiff_t
                      {
                        return distr(gtor, param_t(0, i - 1));
                      }
                    , _1
                    , std::ref(distr)
                    , std::ref(generator))};

        auto one_filter{[](const CardFilter& filter, const RandomizerCard& card) -> bool
        {
            //will return true if the card should be filtered out
            return !filter(card);
        }};

        using namespace boost::adaptors;
        auto all_filters{[&one_filter](const RandomizerCard& card
                                      , const vec_filterT& all_filters) -> bool
        {
            auto bind_one_filter{std::bind(one_filter, _1, std::ref(card))};
            return boost::find_if(all_filters
                                  | indirected
                                  , bind_one_filter) == boost::end(all_filters
                                                                   | indirected);
        }};

        auto bind_all_filters{std::bind(all_filters, _1, std::ref(pre_filters))};

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
        RangeT return_val(boost::copy_range<RangeT>(in | filtered(bind_all_filters)));
        boost::random_shuffle(return_val, gen);
        return boost::copy_range<RangeT>(return_val
                                         | copied(0, std::min(count, return_val.size())));
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

    const static int default_min{0};
    const static int default_max{10};

    struct min_max
    {
        int min{default_min};
        int max{default_max};
        min_max(int min, int max) : min{min}, max{max} {};
    };

    template<typename KeyT>
    using min_max_mapT = std::unordered_map<KeyT, min_max>;

    min_max_mapT<Cardsets> sets_min_max;
    min_max_mapT<Cardtypes> types_min_max;

    template<typename Type>
    inline auto setMin(const Type in, const int new_min, min_max_mapT<Type>& min_max_map) -> void
    {
        assert(new_min >= default_min);

        auto location_itr{min_max_map.find(in)};
        if (location_itr != std::end(min_max_map))
            location_itr->second.min = new_min;
        else
            min_max_map.emplace(in, min_max{new_min, default_max});
    }

    template<typename Type>
    inline auto setMax(const Type in, const int new_max, min_max_mapT<Type>& min_max_map) -> void
    {
        assert(new_max <= default_max);

        auto location_itr{min_max_map.find(in)};
        if (location_itr != std::end(min_max_map))
            location_itr->second.max = new_max;
        else
            min_max_map.emplace(in, min_max{default_min, new_max});
    }

    template<typename Type>
    inline auto getMin(const Type in, const min_max_mapT<Type>& min_max) const -> int
    {
        auto location_itr{min_max.find(in)};
        if (location_itr != std::end(min_max))
            return location_itr->second.min;
        else
            return default_min;
    }

    template<typename Type>
    inline auto getMax(const Type in, const min_max_mapT<Type>& min_max) const -> int
    {
        auto location_itr{min_max.find(in)};
        if (location_itr != std::end(min_max))
            return location_itr->second.max;
        else
            return default_max;
    }

    auto findFilter(const CardFilter& filter)->filter_itr;
    auto findFilter(const CardFilter& filter) const->filter_citr;
    auto filterExistsAlready(const CardFilter& filter) const -> bool;
};  //end class CardShuffler

}   //end namespace Dominion
}   //end namespace SM

#endif  // CARD_SHUFFLER_HPP_INCLUDED