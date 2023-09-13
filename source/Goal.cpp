#include "UseHeaders/globals.h"
#include "UseHeaders/Goal.h"
#include "UseHeaders/VectorFunctions.h"
#include <cmath>
#include <list>
#include <iostream>
#include <typeinfo>

void GoalOBJ::Start(){
    this->started = true;
    //this->pLength = 0.05;
    this->pHeight = 0.05;
    this->pWidth = 1;
}
void GoalOBJ::ColCheck(){
    for (GameObject* OBJ : gameObjects)
    {
        if(OBJ->Type == "Player" && !this->Collected){
            float sx = sin(M_PI / 180 * (this->RotY)) * (this->pWidth/2),sz = cos(M_PI / 180 * (this->RotY)) * (this->pWidth/2);
            float ex = sin(M_PI / 180 * (this->RotY)) * -(this->pWidth/2),ez = cos(M_PI / 180 * (this->RotY)) * -(this->pWidth/2);
            Vector2 linePoint = PointOnLine(OBJ->plx, OBJ->plz,sx + this->plx,sz + this->plz,ex + this->plx,ez + this->plz);
            if(Magnitude(OBJ->plx - linePoint.x,OBJ->plz - linePoint.y) < (OBJ->pWidth/2)  && OBJ->ply > this->ply - (OBJ->pHeight/2) && OBJ->ply < this->ply + (OBJ->pHeight/2))
                {LoadLevelTransition(this->FileLocation, 0.5);this->Collected = true;}
        }
    }
    //this->ply = clip(this->ply, this->floorPosition + (this->pHeight / 2) + 0.0001, this->CeilingPosition - (this->pHeight / 2) - 0.0001);
    
}
void GoalOBJ::Update(){
    if(!this->started)
        this->Start();
    
    this->ColCheck();

        //this->ColCheck();
    //this->fx
}
void GoalOBJ::Draw(){
    //glPolyFmt(POLY_ALPHA(alpha) | POLY_CULL_NONE | POLY_ID(2));
    //glRotatef(this->RotX, 1, 0, 0);
    //glRotatef(360.0f - this->RotY, 0, 1, 0);
    //glLoadIdentity();

    glTranslatef(((this->plx) * worldScale), ((this->ply) * worldScale), ((this->plz) * worldScale));

    glRotatef(this->RotY, 0, 1, 0);
    //glRotatef(360.0f - this->RotY, 0, 1, 0);

    this->WaveRot += 2;
    if(this->WaveRot >= 360)
        this->WaveRot -= 360;

    glBegin(GL_QUAD);
        int i = 0;
        float FlagPieceSize = this->pWidth / 8;
        float LastPoint = 0;
        for (i = 0; i < 8; i++)
        {
            float OldFlagOff = sin(M_PI / 180.0 * (this->WaveRot + (20 * i)));
            float CurrentFlagOff = sin(M_PI / 180.0 * (this->WaveRot + (20 * (i + 1))));
            glColor3f(0.95f, 0.95f, 0.95f);
            if(i%2 == 0)
                glColor3f(0.1f, 0.1f, 0.1f);
            glVertex3f((0 - (this->pWidth / 2) + LastPoint)* worldScale,(-0.15 + (OldFlagOff * 0.1))* worldScale,0);
            glVertex3f((FlagPieceSize - (this->pWidth / 2) + LastPoint)* worldScale,(-0.15 + (CurrentFlagOff * 0.1))* worldScale,0);
            glVertex3f((FlagPieceSize - (this->pWidth / 2) + LastPoint)* worldScale,(0.15 + (CurrentFlagOff * 0.1))* worldScale,0);
            glVertex3f((0 - (this->pWidth / 2) + LastPoint)* worldScale,(0.15 + (OldFlagOff * 0.1))* worldScale,0);

            LastPoint = (i+1) * FlagPieceSize;
        }
        /*
        glColor3f(0.5f,0.1f,0.1f);
        glVertex3f((-0.02 )* worldScale,(0.02)* worldScale,0);
        glVertex3f((0.02 )* worldScale,(0.02)* worldScale,0);
        glVertex3f((0.02 )* worldScale,(-0.02)* worldScale,0);
        glVertex3f((-0.02 )* worldScale,(-0.02)* worldScale,0);
        */
    //glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE | POLY_FORMAT_LIGHT0);
    glEnd();

    glRotatef(-this->RotY, 0, 1, 0);

    glTranslatef(-((this->plx) * worldScale), -((this->ply) * worldScale), -((this->plz) * worldScale));
}
void GoalOBJ::Draw2DTop(){

}void GoalOBJ::Draw2DBottom(){

}
void GoalOBJ::Damage(float Px, float Py, float Pz){

}
void GoalOBJ::Animation(){

}
void GoalOBJ::Attack(){

}
void GoalOBJ::Death(){
    for (GameObject* OBJ : gameObjects)
    {
        if(distance3(this->plx, this->ply, this->plz, OBJ->plx, OBJ->ply, OBJ->plz) < 0.5){
            OBJ->Damage(this->plx, this->ply, this->plz);
        }
    }
    RemoveObjects.push_back(this);
}