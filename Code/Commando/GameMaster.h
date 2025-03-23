#if defined(_MSC_VER)
#pragma once
#endif

class Vector3;
class DefinitionClass;
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
    static void Think();
    static void SpawnObject(Vector3& pos);
static bool IsInVehicle();
static SoldierGameObj* TryGetCachedSoldier();
    static void SetSelectedDef(DefinitionClass* def);
    
    private:
    static bool _isGameMaster;
    static SoldierGameObj* _cachedMasterSoldier;
    static int _lastVehiclePlayerType;
    static bool _isPossessingOther;
    static void InitialSetup();
    static DefinitionClass* _selectedDefinition;


};  