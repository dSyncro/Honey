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
		"%{wks.location}/Projects/Honey",
		"%{wks.location}/Projects/Honey/third-party",
		"%{IncludeDir.spdlog}",
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
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "on"
