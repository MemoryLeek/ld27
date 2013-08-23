#ifndef KEY_H
#define KEY_H

#include "KeyDirectionMapping.h"

class Direction;

class Key : public KeyDirectionMapping
{
	public:
		enum Keys
		{
			KeyDown = 0,
			KeyLeft = 1,
			KeyRight = 2,
			KeyUp = 3
		};

		Key(int value);

		static Key fromDirection(const Direction &direction);
};

#endif // KEY_H
