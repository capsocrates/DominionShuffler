/*
  ==============================================================================

    StringListBoxModel.cpp
    Created: 21 Sep 2015 12:08:25pm
    Author:  caps

  ==============================================================================
*/

#include "StringListBoxModel.hpp"

namespace SM    //Sudden Magic
{
StringListBoxModel::StringListBoxModel(int itemsize)
    : ListBoxModel()
    , items(static_cast<std::vector<std::wstring>::size_type>(itemsize), std::wstring(L""))
{

}

StringListBoxModel::~StringListBoxModel()
{
    //nothing special needed
}

int StringListBoxModel::getNumRows()
{
    return static_cast<int>(items.size());
}

void StringListBoxModel::paintListBoxItem(const int rowNumber,
                                          juce::Graphics &g,
                                          const int width,
                                          const int height,
                                          const bool /*rowIsSelected*/)
{
    if (rowNumber < getNumRows())
    {
        g.setColour(juce::Colours::black);
        juce::Font font(height * 0.7f);
        font.setHorizontalScale(0.9f);
        g.setFont(font);
        g.drawText(juce::String(items[rowNumber].c_str()), 4, 0, width - 6, height, juce::Justification::centredLeft);
    }
}

void StringListBoxModel::addRow()
{
    items.emplace_back(L"");
}

void StringListBoxModel::addRow(const std::wstring& in)
{
    items.emplace_back(in);
}

}   //end namespace SM