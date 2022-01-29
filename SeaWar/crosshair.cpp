/**
 * This class describes MyEntity behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include "crosshair.h"

Crosshair::Crosshair() : extraentity()
{
	this->scale.x = 1;
	this->scale.y = 1;
	this->addSprite("assets/CrosshairRed2.tga");
}

Crosshair::~Crosshair()
{

}

void Crosshair::update(float deltaTime)
{
	// ###############################################################
	// Rotate
	// ###############################################################
	//this->rotation.z += HALF_PI * deltaTime; // 90 deg/sec
	//if (this->rotation.z > TWO_PI) {
	//	this->rotation.z -= TWO_PI;
	//}
}
