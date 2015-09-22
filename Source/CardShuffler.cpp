/*
  ==============================================================================

    card_shuffler.cpp
    Created: 21 Sep 2015 1:51:09pm
    Author:  caps

  ==============================================================================
*/

#include "CardShuffler.hpp"

#include "Cardsets.hpp"
#include "Cardtypes.hpp"
#include "RandomizerCard.hpp"

#include "boost/range/algorithm/find.hpp"
#include "boost/range/algorithm/find_if.hpp"

namespace SM
{
namespace Dominion
{

class CardsetFilter : public CardFilter
{
    Cardsets set;
    bool cardsetIsAllowed;
    virtual auto checkFilter(const RandomizerCard& in) const -> bool
    {
        //should return true if the cardset is allowed and the incoming card has that cardset, OR true if the sets don't match
        return (cardsetIsAllowed && in.set == set) || in.set != set;
    }
    virtual auto getUniqueID() const -> std::wstring
    {
        return std::wstring(cardsetIsAllowed ? L"enables " : L"disables ") + str_from_cardset(set);
    }
public:
    explicit CardsetFilter(const Cardsets set, const bool cardsetIsAllowed)
        : CardFilter()
        , set(set)
        , cardsetIsAllowed(cardsetIsAllowed)
    {}
};

class CardtypeFilter : public CardFilter
{
    Cardtypes type;
    bool cardtypeIsAllowed;
    virtual auto checkFilter(const RandomizerCard& in) const -> bool
    {
        //should return true if the cardset is allowed and the incoming card has that cardset, OR true if the sets don't match
        const bool types_found(boost::find(in.applicable_types, type) != boost::end(in.applicable_types));
        return (cardtypeIsAllowed && types_found) || !types_found;
    }
    auto getUniqueID() const -> std::wstring
    {
        return std::wstring(cardtypeIsAllowed ? L"enables " : L"disables ") + str_from_cardtype(type);
    }
public:
    explicit CardtypeFilter(const Cardtypes type, const bool cardtypeIsAllowed)
        : CardFilter()
        , type(type)
        , cardtypeIsAllowed(cardtypeIsAllowed)
    {}
};

CardShuffler::CardShuffler()
    : generator(engine())
{
    disableCardset(Cardsets::alchemy);
    disableCardset(Cardsets::base);
    disableCardset(Cardsets::cornucopia);
    disableCardset(Cardsets::dark_ages);
    disableCardset(Cardsets::guilds);
    disableCardset(Cardsets::hinterlands);
    disableCardset(Cardsets::intrigue);
    disableCardset(Cardsets::promo);
    disableCardset(Cardsets::prosperity);
    disableCardset(Cardsets::seaside);
}
void CardShuffler::enableCardset(Cardsets in)
{
    //enabling a Cardset will actually be removing the filter that is keeping it from sticking around
    auto filter_to_remove = std::unique_ptr<CardFilter>(new CardsetFilter{in, true});
    if (filterExistsAlready(*filter_to_remove))
    {
        filters.erase(findFilter(*filter_to_remove));
    }
}
void CardShuffler::disableCardset(Cardsets in)
{
    //disabling a Cardset means adding a filter that will exclude it
    auto new_filter = std::unique_ptr<CardFilter>(new CardsetFilter{in, false});
    if (!filterExistsAlready(*new_filter))
        filters.emplace_back(std::move(new_filter));
}
void CardShuffler::enableCardtype(Cardtypes in)
{
    //enabling a Cardtype will actually be removing the filter that is keeping it from sticking around
    auto filter_to_remove = std::unique_ptr<CardFilter>(new CardtypeFilter{in, true});
    if (filterExistsAlready(*filter_to_remove))
        filters.erase(findFilter(*filter_to_remove));
}
void CardShuffler::disableCardtype(Cardtypes in)
{
    //disabling a Cardtype means adding a filter that will exclude it
    auto new_filter = std::unique_ptr<CardFilter>(new CardtypeFilter{in, false});
    if (!filterExistsAlready(*new_filter))
        filters.emplace_back(std::move(new_filter));
}
auto CardShuffler::findFilter(const CardFilter& filter) const -> filter_citr
{
    return boost::find_if(filters,
                          [&filter](const auto& lhs)
    {
        return lhs->uniqueID() == filter.uniqueID();
    });
}
auto CardShuffler::filterExistsAlready(const CardFilter& filter) const -> bool
{
    return findFilter(filter) != boost::end(filters);
}

}   //end namespace Dominion
}   //end namespace SM