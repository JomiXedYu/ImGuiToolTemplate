# ImGuiToolTemplate
 


UIUpdate.cpp

```c++
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
```