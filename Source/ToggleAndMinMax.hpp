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
    ToggleAndMinMax(EnumT value)
        : juce::Component(to_string(value).data())
        , display_text(to_string(value).data())
        , toggle{}
        , min_text("0")
        , min_less_arrow{"", 0.25, juce::Colour{75, 75, 75}}
        , min_more_arrow{"", 0.75, juce::Colour{75, 75, 75}}
        , max_text("10")
        , max_less_arrow{"", 0.25, juce::Colour{75, 75, 75}}
        , max_more_arrow{"", 0.75, juce::Colour{75, 75, 75}}
        , all_buttons{{&display_text, &toggle, &min_text, &min_less_arrow, &min_more_arrow, &max_text, &max_less_arrow, &max_more_arrow}}
        , all_text_buttons{{&display_text, &min_text, &max_text}}
        , all_arrow_buttons{{&min_less_arrow, &min_more_arrow, &max_less_arrow, &max_more_arrow}}
    {
        constexpr auto margin = int(5);
        auto last_right_x = 5;
        for (auto* button : all_buttons)
        {
            addAndMakeVisible(button);
            button->centreWithSize(getWidth(), getHeight());
            button->setTopLeftPosition(last_right_x + margin, margin);
            last_right_x = button->getX() + button->getWidth();
        }
    };
    ~ToggleAndMinMax() {};

    auto paint(juce::Graphics&) -> void {};
    auto resized() -> void
    {
        constexpr auto margin = int(5);
        auto last_right_x = 5;
        for (auto* button : all_buttons)
        {
            addAndMakeVisible(button);
            button->centreWithSize(getWidth(), getHeight());
            button->setTopLeftPosition(last_right_x + margin, margin);
            last_right_x = button->getX() + button->getWidth();
        }
    };
private:
    juce::TextButton display_text;
    juce::ToggleButton toggle;
    juce::TextButton min_text;
    juce::ArrowButton min_less_arrow;
    juce::ArrowButton min_more_arrow;
    juce::TextButton max_text;
    juce::ArrowButton max_less_arrow;
    juce::ArrowButton max_more_arrow;

    std::vector<juce::Button*> all_buttons;
    std::vector<juce::TextButton*> all_text_buttons;
    std::vector<juce::ArrowButton*> all_arrow_buttons;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ToggleAndMinMax)
};

#endif  // TOGGLEANDMINMAX_HPP_INCLUDED
