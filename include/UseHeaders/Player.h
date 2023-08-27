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

