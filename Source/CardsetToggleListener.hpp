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

#include <memory>

namespace SM
{
namespace Dominion
{
enum class Cardsets;
class CardShuffler;
class CardsetToggleListener
{
    /*
    The method I use to create these listeners involves
    creating them in a function, then passing them to
    value->addListener() by pointer, then returning them
    from the function, which invalidates their addres.
    So I stored the listener as a pointer inside this class,
    so this class can be passed around without invalidating the
    address of the listener. This also means I can move
    the ListenImpl into another file as a compilation firewall
    if I want to.
    */
    class ListenImpl : public juce::Value::Listener
    {
    public:
        ListenImpl(Cardsets, CardShuffler&);
        auto valueChanged(juce::Value&) -> void override;
        auto getCardset() const->Cardsets;
    private:
        Cardsets set;
        CardShuffler& shuf;
    };  //end class ListenImpl
    std::unique_ptr<ListenImpl> impl;
public:
    CardsetToggleListener(const Cardsets, CardShuffler&);
    auto getCardset() const -> Cardsets;
    auto getListener() -> ListenImpl *const;
};  //end class CardsetToggleListener
}   //end namespace Dominion
}   //end namespace SM

#endif  // CARDSETTOGGLELISTENER_HPP_INCLUDED