add_executable(
        App main.cpp
        Renderer.cpp
        VertexBuffer.cpp
        IndexBuffer.cpp
        VertexArray.cpp
        Shader.cpp
        Texture.cpp
        Timer.cpp
        Entity.cpp
        Cube.cpp
        )

include_directories(../vendor/)
target_link_libraries(App glfw glad GL image imgui)
