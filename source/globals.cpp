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

Color HexColors[] = {{56,183,100,255}, {65,166,246,255}, {177,62,83,255}, {244,244,244,255}};

float CeilCap = 128;
float FloorCap = -64;

float heading;
float xpos;
float zpos;
float ypos = 0.25;
float yrot;
float lookupdown = 0;

std::vector<HexTile*> Hexs;
std::list<GameObject*> gameObjects;
std::list<GameObject*> PushObjects;
std::list<GameObject*> RemoveObjects;
//Use to allow for more polygons in playable region
float worldScale = 0.25;
controller Controls;
float rotateSpeed = 2;