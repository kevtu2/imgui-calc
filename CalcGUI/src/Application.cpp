﻿#include "Application.h"

namespace MyGUI {
	static bool startCalc = false;

	void RenderMain(float workPosx, float workPosy) {

		// For styling
		ImGuiStyle& style = ImGui::GetStyle();

		ImGui::SetNextWindowPos(ImVec2((workPosx + 1280-500), (workPosy + 50)), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(424, 689), ImGuiCond_Always); // W,H

		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse;
		windowFlags |= ImGuiWindowFlags_NoResize;
		windowFlags |= ImGuiWindowFlags_NoScrollbar;
		windowFlags |= ImGuiWindowFlags_NoScrollWithMouse;

		// Make calculator window
		if (ImGui::Begin("Calculator", &startCalc, windowFlags)) {

			// Math expression display variables - Displays current operations.
			ImGuiWindowFlags inputFlags = ImGuiInputTextFlags_ReadOnly;
			inputFlags |= ImGuiInputTextFlags_NoUndoRedo;
			static char expression[256] = ""; // Expression to display
			ImGui::InputTextMultiline("##Operation", expression, IM_ARRAYSIZE(expression), ImVec2(408, 20), inputFlags);

			// Calculator input box
			static char input[256] = "0";
			ImGui::InputTextMultiline("##Input", input, IM_ARRAYSIZE(input), ImVec2(408, 100), inputFlags);

			ImGui::Spacing();

			ImGui::BeginDisabled(strlen(input) >= 54);

			// CALCULATOR LAYOUT:
			const char* buttons[6][4] = {
				{"cos","sin", "tan","Clr"},
				{"sqr","sqrt","/",  "Del"},
				{"7",  "8",  "9",   "*"	 },
				{"4",  "5",  "6",   "-"	 },
				{"1",  "2",  "3",   "+"	 },
				{"0",  ".",  "(-)", "="	 }
			};

			// For calculator logic (class)
			static Calculator calc;
			static char current[256] = ""; // Current expression to calculate
			static bool firstClear = true;

			// Load buttons
			for (int row = 0; row < 6; ++row) {
				for (int col = 0; col < 4; ++col) {
					{ // Specific shading for different buttons/operations
						if (row == 0 || row == 1 || col == 3) {
							// Row/Col specific highlighting
							style.Colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.60f);
							style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);

							if (buttons[row][col] == "=") {
								// Highlight "=" button
								style.Colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.85f);
								style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
							}
						} else {
							style.Colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
							style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.60f);
						}
					}
					if (ImGui::Button(buttons[row][col], ImVec2(96, 80))) {
						if (row >= 2 && col == 3) {
							// Operator buttons - Need to execute calculation immediately after 2nd operand is inputted
							// For display
							(buttons[row][col] == "=") ? strcat_s(expression, input) : strcpy_s(expression, input);
							strcat_s(expression, buttons[row][col]);

							// For calculations
							strcpy_s(current, input);
							strcat_s(current, buttons[row][col]);
							strcpy_s(input, calc.parse(current));
							firstClear = true;

						} else if (firstClear && buttons[row][col] != "Clr") {
							firstClear = false;
							strcpy_s(input, "");
							strcat_s(input, buttons[row][col]);

						} else if (buttons[row][col] == "Del") {
							calc.del(input);

						} else if (buttons[row][col] == "Clr") {
							calc.clr();
							expression[0] = '\0';
							strcpy_s(input, "0");

						} else {
							strcat_s(input, buttons[row][col]);
						}
					}
					ImGui::SameLine();
				}
				ImGui::Spacing();
				ImGui::Spacing();
			}

			ImGui::EndDisabled();
		}
		ImGui::End();
		return;
	}
	
	void RenderInfo(float workPosx, float workPosy, ImGuiIO& io) {
		// Information window dimensions
		ImGui::SetNextWindowPos(ImVec2((workPosx + 20), (workPosy + 30)), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(360, 140), ImGuiCond_Always);

		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoResize;

		// Make info window
		if (ImGui::Begin("Information"), nullptr, windowFlags) {
			ImGui::Text("Welcome to my Calculator");
			ImGui::Spacing();
			ImGui::Checkbox("Start Calculator", &startCalc);
			ImGui::Spacing();
			ImGui::Text("using imgui ver %s %d", IMGUI_VERSION, IMGUI_VERSION_NUM);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
			ImGui::Spacing();
			if (startCalc) {
				RenderMain(workPosx, workPosy);
			}
		}
		ImGui::End();
		return;
	}
}
