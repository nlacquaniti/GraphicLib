add_library(${PROJECT_NAME} SHARED
	Public/${PROJECT_NAME}/DLL_API.h
	Public/${PROJECT_NAME}/Logger.h
	Public/${PROJECT_NAME}/IndexBuffer.h
	Public/${PROJECT_NAME}/Shader.h
	Public/${PROJECT_NAME}/VertexArray.h
	Public/${PROJECT_NAME}/VertexBuffer.h
	Public/${PROJECT_NAME}/Window.h
	Public/${PROJECT_NAME}/Texture.h
	Public/${PROJECT_NAME}/Utilities/Array.h
	Public/${PROJECT_NAME}/Utilities/Span.h
	Public/${PROJECT_NAME}/Utilities/TextureUtils.h

	Private/IExternalLogSystem.h
	Private/IExternalLogSystem.cpp
	Private/IndexBuffer.cpp
	Private/Shader.cpp
	Private/VertexArray.cpp
	Private/VertexBuffer.cpp
	Private/Logger.cpp
	Private/InternalLogger.h
	Private/InternalLogger.cpp
	Private/Window.cpp
	Private/Texture.cpp
	Private/StbImage.h
	Private/Utilities/TextureUtils.cpp

	Private/Vendor/stb/stb_image.h
)

target_include_directories(${PROJECT_NAME} PUBLIC 
	Public
)
target_include_directories(${PROJECT_NAME} PRIVATE 
	Private
	Private/Vendor
)

target_compile_definitions(${PROJECT_NAME} PRIVATE DLL_EXPORT)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
set_target_properties(${PROJECT_NAME} PROPERTIES
    COMPILE_OPTIONS 
	"-Wall;-Wextra;-Wshadow;-Wconversion;-Wpedantic;-Werror;-Wno-c++98-compat;-Wno-c++98-compat-pedantic;-Wno-unsafe-buffer-usage"
)
endif()

if(GL_ENABLE_OPEN_GL)
	add_custom_command(
	    TARGET ${PROJECT_NAME}
	    POST_BUILD
	    COMMAND ${CMAKE_COMMAND} -E copy_if_different
			$<TARGET_FILE:glfw>
			$<TARGET_FILE_DIR:${PROJECT_NAME}>
	)
	add_custom_command(
	    TARGET ${PROJECT_NAME}
	    POST_BUILD
	    COMMAND ${CMAKE_COMMAND} -E copy_if_different
			$<TARGET_FILE:glad>
			$<TARGET_FILE_DIR:${PROJECT_NAME}>
	)
endif()

add_subdirectory(Private)