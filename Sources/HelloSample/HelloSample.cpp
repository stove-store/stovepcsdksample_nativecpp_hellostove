#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif // IMGUI_DEFINE_MATH_OPERATORS

#include "GUI/ImGuiWin32Base.h"
#include "GUI/Base/BaseSDKTest.h"
#include "GUI/Ownership/OwnershipSDKTest.h"
#include "StoveSignatureVerifier.h"
#include "resource.h"


#pragma region Defines

HWND mainHWnd = nullptr;
bool allocConsole = false;
constexpr auto wndClassTitle = L"PCSDK3 NativeCpp HelloSample";

void CreateMainWindow(HINSTANCE hInstance, int nCmdShow);
void ImGuiInit();
void LoadSDK();
void ImGuiUnInit(HINSTANCE hInstance);
void UnloadSDK();

#pragma endregion



#pragma region Functions

void CreateMainWindow(HINSTANCE hInstance, int nCmdShow)
{
    // register window class

    WNDCLASSEXW wc =
    {
        sizeof(wc),
        CS_CLASSDC,
        WndProc,
        0L,
        0L,
        hInstance,
        nullptr, nullptr, nullptr, nullptr,
        wndClassTitle,
        nullptr
    };
    ::RegisterClassExW(&wc);


    // Create window
    HWND desktop = GetDesktopWindow();

    RECT dwr;
    GetWindowRect(desktop, &dwr);

    int32_t szW = dwr.right - dwr.left;
    int32_t szH = dwr.bottom - dwr.top;

    mainHWnd = ::CreateWindowExW(0, wndClassTitle,
        wndClassTitle,
        WS_OVERLAPPEDWINDOW,
        0, 0, szW, szH,
        nullptr, nullptr, wc.hInstance, nullptr);

    // Initialize Direct3D
    if (!::CreateDeviceD3D(mainHWnd))
    {
        ::CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return;
    }

    // Show the window
    ::ShowWindow(mainHWnd, SW_SHOWDEFAULT);
    ::UpdateWindow(mainHWnd);
}

void ImGuiInit()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    //float dpiScale = ImGui_ImplWin32_GetDpiScaleForHwnd(mainHWnd) * 1.25f;
    //io.FontGlobalScale = dpiScale;
    //io.DisplayFramebufferScale = ImVec2(dpiScale, dpiScale);

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(mainHWnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

    if ((allocConsole = ::AllocConsole()) == true)
    {
        ::freopen("CONIN$", "r", stdin);
        ::freopen("CONOUT$", "w", stdout);

        DWORD consoleModePrev;
        HANDLE handle = ::GetStdHandle(STD_INPUT_HANDLE);
        ::GetConsoleMode(handle, &consoleModePrev);
        ::SetConsoleMode(handle, consoleModePrev & ~ENABLE_QUICK_EDIT_MODE);
    }
}

void LoadSDK()
{
    LoadBaseSDK();
    LoadOwnershipSDK();
}

void ImGuiUnInit(HINSTANCE hInstance)
{
    // Cleanup
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    if (allocConsole)
        ::FreeConsole();

    ::CleanupDeviceD3D();
    ::DestroyWindow(mainHWnd);
    ::UnregisterClassW(wndClassTitle, hInstance);
}

void UnloadSDK()
{
    UnloadBaseSDK();
    UnloadOwnershipSDK();
}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    //ImGui_ImplWin32_EnableDpiAwareness();

    // 1. Start Stove Verify
#if defined(_NDEBUG) || defined(NDEBUG)
    // only in release mode
    StartStoveVerify();
#endif

    // 2 Create Main Wnd
    CreateMainWindow(hInstance, nCmdShow);

    // 3 Init ImGui
    ImGuiInit();

    // 4 Load SDK Dlls
    LoadSDK();

    // 5 Main Loop
    int result = MainMessageLoop();

    // 6 UnInit ImGui
    ImGuiUnInit(hInstance);

    // 7 Unload SDK Dlls
    UnloadSDK();

    return result;
}

#pragma endregion