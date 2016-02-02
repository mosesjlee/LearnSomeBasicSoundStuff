//
//  DelayLine.cpp
//  LearnSomeBasicSoundStuff
//
//  Created by Moses Lee on 1/27/16.
//  Copyright © 2016 Moses Lee. All rights reserved.
//

#include "DelayLine.hpp"
#include <iostream>

DelayLine::DelayLine(){
    buffer.reset(new float[MAX_DELAY * SR/MILLISECONDS]);
    for (int i = 0; i < MAX_DELAY * SR/MILLISECONDS; i++) buffer[i] = 0.0;
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
    for (int i = 0; i < maxDelay; i++) buffer[i] = 0.0;
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

void DelayLine::fillInputBuffer(float * inBuffer, const unsigned int numSamples, int blockPos){
    for (int i = 0; i < numSamples; i++){
        buffer[writeIndex] = inBuffer[i];
        writeIndex = (writeIndex + 1) % maxDelay;
    }
}

void DelayLine::fillOutputBuffer(float * outBuffer, const unsigned int numSamples, int blockPos){
    readIndex = writeIndex - currentDelay;
    if(readIndex < 0) readIndex = maxDelay - currentDelay - 1;
    
//    float fracDelayDiff = currentDelay - (int) currentDelay;
//    float fracDelayDiff_2 = 0.0;
//    
//    //Take care of fractional delay
//    if (fracDelayDiff > 0.00) {
//        fracDelayDiff_2 = 1.0-fracDelayDiff;
//    }
    float val = 0.0;
    for(int i = 0; i < numSamples; i++){
        val = buffer[readIndex] > 1.0 ? 1.0 : buffer[readIndex];
        val = val < -1.0 ? -1.0 : val;
        
        outBuffer[i] = val;
        
        readIndex = (readIndex + 1) % maxDelay;
    }
}



