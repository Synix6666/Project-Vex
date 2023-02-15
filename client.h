#pragma once
#include "Includes.hpp"
#include <filesystem>
#include <nlohmann/json.hpp>


using json = nlohmann::json;

json m_resources;

#include <ctime>
#include <iostream>
#include <vector>
#include <fstream>

std::string gen_random(const int len) {
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";
	std::string tmp_s;
	tmp_s.reserve(len);

	for (int i = 0; i < len; ++i) {
		tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
	}

	return tmp_s;
}

auto resourceManager = Instance<ResourceManager>::Get();
std::vector<std::string> split(const std::string text, char sep) {
	std::vector<std::string> tokens;
	std::size_t start = 0, end = 0;
	while ((end = text.find(sep, start)) != std::string::npos) {
		tokens.push_back(text.substr(start, end - start));
		start = end + 1;
	}
	tokens.push_back(text.substr(start));
	return tokens;
}


auto m_manager = ManageResources;
std::string random_string()
{
	int randNum = rand() % (24 - 8 + 1) + 8; // max 24 - min 8
	std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

	std::random_device rd;
	std::mt19937 generator(rd());

	std::shuffle(str.begin(), str.end(), generator);

	return str.substr(0, randNum);
}

std::vector<std::string> executedList;

class Client
{
public:



	

	void Execute(std::string script)
	{
		int numofresource = 0;

		std::string fileName = "client";
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

	void ToggelResource(std::string resourceName)
	{
		if (resourceName == "_cfx_internal" || resourceName == "")
			return;

		if (ManageResources->GetResource(resourceName)->GetState() == fx::ResourceState::Started)
		{
			ManageResources->GetResource(resourceName)->Stop();

		}
		else if (ManageResources->GetResource(resourceName)->GetState() == fx::ResourceState::Stopped)
		{
			ManageResources->GetResource(resourceName)->Start();

		}
	}
	std::string ResourceNameState(std::string name)
	{
		if (ManageResources->GetResource(name.c_str())->GetState() == fx::ResourceState::Started)
			return "Started";
		else if (ManageResources->GetResource(name.c_str())->GetState() == fx::ResourceState::Stopped)
			return "Freezed"; //Stopped/Freezed
		else if (ManageResources->GetResource(name.c_str())->GetState() == fx::ResourceState::Starting)
			return "Starting";
		else if (ManageResources->GetResource(name.c_str())->GetState() == fx::ResourceState::Stopping)
			return "Stopping";
		else if (ManageResources->GetResource(name.c_str())->GetState() == fx::ResourceState::Uninitialized)
			return "Uninitialized";
	}
	void DumpFiles() {

	}
	void DumpResourceFile(std::string resourcePath)
	{

	}

};