workspace "AdventOfCode"
    architecture "x64"
    configurations { "build" }

    project "AdventOfCode"
        language "C++"
        kind "ConsoleApp"
        location "AdventOfCode"

        targetdir ("bin/")
        objdir ("bin-int/")

        files
        {
            "src/**.h",
            "src/**.cpp",
        }
        
        includedirs
        {
            "src/"
        }
