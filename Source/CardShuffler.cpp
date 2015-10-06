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
    virtual auto checkFilter(const RandomizerCard& in) const -> bool
    {
        //should return true if the cardset is allowed and the incoming card has that cardset, OR true if the sets don't match
        return in.set != set;
    }
    virtual auto getUniqueID() const -> std::wstring
    {
        return std::wstring(L"disables ") + str_from_cardset(set);
    }
public:
    explicit CardsetFilter(const Cardsets set)
        : CardFilter()
        , set(set)
    {}
};

class CardtypeFilter : public CardFilter
{
    Cardtypes type;
    virtual auto checkFilter(const RandomizerCard& in) const -> bool
    {
        //should return true if the cardset is allowed and the incoming card has that cardset, OR true if the sets don't match
        const bool types_found(boost::find(in.applicable_types, type) != boost::end(in.applicable_types));
        return !types_found;
    }
    auto getUniqueID() const -> std::wstring
    {
        return std::wstring(L"disables ") + str_from_cardtype(type);
    }
public:
    explicit CardtypeFilter(const Cardtypes type)
        : CardFilter()
        , type(type)
    {}
};

CardShuffler::CardShuffler()
    : generator(engine())
{
    disableCardset(Cardsets::base);
    disableCardtype(Cardtypes::blank);
    disableCardtype(Cardtypes::curse);
    disableCardtype(Cardtypes::ruins);
    disableCardtype(Cardtypes::shelter);
}
void CardShuffler::enableCardset(Cardsets in)
{
    //enabling a Cardset will actually be removing the filter that is keeping it from sticking around
    CardsetFilter filter_to_remove{in};
    if (filterExistsAlready(filter_to_remove))
        pre_filters.erase(findFilter(filter_to_remove));
}
void CardShuffler::disableCardset(Cardsets in)
{
    //disabling a Cardset means adding a filter that will exclude it
    //auto new_filter = std::make_unique<CardsetFilter>(in);
    CardsetFilter new_filter{in};
    if (!filterExistsAlready(new_filter))
        pre_filters.emplace_back(std::make_unique<CardsetFilter>(new_filter));
}
auto CardShuffler::cardsetEnabled(Cardsets in) -> bool
{
    return !filterExistsAlready(CardsetFilter{in});
}
void CardShuffler::enableCardtype(Cardtypes in)
{
    //enabling a Cardtype will actually be removing the filter that is keeping it from sticking around
    CardtypeFilter filter_to_remove{in};
    if (filterExistsAlready(filter_to_remove))
        pre_filters.erase(findFilter(filter_to_remove));
}
void CardShuffler::disableCardtype(Cardtypes in)
{
    //disabling a Cardtype means adding a filter that will exclude it
    CardtypeFilter new_filter{in};
    if (!filterExistsAlready(new_filter))
        pre_filters.emplace_back(std::make_unique<CardtypeFilter>(new_filter));
}
auto CardShuffler::cardtypeEnabled(Cardtypes in) -> bool
{
    return !filterExistsAlready(CardtypeFilter{in});
}
auto CardShuffler::findFilter(const CardFilter& filter) -> filter_itr
{
    return boost::find_if(pre_filters,
                          [&filter](const filterT& lhs)
    {
        return lhs->uniqueID() == filter.uniqueID();
    });
}
auto CardShuffler::findFilter(const CardFilter& filter) const -> filter_citr
{
    return boost::find_if(pre_filters,
                          [&filter](const filterT& lhs)
    {
        return lhs->uniqueID() == filter.uniqueID();
    });
}
auto CardShuffler::filterExistsAlready(const CardFilter& filter) const -> bool
{
    return findFilter(filter) != boost::end(pre_filters);
}

}   //end namespace Dominion
}   //end namespace SM