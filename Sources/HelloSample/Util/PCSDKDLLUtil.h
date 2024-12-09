#pragma once

#include "DLLUtil.h"
#include <format>

#pragma region Fields

#define PATH_LEN (MAX_PATH + 1)

typedef enum
{
    BASE_SDK = 0,
    GAME_SUPPORT_SDK = 1,
    GAMING_SERVICES_SDK = 2,
    IAP_SDK = 3,
    OWNERSHIP_SDK = 4,
    PCBANG_SDK = 5,
    VIEW_SDK = 6
} SDKType;

void LoadSDK(SDKType type, const char* sdkName);

#pragma endregion



#pragma region Functions

void LoadSDK(SDKType type, const char* sdkDLLName)
{
    char parentPath[PATH_LEN];
    HMODULE hModule = GetModuleHandle(nullptr);
    GetParentPath(hModule, parentPath, sizeof(parentPath));

    if (strlen(parentPath) + strlen(sdkDLLName) >= PATH_LEN)
    {
        const char* log = " - Maximum path length exceeded\n";
        printf(log);
        OutputDebugStringA(log);
        return;
    }

    char dllPath[PATH_LEN];
    snprintf(dllPath, PATH_LEN, "%s\\%s", parentPath, sdkDLLName);

    if (LoadDLL(type, dllPath) == false)
    {
        std::string log = std::format(" - Fail to load DLL : {} \n", sdkDLLName);
        printf(log.c_str());
        OutputDebugStringA(log.c_str());
    }
    else
    {
        std::string log = std::format(" - Success to load DLL : {} \n", sdkDLLName);
        printf(log.c_str());
        OutputDebugStringA(log.c_str());
    }
}

void ReleaseSDK(SDKType type)
{
    ReleaseDLL(type);
}


#pragma endregion