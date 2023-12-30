add_library(${PROJECT_NAME} SHARED
	Public/${PROJECT_NAME}/DLL_API.h
	Public/${PROJECT_NAME}/Logger.h
	Public/${PROJECT_NAME}/IndexBuffer.h
	Public/${PROJECT_NAME}/Shader.h
	Public/${PROJECT_NAME}/VertexArray.h
	Public/${PROJECT_NAME}/VertexBuffer.h
	Public/${PROJECT_NAME}/Texture.h
	Public/${PROJECT_NAME}/FrameBuffer.h
	Public/${PROJECT_NAME}/RenderBuffer.h
	Public/${PROJECT_NAME}/Utilities/Array.h
	Public/${PROJECT_NAME}/Utilities/Span.h
	Public/${PROJECT_NAME}/Utilities/TextureUtils.h
	Public/${PROJECT_NAME}/Utilities/RenderBufferUtils.h
	Public/${PROJECT_NAME}/Utilities/ShaderUtils.h

	Private/IExternalLogSystem.h
	Private/IExternalLogSystem.cpp
	Private/IndexBuffer.cpp
	Private/Shader.cpp
	Private/VertexArray.cpp
	Private/VertexBuffer.cpp
	Private/Texture.cpp
	Private/FrameBuffer.cpp
	Private/RenderBuffer.cpp
	Private/Logger.cpp
	Private/InternalLogger.h
	Private/InternalLogger.cpp
	Private/StbImage.h
	Private/Utilities/TextureUtils.cpp
	Private/Utilities/RenderBufferUtils.cpp
	Private/Utilities/ShaderUtils.cpp

	Private/Vendors/stb/stb_image.h
)

if(GL_ENABLE_OPENGL)
	target_sources(${PROJECT_NAME} PRIVATE 
		Private/OpenGLImpl/APIImpl.h
		Private/OpenGLImpl/ShaderImpl.h
		Private/OpenGLImpl/VertexArrayImpl.h
		Private/OpenGLImpl/VertexBufferImpl.h
		Private/OpenGLImpl/IndexBufferImpl.h
		Private/OpenGLImpl/OpenGLLogSystem.h
		Private/OpenGLImpl/TextureImpl.h
		Private/OpenGLImpl/FrameBufferImpl.h
		Private/OpenGLImpl/RenderBufferImpl.h
		Private/OpenGLImpl/Utils/TextureImplUtils.h
		Private/OpenGLImpl/Utils/RenderBufferImplUtils.h
		Private/OpenGLImpl/Utils/ShaderImplUtils.h
	
		Private/OpenGLImpl/APIImpl.cpp
		Private/OpenGLImpl/ShaderImpl.cpp
		Private/OpenGLImpl/VertexArrayImpl.cpp
		Private/OpenGLImpl/VertexBufferImpl.cpp
		Private/OpenGLImpl/IndexBufferImpl.cpp
		Private/OpenGLImpl/OpenGLLogSystem.cpp
		Private/OpenGLImpl/TextureImpl.cpp
		Private/OpenGLImpl/FrameBufferImpl.cpp
		Private/OpenGLImpl/RenderBufferImpl.cpp
		Private/OpenGLImpl/Utils/TextureImplUtils.cpp
		Private/OpenGLImpl/Utils/RenderBufferImplUtils.cpp
		Private/OpenGLImpl/Utils/ShaderImplUtils.cpp
	
		Private/OpenGLImpl/Vendors/glad/include/glad/glad.h
		Private/OpenGLImpl/Vendors/glad/include/KHR/khrplatform.h
		Private/OpenGLImpl/Vendors/glad/src/glad.c
	)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC 
	Public
)
target_include_directories(${PROJECT_NAME} PRIVATE 
	Private
	Private/Vendors
)
if(GL_ENABLE_OPENGL)
	target_include_directories(${PROJECT_NAME} PRIVATE 
		Private/OpenGLImpl/Vendors/glad/include/
	)
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE DLL_EXPORT)
if(GL_ENABLE_OPENGL)
	target_compile_definitions(${PROJECT_NAME} PRIVATE OPENGL_IMPL)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX Debug)
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	set_target_properties(${PROJECT_NAME} PROPERTIES
	    COMPILE_OPTIONS 
		"-Wall;-Wextra;-Wshadow;-Wconversion;-Wpedantic;-Werror;-Wno-c++98-compat;-Wno-c++98-compat-pedantic;-Wno-unsafe-buffer-usage;"
	)
endif()

add_subdirectory(Private/Vendors/fmt)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt-header-only)