/*
  ==============================================================================

    card_import.cpp
    Created: 14 Sep 2015 11:45:07am
    Author:  Bladerunner

  ==============================================================================
*/

#include "RandomizerCard.hpp"

#include "CardImport.hpp"

#include <sm\group_by.hpp>

#include <algorithm>
#include <array>
#include <cassert>
#include <iterator>
#include <sstream>
#include <iterator>

#include "CardText.hpp"    //all of the card text stored in a global string...

using s = std::wstring;  //std::wstring
using isi = std::istream_iterator<std::wstring, wchar_t>;   //std::istream_iterator<std::wstring>
using as = SM::Dominion::CardTextArray;  //std::array<std::wstring>

namespace SM	//(sudden magic)
{
namespace Dominion  //for all of the code related specifically to the deck-building game Dominion.
{

std::vector<RandomizerCard> make_cards_from_strings(const as& in);

std::vector<RandomizerCard> read_cards()
{
    return make_cards_from_strings(complete_card_text);
}

std::vector<RandomizerCard> make_cards_from_strings(const as& in)
{
    using vrc = std::vector<RandomizerCard>;
    if (in.empty())
        return vrc();

    using asi = as::const_iterator;
    using casi = const asi;
    const s token{L"!!python/object:__main__.Card"};

    casi beg(std::begin(in));
    auto is_beg = [beg](casi in) -> bool
    {
        return beg == in;
    };

    casi end(std::end(in));
    auto is_end = [end](casi in) -> bool
    {
        return end == in;
    };

    //the range should be [b, e) where *b == token in every case but the very first, and *e == token in every case but the last, where e == end(in)
    auto find_next_token = [&token, is_beg, is_end](casi b, casi e) -> asi
    {
        assert(is_beg(b) || *b == token);
        assert(is_end(e) || *e == token);
        return std::find(std::next(b), e, token);
    };

    //create subranges that begin and end with the token
    auto make_range = [&find_next_token](asi b, casi e) -> std::pair<asi, casi>
    {
        return std::make_pair(b, find_next_token(b, e));
    };
    //iterate over the subranges, creating cards from each subrange

    std::vector<RandomizerCard> return_vec;
    group_by(find_next_token(std::begin(in), 
                             std::end(in)), 
             std::end(in), 
             std::back_inserter(return_vec), 
             make_range);

    //return the created cards in a vector
    return return_vec;
}

}	//end namespace Dominion
}	//end namespace SM (sudden magic)