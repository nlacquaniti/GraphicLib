target_sources(${PROJECT_NAME} PRIVATE 
	ShaderImpl.h
	"VertexArrayOpsImpl.h"
	VertexBufferOpsImpl.h
	IndexBufferOpsImpl.h
	
	OpenGLLogSystem.h
	GLFWLogSystem.h
	glad.h
	glfw.h

	WindowImpl.h

	ShaderImpl.cpp
	"VertexArrayOpsImpl.cpp"
	VertexBufferOpsImpl.cpp
	IndexBufferOpsImpl.cpp
	
	WindowImpl.cpp
	OpenGLLogSystem.cpp
	GLFWLogSystem.cpp
)

add_subdirectory(Vendors)

target_compile_definitions(${PROJECT_NAME} PRIVATE OPEN_GL_IMPL)

# GLAD library
add_dependencies(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} PRIVATE glad)

# GLFW Library
add_dependencies(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)