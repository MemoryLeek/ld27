#include "Key.h"
#include "Direction.h"

Key::Key(int value)
	: KeyDirectionMapping(value)
{

}

Key Key::fromDirection(const Direction &direction)
{
	return mapping().key(direction);
}
