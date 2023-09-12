#pragma once
#include<nds.h>
#include "gameObject.h"
#include "Vector"
#include <list>
#include<iostream>

class Player : public GameObject
{
private:

    float Gravity = 0.002;

    int x = 0, y = 0;

    float Speed = 0.1;

    float LastTx = 0;
    float LastTy = 0;

    float floorPosition = 0;
    float CeilingPosition = 128;

    bool Jumped = false;

    float DeathTime = 0;

    int CurrentTile = 0;
    int ProjectileType = 0;

    float RocketMoveTweakX = 0;
    float RocketMoveTweakY = 0;

    float DrawBackShot = 0;

    float TimebtwShot = 0;

    float mfx,mfy,mfz,mrx,mry,mrz;
public:
    float RotY = 0;
    float RotX = 0;
    bool isGrounded = false;
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

