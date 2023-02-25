require "lib"

workspace "Hemy"
    architecture "x64"
    configurations
    {
        "Debug",
        "Release"
    }
    startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDirs = {}
IncludeDirs["glew"] = "Hemy/vendor/glew/include"
IncludeDirs["glfw"] = "Hemy/vendor/glfw/include"

include "Hemy/vendor/glew"
include "Hemy/vendor/glfw"

project "Hemy"
    location "Hemy"
    language "C++"
    staticruntime "on"
    cppdialect "C++17"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "hemypch.h"
    pchsource "Hemy/src/hemypch.cpp"

    files
    {
        "Hemy/src/**.h",
        "Hemy/src/**.cpp"
    }

    includedirs
    {
        "Hemy/src",
        "%{IncludeDirs.glew}"
    }

    links
    {
        "glew",
        "opengl32.lib"
    }

    defines
    {
        "GLEW_STATIC"
    }

    filter "options:lib=static"
        kind "StaticLib"

    filter "options:lib=shared"
        kind "SharedLib"
        defines { "HEMY_BUILD_DLL" }

    filter "system:windows"
        systemversion "latest"
        defines
        {
            "HEMY_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "HEMY_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "HEMY_RELEASE"
        runtime "Release"
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    staticruntime "on"
    cppdialect "C++17"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "Sandbox/src/**.h",
        "Sandbox/src/**.cpp"
    }

    includedirs
    {
        "Hemy/src",
        "%{IncludeDirs.glfw}",
        "%{IncludeDirs.glew}"
    }

    links
    {
        "Hemy",
        "glfw",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"

    filter "options:lib=shared"
        defines { "HEMY_IMPORT_DLL" }

    filter "configurations:Debug"
        defines { "HEMY_DEBUG" }
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines { "HEMY_RELEASE" }
        runtime "Release"
        optimize "on"
