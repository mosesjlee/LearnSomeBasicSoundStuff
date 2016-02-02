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

void DelayLine::fillInputBuffer(float * inBuffer, const unsigned int numSamples, int blockPos){
    for (int i = 0; i < numSamples; i++){
        buffer[writeIndex] = inBuffer[blockPos];
        writeIndex = (writeIndex + 1) % maxDelay;
        blockPos = (blockPos + 1) % numSamples;
    }
}

void DelayLine::fillOutputBuffer(float * outBuffer, const unsigned int numSamples, int blockPos){
    readIndex = writeIndex - currentDelay;
    if(readIndex < 0) readIndex = maxDelay - currentDelay - 1;
    
#if DEBUG1
    std::cout << "read index " << readIndex << "write index: " << writeIndex << std::endl;
#endif
//    float fracDelayDiff = currentDelay - (int) currentDelay;
//    float fracDelayDiff_2 = 0.0;
//    
//    //Take care of fractional delay
//    if (fracDelayDiff > 0.00) {
//        fracDelayDiff_2 = 1.0-fracDelayDiff;
//    }
    
    for(int i = 0; i < numSamples; i++){
        outBuffer[blockPos] = buffer[readIndex];
        
        readIndex = (readIndex + 1) % maxDelay;
        blockPos = (blockPos + 1) % numSamples;
    }
}



