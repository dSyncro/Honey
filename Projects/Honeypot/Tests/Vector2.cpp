#include "../Honeypot.h"

#include <Honey.h>

using namespace Honey::Math;

HNYPT_TEST_CATEGORY(Vector2, "Vector2 tests") {

	HNYPT_TEST_CASE_NODESCR(Vector2Zero)
	{
		CHECK(Vector2(0, 0) == Vector2::Zero);
	}

	HNYPT_TEST_CASE_NODESCR(Vector2One)
	{
		CHECK(Vector2(1, 1) == Vector2::One);
	}

	HNYPT_TEST_CATEGORY(Vector2Test, "Vector2 tests")
	{
		HNYPT_TEST_CASE_NODESCR(Vector2OneZero)
		{
			CHECK(Vector2(1, 0) == Vector2::One);
		}
	}

}

