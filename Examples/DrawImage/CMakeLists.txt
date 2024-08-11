set(GL_EXAMPLES_IMGUI_ROOT_DIR NONE CACHE STRING "Set IMGUI root directory")
set(GL_EXAMPLES_COMMON_DIR ../Common)
set(GL_EXAMPLES_VENDORS_DIR ../Vendors)

add_executable(DrawImageExample
	main.cpp

	${GL_EXAMPLES_COMMON_DIR}/Window/Public/Window/Window.h
	${GL_EXAMPLES_COMMON_DIR}/Window/Public/Window/Input.h
	${GL_EXAMPLES_COMMON_DIR}/Window/Public/Utils/CallbackHandler.h
	${GL_EXAMPLES_COMMON_DIR}/Window/Public/Utils/InputUtils.h

	${GL_EXAMPLES_COMMON_DIR}/Window/Private/Window.cpp
	${GL_EXAMPLES_COMMON_DIR}/Window/Private/Input.cpp
	${GL_EXAMPLES_COMMON_DIR}/Window/Private/InputImpl.h
	${GL_EXAMPLES_COMMON_DIR}/Window/Private/InputImpl.cpp
	${GL_EXAMPLES_COMMON_DIR}/Window/Private/InputImplUtils.h
	${GL_EXAMPLES_COMMON_DIR}/Window/Private/InputImplUtils.cpp
	${GL_EXAMPLES_COMMON_DIR}/Window/Private/Utils/InputUtils.cpp

	${GL_EXAMPLES_IMGUI_ROOT_DIR}/imgui.h
	${GL_EXAMPLES_IMGUI_ROOT_DIR}/imgui.cpp
	${GL_EXAMPLES_IMGUI_ROOT_DIR}/imgui_demo.cpp
	${GL_EXAMPLES_IMGUI_ROOT_DIR}/imgui_draw.cpp
	${GL_EXAMPLES_IMGUI_ROOT_DIR}/imgui_internal.h
	${GL_EXAMPLES_IMGUI_ROOT_DIR}/imgui_tables.cpp
	${GL_EXAMPLES_IMGUI_ROOT_DIR}/imgui_widgets.cpp
	${GL_EXAMPLES_IMGUI_ROOT_DIR}/imstb_rectpack.h
	${GL_EXAMPLES_IMGUI_ROOT_DIR}/imstb_textedit.h
	${GL_EXAMPLES_IMGUI_ROOT_DIR}/imstb_truetype.h
	${GL_EXAMPLES_IMGUI_ROOT_DIR}/backends/imgui_impl_glfw.h
	${GL_EXAMPLES_IMGUI_ROOT_DIR}/backends/imgui_impl_glfw.cpp
)

target_include_directories(DrawImageExample PRIVATE
	${GL_EXAMPLES_COMMON_DIR}/Window/Public
	${GL_EXAMPLES_COMMON_DIR}/Window/Private
	${GL_EXAMPLES_VENDORS_DIR}/
    ${GL_EXAMPLES_IMGUI_ROOT_DIR}/
)

if(GL_ENABLE_OPENGL)
	target_sources(DrawImageExample PRIVATE 
		${GL_EXAMPLES_COMMON_DIR}/Window/Private/OpenGLImpl/WindowImpl.h
		${GL_EXAMPLES_COMMON_DIR}/Window/Private/OpenGLImpl/WindowImpl.cpp

		${GL_EXAMPLES_VENDORS_DIR}/glad/include/glad/glad.h
		${GL_EXAMPLES_VENDORS_DIR}/glad/include/KHR/khrplatform.h
		${GL_EXAMPLES_VENDORS_DIR}/glad/src/glad.c
		${GL_EXAMPLES_IMGUI_ROOT_DIR}/backends/imgui_impl_opengl3.h
		${GL_EXAMPLES_IMGUI_ROOT_DIR}/backends/imgui_impl_opengl3.cpp
	)

	target_include_directories(DrawImageExample PRIVATE
		${GL_EXAMPLES_VENDORS_DIR}/glad/include
	)

	target_compile_definitions(DrawImageExample PRIVATE OPENGL_IMPL)
endif()

target_compile_definitions(DrawImageExample PRIVATE EXEC_PATH="$<TARGET_FILE_DIR:DrawImageExample>/")

add_dependencies(DrawImageExample ${PROJECT_NAME})

find_package(GLFW3 REQUIRED)
find_package(glm REQUIRED)

target_link_libraries(DrawImageExample PRIVATE 
	${PROJECT_NAME}
	glfw
	glm::glm
)

add_custom_command(
	TARGET DrawImageExample 
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
		$<TARGET_FILE:${PROJECT_NAME}>
		$<TARGET_FILE_DIR:DrawImageExample>
)

add_custom_command(
	TARGET DrawImageExample
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_CURRENT_SOURCE_DIR}/Resources
		$<TARGET_FILE_DIR:DrawImageExample>/Resources
)

add_custom_command(
	TARGET DrawImageExample
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
		${CMAKE_CURRENT_SOURCE_DIR}/imgui.ini
		$<TARGET_FILE_DIR:DrawImageExample>/imgui.ini
)

if(GL_ENABLE_EXAMPLES_SYMLINK)
	add_custom_command(
	    TARGET DrawImageExample
	    POST_BUILD
	    COMMAND ${CMAKE_COMMAND} -E create_symlink 
			${CMAKE_CURRENT_SOURCE_DIR}/imgui.ini
			$<TARGET_FILE_DIR:DrawImageExample>/imgui.ini
	    COMMENT "Creating symbolic link: ${SYMLINK_DEST} -> ${SOURCE_FILE}"
	)
endif()
