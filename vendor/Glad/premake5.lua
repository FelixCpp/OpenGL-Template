project "Glad"
	kind "StaticLib"
	language "C"
	staticruntime "On"
	targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir("%{wks.location}/bin/intermediates/" .. outputdir .. "/%{prj.name}")

	files {
		"include/Glad/glad.h",
		"include/Glad/glad_wgl.h",
		"include/KHR/khrplatform.h",
		"src/glad.c",
		"src/glad_wgl.c"
	}

	includedirs {
		"%{IncludeDirs.Glad}"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"