#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_osc/juce_osc.h>

class MainComponent : public juce::Component,
                      private juce::Slider::Listener,
                      private juce::OSCReceiver,
                      private juce::OSCReceiver::ListenerWithOSCAddress<juce::OSCReceiver::MessageLoopCallback>
{
public:
    MainComponent();
    ~MainComponent() override = default;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider voiceSlider, bassSlider, drumsSlider, synthSlider;
    juce::Label  voiceLabel,  bassLabel,  drumsLabel,  synthLabel;

    // OSC
    juce::OSCSender oscSender;
    void sliderValueChanged (juce::Slider* slider) override;

    // Feedback
    void oscMessageReceived (const juce::OSCMessage& msg) override;
    float feedbackValue = 0.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
