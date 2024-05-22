#include "Application.h"
#include "imgui.h"
#include <cstring>

namespace MyGUI {
	static bool startCalc = false;

	void RenderMain(float workPosx, float workPosy) {
		// Main calculator window
		ImGui::SetNextWindowPos(ImVec2((workPosx + 1280-500), (workPosy + 50)), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(400, 650), ImGuiCond_Always); // W,H

		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoMove;
		windowFlags |= ImGuiWindowFlags_NoCollapse;
		windowFlags |= ImGuiWindowFlags_NoResize;

		if (ImGui::Begin("Calculator", nullptr, windowFlags)) { // Beginning window
			ImGui::Text("Test");
		}
		ImGui::End();
		return;
	}
	
	void RenderInfo(float workPosx, float workPosy) {

		ImGui::SetNextWindowPos(ImVec2((workPosx + 20), (workPosy + 30)), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(350, 150), ImGuiCond_Always);

		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoResize;

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
