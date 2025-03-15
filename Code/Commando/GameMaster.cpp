
#include "GameMaster.h"
#include "combat.h"
#include "physicalgameobj.h"
#include "god.h"
#include "objlibrary.h"
#include "soldier.h"
#include "playertype.h"
#include "soldier.h"

bool GameMaster::_isGameMaster = false;
bool GameMaster::_isPossessingOther = false;
SoldierGameObj* GameMaster::_cachedMasterSoldier;

void GameMaster::BecomeGameMaster(void) {
    _isGameMaster = !_isGameMaster;
    if (_isGameMaster) {
        InitialSetup();
    }
}

void GameMaster::InitialSetup()
{
    if (COMBAT_STAR != NULL)
    {
        ReleaseControl(true);
    }
          
    //  todo: spawn in a dummy invis soldier and set fly mode so we can explore?
    if(_cachedMasterSoldier == NULL)
    {
        PhysicalGameObj* newPlayer = ObjectLibraryManager::Create_Object("Walk-Thru");
        _cachedMasterSoldier = newPlayer->As_SoldierGameObj();
        _cachedMasterSoldier->Toggle_Fly_Mode();
        _cachedMasterSoldier->Set_Player_Type(PLAYERTYPE_SPECTATOR);
        _cachedMasterSoldier->Set_Transform(COMBAT_STAR->Get_Transform());
        ControlObject(newPlayer);
        _cachedMasterSoldier->Peek_Model()->Set_Hidden(true);
    } 
}

void GameMaster::ShowEditPanel(PhysicalGameObj* targetObject) {
    //  todo: something similar to the edit vehicle console command for whatever
    //  unit we looking at ig?
}

void GameMaster::ControlObject(PhysicalGameObj* targetObject)
    {
    ReleaseControl(false);
    //  figure out if its a soldier or vehicle
    SoldierGameObj* soldier = targetObject->As_SoldierGameObj();
    VehicleGameObj* vehicle = targetObject->As_VehicleGameObj();
    if (soldier != NULL)
    {
        ActionParamsStruct parameters;
        soldier->Get_Action()->Follow_Input( parameters );

        soldier->Control_Enable (true);
        soldier->Set_Control_Owner (CombatManager::Get_My_Id ());
        soldier->Generate_Control();
        CombatManager::Set_The_Star(soldier);

    } else if (vehicle != NULL) {
        //  we probably create a new character, set the player type to whatever the
        //  vehicle is, then hijack it.
    }
}

bool GameMaster::IsGameMaster()
{
return _isGameMaster;
}

bool GameMaster::IsPossessingOther()
{
return IsGameMaster() && COMBAT_STAR != _cachedMasterSoldier;
}

void GameMaster::RevertToMasterObject()
{
ControlObject(_cachedMasterSoldier);
}


void GameMaster::ReleaseControl(bool reinitAI)
{
SoldierGameObj* curr = COMBAT_STAR;
    if(reinitAI)
{
    cGod::Reinitialize_Ai_On_Star();
}
    curr->Set_Control_Owner(SmartGameObj::SERVER_CONTROL_OWNER);
    curr->Generate_Control();
}