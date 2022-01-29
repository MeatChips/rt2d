/**
 * This class describes MyEntity behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include "bullet.h"

Bullet::Bullet() : extraentity()
{
	this->scale.x = .25;
	this->scale.y = .25;
	this->addSprite("assets/BombBoat2.tga");
}

Bullet::~Bullet()
{

}

void Bullet::update(float deltaTime)
{
	//###############################################################
	//Rotate of the bullet
	//###############################################################
	this->rotation.z += PI * deltaTime; // 90 deg/sec
		if (this->rotation.z > TWO_PI) {
		this->rotation.z -= TWO_PI;
	}


	position += velocity;
}
