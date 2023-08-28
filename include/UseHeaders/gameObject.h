#include<iostream>
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject
{
    public:
        GameObject() = default;
        virtual void Draw() =0;
        virtual void Draw2DTop() =0;
        virtual void Draw2DBottom() =0;
        virtual void Update() =0;
        virtual void Start() =0;
        virtual void Damage(float Px, float Py, float Pz) =0;
        
        int TargetValue = 0;
        int health = 1;
        std::string Type = "entity";
        //std::list<std::string> Items;
        bool started = false, OnScreen = false, Enabled = true;
        float TimeBtwHit = 0;
        float TimeForHit = 0.5;
        float Angle = 0;
        float plx = 0, ply = 1, plz = 0, pvx = 0, pvy = 0, pvz = 0, pWidth = 16, pHeight = 16, pLength = 16, fx = 1, fy = 0, fz = 0, rx, ry, rz;
        ~GameObject(void) = default;
};

#endif

