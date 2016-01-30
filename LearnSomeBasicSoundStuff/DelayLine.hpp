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
#define MAX_DELAY 2000 //Maximum amount of delay in milliseconds = 88200 Samples if SR is 44100
class DelayLine {
public:
    DelayLine();
    DelayLine(unsigned int maxDelay);
    ~DelayLine();
    void setDelay(float newDelay);
    void tick(float * buffer);
    
private:
    float * buffer;
    int readIndex;
    int writeIndex;
};

#endif /* DelayLine_hpp */
