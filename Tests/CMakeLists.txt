
add_executable(GL_TESTS 
    VertexBufferTests.h
    VertexBufferTests.cpp
    main.cpp
)

add_dependencies(GL_TESTS ${PROJECT_NAME})
target_link_libraries(GL_TESTS PRIVATE 
	${PROJECT_NAME}
)
add_custom_command(
	TARGET GL_TESTS 
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
		$<TARGET_FILE:${PROJECT_NAME}>
		$<TARGET_FILE_DIR:GL_TESTS>
)


