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
#include "collider.h"

MyScene::MyScene() : Scene()
{
	// Timers
	sTimer.start();
	aliveTimer.start();

	// create a single instance of MyEntity in the middle of the screen.
	// the Sprite is added in Constructor of MyEntity.
	myentity = new MyEntity();
	background = new Background();
	crosshair = new Crosshair();
	scoretext = new Text();
	myentity->position = Point2(SWIDTH/2, SHEIGHT/2);
	background->position = Point2(SWIDTH/2, SHEIGHT/2);
	crosshair->position = Point2(SWIDTH/3.2, SHEIGHT/3.2);
	scoretext->position.x = 50;
	scoretext->position.y = 75;

	score = 0;

	// create the scene 'tree'
	// add myentity to this Scene as a child.
	this->addChild(background);
	this->addChild(myentity);
	this->addChild(crosshair);
	this->addChild(scoretext);
}

MyScene::~MyScene()
{
	// deconstruct and delete the Tree
	this->removeChild(background);
	this->removeChild(myentity);
	this->removeChild(crosshair);

	// delete myentity from the heap (there was a 'new' in the constructor)
	delete background;
	delete myentity;
	delete crosshair;
}

void MyScene::updateBullets(float deltaTime)
{
	// Deleting bullets when they go outside the screen
	for (int i = bullets.size() - 1; i >= 0; i--) { // backwards!!!
		if (bullets[i]->position.x > SWIDTH || bullets[i]->position.x < 0 || bullets[i]->position.y < 0 || bullets[i]->position.y > SHEIGHT) {
			std::cout << "-- deleting Bullet " << i << " : (" << bullets[i]->position.x << "," << bullets[i]->position.y << ")" << std::endl;
			this->removeChild(bullets[i]);
			delete bullets[i]; // delete from the heap first
			bullets.erase(bullets.begin() + i); // then, remove from the list
		}
	}
}

void MyScene::enemyMovement(float deltaTime) {

	// Movement of the enemy (towards player)
	for (int i = 0; i < enemies.size(); i++) {
		// Variables
		float movespeedE = 85;
		Vector2 AR = myentity->position - enemies[i]->position;
		float b = enemies[i]->rotation.z;
		float angle = AR.getAngle();

		// Rotate towards player
		enemies[i]->rotation.z = angle + 90;

		// Moving on X-axis / Y-axis
		enemies[i]->position.x += movespeedE * sin(b) * deltaTime;
		enemies[i]->position.y -= movespeedE * cos(b) * deltaTime;
	}
}

void MyScene::spawnEnemies()
{
	// Spawning the enemies on the top of the screen
	EnemyOE* e = new EnemyOE();
	enemies.push_back(e);
	this->addChild(e);

	// Random position on the x-axis
	e->position.x = rand() % 1180;
	e->position.y = 2;

	std::cout << "SPAWN ENEMY" << std::endl;
}



void MyScene::update(float deltaTime)
{

	// The time you are alive
	if (aliveTimer.seconds() >= 0.1)
	{
		score += 2;
	}

	// Deleting enemies if bullets hit
	int sizeBullets = bullets.size();
	int sizeEnemies = enemies.size();
	for (int i = 0; i < sizeBullets; i++) {
		for (int ii = 0; ii < sizeEnemies; ii++) {
			if (Collider::circle2rectangle(bullets[i], enemies[ii])) {
				removeChild(enemies[ii]);
				delete enemies[ii]; // delete from the heap first
				std::cout << "HIT" << std::endl;
			}
		}
	}

	// Spawning enemies every (amount) of seconds
	if (sTimer.seconds() > spawnSpeed) {
		spawnEnemies();
		sTimer.start();
	}

	if (sTimer.seconds() > 5 && spawnSpeed > 0.25) {
		spawnSpeed -= 0.25;
		sTimer.start();
		std::cout << spawnSpeed << std::endl;
	}

	// Giving the enemies the possibility to move towards the player
	if (enemies.size() > 0) {
		enemyMovement(deltaTime);
	}

	// If enemy touches player it will stop the game
	for (int i = 0; i < enemies.size(); i++) {
		if (Collider::rectangle2rectangle(myentity, enemies[i])) {
			this->stop();
		}
	}

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
	float movespeedF = 100;
	float movespeedB = 57;
	float rotspeed = 2;

	// Forward
	if (input()->getKey(KeyCode::W)) {
		myentity->position.x -= movespeedF * sin(a) * deltaTime;
		myentity->position.y += movespeedF * cos(a) * deltaTime;
												   
		//std::cout << "FORWARD"; 				   
	}											   
		
	// Backwards
	if (input()->getKey(KeyCode::S)) {			   
		myentity->position.x += movespeedB * sin(a) * deltaTime;
		myentity->position.y -= movespeedB * cos(a) * deltaTime;

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
	if (myentity->position.x < 0) { myentity->position.x = 0; 		this->stop();}
	if (myentity->position.x > SWIDTH) { myentity->position.x = SWIDTH; 		this->stop();}
	if (myentity->position.y < 0) { myentity->position.y = 0; 		this->stop();}
	if (myentity->position.y > SHEIGHT) { myentity->position.y = SHEIGHT; 		this->stop();}

	// Crosshair
	if (crosshair->position.x < 0) { crosshair->position.x = 0; }
	if (crosshair->position.x > SWIDTH) { crosshair->position.x = SWIDTH; }
	if (crosshair->position.y < 0) { crosshair->position.y = 0; }
	if (crosshair->position.y > SHEIGHT) { crosshair->position.y = SHEIGHT; }

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

	// Update buellets
	updateBullets(deltaTime);
	

	// Variables
	Vector2 shootpos = crosshair->position;
	Vector2 shippos = myentity->position;
	Vector2 v = shootpos - shippos;

	// Bullet flies towards crosshair
	if (input()->getMouseDown(0)) {
		Bullet* b = new Bullet();
		this->addChild(b);
		bullets.push_back(b);
		b->position = shippos;
		b->rotation = myentity->rotation;
		b->velocity = v.getNormalized();
		b->velocity += b->distance_travelled;
		if (b->distance_travelled > v.getLength()) {
			//kaboom();
			//std::cout << b->distance_travelled << std::endl;
		}

		std::cout << "SHOOT";
	}

	std::string st = "Score: ";
	st += std::to_string(score);
	scoretext->message(st);
}