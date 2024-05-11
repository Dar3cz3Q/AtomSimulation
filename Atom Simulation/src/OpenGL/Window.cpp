#include "Window.h"

// Include layers
#include "Layers/Example.h"

Window::Window(uint32_t width, uint32_t height, const std::string& title) :
	m_Window(nullptr), m_Width(width), m_Height(height), m_Title(title), m_Minimized(false), m_Running(false), m_LastFrameTime(0.0f), m_Counter(0)
{
    // Initializing window
    int status = glfwInit();

    AS_ASSERT(status);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(m_Width, m_Height, title.c_str(), NULL, NULL);

    AS_ASSERT(m_Window);

    glfwMakeContextCurrent(m_Window);

#ifdef AS_DELTA_TIME
    glfwSwapInterval(0);
#else
    glfwSwapInterval(1);
#endif

    gladLoadGL();

    AS_LOG("Window initialized");
    AS_LOG(glGetString(GL_VERSION));

    //
    // Push layers on stack
    //

    PushLayer(new Example(m_Window));
}

Window::~Window()
{
    glfwTerminate();
}

void Window::Run()
{
    m_Running = true;

    while (m_Running) 
    {

        if (!m_Minimized) 
        {
            float time = static_cast<float>(glfwGetTime());
            float deltaTime = time - m_LastFrameTime;

            for (Layer* layer : m_LayerStack) 
            {
                layer->OnDraw();
            }

#ifdef AS_DELTA_TIME
            if (deltaTime >= AS_DELTA_TIME) {
                m_LastFrameTime = time;
                for (Layer* layer : m_LayerStack) 
                {
                    layer->OnUpdate();
                }
            }
#else
            for (Layer* layer : m_LayerStack)
            {
                layer->OnUpdate();
            }
#endif
        }

        Update();
        Events();
    } 
}

void Window::Update()
{
    glfwSwapBuffers(m_Window);
    glfwPollEvents();

    Statistics();
}

void Window::Events()
{
    if (glfwWindowShouldClose(m_Window)) 
    {
        m_Running = false;
        return;
    }

    glfwGetWindowSize(m_Window, &m_Width, &m_Height);

    if (m_Width == 0 || m_Height == 0) 
    {
        m_Minimized = true;
        return;
    }

    m_Minimized = false;
}

void Window::PushLayer(Layer* layer)
{
    m_LayerStack.PushLayer(layer);
}

void Window::Statistics()
{
#ifdef AS_DELTA_TIME
    float time = static_cast<float>(glfwGetTime());
    float deltaTime = time - m_LastFrameTime;

    m_Counter++;

    if (deltaTime >= AS_DELTA_TIME) {
        float fps = (1.0 / deltaTime) * m_Counter;
        float ms = (deltaTime / m_Counter) * 1000;

        std::string newTitle = m_Title + ": " + std::to_string(fps) + " FPS, " + std::to_string(ms) + " ms";
        glfwSetWindowTitle(m_Window, newTitle.c_str());

        m_Counter = 0;
    }
#endif
}