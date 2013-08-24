#include "JoystickEvent.h"

JoystickEvent::JoystickEvent()
	: m_axis(0, 0),
	  m_buttons(ButtonNone)
{
}

JoystickEvent::JoystickEvent(const QVector2D &axis, Buttons buttons)
	: m_axis(axis),
	  m_buttons(buttons)
{
}

bool JoystickEvent::operator !=(const JoystickEvent &other)
{
	return m_axis != other.m_axis || m_buttons != other.m_buttons;
}

QVector2D JoystickEvent::axis() const
{
	return m_axis;
}

JoystickEvent::Buttons JoystickEvent::buttons() const
{
	return m_buttons;
}
