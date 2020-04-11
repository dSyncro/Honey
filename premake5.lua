workspace "Honey"
	architecture "x86_64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
    }
	
	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.architecture}/%{cfg.system}/%{cfg.buildcfg}"

IncludeDir = {}
IncludeDir["GLFW"] = "Projects/Honey/third-party/glfw/include"

include "Projects/Honey/third-party/glfw"

project "Honey"
	location "Projects/Honey"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin/intermediates/" .. outputdir .. "/%{prj.name}")

	files
	{
		"Projects/%{prj.name}/**.h",
		"Projects/%{prj.name}/**.cpp"
	}

	excludes 
	{
		"Projects/%{prj.name}/third-party/**.h",
		"Projects/%{prj.name}/third-party/**.cpp"
	}

	includedirs
	{
		"Projects/%{prj.name}",
		"Projects/%{prj.name}/third-party/spdlog/include",
		"%{IncludeDir.GLFW}",
	}

	links 
	{
		"GLFW",
		"opengl32.lib",
	}

	filter "system:windows"
		systemversion "latest"

		defines 
		{
			"HNY_PLATFORM_WINDOWS",
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

project "Sandbox"
	location "Projects/Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin/intermediates/" .. outputdir .. "/%{prj.name}")

	files
	{
		"Projects/%{prj.name}/**.h",
		"Projects/%{prj.name}/**.cpp"
	}

	includedirs
	{
		"Projects/Honey/third-party/spdlog/include",
		"Projects/Honey/",
	}

	links
	{
		"Honey"
	}

	filter "system:windows"
		systemversion "latest"

		defines 
		{
			"HNY_PLATFORM_WINDOWS"
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