//
//  DelayLine.hpp
//  LearnSomeBasicSoundStuff
//
//  Created by Moses Lee on 1/27/16.
//  Copyright © 2016 Moses Lee. All rights reserved.
//

#ifndef DelayLine_hpp
#define DelayLine_hpp

#include <stdio.h>
#include <memory>

#include "AudioSpec.h"
#include "Utilities.hpp"

#define MAX_DELAY 4000 //Maximum amount of delay in milliseconds = 176400 Samples if SR is 44100
#define MILLISECONDS 1000 //1000 Milliseconds in a second
class DelayLine {
public:
    DelayLine();
    DelayLine(unsigned int maxDelay);
    ~DelayLine();
    void setDelay(float newDelay);
    void fillOutputBuffer(float * buffer, const unsigned int numSamples, int blockPos);
    void fillInputBuffer(float * buffer, const unsigned int numSamples, int blockPos);
    
private:
    std::unique_ptr<float[]> buffer;
    int readIndex;
    int writeIndex;
    int maxDelay;
    float currentDelay;
};

#endif /* DelayLine_hpp */
