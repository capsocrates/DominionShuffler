/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

#include "CardImport.hpp"
#include "CardShuffler.hpp"
#include "RandomizerCard.hpp"

#include <boost/range/algorithm/transform.hpp>

//==============================================================================
MainContentComponent::MainContentComponent()
    : cards(SM::Dominion::read_cards())
    , cardDisplayModel()
    , cardDisplay(new juce::ListBox("cardDisplay", &cardDisplayModel))
    , shuffleButtonClicked(*this)
    , shuffleButton(new juce::TextButton(L"shuffleButton", L"Shuffle the cards and display them."))
{
    setSize(250, 350);

    addAndMakeVisible(*cardDisplay.get());
    cardDisplay->centreWithSize(getWidth(), 220);

    addAndMakeVisible(*shuffleButton.get());
    shuffleButton->setTopLeftPosition(5, cardDisplay->getBottom() + 5);

    shuffleButton->addListener(&shuffleButtonClicked);

    shuffle();
}

MainContentComponent::~MainContentComponent()
{}

void MainContentComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(0xff001F36));

    g.setFont(juce::Font(16.0f));
    g.setColour(juce::Colours::white);
    g.drawText("Hello World!", getLocalBounds(), juce::Justification::centred, true);
}

void MainContentComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}

void MainContentComponent::shuffle()
{
    boost::transform(shuf.shuffle(cards, 10),
                     cardDisplayModel.back_inserter(),
                     [](const SM::Dominion::RandomizerCard& in) -> std::wstring
    {
        return in.name;
    });
    cardDisplay->updateContent();
}
