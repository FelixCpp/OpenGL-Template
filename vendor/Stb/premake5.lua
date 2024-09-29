project "Stb"
	kind "StaticLib"
	language "C"
	staticruntime "On"
	targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir("%{wks.location}/bin/intermediates/" .. outputdir .. "/%{prj.name}")

	files {
		"include/**.h",
		"src/**.c"
	}

	includedirs {
		"%{IncludeDirs.Stb}"
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines { "DEBUG" }
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		runtime "Release"
		optimize "On"