#pragma once
#include<nds.h>
#include "gameObject.h"
#include "Vector"
#include <list>
#include<iostream>

class Player : public GameObject
{
private:
    float RotY = 0;
    float RotX = 0;

    float Gravity = 10;

    int x = 0, y = 0;

    float Speed = 0.05;

    float LastTx = 0;
    float LastTy = 0;
public:

        virtual void Start();
        virtual void Update();
        virtual void Damage(float Px, float Py);
        virtual void Draw();
        virtual void Draw2D();
        virtual void Animation();
        virtual void ColCheck();
        virtual void Attack();
        virtual void Death();
};
