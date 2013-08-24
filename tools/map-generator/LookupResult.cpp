#include "LookupResult.h"

LookupResult::LookupResult(bool valid)
{
	m_valid = valid;
}

bool LookupResult::isValid()
{
	return m_valid;
}
