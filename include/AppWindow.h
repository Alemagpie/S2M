#ifndef APP_WINDOW_H
#define APP_WINDOW_H

#include <d3d11.h>
#include <windows.h>
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//Handles the creation of the gui window, separate from the drawing of the ui elements
class AppWindow {
    public:
    bool init(const wchar_t *title, int width, int height);

    void shutdown();

    bool processMessages();
    void beginFrame();
    void endFrame();

    private:
    HWND hwnd = nullptr;
    WNDCLASSEXW wc{};
    ID3D11Device* g_pd3dDevice = nullptr;
    ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
    IDXGISwapChain* g_pSwapChain = nullptr;
    ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;
    UINT g_ResizeWidth = 0, g_ResizeHeight = 0;

    bool CreateDeviceD3D();
    void CleanupDeviceD3D();
    void CreateRenderTarget();
    void CleanupRenderTarget();
    static LRESULT WINAPI WndProcStatic(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

#endif