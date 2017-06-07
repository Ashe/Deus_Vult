solution "DeusVult"
    configurations { "Debug", "Release" }

    project "DeusVultCore"
        kind "StaticLib"
        language "C++"
        files {
            "sol2-develop/sol.hpp",
            "Core/**.h",
            "Core/**.cpp"
        }
        links {
           "lua5.1",
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
            "Game/**.h",
            "Game/**.cpp"
        }
        links {
            "DeusVultCore",
            "sfml-graphics",
	    "sfml-window",
            "sfml-system",
            "lua5.1"
        }

	configuration {"linux"}
            buildoptions {"-std=c++14"}

        configuration "Debug"
        defines { "DEBUG" }
        flags { "Symbols" }

        configuration "Release"
        defines { "NDEBUG" }
        flags { "Optimize" }
