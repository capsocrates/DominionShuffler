/*
  ==============================================================================

    CardtypeToggleListener.cpp
    Created: 22 Sep 2015 4:02:54pm
    Author:  caps

  ==============================================================================
*/

#include "CardtypeToggleListener.hpp"

#include "cardtypes.hpp"
#include "CardShuffler.hpp"

#include <cassert>

namespace SM
{
namespace Dominion
{
CardtypeToggleListener::CardtypeToggleListener(Cardtypes type, CardShuffler& shuf)
    : type(type)
    , shuf(shuf)
{
}

auto CardtypeToggleListener::valueChanged(juce::Value& val) -> void
{
    assert(val.getValue().isBool());
    if (val.getValue().operator bool())
        shuf.enableCardtype(type);
    else
        shuf.disableCardtype(type);
}

}   //end namespace Dominion
}   //end namepsace SM