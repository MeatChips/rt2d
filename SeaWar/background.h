/**
 * Copyright 2015 Your Name <you@yourhost.com>
 *
 * @file myentity.h
 *
 * @brief description of MyEntity behavior.
 */

#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "extraentity.h"

/// @brief The MyEntity class is the Entity implementation.
class Background : public extraentity
{
public:
	/// @brief Constructor
	Background();
	/// @brief Destructor
	virtual ~Background();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

private:
	/* add your private declarations */
};

#endif /* MYENTITY_H */
