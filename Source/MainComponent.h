#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

class MainComponent : public juce::Component
{
public:
    MainComponent() { setSize (640, 360); }
    ~MainComponent() override = default;

    void paint (juce::Graphics& g) override
    {
        g.fillAll (juce::Colours::black);
        g.setColour (juce::Colours::white);
        g.setFont (30.0f);
        g.drawFittedText ("StemSonare", getLocalBounds(), juce::Justification::centred, 1);
    }

    void resized() override {}

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
