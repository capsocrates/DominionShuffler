#ifndef STRINGLISTBOXMODEL_HPP_INCLUDED
#define STRINGLISTBOXMODEL_HPP_INCLUDED

/*
  ==============================================================================

    StringListBoxModel.hpp
    Created: 21 Sep 2015 12:08:25pm
    Author:  caps

  ==============================================================================
*/

#pragma warning(push, 0)
#include "D:\dev\source\SuddenMagic\DominionShuffler\JuceLibraryCode\AppConfig.h"
#include "D:\dev\source\SuddenMagic\DominionShuffler\JuceLibraryCode\modules\juce_gui_basics\juce_gui_basics.h" //for juce::ListBoxModel
#pragma warning(pop)

#include <cassert>
#include <iterator>
#include <string>
#include <vector>

namespace SM    //SuddenMagic
{

class StringListBoxModel : public juce::ListBoxModel
{
private:
    std::vector<std::wstring> items;
public:
    typedef std::vector<std::wstring>::iterator iterator;
    typedef std::vector<std::wstring>::const_iterator const_iterator;

    explicit StringListBoxModel(int itemsize);

    ~StringListBoxModel() override;
    int getNumRows() override;
    void paintListBoxItem(int rowNumber,
                          juce::Graphics &g,
                          int width,
                          int height,
                          bool rowIsSelected) override;

    void addRow();
    void addRow(const std::wstring& in);

    friend auto inserter(StringListBoxModel& slbm, const iterator at) -> std::insert_iterator<std::vector<std::wstring>>
    {
        return std::inserter(slbm.items, at);
    }

    auto back_inserter() -> std::back_insert_iterator<std::vector<std::wstring>>
    {
        return std::back_inserter(items);
    }

    friend auto back_inserter(StringListBoxModel& slbm) -> std::back_insert_iterator<std::vector<std::wstring>>
    {
        return std::back_inserter(slbm.items);
    }

    friend auto begin(StringListBoxModel& slbm) -> iterator
    {
        return slbm.items.begin();
    }

    friend auto begin(const StringListBoxModel& slbm) -> const_iterator
    {
        return slbm.items.begin();
    }

    friend auto cbegin(const StringListBoxModel& slbm) -> const_iterator
    {
        return slbm.items.begin();
    }

    friend auto end(StringListBoxModel& slbm) -> iterator
    {
        return slbm.items.end();
    }

    friend auto end(const StringListBoxModel& slbm) -> const_iterator
    {
        return slbm.items.end();
    }

    friend auto cend(const StringListBoxModel& slbm) -> const_iterator
    {
        return slbm.items.end();
    }
};  //end class StringListBoxModel

}   //end namespace SM

#endif  // STRINGLISTBOXMODEL_HPP_INCLUDED
