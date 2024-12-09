#include <d3d11.h>
#include <string>
#include <vector>
#include <unordered_map>

#include "ImGuiSDKFeatureImpl.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_win32.h"
#include "imgui/backends/imgui_impl_dx11.h"

#include "GUI/Base/BaseSDKTest.h"
#include "GUI/Ownership/OwnershipSDKTest.h"
#include "Util/CommonUtil.h"


static const char* CurrentEnv = "SANDBOX";


void ImGuiSDKFeatureMainWnd()
{
    ImGui::Begin("PCSDK3 NativeC Sample");

    if (ImGui::BeginTabBar("SDKFeatureTabs"))
    {
        if (ImGui::BeginTabItem(BASESDK_NAME))
        {
            ImGuiBaseSDKTabImpl();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem(OwnershipSDK_NAME))
        {
            ImGuiOwnershipSDKTabImpl();
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }

    ImGui::End();
}

void ImGuiBaseSDKTabImpl()
{
    ImGui::Text("# BaseSDK Test"); ImGui::NewLine();

    static char GameID[256] = "\0";
    static char AppKey[256] = "\0";
    static char RestartAppIfNecessoryAsyncTimeMillis[256] = "\0";
    static char RunCallbackTimeoutMillis[256] = "\0";

    {
        ImGui::SeparatorText("Necessory Value");

        static const char* EnvItems[] = { "SANDBOX", "LIVE" };
        if (ImGui::BeginCombo("Env", CurrentEnv))
        {
            for (int n = 0; n < IM_ARRAYSIZE(EnvItems); n++)
            {
                bool isSelected = strcmp(CurrentEnv, EnvItems[n]) == 0;

                if (ImGui::Selectable(EnvItems[n], isSelected))
                    CurrentEnv = EnvItems[n];

                if (isSelected)
                    ImGui::SetItemDefaultFocus();
            }

            ImGui::EndCombo();
        }

        ImGui::InputText("GameID", GameID, IM_ARRAYSIZE(GameID), ImGuiInputTextFlags_AlwaysOverwrite);
        ImGui::InputText("AppKey", AppKey, IM_ARRAYSIZE(AppKey), ImGuiInputTextFlags_AlwaysOverwrite);
        ImGui::InputText("RestartAppIfNecessoryAsyncTimeMillis", RestartAppIfNecessoryAsyncTimeMillis,
                         IM_ARRAYSIZE(RestartAppIfNecessoryAsyncTimeMillis), ImGuiInputTextFlags_AlwaysOverwrite | ImGuiInputTextFlags_CharsDecimal);
        ImGui::NewLine();
    }

    {
        ImGui::SeparatorText(" RestartAppIfNecessory");

        if (ImGui::Button("RestartAppIfNecessoryAsync"))
            Base_RestartAppIfNecessaryAsyncTest(Str2WStr(CurrentEnv).c_str(), Str2WStr(GameID).c_str(), Str2WStr(AppKey).c_str());

        ImGui::NewLine();
    }

    {
        ImGui::SeparatorText(" Init/UnInit SDKs");

        if (ImGui::Button("InitSDKs"))
            NonStoveAPI_InitAllTest(Str2WStr(CurrentEnv).c_str(), Str2WStr(GameID).c_str(), Str2WStr(AppKey).c_str());

        ImGui::SameLine();
        if (ImGui::Button("UnInitSDKs"))
            NonStoveAPI_UnInitAllTest();

        ImGui::NewLine();
    }

    {
        ImGui::SeparatorText(" RunCallback");

        if (ImGui::Button("RunCallbackLoop"))
        {
            WPrintFLog(L"RunCallbackLoop");
            gRunCallbackLoop = true;
        }

        ImGui::SameLine();
        if (ImGui::Button("StopRunCallbackLoop"))
        {
            WPrintFLog(L"StopRunCallbackLoop");
            gRunCallbackLoop = false;
        }

        ImGui::NewLine();
    }

    {
        ImGui::SeparatorText(" Get Data");

        if (ImGui::Button("GetToken"))
            Base_GetAccessTokenTest();

        ImGui::SameLine();
        if (ImGui::Button("GetUser"))
            Base_GetUserTest();

        ImGui::SameLine();
        if (ImGui::Button("GetGds"))
            Base_GetGdsTest();

        ImGui::SameLine();
        if (ImGui::Button("GetSignin"))
            Base_GetSigninTest();

        ImGui::NewLine();
    }

    {
        ImGui::SeparatorText(" Etc");

        if (ImGui::Button("BaseGetVersion"))
            Base_GetVersionTest();

        ImGui::NewLine();
    }
}

void ImGuiOwnershipSDKTabImpl()
{
    ImGui::Text("# OwnersipSDK Test");  ImGui::NewLine();

    {
        ImGui::SeparatorText("Get Data");

        if (ImGui::Button("OwnershipList"))
            Ownership_OwnershipListTest();

        ImGui::NewLine();
    }

    {
        ImGui::SeparatorText("Etc");

        if (ImGui::Button("OwnershipGetVersion"))
            Ownership_GetVersionTest();

        ImGui::NewLine();
    }
}
