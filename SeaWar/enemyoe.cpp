/**
 * This class describes MyEntity behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include "enemyoe.h"

EnemyOE::EnemyOE() : extraentity()
{
	this->scale.x = .6;
	this->scale.y = .6;
	this->addSprite("assets/EnemyOneEye.tga");

}

EnemyOE::~EnemyOE()
{

}

void EnemyOE::update(float deltaTime)
{
	// ###############################################################
	// Rotate
	// ###############################################################
	//this->rotation.z += HALF_PI * deltaTime; // 90 deg/sec
	//if (this->rotation.z > TWO_PI) {
	//	this->rotation.z -= TWO_PI;
	//}


}