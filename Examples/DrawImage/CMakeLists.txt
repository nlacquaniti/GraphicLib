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
	../Common/Window/Private/glfw.h

	../Vendors/imgui/imgui.h
	../Vendors/imgui/imgui.cpp
	../Vendors/imgui/imgui_demo.cpp
	../Vendors/imgui/imgui_draw.cpp
	../Vendors/imgui/imgui_internal.h
	../Vendors/imgui/imgui_tables.cpp
	../Vendors/imgui/imgui_widgets.cpp
	../Vendors/imgui/imstb_rectpack.h
	../Vendors/imgui/imstb_textedit.h
	../Vendors/imgui/imstb_truetype.h
	../Vendors/imgui/backends/imgui_impl_glfw.h
	../Vendors/imgui/backends/imgui_impl_glfw.cpp
)

target_include_directories(DrawImageExample PRIVATE
	../Common/Window/Public
	../Common/Window/Private
	../Vendors
	../Vendors/glfw/include
	../Vendors/glm
	../Vendors/imgui
)

if(GL_ENABLE_OPENGL)
	target_sources(DrawImageExample PRIVATE 
		../Common/Window/Private/OpenGLImpl/glad.h
		../Common/Window/Private/OpenGLImpl/WindowImpl.h
		../Common/Window/Private/OpenGLImpl/WindowImpl.cpp

		../Vendors/glad/include/glad/glad.h
		../Vendors/glad/include/KHR/khrplatform.h
		../Vendors/glad/src/glad.c
		../Vendors/imgui/backends/imgui_impl_opengl3.h
		../Vendors/imgui/backends/imgui_impl_opengl3.cpp
	)

	target_include_directories(DrawImageExample PRIVATE
		../Vendors/glad/include
	)

	target_compile_definitions(DrawImageExample PRIVATE OPENGL_IMPL)
endif()

add_dependencies(DrawImageExample ${PROJECT_NAME})
target_link_libraries(DrawImageExample PRIVATE ${PROJECT_NAME})

add_dependencies(DrawImageExample glfw)
target_link_libraries(DrawImageExample PRIVATE glfw)

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
	    COMMAND ${CMAKE_COMMAND} -E copy_if_different
			$<TARGET_FILE:glfw>
			$<TARGET_FILE_DIR:DrawImageExample>
)