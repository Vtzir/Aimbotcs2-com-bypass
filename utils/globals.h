// Generated using https://github.com/a2x/cs2-dumper
// 2024-08-22 00:13:39.639692900 UTC

#pragma once
#include "../cheat/vector.h"


struct globals
{

    //system
    bool Run = true;
    bool ShowMenu = true;


    //aim
    bool AimBot = false;
    bool visibleCheck;
    bool AimRCS;
    float aimfov = 45.f;
    //float fovSpedd = 1.5f;
    float AimSmooth = 2.5f;
    bool AimSmooTh = false;
    bool Aimfov = false;
    int AimKey;

    //visuals
    float screenfov = 0.f;
    bool visuals = false;
    bool esp = false;
    bool e_box = false;
    bool e_line = false;
    bool skeleton = false;

};
extern globals g;



namespace offsets
{
    // Module: client.dll
 
    constexpr std::ptrdiff_t dwLocalPlayerPawn = 0x1855CE8;
    constexpr std::ptrdiff_t dwEntityList = 0x19F2488;
    constexpr std::ptrdiff_t m_iTeamNum = 0x3E3;
    constexpr std::ptrdiff_t m_vOldOrigin = 0x1324; //vector3
    constexpr std::ptrdiff_t m_vecViewOffset = 0xCB0;
    constexpr std::ptrdiff_t m_lifeState = 0x348;
    constexpr std::ptrdiff_t m_entitySpottedState = 0x11A8;
    constexpr std::ptrdiff_t m_bSpotted = 0x8;
    constexpr std::ptrdiff_t m_bSpottedByMask = 0xC;
    constexpr std::ptrdiff_t dwViewRender = 0x1A54D60;
    constexpr std::ptrdiff_t m_modelState = 0x170;
    constexpr std::ptrdiff_t dwViewAngles = 0x1A5E650;
    constexpr std::ptrdiff_t dwViewMatrix = 0x1A54550;
    constexpr std::ptrdiff_t m_pGameSceneNode = 0x328;
    constexpr std::ptrdiff_t m_hPlayerPawn = 0x80C;
    constexpr std::ptrdiff_t m_iHealth = 0x344;
    constexpr std::ptrdiff_t m_aimPunchAngle = 0x1574;
    constexpr std::ptrdiff_t m_hPawn = 0x62C;
    constexpr std::ptrdiff_t m_pCameraServices = 0x11E0;
    constexpr std::ptrdiff_t m_iFOV = 0x210;
    constexpr std::ptrdiff_t m_bIsScoped = 0x23D0;
    constexpr std::ptrdiff_t m_iszPlayerName = 0x660;
    constexpr std::ptrdiff_t m_sSanitizedPlayerName = 0x770;
    constexpr std::ptrdiff_t m_bUseScreenAspectRatio = 0x585; // bool
}