#pragma once
#include "imgui.h"
#include <cstring>
#include <string>
#include <iomanip>
#include <sstream>
#include "Calculator.h"

namespace MyGUI {

	void RenderMain(float, float);
	void RenderInfo(float, float, ImGuiIO&);

}