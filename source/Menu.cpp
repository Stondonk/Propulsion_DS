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
    if(Controls.TpY > 0 && this->Screen == 0)
        this->Screen = 1;
    else if(Controls.TpY > 0 && this->Screen == 1)
        LoadLevel("World.txt");
}
void MainMenu::Update(){
    if(!this->started)
        this->Start();

    this->FakeIslandRot += 12 * 0.013;
    if(this->FakeIslandRot >= 360)
        this->FakeIslandRot -= 360;

    if(Controls.Touching && !this->Tapped){
        this->ColCheck();this->Tapped = true;}
    if(!Controls.Touching)
        this->Tapped = false;

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
    switch (this->Screen)
    {
        case 0:{
            if(this->DsSlideDDist <= 1){
                this->LogoSlide = lerp(this->LogoSlide, 72, 0.1);
                DrawSprite16(13,0+this->LogoSlide,88);
                DrawSprite16(14,16+this->LogoSlide,88);
                DrawSprite16(15,32+this->LogoSlide,88);
                DrawSprite16(16,48+this->LogoSlide,88);
                DrawSprite16(17,64+this->LogoSlide,88);
            }
            //DS logo
            //DrawSprite16(18,80+Xset,((1 - this->DsSlideS) * 88));
            DrawSprite16(18,80+72 + (sin(M_PI / 180.0 *(this->DsSlideDA)) * this->DsSlideDDist),88 - (cos(M_PI / 180.0 *(this->DsSlideDA)) * this->DsSlideDDist));
            DrawSprite16(19,96+72 + (sin(M_PI / 180.0 *(-this->DsSlideSA)) * this->DsSlideSDist),88 + (cos(M_PI / 180.0 *(this->DsSlideSA)) * this->DsSlideSDist));
            if(this->DsSlideDA > 0)
                this->DsSlideDA -= 2;
            this->DsSlideDDist= clip(this->DsSlideDDist - 0.5, 0, 255);
            if(this->DsSlideSA > 0)
                this->DsSlideSA -= 2;
            this->DsSlideSDist= clip(this->DsSlideSDist - 0.5, 0, 255);
                
        }break;
        case 1:{
            DrawSprite16(3,2,2);
            DrawSprite16(20,18,2);
        }break;
    }
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