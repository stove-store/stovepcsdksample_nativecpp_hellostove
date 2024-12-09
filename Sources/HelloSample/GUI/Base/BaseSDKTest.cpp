#include "BaseSDKTest.h"

#include "GUI/Ownership/OwnershipSDKTest.h"
#include "Util/CommonUtil.h"


#pragma region Callbacks

void OnRestartAppIfNecessaryAsyncCallback(Stove::PCSDK::CallbackResult callbackResult, bool restartAppIfNecessary)
{
    PrintStoveAPICallbackResult(L"Base_RestartAppIfNecessaryAsync", &callbackResult);

    if (restartAppIfNecessary)
    {
        WPrintFLog(L"Need to restart app (IPC Fail)");

        // Please enter the program termination code.
    }
    else
    {
        WPrintFLog(L"Not need to restart app (IPC Success)");

        // Please call the Base_Initialize() function here.
    }

    NEW_LINE();
}

void OnBaseInitializeCallback(Stove::PCSDK::CallbackResult callbackResult)
{
    PrintStoveAPICallbackResult(L"Base_Initialize", &callbackResult);

    // 1. Please call the Ownership_Initialize() function here.
    // 2. Please call the Ownership_OwnershipList() function here.
}

void OnBaseInitializeCallbackForInitAllTest(Stove::PCSDK::CallbackResult callbackResult)
{
    PrintStoveAPICallbackResult(L"Base_Initialize", &callbackResult);

    Ownership_InitializeTest();

    // Please call the Ownership_OwnershipList() function here.
}

#pragma endregion



#pragma region Print Functions

void PrintStoveAPIResult(const wchar_t* fnName, const Stove::PCSDK::Result* result)
{
    if (result == nullptr)
    {
        WPrintFLog(L"Result is nullptr");
        NEW_LINE(); return;
    }

    if (result->GetResultCode() == (uint32_t)Stove::PCSDK::Base::SDKResultCode::SUCCESS)
    {
        WPrintFLog(L"FuncName=%s, StoveAPI Result [SUCCESS]", fnName);
    }
    else
    {
        WPrintFLog(L"FuncName=%s, StoveAPI Result [FAIL]", fnName);
    }

    WPrintFLog(L"Result.sdkName=%s", result->GetSDKName());
    WPrintFLog(L"Result.methodCode=%u", result->GetMethodCode());
    WPrintFLog(L"Result.resultCode=%u", result->GetResultCode());
    NEW_LINE();
}

void PrintStoveAPICallbackResult(const wchar_t* fnName, const Stove::PCSDK::CallbackResult* callbackResult)
{
    if (callbackResult == nullptr)
    {
        WPrintFLog(L"CallbackResult is nullptr");
        NEW_LINE(); return;
    }

    PrintStoveAPIResult(fnName, &callbackResult->result);

    WPrintFLog(L"CallbackResult.errorMessage=%s", callbackResult->errorMessage);
    WPrintFLog(L"CallbackResult.externalError=%u", callbackResult->externalError);
    NEW_LINE();
}

void PrintStoveInitializeParam(const Stove::PCSDK::Base::StovePCInitializeParam* param)
{
    if (param == nullptr)
    {
        WPrintFLog(L"StovePCInitializeParam is nullptr");
        NEW_LINE(); return;
    }

    WPrintFLog(L"StovePCInitializeParam.environment=%s", param->GetEnvironment());
    WPrintFLog(L"StovePCInitializeParam.gameId=%s", param->GetGameID());
    WPrintFLog(L"StovePCInitializeParam.applicationKey=%s", param->GetApplicationKey());
    NEW_LINE();
}

void PrintStoveToken(const Stove::PCSDK::Base::StovePCToken* token)
{
    if (token == nullptr)
    {
        WPrintFLog(L"StovePCToken is nullptr");
        NEW_LINE(); return;
    }

    WPrintFLog(L"StovePCToken.accessToken=%s", token->GetAccessToken());
    WPrintFLog(L"StovePCToken.expireIn=%d", token->GetExpireIn());
    NEW_LINE();
}

void PrintStoveUser(const Stove::PCSDK::Base::StovePCUser* user)
{
    if (user == nullptr)
    {
        WPrintFLog(L"StovePCUser is nullptr");
        NEW_LINE(); return;
    }

    WPrintFLog(L"StovePCUser.nickname: %s", user->GetNickname());
    WPrintFLog(L"StovePCUser.gameUserId %llu", user->GetGameUserId());
    NEW_LINE();
}

void PrintStoveGds(const Stove::PCSDK::Base::StovePCGds* gds)
{
    if (gds == nullptr)
    {
        WPrintFLog(L"StovePCGds is nullptr");
        NEW_LINE(); return;
    }

    WPrintFLog(L"StovePCGds.isDefault: %d", gds->IsDefault());
    WPrintFLog(L"StovePCGds.nation: %s", gds->GetNation());
    WPrintFLog(L"StovePCGds.regulation: %s", gds->GetRegulation());
    WPrintFLog(L"StovePCGds.timeZone: %s", gds->GetTimeZone());
    WPrintFLog(L"StovePCGds.utcOffset: %d", gds->GetUtcOffset());
    WPrintFLog(L"StovePCGds.language: %s", gds->GetLanguage());
    NEW_LINE();
}

