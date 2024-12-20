#pragma once
#pragma once
#include "OwnershipSDK.h"
#include "Util/PCSDKDLLUtil.h"
#include "Util/AtomicBool.h"
#include "Util/CommonUtil.h"


#pragma region Fields

constexpr auto OwnershipSDK_NAME = "OwnershipSDK";
constexpr auto OwnershipSDK_DLL_NAME = "OwnershipSDK.dll";

// fnPtr
typedef Stove::PCSDK::Result(__cdecl* Ownership_Initialize_t)();
static Ownership_Initialize_t Ownership_InitializeFnPtr;
typedef Stove::PCSDK::Result(__cdecl* Ownership_UnInitialize_t)();
static Ownership_UnInitialize_t Ownership_UnInitializeFnPtr;
typedef void(__cdecl* Ownership_OwnershipList_t)(Stove::PCSDK::Ownership::OnOwnershipListFinished);
static Ownership_OwnershipList_t Ownership_OwnershipListFnPtr;
typedef Stove::PCSDK::Result(__cdecl* Ownership_GetVersion_t)(wchar_t*, uint32_t);
static Ownership_GetVersion_t Ownership_GetVersionFnPtr;

#pragma endregion


#pragma region Callbacks

// callbacks
void OnOwnershipListCallback(const Stove::PCSDK::CallbackResult callbackResult,
    Stove::PCSDK::Ownership::StovePCOwnership* ownerships,
    uint32_t ownershipSize);
#pragma endregion


#pragma region Print Functions

// print functions
void PrintStoveOwnership(const Stove::PCSDK::Ownership::StovePCOwnership* ownership);

#pragma endregion


#pragma region Feature Functions

// functions
void LoadOwnershipSDK();
void UnloadOwnershipSDK();
void Ownership_InitializeTest();
void Ownership_UnInitializeTest();
void Ownership_OwnershipListTest();
void Ownership_GetVersionTest();

#pragma endregion