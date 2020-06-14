#include "../Honeypot.h"

HNYPT_TEST_CASE("Two Plus Two")
{
	HNYPT_CHECK(2 + 2 == 5);
	HNYPT_CHECK_EXCEPTION(throw 20, int);
}