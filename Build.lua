workspace "PingPongLite"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "App"

   -- Global Output Directory Variable
   OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }
   filter {} -- Clear filter

   -- Solution Items (Visible in VS)
   files { ".clang-format", ".gitignore", "README.md" }
   vpaths {
      ["Solution Items/*"] = { ".clang-format", ".gitignore", "README.md"}
   }

project "PingPongLite"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   staticruntime "off"

   -- Files and Includes
   files { "PingPongLite/Source/**.h", "PingPongLite/Source/**.cpp" }
   includedirs { 
      "%{wks.location}/dep/SDL3_image-3.4.0/include",
      "%{wks.location}/dep/SDL3-3.4.0/include",
      "%{wks.location}/dep/SDL3_ttf-3.2.2/include",
      "%{wks.location}/dep/SDL3_mixer-3.2.0/include",
      "PingPongLite/Source"
   }

   -- Binary and Intermediate locations
   targetdir ("Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   -- Linker Settings (Library Search Paths)
   libdirs { 
      "%{wks.location}/dep/SDL3_image-3.4.0/lib/x64",
      "%{wks.location}/dep/SDL3-3.4.0/lib/x64",
      "%{wks.location}/dep/SDL3_ttf-3.2.2/lib/x64",
      "%{wks.location}/dep/SDL3_mixer-3.2.0/lib/x64"
   }

   -- Libraries to link against
   links { 
      "SDL3", 
      "SDL3_image", 
      "SDL3_ttf", 
      "SDL3_mixer" 
   }

   --Windows copy dependencies
   filter "system:windows"
      -- {COPY} is a Premake token, but for complex folder structures, 
      -- standard shell commands are often more reliable.
      postbuildcommands {
         -- Copy all DLLs from the dependency folders to the target directory
         "{COPYDIR} \"%{wks.location}/dep/SDL3-3.4.0/lib/x64/*.dll\" \"%{cfg.targetdir}\"",
         "{COPYDIR} \"%{wks.location}/dep/SDL3_image-3.4.0/lib/x64/*.dll\" \"%{cfg.targetdir}\"",
         "{COPYDIR} \"%{wks.location}/dep/SDL3_ttf-3.2.2/lib/x64/*.dll\" \"%{cfg.targetdir}\"",
         "{COPYDIR} \"%{wks.location}/dep/SDL3_mixer-3.2.0/lib/x64/*.dll\" \"%{cfg.targetdir}\"",
         
         -- Copy your Assets folder (assumes Assets is in your project root)
         -- Using xcopy style logic to ensure the folder structure is maintained
         "IF EXIST \"%{wks.location}/Assets\" (xcopy /Q /E /Y /I \"%{wks.location}/Assets\" \"%{cfg.targetdir}/assets\")"
      }
   
   --Linux copy dependencies
   filter "system:linux"
      postbuildcommands {
         -- Ensure the target directory and Assets folder exist
         "mkdir -p \"%{cfg.targetdir}/Assets\"",

         -- Copy all shared objects (.so) from the dependency folders
         "cp -f \"%{wks.location}/dep/SDL3-3.4.0/lib/x64/\"*.so* \"%{cfg.targetdir}/\"",
         "cp -f \"%{wks.location}/dep/SDL3_image-3.4.0/lib/x64/\"*.so* \"%{cfg.targetdir}/\"",
         "cp -f \"%{wks.location}/dep/SDL3_ttf-3.2.2/lib/x64/\"*.so* \"%{cfg.targetdir}/\"",
         "cp -f \"%{wks.location}/dep/SDL3_mixer-3.2.0/lib/x64/\"*.so* \"%{cfg.targetdir}/\"",
         
         -- Copy Assets folder content
         "cp -rb \"%{wks.location}/PingPongLite/Assets/\"* \"%{cfg.targetdir}/Assets/\""
      }

   -- Configuration Specific Filters
   filter "system:windows"
       defines { "WINDOWS" }

   filter "configurations:Debug"
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"

   filter "configurations:Dist"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"