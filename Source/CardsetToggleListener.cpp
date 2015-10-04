/*
  ==============================================================================

    CardsetToggleListener.cpp
    Created: 22 Sep 2015 3:43:02pm
    Author:  caps

  ==============================================================================
*/

#include "CardsetToggleListener.hpp"

#include "cardsets.hpp"
#include "CardShuffler.hpp"

#include <cassert>

namespace SM
{
namespace Dominion
{
CardsetToggleListener::ListenImpl::ListenImpl(Cardsets set, CardShuffler& shuf)
    : set(set)
    , shuf(shuf)
{
}

auto CardsetToggleListener::ListenImpl::valueChanged(juce::Value& val) -> void
{
    assert(val.getValue().isBool());
    if (val.getValue().operator bool())
        shuf.enableCardset(set);
    else
        shuf.disableCardset(set);
}

auto CardsetToggleListener::ListenImpl::getCardset() const -> Cardsets
{
    return set;
}

CardsetToggleListener::CardsetToggleListener(const Cardsets set, CardShuffler& shuf)
    : impl{std::make_unique<CardsetToggleListener::ListenImpl>(set, shuf)}
{
}

auto CardsetToggleListener::getCardset() const -> Cardsets
{
    return impl->getCardset();
}

auto CardsetToggleListener::getListener() -> ListenImpl *const
{
    return impl.get();
}

}   //end namespace Dominion
}   //end namepsace SM