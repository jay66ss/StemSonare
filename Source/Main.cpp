#include <juce_gui_basics/juce_gui_basics.h>
#include "MainComponent.h"

class StemSonareApplication : public juce::JUCEApplication
{
public:
    const juce::String getApplicationName() override    { return "StemSonare"; }
    const juce::String getApplicationVersion() override { return "0.1.0"; }
    bool moreThanOneInstanceAllowed() override          { return true; }

    void initialise (const juce::String&) override
    {
        mainWindow.reset (new MainWindow (getApplicationName()));
    }

    void shutdown() override
    {
        mainWindow = nullptr;
    }

    class MainWindow : public juce::DocumentWindow
    {
    public:
        explicit MainWindow (juce::String name)
        : DocumentWindow (name, juce::Colours::darkgrey, DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar (true);
            setContentOwned (new MainComponent(), true);
            centreWithSize (640, 360);
            setVisible (true);
        }

        void closeButtonPressed() override
        {
            juce::JUCEApplication::getInstance()->systemRequestedQuit();
        }

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

private:
    std::unique_ptr<MainWindow> mainWindow;
};

START_JUCE_APPLICATION (StemSonareApplication)
