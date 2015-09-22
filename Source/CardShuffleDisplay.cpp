/*
  ==============================================================================

    CardShuffleDisplay.cpp
    Created: 22 Sep 2015 8:20:12am
    Author:  caps

  ==============================================================================
*/

#include "CardImport.hpp"
#include "CardShuffler.hpp"
#include "RandomizerCard.hpp"

#include "CardShuffleDisplay.hpp"

#include <boost/range/algorithm/transform.hpp>

//==============================================================================
CardShuffleDisplay::CardShuffleDisplay()
    : cardDisplayModel(SM::StringListBoxModel(10))
    , cardDisplayList(L"cardDisplayList", &cardDisplayModel)
    , shuffleButtonClicked(shuffleListener(*this))
    , shuffleButton(L"Shuffle", L"Shuffle the cards and display them.")
    , shuf()
    , cards(SM::Dominion::read_cards())
{
    addAndMakeVisible(&cardDisplayList);
    cardDisplayList.centreWithSize(getWidth(), 220);

    addAndMakeVisible(&shuffleButton);
    shuffleButton.changeWidthToFitText(35);
    shuffleButton.centreWithSize(shuffleButton.getWidth(), shuffleButton.getHeight());
    shuffleButton.setTopLeftPosition(shuffleButton.getX(), cardDisplayList.getBottom() + 5);
    shuffleButton.addListener(&shuffleButtonClicked);
    
    shuffle();
}

CardShuffleDisplay::~CardShuffleDisplay()
{
}

void CardShuffleDisplay::paint (juce::Graphics& g) const
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (juce::Colours::white);   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::lightblue);
    g.setFont (14.0f);
    g.drawText ("CardShuffleDisplay", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void CardShuffleDisplay::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    cardDisplayList.centreWithSize(getWidth(), 220);
    shuffleButton.centreWithSize(shuffleButton.getWidth(), shuffleButton.getHeight());
    shuffleButton.setTopLeftPosition(shuffleButton.getX(), cardDisplayList.getBottom() + 5);
}

auto CardShuffleDisplay::shuffle() -> void
{
    boost::transform(shuf.shuffle(cards, 10),
                     begin(cardDisplayModel),
                     [](const SM::Dominion::RandomizerCard& in) -> std::wstring
    {
        return in.name;
    });
    cardDisplayList.updateContent();
    cardDisplayList.repaint();
}