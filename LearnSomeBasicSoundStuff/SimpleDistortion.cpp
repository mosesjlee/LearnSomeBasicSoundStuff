//
//  SimpleDistortion.cpp
//  LearnSomeBasicSoundStuff
//
//  Created by Moses Lee on 2/1/16.
//  Copyright © 2016 Moses Lee. All rights reserved.
//

#include "SimpleDistortion.hpp"

SimpleDistortion::SimpleDistortion(){
    inBuffer = new float[MAX_SAMPLES];
    drive = 10.0;
}

SimpleDistortion::~SimpleDistortion(){
    delete [] inBuffer;
}

//f(x) = x/|x| (1-e^(x^2/|x|))
void SimpleDistortion::processNextSamples(){
    float x = 0.0;
    for (int i = 0; i < MAX_SAMPLES; i++) {
        x = inBuffer[i];
        //inBuffer[i] = x/fabs(x) * (1 - pow(exp(1.0), pow(x,2)/fabs(x)));
        if(x >= 0)
            inBuffer[i] =  .6 * (1/atan(drive) * atan(drive * x));
        else
            inBuffer[i] = .6 * (1/atan(-drive) * atan(-drive * x));
            
    }
    
}

void SimpleDistortion::setNewDrive(float drive){
    this->drive = drive;
}

void SimpleDistortion::fillOutputBuffer(float * buf, int numFrames, int numChannels){
    for (int i = 0; i < numFrames; i++) {
        for (int j = 0; j < numChannels; j++) {
            buf[i * numChannels + j] = inBuffer[i];
        }
    }
    
}

float * SimpleDistortion::getInputBuffer(){
    return inBuffer;
}