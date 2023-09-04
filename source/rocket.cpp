#include "UseHeaders/globals.h"
#include "UseHeaders/rocket.h"
#include "UseHeaders/VectorFunctions.h"
#include <cmath>
#include <list>
#include <iostream>
#include <typeinfo>

void Rocket::Start(){
    this->started = true;
    this->pLength = 0.05;
    this->pHeight = 0.05;
    this->pWidth = 0.05;

    //Movement
    this->fy = sin(M_PI / 180.0 *(this->RotX));
    this->fz = -cos(M_PI / 180.0 * this->RotX) * cos(M_PI / 180.0 *(this->RotY));
    this->fx = -cos(M_PI / 180.0 * this->RotX) * sin(M_PI / 180.0 *(this->RotY));

    this->pvx = (this->fx * Speed );
    this->pvy = (this->fy * Speed );
    this->pvz = (this->fz * Speed );
}
void Rocket::ColCheck(){
    float ClosestFloor = -4, ClosestCeil = 128;
    this->isGrounded = false;
    for (HexTile* Tile : Hexs)
    {
        if(Tile->State >= 0){
            //Vector2 Points[6] = {{(1 * Tile->scale) + Tile->x, Tile->z}, {(0.5 * Tile->scale) + Tile->x, (-0.75 * Tile->scale) + Tile->z}, {(-0.5 * Tile->scale) + Tile->x, (-0.75 * Tile->scale) + Tile->z}, {(-1 * Tile->scale) + Tile->x, Tile->z}, {(-0.5 * Tile->scale) + Tile->x, (0.75 * Tile->scale) + Tile->z}, {(0.5 * Tile->scale) + Tile->x, (0.75 * Tile->scale) + Tile->z}};
            Vector2 Points1[4] = {{(1 * Tile->scale) + Tile->x, Tile->z}, {(0.5 * Tile->scale) + Tile->x, (-0.75 * Tile->scale) + Tile->z}, {(-0.5 * Tile->scale) + Tile->x, (-0.75 * Tile->scale) + Tile->z}, {(-1 * Tile->scale) + Tile->x, Tile->z}};
            Vector2 Points2[4] = {{(-1 * Tile->scale) + Tile->x, Tile->z}, {(-0.5 * Tile->scale) + Tile->x, (0.75 * Tile->scale) + Tile->z}, {(0.5 * Tile->scale) + Tile->x, (0.75 * Tile->scale) + Tile->z},{(1 * Tile->scale) + Tile->x, Tile->z}};
            if((polyPoint(Points1, this->plx, this->plz) || polyPoint(Points2, this->plx, this->plz)) && this->ply < Tile->y + (this->pHeight / 2) && this->ply > Tile->y - (this->pHeight / 2)){
                //ClosestFloor = Tile->y;
                this->Death();
                
            }
        }
    }
    //this->ply = clip(this->ply, this->floorPosition + (this->pHeight / 2) + 0.0001, this->CeilingPosition - (this->pHeight / 2) - 0.0001);
    
}
void Rocket::Update(){
    if(!this->started)
        this->Start();
        
        this->pvy -= Gravity;

        //Velocity
        if(this->Enabled){
            this->plx += this->pvx;
            this->ply += this->pvy;
            this->plz += this->pvz;
        }
        this->ColCheck();

    if(this->LifeTime > 0)
        this->LifeTime -= 0.013;
    else if(this->LifeTime <= 0)
        this->Death();

    if(this->ply > CeilCap || this->ply < FloorCap)
        this->Death();

        //this->ColCheck();
    //this->fx
}
void Rocket::Draw(){
    int alpha = (int)((this->LifeTime) * 31);
    //glPolyFmt(POLY_ALPHA(alpha) | POLY_CULL_NONE | POLY_ID(2));
    //glRotatef(this->RotX, 1, 0, 0);
    //glRotatef(360.0f - this->RotY, 0, 1, 0);
    //glLoadIdentity();

    glTranslatef(((this->plx) * worldScale), ((this->ply) * worldScale), ((this->plz) * worldScale));

    glRotatef(this->RotY, 0, 1, 0);
    glRotatef(this->RotX, 1, 0, 0);
    //glRotatef(360.0f - this->RotY, 0, 1, 0);

    glBegin(GL_QUAD);
        glColor3f(0.5f,0.1f,0.1f);
        glVertex3f((-0.05 )* worldScale,(0.05)* worldScale,0);
        glVertex3f((0.05 )* worldScale,(0.05)* worldScale,0);
        glVertex3f((0.05 )* worldScale,(-0.05)* worldScale,0);
        glVertex3f((-0.05 )* worldScale,(-0.05)* worldScale,0);
        //glTranslatef(-(this->plx) * worldScale,-(this->ply) * worldScale,-(this->plz) * worldScale);
    //glTranslatef(-this->plx * worldScale, -this->ply * worldScale, -this->plz * worldScale);
    //glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE | POLY_FORMAT_LIGHT0);
    glEnd();

    glRotatef(-this->RotX, 1, 0, 0);
    glRotatef(-this->RotY, 0, 1, 0);

    glTranslatef(-((this->plx) * worldScale), -((this->ply) * worldScale), -((this->plz) * worldScale));
}
void Rocket::Draw2DTop(){

}void Rocket::Draw2DBottom(){

}
void Rocket::Damage(float Px, float Py, float Pz){

}
void Rocket::Animation(){

}
void Rocket::Attack(){

}
void Rocket::Death(){
    for (GameObject* OBJ : gameObjects)
    {
        if(distance3(this->plx, this->ply, this->plz, OBJ->plx, OBJ->ply, OBJ->plz) < 0.5){
            OBJ->Damage(this->plx, this->ply, this->plz);
        }
    }
    
    this->Speed = 0;
    RemoveObjects.push_back(this);
}