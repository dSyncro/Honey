include "./glad.lua"
include "./glfw.lua"
include "./ImGui.lua"

project "ThirdParty"

	kind "None"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin/intermediates/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"./**.h",
		"./**.hpp",
		"./**.cpp",
		"./**.inl"
	}
