#include "UseHeaders/globals.h"
#include "UseHeaders/Menu.h"
#include "UseHeaders/VectorFunctions.h"
#include <cmath>
#include <list>
#include <iostream>
#include <typeinfo>

void MainMenu::DrawDotLine(float x1, float y1, float x2, float y2){
    int lineDis = distance(x1,y1,x2,y2);
    lineDis /= linePointDis;
    int i = 0;
    for (i = 0; i < lineDis; i++)
    {
        Vector2 CPoint = Normilize2D(x2-x1,y2-y1);
        CPoint.x *= (i * linePointDis); CPoint.y *= (i * linePointDis);
        DrawSprite16(0, (int)(CPoint.x + x1) - (int)(this->MapOffsetX), (int)(CPoint.y + y1) - 6 - (int)(this->MapOffsetY),false,false);
    }
    
}
void MainMenu::Start(){
    this->plx = 0;
    this->ply = 1;
    this->plz = 2;
    this->RotX = 30;
}
void MainMenu::ColCheck(){
    if(Controls.TpY > 0 && this->Screen == 0){
        this->Screen = 1;
        this->BgColor1[0] = 0.48;
        this->BgColor1[1] = 0.65;
        this->BgColor1[2] = 0.95;
        
        glClearColor((int)(this->BgColor1[0] * 31),(int)(this->BgColor1[1] * 31),(int)(this->BgColor1[2] * 31),31);
        SetSubBgColorf({this->BgColor1[0],this->BgColor1[1],this->BgColor1[2]});
    }
    else if(Controls.TpY > 0 && this->Screen == 1){
        //LoadLevelTransition("World.txt", 0);
        int mp = 0;
        float TapX = (Controls.TpX) + this->TargetMapOffsetX;
        float TapY = (Controls.TpY) + this->TargetMapOffsetY;
        for (mp = 0; mp < (sizeof(this->MapPoints) / 8); mp++)
        {
            if(Magnitude(this->MapPoints[mp].x - TapX + 8, this->MapPoints[mp].y - TapY + 8) < 12){
                this->TargetMapOffsetX = clip(this->MapPoints[mp].x - 128, -256, 0);
                this->TargetMapOffsetY = clip(this->MapPoints[mp].y - 96, -192,0);
                if(this->SelectStage == mp)
                    LoadLevelTransition(this->WorldNames[mp], 0);
                else
                    this->SelectStage = mp;
            }
        }
        DrawSprite16(0,TapX, TapY,false,false);
    }
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

    if(Controls.B){
        this->TargetMapOffsetX = -128;
        this->TargetMapOffsetY = -96;
        this->SelectStage = -1;
    }

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
            //Title Screen
            if(this->DsSlideDDist <= 1){
                this->LogoSlide = lerp(this->LogoSlide, 72, 0.1);
                DrawSprite16(13,0+this->LogoSlide,88,false,false);
                DrawSprite16(14,16+this->LogoSlide,88,false,false);
                DrawSprite16(15,32+this->LogoSlide,88,false,false);
                DrawSprite16(16,48+this->LogoSlide,88,false,false);
                DrawSprite16(17,64+this->LogoSlide,88,false,false);

                this->BgColor1[0] = lerp(this->BgColor1[0], 0.48,0.05);
                this->BgColor1[1] = lerp(this->BgColor1[1], 0.65,0.05);
                this->BgColor1[2] = lerp(this->BgColor1[2], 0.95,0.05);
                glClearColor((int)(this->BgColor1[0] * 31),(int)(this->BgColor1[1] * 31),(int)(this->BgColor1[2] * 31),31);
                SetSubBgColorf({this->BgColor1[0],this->BgColor1[1],this->BgColor1[2]});
            }
            //DS logo
            //DrawSprite16(18,80+Xset,((1 - this->DsSlideS) * 88));
            DrawSprite16(18,80+72 + (sin(M_PI / 180.0 *(this->DsSlideDA)) * this->DsSlideDDist),88 - (cos(M_PI / 180.0 *(this->DsSlideDA)) * this->DsSlideDDist),false,false);
            DrawSprite16(19,96+72 + (sin(M_PI / 180.0 *(-this->DsSlideSA)) * this->DsSlideSDist),88 + (cos(M_PI / 180.0 *(this->DsSlideSA)) * this->DsSlideSDist),false,false);
            if(this->DsSlideDA > 0)
                this->DsSlideDA -= 2;
            this->DsSlideDDist= clip(this->DsSlideDDist - 0.5, 0, 255);
            if(this->DsSlideSA > 0)
                this->DsSlideSA -= 2;
            this->DsSlideSDist= clip(this->DsSlideSDist - 0.5, 0, 255);
                
        }break;
        case 1:{
            //Level Select
            this->MapOffsetX = lerp(this->MapOffsetX, this->TargetMapOffsetX, 0.075);
            this->MapOffsetY = lerp(this->MapOffsetY, this->TargetMapOffsetY, 0.075);
            DrawSprite16(3,0 - this->MapOffsetX,0 - this->MapOffsetY,false,false);
            int mp = 0;
            for (mp = 0; mp < (sizeof(this->MapPoints) / 8); mp++)
            {
                if(mp == this->SelectStage)
                {
                    DrawSprite16(23,this->MapPoints[mp].x- this->MapOffsetX - 16,this->MapPoints[mp].y- this->MapOffsetY,false,false);    
                    DrawSprite16(23,this->MapPoints[mp].x- this->MapOffsetX + 16,this->MapPoints[mp].y- this->MapOffsetY,true,false);    
                }
                DrawSprite16(20,this->MapPoints[mp].x- this->MapOffsetX,this->MapPoints[mp].y- this->MapOffsetY,false,false);
                this->DrawDotLine(0,0,this->MapPoints[mp].x,this->MapPoints[mp].y);

            }
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