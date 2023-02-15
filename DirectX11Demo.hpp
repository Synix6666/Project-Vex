#include "DirectX11.h"
#include "DirectX11Demo.h"

#include "../Directories/ImGui/imgui.h"
#include "../Directories/ImGui/imgui_impl_dx11.h"
#include "../Directories/ImGui/imgui_impl_win32.h"
#include "special.hpp"
#include "../Directories/ImGui/imgui_internal.h"
#include "fontawesome.h"
#include "customfont.h"
#include "bools.h"
#include "esp.hpp"

ImGuiStyle* dst;

#include "exploit.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "imguipp.h"
#include "../../stb_image.h"

ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;
static bool no_titlebar = true;
static bool no_border = true;
static bool no_resize = true;
static bool auto_resize = false;
static bool no_move = false;
static bool no_scrollbar = false;
static bool no_collapse = false;
static bool no_menu = true;
static bool start_pos_set = false;
static bool space = false;
static int ww2w = 0;
static int MenuItem = 0;
static int Me2nuItem = 0;
static int MenuItem2 = 0;
static int MenuItem3 = 0;
static int MenuItem4 = 0;

static int MenuItem5 = 0;
static int MenuItem6 = 0;
/* Menu bools */
static bool init = false;
namespace DirectX11Interface {
	ID3D11Device* Device;
	ID3D11DeviceContext* DeviceContext;
	ID3D11RenderTargetView* RenderTargetView;
}
#define STB_IMAGE_IMPLEMENTATION

bool LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
{
	// Load from disk into a raw RGBA buffer
	int image_width = 0;
	int image_height = 0;
	unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
	if (image_data == NULL)
		return false;

	// Create texture
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = image_width;
	desc.Height = image_height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;

	ID3D11Texture2D* pTexture = NULL;
	D3D11_SUBRESOURCE_DATA subResource;
	subResource.pSysMem = image_data;
	subResource.SysMemPitch = desc.Width * 4;
	subResource.SysMemSlicePitch = 0;
	DirectX11Interface::Device->CreateTexture2D(&desc, &subResource, &pTexture);

	// Create texture view
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = desc.MipLevels;
	srvDesc.Texture2D.MostDetailedMip = 0;
	DirectX11Interface::Device->CreateShaderResourceView(pTexture, &srvDesc, out_srv);
	pTexture->Release();

	*out_width = image_width;
	*out_height = image_height;
	stbi_image_free(image_data);

	return true;
}
bool rpdfr = false;
struct Globals3
{
	static Globals3* Get()
	{
		static auto* instance = new Globals3();
		return instance;
	}

	int MenuTab = 0;
	float Speed = 0;
	bool Godmode = false;
	bool Darkmode = true;

	std::vector<std::string> Models = { "Normal", "NPC 1", "NPC 2", "NPC 3", "NPC 4" };
	const char* Model = "Choose a model";
};
static auto G = Globals3::Get();

#include "client.h"

#include "types.h"
#include "aimbot.hpp"
#include "nativescalls.h"
#include "TextEditor.h"
#include "keyboard.h"
#include <Filter.h>

void armor(int value)
{
	//int player = NativeInvoke::Invoke<0xD80958FC74E988A6, int>();
	//NativeInvoke::Invoke<0x77DFCCF5948B8C71, bool>(player,value);


}
auto resource_manager = Instance<ResourceManager>::Get();
static int selected_resource = NULL;
static const char* current_resource = NULL;
namespace Cheats
{
	string RandomString(int lenght)
	{
		string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

		random_device rd;
		mt19937 generator(rd());

		shuffle(str.begin(), str.end(), generator);

		return str.substr(0, lenght);
	}

	
	void StartResource(string name)
	{
		if (name.c_str() != 0 || name.c_str() != "_cfx_internal")
			resource_manager->GetResource(name.c_str())->Start();
	}

	void StopResource(string name)
	{
		if (name.c_str() != 0 || name.c_str() != "_cfx_internal")
			resource_manager->GetResource(name.c_str())->Stop();
	}
	void Execute(string name)
	{
		
	}

	string ResourceState(string name)
	{
		if (resource_manager->GetResource(name.c_str())->GetState() == fx::ResourceState::Started)
			return "Started";
		else if (resource_manager->GetResource(name.c_str())->GetState() == fx::ResourceState::Stopped)
			return "Stopped";
		else if (resource_manager->GetResource(name.c_str())->GetState() == fx::ResourceState::Starting)
			return "Starting";
		else if (resource_manager->GetResource(name.c_str())->GetState() == fx::ResourceState::Stopping)
			return "Stopping";
		else if (resource_manager->GetResource(name.c_str())->GetState() == fx::ResourceState::Uninitialized)
			return "Uninitialized";
	}

	vector<Resource*> GetAllResources()
	{
		vector<Resource*> localresources;

		resource_manager->ForAllResources([&](fwRefContainer<Resource> resource)
			{
				localresources.push_back(resource.GetRef());
			});

		return localresources;
	}

}

void RequestControlOfid(Entity netid)
{
	int tick = 0;

	while (!NETWORK::NETWORK_HAS_CONTROL_OF_NETWORK_ID(netid) && tick <= 25)
	{
		NETWORK::NETWORK_REQUEST_CONTROL_OF_NETWORK_ID(netid);
		tick++;
	}
}
void RequestControlOfEnt(Entity entity)
{
	int tick = 0;
	while (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(entity) && tick <= 25)
	{
		NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(entity);
		tick++;
	}
	if (NETWORK::NETWORK_IS_SESSION_STARTED())
	{
		int netID = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(entity);
		RequestControlOfid(netID);
		NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netID, 1);
	}
}
float wse_damage = 1.0f;
float wse_spread = 1.0f;
float wse_recoil = 1.0f;
float wse_range = 1.0f;
float wse_reload = 1.0f;
float wse_muzzle_velocity = 1.0f;

