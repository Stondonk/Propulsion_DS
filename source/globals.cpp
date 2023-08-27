#pragma once
#include<iostream>
#include "UseHeaders/globals.h"

float clip(float n, float lower, float upper) {
  return std::max(lower, std::min(n, upper));
}

float lerp (float start, float end, float amt){
    return (1-amt)*start+amt*end;
}

void SetCamera(float x, float y, float z, float pitch, float yaw){
  xpos = x;
  ypos = y;
  zpos = z;
  lookupdown = pitch;
  yrot = yaw;
}

float heading;
float xpos;
float zpos;
float ypos = 0.25;
float yrot;
float lookupdown = 0;

std::vector<HexTile*> Hexs;
std::vector<GameObject*> gameObjects;
std::vector<GameObject*> RemoveObjects;
float worldScale = 0.25;
controller Controls;
float rotateSpeed = 2;