#pragma once

// Vulkan
#if defined(USE_VULKAN)
	#include "Graphics/GLFW/GLFWVulkan/GLFWVulkanHints.hpp"
	#include "Graphics/GLFW/GLFWVulkan/GLFWVulkan.hpp"
	#define GLFW_INCLUDE_VULKAN
#else
// OpenGL
	#include "Graphics/GLFW/GLFWOpenGL/GLFWOpenGLHints.hpp"
	#include "Graphics/GLFW/GLFWOpenGL/GLFWOpenGLContext.hpp"
#endif
