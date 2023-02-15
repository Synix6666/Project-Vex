#pragma once

#include "../Directories/ImGui/imgui_internal.h"
#include "../Directories/ImGui/imgui.h"

#include <Windows.h>
#include <vector>
#include <iostream>


#include "gui.hpp"

using namespace std;
static bool Safemode = true;
static bool ShBypass = true;

namespace Config
{
	void Render2()
	{
		if (ImGui::Button("Sidebar"))
		{
			SettingsBool::zeroxmenu = true;
		}
	}
	void Render1()
	{
		ImGui::BeginChild("##LeftBlocker", ImVec2(ImGui::GetContentRegionAvail().x / 2, ImGui::GetContentRegionAvail().y - 14));
		{
			ImGui::Text("Visuals");

			ImGui::Checkbox("Enable ESP", &SettingsBool::Esp);

			ImGui::Checkbox("Box ESP", &SettingsBool::BoxEnable);

			ImGui::Checkbox("Skeleton ESP", &SettingsBool::skeletonesp);

			ImGui::Checkbox("Health ESP", &SettingsBool::HealthBarEsp);

			ImGui::Checkbox("Distance ESP", &SettingsBool::DistanceEsp);

			ImGui::Checkbox("Ignore Self", &SettingsBool::ignoreselfEsp);

		}

		ImGui::EndChild();


		ImGui::SameLine();
		ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0));
		ImGui::BeginChild("##Blocker", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y - 14));
		{
			ImGui::Text("Aimbot");
			ImGui::Checkbox("Aimbot", &SettingsBool::mouseaim);
			ImGui::Checkbox("Draw FOV", &SettingsBool::fovenabled);
			if (SettingsBool::fovenabled)
			{
				ImGui::SliderFloat("Size", &SettingsBool::fov, 1.00, 700.00);

			}

			ImGui::SliderFloat("Smoothing", &SettingsBool::smooth, 1.00, 100.00);
			ImGui::Combo("Target", &selectedaim, aimtype, IM_ARRAYSIZE(aimtype));


		}
		ImGui::EndChild();
		ImGui::PopStyleColor();
		ImGui::End();
	}


	void Render()
	{
	


		ImGui::BeginChild("##LeftBlocker", ImVec2(ImGui::GetContentRegionAvail().x / 2, ImGui::GetContentRegionAvail().y - 14));
		{
			ImGui::Checkbox("Godmode", &godmode2);
			ImGui::Checkbox("Invisile", &invisible);
			ImGui::Checkbox("NoClip", &nclip);
			if (ImGui::Checkbox("Tiny Player", &betiny)) { TinyPlayer(betiny); }
			if (ImGui::Button("Sucide")) { ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), 0); }
			if (ImGui::Button("Alpha Player 50%")) {
				ENTITY::SET_ENTITY_ALPHA(PLAYER::PLAYER_PED_ID(), 50, false);
			}
			if (ImGui::Button("New Look")) {
				PED::SET_PED_RANDOM_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), true);
			}
			if (ImGui::Button("Clean Ped")) {
				int Ped = PLAYER::PLAYER_PED_ID(); PED::CLEAR_PED_BLOOD_DAMAGE(Ped); PED::RESET_PED_VISIBLE_DAMAGE(Ped);
			}
			if (ImGui::Button("Teleport To Waypoint")) {
				int WaypointHandle = UI::GET_FIRST_BLIP_INFO_ID(8);
				if (UI::DOES_BLIP_EXIST(WaypointHandle))
				{
					Vector3 WaypointPos = UI::GET_BLIP_COORDS(WaypointHandle);
					int Handle = PLAYER::PLAYER_PED_ID();
					if (PED::IS_PED_IN_ANY_VEHICLE(Handle, 0))
						Handle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
					ENTITY::SET_ENTITY_COORDS(Handle, WaypointPos.x, WaypointPos.y, WaypointPos.z + 25.0f, 0, 0, 0, 1);
				}
			}
		}

		ImGui::EndChild();


		ImGui::SameLine();
		ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0));
		ImGui::BeginChild("##Blocker", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y - 14));
		{
			ImGui::Checkbox("Unlimited Ammo", &ammo2);
			ImGui::Checkbox("Rapid Fire", &rpdfr);
			ImGui::Checkbox("No Recoil", &SettingsBool::norecoil);
			ImGui::Checkbox("No Spread", &SettingsBool::nospread);
			if (ImGui::Button("Give All Weapon")) {

				uint Weapons[] = { 0x99B507EA, 0x678B81B1, 0x4E875F73, 0x958A4A8F, 0x440E4788, 0x84BD7BFD, 0x1B06D571, 0x5EF9FEC4, 0x22D8FE39, 0x99AEEB3B, 0x13532244, 0x2BE6766B, 0xEFE7E2DF, 0xBFEFFF6D, 0x83BF0278, 0xAF113F99, 0x9D07F764, 0x7FD62962, 0x1D073A89, 0x7846A318, 0xE284C527, 0x9D61E50F, 0x3656C8C1, 0x05FC3C11, 0x0C472FE2, 0x33058E22, 0xA284510B, 0x4DD2DC56, 0xB1CA77B1, 0x687652CE, 0x42BF8A85, 0x93E220BD, 0x2C3731D9, 0xFDBC8A50, 0x24B17070, 0x060EC506, 0x34A67B97, 0xFDBADCED, 0x23C9F95C, 0x497FACC3, 0xF9E6AA4B, 0x61012683, 0xC0A3098D, 0xD205520E, 0xBFD21232, 0x7F229F94, 0x92A27487, 0x083839C4, 0x7F7497E5, 0xA89CB99E, 0x3AABBBAA, 0xC734385A, 0x787F0BB, 0x47757124, 0xD04C944D };
				for (int i = 0; i < (sizeof(Weapons) / 4); i++) {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), Weapons[i], 5000, 1);
				}
			}
			if (ImGui::CollapsingHeader("Weapons"))
			{

				if (ImGui::Button("Give Tazer")) {

					int player = NativeInvoke::Invoke<0xD80958FC74E988A6, int>();
					NativeInvoke::Invoke<0xBF0FD6E56C964FCB, bool>(player, NativeInvoke::Invoke<0xC4D88A85, int>(player), 0x3656C8C1, true);

					NativeInvoke::Invoke<0x78F0424C34306220, bool>(player, NativeInvoke::Invoke<0x7F0580C7, int>(player), 0x3656C8C1);
				}
				if (ImGui::Button("Give AP Pistol")) {

					int player = NativeInvoke::Invoke<0xD80958FC74E988A6, int>();
					NativeInvoke::Invoke<0xBF0FD6E56C964FCB, bool>(player, NativeInvoke::Invoke<0xC4D88A85, int>(player), 0x22D8FE39, 100, true);

					NativeInvoke::Invoke<0x78F0424C34306220, bool>(player, NativeInvoke::Invoke<0x7F0580C7, int>(player), 0x22D8FE39);
				}
				if (ImGui::Button("Give Battle Axe")) {

					int player = NativeInvoke::Invoke<0xD80958FC74E988A6, int>();
					NativeInvoke::Invoke<0xBF0FD6E56C964FCB, bool>(player, NativeInvoke::Invoke<0xC4D88A85, int>(player), 0xCD274149, 100, true);

					NativeInvoke::Invoke<0x78F0424C34306220, bool>(player, NativeInvoke::Invoke<0x7F0580C7, int>(player), 0xCD274149);
				}
				if (ImGui::Button("Give Rocket Launcher")) {

					int player = NativeInvoke::Invoke<0xD80958FC74E988A6, int>();
					NativeInvoke::Invoke<0xBF0FD6E56C964FCB, bool>(player, NativeInvoke::Invoke<0xC4D88A85, int>(player), 0xB1CA77B1, 1000, true);

					NativeInvoke::Invoke<0x78F0424C34306220, bool>(player, NativeInvoke::Invoke<0x7F0580C7, int>(player), 0xB1CA77B1, 10);
				}

				if (ImGui::Button("Give Pistol")) {

					int player = NativeInvoke::Invoke<0xD80958FC74E988A6, int>();
					NativeInvoke::Invoke<0xBF0FD6E56C964FCB, bool>(player, NativeInvoke::Invoke<0xC4D88A85, int>(player), 0x1B06D571, 1000);

					NativeInvoke::Invoke<0x78F0424C34306220, bool>(player, NativeInvoke::Invoke<0x7F0580C7, int>(player), 0x1B06D571, 200);
				}
				if (ImGui::Button("Give Combat Pistol")) {

					int player = NativeInvoke::Invoke<0xD80958FC74E988A6, int>();
					NativeInvoke::Invoke<0xBF0FD6E56C964FCB, bool>(player, NativeInvoke::Invoke<0xC4D88A85, int>(player), 0x5EF9FEC4, 200);

					NativeInvoke::Invoke<0x78F0424C34306220, bool>(player, NativeInvoke::Invoke<0x7F0580C7, int>(player), 0x5EF9FEC4, 200);
				}
				if (ImGui::Button("Give Minigun")) {

					int player = NativeInvoke::Invoke<0xD80958FC74E988A6, int>();
					NativeInvoke::Invoke<0xBF0FD6E56C964FCB, bool>(player, NativeInvoke::Invoke<0xC4D88A85, int>(player), 0x2F36B434, 200);

					NativeInvoke::Invoke<0x78F0424C34306220, bool>(player, NativeInvoke::Invoke<0x7F0580C7, int>(player), 0x2F36B434, 200);
				}
				if (ImGui::Button("Give Ammo rifle")) {

					int player = NativeInvoke::Invoke<0xD80958FC74E988A6, int>();
					NativeInvoke::Invoke<0xBF0FD6E56C964FCB, bool>(player, NativeInvoke::Invoke<0xC4D88A85, int>(player), 0xE4BD2FC6, 200);

					NativeInvoke::Invoke<0x78F0424C34306220, bool>(player, NativeInvoke::Invoke<0x7F0580C7, int>(player), 0xE4BD2FC6, 200);
				}
				if (ImGui::Button("Give Flare Gun")) {

					int player = NativeInvoke::Invoke<0xD80958FC74E988A6, int>();
					NativeInvoke::Invoke<0xBF0FD6E56C964FCB, bool>(player, NativeInvoke::Invoke<0xC4D88A85, int>(player), 0xE013E01C, 200);

					NativeInvoke::Invoke<0x78F0424C34306220, bool>(player, NativeInvoke::Invoke<0x7F0580C7, int>(player), 0xE013E01C, 200);
				}
				if (ImGui::Button("Give Mollotov")) {

					int player = NativeInvoke::Invoke<0xD80958FC74E988A6, int>();
					NativeInvoke::Invoke<0xBF0FD6E56C964FCB, bool>(player, NativeInvoke::Invoke<0xC4D88A85, int>(player), 0x84D676D4, 200);

					NativeInvoke::Invoke<0x78F0424C34306220, bool>(player, NativeInvoke::Invoke<0x7F0580C7, int>(player), 0x84D676D4, 200);
				}
				if (ImGui::Button("Give Knife")) {

					int player = NativeInvoke::Invoke<0xD80958FC74E988A6, int>();
					NativeInvoke::Invoke<0xBF0FD6E56C964FCB, bool>(player, NativeInvoke::Invoke<0xC4D88A85, int>(player), 0x99B507EA);

					NativeInvoke::Invoke<0x78F0424C34306220, bool>(player, NativeInvoke::Invoke<0x7F0580C7, int>(player), 0x99B507EA);
				}
				if (ImGui::Button("Give Switch Blade")) {

					int player = NativeInvoke::Invoke<0xD80958FC74E988A6, int>();
					NativeInvoke::Invoke<0xBF0FD6E56C964FCB, bool>(player, NativeInvoke::Invoke<0xC4D88A85, int>(player), 0xDFE37640);

					NativeInvoke::Invoke<0x78F0424C34306220, bool>(player, NativeInvoke::Invoke<0x7F0580C7, int>(player), 0xDFE37640);
				}
			}


		}
		ImGui::EndChild();
		ImGui::PopStyleColor();

	}
}