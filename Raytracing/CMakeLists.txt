cmake_minimum_required (VERSION 3.8)

add_executable (Raytracing
	"main.cpp"
	"src/image/Image.cpp"
	"src/math/Point.cpp" "src/math/Vector.cpp" "src/math/Matrix.cpp"
	"src/texture/Color.cpp" "src/texture/Material.cpp"
	"src/engine/Ray.cpp" "src/engine/Entity.cpp" "src/engine/Object.cpp" "src/engine/Light.cpp" "src/engine/Camera.cpp" "src/engine/Scene.cpp" "src/engine/Renderer.cpp"
	"src/primitives/Sphere.cpp" "src/primitives/Plane.cpp" "src/primitives/Cube.cpp" "src/primitives/Cone.cpp"
	"src/lights/AmbientLight.cpp" "src/lights/PointLight.cpp"
	"src/ui/ImGUI_context.cpp" "src/ui/OpenGL_context.cpp" "src/ui/window.cpp"
    "src/primitives/Square.cpp" "src/primitives/Cylinder.cpp" "src/primitives/Triangle.cpp" "src/engine/Serializer.cpp"  "src/texture/Texture.cpp" "src/helpers/Utility.cpp" "src/helpers/IdGenerator.cpp")

add_subdirectory("vendor")

target_link_libraries(Raytracing PUBLIC
		glfw
		glad
        imgui
 )

 target_include_directories(Raytracing PRIVATE
        "vendor/nlohmann"
)