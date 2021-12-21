/**
 * This class describes MyScene behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include <fstream>
#include <sstream>

#include "myscene.h"
#include "background.h"

MyScene::MyScene() : Scene()
{

	// create a single instance of MyEntity in the middle of the screen.
	// the Sprite is added in Constructor of MyEntity.
	myentity = new MyEntity();
	background = new Background();
	enemyoe = new EnemyOE();
	myentity->position = Point2(SWIDTH/2, SHEIGHT/2);
	background->position = Point2(SWIDTH/2, SHEIGHT/2);
	enemyoe->position = Point2(SWIDTH/1.2, SHEIGHT/1.2);

	// create the scene 'tree'
	// add myentity to this Scene as a child.
	this->addChild(background);
	this->addChild(myentity);
	this->addChild(enemyoe);
}


MyScene::~MyScene()
{
	// deconstruct and delete the Tree
	this->removeChild(background);
	this->removeChild(myentity);
	this->removeChild(enemyoe);



	// delete myentity from the heap (there was a 'new' in the constructor)
	delete background;
	delete myentity;
	delete enemyoe;
}

void MyScene::update(float deltaTime)
{
	// ###################################################################
	// Escape key stops the Scene
	// ###################################################################
	if (input()->getKeyUp(KeyCode::Escape)) {
		this->stop();
	}

	// ###################################################################
	// Movement Boat / WASD movement
	// ###################################################################

	// Variables
	float a = myentity->rotation.z;
	float movespeedF = .17;
	float movespeedB = .08;
	float rotspeed = 2;

	// Forward
	if (input()->getKey(KeyCode::W)) {
		myentity->position.x -= movespeedF * sin(a);
		myentity->position.y += movespeedF * cos(a);
												   
		//std::cout << "FORWARD"; 				   
	}											   
		
	// Backwards
	if (input()->getKey(KeyCode::S)) {			   
		myentity->position.x += movespeedB * sin(a);
		myentity->position.y -= movespeedB * cos(a);

		//std::cout << "BACKWARDS";
	}

	// Go right
	if (input()->getKey(KeyCode::D)) {
		myentity->rotation.z += rotspeed * deltaTime;

		//std::cout << "RIGHT";
	}

	// Go left
	if (input()->getKey(KeyCode::A)) {
		myentity->rotation.z -= rotspeed * deltaTime;

		//std::cout << "LEFT";
	}

	// ###################################################################
	// Borders                                                           
	// ###################################################################

	// Player
	if (myentity->position.x < 0) { myentity->position.x = 0; }
	if (myentity->position.x > SWIDTH) { myentity->position.x = SWIDTH; }
	if (myentity->position.y < 0) { myentity->position.y = 0; }
	if (myentity->position.y > SHEIGHT) { myentity->position.y = SHEIGHT; }

	// Enemy
	if (enemyoe->position.x < 0) { enemyoe->position.x = 0; }
	if (enemyoe->position.x > SWIDTH) { enemyoe->position.x = SWIDTH; }
	if (enemyoe->position.y < 0) { enemyoe->position.y = 0; }
	if (enemyoe->position.y > SHEIGHT) { enemyoe->position.y = SHEIGHT; }

	// ###################################################################
	// Movement EnemyOneEye
	// ###################################################################

	// Variables
	float movespeedE = .18;
	Vector2 AR = myentity->position - enemyoe->position;
	float b = enemyoe->rotation.z;
	float angle = AR.getAngle();
	
	// Rotate towards player
	enemyoe->rotation.z = angle + 90;

	// Moving on X-axis / Y-axis
	enemyoe->position.x += movespeedE * sin(b);
	enemyoe->position.y -= movespeedE * cos(b);
}