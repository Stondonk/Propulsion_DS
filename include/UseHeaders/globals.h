#pragma once
#include <nds.h>
#include <malloc.h>
#include <stdio.h>

#include <filesystem.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include<iostream>
#include "gameObject.h"

struct controller {
	//Dpad
	bool Up = false,Down = false,Left = false, Right = false;
	//Face buttons
	bool A = false,B = false,X = false,Y = false;
	//bumpers
	bool L = false,R = false;
	//Start and select
	bool Str = false, Slt = false;
	//Direction
	int x = 0, y = 0;
	//touch position
	int TpX = 0, Tpy = 0;
};
typedef struct tagVERTEX {
	float x, y, z;
	t16 u, v;
} VERTEX;

typedef struct tagTRIANGLE {
	VERTEX vertex[3];
} TRIANGLE;

typedef struct tagSECTOR {
	int numTriangles;
	TRIANGLE* Triangle;
} SECTOR;

typedef struct tagQUAD {
	VERTEX vertex[4];
} QUAD;

typedef struct tagQUADSECTOR {
	int numQuads;
	QUAD* Quad;
} QSECTOR;

extern float clip(float n, float lower, float upper);
extern float lerp (float start, float end, float amt);

extern float worldScale;
extern controller Controls;
extern float rotateSpeed;