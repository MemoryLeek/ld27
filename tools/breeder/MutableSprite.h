#ifndef MUTABLESPRITE_H
#define MUTABLESPRITE_H

#include <QImage>

class MutableSprite
{
	public:
		void addFrame(const QImage image);
		void setDelay(const float delay);

		bool isValid() const;

	private:
		friend QDataStream &operator <<(QDataStream &stream, const MutableSprite &sprite);

		QList<QImage> m_frames;

		float m_delay;
		float m_index;
};

#endif // MUTABLESPRITE_H
