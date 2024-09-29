include "./dependencies.lua"

workspace "Workspace"
	architecture "x86_64"
	startproject "Sandbox"
	flags { "MultiProcessorCompile" }
	configurations { "Debug", "Release" }

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	group "Dependencies"
		include "vendor/Premake"
		include "vendor/GLFW"
		include "vendor/Glad"
		include "vendor/Stb"
		include "vendor/Spdlog"

	group ""
		include "Sandbox"