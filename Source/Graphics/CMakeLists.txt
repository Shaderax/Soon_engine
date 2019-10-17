cmake_minimum_required (VERSION 3.10)

add_subdirectory(GLFW)
add_subdirectory(Vulkan)
add_subdirectory(Materials)

add_library(Graphics INTERFACE)

#target_link_libraries(Graphics INTERFACE GraphicsGLFW GraphicsVulkan Materials)
