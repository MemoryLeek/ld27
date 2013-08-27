#ifndef RENDERINGCOMMAND_H
#define RENDERINGCOMMAND_H

#include <QPainter>
#include <QObject>

template<class ...TArguments>
using Method = void (QPainter::*)(TArguments...);

class IRenderingCommand : public QObject
{
	public:
		virtual void invoke(QPainter *painter) = 0;
};

template<class ...TArguments>
class RenderingCommand : public IRenderingCommand
{
	public:
		RenderingCommand(Method<TArguments...> method, TArguments... arguments)
		{
			m_invoker = std::bind(&RenderingCommand<TArguments...>::call, this, std::placeholders::_1, method, arguments...);
		}

		void invoke(QPainter *painter) override
		{
			m_invoker(painter);
		}

	private:
		void call(QPainter *painter, Method<TArguments...> method, TArguments... arguments)
		{
			(painter->*method)(arguments...);
		}

		std::function<void(QPainter *)> m_invoker;
};

#endif // RENDERINGCOMMAND_H
