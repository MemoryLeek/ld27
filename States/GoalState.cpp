#include "GoalState.h"
#include "SharedState.h"

#include "States/GameState.h"

namespace States
{
	GoalState::GoalState()
	{
		setFlag(QQuickItem::ItemHasContents);
	}

	QSGNode *GoalState::updatePaintNode(QSGNode *node, QQuickItem::UpdatePaintNodeData *)
	{
//		changeState<States::GameState>();

		return node;
	}

	void GoalState::initialize()
	{
		SharedState *state = getComponent<SharedState>();
		state->nextMap();
	}

	void GoalState::complete()
	{

	}
}
