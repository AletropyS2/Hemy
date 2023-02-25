project "glew"
    kind "StaticLib"
    language "C"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "include/GL/eglew.h",
        "include/GL/glew.h",
        "include/GL/glxew.h",
        "include/GL/wglew.h",
        "src/glew.c"
    }

    includedirs
    {
        "include"
    }

    defines
    {
        "GLEW_STATIC"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "WIN32",
            "_WINDOWS"
        }

    filter "configurations:Debug"
        defines "DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "NDEBUG"
        runtime "Release"
        optimize "on"