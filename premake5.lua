workspace "AdventOfCode"
    architecture "x64"
    configurations { "build" }

    project "AdventOfCode"
        language "C++"
        cppdialect "C++20"
        kind "ConsoleApp"

        targetdir ("bin/")
        objdir ("bin-int/")
        
        optimize "speed"

        files
        {
            "src/**.h",
            "src/**.cpp",
        }
        
        includedirs
        {
            "src/"
        }
