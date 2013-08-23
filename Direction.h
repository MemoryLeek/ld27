#ifndef DIRECTION_H
#define DIRECTION_H

#include "KeyDirectionMapping.h"

class Key;

class Direction : public KeyDirectionMapping
{
	public:
		Direction(int value);

		static Direction fromKey(const Key &key);
};

#endif // DIRECTION_H
