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
IncludeDir["spdlog"] = "Projects/Honey/third-party/spdlog/include"
IncludeDir["GLFW"] = "Projects/Honey/third-party/glfw/include"
IncludeDir["GLAD"] = "Projects/Honey/third-party/glad/include"
IncludeDir["GLM"] = "Projects/Honey/third-party/glm"
IncludeDir["ImGui"] = "Projects/Honey/third-party/ImGui"
IncludeDir["StbImage"] = "Projects/Honey/third-party/stb_image"

group "Dependencies"

	include "Projects/Honey/third-party/glfw"
	include "Projects/Honey/third-party/glad"
	include "Projects/Honey/third-party/ImGui"

group ""

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
		"Projects/%{prj.name}/*.h",
		"Projects/%{prj.name}/*.cpp",

		"Projects/%{prj.name}/Honey/**.h",
		"Projects/%{prj.name}/Honey/**.cpp",

		"Projects/%{prj.name}/third-party/spdlog/include/**.h",

		"Projects/%{prj.name}/third-party/glm/glm/**.inl",
		"Projects/%{prj.name}/third-party/glm/glm/**.hpp",

		"Projects/%{prj.name}/third-party/stb_image/**.h",
		"Projects/%{prj.name}/third-party/stb_image/**.cpp",
	}

	defines 
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE",
		"_SILENCE_CXX17_RESULT_OF_DEPRECATION_WARNING"
	}

	includedirs
	{
		"Projects/%{prj.name}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.StbImage}",
	}

	links 
	{
		"GLFW",
		"GLAD",
		"ImGui"
		
	}

	filter "system:windows"
		systemversion "latest"
		
		links 
		{
			"opengl32.lib",
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
		"Projects/Honey/third-party",
		"%{IncludeDir.GLM}",
	}
	
	

	links
	{
		"Honey",	
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

group "Tools"

project "Honeycomb"

	location "Projects/Honeycomb"
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
		"Projects/Honey/third-party",
		"%{IncludeDir.GLM}",
	}

	links
	{
		"Honey",
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

project "Honeypot"

	location "Projects/Honeypot"
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
		"Projects/Honey/third-party",
		"%{IncludeDir.GLM}",
	}

	links
	{
		"Honey",
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