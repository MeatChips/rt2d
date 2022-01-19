/**
 * This class describes MyScene behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include <fstream>
#include <sstream>
#include <glfw3.h>

#include <rt2dconfig.h>

#include "myscene.h"

MyScene::MyScene() : Scene()
{
	// create a single instance of MyEntity in the middle of the screen.
	// the Sprite is added in Constructor of MyEntity.
	myentity = new MyEntity();
	background = new Background();
	enemyoe = new EnemyOE();
	crosshair = new Crosshair();
	bullet = new Bullet();
	myentity->position = Point2(SWIDTH/2, SHEIGHT/2);
	background->position = Point2(SWIDTH/2, SHEIGHT/2);
	enemyoe->position = Point2(SWIDTH/1.2, SHEIGHT/1.2);
	crosshair->position = Point2(SWIDTH/3.2, SHEIGHT/3.2);
	bullet->position = Point2(SWIDTH/2, SHEIGHT/2);

	// create the scene 'tree'
	// add myentity to this Scene as a child.
	this->addChild(background);
	this->addChild(myentity);
	this->addChild(enemyoe);
	this->addChild(bullet);
	this->addChild(crosshair);
}

MyScene::~MyScene()
{
	// deconstruct and delete the Tree
	this->removeChild(background);
	this->removeChild(myentity);
	this->removeChild(enemyoe);
	this->removeChild(crosshair);
	this->removeChild(bullet);

	// delete myentity from the heap (there was a 'new' in the constructor)
	delete background;
	delete myentity;
	delete enemyoe;
	delete crosshair;
	delete bullet;
}

void MyScene::updateBullets(float deltaTime)
{
	for (int i = bullets.size() - 1; i >= 0; i--) { // backwards!!!
		if (bullets[i]->position.x > SWIDTH || bullets[i]->position.x < 0 || bullets[i]->position.y < 0 || bullets[i]->position.y > SHEIGHT) {
			std::cout << "-- deleting Bullet " << i << " : (" << bullets[i]->position.x << "," << bullets[i]->position.y << ")" << std::endl;
			removeChild(bullets[i]);
			delete bullets[i]; // delete from the heap first
			bullets.erase(bullets.begin() + i); // then, remove from the list
		}
	}
}

//void MyScene::kaboom(float deltaTime) {
//	if (bullet->position = crosshair->position) {
//		delete bullet;
//	}
//}

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

	// Crosshair
	if (crosshair->position.x < 0) { crosshair->position.x = 0; }
	if (crosshair->position.x > SWIDTH) { crosshair->position.x = SWIDTH; }
	if (crosshair->position.y < 0) { crosshair->position.y = 0; }
	if (crosshair->position.y > SHEIGHT) { crosshair->position.y = SHEIGHT; }

	// Bullet
	if (bullet->position.x < 0) { bullet->position.x = 0; }
	if (bullet->position.x > SWIDTH) { bullet->position.x = SWIDTH; }
	if (bullet->position.y < 0) { bullet->position.y = 0; }
	if (bullet->position.y > SHEIGHT) { bullet->position.y = SHEIGHT; }

	// ###################################################################
	// Movement EnemyOneEye
	// ###################################################################

	// Variables
	float movespeedE = .13;
	Vector2 AR = myentity->position - enemyoe->position;
	float b = enemyoe->rotation.z;
	float angle = AR.getAngle();
	
	// Rotate towards player
	enemyoe->rotation.z = angle + 90;

	// Moving on X-axis / Y-axis
	enemyoe->position.x += movespeedE * sin(b);
	enemyoe->position.y -= movespeedE * cos(b);

	// ###################################################################
	// Crosshair movement 
	// ###################################################################

	// Variables
	int mouseX = input()->getMouseX();
	int mouseY = input()->getMouseY();

	// Crosshair on mouse position
	crosshair->position.x = mouseX;
	crosshair->position.y = mouseY;

	// Hide cursor
	// Code changed in renderer.cpp

	// ###################################################################
	// Shooting
	// ###################################################################

	updateBullets(deltaTime);

	// Variables
	Vector2 shootpos = crosshair->position;
	Vector2 shippos = myentity->position;
	Vector2 v = shootpos - shippos;

	// Bullet flies towards crosshair
	if (input()->getMouseDown(GLFW_MOUSE_BUTTON_LEFT)) {
		Bullet* b = new Bullet();
		addChild(b);
		bullets.push_back(b);
		b->position = shippos;
		b->rotation = myentity->rotation;
		b->velocity = v.getNormalized();
		b->velocity += b->distance_travelled;
		if (b->distance_travelled > v.getLength()) {
			//kaboom();
			//std::cout << b->distance_travelled;
		}

		std::cout << "SHOOT";
	}
}