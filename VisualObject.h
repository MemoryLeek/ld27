#ifndef VISUALOBJECT_H
#define VISUALOBJECT_H

template<class T>
class VisualObject : public T
{
	protected:
		virtual void initialize() = 0;
		virtual void complete() = 0;
	
	private:
		void classBegin() override
		{
			T::classBegin();
			initialize();
		}

		void componentComplete() override
		{
			T::componentComplete();
			complete();
		}
};

#endif // VISUALOBJECT_H
