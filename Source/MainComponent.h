#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "sm\StringListBoxModel.hpp"

#include "../JuceLibraryCode/JuceHeader.h"

#include <memory>

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

    void paint(juce::Graphics&);
    void resized();

private:
    SM::StringListBoxModel cardDisplayModel;
    std::unique_ptr<juce::ListBox> cardDisplay;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED