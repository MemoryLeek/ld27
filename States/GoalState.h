#ifndef GOALSTATE_H
#define GOALSTATE_H

#include "State.h"

namespace States
{
	class GoalState : public State<QQuickItem>
	{
		public:
			GoalState();

		private:
			QSGNode *updatePaintNode(QSGNode *node, UpdatePaintNodeData *) override;

			void initialize() override;
			void complete() override;
	};
}

#endif // GOALSTATE_H
