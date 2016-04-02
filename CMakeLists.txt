project(projetSimu)
cmake_minimum_required(VERSION 2.8)
set(EXECUTABLE_NAME ${PROJECT_NAME})


set(CMAKE_CXX_FLAGS "-std=c++11 -g")
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)

file(GLOB_RECURSE SRC_LIST src/*)


#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  add_executable(${PROJECT_NAME} ${SRC_LIST})
  target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
  add_subdirectory(tests)
endif()
