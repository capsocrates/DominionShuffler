#ifndef CARDSETTOGGLELISTENER_HPP_INCLUDED
#define CARDSETTOGGLELISTENER_HPP_INCLUDED

/*
  ==============================================================================

    CardsetToggleListener.hpp
    Created: 22 Sep 2015 3:43:02pm
    Author:  caps

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"

namespace SM
{
namespace Dominion
{
enum class Cardsets;
class CardShuffler;
class CardsetToggleListener : public juce::Value::Listener
{
public:
    CardsetToggleListener(Cardsets, CardShuffler&);
    auto valueChanged(juce::Value&) -> void override;
private:
    Cardsets set;
    CardShuffler& shuf;
};  //end class CardsetToggleListener
}   //end namespace Dominion
}   //end namespace SM

#endif  // CARDSETTOGGLELISTENER_HPP_INCLUDED