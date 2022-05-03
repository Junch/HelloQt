
#include "catch.hpp"
#include "counter.h"

TEST_CASE("signal & slot", "[signal]")
{
    Counter counter;
    counter.setValue(10);
}
