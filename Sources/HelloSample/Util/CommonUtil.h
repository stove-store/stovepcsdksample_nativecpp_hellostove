#pragma once
#include <wctype.h>
#include <stdarg.h>
#include <string>
#include <sstream>

#define NEW_LINE()  wprintf(L"\n")


#pragma region Functions

bool IsNumericA(const char* str);
bool IsNumericW(const wchar_t* wstr);
int64_t WStrToInt64(const wchar_t* wstr);
std::wstring Str2WStr(const std::string& charArray);
void RemoveTrailingNewline(wchar_t* wstr);
void WPrintFTitle(const wchar_t* format, ...);
void WPrintFLog(const wchar_t* format, ...);

#pragma endregion



#pragma region Functions Impl

bool IsNumericA(const char* str)
{
    if (str == nullptr || *str == '\0')
        return false;

    while (*str)
    {
        if (!isdigit((unsigned char)*str))
        {
            return false;
        }
        str++;
    }

    return true;
}

bool IsNumericW(const wchar_t* wstr)
{
    if (wstr == nullptr || *wstr == L'\0')
        return false;

    while (*wstr)
    {
        if (!iswdigit(*wstr))
        {
            return false;
        }
        wstr++;
    }

    return true;
}

int64_t WStrToInt64(const wchar_t* wstr)
{
    wchar_t* endptr = nullptr;
    return wcstoll(wstr, &endptr, 10);
}

std::wstring Str2WStr(const std::string& str)
{
    std::wstring wstr;

    // 필요한 버퍼 크기 계산
    int bufferSize = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
    if (bufferSize == 0)
        return wstr;

    // wchar_t 버퍼 할당
    wstr.resize(bufferSize, 0);
    wchar_t* wCharArray = new wchar_t[bufferSize];

    // 변환 수행
    int result = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, wCharArray, bufferSize);
    if (result == 0)
    {
        delete[] wCharArray;
        return wstr;
    }

    wstr.assign(wCharArray);
    delete[] wCharArray;

    return wstr;
}

void RemoveTrailingNewline(wchar_t* wstr)
{
    size_t len = wcslen(wstr);

    if (len > 0 && wstr[len - 1] == L'\n')
    {
        wstr[len - 1] = L'\0';
    }
}

void WPrintFTitle(const wchar_t* format, ...)
{
    std::wstringstream wss;
    wss << L" ---> ";
    wss << format;
    wss << L" <---\n";

    va_list args;
    va_start(args, format);
    vwprintf(wss.str().c_str(), args);
    va_end(args);
}

void WPrintFLog(const wchar_t* format, ...)
{
    std::wstringstream wss;
    wss << L" - ";
    wss << format << L"\n";

    va_list args;
    va_start(args, format);
    vwprintf(wss.str().c_str(), args);
    va_end(args);
}

#pragma endregion