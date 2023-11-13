target_sources(${PROJECT_NAME} PRIVATE 
	ShaderImpl.h
	VertexArrayImpl.h
	VertexBufferImpl.h
	IndexBufferImpl.h
	OpenGLLogSystem.h
	glad.h
	TextureImpl.h

	ShaderImpl.cpp
	VertexArrayImpl.cpp
	VertexBufferImpl.cpp
	IndexBufferImpl.cpp
	
	OpenGLLogSystem.cpp
	TextureImpl.cpp

	Vendors/glad/include/glad/glad.h
	Vendors/glad/include/KHR/khrplatform.h
	Vendors/glad/src/glad.c
)

target_include_directories(${PROJECT_NAME} PRIVATE 
	Vendors/glad/include/
)

target_compile_definitions(${PROJECT_NAME} PRIVATE OPENGL_IMPL)