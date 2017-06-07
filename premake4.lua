solution "DeusVult"
    configurations { "Debug", "Release" }

    project "DeusVultCore"
        kind "StaticLib"
        language "C++"
        files {
            "Core/**.h",
            "Core/**.cpp"
        }

        configuration "Debug"
        defines { "DEBUG" }
        flags { "Symbols" }

        configuration "Release"
        defines { "NDEBUG" }
        flags { "Optimize" }

    project "DeusVultGame"
        kind "ConsoleApp"
        language "C++"
        files {
            "sol2-develop/sol.hpp",
            "Game/**.h",
            "Game/**.cpp"
        }
        links {
            "DeusVultCore",
            "SFML-Graphics",
	    "SFML-Window",
            "lua5.1"
        }

	configuration {"linux"}
            buildoptions {"-std=c++11", "-I/usr/include/lua5.1"}

        configuration "Debug"
        defines { "DEBUG" }
        flags { "Symbols" }

        configuration "Release"
        defines { "NDEBUG" }
        flags { "Optimize" }