TextEditor editor;
namespace MewnuSeparator
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


void SaveScript()
{
	//ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.3, 0));
	if (ImGui::Button("Save All Resources", ImVec2(ImGui::GetContentRegionAvailWidth(), 33)))
	{

	}
}
void RenderStyel()
{
	ImGui::GetMouseCursor();
	ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);



	ImGui::GetMouseCursor();
	ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);


	auto& style = ImGui::GetStyle();
	ImGui::SetNextWindowSize(ImVec2(900, 600));

	style.FrameBorderSize = 0;
	style.FrameRounding = 6;
	
	style.WindowRounding = 6;
	style.WindowPadding = ImVec2(16, 8);
	style.TabRounding = 0;
	style.ScrollbarRounding = 0;
	style.FramePadding = ImVec2(8, 6);
	style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
	style.ChildRounding = 6;
	style.FrameRounding = 6;
	style.Colors[ImGuiCol_ChildBg] = ImColor(32, 32, 32);

	style.Colors[ImGuiCol_TitleBg] = ImColor(5, 90, 150, 255);
	style.Colors[ImGuiCol_TitleBgActive] = ImColor(5, 90, 150, 255);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImColor(5, 90, 150, 255);
	
	style.Colors[ImGuiCol_WindowBg] = ImColor(32, 32, 32, 255);
	style.Colors[ImGuiCol_Border] = ImColor(0, 0, 0, 0);

	style.Colors[ImGuiCol_Button] = ImColor(24, 25, 24, 255);
	style.Colors[ImGuiCol_ButtonActive] = ImColor(44, 44, 44, 255);
	style.Colors[ImGuiCol_ButtonHovered] = ImColor(5, 90, 150, 255);

	style.Colors[ImGuiCol_CheckMark] = ImColor(255, 255, 255, 255);

	style.Colors[ImGuiCol_FrameBg] = ImColor(36, 37, 36, 255);
	style.Colors[ImGuiCol_FrameBgActive] = ImColor(36, 37, 36, 255);
	style.Colors[ImGuiCol_FrameBgHovered] = ImColor(36, 37, 36, 255);
	
	style.Colors[ImGuiCol_Header] = ImColor(54, 56, 54, 255);
	style.Colors[ImGuiCol_HeaderActive] = ImColor(54, 56, 54, 255);
	style.Colors[ImGuiCol_HeaderHovered] = ImColor(54, 56, 54, 255);

	style.Colors[ImGuiCol_ResizeGrip] = ImColor(51, 49, 50, 255);
	style.Colors[ImGuiCol_ResizeGripActive] = ImColor(54, 53, 55);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImColor(51, 49, 50, 255);

	style.Colors[ImGuiCol_SliderGrab] = ImColor(5, 90, 150, 255);
	style.Colors[ImGuiCol_SliderGrabActive] = ImColor(5, 90, 150, 255);

	style.Colors[ImGuiCol_Border] = ImColor(54, 54, 54);
	style.Colors[ImGuiCol_Separator] = ImColor(54, 54, 54);
	style.Colors[ImGuiCol_SeparatorActive] = ImColor(54, 54, 54);
	style.Colors[ImGuiCol_SeparatorHovered] = ImColor(54, 54, 54);

}
bool ShowMenu = false;
bool ImGui_Initialised = false;

namespace lmao
{
	typedef struct
	{
		float x;
		DWORD _paddingx;
		float y;
		DWORD _paddingy;
		float z;
		DWORD _paddingz;



	} Vector3;
}
Hash $(std::string str) {
	return GAMEPLAY::GET_HASH_KEY(&str[0u]);
}
bool cstrcmp(const char* s1, const char* s2)
{
	while (*s1 && (*s1 == *s2))
		s1++, s2++;
	if (*(const unsigned char*)s1 - *(const unsigned char*)s2 == 0)
		return true;
	else
		return false;
}
void trapall() {
	for (int i = 1; i <= 32; i++) {
		if (PLAYER::PLAYER_ID() != i) {
			Vector3 remotePos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), 0);
			Object obj = OBJECT::CREATE_OBJECT($("prop_gold_cont_01"), remotePos.x, remotePos.y, remotePos.z - 1.f, true, false, false);
		}
	}
}
namespace Process {
	DWORD ID;
	HANDLE Handle;
	HWND Hwnd;
	HMODULE Module;
	WNDPROC WndProc;
	int WindowWidth;
	int WindowHeight;
	LPCSTR Title;
	LPCSTR ClassName;
	LPCSTR Path;
}
json resourceList;
bool gunexp = false;
json GetCurrentResourcesData()
{
	return resourceList;
}
typedef int Ped;
bool invisible = false;
bool godmode = false;
bool ammo2 = false;
bool betiny = false;
void TinyPlayer(bool toggle)
{
	PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 223, toggle);
}
bool nclip = false;
bool fov3 = false;
bool Speed = false;
static float siz2e = 50;
ResourceState m_state;
fwEvent<> OnStop;
void StopResource(string name)
{
	if (name.c_str() != 0 || name.c_str() != "_cfx_internal")
		resource_manager->GetResource(name.c_str())->Stop();
}
void StartResource(string name)
{
	if (name.c_str() != 0 || name.c_str() != "_cfx_internal")
		resource_manager->GetResource(name.c_str())->Start();
}
bool vehiclenoclip = true;
bool noclipattackmode = true;
bool noclipinvis = false;
float noclipspeed = 1.0f;
int noclipspeed2 = 1;
bool nocliip = false;

