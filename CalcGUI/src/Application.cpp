#include "Application.h"
#include "imgui.h"
#include <cstring>
#include <iostream>

namespace MyGUI {
	static bool startCalc = false;

	void RenderMain(float workPosx, float workPosy, ImGuiIO& io) {

		// Calculator window dimensions
		//ImFont* titleFont = io.Fonts->AddFontFromFileTTF("..\\CalcGUI\\misc\\fonts\\RedditMono-VariableFont_wght.ttf", 18.0f); // Title font
		//ImFont* bodyFont = io.Fonts->AddFontFromFileTTF("..\\CalcGUI\\misc\\fonts\\RedditMono-VariableFont_wght.ttf", 36.0f); // Body font
		//ImGui::PushFont(titleFont); // Push title font to use
		// TODO: Figure out how to change font locally 

		ImGui::SetNextWindowPos(ImVec2((workPosx + 1280-500), (workPosy + 50)), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(424, 632), ImGuiCond_Always); // W,H

		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoMove;
		windowFlags |= ImGuiWindowFlags_NoCollapse;
		windowFlags |= ImGuiWindowFlags_NoResize;

		// Make calculator window
		if (ImGui::Begin("Calculator", &startCalc, windowFlags)) {
			//ImGui::PopFont(); // Pop title font
			//ImGui::PushFont(bodyFont); // Use body font

			// Tool tip - Calculator description
			ImGui::TextDisabled("(?)");
			if (ImGui::IsItemHovered()) {
				ImGui::BeginTooltip();
				ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
				ImGui::TextUnformatted("This is the beginning of the calculator app.");
				ImGui::PopTextWrapPos();
				ImGui::EndTooltip();
			}

			// Calculator input box
			static char input[55] = "";
			ImGuiWindowFlags inputFlags = ImGuiInputTextFlags_ReadOnly;
			inputFlags |= ImGuiInputTextFlags_NoUndoRedo;

			ImGui::InputTextMultiline("##Input", input, IM_ARRAYSIZE(input), ImVec2(408, 100), inputFlags);
			ImGui::Spacing();

			ImGui::BeginDisabled(strlen(input) == 54); // Disable buttons after max chars.

			// LAYOUT TO USE:
			/*const char* buttons[6][4] = {
				{"cos","sin", "tan","del"},
				{"pow","sqr","sqrt","/"  },
				{"7",  "8",  "9",   "*"	 },
				{"4",  "5",  "6",   "-"	 },
				{"1",  "2",  "3",   "+"	 },
				{"0",  ".",  "(-)", "="	 }
			};*/
			
			// Digits (GUI Template)
			if (ImGui::Button("7", ImVec2(96,80))) strcat_s(input, "7"); ImGui::SameLine();
			if (ImGui::Button("8", ImVec2(96,80))) strcat_s(input, "8"); ImGui::SameLine();
			if (ImGui::Button("9", ImVec2(96,80))) strcat_s(input, "9"); ImGui::SameLine();
			if (ImGui::Button("Del", ImVec2(96, 80)))

			ImGui::Spacing();
			ImGui::Spacing();

			if (ImGui::Button("4", ImVec2(96,80))) strcat_s(input, "4"); ImGui::SameLine();
			if (ImGui::Button("5", ImVec2(96,80))) strcat_s(input, "5"); ImGui::SameLine();
			if (ImGui::Button("6", ImVec2(96,80))) strcat_s(input, "6"); ImGui::SameLine();

			ImGui::Spacing();
			ImGui::Spacing();

			if (ImGui::Button("1", ImVec2(96,80))) strcat_s(input, "1"); ImGui::SameLine();
			if (ImGui::Button("2", ImVec2(96,80))) strcat_s(input, "2"); ImGui::SameLine();
			if (ImGui::Button("3", ImVec2(96,80))) strcat_s(input, "3"); ImGui::SameLine();

			ImGui::EndDisabled();

		}
		ImGui::End();
		return;
	}
	
	void RenderInfo(float workPosx, float workPosy, ImGuiIO& io) {

		// Information window dimensions
		ImGui::SetNextWindowPos(ImVec2((workPosx + 20), (workPosy + 30)), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(350, 150), ImGuiCond_Always);

		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoResize;

		// Make info window
		if (ImGui::Begin("Information"), nullptr, windowFlags) {
			ImGui::Text("Welcome to my Calculator!");
			ImGui::Spacing();
			ImGui::Text("using imgui ver %s %d", IMGUI_VERSION, IMGUI_VERSION_NUM);
			ImGui::Spacing();
			ImGui::Checkbox("Start Calculator", &startCalc);
			if (startCalc) {
				RenderMain(workPosx, workPosy, io);
			}
		}
		ImGui::End();
		return;
	}
}
