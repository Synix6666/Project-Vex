#pragma once
#include "customapi.h"
#include "bools.h"
#include "../Directories/ImGui/imgui.h"
#include "vector.h"
#include "bones.h"
#include "thing.h"
#include "special.hpp"



#include <Windows.h>
#include <iostream>



Renderer* renderer = new Renderer;
#define render renderer
uintptr_t GetClosestPlayer()
{
	uintptr_t ClosestPlayer = 0;
	float closestdist = FLT_MAX;
	float dist;

	uintptr_t ReplayInterfacePatternFixed = Read<uintptr_t>(replayptr + *(int*)(replayptr + 0x3) + 0x7);


	uintptr_t PedReplayInterface = Read<uintptr_t>(ReplayInterfacePatternFixed + 0x18);

	if (PedReplayInterface) {
		int MaxPeds = Read<int>(PedReplayInterface + 0x108);

		for (int i = 0; i < MaxPeds; i++) {
			uintptr_t PedList = Read<uintptr_t>(PedReplayInterface + 0x100);
			if (!PedList) continue;
			uintptr_t pCPed = Read<uintptr_t>(PedList + (i * 0x10));
			if (!pCPed) continue;

			if (pCPed == localplayer) continue;

			Vec3 EntPos = *(Vec3*)(pCPed + 0x90);


			float Health = Read<float>(pCPed + 0x280);

			if (Health < 0 || Health == 0) continue;

			ImVec2 Ent2DPos = WorldToScreen(EntPos);
			if (selectedaim == 1)
			{

				auto ped_type = Read<uint32_t>(pCPed + 0x10A8);
				ped_type = ped_type << 11 >> 25;


				if (ped_type != 2) {
					continue;
				}
			}
			if (selectedaim == 2)
			{
				auto ped_type = Read<uint32_t>(pCPed + 0x10A8);
				ped_type = ped_type << 11 >> 25;


				if (ped_type == 2) {
					continue;
				}
			}

			ImVec2 Head = GetBonePosW2S(pCPed, SKEL_Head);
			ImVec2 middle = render->GetWindowMiddle();
			dist = pythag(middle, Head);

			if (dist < closestdist)
			{
				closestdist = dist;
				ClosestPlayer = pCPed;
			}
		}
	}

	return ClosestPlayer;
}
void do_aimbot(uintptr_t entity) { // pretty buggy, needs playing around with sensitivity

	auto get_distance = [](double x1, double y1, double x2, double y2) {
		return sqrtf(pow(x2 - x1, 2.0) + pow(y2 - y1, 2.0));
	};

	auto bone_pos = GetBonePosW2S(entity, SKEL_Head);
    Vec3 bone_postest = GetBonePos(entity, SKEL_Head);

	if (SettingsBool::mouseaim)
	{
		float aimspeedon = SettingsBool::smooth + 1;
		ImVec2 screen = bone_pos;

		auto center_x = 1920 / 2;
		auto center_y = 1080 / 2;
		auto fov = get_distance(center_x, center_y, screen.x, screen.y);
		float TargetX = 0;
		float TargetY = 0;

		if (screen.x != 0) {
			if (screen.x > center_x) {
				TargetX = -(center_x - screen.x);
				TargetX /= aimspeedon;
				if (TargetX + center_x > center_x * 2) TargetX = 0;
			}

			if (screen.x < center_x) {
				TargetX = screen.x - center_x;
				TargetX /= aimspeedon;
				if (TargetX + center_x < 0) TargetX = 0;
			}
		}

		if (screen.y != 0) {
			if (screen.y > center_y) {
				TargetY = -(center_y - screen.y);
				TargetY /= aimspeedon;
				if (TargetY + center_y > center_y * 2) TargetY = 0;
			}

			if (screen.y < center_y) {
				TargetY = screen.y - center_y;
				TargetY /= aimspeedon;
				if (TargetY + center_y < 0) TargetY = 0;
			}
		}

	

		

		if (fov < SettingsBool::fov) 
		{

			if (SAFE_CALL(GetAsyncKeyState)(VK_RBUTTON) & 0x8000) {

				mouse_event(MOUSEEVENTF_MOVE, float(TargetX), float(TargetY / 1.2), 0, 0);


			}
		}
	}

	
}
void aimbottrick()
{
	if (SettingsBool::enableaimbot)
	{
		if (localplayer)
		{
			if (GetClosestPlayer())
			{

				do_aimbot(GetClosestPlayer());

			}
		}
	}

}