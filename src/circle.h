#pragma once
#include "ofxGui.h"
#include <json.hpp>
using nlohmann::json;
namespace circleSpace {
	class circle {
	public:
		ofPoint location;
		int radius;
		int milisecondTime;
		int xCoord;
		int yCoord;
		bool clicked;
		bool deleted;
		int getTimeError(int timeClicked);
		int scoreClick(int timeError);
		circle(int time, int x, int y, int radius);
		void deleteCircle();
	};
	inline void to_json(json& j, const circle& circle);
	inline void from_json(const json& j, circle& circle);
}