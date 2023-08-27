#pragma once
#include <nds.h>
#include <malloc.h>
#include <stdio.h>

#include <filesystem.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include<iostream>

typedef struct tagVERTEX {
	v16 x, y, z;
	t16 u, v;
} VERTEX;

typedef struct tagTRIANGLE {
	VERTEX vertex[3];
} TRIANGLE;

typedef struct tagSECTOR {
	int numtriangles;
	TRIANGLE* triangle;
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

extern float rotateSpeed;