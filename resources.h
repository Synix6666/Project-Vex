#pragma once

#include <direct.h> //mkdir

#include "../Directories/ImGui/imgui.h"
#include "../Directories/ImGui/imgui_internal.h"

#include <Windows.h>
#include <iostream>
#include <vector>
#include <fstream>

#include "exec.h"

#include "TextEditor.h"
#include "gui.hpp"
#include "fontawesome.h"

TextEditor dumper;

static int ResourceTab = 0;
static bool ShowResources = false;
static char Buffer[256] = "";

std::vector<const char*> BlockedEvents = {};
static int SelectedEvent = NULL;

std::vector<const char*> Triggers = {
	"TriggerServerEvent('esx_truckerjob:pay', 1000000)",
	"TriggerServerEvent('esx_slotmachine:sv:2', 100000)",
	"TriggerEvent('esx:spawnVehicle', \"fmj\")",
	"TriggerServerEvent('esx_vehicleshop:putStockItems', \"bread\",-100)",
	"TriggerEvent('esx:teleport', {x= 100.0, y= 1200.0, z= 20.0})",
	"TriggerEvent('esx_ambulancejob:revive')",
	"TriggerServerEvent('esx_property:buyProperty', \"LowEndApartment\")",
	"TriggerServerEvent('AdminMenu:giveDirtyMoney', 500000)",
	"TriggerServerEvent('AdminMenu:giveBank', 10000)",
	"TriggerServerEvent('AdminMenu:giveCash', 60000)",
	"TriggerEvent('esx_skin:openSaveableMenu')",
	"TriggerServerEvent('NB:recruterplayer', PLAYER_ID, \"mecano\", 0)",
	"TriggerServerEvent('esx_billing:sendBill', PLAYER_ID, \"Purposeless\", \"Payday\", 100)",
	"TriggerServerEvent('esx_policejob:handcuff', playerId)",
	"TriggerServerEvent('esx_drugs:startHarvestCoke')",
	"TriggerServerEvent('esx_weashop:buyItem', \"WEAPON_MACHETE\", 0, \"BlackWeashop\")",
	"TriggerServerEvent('lscustoms:payGarage', amount)",
	"TriggerServerEvent('taxi:success',pay)"
};

std::string ResourceMetaData =
R"(

fx_version 'cerulean'
games { 'gta5' }

version '1.0.0'

client_scripts {
    'client.lua',
}
server_script 'server.lua'

)";

void CopyToClipBoard(HWND hwnd, const std::string& s) {
	OpenClipboard(hwnd);
	EmptyClipboard();
	HGLOBAL hGlobe = GlobalAlloc(GMEM_MOVEABLE, s.size() + 1);
	if (!hGlobe) {
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hGlobe), s.c_str(), s.size() + 1);
	GlobalUnlock(hGlobe);
	SetClipboardData(CF_TEXT, hGlobe);
	CloseClipboard();
	GlobalFree(hGlobe);
}

namespace Resources
{
	void SaveResources()
	{
		//ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.3, 0));
		if (ImGui::Button("Save All Resources", ImVec2(ImGui::GetContentRegionAvailWidth(), 33)))
		{
			MessageBoxA(NULL, "Dump successfully saved to C:\\redENGINE\\Dumps\\127.0.0.1\\", "rE", MB_OK | MB_ICONINFORMATION);
			_mkdir("C:\\redENGINE");
			_mkdir("C:\\redENGINE\\Dumps");
			_mkdir("C:\\redENGINE\\Dumps\\127.0.0.1");

			std::ofstream file;
			try {
				file.open("C:\\redENGINE\\Dumps\\127.0.0.1\\__resource.lua");
				file << ResourceMetaData << std::endl;
				file.close();
			}
			catch (...)
			{
				MessageBoxA(NULL, "Failed to save resource metadata.", "rE", MB_OK | MB_ICONERROR);
			}

		}
		//ImGui::PopStyleVar();
	}

	void Render()
	{
		dumper.SetShowWhitespaces(false);
		dumper.SetReadOnly(true);
		dumper.SetPalette(TextEditor::GetDarkPalette());

		ImGui::SetCursorPosX(ImGui::GetContentRegionAvail().x / 1.3);
		ImGui::Text("Resources");
		Gui::Seperator("##resources_seperator_2");

		if (ImGui::Button(ICON_FA_FOLDER_OPEN" File Browser", ImVec2(ImGui::GetWindowWidth() / 4, 33)))
		{
			ResourceTab = 1;
		}
		ImGui::SameLine();
		if (ImGui::Button(ICON_FA_SEARCH_PLUS" Triggers", ImVec2(ImGui::GetWindowWidth() / 4, 33)))
		{
			ResourceTab = 2;
		}
		ImGui::SameLine();
		if (ImGui::Button(ICON_FA_TAGS" Stopper", ImVec2(ImGui::GetContentRegionAvail().x, 33)))
		{
			ResourceTab = 3;
		}


		Gui::Seperator("##resources_seperator_3");

		
		static ImGuiTextFilter filter;
		if (ResourceTab == 1)
		{
			ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(15, 15, 15, 255));
			ImGui::ListBoxHeader("##resourcebox", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetWindowSize().y - 160));

			for (fx::Resource* resource : Cheats::GetAllResources())
			{
				static std::vector<std::string> reso2urces =
				{
					resource->GetName().c_str()
				};
				current_resource = resource->GetName().c_str();
				string name = resource->GetName().c_str() + (string)" [" + Cheats::ResourceState(current_resource) + (string)"]";
				for (const auto& resource : reso2urces)
				{
					if (filter.PassFilter(resource.c_str()))
					{
						if (ImGui::CollapsingHeader(name.c_str(), selected_resource))
						{

							if (ImGui::Button("Stop resource"))
							{
								StopResource(current_resource);
							}
							ImGui::SameLine();
							if (ImGui::Button("Start resource"))
							{
								StartResource(current_resource);
							}

						}
					}

				}


			}

			ImGui::ListBoxFooter();
			ImGui::PopStyleColor();
			Gui::Seperator("##saveresourcesbutton");
			SaveResources();

		}
		else if (ResourceTab == 2) //Triggers
		{
			ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(15, 15, 15, 255));
			ImGui::ListBoxHeader("##Triggers", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetWindowSize().y - 160));
			for (int i = 0; i < Triggers.size(); i++)
			{
				ImGui::Text(Triggers[i]);
				ImGui::SameLine();
				if (ImGui::Button("Copy", ImVec2(55, 30)))
				{
					if (Triggers.at(i) == NULL)
					{
						MessageBoxA(NULL, "Choose a trigger to copy.", "rE", MB_OK | MB_ICONERROR);
						return;
					}
					else
					{
						CopyToClipBoard(FindWindowA(NULL, "FiveM"), Triggers.at(i));
					}

				}
			}
			ImGui::ListBoxFooter();
			ImGui::PopStyleColor();
			Gui::Seperator("##resources_seperator_4");
			SaveResources();
		}
		else if (ResourceTab == 3) //Stopper
		{
			

			
		}

	}
}