solution "DeusVult"
    configurations { "Debug", "Release" }

    project "DeusVultCore"
        kind "StaticLib"
        language "C++"
        files {
            "sol2-develop/sol.hpp",
            "Core/**.h",
            "Core/**.cpp",
            "spine/spine-c/**.c",
            "spine/spine-sfml/**.cpp"
        }
        links {
           "lua5.1",
        }
        includedirs {
           "spine/spine-sfml/src",
           "spine/spine-c/spine-c/include"
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
            "Game/**.cpp",
            "spine/spine-c/src/spine/**.c",
            "spine/spine-sfml/src/spine/**.cpp"
        }
        links {
            "DeusVultCore",
            "sfml-graphics",
            "sfml-window",
            "sfml-system",
            "lua5.1"
        }
        includedirs {
           "spine/spine-sfml/src",
           "spine/spine-c/spine-c/include"
        }

	configuration {"linux"}
            buildoptions {"-std=c++14"}

        configuration "Debug"
        defines { "DEBUG" }
        flags { "Symbols" }

        configuration "Release"
        defines { "NDEBUG" }
        flags { "Optimize" }
