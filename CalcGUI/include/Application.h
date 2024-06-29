#pragma once
#include "imgui.h"
#include <cstring>
#include <iostream>
#include "Calculator.h"

namespace MyGUI {
	extern char* history_exp;
	void RenderMain(float, float);
	void RenderInfo(float, float, ImGuiIO&);

}