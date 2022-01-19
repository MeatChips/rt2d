/**
 * Copyright 2015 Your Name <you@yourhost.com>
 *
 * @file myentity.h
 *
 * @brief description of MyEntity behavior.
 */

#ifndef CROSSHAIR_H
#define CROSSHAIR_H

#include <entity.h>

/// @brief The MyEntity class is the Entity implementation.
class Crosshair : public Entity
{
public:
	/// @brief Constructor
	Crosshair();
	/// @brief Destructor
	virtual ~Crosshair();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

private:
	/* add your private declarations */
};

#endif /* MYENTITY_H */
