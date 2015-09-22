#ifndef CARDSHUFFLEDISPLAY_HPP_INCLUDED
#define CARDSHUFFLEDISPLAY_HPP_INCLUDED

/*
  ==============================================================================

    CardShuffleDisplay.hpp
    Created: 22 Sep 2015 8:20:12am
    Author:  caps

  ==============================================================================
*/

#include "CardShuffler.hpp"
#include "sm\StringListBoxModel.hpp"

#pragma warning(push, 0)
#include "../JuceLibraryCode/JuceHeader.h"
#pragma warning(pop)

#include <vector>

//==============================================================================

namespace SM
{
namespace Dominion
{

class CardShuffleDisplay : public juce::Component
{
public:
    CardShuffleDisplay(CardShuffler&);
    ~CardShuffleDisplay();

    void paint (juce::Graphics&) const;
    void resized();

private:
    SM::StringListBoxModel cardDisplayModel;
    juce::ListBox cardDisplayList;
    class shuffleListener : public juce::TextButton::Listener
    {
    private:
        CardShuffleDisplay& main;
    public:
        explicit shuffleListener(CardShuffleDisplay& main) : juce::TextButton::Listener(), main(main) {};
        void buttonClicked(juce::Button* /*btn*/) override
        {
            main.shuffle();
        }
    };
    shuffleListener shuffleButtonClicked;
    juce::TextButton shuffleButton;

    CardShuffler& shuf;
    std::vector<SM::Dominion::RandomizerCard> cards;

    auto shuffle() -> void;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CardShuffleDisplay)
};

}   //end namespace Dominion
}   //end namespace SM

#endif  // CARDSHUFFLEDISPLAY_HPP_INCLUDED
