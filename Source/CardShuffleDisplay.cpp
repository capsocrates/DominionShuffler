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
#include <boost/range/numeric.hpp>

namespace SM
{
namespace Dominion
{

//==============================================================================
CardShuffleDisplay::CardShuffleDisplay(CardShuffler& shuf)
    : cardDisplayModel(SM::StringListBoxModel(10))
    , cardDisplayList(L"cardDisplayList", &cardDisplayModel)
    , shuffleButtonClicked(shuffleListener(*this))
    , shuffleButton(L"Shuffle", L"Shuffle the cards and display them.")
    , shuf(shuf)
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
{}

void CardShuffleDisplay::paint(juce::Graphics& g) const
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll(juce::Colours::black);   // clear the background

    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component
}

void CardShuffleDisplay::resized()
{
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
        return in.name
            + L" SET:" + pretty_str_from_cardset(in.set)
            + L" TYPES:" + boost::accumulate(in.applicable_types
                                             , std::wstring{}
                                             , [](std::wstring& acc
                                                  , const Cardtypes in) -> std::wstring
        {
            return acc + (!acc.empty() ? L"," : L"") + str_from_cardtype(in);
        });
    });
    cardDisplayList.updateContent();
    cardDisplayList.repaint();
}

}   //end namespace Dominion
}   //end namespace SM