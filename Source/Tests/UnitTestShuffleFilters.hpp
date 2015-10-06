#ifndef FILTERTESTER_HPP_INCLUDED
#define FILTERTESTER_HPP_INCLUDED

/*
  ==============================================================================

    UnitTestShuffleFilters.hpp
    Created: 6 Oct 2015 3:05:39pm
    Author:  caps

  ==============================================================================
*/

#pragma warning(push, 0)
#include "../JuceLibraryCode/JuceHeader.h"
#pragma warning(pop)

#include <memory>

namespace SM
{
//class pre-declaration
namespace Dominion
{
class CardShuffler;
}

class ShuffleFiltersUnitTest : public juce::UnitTest
{
protected:
    std::unique_ptr<Dominion::CardShuffler> shuf;
public:
    explicit ShuffleFiltersUnitTest(const juce::String& name) : juce::UnitTest(name) {};
    auto initialise() -> void override;
};
}   //end namespace SM

#endif  // FILTERTESTER_HPP_INCLUDED