#if defined(_MSC_VER)
#pragma once
#endif

class PhysicalGameObj;
class SoldierGameObj;

class GameMaster
{ 
    public:
    static void BecomeGameMaster(void);
    static void ControlObject(PhysicalGameObj* targetObject);
    static void ShowEditPanel(PhysicalGameObj* targetObject);
    static void ReleaseControl(bool giveBackAI);
    static bool IsGameMaster();
    static bool IsPossessingOther();
    static void RevertToMasterObject();
static bool IsInVehicle();
    
    private:
    static bool _isGameMaster;
    static SoldierGameObj* _cachedMasterSoldier;
    static bool _isPossessingOther;
    static void InitialSetup();


};  