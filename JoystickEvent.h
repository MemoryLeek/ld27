#ifndef JOYSTICKEVENT_H
#define JOYSTICKEVENT_H

#include <QVector2D>

class JoystickEvent
{
	public:
		JoystickEvent();
		JoystickEvent(const QVector2D &axis);

		bool operator !=(const JoystickEvent &other);

		QVector2D getAxis() const;

	private:
		QVector2D m_axis;
};

#endif // JOYSTICKEVENT_H
