# CMakeList.txt : CMake project for ImageSubjectSequence, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
project(Raytracing)

# Add source to this project's executable
add_executable (Raytracing
	"main.cpp"
	"src/image/Image.cpp"
	"src/math/Point.cpp" "src/math/Vector.cpp" "src/math/Matrix.cpp"
	"src/texture/Color.cpp" "src/texture/Material.cpp"
	"src/engine/Ray.cpp" "src/engine/Entity.cpp" "src/engine/Object.cpp" "src/engine/Light.cpp" "src/engine/Camera.cpp" "src/engine/Scene.cpp" "src/engine/Renderer.cpp"
	"src/primitives/Sphere.cpp"
	"src/ui/ImGUI_context.cpp"
	"src/ui/OpenGL_context.cpp"
	"src/ui/window.cpp"
	)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui")
set(DEPENDENCIES_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb/")
target_include_directories(Raytracing PUBLIC  ${DEPENDENCIES_HEADERS} )
target_link_libraries(Raytracing PUBLIC
		glfw
		glad
        imgui
 )

# TODO: Add tests and install targets if needed.
