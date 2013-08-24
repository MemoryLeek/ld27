#include "JoystickEvent.h"

JoystickEvent::JoystickEvent()
	: m_axis(0, 0)
{
}

JoystickEvent::JoystickEvent(const QVector2D &axis)
	: m_axis(axis)
{
}

bool JoystickEvent::operator !=(const JoystickEvent &other)
{
	return m_axis != other.m_axis;
}

QVector2D JoystickEvent::getAxis() const
{
	return m_axis;
}
