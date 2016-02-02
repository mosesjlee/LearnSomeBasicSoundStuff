//
//  DelayModule.cpp
//  LearnSomeBasicSoundStuff
//
//  Created by Moses Lee on 1/31/16.
//  Copyright © 2016 Moses Lee. All rights reserved.
//

#include "DelayModule.hpp"

DelayModule::DelayModule(){
    readIndex = writeIndex = 0;
    delayLine.reset(new DelayLine());
    dryBuffer.reset(new float[MAX_SAMPLES]);
    wetBuffer.reset(new float[MAX_SAMPLES]);
    feedbackBuffer.reset(new float[MAX_SAMPLES]);
    
    //Set the gains
    dryGain = 1.0;
    wetGain = feedbackGain = 0.0;
    
    //Zero out all buffers
    for (int i = 0; i < MAX_SAMPLES; i++) {
        dryBuffer[i] = wetBuffer[i] = feedbackBuffer[i] = 0.0;
    }
}

DelayModule::~DelayModule(){
    
}

void DelayModule::setDelayTime(float newDelay){
    delayLine->setDelay(newDelay);
    
}

void DelayModule::setDryGain(float gain){
    dryGain = gain;
    
}

void DelayModule::setWetGain(float gain){
    wetGain = gain;
}

void DelayModule::setFeedbackGain(float gain){
    feedbackGain = gain;
}

float * DelayModule::getInputBuffer(){
    return dryBuffer.get();
}

//This doesn't work. I originally tried to implement this for live sound?
void DelayModule::fillInputBuffer(float * input, int numSamples, int blockPos){
    for (int i = 0; i < numSamples; i++) {
        dryBuffer[writeIndex] = input[i];
        writeIndex = (writeIndex + 1) % MAX_SAMPLES;
    }
}

void DelayModule::processNextSamples(){
    for (int i = 0; i < MAX_SAMPLES; i++) {
        feedbackBuffer[writeIndex] = feedbackGain * wetBuffer[writeIndex] + dryBuffer[writeIndex];
        writeIndex = (writeIndex + 1) % MAX_SAMPLES;
    }
    
    delayLine->fillInputBuffer(feedbackBuffer.get(), MAX_SAMPLES, 0);
}


void DelayModule::tick(float * buffer, int numFrames, int numChannels){
    delayLine->fillOutputBuffer(wetBuffer.get(), MAX_SAMPLES, writeIndex);
    
    for (int i = 0; i < numFrames; i++){
        for (int j = 0; j < numChannels; j++) {
            buffer[i * numChannels + j] = (dryBuffer[readIndex] * dryGain) +
                                          (wetBuffer[readIndex] * wetGain);
        }
        readIndex = (readIndex + 1) % MAX_SAMPLES;//MAX_DELAY * SR/MILLISECONDS;
    }
}