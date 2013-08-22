#ifndef QTIMEREX_H
#define QTIMEREX_H

#include <QTimer>

class QTimerEx
{
	public:
		template<class TInstance>
		static void singleShot(int msec, TInstance *instance, void (TInstance::*slot)())
		{
			QTimer *timer = new QTimer();
			timer->connect(timer, &QTimer::timeout, instance, slot);
			timer->connect(timer, &QTimer::timeout, &QTimer::deleteLater);
			timer->start(msec);
		}
};

#endif // QTIMEREX_H
