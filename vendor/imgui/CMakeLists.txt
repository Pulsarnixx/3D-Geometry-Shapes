add_library(
        imgui STATIC
        imgui_demo.cpp
        imgui_draw.cpp
        imgui_tables.cpp
        imgui_widgets.cpp
        imgui.cpp
        imgui_impl_glfw.cpp
        imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC ${CMAKE_SOURCE_DIR}/vendor/glfw/include)