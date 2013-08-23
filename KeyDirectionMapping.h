#ifndef KEYDIRECTIONMAPPING_H
#define KEYDIRECTIONMAPPING_H

#include <QMap>

class KeyDirectionMapping
{
	public:
		operator int() const;

	protected:
		KeyDirectionMapping(int value);

		static QMap<int, int> mapping();

	private:
		int m_value;
};

#endif // KEYDIRECTIONMAPPING_H
