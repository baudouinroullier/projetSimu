macro (add_exec name src)
	add_executable(${name} ${src})
	target_link_libraries(${name} ${SFML_LIBRARIES})
endmacro (add_exec)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "..")

add_exec("testFPS" "testfps.cpp")
add_exec("testSFML" "testsfml.cpp")

add_exec("testMap" "testmap.cpp;../src/drawlib/map.cpp")
add_exec("testAnimatedSprite" "testanimatedsprite.cpp;../src/drawlib/animatedsprite.cpp")
add_exec("testParticleEffect" "testparticleeffect.cpp;../src/drawlib/particleengine.cpp;../src/drawlib/particletemplate.cpp;../src/drawlib/particleeffect.cpp;../src/drawlib/particle.cpp")
