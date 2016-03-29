project(projetSimu)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(src/ SRC_LIST)
set(EXECUTABLE_NAME ${PROJECT_NAME})

macro (add_exec name src)
	add_executable(${name} ${src})
	target_link_libraries(${name} ${SFML_LIBRARIES})
endmacro (add_exec)


set(CMAKE_CXX_FLAGS "-std=c++11 -g")
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)

#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  add_exec(${PROJECT_NAME} ${SRC_LIST})
  add_subdirectory(tests)
endif()

