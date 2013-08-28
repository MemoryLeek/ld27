#ifndef DEATHSTATE_H
#define DEATHSTATE_H

#include <QQuickItem>

#include "State.h"

namespace States
{
	class DeathState : public State<QQuickItem>
	{
		Q_OBJECT

		public:
			DeathState();

		private:
			void initialize() override;
			void complete() override;
	};
}

#endif // DEATHSTATE_H
