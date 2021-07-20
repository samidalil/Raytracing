cmake_minimum_required(VERSION 3.19)

project(imgui)


file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"  "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

add_library(imgui ${SOURCES} )


set(DEPENDENCIES_HEADERS
			"${CMAKE_CURRENT_SOURCE_DIR}/"
			"${CMAKE_CURRENT_SOURCE_DIR}/include/"			
       
)

target_include_directories(imgui PUBLIC  ${DEPENDENCIES_HEADERS} )


target_link_libraries(imgui PUBLIC
		glfw
		glad
  )