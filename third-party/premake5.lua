include "./glad.lua"
include "./glfw.lua"
include "./ImGui.lua"

project "ThirdParty"

	kind "None"

	files 
	{
		"./**.h",
		"./**.hpp",
		"./**.cpp",
		"./**.inl"
	}
