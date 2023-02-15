#pragma once

#include "../Directories/ImGui/imgui.h"
#include "../Directories/ImGui/imgui_internal.h"



#include <Windows.h>
#include <iostream>
#include <vector>

namespace Gui
{
	void Seperator(const std::string id, float width = ImGui::GetContentRegionAvail().x, float height = 1, bool visible = true)
	{
		ImGui::BeginChild(id.c_str(), ImVec2(width, height), visible);
		ImGui::EndChild();
	}

	void SetGetPosX(float value)
	{
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + value);
	}

	void SetGetPosY(float value)
	{
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + value);
	}

	void SetPosX(float value)
	{
		ImGui::SetCursorPosX(value);
	}

	void SetPosY(float value)
	{
		ImGui::SetCursorPosY(value);
	}
}