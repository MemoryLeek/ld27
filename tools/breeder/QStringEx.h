#ifndef QSTRINGEX_H
#define QSTRINGEX_H

#include <QString>

class QStringEx
{
	public:
		template<class ...T>
		static QString format(const QString &format, T... arguments)
		{
			return QString(format).arg(arguments...);
		}

		static QString format(const QString &format)
		{
			return format;
		}
};

#endif // QSTRINGEX_H
