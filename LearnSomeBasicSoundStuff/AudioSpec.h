//
//  AudioSpec.h
//  NewProject
//
//  Created by Moses Lee on 10/23/15.
//
//

#include <TargetConditionals.h>

#ifndef AudioSpec_h
#define AudioSpec_h
#define SR 44100

#if (TARGET_IPHONE_SIMULATOR)
#define MAX_SAMPLES 512
#elif TARGET_OS_MAC
#define MAX_SAMPLES 512
#else
#define MAX_SAMPLES 1024
#endif

//Maybe i should subclass my stuff.
class AudioElements {
    
};

#endif /* AudioSpec_h */
