cmake_minimum_required (VERSION 3.10)

add_library(VulkanLib SHARED IMPORTED)
#set_target_properties(VulkanLib PROPERTIES IMPORTED_LOCATION "./macos/libvulkan.dylib")

#link_directories("./macos/")

#target_link_libraries(GLFWVulkan "-framework AppKit -framework OpenGL -framework IOKit -framework CoreVideo")
