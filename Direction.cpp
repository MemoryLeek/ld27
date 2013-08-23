#include "Direction.h"
#include "Key.h"

Direction::Direction(int value)
	: KeyDirectionMapping(value)
{

}

Direction Direction::fromKey(const Key &key)
{
	return mapping().value(key);
}
