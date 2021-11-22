/*
  ==============================================================================

    Topic.h
    Created: 16 May 2018 8:52:28pm
    Author:  Matthias Pueski

  ==============================================================================
*/

#pragma once


#include "../JuceLibraryCode/JuceHeader.h"

class Topic {
  
public:
    Topic();
    ~Topic();
    
    void setName(juce::String name);
    juce::String getName();
    
    float getValue();
    void setValue(float value);
    
private:
    juce::String name;
    float value;
    
};
