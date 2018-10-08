#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "fifo.hpp"

TEST_CASE("Fifo", "Basic queue behaviour") {
	// zero capacity
	Fifo* f = new Fifo(0);
	REQUIRE(f != nullptr);
	REQUIRE(!f->push(0));

	// capacity 1
	Fifo* f2 = new Fifo(1);
	REQUIRE(f2 != nullptr);
	REQUIRE(f2->push(0));
	REQUIRE(!f2->push(1));

	// capacity 2
	Fifo* f3 = new Fifo(2);
	REQUIRE(f3 != nullptr);
	REQUIRE(f3->push(0));
	REQUIRE(f3->push(1));
	REQUIRE(!f3->push(2));	// Nope, full
	REQUIRE(f3->pop() == 0);
	REQUIRE(f3->push(2));	// Now there's space
	REQUIRE(f3->pop() == 1);
	REQUIRE(f3->pop() == 2);
}
