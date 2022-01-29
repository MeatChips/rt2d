/**
 * Copyright 2015 Your Name <you@yourhost.com>
 *
 * @file myscene.h
 *
 * @brief description of MyScene behavior.
 */

#ifndef MYSCENE_H
#define MYSCENE_H

#include <rt2d/scene.h>
#include <rt2d/text.h>

#include "myentity.h"
#include "background.h"
#include "enemyoe.h"
#include "crosshair.h"
#include "bullet.h"
#include "collider.h"
#include "extraentity.h"

/// @brief The MyScene class is the Scene implementation.
class MyScene : public Scene
{
public:
	/// @brief Constructor
	MyScene();
	/// @brief Destructor
	virtual ~MyScene();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);
	virtual void updateBullets(float deltaTime); 
	virtual void spawnEnemies();
	virtual void enemyMovement(float deltaTime);

	int spawnSpeed = 5;

private:
	/// @brief the rotating square in the middle of the screen
	MyEntity* myentity;
	Background* background;
	EnemyOE* enemyoe;
	Crosshair* crosshair;

	Timer sTimer;
	Timer aliveTimer;

	Collider* square1;
	Collider* square2;
	Collider* circle1;

	std::vector<Bullet*> bullets;
	std::vector<EnemyOE*> enemies;

	Text* scoretext;
	int score;
};

#endif /* SCENE00_H */
