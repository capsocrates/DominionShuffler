/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

#include "CardImport.hpp"

//==============================================================================
MainContentComponent::MainContentComponent()
    : tabs(juce::TabbedButtonBar::TabsAtTop)
{
    #ifdef MOBILE_DEVICE_IS_BEING_COMPILED
        setFullScreen(true);
    #else
        setSize(250, 350);
    #endif
    addAndMakeVisible(&tabs);
    tabs.centreWithSize(getWidth(), getHeight());
    tabs.setTabBarDepth(30);
    tabs.addTab(juce::translate("Cards"), juce::Colours::lightgrey, &cardDisplay, false);
    tabs.addTab(juce::translate("Settings"), juce::Colours::lightgrey, 0, false);
    tabs.setCurrentTabIndex(0);
}

MainContentComponent::~MainContentComponent()
{}

void MainContentComponent::paint(juce::Graphics& /*g*/) const
{}

void MainContentComponent::resized()
{
    tabs.centreWithSize(getWidth(), getHeight());
}