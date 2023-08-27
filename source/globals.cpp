#pragma once
#include<iostream>
#include "UseHeaders/globals.h"

float clip(float n, float lower, float upper) {
  return std::max(lower, std::min(n, upper));
}

float lerp (float start, float end, float amt){
    return (1-amt)*start+amt*end;
}

float worldScale = 0.25;
controller Controls;
float rotateSpeed = 2;