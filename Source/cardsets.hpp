#ifndef CARDSETS_HPP_INCLUDED
#define CARDSETS_HPP_INCLUDED

/*
  ==============================================================================

    Cardsets.hpp
    Created: 14 Sep 2015 2:09:19pm
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
//An enumeration of all of the sets published in the deck-building game Dominion at the time of this compilation.
enum class Cardsets
{
    alchemy
    , base
    , cornucopia
    , dark_ages
    , dominion
    , guilds
    , hinterlands
    , intrigue
    , promo
    , prosperity
    , seaside
};  //end enum class Cardsets

inline auto cardset_vec() -> std::vector<Cardsets>
{
    return{{Cardsets::alchemy
           , Cardsets::base
           , Cardsets::cornucopia
           , Cardsets::dark_ages
           , Cardsets::dominion
           , Cardsets::guilds
           , Cardsets::hinterlands
           , Cardsets::intrigue
           , Cardsets::promo
           , Cardsets::prosperity
           , Cardsets::seaside}};
}

inline auto filtered_cardset_vec() -> std::vector<Cardsets>
{
    return{{Cardsets::alchemy
        , Cardsets::cornucopia
        , Cardsets::dark_ages
        , Cardsets::dominion
        , Cardsets::guilds
        , Cardsets::hinterlands
        , Cardsets::intrigue
        , Cardsets::promo
        , Cardsets::prosperity
        , Cardsets::seaside}};
}

inline auto cardset_from_str(const std::wstring& cardset) -> Cardsets
{
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

inline auto pretty_str_from_cardset(const Cardsets in)->std::wstring
{
    switch (in)
    {
    case(Cardsets::alchemy) :
        return L"Alchemy";
        break;
    case(Cardsets::base) :
        return L"Base Cards";
        break;
    case(Cardsets::cornucopia) :
        return L"Cornucopia";
        break;
    case(Cardsets::dark_ages) :
        return L"Dark Ages";
        break;
    case(Cardsets::dominion) :
        return L"Dominion";
        break;
    case(Cardsets::guilds) :
        return L"Guilds";
        break;
    case(Cardsets::hinterlands) :
        return L"Hinterlands";
        break;
    case(Cardsets::intrigue) :
        return L"Intrigue";
        break;
    case(Cardsets::promo) :
        return L"Promo Cards";
        break;
    case(Cardsets::prosperity) :
        return L"Prosperity";
        break;
    case(Cardsets::seaside) :
        return L"Seaside";
        break;
    default:
        assert(!"reached invalid if statement in cardset to pretty string conversion");
        return L"Base";
    }
}

inline auto str_from_cardset(const Cardsets in) -> std::wstring
{
    switch (in)
    {
    case(Cardsets::alchemy) :
        return L"alchemy";
        break;
    case(Cardsets::base) :
        return L"base";
        break;
    case(Cardsets::cornucopia) :
        return L"cornucopia";
        break;
    case(Cardsets::dark_ages) :
        return L"dark";
        break;
    case(Cardsets::dominion) :
        return L"dominion";
        break;
    case(Cardsets::guilds) :
        return L"guilds";
        break;
    case(Cardsets::hinterlands) :
        return L"hinterlands";
        break;
    case(Cardsets::intrigue) :
        return L"intrigue";
        break;
    case(Cardsets::promo) :
        return L"promo";
        break;
    case(Cardsets::prosperity) :
        return L"prosperity";
        break;
    case(Cardsets::seaside) :
        return L"seaside";
        break;
    default:
        assert(!"reached invalid if statement in cardset to string conversion");
        return L"base";
    }

}

}	//end namespace Dominion
}	//end namespace SM (sudden magic)

#endif  // CARDSETS_HPP_INCLUDED