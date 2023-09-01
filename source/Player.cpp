#include "UseHeaders/globals.h"
#include "UseHeaders/Player.h"
#include "UseHeaders/VectorFunctions.h"
#include <cmath>
#include <list>
#include <iostream>
#include <typeinfo>

void Player::Start(){
    this->started = true;
    this->pLength = 0.15;
    this->pHeight = 0.5;
    this->pWidth = 0.15;
    this->TimeForHit = 0.05;
}
void Player::ColCheck(){
    float ClosestFloor = -4, ClosestCeil = 128;
    this->isGrounded = false;
    this->CurrentTile = -1;
    for (HexTile* Tile : Hexs)
    {
        if(Tile->State >= 0){
            //Vector2 Points[6] = {{(1 * Tile->scale) + Tile->x, Tile->z}, {(0.5 * Tile->scale) + Tile->x, (-0.75 * Tile->scale) + Tile->z}, {(-0.5 * Tile->scale) + Tile->x, (-0.75 * Tile->scale) + Tile->z}, {(-1 * Tile->scale) + Tile->x, Tile->z}, {(-0.5 * Tile->scale) + Tile->x, (0.75 * Tile->scale) + Tile->z}, {(0.5 * Tile->scale) + Tile->x, (0.75 * Tile->scale) + Tile->z}};
            Vector2 Points1[4] = {{(1 * Tile->scale) + Tile->x, Tile->z}, {(0.5 * Tile->scale) + Tile->x, (-0.75 * Tile->scale) + Tile->z}, {(-0.5 * Tile->scale) + Tile->x, (-0.75 * Tile->scale) + Tile->z}, {(-1 * Tile->scale) + Tile->x, Tile->z}};
            Vector2 Points2[4] = {{(-1 * Tile->scale) + Tile->x, Tile->z}, {(-0.5 * Tile->scale) + Tile->x, (0.75 * Tile->scale) + Tile->z}, {(0.5 * Tile->scale) + Tile->x, (0.75 * Tile->scale) + Tile->z},{(1 * Tile->scale) + Tile->x, Tile->z}};
            if((polyPoint(Points1, this->plx, this->plz) || polyPoint(Points2, this->plx, this->plz)) && this->ply < Tile->y + (this->pHeight / 2) && this->ply > Tile->y - (this->pHeight / 2)){
                //ClosestFloor = Tile->y;
                if(this->ply > Tile->y){
                    ClosestFloor = Tile->y;
                    this->isGrounded = true;
                }else{
                    ClosestCeil = Tile->y;
                }
                this->CurrentTile = Tile->Type;
                
            }
        }
    }

    this->floorPosition = ClosestFloor;
    this->CeilingPosition = ClosestCeil;
    this->ply = clip(this->ply, this->floorPosition + (this->pHeight / 2) + 0.0001, this->CeilingPosition - (this->pHeight / 2) - 0.0001);
    
}
void Player::Update(){
    if(!this->started)
        this->Start();

        if(this->TimeBtwHit > 0)
            this->TimeBtwHit -= 0.013;

        //Gravity
        if(!this->isGrounded)
            this->pvy -= Gravity;
        else
            this->pvy = 0;

        //Movement
        this->fz = cos(M_PI / 180.0 *(this->RotY));
        this->fx = sin(M_PI / 180.0 *(this->RotY));

        float forRot = sin(M_PI / 180.0 *(this->RotX));

        this->rz = cos(M_PI / 180.0 *(this->RotY + 90));
        this->rx = sin(M_PI / 180.0 *(this->RotY + 90));

	    if (Controls.Left || Controls.Y)
           this->x = -1;
		else if (Controls.Right || Controls.A)
            this->x = 1;
        else
            this->x = 0;
		
		if (Controls.Down || Controls.B)
		    this->y = 1;
		else if (Controls.Up || Controls.X)
            this->y = -1;
        else
            this->y = 0;

        if((Controls.L || Controls.R) && !this->Jumped){
            Rocket* TempRocket = new Rocket();
            TempRocket->plx = this->plx;
            TempRocket->ply = this->ply - 0.1;
            TempRocket->plz = this->plz;

            if(this->ProjectileType == 1)
                TempRocket->Gravity = this->Gravity;

            TempRocket->RotX = this->RotX + 180;
            TempRocket->RotY = this->RotY + 180;
            PushObjects.push_back(TempRocket);
            /*
            //Jumping
            if(this->isGrounded){
                this->pvy = 0.1;
                this->Jumped = true;
                this->isGrounded = false;
            }
            */
           this->Jumped = true;
        }else if(!Controls.L && !Controls.R && this->Jumped){
            this->Jumped = false;
        }
        //if(Controls.Slt)
        //this->Death();
            float TargetSpeed = 0.075;

            float TempZ = this->pvz;
            TempZ -= ((this->fz * this->Speed * -y) + (this->rz * this->Speed * -x)) * 0.013;
            TempZ *= pow(1.0 - (0.65), TargetSpeed);

            float TempX = this->pvx;
            TempX -= ((this->fx * this->Speed * -y) + (this->rx * this->Speed * -x)) * 0.013;
            TempX *= pow(1.0 - (0.65), TargetSpeed);

        this->pvx = TempX;
        this->pvz = TempZ;

        //Camera
            float dx = Controls.TpX - this->LastTx;
			float dy = Controls.TpY - this->LastTy;

			// filtering measurement errors
			if (dx<20 && dx>-20 && dy<20 && dy>-20)
			{
				if(dx>-0.3&&dx<0.3)
					dx=0;

				if(dy>-0.2&&dy<0.2) dy=0;

					this->RotX = clip(lookupdown - dy, -89, 89);

					this->RotY += (dx);
					if(this->RotY < 0)
						this->RotY += 360;
					else if(this->RotY > 359.9)
						this->RotY -= 360;
					//yrot = this->RotY;
			}

		this->LastTx = Controls.TpX;
        this->LastTy = Controls.TpY;

        //Velocity
        if(this->Enabled){
            this->plx += this->pvx;
            this->ply += this->pvy;
            this->plz += this->pvz;
        }

        this->ColCheck();

    SetCamera(this->plx, this->ply, this->plz, this->RotX, this->RotY);
    //this->fx
}
void Player::Draw(){
    
}
void Player::Draw2DTop(){

}void Player::Draw2DBottom(){

}
void Player::Damage(float Px, float Py, float Pz){
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
void Player::Animation(){

}
void Player::Attack(){

}
void Player::Death(){
    RemoveObjects.push_back(this);
}