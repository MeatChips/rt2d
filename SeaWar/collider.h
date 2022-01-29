/**
 * This class describes Collider behavior.
 *
 * Copyright 2019 Rik Teerling <rik@onandoffables.com>
 */

#ifndef COLLIDER_H
#define COLLIDER_H

#include <algorithm> // std::min + std::max
#include <rt2d/pointx.h> // Point2
#include "extraentity.h"

class Collider
{
public:

	// https://yal.cc/rectangle-circle-intersection-test/
	static bool circle2rectangle(const extraentity* circle, const extraentity* rect) {
		float mx = std::max(rect->position.x, std::min(circle->position.x, rect->position.x + rect->width));
		float my = std::max(rect->position.y, std::min(circle->position.y, rect->position.y + rect->height));
		float dx = circle->position.x - mx;
		float dy = circle->position.y - my;
		return (dx * dx + dy * dy) < (circle->radius * circle->radius);
	}

	static bool rectangle2rectangle(const extraentity * rect1, const extraentity * rect2) {
		float mx = std::max(rect2->position.x, std::min(rect1->position.x, rect2->position.x + rect2->width));
		float my = std::max(rect2->position.y, std::min(rect1->position.y, rect2->position.y + rect2->height));
		float dx = rect1->position.x - mx;
		float dy = rect1->position.y - my;
		return (dx * dx + dy * dy) < (rect1->radius * rect1->radius);


	}

private:
	// Disallow creating an instance of this object
	Collider() {}
};

#endif /* COLLIDER_H */