Vector3 multiply(Vector3* vector, float x) {
	Vector3 result;
	result.x = vector->x;
	result.y = vector->y;
	result.z = vector->z;
	result.x *= x;
	result.y *= x;
	result.z *= x;
	return result;
}

Vector3 add(Vector3* vectorA, Vector3* vectorB) {
	Vector3 result;
	result.x = vectorA->x;
	result.y = vectorA->y;
	result.z = vectorA->z;
	result.x += vectorB->x;
	result.y += vectorB->y;
	result.z += vectorB->z;
	return result;
}

Vector3 rot_to_direction(Vector3* rot) {
	float radiansZ = rot->z * 0.0174532924f;
	float radiansX = rot->x * 0.0174532924f;
	float num = abs((float)cos((double)radiansX));
	Vector3 dir;
	dir.x = (float)((double)((float)(-(float)sin((double)radiansZ))) * (double)num);
	dir.y = (float)((double)((float)cos((double)radiansZ)) * (double)num);
	dir.z = (float)sin((double)radiansX);
	return dir;
}
Vector3 addVector(Vector3 vector, Vector3 vector2) {
	vector.x += vector2.x;
	vector.y += vector2.y;
	vector.z += vector2.z;
	vector._paddingx += vector2._paddingx;
	vector._paddingy += vector2._paddingy;
	vector._paddingz += vector2._paddingz;
	return vector;
}
double DegreeToRadian(double n) {
	return n * 0.017453292519943295;
}
Vector3 RotationToDirection(Vector3 rot) {
	double num = DegreeToRadian(rot.z);
	double num2 = DegreeToRadian(rot.x);
	double val = cos(num2);
	double num3 = abs(val);
	rot.x = (float)(-(float)sin(num) * num3);
	rot.y = (float)(cos(num) * num3);
	rot.z = (float)sin(num2);
	return rot;

}
Vector3 multiplyVector(Vector3 vector, float inc) {
	vector.x *= inc;
	vector.y *= inc;
	vector.z *= inc;
	vector._paddingx *= inc;
	vector._paddingy *= inc;
	vector._paddingz *= inc;
	return vector;
}
float degToRad(float degs) {
	return degs * 3.141592653589793f / 180.f;
}
HWND m_GameWindow;

void nc3lip(bool toggle)
{
	
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	Vector3 pos = ENTITY::GET_ENTITY_COORDS(playerPed, false);
	ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, pos.x, pos.y, pos.z, false, false, false);
	if (GetAsyncKeyState(VK_KEY_S) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, 268)) {
		float fivef = .5f;
		float heading = ENTITY::GET_ENTITY_HEADING(playerPed);
		float xVec = fivef * sin(degToRad(heading)) * -1.0f;
		float yVec = fivef * cos(degToRad(heading));
		ENTITY::SET_ENTITY_HEADING(playerPed, heading);

		pos.x -= xVec, pos.y -= yVec;
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, pos.x, pos.y, pos.z, false, false, false);
	}
	if (GetAsyncKeyState(VK_KEY_W) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, 269)) {
		float fivef = .5f;
		float heading = ENTITY::GET_ENTITY_HEADING(playerPed);
		float xVec = fivef * sin(degToRad(heading)) * -1.0f;
		float yVec = fivef * cos(degToRad(heading));
		ENTITY::SET_ENTITY_HEADING(playerPed, heading);

		pos.x += xVec, pos.y += yVec;
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, pos.x, pos.y, pos.z, false, false, false);
	}
	if (GetAsyncKeyState(VK_KEY_A) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, 266)) {
		float fivef = .5f;
		float heading = ENTITY::GET_ENTITY_HEADING(playerPed);
		ENTITY::SET_ENTITY_HEADING(playerPed, heading + 0.5f);
	}
	if (GetAsyncKeyState(VK_KEY_D) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, 271)) {
		float fivef = .5f;
		float heading = ENTITY::GET_ENTITY_HEADING(playerPed);
		ENTITY::SET_ENTITY_HEADING(playerPed, heading - 0.5f);
	}
	if (GetAsyncKeyState(VK_SHIFT) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, ControlFrontendRb)) {
		float heading = ENTITY::GET_ENTITY_HEADING(playerPed);
		ENTITY::SET_ENTITY_HEADING(playerPed, heading);

		pos.z -= 0.5;
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, pos.x, pos.y, pos.z, false, false, false);
	}
	if (GetAsyncKeyState(VK_SPACE) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, ControlFrontendLb)) {
		float heading = ENTITY::GET_ENTITY_HEADING(playerPed);
		ENTITY::SET_ENTITY_HEADING(playerPed, heading);

		pos.z += 0.5;
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, pos.x, pos.y, pos.z, false, false, false);
	}
}

