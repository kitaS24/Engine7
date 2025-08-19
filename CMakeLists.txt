cmake_minimum_required(VERSION 4.0)
project(Engine7)

set(CMAKE_CXX_STANDARD 17)

# ImGui
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/Engine/include/ImGui)
set(IMGUI_SRC
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

add_executable(Engine7 main.cpp ${IMGUI_SRC})

include_directories(Engine/)
include_directories(Engine/Core)
include_directories(Engine/Ents)
include_directories(Engine/subsys)


include_directories(Engine/include/ImGui/backends)
include_directories(Engine/include/ImGui/misc)
include_directories(Engine/include/ImGui/misc/cpp)
include_directories(Engine/include/ImGui/misc/debuggers)
include_directories(Engine/include/ImGui/misc/fonts)
include_directories(Engine/include/ImGui/misc/freetype)
include_directories(Engine/include/ImGui/misc/single_file)

set(GlInclude "Engine/include/") # GLFW,GLEW include folder (include/GLEW/,include/GLFW/)
include_directories(${GlInclude})
find_package(OpenGL REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE external/glfw/include)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/${GlInclude}/GLFW/glfw3.lib ${CMAKE_SOURCE_DIR}/${GlInclude}/GLEW/glew32s.lib OpenGL::GL)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
)
