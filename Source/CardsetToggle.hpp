#ifndef CARDSETTOGGLE_HPP_INCLUDED
#define CARDSETTOGGLE_HPP_INCLUDED

/*
  ==============================================================================

    CardsetToggle.hpp
    Created: 22 Sep 2015 10:30:12am
    Author:  caps

  ==============================================================================
*/

#include "Cardsets.hpp"

#include "../JuceLibraryCode/JuceHeader.h"

namespace SM
{
namespace Dominion
{
class CardShuffler;
//==============================================================================
class CardsetToggle : public juce::BooleanPropertyComponent
{
public:
    CardsetToggle(Cardsets, CardShuffler&);
    auto setState (bool newState) -> void override;
private:
    Cardsets set;
    CardShuffler& shuf;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CardsetToggle)
};

}   //end namespace Dominion
}   //end namespace SM

#endif  // CARDSETTOGGLE_HPP_INCLUDED