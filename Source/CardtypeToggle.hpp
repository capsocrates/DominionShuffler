#ifndef CARDTYPETOGGLE_HPP_INCLUDED
#define CARDTYPETOGGLE_HPP_INCLUDED

/*
  ==============================================================================

    CardtypeToggle.hpp
    Created: 22 Sep 2015 10:30:12am
    Author:  caps

  ==============================================================================
*/

#include "Cardtypes.hpp"

#include "../JuceLibraryCode/JuceHeader.h"

namespace SM
{
namespace Dominion
{
class CardShuffler;
//==============================================================================
class CardtypeToggle : public juce::BooleanPropertyComponent
{
public:
    CardtypeToggle(Cardtypes, CardShuffler&);
    auto setState (bool newState) -> void override;
private:
    Cardtypes type;
    CardShuffler& shuf;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CardtypeToggle)
};

}   //end namespace Dominion
}   //end namespace SM

#endif  // CARDTYPETOGGLE_HPP_INCLUDED