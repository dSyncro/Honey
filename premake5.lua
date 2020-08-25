include "./third-party/premake/customization/solution_items.lua"

workspace "Honey"

	architecture "x86_64"
	startproject "Honeycomb"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	solution_items 
	{
		".gitmodules",
		".gitignore",
		".editorconfig",
	}
	
	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.architecture}/%{cfg.system}/%{cfg.buildcfg}"

IncludeDir = {}

IncludeDir["Honey"] = "%{wks.location}/Projects/Honey/"
IncludeDir["ThirdParty"] = "%{wks.location}/third-party/"
IncludeDir["spdlog"] = "%{wks.location}/third-party/spdlog/include"
IncludeDir["GLFW"] = "%{wks.location}/third-party/glfw/include"
IncludeDir["GLAD"] = "%{wks.location}/third-party/glad/include"
IncludeDir["ImGui"] = "%{wks.location}/third-party/ImGui"
IncludeDir["GLM"] = "%{wks.location}/third-party/glm"
IncludeDir["StbImage"] = "%{wks.location}/third-party/stb_image"
IncludeDir["EnTT"] = "%{wks.location}/third-party/entt/include"

group "Dependencies"

	include "third-party/"
	include "third-party/premake"

group ""

	include "Projects/Honey"
	include "Projects/Sandbox"

group "Tools"

	include "Projects/Honeycomb"
	include "Projects/Honeypot"