void PrintStoveSignin(const Stove::PCSDK::Base::StovePCSignin* signin)
{
    if (signin == nullptr)
    {
        WPrintFLog(L"StovePCSignin is nullptr");
        NEW_LINE(); return;
    }

    WPrintFLog(L"StovePCSignin.personVerify: %d", signin->GetPersonVerify());
    WPrintFLog(L"StovePCSignin.emailVerify: %d", signin->GetEmailVerify());
    WPrintFLog(L"StovePCSignin.nationality: %s", signin->GetNationality());
    WPrintFLog(L"StovePCSignin.providerCode: %s", signin->GetProviderCode());
    WPrintFLog(L"StovePCSignin.accountType: %d", signin->GetAccountType());
    NEW_LINE();
}

#pragma endregion


#pragma region Feature Functions

void LoadBaseSDK()
{
    LoadSDK(BASE_SDK, BASESDK_DLL_NAME);
}

void UnloadBaseSDK()
{
    ReleaseSDK(BASE_SDK);
}

void Base_RestartAppIfNecessaryAsyncTest(const wchar_t* env,
                                             const wchar_t* gameId,
                                             const wchar_t* applicationKey)
{
    WPrintFTitle(L"Start of Base_RestartAppIfNecessaryAsyncTest");

    if (Base_RestartAppIfNecessaryAsyncFnPtr == nullptr)
    {
        Base_RestartAppIfNecessaryAsyncFnPtr =
            FindProcInDLL(BASE_SDK, Base_RestartAppIfNecessaryAsync, Base_RestartAppIfNecessaryAsync_t);
    }

    if (Base_RestartAppIfNecessaryAsyncFnPtr == nullptr)
    {
        WPrintFLog(L"Fail to load Base_RestartAppIfNecessaryAsync..");
        NEW_LINE(); return;
    }

    Stove::PCSDK::Base::StovePCInitializeParam initParam;
    initParam.SetApplicationKey((wchar_t*)applicationKey);
    initParam.SetEnvironment((wchar_t*)env);
    initParam.SetGameID((wchar_t*)gameId);

    Base_RestartAppIfNecessaryAsyncFnPtr(&initParam, 1000, OnRestartAppIfNecessaryAsyncCallback);
    NEW_LINE();
}

void Base_InitializeTest(const wchar_t* env,
                                 const wchar_t* gameId,
                                 const wchar_t* applicationKey)
{
    WPrintFTitle(L"Start of Base_InitializeTest");

    if (Base_InitializeFnPtr == nullptr)
    {
        Base_InitializeFnPtr =
            FindProcInDLL(BASE_SDK, Base_Initialize, Base_Initialize_t);
    }

    if (Base_InitializeFnPtr == nullptr)
    {
        WPrintFLog(L"Fail to load Base_Initialize..");
        NEW_LINE(); return;
    }

    Stove::PCSDK::Base::StovePCInitializeParam initParam;
    initParam.SetApplicationKey((wchar_t*)applicationKey);
    initParam.SetEnvironment((wchar_t*)env);
    initParam.SetGameID((wchar_t*)gameId);

    Base_InitializeFnPtr(&initParam, OnBaseInitializeCallback);
    NEW_LINE();
}

void NonStoveAPI_InitAllTest(const wchar_t* env,
                             const wchar_t* gameId,
                             const wchar_t* applicationKey)
{
    WPrintFTitle(L"Start of NonStoveAPI_InitAllTest");

    if (Base_InitializeFnPtr == nullptr)
    {
        Base_InitializeFnPtr =
            FindProcInDLL(BASE_SDK, Base_Initialize, Base_Initialize_t);
    }

    if (Base_InitializeFnPtr == nullptr)
    {
        WPrintFLog(L"Fail to load Base_Initialize..");
        NEW_LINE(); return;
    }

    Stove::PCSDK::Base::StovePCInitializeParam initParam;
    initParam.SetApplicationKey((wchar_t*)applicationKey);
    initParam.SetEnvironment((wchar_t*)env);
    initParam.SetGameID((wchar_t*)gameId);

    Base_InitializeFnPtr(&initParam, OnBaseInitializeCallbackForInitAllTest);
    NEW_LINE();
}

void Base_UnInitializeTest()
{
    WPrintFTitle(L"Start of Base_BaseUnInitializeTest");

    if (Base_UnInitializeFnPtr == nullptr)
    {
        Base_UnInitializeFnPtr =
            FindProcInDLL(BASE_SDK, Base_UnInitialize, Base_UnInitialize_t);
    }

    if (Base_UnInitializeFnPtr == nullptr)
    {
        WPrintFLog(L"Fail to load Base_UnInitialize..");
        NEW_LINE(); return;
    }

    Stove::PCSDK::Result result = Base_UnInitializeFnPtr();
    PrintStoveAPIResult(L"Base_UnInitialize", &result);
    NEW_LINE();
}

