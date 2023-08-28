#pragma once
#include <fstream>
#include <list>
#include<iostream>
#include<algorithm>
#include <stdexcept>
#include<utility>
#include<nds.h>
#include "globals.h"

using namespace std;

struct Vector2
{
    float x = 0;
    float y = 0;
};

struct Vector3
{
    float x = 0;
    float y = 0;
    float z = 0;
};

bool lineLine(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
Vector2 VeclineLine(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
Vector2 linePoint(float x1, float y1, float x2, float y2, float px, float py);
bool PointBox(float x1, float y1, float x2, float y2, float Px, float Py);
bool BoxBox(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
float distance(float x1, float y1, float x2, float y2);
float Magnitude(float x, float y);
float VectLerpAngle(float A, float B, float T);
Vector2 PointOnLine(float x, float y, float Lx1, float Ly1, float Lx2, float Ly2);
bool polyPoint(Vector2 vertices[], float px, float py);
bool polyLine(Vector2 vertices[], float x1, float y1, float x2, float y2);
bool polyPoly(Vector2 p1[], Vector2 p2[]);

float repeat(float t, float m);
float lerpAngle(float A,float B,float T);

//void AllocateMeshData(Mesh* mesh, int triangleCount);
//Mesh GenQuad(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4);
//Mesh GenTri(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);