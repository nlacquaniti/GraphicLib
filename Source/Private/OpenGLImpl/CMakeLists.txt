target_sources(${PROJECT_NAME} PRIVATE 
	APIImpl.h
	ShaderImpl.h
	VertexArrayImpl.h
	VertexBufferImpl.h
	IndexBufferImpl.h
	OpenGLLogSystem.h
	TextureImpl.h
	FrameBufferImpl.h
	RenderBufferImpl.h
	Utils/TextureImplUtils.h
	Utils/RenderBufferImplUtils.h

	APIImpl.cpp
	ShaderImpl.cpp
	VertexArrayImpl.cpp
	VertexBufferImpl.cpp
	IndexBufferImpl.cpp
	OpenGLLogSystem.cpp
	TextureImpl.cpp
	FrameBufferImpl.cpp
	RenderBufferImpl.cpp
	Utils/TextureImplUtils.cpp
	Utils/RenderBufferImplUtils.cpp

	Vendors/glad/include/glad/glad.h
	Vendors/glad/include/KHR/khrplatform.h
	Vendors/glad/src/glad.c
)

target_include_directories(${PROJECT_NAME} PRIVATE 
	Vendors/glad/include/
)

target_compile_definitions(${PROJECT_NAME} PRIVATE OPENGL_IMPL)