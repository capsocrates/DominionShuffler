/*
  ==============================================================================

    SettingsDisplay.cpp
    Created: 22 Sep 2015 12:35:42pm
    Author:  caps

  ==============================================================================
*/

#include "SettingsDisplay.hpp"

#include "CardsetToggleListener.hpp"
#include "CardtypeToggleListener.hpp"

#include "cardsets.hpp"
#include "cardtypes.hpp"

#include "sm/utility_make_unique.hpp"

#include "../JuceLibraryCode/JuceHeader.h"

#include "boost/range/adaptor/indirected.hpp"
#include "boost/range/adaptor/transformed.hpp"
#include "boost/range/join.hpp"
#include "boost/range/algorithm/transform.hpp"
#include "boost/range/numeric.hpp"

namespace SM
{
namespace Dominion
{

using toggle = std::unique_ptr<juce::BooleanPropertyComponent>;
using vec_toggles = std::vector<toggle>;

using vec_set = std::vector<CardsetToggleListener>;
using vec_type = std::vector<CardtypeToggleListener>;

template<typename EnumT>
using mapT = std::unordered_map < EnumT
    , juce::Value
    , utility::enum_hash < EnumT >> ;
using map_set_value = mapT<Cardsets>;
using map_type_value = mapT<Cardtypes>;
using set_value_pair = map_set_value::value_type;
using type_value_pair = map_type_value::value_type;

auto make_set_toggle_values() -> map_set_value
{
    /*
    Android compiler was complaining about
    passing a lambda to boost::transformed
    */
    std::function<set_value_pair(Cardsets)> do_transform = [](const Cardsets in) -> set_value_pair
    {
        return std::make_pair(in, juce::Value(juce::var(false)));
    };
    using namespace boost::adaptors;
    return boost::copy_range<map_set_value>(filtered_cardset_vec() | transformed(do_transform));
}

auto make_type_toggle_values() -> map_type_value
{
    /*
    Android compiler was complaining about
    passing a lambda to boost::transformed
    */
    std::function<type_value_pair(Cardtypes)> do_transform = [](const Cardtypes in) -> type_value_pair
    {
        return std::make_pair(in, juce::Value(juce::var(false)));
    };
    using namespace boost::adaptors;
    return boost::copy_range<map_type_value>(filtered_cardtype_vec() | transformed(do_transform));
}

auto make_cardset_toggles(CardShuffler& shuf, map_set_value& values) -> vec_set
{
    /*
    Android compiler was complaining about
    passing a lambda to boost::transformed
    */
    std::function<CardsetToggleListener(Cardsets)> do_transform = [&shuf, &values](const Cardsets in) -> CardsetToggleListener
    {
        CardsetToggleListener temp{in, shuf};
        values.at(in).addListener(temp.getListener());
        return temp;
    };
    using namespace boost::adaptors;
    return boost::copy_range<vec_set>(filtered_cardset_vec() | transformed(do_transform));
}

auto make_cardtype_toggles(CardShuffler& shuf, map_type_value& values) -> vec_type
{
    /*
    Android compiler was complaining about
    passing a lambda to boost::transformed
    */
    std::function<CardtypeToggleListener(Cardtypes)> do_transform = [&shuf
        , &values](const Cardtypes in) -> CardtypeToggleListener
    {
        CardtypeToggleListener temp{in, shuf};
        values.at(in).addListener(temp.getListener());
        return temp;
    };
    using namespace boost::adaptors;
    return boost::copy_range<vec_type>(filtered_cardtype_vec() | transformed(do_transform));
}

auto make_toggle_buttons(const map_set_value& sets, const map_type_value& types) -> vec_toggles
{
    auto setF = [](const set_value_pair& val) -> toggle
    {
        return SM::utility::make_unique<juce::BooleanPropertyComponent>(
            val.second
            , pretty_str_from_cardset(val.first).c_str()
            , "");
    };
    auto typeF = [](const type_value_pair& val) -> toggle
    {
        return SM::utility::make_unique<juce::BooleanPropertyComponent>(
            val.second
            , str_from_cardtype(val.first).c_str()
            , "");
    };
    vec_toggles return_vec(sets.size() + types.size());
    boost::transform(sets, return_vec.begin(), setF);
    boost::transform(types, return_vec.begin() + sets.size(), typeF);
    return return_vec;
}

//==============================================================================
SettingsDisplay::SettingsDisplay(CardShuffler& shuf)
    : view(L"SettingsView")
    , subview(L"Display")
    , setToggleValues(make_set_toggle_values())
    , typeToggleValues(make_type_toggle_values())
    , setToggleListeners(make_cardset_toggles(shuf, setToggleValues))
    , typeToggleListeners(make_cardtype_toggles(shuf, typeToggleValues))
    , toggles(make_toggle_buttons(setToggleValues, typeToggleValues))
{
    addAndMakeVisible(view);
    view.centreWithSize(getWidth(), getHeight());
    view.setViewedComponent(&subview, false);
    constexpr auto margin(int{5});
    constexpr auto height(int{25});
    const auto width(view.getWidth() - view.getScrollBarThickness());
    auto& subviewRef(subview);
    auto align_tops = [&subviewRef
        , width
        , height
        , margin](const int top
                  , juce::BooleanPropertyComponent& next) -> int
    {
        subviewRef.addAndMakeVisible(&next);
        next.centreWithSize(width, height);
        next.setTopLeftPosition(margin, top);
        next.setState(true);
        return next.getBottom() + margin;
    };
    using namespace boost::adaptors;
    subview.centreWithSize(width,
                           boost::accumulate(toggles
                                             | indirected
                                             , margin
                                             , align_tops));
}

SettingsDisplay::~SettingsDisplay()
{}

void SettingsDisplay::paint(juce::Graphics& /*g*/) const
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    //g.fillAll(juce::Colours::white);   // clear the background

    //g.setColour(juce::Colours::grey);
    //g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

    //g.setColour(juce::Colours::lightblue);
    //g.setFont(14.0f);
    //g.drawText("SettingsDisplay", getLocalBounds(),
    //           juce::Justification::centred, true);   // draw some placeholder text
}

void SettingsDisplay::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    view.centreWithSize(getWidth(), getHeight());
    subview.centreWithSize(view.getWidth() - view.getScrollBarThickness(), subview.getHeight());
    subview.setTopLeftPosition(0, 0);

    for (auto& in : toggles)
    {
        auto margin(int{in->getX()});
        auto top(int{in->getY()});
        in->centreWithSize(view.getViewWidth() - margin, in->getHeight());
        in->setTopLeftPosition(margin, top);
    }
}

}   //end namespace Dominion
}   //end namespace SM