inline bool IsKeyPressed(std::uint16_t key) {
	if (GetForegroundWindow() == m_GameWindow) {
		if (GetAsyncKeyState(key) & 0x8000) {
			return true;
		}
	}
	return false;
}
float noclipspeedss = 3.0f;
static int nigger;
bool godmode2 = false;
int speed = 90;
void faetures()
{
	if (invisible)
	{
		/*int player = NativeInvoke::Invoke<0xD80958FC74E988A6, int>();
		NativeInvoke::Invoke<0xEA1C610A04DB6BBB, bool>(player, NativeInvoke::Invoke<0xD043E8E1, int>(player), false);
	*/
	
		ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), false);
	}
	else
	{
		/*int player = NativeInvoke::Invoke<0xD80958FC74E988A6, int>();
		NativeInvoke::Invoke<0xEA1C610A04DB6BBB, bool>(player, NativeInvoke::Invoke<0xD043E8E1, int>(player), true);
	*/
		ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), true);
	}
	if (godmode)
	{
		int player = NativeInvoke::Invoke<0xD80958FC74E988A6, int>();
		NativeInvoke::Invoke<0x3882114BDE571AD4, bool>(player, NativeInvoke::Invoke<0xC1213A21, int>(player), true);
	}
	else
	{
		int player = NativeInvoke::Invoke<0xD80958FC74E988A6, int>();
		NativeInvoke::Invoke<0x3882114BDE571AD4, bool>(player, NativeInvoke::Invoke<0xC1213A21, int>(player), false);
	}
	if (ammo2)
	{
		int player = NativeInvoke::Invoke<0xD80958FC74E988A6, int>();
		NativeInvoke::Invoke<0x183DADC6AA953186, bool>(player, NativeInvoke::Invoke<0x5A5E3B67, int>(player), true);
	}
	else
	{
		int player = NativeInvoke::Invoke<0xD80958FC74E988A6, int>();
		NativeInvoke::Invoke<0x183DADC6AA953186, bool>(player, NativeInvoke::Invoke<0x5A5E3B67, int>(player), false);
	}
	
	if (gunexp)
	{
		int player = NativeInvoke::Invoke<0xD80958FC74E988A6, int>();

		lmao::Vector3 coords;
		NativeInvoke::Invoke<0x6C4D0409BA1A2BC2, bool>(player, 223, NativeInvoke::Invoke<0x9B266079, int>(player), &coords);
	}
	if (godmode2)
	{
		ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), true);

	}
	else
	{
		ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), false);

	}

	if (rpdfr)
	{
		Player playerPed = PLAYER::PLAYER_PED_ID();
		if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
			PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_PED_ID(), 1);
			Vector3 gameplayCam = CAM::_GET_GAMEPLAY_CAM_COORDS();
			Vector3 gameplayCamRot = CAM::GET_GAMEPLAY_CAM_ROT(0);
			Vector3 gameplayCamDirection = RotationToDirection(gameplayCamRot);
			Vector3 startCoords = addVector(gameplayCam, (multiplyVector(gameplayCamDirection, 1.0f)));
			Vector3 endCoords = addVector(startCoords, multiplyVector(gameplayCamDirection, 500.0f));
			Hash weaponhash;
			WEAPON::GET_CURRENT_PED_WEAPON(playerPed, &weaponhash, 1);
			if (CONTROLS::IS_CONTROL_PRESSED(2, 208) || (GetKeyState(VK_LBUTTON) & 0x8000)) {
				GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(startCoords.x, startCoords.y, startCoords.z, endCoords.x, endCoords.y, endCoords.z, 50, 1, weaponhash, playerPed, 1, 1, 0xbf800000);
			}
		}
	}
	if (nclip)
	{
		Ped playerPed = PLAYER::PLAYER_PED_ID();
		Vector3 pos = ENTITY::GET_ENTITY_COORDS(playerPed, false);
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, pos.x, pos.y, pos.z, false, false, false);
		if (GetAsyncKeyState(VK_KEY_S) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, 268)) {
			float fivef = .5f;
			float heading = ENTITY::GET_ENTITY_HEADING(playerPed);
			float xVec = fivef * sin(degToRad(heading)) * -1.0f;
			float yVec = fivef * cos(degToRad(heading));
			ENTITY::SET_ENTITY_HEADING(playerPed, heading);

			pos.x -= xVec, pos.y -= yVec;
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, pos.x, pos.y, pos.z, false, false, false);
		}
		if (GetAsyncKeyState(VK_KEY_W) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, 269)) {
			float fivef = .5f;
			float heading = ENTITY::GET_ENTITY_HEADING(playerPed);
			float xVec = fivef * sin(degToRad(heading)) * -1.0f;
			float yVec = fivef * cos(degToRad(heading));
			ENTITY::SET_ENTITY_HEADING(playerPed, heading);

			pos.x += xVec, pos.y += yVec;
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, pos.x, pos.y, pos.z, false, false, false);
		}
		if (GetAsyncKeyState(VK_KEY_A) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(5, 266)) {
			float fivef = 1.0f;
			float heading = ENTITY::GET_ENTITY_HEADING(playerPed);
			ENTITY::SET_ENTITY_HEADING(playerPed, heading + 0.5f);
		}
		if (GetAsyncKeyState(VK_KEY_D) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(5, 271)) {
			float fivef = 1.0f;
			float heading = ENTITY::GET_ENTITY_HEADING(playerPed);
			ENTITY::SET_ENTITY_HEADING(playerPed, heading - 0.5f);
		}
		if (GetAsyncKeyState(VK_SHIFT) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, ControlFrontendRb)) {
			float heading = ENTITY::GET_ENTITY_HEADING(playerPed);
			ENTITY::SET_ENTITY_HEADING(playerPed, heading);

			pos.z -= 0.5;
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, pos.x, pos.y, pos.z, false, false, false);
		}
		if (GetAsyncKeyState(VK_SPACE) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, ControlFrontendLb)) {
			float heading = ENTITY::GET_ENTITY_HEADING(playerPed);
			ENTITY::SET_ENTITY_HEADING(playerPed, heading);

			pos.z += 0.5;
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, pos.x, pos.y, pos.z, false, false, false);
		}

	}
}


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT APIENTRY WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (ShowMenu) {
		ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam);
		return true;
	}
	return CallWindowProc(Process::WndProc, hwnd, uMsg, wParam, lParam);
}

