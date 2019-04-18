#pragma once

#define USE_VULKAN 1
// Vulkan
#if defined(USE_VULKAN)
#warning "ole"
	#define GLFW_INCLUDE_VULKAN 1
	#include "Graphics/GLFW/GLFWVulkan/GLFWVulkanHints.hpp"
	#include "Graphics/GLFW/GLFWVulkan/GLFWVulkan.hpp"
#else
// OpenGL
	#include "Graphics/GLFW/GLFWOpenGL/GLFWOpenGLHints.hpp"
	#include "Graphics/GLFW/GLFWOpenGL/GLFWOpenGLContext.hpp"
#endif
