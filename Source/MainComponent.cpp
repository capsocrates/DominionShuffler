/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "card_import.hpp"
#include "randomizer_card.hpp"

#include "StringListBoxModel.hpp"

#include "MainComponent.h"

//==============================================================================
MainContentComponent::MainContentComponent()
    : cardDisplay(new juce::ListBox("cardDisplay", new SM::StringListBoxModel()))
{
    setSize(600, 400);

    auto cards = SM::dominion::read_cards();
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
