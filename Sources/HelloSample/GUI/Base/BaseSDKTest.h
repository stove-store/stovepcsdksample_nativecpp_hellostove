#pragma once
#include "BaseSDK.h"
#include "Util/PCSDKDLLUtil.h"
#include "Util/AtomicBool.h"
#include "Util/CommonUtil.h"


#pragma region Fields

constexpr auto BASESDK_NAME = "BaseSDK";
constexpr auto BASESDK_DLL_NAME = "BaseSDK.dll";

constexpr auto STOVE_ENV_SB = L"SANDBOX";
constexpr auto STOVE_ENV_LIVE = L"LIVE";

// fnPtr
typedef bool(__cdecl* Base_RestartAppIfNecessaryAsync_t)(const Stove::PCSDK::Base::StovePCInitializeParam*, uint32_t, Stove::PCSDK::Base::OnRestartAppIfNecessaryAsyncFinished);
static Base_RestartAppIfNecessaryAsync_t Base_RestartAppIfNecessaryAsyncFnPtr = nullptr;
typedef void(__cdecl* Base_Initialize_t)(const Stove::PCSDK::Base::StovePCInitializeParam*, Stove::PCSDK::Base::OnInitializeFinished);
static Base_Initialize_t Base_InitializeFnPtr = nullptr;
typedef Stove::PCSDK::Result(__cdecl* Base_UnInitialize_t)();
static Base_UnInitialize_t Base_UnInitializeFnPtr = nullptr;
typedef void(__cdecl* Base_RunCallback_t)();
static Base_RunCallback_t Base_RunCallbackFnPtr = nullptr;
typedef Stove::PCSDK::Result(__cdecl* Base_GetAccessToken_t)(wchar_t*, uint32_t);
static Base_GetAccessToken_t Base_GetAccessTokenFnPtr = nullptr;
typedef Stove::PCSDK::Result(__cdecl* Base_GetUser_t)(Stove::PCSDK::Base::StovePCUser*);
static Base_GetUser_t Base_GetUserFnPtr = nullptr;
typedef Stove::PCSDK::Result(__cdecl* Base_GetGds_t)(Stove::PCSDK::Base::StovePCGds*);
static Base_GetGds_t Base_GetGdsFnPtr = nullptr;
typedef Stove::PCSDK::Result(__cdecl* Base_GetSignin_t)(Stove::PCSDK::Base::StovePCSignin*);
static Base_GetSignin_t Base_GetSigninFnPtr = nullptr;
typedef Stove::PCSDK::Result(__cdecl* Base_GetVersion_t)(wchar_t*, uint32_t);
static Base_GetVersion_t Base_GetVersionFnPtr = nullptr;

#pragma endregion


#pragma region Callbacks

// callbacks
void OnRestartAppIfNecessaryAsyncCallback(Stove::PCSDK::CallbackResult callbackResult, bool restartAppIfNecessary);
void OnBaseInitializeCallback(Stove::PCSDK::CallbackResult callbackResult);
void OnBaseInitializeCallbackForInitAllTest(Stove::PCSDK::CallbackResult callbackResult);

#pragma endregion


#pragma region Print Functions

// print functions
void PrintStoveAPIResult(const wchar_t* fnName, const Stove::PCSDK::Result* result);
void PrintStoveAPICallbackResult(const wchar_t* fnName, const Stove::PCSDK::CallbackResult* callbackResult);
void PrintStoveInitializeParam(const Stove::PCSDK::Base::StovePCInitializeParam* token);
void PrintStoveToken(const Stove::PCSDK::Base::StovePCToken* token);
void PrintStoveUser(const Stove::PCSDK::Base::StovePCUser* token);
void PrintStoveGds(const Stove::PCSDK::Base::StovePCGds* token);
void PrintStoveSignin(const Stove::PCSDK::Base::StovePCSignin* token);

#pragma endregion


#pragma region Feature Functions

// functions
void LoadBaseSDK();
void UnloadBaseSDK();
void Base_RestartAppIfNecessaryAsyncTest(const wchar_t* env,
                                             const wchar_t* gameId,
                                             const wchar_t* applicationKey);
void Base_InitializeTest(const wchar_t* env,
                                 const wchar_t* gameId,
                                 const wchar_t* applicationKey);
void NonStoveAPI_InitAllTest(const wchar_t* env,
                             const wchar_t* gameId,
                             const wchar_t* applicationKey);
void Base_UnInitializeTest();
void NonStoveAPI_UnInitAllTest();
void Base_RunCallbackTest();
void Base_GetAccessTokenTest();
void Base_GetUserTest();
void Base_GetGdsTest();
void Base_GetSigninTest();
void Base_GetVersionTest();

#pragma endregion

