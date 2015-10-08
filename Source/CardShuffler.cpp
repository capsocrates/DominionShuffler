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

#include "sm/utility_make_unique.hpp"

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
    disable(Cardsets::base);
    disable(Cardtypes::blank);
    disable(Cardtypes::curse);
    disable(Cardtypes::ruins);
    disable(Cardtypes::shelter);
}
auto CardShuffler::enable(const Cardsets in) -> void
{
    //enabling a Cardset will actually be removing the filter that is keeping it from sticking around
    const CardsetFilter filter_to_remove{in};
    if (filterExistsAlready(filter_to_remove))
        pre_filters.erase(findFilter(filter_to_remove));
}
auto CardShuffler::disable(const Cardsets in) -> void
{
    //disabling a Cardset means adding a filter that will exclude it
    const CardsetFilter new_filter{in};
    if (!filterExistsAlready(new_filter))
        pre_filters.emplace_back(SM::utility::make_unique<CardsetFilter>(new_filter));
}
auto CardShuffler::isEnabled(const Cardsets in) const -> bool
{
    return !filterExistsAlready(CardsetFilter{in});
}
auto CardShuffler::enable(const Cardtypes in) -> void
{
    //enabling a Cardtype will actually be removing the filter that is keeping it from sticking around
    const CardtypeFilter filter_to_remove{in};
    if (filterExistsAlready(filter_to_remove))
        pre_filters.erase(findFilter(filter_to_remove));
}
auto CardShuffler::disable(const Cardtypes in) -> void
{
    //disabling a Cardtype means adding a filter that will exclude it
    const CardtypeFilter new_filter{in};
    if (!filterExistsAlready(new_filter))
        pre_filters.emplace_back(SM::utility::make_unique<CardtypeFilter>(new_filter));
}
auto CardShuffler::isEnabled(const Cardtypes in) const -> bool
{
    return !filterExistsAlready(CardtypeFilter{in});
}
auto CardShuffler::setMin(const Cardsets in, const int new_min) -> void
{
    setMin(in, new_min, sets_min_max);
}
auto CardShuffler::setMax(const Cardsets in, const int new_max) -> void
{
    setMax(in, new_max, sets_min_max);
}
auto CardShuffler::getMin(const Cardsets in) const -> int
{
    return getMin(in, sets_min_max);
}
auto CardShuffler::getMax(const Cardsets in) const -> int
{
    return getMax(in, sets_min_max);
}
auto CardShuffler::setMin(const Cardtypes in, const int new_min) -> void
{
    setMin(in, new_min, types_min_max);
}
auto CardShuffler::setMax(const Cardtypes in, const int new_max) -> void
{
    setMax(in, new_max, types_min_max);
}
auto CardShuffler::getMin(const Cardtypes in) const -> int
{
    return getMin(in, types_min_max);
}
auto CardShuffler::getMax(const Cardtypes in) const -> int
{
    return getMax(in, types_min_max);
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