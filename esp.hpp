#pragma once
#include "customapi.h"
#include "bools.h"
#include "../Directories/ImGui/imgui.h"
#include "vector.h"
#include "bones.h"
#include "thing.h"


Renderer* renderer1 = new Renderer;
#define render1 renderer1 

auto DrawOutlinedText(ImFont* pFont, const std::string& text, const ImVec2& pos, float size, ImU32 color, bool center) -> VOID
{
	std::stringstream stream(text);
	std::string line;

	float y = 0.0f;
	int index = 0;

	while (std::getline(stream, line))
	{
		ImVec2 textSize = pFont->CalcTextSizeA(size, FLT_MAX, 0.0f, line.c_str());

		if (center)
		{
			ImGui::GetBackgroundDrawList()->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) + 1, (pos.y + textSize.y * index) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
			ImGui::GetBackgroundDrawList()->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) - 1, (pos.y + textSize.y * index) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
			ImGui::GetBackgroundDrawList()->AddText(pFont, size, ImVec2(pos.x - textSize.x / 2.0f, pos.y + textSize.y * index), ImGui::GetColorU32(color), line.c_str());
		}
		else
		{//
			ImGui::GetBackgroundDrawList()->AddText(pFont, size, ImVec2((pos.x) + 1, (pos.y + textSize.y * index) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
			ImGui::GetBackgroundDrawList()->AddText(pFont, size, ImVec2((pos.x) - 1, (pos.y + textSize.y * index) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
			ImGui::GetBackgroundDrawList()->AddText(pFont, size, ImVec2(pos.x, pos.y + textSize.y * index), ImGui::GetColorU32(color), line.c_str());
		}

		y = pos.y + textSize.y * (index + 1);
		index++;
	}
}
#include "wtypes.h"
#include <iostream>
using namespace std;

// Get the horizontal and vertical screen sizes in pixel
void GetDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	// The top left corner will have coordinates (0,0)
	// and the bottom right corner will have coordinates
	// (horizontal, vertical)
	horizontal = desktop.right;
	vertical = desktop.bottom;
}
void esptrick()
{
	if (SettingsBool::fovenabled)
	{
		int horizontal = 0;
		int vertical = 0;
		GetDesktopResolution(horizontal, vertical);
		ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(horizontal / 2, vertical / 2), SettingsBool::fov, IM_COL32(255, 255, 255, 255), 40.0f);
	}

	if (localplayer)
	{

		if (SettingsBool::Esp)
		{

			uintptr_t ReplayInterfacePatternFixed = Read<uint64_t>(replayptr + *(int*)(replayptr + 0x3) + 0x7);
			if (!ReplayInterfacePatternFixed) return;
			uintptr_t Pedrpin = Read<uint64_t>(ReplayInterfacePatternFixed + 0x18);
			if (Pedrpin)
			{
				int MaxPeds = Read<int>(Pedrpin + 0x108);

				for (int i = 0; i < MaxPeds; i++)
				{
					if (!Pedrpin) continue;
					uintptr_t PedList = Read<uint64_t>(Pedrpin + 0x100);
					if (!PedList) continue;
					uintptr_t CPed = Read<uint64_t>(PedList + (i * 0x10));
					//std::cout << i << std::endl;

					if (!CPed) continue;
					if (SettingsBool::ignoreselfEsp)
					{
						if (CPed == localplayer)
							continue;
					}

					if (SettingsBool::PedEsp == false)
					{

						auto ped_type = Read<uint32_t>(CPed + 0x10A8);
						ped_type = ped_type << 11 >> 25;

						if (ped_type != 2) {
							continue;
						}
					}

					float HealthPed = Read<float>(CPed + 0x280);

					if (HealthPed == 0)
					{
						continue;
					}
					//BYTE Entitytype = *(BYTE*)(CPed + 0xFD9);
					Vec3 EntPos = Read<Vec3>(CPed + 0x90);
					Vec3 LocPos = Read<Vec3>(localplayer + 0x90);

					Vec3 DistanceCalculation = (LocPos - EntPos);
					double Distance = sqrtf(DistanceCalculation.x * DistanceCalculation.x + DistanceCalculation.y * DistanceCalculation.y + DistanceCalculation.z * DistanceCalculation.z);
					if (Distance > SettingsBool::distancelimite)
					{
						continue;
					}


					float ArmorPed;

					auto draw = ImGui::GetBackgroundDrawList();





					using convert_type = std::codecvt_utf8<wchar_t>;
					std::wstring_convert<convert_type, wchar_t> converter;
					std::string texthealth;
					//std::string textarmor;
					texthealth = "[ " + std::to_string(static_cast<int>(HealthPed)) + "HP ]";
					//textarmor = "[ " + std::to_string(static_cast<int>(ArmorPed)) + "Armor ]";

					std::string distancestring = "[ Distance : " + std::to_string(static_cast<int>(Distance)) + " m ]";


					ImVec2 Ped2DPos = WorldToScreen(EntPos);
					ImVec2 LocPos2D = WorldToScreen(LocPos);

					ImVec2 Head = GetBonePosW2S(CPed, SKEL_Head);
					ImVec2 LeftFoot = GetBonePosW2S(CPed, SKEL_L_Foot);
					ImVec2 RightFoot = GetBonePosW2S(CPed, SKEL_R_Foot);
					ImVec2 Leftarm = GetBonePosW2S(CPed, MH_L_Elbow);
					ImVec2 Rightarm = GetBonePosW2S(CPed, MH_R_Elbow);
					ImColor ESPSkeleton = ImColor(71, 86, 200);


					float FootAdv = (LeftFoot.y + RightFoot.y) / 2;
					float height = fabs(Head.y - (FootAdv)) * 1.2;
					//	float width = (Rightarm.x - Leftarm.x);
					float width = height / 2.5;
					float font_size = 18;

					if (render1->OnScreen(Ped2DPos))
					{


						if (render1->OnScreen(Head))
						{
							if (render1->OnScreen(RightFoot))
							{
								if (render1->OnScreen(LeftFoot))
								{
									if (render1->OnScreen(Rightarm))
									{
										if (render1->OnScreen(Leftarm))
										{
											if (SettingsBool::BoxEnable)
											{
												//2D Filled
												if (selectedbox == 1)
												{
													draw->AddRectFilled(ImVec2(Ped2DPos.x - width / 1.5, Ped2DPos.y - height / 1.5), ImVec2(Ped2DPos.x + width / 2, Ped2DPos.y + height / 1.6), ImColor(0, 0, 0, 50), 1, 1);
													draw->AddRect(ImVec2(Ped2DPos.x - width / 1.5, Ped2DPos.y - height / 1.5), ImVec2(Ped2DPos.x + width / 2, Ped2DPos.y + height / 1.6), ImColor(5, 5, 5, 100), 1, 1,3);
													draw->AddRect(ImVec2(Ped2DPos.x - width / 1.5, Ped2DPos.y - height / 1.5), ImVec2(Ped2DPos.x + width / 2, Ped2DPos.y + height / 1.6), ImColor(0, 0, 0, 255), 1, 1, 1);
												}
												//2D 
												if (selectedbox == 0)
												{
													draw->AddRect(ImVec2(Ped2DPos.x - width / 1.5, Ped2DPos.y - height / 1.5), ImVec2(Ped2DPos.x + width / 2, Ped2DPos.y + height / 1.6), ImColor(6, 6, 6, 100), 1, 1, 3);
													draw->AddRect(ImVec2(Ped2DPos.x - width / 1.5, Ped2DPos.y - height / 1.5), ImVec2(Ped2DPos.x + width / 2, Ped2DPos.y + height / 1.6), ImColor(0, 0, 0, 255), 1, 1, 1);
												}
												//Corner 
												if (selectedbox == 2)
												{

												}
											}
											if (SettingsBool::skeletonesp)
											{
												ImVec2 Back = GetBonePosW2S(CPed, SKEL_Neck_1);

												ImVec2 LeftClavicle = GetBonePosW2S(CPed, SKEL_L_Clavicle);
												ImVec2 LeftElbow = GetBonePosW2S(CPed, MH_L_Elbow);
												ImVec2 LeftUpperArm = GetBonePosW2S(CPed, SKEL_L_UpperArm);
												ImVec2 LeftForearm = GetBonePosW2S(CPed, SKEL_L_Forearm);
												ImVec2 LeftHand = GetBonePosW2S(CPed, SKEL_L_Hand);

												ImVec2 RightClavicle = GetBonePosW2S(CPed, SKEL_R_Clavicle);
												ImVec2 RightElbow = GetBonePosW2S(CPed, MH_R_Elbow);
												ImVec2 RightUpperArm = GetBonePosW2S(CPed, SKEL_R_UpperArm);
												ImVec2 RightForearm = GetBonePosW2S(CPed, SKEL_R_Forearm);
												ImVec2 RightHand = GetBonePosW2S(CPed, SKEL_R_Hand);

												ImVec2 Pelvis = GetBonePosW2S(CPed, SKEL_Pelvis);

												ImVec2 LeftThigh = GetBonePosW2S(CPed, SKEL_L_Thigh);
												ImVec2 LeftCalf = GetBonePosW2S(CPed, SKEL_L_Calf);

												ImVec2 RightThigh = GetBonePosW2S(CPed, SKEL_R_Thigh);
												ImVec2 RightCalf = GetBonePosW2S(CPed, SKEL_R_Calf);

												// BACK / SPINE
												draw->AddLine(Head, Back, ESPSkeleton, 1);

												// LEFT ARM
												draw->AddLine(Back, LeftUpperArm, ESPSkeleton, 1);
												draw->AddLine(LeftUpperArm, LeftForearm, ESPSkeleton, 1);
												draw->AddLine(LeftForearm, LeftHand, ESPSkeleton, 1);

												// RIGHT ARM
												draw->AddLine(Back, RightUpperArm, ESPSkeleton, 1);
												draw->AddLine(RightUpperArm, RightForearm, ESPSkeleton, 1);
												draw->AddLine(RightForearm, RightHand, ESPSkeleton, 1);

												// SPINE
												draw->AddLine(Back, Pelvis, ESPSkeleton, 1);

												// LEFT LEG
												draw->AddLine(Pelvis, LeftThigh, ESPSkeleton, 1);
												draw->AddLine(LeftThigh, LeftCalf, ESPSkeleton, 1);
												draw->AddLine(LeftCalf, LeftFoot, ESPSkeleton, 1);

												// RIGHT LEG
												draw->AddLine(Pelvis, RightThigh, ESPSkeleton, 1);
												draw->AddLine(RightThigh, RightCalf, ESPSkeleton, 1);
												draw->AddLine(RightCalf, RightFoot, ESPSkeleton, 1);


											}
											if (SettingsBool::HealthBarEsp)
											{
												float HealthPercentage = height / 100 * (HealthPed - 100);
												float fixedhealth = HealthPed - 100;

												ImColor col;
												if (fixedhealth >= 75 && fixedhealth <= 100)
												{
													col = ImColor(81, 252, 141, 255);
												}
												else if (fixedhealth < 75 && fixedhealth > 50)
												{
													col = ImColor(191, 245, 64, 255);
												}
												else if (fixedhealth < 50 && fixedhealth > 25)
												{
													col = ImColor(221, 245, 64, 255);
												}
												else if (fixedhealth < 25 && fixedhealth > 0)
												{
													col = ImColor(245, 79, 64, 255);
												}

												render1->DrawHealthBar(ImVec2(Ped2DPos.x + (width / 1.87), Ped2DPos.y + height / 2), ImVec2(4, HealthPercentage), col);
												//render->DrawBox(ImVec2(Ped2DPos.x + (width / 1.865), Ped2DPos.y - height / 2), ImVec2(4, height), ImColor(40, 41, 40, 255), 1);
											}
											if (SettingsBool::DistanceEsp)
											{


												if (Distance <= 25)
												{
													DrawOutlinedText(ImGui::GetFont(), distancestring.c_str(), ImVec2((Ped2DPos.x - width / 2) + (width / 2 - font_size + (font_size / 2) + 20), Ped2DPos.y + height / 2), 14.0f, ImColor(255, 255, 255), true);
													DrawOutlinedText(ImGui::GetFont(), ICON_FA_LEAF"", ImVec2((Ped2DPos.x - width / 2) + (width / 2 - font_size + (font_size / 2) + 20), Ped2DPos.y + height / 2), 14.0f, ImColor(255, 255, 255), true);

												}
												else if (Distance <= 50 && Distance > 25)
												{
													DrawOutlinedText(ImGui::GetFont(), distancestring.c_str(), ImVec2((Ped2DPos.x - width / 2) + (width / 2 - font_size + (font_size / 2) + 20), Ped2DPos.y + height / 2), 12.0f, ImColor(255, 255, 255), true);
													DrawOutlinedText(ImGui::GetFont(), ICON_FA_LEAF"", ImVec2((Ped2DPos.x - width / 2) + (width / 2 - font_size + (font_size / 2) + 20), Ped2DPos.y + height / 2), 12.0f, ImColor(255, 255, 255), true);
												}
												else if (Distance <= 75 && Distance > 50)
												{
													DrawOutlinedText(ImGui::GetFont(), distancestring.c_str(), ImVec2((Ped2DPos.x - width / 2) + (width / 2 - font_size + (font_size / 2) + 20), Ped2DPos.y + height / 2), 10.0f, ImColor(255, 255, 255), true);
													DrawOutlinedText(ImGui::GetFont(), ICON_FA_LEAF"", ImVec2((Ped2DPos.x - width / 2) + (width / 2 - font_size + (font_size / 2) + 20), Ped2DPos.y + height / 2), 10.0f, ImColor(255, 255, 255), true);
												}
												else if (Distance <= 100 && Distance > 75)
												{
													DrawOutlinedText(ImGui::GetFont(), distancestring.c_str(), ImVec2((Ped2DPos.x - width / 2) + (width / 2 - font_size + (font_size / 2) + 20), Ped2DPos.y + height / 2), 8.0f, ImColor(255, 255, 255), true);
													DrawOutlinedText(ImGui::GetFont(), ICON_FA_LEAF"", ImVec2((Ped2DPos.x - width / 2) + (width / 2 - font_size + (font_size / 2) + 20), Ped2DPos.y + height / 2), 8.0f, ImColor(255, 255, 255), true);

												}
												else if (Distance <= 125 && Distance > 100)
												{
													DrawOutlinedText(ImGui::GetFont(), distancestring.c_str(), ImVec2((Ped2DPos.x - width / 2) + (width / 2 - font_size + (font_size / 2) + 20), Ped2DPos.y + height / 2), 6.0f, ImColor(255, 255, 255), true);
													DrawOutlinedText(ImGui::GetFont(), ICON_FA_LEAF"", ImVec2((Ped2DPos.x - width / 2) + (width / 2 - font_size + (font_size / 2) + 20), Ped2DPos.y + height / 2), 6.0f, ImColor(255, 255, 255), true);
												}
												//	render->DrawText(ImVec2((Ped2DPos.x - width / 2) + (width / 2 - font_size + (font_size / 2) + 20), Ped2DPos.y + height / 2),ImColor(255,255,255,255), distancestring.c_str());
											
											
											}
											

										}
									}
								}
							}
						}

					}


				}
			}

		}
	}
}
	
