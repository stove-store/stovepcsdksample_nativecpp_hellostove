#pragma once

#ifdef __cplusplus
extern "C" {
#endif
    /*
    * @brief StartStoveVerify
    * @details StovePCSDK의 DLL이 변조되지 않았는지 확인하는 함수
    * @details StovePCSDK의 DLL이 변조된 것이 확인되면 즉시 프로그램을 종료합니다.
    *          해당 함수는 Release 배포 빌드에서만 사용을 해야합니다.
    */
    void StartStoveVerify();
#ifdef __cplusplus
}
#endif