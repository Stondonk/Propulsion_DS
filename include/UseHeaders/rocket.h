#pragma once
#include<nds.h>
#include "gameObject.h"
#include "Vector"
#include <list>
#include<iostream>

class Rocket : public GameObject
{
private:
    //float Gravity = 0.002;
    float Speed = 0.05;
public:
    float LifeTime = 1;
    float RotY = 0;
    float RotX = 0;
    float Gravity = 0;
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

