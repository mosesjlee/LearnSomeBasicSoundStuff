//
//  DelayModule.hpp
//  LearnSomeBasicSoundStuff
//
//  Created by Moses Lee on 1/31/16.
//  Copyright © 2016 Moses Lee. All rights reserved.
//

#ifndef DelayModule_hpp
#define DelayModule_hpp

#include <stdio.h>
#include <memory>

#include "DelayLine.hpp"

class DelayModule {
public:
    DelayModule();
    ~DelayModule();
    void setDelayTime(float);
    void setDryGain(float gain);
    void setWetGain(float gain);
    
private:
    std::unique_ptr<DelayLine> delayLine;
    std::unique_ptr<float[]> dryBuffer;
    std::unique_ptr<float[]> wetBuffer;
    std::unique_ptr<float[]> outBuffer;
    float wetGain;
    float dryGain;

};

#endif /* DelayModule_hpp */
