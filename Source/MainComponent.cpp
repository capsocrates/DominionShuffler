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
    , shuf()
    , cardDisplay(shuf)
    , settingsDisplay(shuf)
{
    #ifdef MOBILE_DEVICE_IS_BEING_COMPILED
        setSize(getParentWidth(), getParentHeight());
    #else
        setSize(250, 350);
    #endif
    addAndMakeVisible(tabs);
    tabs.centreWithSize(getWidth(), getHeight());
    tabs.setTabBarDepth(30);
    tabs.addTab(juce::translate(L"Cards"), juce::Colours::lightgrey, &cardDisplay, false);
    tabs.addTab(juce::translate(L"Settings"), juce::Colours::lightgrey, &settingsDisplay, false);
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