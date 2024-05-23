set(IMGUI_ROOT_DIR ${FETCHCONTENT_BASE_DIR}/imgui-src)

add_executable(DrawImageExample
	main.cpp

	../Common/Window/Public/Window/Window.h
	../Common/Window/Public/Window/Input.h
	../Common/Window/Public/Utils/CallbackHandler.h
	../Common/Window/Public/Utils/InputUtils.h

	../Common/Window/Private/Window.cpp
	../Common/Window/Private/Input.cpp
	../Common/Window/Private/InputImpl.h
	../Common/Window/Private/InputImpl.cpp
	../Common/Window/Private/InputImplUtils.h
	../Common/Window/Private/InputImplUtils.cpp
	../Common/Window/Private/Utils/InputUtils.cpp

  ${IMGUI_ROOT_DIR}/imgui.h
	${IMGUI_ROOT_DIR}/imgui.cpp
	${IMGUI_ROOT_DIR}/imgui_demo.cpp
	${IMGUI_ROOT_DIR}/imgui_draw.cpp
	${IMGUI_ROOT_DIR}/imgui_internal.h
	${IMGUI_ROOT_DIR}/imgui_tables.cpp
	${IMGUI_ROOT_DIR}/imgui_widgets.cpp
	${IMGUI_ROOT_DIR}/imstb_rectpack.h
	${IMGUI_ROOT_DIR}/imstb_textedit.h
	${IMGUI_ROOT_DIR}/imstb_truetype.h
	${IMGUI_ROOT_DIR}/backends/imgui_impl_glfw.h
	${IMGUI_ROOT_DIR}/backends/imgui_impl_glfw.cpp
)

target_include_directories(DrawImageExample PRIVATE
	../Common/Window/Public
	../Common/Window/Private
	../Vendors
    ${IMGUI_ROOT_DIR}/
)

if(GL_ENABLE_OPENGL)
	target_sources(DrawImageExample PRIVATE 
		../Common/Window/Private/OpenGLImpl/WindowImpl.h
		../Common/Window/Private/OpenGLImpl/WindowImpl.cpp

		../Vendors/glad/include/glad/glad.h
		../Vendors/glad/include/KHR/khrplatform.h
		../Vendors/glad/src/glad.c
		${IMGUI_ROOT_DIR}/backends/imgui_impl_opengl3.h
		${IMGUI_ROOT_DIR}/backends/imgui_impl_opengl3.cpp
	)

	target_include_directories(DrawImageExample PRIVATE
		../Vendors/glad/include
	)

	target_compile_definitions(DrawImageExample PRIVATE OPENGL_IMPL)
endif()

target_compile_definitions(DrawImageExample PRIVATE EXEC_PATH="${CMAKE_CURRENT_BINARY_DIR}/")

add_dependencies(DrawImageExample ${PROJECT_NAME})
target_link_libraries(DrawImageExample PRIVATE ${PROJECT_NAME})

target_link_libraries(DrawImageExample PRIVATE glfw)
target_link_libraries(DrawImageExample PRIVATE glm)

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
