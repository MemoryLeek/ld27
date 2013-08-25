#ifndef JOYSTICKEVENT_H
#define JOYSTICKEVENT_H

#include <QVector2D>

class JoystickEvent
{
	public:
		enum Button
		{
			ButtonNone,
			ButtonJump
		};
		Q_DECLARE_FLAGS(Buttons, Button)

		JoystickEvent();
		JoystickEvent(const QVector2D &axis, Buttons buttons);

		bool operator !=(const JoystickEvent &other);

		QVector2D axis() const;
		Buttons buttons() const;

	private:
		QVector2D m_axis;
		Buttons m_buttons;
};
Q_DECLARE_OPERATORS_FOR_FLAGS(JoystickEvent::Buttons)

#endif // JOYSTICKEVENT_H
