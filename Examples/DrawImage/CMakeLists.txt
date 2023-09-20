add_executable(DrawImageExample
	main.cpp
)

target_link_libraries(DrawImageExample PRIVATE ${PROJECT_NAME})

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
	COMMAND ${CMAKE_COMMAND} -E copy
		$<TARGET_FILE:glfw>
		$<TARGET_FILE_DIR:DrawImageExample>
	)
add_custom_command(
	TARGET DrawImageExample
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
		$<TARGET_FILE:glad>
		$<TARGET_FILE_DIR:DrawImageExample>
	)