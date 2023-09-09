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

void DrawText(std::string Text, int side, int x, int y){
  int i = 0;
  int offsetX = side * ((Text.size() * 16) / 2);
  for (i = 0; i < Text.size(); i++)
  {
    DrawSprite16(((int)Text[i]-46),x + (i * 16) - (((Text.size() * 16) / 2) + offsetX),y);
  }
  
}

void DrawSprite16(int Car, int x, int y){
  oamSet(&oamSub, SpriteAssetIndex, x, y, 0, 0, SpriteSize_16x16, SpriteColorFormat_256Color,Text_sprite_mem[Car], -1, false, false, false, false, false);
  SpriteAssetIndex++;
}

QSECTOR Rsector;

bool GameMasterEnable = false;

int SpriteAssetIndex = 0;

u16* Text_sprite_mem[12];

bool PauseGame = false;
bool CanPause = true;

Color HexColors[] = {{56,183,100,255}, {65,166,246,255}, {177,62,83,255}, {244,244,244,255}};

float CeilCap = 128;
float FloorCap = -64;

float heading;
float xpos;
float zpos;
float ypos = 0.25;
float yrot;
float lookupdown = 0;

std::list<HexTile*> Hexs;
std::list<GameObject*> gameObjects;
std::list<GameObject*> PushObjects;
std::list<GameObject*> RemoveObjects;
//Use to allow for more polygons in playable region
float worldScale = 0.25;
controller Controls;
float rotateSpeed = 2;