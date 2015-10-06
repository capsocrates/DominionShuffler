#ifndef TEST_RUNNER_HPP_INCLUDED
#define TEST_RUNNER_HPP_INCLUDED

/*
  ==============================================================================

    TestRunner.hpp
    Created: 14 Sep 2015 2:28:25pm
    Author:  Bladerunner

  ==============================================================================
*/

#pragma warning(push, 0)
#include "../JuceLibraryCode/JuceHeader.h"
#pragma warning(pop)

namespace SM
{
class UnitTestRunner : public juce::UnitTestRunner
{
};
}   //end namespace SM

#endif  // TEST_RUNNER_HPP_INCLUDED
