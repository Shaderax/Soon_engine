#pragma once

// Vulkan
#if defined(USE_VULKAN)
	#warning "ole"
	#include "Graphics/GLFW/GLFWVulkan/GLFWVulkan.hpp"
	#include "Graphics/GLFW/GLFWVulkan/GLFWVulkanHints.hpp"
#else
	#warning "Spa bon"
// OpenGL
	#include "Graphics/GLFW/GLFWOpenGL/GLFWOpenGLHints.hpp"
	#include "Graphics/GLFW/GLFWOpenGL/GLFWOpenGLContext.hpp"
#endif
