#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <Windows.h>

#pragma region Fields

static volatile SHORT atomicBool = 0;

bool GetGlobalAtomicBool();
void SetGlobalAtomicBool(bool value);

#pragma endregion


#pragma region Functions

bool GetGlobalAtomicBool()
{
    return _InterlockedCompareExchange16(&atomicBool, 1, 1) == 1;
}

void SetGlobalAtomicBool(bool value)
{
    if (value) _InterlockedExchange16(&atomicBool, 1);
    else _InterlockedExchange16(&atomicBool, 0);
}

#pragma endregion