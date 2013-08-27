#ifndef ICOLLECTIONITEM_H
#define ICOLLECTIONITEM_H

#include <QList>

template<class T>
class ICollectionItem
{
	public:
		void addTo(QList<T> &list)
		{
			list << *(T *)this;
		}

		void removeFrom(QList<T> &list)
		{
			list.removeAll(*(T *)this);
		}
};

#endif // ICOLLECTIONITEM_H
