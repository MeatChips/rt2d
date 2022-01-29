/**
 * Copyright 2015 Your Name <you@yourhost.com>
 *
 * @file myentity.h
 *
 * @brief description of MyEntity behavior.
 */

#ifndef BULLET_H
#define BULLET_H

#include "extraentity.h"

/// @brief The MyEntity class is the Entity implementation.
class Bullet : public extraentity
{
public:
	/// @brief Constructor
	Bullet();
	/// @brief Destructor
	virtual ~Bullet();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

	Vector2 velocity;
	float distance_travelled = 0;

private:
	/* add your private declarations */
};

#endif /* BULLET_H */
