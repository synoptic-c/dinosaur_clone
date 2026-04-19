#include"window.hpp"
void Window::Initialize(const std::string& loadPath)
{
	if (!glfwInit())
	{
		std::cout << "GLFW initialization failed" << std::endl;
	}
#ifdef _WIN32
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
#elif __linux__
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
#elif __APPLE__
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	m_path = loadPath;
	std::map<std::string, std::string> loadData = resourcemanager::LoadFromIni(m_path);
	m_windowData.width = std::stoi(loadData["width"]);
	m_windowData.height = std::stoi(loadData["height"]);
	m_windowData.title = loadData["title"];
	m_windowData.top = 0;
	m_handle = glfwCreateWindow(m_windowData.width, m_windowData.height, m_windowData.title.c_str(), nullptr, nullptr);
	if (!m_handle)
	{
		std::cout << "Window creation failed" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(m_handle);
	glfwSetFramebufferSizeCallback(m_handle, [](GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	});
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "glad initialization failed" << std::endl;
		glfwDestroyWindow(m_handle);
		glfwTerminate();
	}
}
void Window::SetSize(int width, int height, bool& isWindow)
{
	if (isWindow == true)
	{
		glfwSetWindowSize(m_handle, width, height);
		isWindow = false;
	}
}
void Window::SetFullScreen(bool isFullScreen)
{
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	if (isFullScreen == true)
	{
		if (m_windowData.top < 1)
		{
			glfwGetWindowFrameSize(m_handle, nullptr, &m_windowData.top, nullptr, nullptr);
		}
		glfwSetWindowMonitor(m_handle, monitor, 0, 0, GetWidth(), GetHeight(), mode->refreshRate);
	}
	else if (isFullScreen == false)
	{
		glfwGetWindowPos(m_handle, &m_windowData.x, &m_windowData.y);
		glfwSetWindowMonitor(m_handle, nullptr, m_windowData.x, m_windowData.y + m_windowData.top, GetWidth(), GetHeight(), mode->refreshRate);
		m_windowData.top = 0;
	}
}
GLFWwindow* Window::GetHandle()
{
	return m_handle;
}
int Window::GetWidth()
{
	int width;
	glfwGetWindowSize(m_handle, &width, 0);
	return width;
}
int Window::GetHeight()
{
	int height;
	glfwGetWindowSize(m_handle, 0, &height);
	return height;
}
void Window::Destroy()
{
	m_windowData.width = GetWidth();
	m_windowData.height = GetHeight();
	std::map<std::string, std::string> saveData;
	saveData.emplace("width", std::to_string(m_windowData.width));
	saveData.emplace("height", std::to_string(m_windowData.height));
	saveData.emplace("title", m_windowData.title);
	resourcemanager::SaveToIni(m_path, saveData);
	glfwDestroyWindow(m_handle);
	glfwTerminate();
}