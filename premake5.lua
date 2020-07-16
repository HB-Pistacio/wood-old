-- RUN THIS TO CONSTRUCT A MAKE FILE:  
-- ./vendor/bin/premake/premake5 gmake2  
-- Then just run "make" in the root folder

workspace "Wood"
architecture "x86_64"
configurations { "Debug", "Release", "Dist" }

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Wood"
  kind "SharedLib"
  language "C++"
  location "Wood"

  targetdir ("bin/" .. outputDir .. "/%{prj.name}")
  objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

  pchheader "pchwd.h"

  files {
    "%{prj.name}/src/**.h",
    "%{prj.name}/src/**.cpp"
  }

  includedirs {
    "%{prj.name}/src",
    "%{prj.name}/vendor/spdlog/include"
  }

  filter "system:macosx"
    cppdialect "C++17"
    staticruntime "On"
    systemversion "latest"
    
    defines {
      "WD_PLATFORM_MACOS",
      "WD_BUILD_DYLIB"
    }

    postbuildcommands {
      ("{MKDIR} ../bin/" .. outputDir .. "/Sandbox"),
      ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputDir .. "/Sandbox/libWood.dylib")
    }

  filter "configurations:Debug"
    defines "WD_DEBUG"
    symbols "On"
  
  filter "configurations:Release"
    defines "WD_RELEASE"
    optimize "On"
  
  filter "configurations:Dist"
    defines "WD_DIST"
    optimize "On"

project "Sandbox"
  kind "ConsoleApp"
  language "C++"
  location "Sandbox"

  targetdir ("bin/" .. outputDir .. "/%{prj.name}")
  objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

  files {
    "%{prj.name}/src/**.h",
    "%{prj.name}/src/**.cpp"
  }

  includedirs {
    "Wood/vendor/spdlog/include",
    "Wood/src"
  }

  links { "Wood" }

  filter "system:macosx"
    cppdialect "C++17"
    staticruntime "On"
    systemversion "latest"
    
    defines {
      "WD_PLATFORM_MACOS"
    }

  filter "configurations:Debug"
    defines "WD_DEBUG"
    symbols "On"
  
  filter "configurations:Release"
    defines "WD_RELEASE"
    optimize "On"
  
  filter "configurations:Dist"
    defines "WD_DIST"
    optimize "On"