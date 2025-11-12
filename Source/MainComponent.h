#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

class MainComponent : public juce::Component,
                      private juce::Slider::Listener
{
public:
    MainComponent();
    ~MainComponent() override = default;

    void paint   (juce::Graphics&) override;
    void resized() override;

private:
    // 4 sliders + labels
    juce::Slider voiceSlider, bassSlider, drumsSlider, synthSlider;
    juce::Label  voiceLabel,  bassLabel,  drumsLabel,  synthLabel;

    void sliderValueChanged (juce::Slider* slider) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
