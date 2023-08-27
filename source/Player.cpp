#include "UseHeaders/globals.h"
#include "UseHeaders/Player.h"
#include <cmath>
#include <list>
#include <iostream>
#include <typeinfo>

void Player::Start(){
    this->started = true;

}
void Player::ColCheck(){

    
}
void Player::Update(){
    if(!this->started)
        this->Start();

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