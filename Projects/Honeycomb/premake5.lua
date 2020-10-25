project "Honeycomb"

	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin/intermediates/" .. outputdir .. "/%{prj.name}")

	files
	{
		"**.h",
		"**.cpp"
	}

	includedirs
	{
		"%{wks.location}/Projects/Honeycomb/",
		"%{IncludeDir.Honey}",
		"%{IncludeDir.ThirdParty}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.Stb}",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.EnTT}"
	}

	links
	{
		"Honey"
	}

	filter "system:windows"
		systemversion "latest"

	filter "system:linux"
		systemversion "latest"
		
		links 
		{
			"GLFW",
			"GLAD",
			"ImGui",
			"pthread",
			"dl"
		}

	filter "configurations:Debug"
		defines "HNY_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "HNY_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "HNY_DIST"
		runtime "Release"
		optimize "on"
