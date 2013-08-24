#ifndef LOOKUPRESULT_H
#define LOOKUPRESULT_H

class LookupResult
{
	public:
		LookupResult(bool valid);

		bool isValid();

	private:
		bool m_valid;
};

#endif // LOOKUPRESULT_H
