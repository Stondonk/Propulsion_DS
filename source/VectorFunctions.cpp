#include "UseHeaders/globals.h"
#include "UseHeaders/VectorFunctions.h"
#include<cmath>
#include <fstream>
#include<iostream>
#include<algorithm>
#include <stdexcept>
#include<utility>
#include <tuple>
#include <vector>

bool lineLine(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {

  // calculate the direction of the lines
  float uA = ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
  float uB = ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));

  // if uA and uB are between 0-1, lines are colliding
  if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) {

    // optionally, draw a circle where the lines meet
    float intersectionX = x1 + (uA * (x2-x1));
    float intersectionY = y1 + (uA * (y2-y1));
    //SDL_SetRenderDrawColor(renderer, 255,255,0,255);
    //DrawReLine(intersectionX,-intersectionY,intersectionX,-intersectionY + 32, 255,255,0);

    //Ellipise(intersectionX, intersectionY, 20, 20);

    return true;
  }
  return false;
}
Vector2 VeclineLine(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {

  // calculate the direction of the lines
  float uA = ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
  float uB = ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));

  // if uA and uB are between 0-1, lines are colliding
  if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) {

    // optionally, draw a circle where the lines meet
    float intersectionX = x1 + (uA * (x2-x1));
    float intersectionY = y1 + (uA * (y2-y1));
    //SDL_SetRenderDrawColor(renderer, 255,255,0,255);
    //DrawReLine(intersectionX,-intersectionY,intersectionX,-intersectionY + 32, 255,255,0);

    //Ellipise(intersectionX, intersectionY, 20, 20);

    return {intersectionX, intersectionY};
  }
  return {x2,y2};
}
Vector2 linePoint(float x1, float y1, float x2, float y2, float px, float py) {

  // get distance from the point to the two ends of the line
  float d1 = distance(px,py, x1,y1);
  float d2 = distance(px,py, x2,y2);

  // get the length of the line
  float lineLen = distance(x1,y1, x2,y2);

  // since floats are so minutely accurate, add
  // a little buffer zone that will give collision
  float buffer = 0.1;    // higher # = less accurate

  // if the two distances are equal to the line's
  // length, the point is on the line!
  // note we use the buffer here to give a range,
  // rather than one #
  if (d1+d2 >= lineLen-buffer && d1+d2 <= lineLen+buffer) {
    return {};
  }
  return {px, py};
}
bool PointBox(float x1, float y1, float x2, float y2, float Px, float Py){
    if(Px > x1 && Py > y1 && Px < x2 && Py < y2){
        return true;
    }
    return false;
}
bool BoxBox(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4){
    if (x2 >= x3 && x1 <= x4 && y2 >= y3 && y1 <= y4) {
        return true;
    }
    //DrawQuad(x1,y1,x2,y1,x1,y2,x2,y2,255,255,255);
    //DrawQuad(x3,y3,x4,y3,x3,y4,x4,y4,255,255,255);
    return false;
}
float distance(float x1, float y1, float x2, float y2)
{
    // distance beween points
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}
float Magnitude(float x, float y){
    return sqrt((x*x) + (y*y));
}
float VectLerpAngle(float A, float B, float T){
    float Cx = (sin(M_PI / 180.0 * (A)));
    float Cy = (-cos(M_PI / 180.0 * (A)));
    float Tx = (sin(M_PI / 180.0 * (B)));
    float Ty = (-cos(M_PI / 180.0 * (B)));
    float x = atan2(lerp(Cx, Tx, T),-lerp(Cy, Ty, T)) * 180.0 / M_PI;
    return x;
}
float repeat(float t, float m) {
    return clip(t - floor(t / m) * m, 0, m);
}
float lerpAngle(float A,float B,float T){
    const float dt = repeat(B - A, 360);
    return lerp(A, A + (dt > 180 ? dt - 360 : dt), T);
}
Vector2 PointOnLine(float x, float y, float Lx1, float Ly1, float Lx2, float Ly2){
  float distX = Lx1 - Lx2;
  float distY = Ly1 - Ly2;
  float len = sqrt( (distX*distX) + (distY*distY) );
  float dot = clip(( ((x-Lx1)*(Lx2-Lx1)) + ((y-Ly1)*(Ly2-Ly1)) ) / pow(len,2), 0, 1); 
  float closestX = Lx1 + (dot * (Lx2-Lx1));
  float closestY = Ly1 + (dot * (Ly2-Ly1));
  return {closestX, closestY};
}
//Polygon Stuff

bool polyPoint(Vector2 vertices[], float px, float py) {
  bool collision = false;

  int next = 0;
  for (int current=0; current< sizeof(vertices); current++) {

    next = current+1;
    if (next == sizeof(vertices)) next = 0;

    Vector2 vc = vertices[current];
    Vector2 vn = vertices[next];
    // compare position, flip 'collision' variable
    // back and forth
    if (((vc.y >= py && vn.y < py) || (vc.y < py && vn.y >= py)) && (px < (vn.x-vc.x)*(py-vc.y) / (vn.y-vc.y)+vc.x)) {
        collision = !collision;
    }
  }
  return collision;
}

bool polyLine(Vector2 vertices[], float x1, float y1, float x2, float y2) {

  int next = 0;
  for (int current=0; current<sizeof(vertices); current++) {
    next = current+1;
    if (next == (int)sizeof(vertices)) next = 0;

    // get the PVectors at our current position
    // extract X/Y coordinates from each
    float x3 = vertices[current].x;
    float y3 = vertices[current].y;
    float x4 = vertices[next].x;
    float y4 = vertices[next].y;

    // do a Line/Line comparison
    // if true, return 'true' immediately and
    // stop testing (faster)
    bool hit = lineLine(x1, y1, x2, y2, x3, y3, x4, y4);
    if (hit) {
      return true;
    }
  }

  // never got a hit
  return false;
}

bool polyPoly(Vector2 p1[], Vector2 p2[]) {
  int next = 0;
  for (int current=0; current< sizeof(p1); current++) {
    next = current+1;
    if (next == (int)sizeof(p1)) next = 0;

    // get the PVectors at our current position
    // this makes our if statement a little cleaner
    Vector2 vc = p1[current];    // c for "current"
    Vector2 vn = p1[next];       // n for "next"

    // now we can use these two points (a line) to compare
    // to the other polygon's vertices using polyLine()
    bool collision = polyLine(p2, vc.x,vc.y,vn.x,vn.y);
    if (collision) return true;

    // optional: check if the 2nd polygon is INSIDE the first
    collision = polyPoint(p1, p2[0].x, p2[0].y);
    if (collision) return true;
  }

  return false;
}