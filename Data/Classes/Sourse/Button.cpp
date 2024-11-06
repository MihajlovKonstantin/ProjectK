#include "Data/Classes/Header/Button.h"



Button::Button(std::array<float, 2> inputSize, std::array<float, 2> inputPosition, std::string inputText, float inputScale, int inputButtonIndex, int inputSwitchControlIndex, int inputDataControlIndex, int SecondSCI,  vector<int>& SecondDCI)
{
	size = inputSize;
	position = inputPosition;
	text = inputText;
	scale = inputScale;
	SwitchControlIndex = inputSwitchControlIndex;
	DataControlIndex = inputDataControlIndex;
}

Button::Button(std::array<float, 2> inputSize, std::array<float, 2> inputPosition, std::string inputText, float inputScale,int inputButtonIndex, int inputSwitchControlIndex, int inputDataControlIndex)
 {
	 size = inputSize;
	 position = inputPosition;
	 text = inputText;
	 scale = inputScale;
	 SwitchControlIndex = inputSwitchControlIndex;
	 DataControlIndex = inputDataControlIndex;
 }

 Button::Button()
 {
 }

 Button::~Button()
 {
 }

 std::string Button::GetText()
 {
	 return text;
 }

 std::array<float,2> Button::GetSize()
 {
	 return size;
 }

 std::array<float, 2> Button::GetPosition()
 {
	 return position;
 }
 float Button::GetScale()
 {
	 return scale;
 }

 std::array<int, 2>Button::SendClickData()
 {
	 std::array<int, 2> result = { SwitchControlIndex, DataControlIndex };
	 return result;
 }

 void Button::ChangeVisiable()
 {
	 if (visable)
	 {
		 visable = false;
	 }
	 else
	 {
		 visable = true;
	 }
 }

 bool Button::GetVisable()
 {
	 return visable;
 }

 void Button::ChangeActive()
 {
	 if(active)
	 {
		active = false;
	 }
	 else
	 {
		active = true;
	 }
 }

 bool Button::GetActive()
 {
	 return active;
 }


