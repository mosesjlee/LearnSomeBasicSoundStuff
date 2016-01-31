//
//  DelayLine.cpp
//  LearnSomeBasicSoundStuff
//
//  Created by Moses Lee on 1/27/16.
//  Copyright © 2016 Moses Lee. All rights reserved.
//

#include "DelayLine.hpp"

DelayLine::DelayLine(){
    buffer.reset(new float[MAX_DELAY * SR/MILLISECONDS]);
    maxDelay = MAX_DELAY * SR/MILLISECONDS;
    readIndex = 0;
    writeIndex = 0;
    currentDelay = 0.0;
}

DelayLine::DelayLine(unsigned int newMaxDelay){
    if (newMaxDelay > MAX_DELAY){
        buffer.reset(new float[MAX_DELAY * SR/MILLISECONDS]);
        maxDelay = MAX_DELAY * SR/MILLISECONDS;
    } else {
        buffer.reset(new float[newMaxDelay * SR/MILLISECONDS]);
        maxDelay = newMaxDelay * SR/MILLISECONDS;
    }
    readIndex = 0;
    writeIndex = 0;
    currentDelay = 0.0;
}

DelayLine::~DelayLine(){
    
}

//newDelay in milliseconds
void DelayLine::setDelay(float newDelay){
    currentDelay = newDelay * SR/MILLISECONDS;
}


void DelayLine::fillInputBuffer(float * inBuffer, const unsigned int numSamples){
    for (int i = 0; i < numSamples; i++){
        buffer[writeIndex] = inBuffer[i];
        writeIndex = (writeIndex + 1) % maxDelay;
    }
}

void DelayLine::tick(float * buffer, const unsigned int numFrames, const unsigned int numChannels){
    readIndex = readIndex - currentDelay;
    for(int i = 0; i < numFrames; i++){
        for(int j = 0; j < numChannels; j++){
            
        }
    }
}



