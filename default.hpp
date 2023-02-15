#pragma once

#include "../Directories/ImGui/imgui.h"
#include "../Directories/ImGui/imgui_internal.h"


#include <Windows.h>
#include <iostream>
#include <vector>

#include "gui.hpp"

namespace Default
{
	void Render()
	{
		ImGui::SetCursorPosX(ImGui::GetContentRegionAvail().x / 1.3);
		ImGui::Text("Default");
		Gui::Seperator("##default_seperator_1");
		ImGui::Text("No section has been selected. Click a button on the left navbar.");
	}
}