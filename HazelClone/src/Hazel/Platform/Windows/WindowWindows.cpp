#include "hzpch.h"
#include "WindowWindows.h"

namespace Hazel 
{
	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowWindows(props);
	}

	WindowWindows::WindowWindows(const WindowProps& props)
	{
		Init(props);
	}


	WindowWindows::~WindowWindows()
	{
		Shutdown();
	}

	void WindowWindows::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		HZ_CORE_INFO("Creating Window {0}, ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			HZ_CORE_ASSERT(success, "Could not initialize GLFW");

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
	}

	void WindowWindows::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowWindows::SetVSync(bool enabled)
	{
		if (enabled)
		{
			glfwSwapInterval(1);
		}
		else
			glfwSwapInterval(0);
		m_Data.VSync = enabled;

	}

	bool WindowWindows::IsVSync() const
	{
		return m_Data.VSync;
	}



	void WindowWindows::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

}
