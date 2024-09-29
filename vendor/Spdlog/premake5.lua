project "Spdlog"
	kind "StaticLib"
	language "C++"
	cppdialect "C++11"
	defines { "SPDLOG_COMPILED_LIB" }

	files {
		"include/**.h",
		"src/**.cpp"
	}

	includedirs {
		"include"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"