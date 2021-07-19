# CMakeList.txt : CMake project for ImageSubjectSequence, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable
add_executable (Raytracing
	"main.cpp"
	"src/image/Image.cpp"
	"src/math/Point.cpp" "src/math/Vector.cpp" "src/math/Matrix.cpp"
	"src/engine/Ray.cpp" "src/engine/Entity.cpp"
)

# TODO: Add tests and install targets if needed.
