#pragma once
#include "ofxGui.h"
#include <json.hpp>
using nlohmann::json;
namespace circleSpace {
	class circle {
	public:
		//Center of circle
		ofPoint location;
		int radius;
		//When circle should be clicked
		int milisecondTime;
		int xCoord;
		int yCoord;
		//Displayed number in the circle
		int displayNum;
		//True if number to display is assigned
		bool assignedNum;
		bool clicked;
		bool deleted;
		/*@param Time circle is clicked
		@return Difference between clicked and expected
		*/
		int getTimeError(int timeClicked);
		/*@param Difference in time between expected and clicked
		@return Score based on the size of the error
		*/
		int scoreClick(int timeError);
		circle(int time, int x, int y, int radius);
		//Deletes the circle
		void deleteCircle();
		/*@param Vector of all circles and the current circle's position
		@return True if all circles before it has been clicked/deleted otherwise false
		*/
		bool isClickable(std::vector<circle> circles, int position);
	};
	inline void to_json(json& j, const circle& circle);
	inline void from_json(const json& j, circle& circle);
}