void NonStoveAPI_UnInitAllTest()
{
    WPrintFTitle(L"Start of NonStoveAPI_UnInitAllTest..");

    Base_UnInitializeTest();
    Ownership_UnInitializeTest();
    NEW_LINE();
}

void Base_RunCallbackTest()
{
    if (Base_RunCallbackFnPtr == nullptr)
    {
        Base_RunCallbackFnPtr =
            FindProcInDLL(BASE_SDK, Base_RunCallback, Base_RunCallback_t);
    }

    if (Base_RunCallbackFnPtr == nullptr)
    {
        WPrintFLog(L"Fail to load Base_RunCallback..");
        NEW_LINE(); return;
    }

    Base_RunCallbackFnPtr();
}

void Base_GetAccessTokenTest()
{
    WPrintFTitle(L"Start of Base_GetAccessTokenTest");

    if (Base_GetAccessTokenFnPtr == nullptr)
    {
        Base_GetAccessTokenFnPtr =
            FindProcInDLL(BASE_SDK, Base_GetAccessToken, Base_GetAccessToken_t);
    }

    if (Base_GetAccessTokenFnPtr == nullptr)
    {
        WPrintFLog(L"Fail to load Base_GetAccessToken..");
        NEW_LINE(); return;
    }

    wchar_t accessToken[1024] = { 0, };
    Stove::PCSDK::Result result = Base_GetAccessTokenFnPtr(accessToken, 1024);

    PrintStoveAPIResult(L"Base_GetAccessToken", &result);
    WPrintFLog(L"AccessToken: %s", accessToken);
    NEW_LINE();
}

void Base_GetUserTest()
{
    WPrintFTitle(L"Start of Base_GetUserTest..");

    if (Base_GetUserFnPtr == nullptr)
    {
        Base_GetUserFnPtr =
            FindProcInDLL(BASE_SDK, Base_GetUser, Base_GetUser_t);
    }

    if (Base_GetUserFnPtr == nullptr)
    {
        WPrintFLog(L"Fail to load Base_GetUser..");
        NEW_LINE(); return;
    }

    Stove::PCSDK::Base::StovePCUser user;
    Stove::PCSDK::Result result = Base_GetUserFnPtr(&user);

    PrintStoveAPIResult(L"Base_GetUser", &result);
    PrintStoveUser(&user);
    NEW_LINE();
}

void Base_GetGdsTest()
{
    WPrintFTitle(L"Start of Base_GetGdsTest");

    if (Base_GetGdsFnPtr == nullptr)
    {
        Base_GetGdsFnPtr =
            FindProcInDLL(BASE_SDK, Base_GetGds, Base_GetGds_t);
    }

    if (Base_GetGdsFnPtr == nullptr)
    {
        WPrintFLog(L"Fail to load Base_GetGds..");
        NEW_LINE(); return;
    }

    Stove::PCSDK::Base::StovePCGds gds;
    Stove::PCSDK::Result result = Base_GetGdsFnPtr(&gds);

    PrintStoveAPIResult(L"Base_GetGds", &result);
    PrintStoveGds(&gds);
    NEW_LINE();
}

void Base_GetSigninTest()
{
    WPrintFTitle(L"Start of Base_GetSigninTest");

    if (Base_GetSigninFnPtr == nullptr)
    {
        Base_GetSigninFnPtr =
            FindProcInDLL(BASE_SDK, Base_GetSignin, Base_GetSignin_t);
    }

    if (Base_GetSigninFnPtr == nullptr)
    {
        WPrintFLog(L"Fail to load Base_GetSignin..");
        NEW_LINE(); return;
    }

    Stove::PCSDK::Base::StovePCSignin signin;
    Stove::PCSDK::Result result = Base_GetSigninFnPtr(&signin);

    PrintStoveAPIResult(L"Base_GetSignin", &result);
    PrintStoveSignin(&signin);
    NEW_LINE();
}

void Base_GetVersionTest()
{
    WPrintFTitle(L"Start of Base_GetVersionTest");

    if (Base_GetVersionFnPtr == nullptr)
    {
        Base_GetVersionFnPtr =
            FindProcInDLL(BASE_SDK, Base_GetVersion, Base_GetVersion_t);
    }

    if (Base_GetVersionFnPtr == nullptr)
    {
        WPrintFLog(L"Fail to load Base_GetVersion..");
        NEW_LINE(); return;
    }

    wchar_t version[1024] = { 0, };

    Stove::PCSDK::Result result = Base_GetVersionFnPtr(version, 1024);
    PrintStoveAPIResult(L"Base_GetVersion", &result);

    WPrintFLog(L"BaseSDK Version: %s", version);
    NEW_LINE();
}

#pragma endregion
