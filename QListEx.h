#ifndef QLISTEX_H
#define QLISTEX_H

#include <QList>
#include <QHash>
#include <QAbstractListModel>
#include <QDebug>


template<class T>
class QListEx : public QList<T *>
{
	public:
		QListEx()
		{

		}

		QListEx(const QList<T *> &list)
			: QList<T *>(list)
		{

		}

		QListEx(const QListEx<T> &list)
			: QList<T *>(list)
		{

		}

		void sort(bool (*lessThan)(T *, T *))
		{
			qSort(this->begin(), this->end(), lessThan);
		}

		template<class TType>
		QListEx<TType> ofType() const
		{
			QListEx<TType> list;

			foreach(T *item, *this)
			{
				TType *ofType = dynamic_cast<TType *>(item);

				if(ofType)
				{
					list << ofType;
				}
			}

			return list;
		}

		template<class TKey>
		QHash<TKey, QList<T *>> groupBy(TKey (T::*selector)() const)
		{
			QHash<TKey, QList<T *>> grouped;

			foreach(T *item, *this)
			{
				TKey key = ((item)->*(selector))();

				QList<T *> list = grouped[key];
				list << item;
			}

			return grouped;
		}

		operator QList<T *>()
		{
			return *this;
		}

		static QList<T> populate(int size)
		{
			QList<T> list;

			for(int i = 0; i < size; i++)
			{
				list << T();
			}

			return list;
		}

		static QListEx<T> fromList(QList<T> &source)
		{
			QListEx<T> list;

			for(T &item : source)
			{
				list << &item;
			}

			return list;
		}
};

#endif // QLISTEX_H
