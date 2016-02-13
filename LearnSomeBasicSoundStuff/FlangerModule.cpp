//
//  FlangerModule.cpp
//  LearnSomeBasicSoundStuff
//
//  Created by Moses Lee on 2/13/16.
//  Copyright © 2016 Moses Lee. All rights reserved.
//

#include "FlangerModule.hpp"
FlangerModule::FlangerModule(){
    delayComp.reset(new DelayModule());
    sineComp.reset(new SineWaveOsc());
    inputBuf.reset(new float[MAX_SAMPLES]);
    outputBuf.reset(new float[MAX_SAMPLES]);

    //Initialize
    setMinDelay(0);
    setDelayDepth(0);
}

FlangerModule::~FlangerModule(){
    
}

void FlangerModule::setDryGain(float gain){
    dryGain = gain;
    delayComp->setDryGain(gain);
}

void FlangerModule::setWetGain(float gain){
    wetGain = gain;
    delayComp->setWetGain(gain);
    
}
void FlangerModule::setFeedbackGain(float gain){
    delayComp->setFeedbackGain(gain);
}

void FlangerModule::setDelayRate(float rate){
    delayRate = rate;
    sineComp->setFreq(rate);
    
}

void FlangerModule::setMinDelay(float delay){
    minDelay = delay;
    midPoint = minDelay + delayDepth/2;
}

void FlangerModule::setDelayDepth(float delay){
    delayDepth = delay;
    delayDifferential = delayDepth/2;
}

float * FlangerModule::getInputBuffer(){
    return delayComp->getInputBuffer();
    //return inputBuf.get();
}

void FlangerModule::processNextSamples(){
    for (int i = 0; i < MAX_SAMPLES; i++) {
        delayComp->setDelayTime(sineComp->tick() * delayDifferential + midPoint);
    }
    delayComp->processNextSamples();
    delayComp->tick(outputBuf.get(), MAX_SAMPLES, 1);
}

void FlangerModule::fillOutputBuffer(float * buf, int numFrames, int numChannels){
    for (int i = 0; i < numFrames; i++) {
        for(int j = 0; j < numChannels; j++){
            buf[i * numChannels + j] = outputBuf[i];
        }
    }
    
}


