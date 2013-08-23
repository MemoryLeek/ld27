#include "KeyDirectionMapping.h"
#include "Key.h"

KeyDirectionMapping::operator int() const
{
	return m_value;
}

KeyDirectionMapping::KeyDirectionMapping(int value)
{
	m_value = value;
}

QMap<int, int> KeyDirectionMapping::mapping()
{
	return
	{
		{ Key::KeyDown, 90 },
		{ Key::KeyLeft, 180 },
		{ Key::KeyRight, 0 },
		{ Key::KeyUp, -90 }
	};
}
