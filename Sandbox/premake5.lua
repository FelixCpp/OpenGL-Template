project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
	defines { "GLFW_INCLUDE_NONE" }

	files {
		"modules/**.ixx",
		"src/**.cpp",
	}

	includedirs {
		"include",
		"%{IncludeDirs.GLFW}",
		"%{IncludeDirs.Glad}",
		"%{IncludeDirs.Stb}",
		"%{IncludeDirs.Spdlog}",
	}

	links {
		"GLFW",
		"Glad",
		"Stb"
	}

	filter "files:**.ixx"
		compileas "Module"

	filter "system:windows"
		systemversion "latest"
		defines { "SANDBOX_PLATFORM_WINDOWS" }

	filter "configurations:Debug"
		defines { "SANDBOX_DEBUG", "_DEBUG" }
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines { "SANDBOX_RELEASE", "NDEBUG" }
		runtime "Release"
		optimize "On"