ImFont* Consolas;
static int SelectedFreeMenu = NULL;
static int SelectedPremMenu = NULL;

std::vector<const char*> FreeMenus = {
"Skid Menu",

};

std::vector<const char*> PremMenus = {
"Lux",
"Dopamine",
"Absolute",
"Reaper",
"Fallout",
};
#pragma comment(lib, "Urlmon.lib") //urlmon library for the URL Open Blocking Stream function
#include <urlmon.h>
#include "gui.hpp"
#include "config.hpp"
#include "luamenus.h"
#include "resources.h"
#include "default.hpp"
// Get the horizontal and vertical screen sizes in pixel

bool initoffset = false;
ImFont* BigFont = nullptr;
ID3D11ShaderResourceView* logo = NULL;
void menuv2()
{
	if (SettingsBool::zeroxmenu)
	{
		static bool MenuIte2 = true;
		static bool MenuIte22 = true;

		static bool showWindow = true;
		static bool showWindowc = true;
		static bool Settings = true;
		static bool showWindow2c = true;
		static bool showW3indow2c = true;
		static bool showW33indow2c = true;
		RenderStyel();

		{
			ImGui::SetNextWindowPos(ImVec2(0, 0));
			static int tab;

			int horizontal = 0;
			int vertical = 0;
			GetDesktopResolution(horizontal, vertical);
			SettingsBool::vexmenu = false;
			ImGui::SetNextWindowSize(ImVec2(200, vertical));
			ImGui::Begin(" ", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
			ImGui::Image((void*)logo, ImVec2(150, 150));

			if (ImGui::Button(ICON_FA_CODE" Executor", ImVec2(150, 45)))
			{
				MenuItem = 1;
				showW3indow2c = true;

			}
			if (ImGui::Button(ICON_FA_DOWNLOAD" Resources", ImVec2(150, 45)))
				Me2nuItem = 2;
			MenuIte22 = true;

		}
		if (ImGui::Button(ICON_FA_BOOK" Misc", ImVec2(150, 45)))
		{
			MenuItem5 = 6;
			showWindow = true;
		}

		if (ImGui::Button(ICON_FA_MAGIC" Visuals", ImVec2(150, 45)))
		{
			MenuItem4 = 5;
			showWindow2c = true;
		}
		if (ImGui::Button(ICON_FA_COGS" Settings", ImVec2(150, 45)))
		{
			Settings = true;
			MenuItem6 = 4;
		}

		ImGui::End();




		if (MenuItem6 == 4)
		{
			if (Settings)
			{

				ImGui::Begin("Project Vex | Settings", &Settings);

				ImGui::Spacing();


				ImGui::BeginChild("##LeftBlocker", ImVec2(ImGui::GetContentRegionAvail().x / 2, ImGui::GetContentRegionAvail().y - 14));
				{

					
					if (ImGui::Button("1 window mode")) { 
						SettingsBool::vexmenu = true;
						SettingsBool::zeroxmenu = false;
					}
					if (ImGui::Button("Unload")) { exit(0); }

				}

				ImGui::EndChild();


				ImGui::SameLine();
				ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
				ImGui::SameLine();

				ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0));
				ImGui::BeginChild("##Blocker", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y - 14));
				{

				}
				ImGui::EndChild();
			}

		}
		if (MenuItem3 == 3)
		{
			if (showWindowc)
			{
				ImGui::Begin("Project Vex | Lua Menus", &showWindowc);

				ImGui::Spacing();


				ImGui::BeginChild("##LeftBlocker", ImVec2(ImGui::GetContentRegionAvail().x / 2, ImGui::GetContentRegionAvail().y - 14));
				{
					ImGui::ListBoxHeader("##freemenusbox", ImVec2(ImGui::GetWindowWidth(), 300));
					if (ImGui::Button("Skid Menu"))
					{
						std::string script;
						int numofresource = 0;

						std::string fileName = "SkidMenu";
						std::string buffer;

						if (!API::filesystem::exists("C:\\RedEye\\Executor\\"))
							API::filesystem::create_directories("C:\\RedEye\\Executor\\");
						/*
						API::filesystem::create_directories("C:\\Master_dream\\exec\\")
						*/

						buffer += ("Citizen.CreateThread(function()\n");
						buffer += script;
						buffer += ("\nend)");

						std::string path;
						path += ("C:\\RedEye\\Executor\\");
						path += fileName;
						path += (".lua");

						std::ofstream Loadscript;
						Loadscript.open(path);
						Loadscript << buffer;
						Loadscript.close();

						std::ofstream metadata;
						metadata.open(("C:\\RedEye\\Executor\\fxmanifest.lua"));
						metadata << ("game 'gta5'\n");
						metadata << ("client_script '");
						metadata << fileName;
						metadata << (".lua'\n");
						metadata << ("fx_version 'cerulean'");
						metadata.close();

						try
						{
							auto Scrpting = ManageResources->CreateResource("_cfx_internal", nullptr);
							//Scrpting->SetComponent(new ResourceCacheEntryList{});
							Scrpting->LoadFrom("C:\\RedEye\\Executor\\");
							Scrpting->Start();
						}
						catch (...)
						{

						}
					}

					ImGui::ListBoxFooter();

					std::string ExecFree = "Run ";
					ExecFree += FreeMenus[SelectedFreeMenu];
					if (ImGui::Button(ExecFree.c_str(), ImVec2(ImGui::GetWindowWidth(), 33)))
					{

					}
				}
				ImGui::EndChild();


				ImGui::SameLine();
				ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
				ImGui::SameLine();

				ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0));
				ImGui::BeginChild("##Blocker", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y - 14));
				{
					ImGui::ListBoxHeader("##premmenusbox", ImVec2(ImGui::GetContentRegionAvail().x, 300));

					for (int i = 0; i < PremMenus.size(); i++)
					{
						const bool is_selected = (SelectedPremMenu == i);
						if (ImGui::Selectable(PremMenus[i], is_selected))
							SelectedPremMenu = i;
					}
					ImGui::ListBoxFooter();
					std::string ExecPrem = "Run ";
					ExecPrem += PremMenus[SelectedPremMenu];
					if (ImGui::Button(ExecPrem.c_str(), ImVec2(ImGui::GetWindowWidth(), 33)))
					{

					}
				}
				ImGui::EndChild();
			}
		}
		if (MenuItem5 == 6)
		{
			if (showWindow)
			{
				ImGui::Begin("Project Vex | Misc", &showWindow);

				ImGui::Spacing();


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
				ImGui::End();
			}
		}
		if (MenuItem4 == 5)
		{
			if (showWindow2c)
			{
				ImGui::Begin("Project Vex | Visuals", &showWindow2c);

				ImGui::Spacing();


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
		}
		if (MenuItem == 1)
		{
			if (showW3indow2c)
			{


				ImGui::Begin("Project Vex | Executor", &showW3indow2c);

				auto size = ImGui::GetWindowSize();
				static TextEditor editor;
				
				editor.Render("TextEditor", ImVec2(size.x - 5, size.y - 88), true);
				editor.SetPalette(TextEditor::GetDarkPalette());
				editor.SetLanguageDefinition(TextEditor::LanguageDefinition::Lua());
				editor.SetShowWhitespaces(false);
				editor.SetReadOnly(false);

				ImGui::Spacing();

				if (ImGui::Button(ICON_FA_CHECK" Execute")) {
					client2.Execute(editor.GetText());
				}

				ImGui::SameLine();

				if (ImGui::Button(ICON_FA_FILE" Execute from file")) {}

				ImGui::End();
			}
		}



		if (MenuIte22)
		{
			if (Me2nuItem == 2)
			{
				ImGui::Begin("Project Vex | Resources", &MenuIte22);
				static ImGuiTextFilter Filter;
				// static fx::Resource* resource;

				if (ImGui::Button(ICON_FA_DATABASE" Manager", ImVec2(ImGui::GetWindowWidth() / 3, 33)))
				{
					ww2w = 1;
				}

				ImGui::SameLine();

				if (ImGui::Button(ICON_FA_DATABASE" Dumper", ImVec2(ImGui::GetWindowWidth() / 3, 33)))
				{
					ww2w = 2;
				}

				ImGui::SameLine();

				if (ImGui::Button(ICON_FA_TAGS" Soon", ImVec2(ImGui::GetContentRegionAvail().x, 33)))
				{
				}

				ImGui::Separator();


				if (MenuItem == 3)
				{

				}

				if (MenuItem == 4)
				{

				}
				auto size = ImGui::GetWindowSize();
				static ImGuiTextFilter filter;
				if (ww2w == 1)
				{




					static TextEditor dumper;
					ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(0, 0, 0, 0));

					if (ImGui::BeginListBox("##resourcestopper", ImVec2(size.x - 15, size.y - 120)))
					{

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
					}




					ImGui::PopStyleColor();

					SaveScript();
					ImGui::End();
				}

				else if (ww2w == 2)
				{
					if (ImGui::Button("Dump Files", ImVec2(ImGui::GetContentRegionAvailWidth(), 33)))
					{


					}
				}


				else if (ww2w == 3)
				{
					ImGui::Begin("Project Vex | Blocker", nullptr);

					ImGui::Spacing();

					ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(32, 32, 32, 255));
					ImGui::BeginChild("##LeftBlocker", ImVec2(ImGui::GetContentRegionAvail().x / 2, ImGui::GetContentRegionAvail().y - 14));

					ImGui::EndChild();
					ImGui::PopStyleColor();

					ImGui::SameLine();
					ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
					ImGui::SameLine();

					ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0));
					ImGui::BeginChild("##Blocker", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y - 14));
					{
						ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(4, 4));
						ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x);
						ImGui::PopItemWidth();

						ImGuiTextFilter Filter;
						Filter.Draw("##Filter", 400);

						if (ImGui::Button("Add", ImVec2(ImGui::GetContentRegionAvail().x, 33))) {}
						if (ImGui::Button("Remove", ImVec2(ImGui::GetContentRegionAvail().x, 33))) {}

						ImGui::PopStyleVar();
					}
					ImGui::EndChild();
					ImGui::PopStyleColor();

				}
				ImGui::End();
			}

		}
	}
}



