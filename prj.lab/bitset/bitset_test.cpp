#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <bitset/bitset.h>
#include <iostream>
#include <sstream>
TEST_CASE("TESTING ALL") {
	Bitset a(24, 1);
	CHECK(a == Bitset("111111111111111111111111"));
	a <<= 2;
	CHECK(a == Bitset("111111111111111111111100"));
	a >>= 2;
	CHECK(a == Bitset("001111111111111111111111"));
	CHECK_THROWS_AS(Bitset(-3), std::invalid_argument); // negative size
	CHECK_THROWS_AS(Bitset(0) &= Bitset(1), std::logic_error); // different sizes
	CHECK_THROWS_AS(Bitset(3)[-1], std::invalid_argument); // negative index
	Bitset b(24, 1);
	std::stringstream sstream("");
	sstream << b;
	CHECK(sstream.str() == std::string("111111111111111111111111"));
	bool bool_buff = a[22];
	CHECK_FALSE(bool_buff);
	a[22] = false;
	CHECK(~a[22]);
}