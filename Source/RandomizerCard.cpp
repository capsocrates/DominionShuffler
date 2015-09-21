/*
  ==============================================================================

    Card.cpp
    Created: 14 Sep 2015 11:44:59am
    Author:  Bladerunner

  ==============================================================================
*/

#include "RandomizerCard.hpp"

#include <sm\group_by.hpp>

#include <algorithm>
#include <cassert>
#include <iterator>
#include <numeric>

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

auto get_cardset(vsi b, vsi e)
{
    const s cardset{*std::next(std::find(b, e, L"cardset:"))};
    if (cardset == L"alchemy")
        return Cardsets::alchemy;
    else if (cardset == L"base")
        return Cardsets::base;
    else if (cardset == L"cornucopia")
        return Cardsets::cornucopia;
    else if (cardset == L"dark")
        return Cardsets::dark_ages;
    else if (cardset == L"dominion")
        return Cardsets::dominion;
    else if (cardset == L"guilds")
        return Cardsets::guilds;
    else if (cardset == L"hinterlands")
        return Cardsets::hinterlands;
    else if (cardset == L"intrigue")
        return Cardsets::intrigue;
    else if (cardset == L"promo")
        return Cardsets::promo;
    else if (cardset == L"prosperity")
        return Cardsets::prosperity;
    else if (cardset == L"seaside")
        return Cardsets::seaside;
    else
        assert(!"reached invalid if statement in string to cardset conversion");

    return Cardsets::base;
}

auto cardtype_from_str(const std::wstring& in)
{
    if (in == L"Action")
        return Cardtypes::action;
    else if (in == L"Attack")
        return Cardtypes::attack;
    else if (in == L"Blank")
        return Cardtypes::blank;
    else if (in == L"Curse")
        return Cardtypes::curse;
    else if (in == L"Duration")
        return Cardtypes::duration;
    else if (in == L"Event")
        return Cardtypes::event;
    else if (in == L"Looter")
        return Cardtypes::looter;
    else if (in == L"Prize")
        return Cardtypes::prize;
    else if (in == L"Reaction")
        return Cardtypes::reaction;
    else if (in == L"Reserve")
        return Cardtypes::reserve;
    else if (in == L"Ruins")
        return Cardtypes::ruins;
    else if (in == L"Shelter")
        return Cardtypes::shelter;
    else if (in == L"Traveler")
        return Cardtypes::traveler;
    else if (in == L"Treasure")
        return Cardtypes::treasure;
    else if (in == L"Victory")
        return Cardtypes::victory;
    else
        assert(!"reached invalid if statement in string to cardset conversion");

    return Cardtypes::action;
}

auto types(vsi b, vsi e)
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
    , gold_cost(std::stoi(read_after(L"cost:", L"description:", b, e, {L""})))
    , potion_cost(std::stoi(read_after(L"potcost:", L"types:", b, e, {L""})))
    , description(read_after(L"description:", L"extra:", b, e))
    , extra_information(read_after(L"extra:", L"name:", b, e))
    , applicable_types(types(b, e))
{}

}	//end namespace Dominion
}	//end namespace SM (sudden magic)