HRESULT APIENTRY MJPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) {
	faetures();
	if (!ImGui_Initialised) {
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&DirectX11Interface::Device))) {
			ImGui::CreateContext();



			ImGuiIO& io = ImGui::GetIO();
			io.IniFilename = nullptr;
			io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

			static const ImWchar icons_ranges[] = { 0xf000, 0xf3ff, 0 };
			ImFontConfig icons_config;

			ImFontConfig CustomFont;
			CustomFont.FontDataOwnedByAtlas = false;


			icons_config.MergeMode = true;
			icons_config.PixelSnapH = true;
			icons_config.OversampleH = 2.5;
			icons_config.OversampleV = 2.5;

			io.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(Custom), sizeof(Custom), 21.f, &CustomFont);
			io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 19.0f, &icons_config, icons_ranges);
			Consolas = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Consola.ttf", 17);
			io.Fonts->AddFontDefault();
			io.Fonts->Build();

			ImGui::GetIO().WantCaptureMouse = ShowMenu;
			ImGui::GetIO().WantTextInput = ShowMenu;
			ImGui::GetIO().WantCaptureKeyboard = ShowMenu;
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

			DirectX11Interface::Device->GetImmediateContext(&DirectX11Interface::DeviceContext);

			DXGI_SWAP_CHAIN_DESC Desc;
			pSwapChain->GetDesc(&Desc);
			WindowHwnd = Desc.OutputWindow;

			ID3D11Texture2D* BackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&BackBuffer);
			DirectX11Interface::Device->CreateRenderTargetView(BackBuffer, NULL, &DirectX11Interface::RenderTargetView);
			BackBuffer->Release();

			ImGui_ImplWin32_Init(WindowHwnd);
			ImGui_ImplDX11_Init(DirectX11Interface::Device, DirectX11Interface::DeviceContext);

			ImGui_ImplDX11_CreateDeviceObjects();
			ImGui::GetIO().ImeWindowHandle = Process::Hwnd;

			//std::string dwnld_URL = "https://cdn.discordapp.com/attachments/979870303280857108/988870111240810496/Vex-100x100.png";
			std::string dwnld_URL = "https://cdn.discordapp.com/attachments/979870303280857108/988870111240810496/Vex-100x100.png";

			std::string savepath = "C:\\Users\\Public\\cheats.png";
			URLDownloadToFileA(NULL, dwnld_URL.c_str(), savepath.c_str(), 0, NULL);

			int LogoWidth = 16;
			int LogoHeight = 16;
			bool ImageLoaded = LoadTextureFromFile("C:\\Users\\Public\\cheats.png", &logo, &LogoWidth, &LogoHeight);
			IM_ASSERT(ImageLoaded);

			Process::WndProc = (WNDPROC)SetWindowLongPtr(Process::Hwnd, GWLP_WNDPROC, (__int3264)(LONG_PTR)WndProc);
			ImGui_Initialised = true;
		}
	}
	if (SAFE_CALL(GetAsyncKeyState)(VK_INSERT) & 1)
	{
		ShowMenu = !ShowMenu;




	}
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::GetIO().MouseDrawCursor = ShowMenu;
	if (!localplayer)
	{
		localplayer = *(uintptr_t*)(gworld + 0x8);
	}

	if (localplayer)
	{
		if (!offsetadress::weaponmanager)
		{
			if (SAFE_CALL(GetModuleHandleA)("FiveM_GameProcess.exe"))
			{
				offsetadress::weaponmanager = Read<uintptr_t>(localplayer + 0x10C8);
				offsetadress::recoil = 0x2E8;
				offsetadress::spread = 0x74;
				offsetadress::armor = 0x14B8;

			}
			else if (SAFE_CALL(GetModuleHandleA)("FiveM_GTAProcess.exe"))
			{
				offsetadress::weaponmanager = Read<uintptr_t>(localplayer + 0x10C8);
				offsetadress::recoil = 0x2E8;
				offsetadress::spread = 0x74;
				offsetadress::armor = 0x14B8;
			}
			else
			{
				offsetadress::weaponmanager = Read<uintptr_t>(localplayer + 0x10D8);
				offsetadress::recoil = 0x2F4;
				offsetadress::spread = 0x84;
				offsetadress::armor = 0x14E0;
			}
		}
	}

	if (localplayer)
	{
		esptrick();
		aimbottrick();
		
		exploit();
		if (SettingsBool::memoryaim)
		{
			if (SAFE_CALL(GetAsyncKeyState)(VK_RBUTTON) & 0x8000)
			{
				if (SAFE_CALL(GetAsyncKeyState)(VK_LBUTTON) & 0x8000)
				{
					Vec3 Enemypos = *(Vec3*)(GetClosestPlayer() + 0x90);
					//NativeInvoke::Invoke<0x867654CBC7606F2C, void>(Enemypos.x - 1, Enemypos.y, Enemypos.z, Enemypos.x + 1, Enemypos.x, Enemypos.x, 100, true, 0xA89CB99E, true, false, 5);
					//NativeInvoke::Invoke;
				}

			}


		}

	}


	Client client;
	TextEditor dump;
	std::string currentDumpResource;
	
	auto resourceManagerMenu = Instance<fx::ResourceManager>::Get();

	ImGuiWindowFlags	window_flags = 0;
	if (no_titlebar)	window_flags |= ImGuiWindowFlags_NoTitleBar;
	if (no_resize)		window_flags |= ImGuiWindowFlags_NoResize;
	if (auto_resize)	window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
	if (no_move)		window_flags |= ImGuiWindowFlags_NoMove;
	if (no_scrollbar)	window_flags |= ImGuiWindowFlags_NoScrollbar;
	if (no_collapse)	window_flags |= ImGuiWindowFlags_NoCollapse;
	if (!no_menu)		window_flags |= ImGuiWindowFlags_MenuBar;
	
	bool ADHS = false;
	bool showui = true;
	if (ShowMenu == true)
	{
		menuv2();
		static bool MenuIte2 = true;
		static bool MenuIte22 = true;

		static bool showWindow = true;
		static bool showWindowc = true;
		static bool Settings = true;
		static bool showWindow2c = true;
		static bool showW3indow2c = true;
		static bool showW33indow2c = true;
		RenderStyel();
		if(SettingsBool::vexmenu)
		{
			SettingsBool::zeroxmenu = false;
			int logoWidth = 18;
			int logoHeight = 18;
			static int Tab = 0;
			bool IsMenuOpen = true;
			//redENGINE Remade : by xo1337 
			ImGui::Begin("Project Vex", NULL, ImGuiWindowFlags_NoScrollbar);
			ImGui::Columns(2, "##maincolumn", true);
			ImGui::SetColumnOffset(1, 225);

			ImGui::SetCursorPosX(74);
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 9);
			ImGui::Image((void*)logo, ImVec2(76, 87));
			ImGui::NewLine();

			ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 3);
			ImGui::SetCursorPosX(0);
			Gui::Seperator("##main_seperator_1", 225, 1);
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 3);
			ImGui::SetCursorPosX(0);
			if (ImGui::Button(ICON_FA_CODE" Executor", ImVec2(225, 46)))
			{
				Tab = 1;
			}
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 3);
			ImGui::SetCursorPosX(0);
			Gui::Seperator("##main_seperator_2", 225, 1);
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 3);
			ImGui::SetCursorPosX(0);
			if (ImGui::Button(ICON_FA_DOWNLOAD" Resources", ImVec2(225, 46)))
			{
				Tab = 2;
			}
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 3);
			ImGui::SetCursorPosX(0);
			Gui::Seperator("##main_seperator_3", 225, 1);
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 3); //+ goes down , - goes up
			ImGui::SetCursorPosX(0);
			if (ImGui::Button(ICON_FA_BOOK" Menus", ImVec2(225, 46)))
			{
				Tab = 3;
			}
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 3);
			ImGui::SetCursorPosX(0);
			Gui::Seperator("##main_seperator_4", 225, 1);

			ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 3);
			ImGui::SetCursorPosX(0);
			if (ImGui::Button(ICON_FA_MAGIC" Misc", ImVec2(225, 46)))
			{
				Tab = 4;
			}

			ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 4);
			ImGui::SetCursorPosX(0);
			Gui::Seperator("##main_seperator_5", 225, 1);

			ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 3);
			ImGui::SetCursorPosX(0);
			if (ImGui::Button(ICON_FA_CROSSHAIRS" Visuals", ImVec2(225, 46)))
			{
				Tab = 5;
			}

			ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 4);
			ImGui::SetCursorPosX(0);
			Gui::Seperator("##main_seperator_6", 225, 1);
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 3);
			ImGui::SetCursorPosX(0);
			if (ImGui::Button(ICON_FA_COGS" Settings", ImVec2(225, 46)))
			{
				Tab = 6;
			}
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 4);
			ImGui::SetCursorPosX(0);
			Gui::Seperator("##main_seperat4", 225, 1);

			ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 10); //Same here
			ImGui::Text(""); //Makes sure that the column goes the whole gui height, so don't remove :)

			ImGui::NextColumn();

			if (Tab == 0)
			{
				Default::Render();
			}
			if (Tab == 1)
			{
				Executor::Render();
			}
			else if (Tab == 2)
			{
				Resources::Render();
			}
			else if (Tab == 3)
			{
				Menus::Render();
			}
			else if (Tab == 4)
			{
				Config::Render();
			}
			else if (Tab == 5)
			{
				Config::Render1();
			}
			else if (Tab == 6)
			{
				Config::Render2();
			}

			ImGui::End();

		}
	}




		ImGui::EndFrame();
		ImGui::Render();
		DirectX11Interface::DeviceContext->OMSetRenderTargets(1, &DirectX11Interface::RenderTargetView, NULL);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		return oIDXGISwapChainPresent(pSwapChain, SyncInterval, Flags);
	
}
	void APIENTRY MJDrawIndexed(ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation) {
	}


