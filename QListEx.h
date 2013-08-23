#ifndef QLISTEX_H
#define QLISTEX_H

#include <QList>
#include <QHash>
#include <QAbstractListModel>
#include <QDebug>

template<class T>
class QListEx : public QList<T>
{
	public:
		void sort(bool (*lessThan)(T &, T &))
		{
			qSort(this->begin(), this->end(), lessThan);
		}
};

template<class T>
class QListEx<T *> : public QList<T *>
{
	public:
		void sort(bool (*lessThan)(T *, T *))
		{
			qSort(this->begin(), this->end(), lessThan);
		}
};

#endif // QLISTEX_H
