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
CardtypeToggleListener::ListenImpl::ListenImpl(Cardtypes type, CardShuffler& shuf)
    : type(type)
    , shuf(shuf)
{
}

auto CardtypeToggleListener::ListenImpl::valueChanged(juce::Value& val) -> void
{
    assert(val.getValue().isBool());
    if (val.getValue().operator bool())
        shuf.enable(type);
    else
        shuf.disable(type);
}

auto CardtypeToggleListener::ListenImpl::getCardtype() const -> Cardtypes
{
    return type;
}

CardtypeToggleListener::CardtypeToggleListener(const Cardtypes type, CardShuffler& shuf)
    : impl{std::make_unique<CardtypeToggleListener::ListenImpl>(type, shuf)}
{
}

auto CardtypeToggleListener::getCardtype() const -> Cardtypes
{
    return impl->getCardtype();
}

auto CardtypeToggleListener::getListener() -> ListenImpl *const
{
    return impl.get();
}

}   //end namespace Dominion
}   //end namepsace SM