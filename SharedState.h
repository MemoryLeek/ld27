#ifndef SHAREDSTATE_H
#define SHAREDSTATE_H

#include <QStringList>
#include <QMetaType>

class SharedState : public QObject
{
	Q_OBJECT

	public:
		SharedState();

		QStringList availableMaps() const;
		QString currentMap() const;

		void nextMap();
		void previousMap();

	private:
		QStringList m_availableMaps;
		int m_currentMap;
};

Q_DECLARE_METATYPE(SharedState *)

#endif // SHAREDSTATE_H
