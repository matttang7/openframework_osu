#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "circle.h"
#include "slider.h"
using namespace circleSpace;
//int main() {
//	int result = Catch::Session().run();
//	system("pause");
//	return result;
//}
TEST_CASE("Checks if methods in circle class work correctly", "[circle]") {
	circle c = circle(0, 0, 0, 50);
	REQUIRE(c.scoreClick(0) == 100);
	c.deleteCircle();
	REQUIRE(c.deleted == true);
	std::vector<circle> circles;
	circles.push_back(c);
	circles.push_back(circle(1, 1, 1, 50));
	REQUIRE(c.isClickable(circles, 1) == true);
}
TEST_CASE("Checks if slider class work correctly", "[slider]") {
	slider s = slider(0, 0, 0, 0, 0, 0, 0, 0);
	s.deleteSlider();
	REQUIRE(s.deleted == true);
	REQUIRE(s.pointOne.x < 0);
	REQUIRE(s.pointOne.y < 0);
}