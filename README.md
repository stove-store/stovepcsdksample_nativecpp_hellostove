# PC SDK 3.x NativeCpp HelloStove Sample 


## Development Environment
 - VisualStudio 2022
 - Windows SDK 10.x
 - C++20
 - Solution Configuration : Debug, Release
 - Solution Platform : x86, x64


## Required SDK Functions for Game Integration
  - BaseSDK
    - Base_RestartAppIfNecessary
    - Base_Initialize
    - Base_UnInitialize
    - Base_RunCallback
  - OwnershipSDK
    - Ownership_OwnershipList


## Preparation
 - Copy StovePCSDK v3.x to the folder structure as shown below
 
```
Depends
└ StovePCSDK
  ├ BaseSDK
  | └ Deploy
  │   ├ Bin
  │   │ ├ Win32
  │   │ │└ Release
  │   │ │  └ BaseSDK.dll
  │   │ └ x64
  │   │   └ Release
  │   │    └ BaseSDK.dll
  │   ├ Include
  │   │ ├ Misc
  │   │ │ ├ result
  │   │ │ │ └ result.h
  │   │ │ ├ BaseSDKResult.h
  │   │ │ ├ Callbacks.h
  │   │ │ ├ Enumerations.h
  │   │ │ ├ SDKExports.h
  │   │ │ ├ Structures.h
  │   │ └ BaseSDK.h
  │   └ Lib
  │     ├ Win32
  │     │ └ Release
  │     │   └ BaseSDK.lib
  │     └ x64
  │       └ Release
  │         └ BaseSDK.lib
  └ OwnershipSDK
      ├ Bin
      │ ├ Win32
      │ │└ Release
      │ │  └ OwnershipSDK.dll
      │ └ x64
      │   └ Release
      │    └ OwnershipSDK.dll
      ├ Include
      │ ├ Misc
      │ │ ├ OwnershipSDKResult.h
      │ │ ├ Callbacks.h
      │ │ ├ Enumerations.h
      │ │ ├ Structures.h
      │ └ OwnershipSDK.h
      └ Lib
        ├ Win32
        │ └ Release
        │   └ OwnershipSDK.lib
        └ x64
          └ Release
            └ OwnershipSDK.lib
```