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
IncludeDir["ThirdParty"] = "%{wks.location}/Projects/Honey/third-party/"
IncludeDir["spdlog"] = "%{wks.location}/Projects/Honey/third-party/spdlog/include"
IncludeDir["GLFW"] = "%{wks.location}/Projects/Honey/third-party/glfw/include"
IncludeDir["GLAD"] = "%{wks.location}/Projects/Honey/third-party/glad/include"
IncludeDir["ImGui"] = "%{wks.location}/Projects/Honey/third-party/ImGui"
IncludeDir["GLM"] = "%{wks.location}/Projects/Honey/third-party/glm"
IncludeDir["StbImage"] = "%{wks.location}/Projects/Honey/third-party/stb_image"
IncludeDir["EnTT"] = "%{wks.location}/Projects/Honey/third-party/entt/include"

group "Dependencies"

	include "third-party/premake"
	include "Projects/Honey/third-party/"

group ""

	include "Projects/Honey"
	include "Projects/Sandbox"

group "Tools"

	include "Projects/Honeycomb"
	include "Projects/Honeypot"
