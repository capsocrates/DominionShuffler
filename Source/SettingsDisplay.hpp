#ifndef SETTINGSDISPLAY_H_INCLUDED
#define SETTINGSDISPLAY_H_INCLUDED

/*
  ==============================================================================

    SettingsDisplay.hpp
    Created: 22 Sep 2015 12:35:42pm
    Author:  caps

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"

#include <memory>
#include <unordered_map>

namespace SM
{
namespace Dominion
{

enum class Cardsets;
enum class Cardtypes;
class CardsetToggleListener;
class CardtypeToggleListener;
class CardShuffler;
//==============================================================================
class SettingsDisplay    : public juce::Component
{
public:
    explicit SettingsDisplay(CardShuffler& shuf);
    ~SettingsDisplay();

    void paint (juce::Graphics&) const;
    void resized();

private:
    juce::Viewport view;
    juce::Component subview;
    std::unordered_map<Cardsets, juce::Value> setToggleValues;
    std::unordered_map<Cardtypes, juce::Value> typeToggleValues;
    std::vector<CardsetToggleListener> setToggleListeners;
    std::vector<CardtypeToggleListener> typeToggleListeners;
    std::vector<std::unique_ptr<juce::BooleanPropertyComponent>> toggles;
    //std::vector<std::unique_ptr<CardsetToggle>> cardset_toggles;
    //std::vector<std::unique_ptr<CardtypeToggle>> cardtype_toggles;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingsDisplay)
};

}   //end namespace Dominion
}   //end namespace SM


#endif  // SETTINGSDISPLAY_H_INCLUDED
