#include "UseHeaders/globals.h"
#include "UseHeaders/rocket.h"
#include "UseHeaders/VectorFunctions.h"
#include <cmath>
#include <list>
#include <iostream>
#include <typeinfo>

void Rocket::Start(){
    this->started = true;
    this->pLength = 0.15;
    this->pHeight = 0.15;
    this->pWidth = 0.15;
}
void Rocket::ColCheck(){
    float ClosestFloor = -4, ClosestCeil = 128;
    this->isGrounded = false;
    for (HexTile* Tile : Hexs)
    {
        //Vector2 Points[6] = {{(1 * Tile->scale) + Tile->x, Tile->z}, {(0.5 * Tile->scale) + Tile->x, (-0.75 * Tile->scale) + Tile->z}, {(-0.5 * Tile->scale) + Tile->x, (-0.75 * Tile->scale) + Tile->z}, {(-1 * Tile->scale) + Tile->x, Tile->z}, {(-0.5 * Tile->scale) + Tile->x, (0.75 * Tile->scale) + Tile->z}, {(0.5 * Tile->scale) + Tile->x, (0.75 * Tile->scale) + Tile->z}};
        Vector2 Points1[4] = {{(1 * Tile->scale) + Tile->x, Tile->z}, {(0.5 * Tile->scale) + Tile->x, (-0.75 * Tile->scale) + Tile->z}, {(-0.5 * Tile->scale) + Tile->x, (-0.75 * Tile->scale) + Tile->z}, {(-1 * Tile->scale) + Tile->x, Tile->z}};
        Vector2 Points2[4] = {{(-1 * Tile->scale) + Tile->x, Tile->z}, {(-0.5 * Tile->scale) + Tile->x, (0.75 * Tile->scale) + Tile->z}, {(0.5 * Tile->scale) + Tile->x, (0.75 * Tile->scale) + Tile->z},{(1 * Tile->scale) + Tile->x, Tile->z}};
        if((polyPoint(Points1, this->plx, this->plz) || polyPoint(Points2, this->plx, this->plz)) && this->ply < Tile->y + (this->pHeight / 2) && this->ply > Tile->y - (this->pHeight / 2)){
            //ClosestFloor = Tile->y;
            if(this->ply > Tile->y){
                ClosestFloor = Tile->y;
                this->isGrounded = true;
            }else{
                ClosestCeil = Tile->y;
            }
            
        }
    }
    //this->ply = clip(this->ply, this->floorPosition + (this->pHeight / 2) + 0.0001, this->CeilingPosition - (this->pHeight / 2) - 0.0001);
    
}
void Rocket::Update(){
    if(!this->started)
        this->Start();

        //Movement
        this->fy = sin(M_PI / 180.0 *(this->RotX));
        this->fz = cos(M_PI / 180.0 *(this->RotY));
        this->fx = sin(M_PI / 180.0 *(this->RotY));

        this->pvx = (this->fx * Speed );
        this->pvy = (this->fy * Speed );
        this->pvz = (this->fz * Speed );

        //Velocity
        if(this->Enabled){
            this->plx += this->pvx;
            this->ply += this->pvy;
            this->plz += this->pvz;
        }

        //this->ColCheck();
    //this->fx
}
void Rocket::Draw(){
    glBegin(GL_QUAD);
    glColor3f(0.5f,0.1f,0.1f);	
    glVertex3f(this->plx - 0.2,this->ply + 0.2,this->plz);
    glVertex3f(this->plx + 0.2,this->ply + 0.2,this->plz);
    glVertex3f(this->plx + 0.2,this->ply - 0.2,this->plz);
    glVertex3f(this->plx - 0.2,this->ply - 0.2,this->plz);
    glEnd();
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

}