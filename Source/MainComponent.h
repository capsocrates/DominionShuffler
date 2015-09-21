#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "CardShuffler.hpp"

#include "sm\StringListBoxModel.hpp"

#include "../JuceLibraryCode/JuceHeader.h"

#include <memory>

namespace SM { namespace Dominion { class RandomizerCard; } }

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
    void shuffle();

    SM::Dominion::CardShuffler shuf;
    std::vector<SM::Dominion::RandomizerCard> cards;

    SM::StringListBoxModel cardDisplayModel;
    std::unique_ptr<juce::ListBox> cardDisplay;
    class shuffleListener : public juce::TextButton::Listener 
    {
    private:
        MainContentComponent& main;
    public:
        shuffleListener(MainContentComponent& main) : juce::TextButton::Listener(), main(main) {};
        void buttonClicked(juce::Button* /*btn*/) override
        {
            main.shuffle();
        }
    };
    shuffleListener shuffleButtonClicked;
    std::unique_ptr<juce::TextButton> shuffleButton;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED