project "Honey"

	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin/intermediates/" .. outputdir .. "/%{prj.name}")

	files
	{
		"*.h",
		"*.cpp",

		"Honey/**.h",
		"Honey/**.cpp",

		-- Dependencies
		"%{wks.location}/third-party/spdlog/include/**.h",
		"%{wks.location}/third-party/glm/glm/**.inl",
		"%{wks.location}/third-party/glm/glm/**.hpp",
		"%{wks.location}/third-party/stb_image/**.h",
		"%{wks.location}/third-party/stb_image/**.cpp",
		"%{wks.location}/third-party/entt/include/**.h",
		"%{wks.location}/third-party/entt/include/**.cpp",
	}

	defines
	{
		"_SILENCE_CXX17_RESULT_OF_DEPRECATION_WARNING",
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"./",

		"%{IncludeDir.spdlog}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.StbImage}",
		"%{IncludeDir.EnTT}"
	}

	links
	{
		"GLFW",
		"GLAD",
		"ImGui",
	}

	filter "system:windows"
		systemversion "latest"

		excludes
		{
			"Honey/Platform/Windows/**.h",
			"Honey/Platform/Windows/**.cpp",
		}
		
		links 
		{
			"opengl32.lib",
			"d3d12.lib",
			"dxgi.lib",
			"d3dcompiler.lib"
		}

	filter "system:linux"
		systemversion "latest"

		excludes 
		{
			"Honey/Platform/Windows/**.h",
			"Honey/Platform/Windows/**.cpp",
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
