#pragma once
#include "imgui.h"
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include "Calculator.h"

namespace MyGUI 
{
	extern char* history_exp;
	void RenderMain(float, float);
	void RenderInfo(float, float, ImGuiIO&);

}