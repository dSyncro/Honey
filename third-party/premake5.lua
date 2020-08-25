include "./glad.lua"
include "./glfw.lua"
include "./ImGui.lua"

project "ThirdParty"

	kind "Utility"

	files 
	{
		"./**.h",
		"./**.hpp",
		"./**.cpp",
		"./**.inl"
	}
