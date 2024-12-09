#pragma once
#pragma warning (disable:4996)

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <wchar.h>
#include <Windows.h>


#pragma region Fields

#define MAX_DLL_COUNT 32
static HMODULE _hModule[MAX_DLL_COUNT] = { 0, };
static DWORD _lastError[MAX_DLL_COUNT] = { 0, };

void GetParentPath(HMODULE hModule, char* parentPath, size_t size);
bool LoadDLL(int32_t idx, const char* path);
void ReleaseDLL(int32_t idx);
void* FindProcInDLLImpl(int32_t idx, const char* fnName);

#define FUNC_NAME(fn) #fn
#define FindProcInDLL(idx, fn, fn_t) (fn_t)FindProcInDLLImpl(idx, FUNC_NAME(fn))

#pragma endregion



#pragma region Functions

void GetParentPath(HMODULE hModule, char* parentPath, size_t size)
{
    char fullPath[MAX_PATH];

    // 1. Get the full path of the DLL
    if (GetModuleFileNameA(hModule, fullPath, MAX_PATH) == 0)
    {
        printf("Failed to get module file name\n");
        return;
    }

    // 2. Find the last backslash in the path
    char* lastBackslash = strrchr(fullPath, '\\');
    if (lastBackslash != nullptr)
    {
        // 3. Null-terminate the string at the last backslash to remove the file name
        *lastBackslash = '\0';
    }

    // 4. Copy the parent path to the output buffer
    strncpy(parentPath, fullPath, size);
    parentPath[size - 1] = '\0'; // Ensure null-termination
}

bool LoadDLL(int32_t idx, const char* path)
{
    if (_hModule[idx])
        ReleaseDLL(idx);

    _hModule[idx] = LoadLibraryA(path);
    _lastError[idx] = GetLastError();

    return _hModule[idx] != nullptr;
}

void ReleaseDLL(int32_t idx)
{
    if (_hModule[idx])
    {
        FreeLibrary(_hModule[idx]);
        _lastError[idx] = GetLastError();
    }
    else
    {
        _lastError[idx] = 0;
    }

    _hModule[idx] = nullptr;
}

void* FindProcInDLLImpl(int32_t idx, const char* fnName)
{
    if (_hModule[idx] == nullptr)
    {
        _lastError[idx] = 0;
        return nullptr;
    }

    void* funcPtr = GetProcAddress(_hModule[idx], fnName);
    _lastError[idx] = GetLastError();

    return funcPtr;
}

#pragma endregion