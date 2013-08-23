#ifndef MENUENTRY_H
#define MENUENTRY_H

#include <QObject>

template<class TInstance>
using Callback = void (TInstance::*)();

class IMenuEntry : public QObject
{
	Q_OBJECT

	Q_PROPERTY(QString title READ title NOTIFY titleChanged)

	public:
		virtual QString title() const = 0;

	public slots:
		virtual void invoke() const = 0;

	signals:
		void titleChanged();
};

template<class TInstance>
class MenuEntry : public IMenuEntry
{
	public:
		MenuEntry(const QString &title, TInstance *instance, Callback<TInstance> callback)
		{
			m_title = title;
			m_instance = instance;
			m_callback = callback;
		}

		QString title() const override
		{
			return m_title;
		}

		void invoke() const override
		{
			(m_instance->*m_callback)();
		}

	private:
		QString m_title;
		TInstance *m_instance;
		Callback<TInstance> m_callback;
};

#endif // MENUENTRY_H