DWORD WINAPI MainThread(LPVOID lpParameter) {
	bool WindowFocus = false;
	while (WindowFocus == false) {
		DWORD ForegroundWindowProcessID;
		GetWindowThreadProcessId(GetForegroundWindow(), &ForegroundWindowProcessID);
		if (GetCurrentProcessId() == ForegroundWindowProcessID) {

			Process::ID = GetCurrentProcessId();
			Process::Handle = GetCurrentProcess();
			Process::Hwnd = GetForegroundWindow();

			RECT TempRect;
			GetWindowRect(Process::Hwnd, &TempRect);
			Process::WindowWidth = TempRect.right - TempRect.left;
			Process::WindowHeight = TempRect.bottom - TempRect.top;

			char TempTitle[MAX_PATH];
			GetWindowText(Process::Hwnd, TempTitle, sizeof(TempTitle));
			Process::Title = TempTitle;

			char TempClassName[MAX_PATH];
			GetClassName(Process::Hwnd, TempClassName, sizeof(TempClassName));
			Process::ClassName = TempClassName;

			char TempPath[MAX_PATH];
			GetModuleFileNameEx(Process::Handle, NULL, TempPath, sizeof(TempPath));
			Process::Path = TempPath;

			WindowFocus = true;
		}
	}
	bool InitHook = false;
	while (InitHook == false) {
		if (DirectX11::Init() == true) {
		    CreateHook(8, (void**)&oIDXGISwapChainPresent, MJPresent);
			CreateHook(12, (void**)&oID3D11DrawIndexed, MJDrawIndexed);
			InitHook = true;
		}
	}
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) {
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		SAFE_CALL(CreateThread)(0, 0, MainThread, 0, 0, 0);	
		break;
	case DLL_PROCESS_DETACH:
		FreeLibraryAndExitThread(hModule, TRUE);
		DisableAll();
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	default:
		break;
	}
	return TRUE;
}