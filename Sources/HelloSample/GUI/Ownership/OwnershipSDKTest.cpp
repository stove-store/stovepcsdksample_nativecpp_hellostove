#include "OwnershipSDKTest.h"
#include "GUI/Base/BaseSDKTest.h"

#pragma region Callbacks

void OnOwnershipListCallback(const Stove::PCSDK::CallbackResult callbackResult,
                             Stove::PCSDK::Ownership::StovePCOwnership* ownerships,
                             uint32_t ownershipSize)
{
    PrintStoveAPICallbackResult(L"Ownership_OwnershipList", &callbackResult);

    if (callbackResult.result.GetResultCode() == (uint32_t)Stove::PCSDK::Ownership::SDKResultCode::SUCCESS)
    {
        for (uint32_t i = 0; i < ownershipSize; i++)
            PrintStoveOwnership(&ownerships[i]);

        WPrintFLog(L"ownershipSize=%u", ownershipSize);

        // Ownership Check Logic
        if (callbackResult.result.IsSuccessful() == false)
        {
            // Please enter the program termination code.
            return;
        }

        bool owned = false;
        for (uint32_t i = 0; i < ownershipSize; i++)
        {
            if (ownerships[i].GetOwnershipCode() != Stove::PCSDK::Ownership::OwnershipCode::ACQUIRE)
            {
                // you do not own the game, please enter your source code.
                continue;
            }

            if (ownerships[i].GetGameCode() == Stove::PCSDK::Ownership::OwnershipGameCode::BASIC)
            {
                // you own the basic game, please enter your source code.
                owned = true;
            }

            if (ownerships[i].GetGameCode() == Stove::PCSDK::Ownership::OwnershipGameCode::DEMO)
            {
                // you own the demo game, please enter your source code.
                owned = true;
            }

            if (ownerships[i].GetGameCode() == Stove::PCSDK::Ownership::OwnershipGameCode::DLC)
            {
                // you own the dlc game, please enter your source code.
                owned = true;
            }
        }

        if (owned == false)
        {
            // Please enter the program termination code.
            return;
        }

        NEW_LINE();
    }
}

#pragma endregion


#pragma region Print Functions

void PrintStoveOwnership(const Stove::PCSDK::Ownership::StovePCOwnership* ownership)
{
    if (ownership == nullptr)
    {
        WPrintFLog(L"StovePCOwnership is nullptr");
        NEW_LINE(); return;
    }

    WPrintFLog(L"StovePCOwnership.gameId=%s", ownership->GetGameId());
    WPrintFLog(L"StovePCOwnership.gameCode=%d", ownership->GetGameCode());
    WPrintFLog(L"StovePCOwnership.ownershipCode=%d", ownership->GetOwnershipCode());
    WPrintFLog(L"StovePCOwnership.purchaseDate=%llu", ownership->GetPurchaseDate());
    NEW_LINE();
}

#pragma endregion


#pragma region Feature Functions

void LoadOwnershipSDK()
{
    LoadSDK(OWNERSHIP_SDK, OwnershipSDK_DLL_NAME);
}

void UnloadOwnershipSDK()
{
    ReleaseSDK(OWNERSHIP_SDK);
}

void Ownership_InitializeTest()
{
    WPrintFTitle(L"Start of Ownership_InitializeTest..");

    if (Ownership_InitializeFnPtr == nullptr)
    {
        Ownership_InitializeFnPtr =
            FindProcInDLL(OWNERSHIP_SDK, Ownership_Initialize, Ownership_Initialize_t);
    }

    if (Ownership_InitializeFnPtr == nullptr)
    {
        WPrintFLog(L"Fail to load Ownership_Initialize");
        NEW_LINE(); return;
    }

    Stove::PCSDK::Result result = Ownership_InitializeFnPtr();
    PrintStoveAPIResult(L"Ownership_Initialize", &result);
    NEW_LINE();
}

void Ownership_UnInitializeTest()
{
    WPrintFTitle(L"Start of Ownership_UnInitializeTest..");

    if (Ownership_UnInitializeFnPtr == nullptr)
    {
        Ownership_UnInitializeFnPtr =
            FindProcInDLL(OWNERSHIP_SDK, Ownership_UnInitialize, Ownership_UnInitialize_t);
    }

    if (Ownership_UnInitializeFnPtr == nullptr)
    {
        WPrintFLog(L"Fail to load Ownership_UnInitialize");
        NEW_LINE(); return;
    }

    Stove::PCSDK::Result result = Ownership_UnInitializeFnPtr();
    PrintStoveAPIResult(L"Ownership_UnInitialize", &result);
    NEW_LINE();
}

void Ownership_OwnershipListTest()
{
    WPrintFTitle(L"Start of Ownership_OwnershipListTest");

    if (Ownership_OwnershipListFnPtr == nullptr)
    {
        Ownership_OwnershipListFnPtr =
            FindProcInDLL(OWNERSHIP_SDK, Ownership_OwnershipList, Ownership_OwnershipList_t);
    }

    if (Ownership_OwnershipListFnPtr == nullptr)
    {
        WPrintFLog(L"Fail to load Ownership_OwnershipList..");
        NEW_LINE(); return;
    }

    Ownership_OwnershipListFnPtr(OnOwnershipListCallback);
    NEW_LINE();
}

void Ownership_GetVersionTest()
{
    WPrintFTitle(L"Start of Ownership_GetVersionTest");

    if (Ownership_GetVersionFnPtr == nullptr)
    {
        Ownership_GetVersionFnPtr =
            FindProcInDLL(OWNERSHIP_SDK, Ownership_GetVersion, Ownership_GetVersion_t);
    }

    if (Ownership_GetVersionFnPtr == nullptr)
    {
        WPrintFLog(L"Fail to load Ownership_GetVersion..");
        NEW_LINE(); return;
    }

    wchar_t version[1024] = { 0, };
    Stove::PCSDK::Result result = Ownership_GetVersionFnPtr(version, 1024);

    PrintStoveAPIResult(L"Ownership_GetVersion", &result);
    WPrintFLog(L"OwnershipSDK Version: %s", version);
    NEW_LINE();
}

#pragma endregion
