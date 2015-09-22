#ifndef CARD_SHUFFLER_HPP_INCLUDED
#define CARD_SHUFFLER_HPP_INCLUDED

/*
  ==============================================================================

    CardShuffler.hpp
    Created: 21 Sep 2015 1:51:09pm
    Author:  caps

  ==============================================================================
*/

#include <boost/range/adaptor/sliced.hpp>
#include <boost/range/algorithm/random_shuffle.hpp>
#include <boost/range/sub_range.hpp>

#include <functional>   //for std::bind
#include <random>

namespace SM
{
namespace Dominion
{

class CardShuffler
{
public:
    CardShuffler();

    template<typename RangeT>
    auto shuffle(RangeT& in,
                 typename RangeT::size_type count) -> boost::sliced_range<RangeT>
    {
        typedef typename std::iterator_traits<typename RangeT::iterator>::difference_type diff_t;
        typedef typename std::make_unsigned<diff_t>::type udiff_t;
        typedef typename std::uniform_int_distribution<udiff_t> distr_t;
        typedef typename distr_t::param_type param_t;

        distr_t distr;
        using namespace std::placeholders;
        auto gen = std::bind([](udiff_t i,
                                distr_t& distr,
                                std::mt19937& gtor) -> udiff_t
        {
            return distr(gtor, param_t(0, i - 1));
        },
                             _1,
            std::ref(distr),
            std::ref(generator));

        return boost::random_shuffle(in, gen) | boost::adaptors::sliced(0, count);
    }
private:
    std::random_device engine;
    std::mt19937 generator;
};  //end class CardShuffler

}   //end namespace Dominion
}   //end namespace SM

#endif  // CARD_SHUFFLER_HPP_INCLUDED