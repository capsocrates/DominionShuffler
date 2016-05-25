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
    ToggleAndMinMax(EnumT)
        : toggle(),
          text("0") {};
    ~ToggleAndMinMax() {};

    auto paint (juce::Graphics&) -> void {};
    auto resized() -> void {};
private:
    juce::ToggleButton toggle;
    juce::TextButton min_text;
    juce::ArrowButton min_less_arrow;
    juce::ArrowButton min_more_arrow;
    juce::TextButton max_text;
    juce::ArrowButton max_less_arrow;
    juce::ArrowButton max_more_arrow;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ToggleAndMinMax)
};

#endif  // TOGGLEANDMINMAX_HPP_INCLUDED
