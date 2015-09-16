/*
  ==============================================================================

    Card.cpp
    Created: 14 Sep 2015 11:44:59am
    Author:  Bladerunner

  ==============================================================================
*/

#include "randomizer_card.hpp"

#include "D:\\SuddenMagic\\lib\\fold_subranges.hpp"

#include <algorithm>
#include <cassert>
#include <iterator>
#include <numeric>

using s = std::wstring;  //std::wstring
using vsi = std::vector<s>::const_iterator;

namespace SM	//(sudden magic)
{
namespace dominion  //for all of the code related specifically to the deck-building game Dominion.
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
        return cardsets::alchemy;
    else if (cardset == L"base")
        return cardsets::base;
    else if (cardset == L"cornucopia")
        return cardsets::cornucopia;
    else if (cardset == L"dark")
        return cardsets::dark_ages;
    else if (cardset == L"dominion")
        return cardsets::dominion;
    else if (cardset == L"guilds")
        return cardsets::guilds;
    else if (cardset == L"hinterlands")
        return cardsets::hinterlands;
    else if (cardset == L"intrigue")
        return cardsets::intrigue;
    else if (cardset == L"promo")
        return cardsets::promo;
    else if (cardset == L"prosperity")
        return cardsets::prosperity;
    else if (cardset == L"seaside")
        return cardsets::seaside;
    else
        assert(!"reached invalid if statement in string to cardset conversion");

    return cardsets::base;
}

auto cardtype_from_str(const std::wstring& in)
{
    if (in == L"Action")
        return cardtypes::action;
    else if (in == L"Attack")
        return cardtypes::attack;
    else if (in == L"Blank")
        return cardtypes::blank;
    else if (in == L"Curse")
        return cardtypes::curse;
    else if (in == L"Duration")
        return cardtypes::duration;
    else if (in == L"Event")
        return cardtypes::event;
    else if (in == L"Looter")
        return cardtypes::looter;
    else if (in == L"Prize")
        return cardtypes::prize;
    else if (in == L"Reaction")
        return cardtypes::reaction;
    else if (in == L"Reserve")
        return cardtypes::reserve;
    else if (in == L"Ruins")
        return cardtypes::ruins;
    else if (in == L"Shelter")
        return cardtypes::shelter;
    else if (in == L"Traveler")
        return cardtypes::traveler;
    else if (in == L"Treasure")
        return cardtypes::treasure;
    else if (in == L"Victory")
        return cardtypes::victory;
    else
        assert(!"reached invalid if statement in string to cardset conversion");

    return cardtypes::action;
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

    std::vector<cardtypes> return_vec;

    fold_subranges(sb
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

randomizer_card::randomizer_card(const std::vector<std::wstring>& in)
    : randomizer_card(std::begin(in), std::end(in))
{}

randomizer_card::randomizer_card(const vsi b, const vsi e)
    : set(get_cardset(b, e))
    , name(read_after(L"name:", L"potcost:", b, e))
    , gold_cost(std::stoi(read_after(L"cost:", L"description:", b, e, {L""})))
    , potion_cost(std::stoi(read_after(L"potcost:", L"types:", b, e, {L""})))
    , description(read_after(L"description:", L"extra:", b, e))
    , extra_information(read_after(L"extra:", L"name:", b, e))
    , applicable_types(types(b, e))
{}

}	//end namespace dominion
}	//end namespace SM (sudden magic)