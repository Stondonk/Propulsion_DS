#include "UseHeaders/globals.h"
#include "UseHeaders/Player.h"
#include <cmath>
#include <list>
#include <iostream>
#include <typeinfo>

void Player::Start(){
    this->started = true;
    this->pHeight = 0.5;
}
void Player::ColCheck(){

    
}
void Player::Update(){
    if(!this->started)
        this->Start();

        //Movement
        this->fz = cos(M_PI / 180.0 *(this->RotY));
        this->fx = sin(M_PI / 180.0 *(this->RotY));

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

        this->pvx = (this->fx * Speed * y) + (this->rx * Speed * x);
        this->pvz = (this->fz * Speed * y) + (this->rz * Speed * x);

        //Camera
            float dx = Controls.TpX - this->LastTx;
			float dy = Controls.TpY - this->LastTy;

			// filtering measurement errors
			if (dx<20 && dx>-20 && dy<20 && dy>-20)
			{
				if(dx>-3&&dx<3)
					dx=0;

				if(dy>-2&&dy<2) dy=0;

					this->RotX = clip(lookupdown - dy, -90, 90);

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
        this->plx += this->pvx;
        this->ply += this->pvy;
        this->plz += this->pvz;

    SetCamera(this->plx, this->ply, this->plz, this->RotX, this->RotY);
    //this->fx
}
void Player::Draw(){
    
}
void Player::Draw2D(){

}
void Player::Damage(float Px, float Py){

}
void Player::Animation(){

}
void Player::Attack(){

}
void Player::Death(){

}