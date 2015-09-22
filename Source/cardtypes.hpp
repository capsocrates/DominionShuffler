#ifndef CARDTYPES_HPP_INCLUDED
#define CARDTYPES_HPP_INCLUDED

/*
  ==============================================================================

    Cardtypes.hpp
    Created: 14 Sep 2015 2:09:25pm
    Author:  Bladerunner

  ==============================================================================
*/

#include <cassert>
#include <string>
#include <vector>

namespace SM	//(sudden magic)
{
namespace Dominion  //for all of the code related specifically to the deck-building game Dominion.
{
//An enumeration of all possible card types in the deck-building game Dominion at the time of this compilation.
enum class Cardtypes
{
    action
    , attack
    , blank
    , curse
    , duration
    , event
    , looter
    , prize
    , reaction
    , reserve
    , ruins
    , shelter
    , traveler
    , treasure
    , victory
};  //end enum class Cardtypes

inline auto cardtype_vec() -> std::vector<Cardtypes>
{
    return{{Cardtypes::action
        , Cardtypes::attack
        , Cardtypes::blank
        , Cardtypes::curse
        , Cardtypes::duration
        , Cardtypes::event
        , Cardtypes::looter
        , Cardtypes::prize
        , Cardtypes::reaction
        , Cardtypes::reserve
        , Cardtypes::ruins
        , Cardtypes::shelter
        , Cardtypes::traveler
        , Cardtypes::treasure
        , Cardtypes::victory}};
}

inline auto cardtype_from_str(const std::wstring& in) -> Cardtypes
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

inline auto str_from_cardtype(const Cardtypes in) -> std::wstring
{
    switch (in)
    {
    case(Cardtypes::action) :
        return L"Action";
        break;
    case(Cardtypes::attack) :
        return L"Attack";
        break;
    case(Cardtypes::blank) :
        return L"Blank";
        break;
    case(Cardtypes::curse) :
        return L"Curse";
        break;
    case(Cardtypes::duration) :
        return L"Duration";
        break;
    case(Cardtypes::event) :
        return L"Event";
        break;
    case(Cardtypes::looter) :
        return L"Looter";
        break;
    case(Cardtypes::prize) :
        return L"Prize";
        break;
    case(Cardtypes::reaction) :
        return L"Reaction";
        break;
    case(Cardtypes::reserve) :
        return L"Reserve";
        break;
    case(Cardtypes::ruins) :
        return L"Ruins";
        break;
    case(Cardtypes::shelter) :
        return L"Shelter";
        break;
    case(Cardtypes::traveler) :
        return L"Traveler";
        break;
    case(Cardtypes::treasure) :
        return L"Treasure";
        break;
    case(Cardtypes::victory) :
        return L"Victory";
        break;
    default:
        assert(!"reached invalid if statement in string to cardset conversion");
        return L"Action";
    }
}

}	//end namespace Dominion
}	//end namespace SM (sudden magic)

#endif  // CARDTYPES_HPP_INCLUDED