#pragma once
#include <imgui/imgui.h>
#include <Windows.h>
#include <iostream>
#include <tuple>

HWND GetCurrentWindow();
void SetWindowTitle(const char* title);
std::tuple<int, int> GetWindowSize();