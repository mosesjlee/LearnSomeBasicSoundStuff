//
//  Utilities.cpp
//  LearnSomeBasicSoundStuff
//
//  Created by Moses Lee on 1/31/16.
//  Copyright © 2016 Moses Lee. All rights reserved.
//

#include "Utilities.hpp"

float lerp(float x_0, float x_1, float y_0, float y_1, float x){
    return ((x - x_0) * (y_1 - y_0))/(x_1 - x_0) + y_0;
}