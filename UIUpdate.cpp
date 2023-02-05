#include "Main.h"
#include "UIUpdate.h"
#include <string>
#include <iostream>
#include <CoreLib/CoreLib.h>
#include <CoreLib.Serialization/JsonSerializer.h>
#include <CoreLib.Serialization/DataSerializer.h>

using namespace std;
using namespace jxcorlib;


void _UIWindowInit(char* title, int* width, int* height)
{
    ::strcpy_s(title, 256, __PROJECT_NAME);
    *width = 400;
    *height = 600;
}

void _UIStyleInit()
{
    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    style.FrameRounding = 12;
}

void _UIUpdate()
{
    ImGui::Text("世界，你好");
    if (ImGui::Button("Hello world!", {-1,0}))
    {

    }
}