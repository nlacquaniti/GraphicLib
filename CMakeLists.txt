cmake_minimum_required(VERSION 3.23)

project(GraphicLib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(GL_ENABLE_OPENGL "Use OpenGL has a graphic library" ON)
option(GL_ENABLE_EXAMPLES "Build example projects" OFF)
option(GL_ENABLE_EXAMPLES_SYMLINK "Enable example projects files symlink" ON)


add_library(${PROJECT_NAME} SHARED
	Source/Public/${PROJECT_NAME}/DLL_API.h
	Source/Public/${PROJECT_NAME}/Logger.h
	Source/Public/${PROJECT_NAME}/IndexBuffer.h
	Source/Public/${PROJECT_NAME}/Shader.h
	Source/Public/${PROJECT_NAME}/VertexArray.h
	Source/Public/${PROJECT_NAME}/VertexBuffer.h
	Source/Public/${PROJECT_NAME}/Texture.h
	Source/Public/${PROJECT_NAME}/FrameBuffer.h
	Source/Public/${PROJECT_NAME}/RenderBuffer.h
	Source/Public/${PROJECT_NAME}/Utilities/Array.h
	Source/Public/${PROJECT_NAME}/Utilities/Span.h
	Source/Public/${PROJECT_NAME}/Utilities/TextureUtils.h
	Source/Public/${PROJECT_NAME}/Utilities/RenderBufferUtils.h
	Source/Public/${PROJECT_NAME}/Utilities/ShaderUtils.h

	Source/Private/IExternalLogSystem.h
	Source/Private/IExternalLogSystem.cpp
	Source/Private/IndexBuffer.cpp
	Source/Private/Shader.cpp
	Source/Private/VertexArray.cpp
	Source/Private/VertexBuffer.cpp
	Source/Private/Texture.cpp
	Source/Private/FrameBuffer.cpp
	Source/Private/RenderBuffer.cpp
	Source/Private/Logger.cpp
	Source/Private/InternalLogger.h
	Source/Private/InternalLogger.cpp
	Source/Private/StbImage.h
	Source/Private/FmtFormat.h
	Source/Private/Utilities/TextureUtils.cpp
	Source/Private/Utilities/RenderBufferUtils.cpp
	Source/Private/Utilities/ShaderUtils.cpp

	Source/Private/Vendors/stb/stb_image.h
)

if(GL_ENABLE_OPENGL)
	target_sources(${PROJECT_NAME} PRIVATE 
		Source/Private/OpenGLImpl/APIImpl.h
		Source/Private/OpenGLImpl/ShaderImpl.h
		Source/Private/OpenGLImpl/VertexArrayImpl.h
		Source/Private/OpenGLImpl/VertexBufferImpl.h
		Source/Private/OpenGLImpl/IndexBufferImpl.h
		Source/Private/OpenGLImpl/OpenGLLogSystem.h
		Source/Private/OpenGLImpl/TextureImpl.h
		Source/Private/OpenGLImpl/FrameBufferImpl.h
		Source/Private/OpenGLImpl/RenderBufferImpl.h
		Source/Private/OpenGLImpl/Utils/TextureImplUtils.h
		Source/Private/OpenGLImpl/Utils/RenderBufferImplUtils.h
		Source/Private/OpenGLImpl/Utils/ShaderImplUtils.h
	
		Source/Private/OpenGLImpl/APIImpl.cpp
		Source/Private/OpenGLImpl/ShaderImpl.cpp
		Source/Private/OpenGLImpl/VertexArrayImpl.cpp
		Source/Private/OpenGLImpl/VertexBufferImpl.cpp
		Source/Private/OpenGLImpl/IndexBufferImpl.cpp
		Source/Private/OpenGLImpl/OpenGLLogSystem.cpp
		Source/Private/OpenGLImpl/TextureImpl.cpp
		Source/Private/OpenGLImpl/FrameBufferImpl.cpp
		Source/Private/OpenGLImpl/RenderBufferImpl.cpp
		Source/Private/OpenGLImpl/Utils/TextureImplUtils.cpp
		Source/Private/OpenGLImpl/Utils/RenderBufferImplUtils.cpp
		Source/Private/OpenGLImpl/Utils/ShaderImplUtils.cpp
	
		Source/Private/OpenGLImpl/Vendors/glad/include/glad/glad.h
		Source/Private/OpenGLImpl/Vendors/glad/include/KHR/khrplatform.h
		Source/Private/OpenGLImpl/Vendors/glad/src/glad.c
	)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC 
	Source/Public
)
target_include_directories(${PROJECT_NAME} PRIVATE 
	Source/Private
	Source/Private/Vendors
)
if(GL_ENABLE_OPENGL)
	target_include_directories(${PROJECT_NAME} PRIVATE 
		Source/Private/OpenGLImpl/Vendors/glad/include/
	)
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE DLL_EXPORT)
if(GL_ENABLE_OPENGL)
	target_compile_definitions(${PROJECT_NAME} PRIVATE OPENGL_IMPL)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX Debug)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	target_compile_options(${PROJECT_NAME} PRIVATE 
	/Wall 
	/WX 
	/wd4820
	/wd5045
	/wd4514
)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	target_compile_options(${PROJECT_NAME} PRIVATE 
		-Wall 
		-Wextra
		-Wshadow
		-Wconversion
		-Wpedantic
		-Werror
		-Wno-c++98-compat
		-Wno-c++98-compat-pedantic
		-Wno-unsafe-buffer-usage
	)
endif()

target_link_libraries(
	${PROJECT_NAME} PRIVATE 
	fmt::fmt
	assimp
)

if(GL_ENABLE_EXAMPLES)
	add_subdirectory(Examples)
endif()
add_subdirectory(Source/Private/Vendors)