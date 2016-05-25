#ifndef TOGGLEANDMINMAX_HPP_INCLUDED
#define TOGGLEANDMINMAX_HPP_INCLUDED

/*
  ==============================================================================

    ToggleAndMinMax.hpp
    Created: 8 Oct 2015 3:11:31pm
    Author:  caps

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
template<typename EnumT>
class ToggleAndMinMax : public juce::Component
{
public:
    ToggleAndMinMax(EnumT) {};
    ~ToggleAndMinMax() {};

    auto paint (juce::Graphics&) -> void {};
    auto resized() -> void {};
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ToggleAndMinMax)
};

#include "ToggleAndMinMax.tcc"

#endif  // TOGGLEANDMINMAX_HPP_INCLUDED
