/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JamToolsAudioProcessorEditor::JamToolsAudioProcessorEditor (JamToolsAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    std::cout << "\neditor constructor\n";
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

JamToolsAudioProcessorEditor::~JamToolsAudioProcessorEditor()
{
    std::cout << "\neditor deconstructor\n";
}

//==============================================================================
void JamToolsAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);

    juce::String s = "Jam App is running. Go to http://localhost:8080";

    g.drawFittedText (s, getLocalBounds(), juce::Justification::centred, 1);
}

void JamToolsAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
