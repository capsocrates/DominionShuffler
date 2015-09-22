#ifndef CARDTYPETOGGLELISTENER_HPP_INCLUDED
#define CARDTYPETOGGLELISTENER_HPP_INCLUDED

/*
  ==============================================================================

    CardtypeToggleListener.hpp
    Created: 22 Sep 2015 4:02:54pm
    Author:  caps

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"

namespace SM
{
namespace Dominion
{
enum class Cardtypes;
class CardShuffler;
class CardtypeToggleListener : public juce::Value::Listener
{
public:
    CardtypeToggleListener(Cardtypes, CardShuffler&);
    auto valueChanged(juce::Value&) -> void override;
private:
    Cardtypes type;
    CardShuffler& shuf;
};  //end class CardtypeToggleListener
}   //end namespace Dominion
}   //end namespace SM

#endif  // CARDTYPETOGGLELISTENER_HPP_INCLUDED