#include "Application.h"
#include "imgui.h"
#include <cstring>

namespace MyGUI {
	static bool startCalc = false;

	void RenderMain(float workPosx, float workPosy) {

		// Calculator window dimensions
		ImGui::SetNextWindowPos(ImVec2((workPosx + 1280-500), (workPosy + 50)), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(400, 650), ImGuiCond_FirstUseEver); // W,H

		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoMove;
		windowFlags |= ImGuiWindowFlags_NoCollapse;
		windowFlags |= ImGuiWindowFlags_NoResize;

		// Make calculator window
		if (ImGui::Begin("Calculator", &startCalc, windowFlags)) {

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
			static char input[256] = "";
			ImGuiWindowFlags inputFlags = ImGuiInputTextFlags_ReadOnly;
			inputFlags |= ImGuiInputTextFlags_NoUndoRedo;

			ImGui::InputTextMultiline("##Input", input, IM_ARRAYSIZE(input), ImVec2(385, 100), inputFlags);
			//if (sizeof(input) == 54) strcat_s(input, "\n"); TODO: Fix new line problem after 54 characters!
			if (ImGui::Button("7", ImVec2(100,80))) strcat_s(input, "7"); ImGui::SameLine();
			if (ImGui::Button("8", ImVec2(100,80))) strcat_s(input, "8"); ImGui::SameLine();
			if (ImGui::Button("9", ImVec2(100,80))) strcat_s(input, "9"); ImGui::SameLine();
		}
		ImGui::End();
		return;
	}
	
	void RenderInfo(float workPosx, float workPosy) {

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
				RenderMain(workPosx, workPosy);
			}
		}
		ImGui::End();
		return;
	}
}
