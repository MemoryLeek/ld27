#include <qmath.h>

#include "OuterBounds.h"

OuterBounds::OuterBounds()
{
	m_x = 0;
	m_y = 0;
}

OuterBounds::~OuterBounds()
{
	delete m_x;
	delete m_y;
}

int OuterBounds::x() const
{
	return *m_x;
}

int OuterBounds::y() const
{
	return *m_y;
}

void OuterBounds::tryExtend(OuterBounds::Strategy strategy, const int x, const int y)
{
	if(m_x && m_y)
	{
		switch(strategy)
		{
			case TopLeft:
			{
				*m_x = qMin(*m_x, x);
				*m_y = qMin(*m_y, y);

				break;
			}

			case BottomRight:
			{
				*m_x = qMax(*m_x, x);
				*m_y = qMax(*m_y, y);

				break;
			}
		}
	}
	else
	{
		m_x = new int(x);
		m_y = new int(y);
	}
}
