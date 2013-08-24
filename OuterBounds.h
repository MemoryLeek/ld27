#ifndef OUTERBOUNDS_H
#define OUTERBOUNDS_H

class OuterBounds
{
	public:
		enum Strategy
		{
			TopLeft,
			BottomRight
		};

		OuterBounds();
		~OuterBounds();

		int x() const;
		int y() const;

		void tryExtend(Strategy strategy, const int x, const int y);

	private:
		int *m_x;
		int *m_y;
};

#endif // OUTERBOUNDS_H
