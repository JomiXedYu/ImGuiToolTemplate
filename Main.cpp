#include "Main.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <Windows.h>
#include "UIUpdate.h"
#include "Monaco.ttf.h"

using namespace std;

GLFWwindow* window;

HWND GetCurrentWindow()
{
    return glfwGetWin32Window(window);
}

void SetWindowTitle(const char* title)
{
    SetWindowText(GetCurrentWindow(), title);
}

struct {
    int width, height;
} windows_size;

std::tuple<int, int> GetWindowSize()
{
    return { windows_size.width, windows_size.height };
}

static float GetUIScaling()
{
    const HDC hDC = ::GetDC(NULL);
    const UINT dpix = ::GetDeviceCaps(hDC, LOGPIXELSX);
    ::ReleaseDC(NULL, hDC);
    return  dpix / 96.f;
}
static void OnWindowResize(GLFWwindow* window, int width, int height)
{
    windows_size = { width, height };
    glViewport(0, 0, windows_size.width, windows_size.height);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    char title[256];

    _UIWindowInit(title, &windows_size.width, &windows_size.height);

    window = glfwCreateWindow(windows_size.width, windows_size.height, title, NULL, NULL);
    int max_width = GetSystemMetrics(SM_CXSCREEN);
    int max_height = GetSystemMetrics(SM_CYSCREEN);
    glfwSetWindowMonitor(window, NULL, (max_width / 2) - (windows_size.width / 2), (max_height / 2) - (windows_size.height / 2), windows_size.width, windows_size.height, GLFW_DONT_CARE);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glfwSetWindowSizeCallback(window, &OnWindowResize);
    glViewport(0, 0, windows_size.width, windows_size.height);

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.IniFilename = nullptr;

    io.FontGlobalScale = GetUIScaling();

    ImFontConfig eng_config = {};
    ImFontConfig chs_config = {};

    eng_config.FontDataOwnedByAtlas = false;
    io.Fonts->AddFontFromMemoryTTF(Monaco_ttf, sizeof(Monaco_ttf), 16, &eng_config, io.Fonts->GetGlyphRangesDefault());

    chs_config.MergeMode = true;
    io.Fonts->AddFontFromFileTTF(R"(C:\Windows\Fonts\msyh.ttc)", 16, &chs_config, io.Fonts->GetGlyphRangesChineseSimplifiedCommon());

    io.Fonts->Build();

    _UIStyleInit();

    ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        auto win_flags =
            ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_::ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_::ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_::ImGuiWindowFlags_NoMove;

        if (ImGui::Begin("top window", nullptr, win_flags))
        {
            ImGui::SetWindowPos({ 0,0 });
            ImGui::SetWindowSize({ (float)windows_size.width, (float)windows_size.height });
            _UIUpdate();
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}
