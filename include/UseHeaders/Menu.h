#pragma once
#include<nds.h>
#include "gameObject.h"
#include "VectorFunctions.h"
#include "Vector"
#include "globals.h"
#include <list>
#include<iostream>

struct MenuButton
{
    float x;
    float y;
    int image = 0;
};


class MainMenu : public GameObject
{
private:
    int x = 0, y = 0;

    float LastTx = 0;
    float LastTy = 0;

    float floorPosition = 0;
    float CeilingPosition = 128;

    int CurrentTile = 0;
    int ProjectileType = 0;

    float FakeIslandRot = 0;
    Vector3 FakeIslandPos = {0,0,0};

    int Screen = 0;

    bool Tapped = false;

    //LOGO stuff
    float DsSlideDA = 720, DsSlideDDist = 128, DsSlideSA = 720, DsSlideSDist = 128;
    float LogoSlide = -80;

    //BG
    float BgColor1[3] = {0,0,0};
public:
    float RotY = 0;
    float RotX = 0;
    bool isGrounded = false;
    MenuButton Buttons[1] = {{2,2,2}};
        virtual void Start();
        virtual void Update();
        virtual void Damage(float Px, float Py, float Pz);
        virtual void Draw();
        virtual void Draw2DTop();
        virtual void Draw2DBottom();
        virtual void Animation();
        virtual void ColCheck();
        virtual void Attack();
        virtual void Death();
};

