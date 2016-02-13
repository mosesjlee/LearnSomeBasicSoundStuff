//
//  FlangerModule.hpp
//  LearnSomeBasicSoundStuff
//
//  Created by Moses Lee on 2/13/16.
//  Copyright © 2016 Moses Lee. All rights reserved.
//

#ifndef FlangerModule_hpp
#define FlangerModule_hpp

#include <stdio.h>
#include "AudioSpec.h"
#include "DelayModule.hpp"
#include "SineWaveOsc.h"

class FlangerModule : public MyAudioModule{
public:
    FlangerModule();
    ~FlangerModule();
    void setDryGain(float);
    void setWetGain(float);
    void setFeedbackGain(float);
    void setDelayRate(float);
    void setMinDelay(float);
    void setDelayDepth(float);
    float * getInputBuffer();
    void processNextSamples();
    void fillOutputBuffer(float *, int, int);
    
private:
    std::unique_ptr<DelayModule> delayComp;
    std::unique_ptr<SineWaveOsc> sineComp;
    std::unique_ptr<float[]> inputBuf;
    std::unique_ptr<float[]> outputBuf;
    float dryGain;
    float wetGain;
    float feedbackGain;
    float delayDepth;
    float minDelay;
    float delayRate;
    float midPoint;
    float delayDifferential;
    
};

#endif /* FlangerModule_hpp */
