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

auto make_cardset_toggles(CardShuffler& shuf) -> vec_set
{
    using namespace boost::adaptors;
    return boost::copy_range<vec_set>(cardset_vec()
                                      | transformed([&shuf](const Cardsets in) -> CardsetToggleListener
    {
        return{in, shuf};
    }));
}

auto make_cardtype_toggles(CardShuffler& shuf) -> vec_type
{
    using namespace boost::adaptors;
    return boost::copy_range<vec_type>(cardtype_vec()
                                       | transformed([&shuf](const Cardtypes in) -> CardtypeToggleListener
    {
        return{in, shuf};
    }));
}

auto make_toggle_buttons() -> vec_toggles
{
    auto typeF = []() -> auto {};
    auto setF = []() -> auto {};
    using namespace boost::adaptors;
    return boost::copy_range<vec_toggles>(boost::join(cardtype_vec()
                                                      | transformed(typeF)
                                                      , cardset_vec()
                                                      | transformed(setF)));
}

//==============================================================================
SettingsDisplay::SettingsDisplay(CardShuffler& shuf)
    : view(L"SettingsView")
    , subview(L"Display")
    , setToggleListeners(make_cardset_toggles(shuf))
    , typeToggleListeners(make_cardtype_toggles(shuf))
    , toggles(make_toggle_buttons())
{
    addAndMakeVisible(view);
    view.centreWithSize(getWidth(), getHeight());
    view.addAndMakeVisible(subview);
    constexpr auto margin(int{5});
    constexpr auto height(int{25});
    auto align_tops = [&](const auto top, juce::BooleanPropertyComponent& next) -> int
    {
        subview.addAndMakeVisible(&next);
        next.centreWithSize(this->getWidth(), height);
        next.setTopLeftPosition(margin, top);
        next.setState(true);
        return next.getBottom() + margin;
    };
    using namespace boost::adaptors;
    subview.centreWithSize(view.getWidth(),
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
    subview.centreWithSize(view.getWidth(), subview.getHeight());
    subview.setTopLeftPosition(0, 0);

    for (auto& in : toggles)
    {
        auto margin(int{in->getX()});
        auto top(int{in->getY()});
        in->centreWithSize(getWidth() - margin, in->getHeight());
        in->setTopLeftPosition(margin, top);
    }
}

}   //end namespace Dominion
}   //end namespace SM