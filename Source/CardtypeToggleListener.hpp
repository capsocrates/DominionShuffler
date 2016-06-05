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

#include <memory>

namespace SM
{
namespace Dominion
{
enum class Cardtypes;
class CardShuffler;
class CardtypeToggleListener
{
    /*
    The method I use to create these listeners involves
    creating them in a function, then passing them to
    value->addListener() by pointer, then returning them
    from the function, which invalidates their address.
    So I stored the listener as a pointer inside this class,
    so this class can be passed around without invalidating the
    address of the listener. This also means I can move
    the ListenImpl into another file as a compilation firewall
    if I want to.
    */
    class ListenImpl : public juce::Value::Listener
    {
    public:
        ListenImpl(const Cardtypes, CardShuffler&);
        auto valueChanged(juce::Value&) -> void override;
        auto getCardtype() const->Cardtypes;
    private:
        Cardtypes type;
        CardShuffler& shuf;
    };  //end class ListenImpl
    std::unique_ptr<ListenImpl> impl;
public:
    CardtypeToggleListener(const Cardtypes, CardShuffler&);
    auto getCardtype() const -> Cardtypes;
    auto getListener() -> ListenImpl *const;
};
}   //end namespace Dominion
}   //end namespace SM

#endif  // CARDTYPETOGGLELISTENER_HPP_INCLUDED