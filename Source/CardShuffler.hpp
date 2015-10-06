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
#include <boost/range/adaptor/indirected.hpp>
#include <boost/range/adaptor/copied.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/algorithm/find_if.hpp>
#include <boost/range/algorithm/random_shuffle.hpp>
#include <boost/range/sub_range.hpp>

#include <functional>   //for std::bind
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
    virtual auto getUniqueID() const -> std::wstring = 0;
};

class CardShuffler
{
public:
    CardShuffler();

    template<typename RangeT>
    auto shuffle(RangeT& in,
                 typename RangeT::size_type count) -> RangeT
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
        TODO: add post-shuffle filters
        return the first 10 elements of that range
        */
        RangeT return_val(boost::copy_range<RangeT>(in | filtered(bind_all_filters)));
        boost::random_shuffle(return_val, gen);
        return boost::copy_range<RangeT>(return_val
                                         | copied(0, std::min(count, return_val.size())));
    }

    auto enableCardset(Cardsets in) -> void;
    auto disableCardset(Cardsets in) -> void;
    auto cardsetEnabled(Cardsets in) -> bool;

    auto enableCardtype(Cardtypes in) -> void;
    auto disableCardtype(Cardtypes in) -> void;
    auto cardtypeEnabled(Cardtypes in) -> bool;
private:
    std::random_device engine;
    std::mt19937 generator;
    //TODO: add a uniform_int_distribution filter
    typedef std::unique_ptr<CardFilter> filterT;
    typedef std::vector<filterT> vec_filterT;
    vec_filterT pre_filters;
    vec_filterT post_filters;
    typedef vec_filterT::iterator filter_itr;
    typedef vec_filterT::const_iterator filter_citr;

    auto findFilter(const CardFilter& filter) -> filter_itr;
    auto findFilter(const CardFilter& filter) const -> filter_citr;
    auto filterExistsAlready(const CardFilter& filter) const -> bool;
};  //end class CardShuffler

}   //end namespace Dominion
}   //end namespace SM

#endif  // CARD_SHUFFLER_HPP_INCLUDED