//
//  SimpleDistortion.hpp
//  LearnSomeBasicSoundStuff
//
//  Created by Moses Lee on 2/1/16.
//  Copyright © 2016 Moses Lee. All rights reserved.
//

#ifndef SimpleDistortion_hpp
#define SimpleDistortion_hpp

#include <stdio.h>
#include <tgmath.h>
#include "AudioSpec.h"

class SimpleDistortion {
public:
    SimpleDistortion();
    ~SimpleDistortion();
    
    //f(x) = x/|x| (1-e^(x^2/|x|))
    void processNextSamples();
    void fillOutputBuffer(float * buf, int numFrames, int numChannels);
    float * getInputBuffer();
    void setNewDrive(float drive);
private:
    float * inBuffer;
    float * outBuffer;
    float drive;
    int writeIndex;
    int readIndex;
    
};
#endif /* SimpleDistortion_hpp */
