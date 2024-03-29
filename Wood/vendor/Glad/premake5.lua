project "glad"
	kind "StaticLib"
	language "C"

	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

	files
	{
		"include/glad/glad.h",
		"include/KHR/khrplatform.h",
    "src/glad.c",
  }
  
  includedirs {
    "include"
  }

	filter "system:macosx"
		systemversion "latest"
		staticruntime "On"