#include <iostream>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <GLFW/glfw3.h>
#include <Glad/glad.h>

int main()
{
	const auto logger = spdlog::stdout_color_mt("Console");
	logger->set_level(spdlog::level::trace);
	logger->set_pattern("%^[%T] %n: %v%$");
	logger->set_error_handler([](const std::string& message)
	{
		std::cerr << "Logging-Error: " << message << std::endl;
	});

	set_default_logger(logger);

	if (not glfwInit())
	{
		spdlog::error("Failed to initialize GLFW");
		return 1;
	}

	glfwSetErrorCallback([](const int errorCode, const char* errorMessage)
	{
		spdlog::error("GLFW-Error ({0}): {1}", errorCode, errorMessage);
	});

	constexpr auto initialWindowWidth = 800;
	constexpr auto initialWindowHeight = 600;

	if (GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor())
	{
		if (const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor))
		{
			spdlog::info("Primary Monitor: {0}x{1}@{2}Hz", videoMode->width, videoMode->height, videoMode->refreshRate);
			glfwWindowHint(GLFW_RED_BITS, videoMode->redBits);
			glfwWindowHint(GLFW_GREEN_BITS, videoMode->greenBits);
			glfwWindowHint(GLFW_BLUE_BITS, videoMode->blueBits);
			glfwWindowHint(GLFW_REFRESH_RATE, videoMode->refreshRate);
			glfwWindowHint(GLFW_POSITION_X, (videoMode->width - initialWindowWidth) / 2);
			glfwWindowHint(GLFW_POSITION_Y, (videoMode->height - initialWindowHeight) / 2);
		}
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifndef NDEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

	GLFWwindow* window = glfwCreateWindow(initialWindowWidth, initialWindowHeight, "Sandbox", nullptr, nullptr);
	if (window == nullptr)
	{
		spdlog::error("Failed to create GLFW window");
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (not gladLoadGLLoader(std::bit_cast<GLADloadproc>(&glfwGetProcAddress)))
	{
		spdlog::error("Failed to initialize GLAD");
		glfwDestroyWindow(window);
		glfwTerminate();
		return 1;
	}

	spdlog::info("OpenGL Information:");
	spdlog::info("\tOpenGL Version: {0}", std::bit_cast<const GLchar*>(glGetString(GL_VERSION)));
	spdlog::info("\tGLSL Version: {0}", std::bit_cast<const GLchar*>(glGetString(GL_SHADING_LANGUAGE_VERSION)));
	spdlog::info("\tVendor: {0}", std::bit_cast<const GLchar*>(glGetString(GL_VENDOR)));
	spdlog::info("\tRenderer: {0}", std::bit_cast<const GLchar*>(glGetString(GL_RENDERER)));

	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, const int width, const int height)
	{
		spdlog::debug("Resizing window to {0}x{1}", width, height);
		glViewport(0, 0, width, height);
	});

	glfwSetKeyCallback(window, [](GLFWwindow* window, const int key, const int scancode, const int action, const int mods)
	{
		spdlog::debug("Key: {0}, Scancode: {1}, Action: {2}, Mods: {3}", key, scancode, action, mods);

		if (action == GLFW_PRESS and key == GLFW_KEY_ESCAPE)
		{
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}
	});

	while (not glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
	}

	spdlog::debug("Shutting down");
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}