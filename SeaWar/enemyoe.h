/**
 * Copyright 2015 Your Name <you@yourhost.com>
 *
 * @file myentity.h
 *
 * @brief description of MyEntity behavior.
 */

#ifndef ENEMYOE_H
#define ENEMYOE_H

#include <entity.h>

/// @brief The MyEntity class is the Entity implementation.
class EnemyOE : public Entity
{
public:
	/// @brief Constructor
	EnemyOE();
	/// @brief Destructor
	virtual ~EnemyOE();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

private:
	/* add your private declarations */
};

#endif /* MYENTITY_H */
