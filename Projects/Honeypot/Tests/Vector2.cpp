#include "../Honeypot.h"

#include <Honey.h>

using namespace Honey::Math;

TEST_CATEGORY("Vector2", "Vector2 tests") {

	TEST_CASE("Vector2 Zero")
	{
		CHECK(Vector2(0, 0) == Vector2::Zero);
	}

	HNYPT_TEST_CASE("Vector2 One")
	{
		CHECK(Vector2(1, 1) == Vector2::One);
	}

}

