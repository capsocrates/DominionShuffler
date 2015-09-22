/*
  ==============================================================================

    Card.cpp
    Created: 14 Sep 2015 11:44:59am
    Author:  Bladerunner

  ==============================================================================
*/

#include "RandomizerCard.hpp"

#include "sm\group_by.hpp"

#include <algorithm>
#include <cassert>
#include <cwchar>   //for std::wcstoll, since std::stoi doesn't seem to be available on the Android C++ compiler
#include <iterator>
#include <numeric>
#include <string>

using s = std::wstring;  //std::wstring
using vsi = std::vector<s>::const_iterator;

namespace SM	//(sudden magic)
{
namespace Dominion  //for all of the code related specifically to the deck-building game Dominion.
{

s read_after(const s& start_key, const s& end_key, vsi b, vsi e, const s& delim = {L" "})
{
    vsi sub_b{std::find(b, e, start_key)};
    return std::accumulate(std::next(sub_b), std::find(sub_b, e, end_key), s{L""}, [&delim](const s sum, const s in)
    {
        return (!sum.empty() ? (sum + delim + in) : in);
    });
}

auto get_cardset(vsi b, vsi e) -> Cardsets
{
    return cardset_from_str(*std::next(std::find(b, e, L"cardset:")));
}

auto types(vsi b, vsi e) -> std::vector<Cardtypes>
{
    //this should be something like "[Action]" or "[Action, Attack]"
    const s bracket_tuple{read_after(L"!!python/tuple", L"-", b, e, {L""})};

    //we want it to come out as a vector of card type enums
    using ssi = s::const_iterator;  //a sub-string iterator

    auto bracket = [](const wchar_t in)
    {
        return in == L']';
    };

    auto find_bracket = [bracket](ssi b, ssi e)
    {
        return std::find_if(b, e, bracket);
    };

    ssi sb{std::begin(bracket_tuple)}, //substring begin
        se{find_bracket(sb, std::end(bracket_tuple))};   //substring end

    auto comma_or_bracket = [](const wchar_t in)
    {
        return in == L',' || in == L']';
    };

    //bind the find algorithm
    auto find_comma_or_bracket = [comma_or_bracket](ssi b, ssi e)
    {
        //the input should be [somecardtype,optionalothercardtype]
        assert(b == e || *b == L'[' || *b == L',');
        return std::find_if(std::next(b), e, comma_or_bracket);
    };

    std::vector<Cardtypes> return_vec;

    group_by(sb
             , se
             , std::back_inserter(return_vec)
             , [find_comma_or_bracket](ssi b, ssi e)
    {
        return std::make_pair(b, find_comma_or_bracket(b, e));
    }
             , [find_comma_or_bracket](ssi b, ssi e)
    {
        return cardtype_from_str(s{std::next(b), find_comma_or_bracket(b, e)});
    });

    return return_vec;
}

RandomizerCard::RandomizerCard(const std::vector<std::wstring>& in)
    : RandomizerCard(std::begin(in), std::end(in))
{}

RandomizerCard::RandomizerCard(const vsi b, const vsi e)
    : set(get_cardset(b, e))
    , name(read_after(L"name:", L"potcost:", b, e))
    , gold_cost(static_cast<int>(std::wcstol(read_after(L"cost:", L"description:", b, e, {L""}).c_str(), nullptr,10)))   //stoi(read_after(L"cost:", L"description:", b, e, {L""})))
    , potion_cost(static_cast<int>(std::wcstol(read_after(L"potcost:", L"types:", b, e, {L""}).c_str(), nullptr, 10))) //stoi(read_after(L"potcost:", L"types:", b, e, {L""})))
    , description(read_after(L"description:", L"extra:", b, e))
    , extra_information(read_after(L"extra:", L"name:", b, e))
    , applicable_types(types(b, e))
{}

}	//end namespace Dominion
}	//end namespace SM (sudden magic)