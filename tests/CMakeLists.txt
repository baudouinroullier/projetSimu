macro (add_exec name src)
	add_executable(${name} ${src})
	target_link_libraries(${name} ${SFML_LIBRARIES})
endmacro (add_exec)


add_exec("testFPS" "test_fps.cpp")
add_exec("testSFML" "test_sfml.cpp")
