#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "CardShuffleDisplay.hpp"
#include "SettingsDisplay.hpp"

#pragma warning(push, 0)
#include "../JuceLibraryCode/JuceHeader.h"
#pragma warning(pop)

#include <vector>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent : public juce::Component
{
public:
    //==============================================================================
    MainContentComponent();
    ~MainContentComponent();

    void paint(juce::Graphics&) const;
    void resized();

private:
    juce::TabbedComponent tabs;
    SM::Dominion::CardShuffler shuf;
    SM::Dominion::CardShuffleDisplay cardDisplay;
    SM::Dominion::SettingsDisplay settingsDisplay;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED