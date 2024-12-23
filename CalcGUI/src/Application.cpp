﻿#include "Application.h"

namespace MyGUI {
	// Window Flags
	static bool show_app_calculator = false;
	static bool show_window_mode = false;
	static bool show_window_history = false;
	static bool show_window_about = false;

	// For calculator logic (class)
	static Calculator calc;
	static char calculate_exp[256] = ""; // Current expression to calculate

	static size_t str_size = 256;
	static char* history_exp = new char[str_size]();

	// for the calculator input/answer box
	static char input[256] = "0"; // Used for displaying the answer and the number to be used as input operands.

	// for the calculator expression box - Displays the current expression that the user inputs.
	static char display_exp[256] = ""; // Expression to display

	static char equation_exp[256] = ""; // Contains the entire equation that was calculated.
	static bool firstClear = true;
	static bool firstCalc = false;
	static bool equalPress = false;
	static bool isDouble = false;


	static void ShowHistoryWindow(bool* p_open) 
	{
		// Logic for displaying calculation history
		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_HorizontalScrollbar;
		windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
		windowFlags |= ImGuiWindowFlags_NoCollapse;
		windowFlags |= ImGuiWindowFlags_NoResize;

		if (!ImGui::Begin("History", p_open, windowFlags)) 
		{
			ImGui::End();
			return;
		}
		if (ImGui::Button("Clear History")) history_exp[0] = '\0';
		ImGui::Text(history_exp);
		ImGui::End();
	}

	static void ShowAboutWindow(bool* p_open) 
	{
		// Logic for showing the about window - details about the application
		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_AlwaysAutoResize;
		windowFlags |= ImGuiWindowFlags_NoCollapse;
		if (!ImGui::Begin("About", p_open, windowFlags)) 
		{
			ImGui::End();
			return;
		}
		ImGui::Text("Dear ImGui %s (%d), DirectX11 Backend", IMGUI_VERSION, IMGUI_VERSION_NUM);
		ImGui::Text("By Omar Cornut and all Dear ImGui contributors.");
		ImGui::Text("Dear ImGui is licensed under the MIT License, see LICENSE for more information.");
		ImGui::Separator();
		ImGui::Text("Thank you for using my simple calculator.");
		ImGui::Text("Please check out the Dear ImGui repo for more information about the framework.");
		ImGui::Text("- Kevin Tu");
		ImGui::End();
	}

	void GrowString(char* (&str)) 
	{
		size_t new_size = str_size * 2;
		char* newStr = new char[new_size];
		for (size_t i = 0; i < strlen(str); ++i) newStr[i] = str[i];
		newStr[strlen(str)] = '\0';
		delete[] str;
		str = newStr;
		str_size = new_size;
	}

	void clear_inputs() 
	{
		calc.clr();
		display_exp[0] = '\0';
		equation_exp[0] = '\0';
		strcpy_s(input, "0");
		firstClear = true;
		firstCalc = false;
		equalPress = false;
		isDouble = false;
	}

