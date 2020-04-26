#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "Size.h"
using y44::curses_lib::Size;

TEST_CASE("Size struct", "[Size]") {
  Size s1{1, 2};
  Size s2{3, 4};

  REQUIRE(s1.width == 1);
  REQUIRE(s1.height == 2);
  
  Size s3 = s1 + s2;
  REQUIRE(s3.width == 4);
  REQUIRE(s3.height == 6);

  Size s4;
  s4 += s3;
  REQUIRE(s4.width == s3.width);
  REQUIRE(s4.height == s3.height);

  Size s5;
  s5.width = 5;
  s5.height = 9;
  s5 += s3;
  REQUIRE(s5.width == 5 + 4);
  REQUIRE(s5.height == 9 + 6);

}

