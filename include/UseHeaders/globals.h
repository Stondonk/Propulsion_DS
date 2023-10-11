#pragma once
#include <nds.h>
#include <malloc.h>
#include <stdio.h>

#include <filesystem.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include<iostream>
#include <vector>
#include <list>
#include "gameObject.h"
#include "Player.h"
#include "rocket.h"
#include "Atlas.h"
#include "gameMaster.h"
#include "LevelLoader.h"
#include "Menu.h"
#include "Goal.h"

struct controller {
	//Dpad
	bool Up = false,Down = false,Left = false, Right = false;
	//Face buttons
	bool A = false,B = false,X = false,Y = false;
	//bumpers
	bool L = false,R = false;
	//Start and select
	bool Str = false, Slt = false;
	//touch position
	int TpX = 0, TpY = 0;
	//is touching , I know what your thinking dont follow this variable title up with an inapropriate comment you knob
	bool Touching = false;
};

struct HexTile{
	float x, y, z, Vx, Vy, Vz;
	int r, g, b;
	float scale = 1;
	int State = 0;
	int Type = 0;
	int ID = 0;
};
struct WallTile{
	float x1, y1, z1, x2, y2, z2, h;
	int r, g, b;
};
struct Color
{
	int r,g,b,a;
};
struct Colorf
{
	float r,g,b,a;
};

extern u16 BgSubPalette[3];

extern Color HexColors[];

typedef struct tagVERTEX {
	float x, y, z;
	t16 u, v;
} VERTEX;

typedef struct tagTRIANGLE {
	VERTEX vertex[3];
	int r, g, b;
} TRIANGLE;

typedef struct tagSECTOR {
	int numTriangles;
	TRIANGLE* Triangle;
} SECTOR;

typedef struct tagQUAD {
	VERTEX vertex[4];
	Color color;
} QUAD;

typedef struct tagQUADSECTOR {
	int numQuads;
	QUAD* Quad;
} QSECTOR;

extern QSECTOR Rsector;

extern bool GameMasterEnable;

extern int SpriteAssetIndex;

extern std::string CurrentStage;

extern float TransitionTime,TransitionVal;
extern bool OpenTransition;
extern std::string Trasnitionlocation;

extern u16* Text_sprite_mem[];

extern bool PauseGame;
extern bool CanPause;

extern float heading;
extern float xpos;
extern float zpos;
extern float ypos;
extern float yrot;				// Y Rotation
extern float lookupdown;

extern float CeilCap;
extern float FloorCap;

extern bool InvertLook;

extern float clip(float n, float lower, float upper);
extern float lerp (float start, float end, float amt);
extern void SetCamera(float x, float y, float z, float pitch, float yaw);
extern void DrawText(std::string Text, int side, int x, int y);
extern void DrawSprite16(int Car, int x, int y, bool flipX, bool flipY);
extern void SetSubBgColorf(Colorf Color);

extern std::list<HexTile*> Hexs;
extern std::list<GameObject*> gameObjects;
extern std::list<GameObject*> PushObjects;
extern std::list<GameObject*> RemoveObjects;

extern float worldScale;
extern controller Controls;
extern float rotateSpeed;