	void RenderMain(float workPosx, float workPosy) 
	{

		// For styling
		ImGuiStyle& style = ImGui::GetStyle();

		ImGui::SetNextWindowPos(ImVec2((workPosx + 1280 - 500), (workPosy + 50)), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(424, 715), ImGuiCond_Always); // W,H

		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse;
		windowFlags |= ImGuiWindowFlags_AlwaysAutoResize;
		windowFlags |= ImGuiWindowFlags_NoScrollbar;
		windowFlags |= ImGuiWindowFlags_NoScrollWithMouse;
		windowFlags |= ImGuiWindowFlags_MenuBar;

		// Make calculator window
		if (ImGui::Begin("Calculator", &show_app_calculator, windowFlags)) 
		{

			{ // Settings menu bar
				if (ImGui::BeginMenuBar()) 
				{
					if (ImGui::BeginMenu("Settings")) 
					{

						if (ImGui::BeginMenu("Mode")) 
						{
							ImGui::TextDisabled("(?)");
							if (ImGui::IsItemHovered()) 
							{
								ImGui::BeginTooltip();
								ImGui::TextUnformatted("DEFAULTS:");
								ImGui::BulletText("Floating Point: 12 decimal places");
								ImGui::BulletText("Trigonometry Angle: radians");
								ImGui::EndTooltip();
							}

							// Logic for floating point precision
							ImGui::Text("Set Float Precision");
							static int x1 = 12;
							ImGui::SliderInt("##Float", &x1, 0, 12);
							calc.set_precision(x1);
							ImGui::Separator();

							// Logic for trigonometry settings
							if (ImGui::TreeNode("Trigonometry")) 
							{
								static int selected = -1;
								static const char* modes[2] = { "Degrees", "Radians" };
								for (int n = 0; n < 2; ++n) 
								{
									if (ImGui::Selectable(modes[n], selected == n)) 
									{
										selected = n;
										calc.set_trig(selected);
									}
								}
								// Toggles radians or degrees.
								ImGui::TreePop();
							}

							ImGui::EndMenu();
						}

						ImGui::MenuItem("History", NULL, &show_window_history);
						ImGui::MenuItem("About", "(?)", &show_window_about);
						ImGui::EndMenu();
					}
					ImGui::EndMenuBar();
				}
				if (show_window_history) 
				{
					ImGui::SetNextWindowPos(ImVec2((workPosx + 458), (workPosy + 50)), ImGuiCond_Always);
					ImGui::SetNextWindowSize(ImVec2(324, 715), ImGuiCond_Always);
					ShowHistoryWindow(&show_window_history);
				}
				if (show_window_about) ShowAboutWindow(&show_window_about);
			}

			// Math expression display variables - Displays current operations.
			ImGuiWindowFlags inputFlags = ImGuiInputTextFlags_ReadOnly;
			inputFlags |= ImGuiInputTextFlags_NoUndoRedo;
			ImGui::InputTextMultiline("##Operation", display_exp, IM_ARRAYSIZE(display_exp), ImVec2(408, 20), inputFlags);

			// Calculator input/answer box
			ImGui::InputTextMultiline("##Input", input, IM_ARRAYSIZE(input), ImVec2(408, 100), inputFlags);

			ImGui::Spacing();

			ImGui::BeginDisabled(strlen(input) >= 54);

			if (strlen(input) >= 54) 
			{
				calc.clr();
				display_exp[0] = '\0';
				strcpy_s(input, "Overflow!");
				firstClear = true;
			}

			// CALCULATOR LAYOUT:
			const char* buttons[6][4] = 
			{
				{"sqr","sqrt","Del","Clr" },
				{"sin","cos","tan", "/"   },
				{"7",  "8",  "9",   "*"	  },
				{"4",  "5",  "6",   "-"	  },
				{"1",  "2",  "3",   "+"	  },
				{"0",  ".",  "(-)", "="	  }
			};

			// Load buttons
			for (int row = 0; row < 6; ++row) 
			{
				for (int col = 0; col < 4; ++col) 
				{
					{ // Specifies shading depending on buttons/operations
						if (row == 0 || row == 1 || col == 3) 
						{
							// Row/Col specific highlighting
							style.Colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.60f);
							style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);

							if (buttons[row][col] == "=") 
							{
								// Highlight "=" button
								style.Colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.85f);
								style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
							}
						}
						else 
						{
							style.Colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
							style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.60f);
						}
					}
					// Primary logic for calculator buttons
					if (ImGui::Button(buttons[row][col], ImVec2(96, 80))) 
					{
						// Clears current screen to allow next input upon pressing equals sign.
						if (equalPress) clear_inputs();

						if (buttons[row][col] == "(-)") 
						{
							char buffer[256];
							double temp_input = atof(input);
							temp_input *= -1;
							if (isDouble) 
							{
								snprintf(buffer, sizeof(buffer), "%.*f", calc.get_precision(), temp_input);
							}
							else 
							{
								snprintf(buffer, sizeof(buffer), "%.0f", temp_input);
							}
							strcpy_s(input, buffer);

						}
						else if (row >= 1 && col == 3 || row == 1 && col <= 2) 
						{
							// Operator buttons & Trig functions - Need to execute calculation immediately after 2nd operand is inputted

							// For displaying only
							// TODO: Refactor this section of code (disgusting ew).
							if (buttons[row][col] == "=" && !equalPress) 
							{
								strcat_s(display_exp, input);
								strcat_s(display_exp, buttons[row][col]);
								strcpy_s(calculate_exp, input);
								strcat_s(calculate_exp, buttons[row][col]);
								strcpy_s(input, calc.parse(calculate_exp));
								calc.calculated = false;
								equalPress = true;

							}
							else if (!calc.calculated && !equalPress) 
							{
								strcpy_s(equation_exp, display_exp);
								strcat_s(equation_exp, input); // Used for history
								if (row == 1 && col <= 2) 
								{
									// Specific to trig functions - Need to immediately calculate trig_func(current_input)
									calc.trig = true;

									// Expressions to display logic below need to be changed so it displays sin(75)= for example.
									strcat_s(display_exp, buttons[row][col]);
									strcat_s(display_exp, "(");
									strcat_s(display_exp, input);
									strcat_s(display_exp, ")");

									strcpy_s(calculate_exp, input);
									strcat_s(calculate_exp, buttons[row][col]);
									strcpy_s(input, calc.parse(calculate_exp));

								}
								else 
								{
									strcpy_s(display_exp, input);
									strcat_s(display_exp, buttons[row][col]);
									strcpy_s(calculate_exp, input);
									strcat_s(calculate_exp, buttons[row][col]);
									strcpy_s(input, calc.parse(calculate_exp));
								}

							}

							if (calc.calculated) 
							{
								calc.get_results(display_exp);
								strcat_s(equation_exp, "=");
								strcat_s(equation_exp, display_exp);
								strcat_s(display_exp, buttons[row][col]);
								strcpy_s(calculate_exp, display_exp);
								calc.calculated = false;

								if ((strlen(equation_exp) + strlen(history_exp) + 1) >= str_size - 1) GrowString(history_exp);
								strcat_s(history_exp, str_size, equation_exp);
								strcat_s(history_exp, str_size, "\n");
								equation_exp[0] = '\0';
							}

							size_t histsize = strlen(history_exp);
							size_t displaysize = strlen(display_exp);
							size_t inputsize = strlen(input);
							if ((histsize + displaysize + inputsize + 1) >= str_size - 1) GrowString(history_exp);

							// Used to reset upon next input
							if (buttons[row][col] == "=") 
							{
								calc.clr();
								strcat_s(history_exp, str_size, display_exp); // Concatenate expression e.g, 7*3=
								strcat_s(history_exp, str_size, input); // Concatenate answer e.g, 7*3=21
								strcat_s(history_exp, str_size, "\n");
							}
							firstClear = true;

						}
						else if (firstClear && buttons[row][col] != "Clr") 
						{
							firstClear = false;
							strcpy_s(input, "");
							strcat_s(input, buttons[row][col]);

						}
						else if (buttons[row][col] == "Del") 
						{
							calc.del(input);

						}
						else if (buttons[row][col] == "Clr") 
						{
							clear_inputs();

						}
						else if (buttons[row][col] == "." && !isDouble) 
						{
							// Concatenate decimal point only once.
							isDouble = true;
							strcat_s(input, buttons[row][col]);

						}
						else if (row == 1 && col <= 2) 
						{
							// These are the trig function buttons
							double tempInput = atof(input);
							/*calc.trig(buttons[row][col], tempInput);*/
						}
						else 
						{
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

	void RenderInfo(float workPosx, float workPosy, ImGuiIO& io) 
	{
		// Global window dimensions

		// Information window dimensions
		ImGui::SetNextWindowPos(ImVec2((workPosx + 20), (workPosy + 30)), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(360, 140), ImGuiCond_Always);

		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoResize;

		// Make info window
		if (ImGui::Begin("Information"), nullptr, windowFlags) 
		{
			ImGui::Text("Welcome to my Calculator");
			ImGui::Spacing();
			ImGui::Checkbox("Start Calculator", &show_app_calculator);
			ImGui::Spacing();
			ImGui::Text("using imgui ver %s %d DirectX11", IMGUI_VERSION, IMGUI_VERSION_NUM);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
			ImGui::Spacing();
		}

		if (show_app_calculator) RenderMain(workPosx, workPosy);

		ImGui::End();
		return;
	}
}