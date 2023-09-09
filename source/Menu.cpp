#include "UseHeaders/globals.h"
#include "UseHeaders/Menu.h"
#include "UseHeaders/VectorFunctions.h"
#include <cmath>
#include <list>
#include <iostream>
#include <typeinfo>

void MainMenu::Start(){
    this->plx = 0;
    this->ply = 1;
    this->plz = 2;
    this->RotX = 30;
}
void MainMenu::ColCheck(){
    if(Controls.TpY > 0)
        LoadLevel("World.txt");
}
void MainMenu::Update(){
    if(!this->started)
        this->Start();

    this->FakeIslandRot += 12 * 0.013;
    if(this->FakeIslandRot >= 360)
        this->FakeIslandRot -= 360;

    if(Controls.A)
        this->ColCheck();

    SetCamera(this->plx, this->ply, this->plz, this->RotX, this->RotY);
}
void MainMenu::Draw(){
    
    glTranslatef(((this->FakeIslandPos.x) * worldScale), ((this->FakeIslandPos.y) * worldScale), ((this->FakeIslandPos.z) * worldScale));

    glRotatef(this->FakeIslandRot, 0, 1, 0);
    //glRotatef(360.0f - this->RotY, 0, 1, 0);

    glBegin(GL_QUAD);
        glColor3f(0.5f,0.1f,0.1f);
        float Scale = 1;
		glVertex3f(((-1 * Scale) + this->FakeIslandPos.x) * worldScale,(this->FakeIslandPos.y) * worldScale,(0 + this->FakeIslandPos.z) * worldScale);
		glVertex3f(((-0.5f * Scale) + this->FakeIslandPos.x) * worldScale,(this->FakeIslandPos.y) * worldScale,((0.75f * Scale) + this->FakeIslandPos.z) * worldScale);
		glVertex3f(((0.5f * Scale) + this->FakeIslandPos.x) * worldScale,(this->FakeIslandPos.y) * worldScale,((0.75f * Scale) + this->FakeIslandPos.z) * worldScale);
		glVertex3f(((1 * Scale) + this->FakeIslandPos.x) * worldScale,(this->FakeIslandPos.y) * worldScale,(0 + this->FakeIslandPos.z) * worldScale);

		glVertex3f (((-1 * Scale) + this->FakeIslandPos.x) * worldScale,(this->FakeIslandPos.y) * worldScale,(0 + this->FakeIslandPos.z) * worldScale);
		glVertex3f (((-0.5f * Scale) + this->FakeIslandPos.x) * worldScale,(this->FakeIslandPos.y) * worldScale,((-0.75f*Scale) + this->FakeIslandPos.z) * worldScale);
        glVertex3f (((0.5f * Scale) + this->FakeIslandPos.x) * worldScale,(this->FakeIslandPos.y) * worldScale,((-0.75f*Scale) + this->FakeIslandPos.z) * worldScale);
		glVertex3f (((1 * Scale) + this->FakeIslandPos.x) * worldScale,(this->FakeIslandPos.y) * worldScale,(0 + this->FakeIslandPos.z) * worldScale);


        glVertex3f((-0.02 )* worldScale,(0.02)* worldScale,0);
        glVertex3f((0.02 )* worldScale,(0.02)* worldScale,0);
        glVertex3f((0.02 )* worldScale,(-0.02)* worldScale,0);
        glVertex3f((-0.02 )* worldScale,(-0.02)* worldScale,0);
    //glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE | POLY_FORMAT_LIGHT0);
    glEnd();

    glRotatef(-this->FakeIslandRot, 0, 1, 0);

    glTranslatef(-((this->FakeIslandPos.x) * worldScale), -((this->FakeIslandPos.y) * worldScale), -((this->FakeIslandPos.z) * worldScale));
}
void MainMenu::Draw2DTop(){

}void MainMenu::Draw2DBottom(){
    
}
void MainMenu::Damage(float Px, float Py, float Pz){
    if(this->TimeBtwHit <= 0){
        this->health -= 1;
        float ForceXZ = 0.15, ForceY = 0.35;
        
        Vector2 newTargetLoc = {Px - (this->plx), Pz - (this->plz) };
        float BaseAngle = (atan2(newTargetLoc.x , -newTargetLoc.y) * 180 / M_PI);
        float DifX = -(sin(M_PI / 180.0 * (BaseAngle))) * ForceXZ;
         float DifZ = (cos(M_PI / 180.0 * (BaseAngle))) * ForceXZ;
        //float DifY = -(sin(M_PI / 180.0 * (BaseAngle))) * 0.5;
        //Better than angle cal for more height - 0.5 is radius
        float UpForce = ((0.5 - distance3(this->plx, this->ply, this->plz, Px, Py, Pz)) * ForceY);
        if(this->ply < Py)
            UpForce *= -1;
        this->pvy = UpForce;
        this->pvx = DifX;
        this->pvz = DifZ;
        this->isGrounded = false;
        this->TimeBtwHit = this->TimeForHit;
    }
}
void MainMenu::Animation(){

}
void MainMenu::Attack(){

}
void MainMenu::Death(){
    RemoveObjects.push_back(this);
}