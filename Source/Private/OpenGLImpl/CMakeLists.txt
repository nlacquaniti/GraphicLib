target_sources(${PROJECT_NAME} PRIVATE 
	ShaderImpl.h
	ShaderImpl.cpp
	VertexArrayImpl.h
	VertexArrayImpl.h
	VertexArrayImpl.cpp
	VertexBufferImpl.h
	VertexBufferImpl.cpp
	IndexBufferImpl.h
	IndexBufferImpl.cpp
	WindowImpl.h
	WindowImpl.cpp
	OpenGLLogSystem.h
	OpenGLLogSystem.cpp
	GLFWLogSystem.h
	GLFWLogSystem.cpp
	glad.h
	glfw.h
)

add_subdirectory(Vendors)

target_compile_definitions(${PROJECT_NAME} PRIVATE OPEN_GL_IMPL)

# GLAD library
add_dependencies(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} PRIVATE glad)

# GLFW Library
add_dependencies(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)