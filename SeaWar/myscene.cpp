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
	myentity->position = Point2(SWIDTH/2, SHEIGHT/2);
	background->position = Point2(SWIDTH/2, SHEIGHT/2);
	float x;
	float y;
	float z;

	// create the scene 'tree'
	// add myentity to this Scene as a child.
	this->addChild(background);
	this->addChild(myentity);
}


MyScene::~MyScene()
{
	// deconstruct and delete the Tree
	this->removeChild(background);
	this->removeChild(myentity);



	// delete myentity from the heap (there was a 'new' in the constructor)
	delete background;
	delete myentity;
}


void MyScene::update(float deltaTime)
{
	// ###############################################################
	// Escape key stops the Scene
	// ###############################################################
	if (input()->getKeyUp(KeyCode::Escape)) {
		this->stop();
	}

	// ###############################################################
	// Movement boat / WASD movement
	// ###############################################################

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

	// Borders
	if (myentity->position.x < 0) { myentity->position.x = 0; }
	if (myentity->position.x > SWIDTH) { myentity->position.x = SWIDTH; }
	if (myentity->position.y < 0) { myentity->position.y = 0; }
	if (myentity->position.y > SHEIGHT) { myentity->position.y = SHEIGHT; }
}
