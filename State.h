#ifndef STATE_H
#define STATE_H

#include <QRegularExpression>

#include "Window.h"
#include "Container.h"
#include "VisualObject.h"

template<class T>
class State
	: public VisualObject<T>
	, public Container
{
	protected:

};

#endif // STATE_H
