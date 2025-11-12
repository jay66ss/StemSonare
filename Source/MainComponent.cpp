#include "MainComponent.h"

namespace {
    void setupSlider(juce::Slider& s)
    {
        s.setSliderStyle(juce::Slider::LinearBarVertical);
        s.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 18);
        s.setRange(0.0, 1.0, 0.001);
        s.setValue(0.5);
    }

    void setupLabel(juce::Label& l, const juce::String& name)
    {
        l.setText(name, juce::dontSendNotification);
        l.setJustificationType(juce::Justification::centred);
        l.setColour(juce::Label::textColourId, juce::Colours::white);
    }
}

MainComponent::MainComponent()
{   
    const bool okSend = oscSender.connect("127.0.0.1",7000);
    jassert(okSend);

    if (!connect(7001)) jassertfalse;
    addListener(this, "/feedback");
    // Sliders
    for (auto* s : { &voiceSlider, &bassSlider, &drumsSlider, &synthSlider })
    {
        setupSlider(*s);
        addAndMakeVisible(*s);
        s->addListener(this);
    }

    // Labels
    setupLabel(voiceLabel, "Voice");   addAndMakeVisible(voiceLabel);
    setupLabel(bassLabel,  "Bass");    addAndMakeVisible(bassLabel);
    setupLabel(drumsLabel, "Drums");   addAndMakeVisible(drumsLabel);
    setupLabel(synthLabel, "Synth");   addAndMakeVisible(synthLabel);

    setSize(720, 400);
}

void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white.withAlpha(0.1f));
    g.drawRect(getLocalBounds().reduced(10));
    auto meter = getLocalBounds().removeFromBottom(20).reduced(20, 0);
    g.setColour(juce::Colours::grey.withAlpha(0.4f)); g.fillRect(meter);
    g.setColour(juce::Colours::white);
    auto w = int(meter.getWidth() * juce::jlimit(0.0f, 1.0f, feedbackValue));
    g.fillRect(meter.removeFromLeft(w));

}

void MainComponent::resized()
{
    auto area = getLocalBounds().reduced(20);
    auto col  = area.withWidth(area.getWidth() / 4);

    auto place = [](juce::Slider& s, juce::Label& l, juce::Rectangle<int> r)
    {
        auto labelH = 20;
        l.setBounds(r.removeFromTop(labelH));
        s.setBounds(r.reduced(8));
    };

    auto r = area;
    place(voiceSlider, voiceLabel, r.removeFromLeft(col.getWidth()));
    place(bassSlider,  bassLabel,  r.removeFromLeft(col.getWidth()));
    place(drumsSlider, drumsLabel, r.removeFromLeft(col.getWidth()));
    place(synthSlider, synthLabel, r);
}

void MainComponent::sliderValueChanged(juce::Slider* s)
{
    if (s == &voiceSlider)
    {
        juce::Logger::writeToLog("Voice: " + juce::String((float)s->getValue(), 3));
        oscSender.send("/slider/voice", (float)s->getValue());
    }
    else if (s == &bassSlider)
    {
        juce::Logger::writeToLog("Bass: " + juce::String((float)s->getValue(), 3));
        oscSender.send("/slider/bass", (float)s->getValue());
    }
    else if (s == &drumsSlider)
    {
        juce::Logger::writeToLog("Drums: " + juce::String((float)s->getValue(), 3));
        oscSender.send("/slider/drums", (float)s->getValue());
    }
    else if (s == &synthSlider)
    {
        juce::Logger::writeToLog("Synth: " + juce::String((float)s->getValue(), 3));
        oscSender.send("/slider/synth", (float)s->getValue());
    }
    
}
void MainComponent::oscMessageReceived (const juce::OSCMessage& msg)
{
    if (msg.getAddressPattern().toString() == "/feedback"
        && msg.size() > 0 && msg[0].isFloat32())
    {
        feedbackValue = msg[0].getFloat32(); // 0..1
        repaint();
    }
}


