
#include "GameMaster.h"
#include "combat.h"
#include "physicalgameobj.h"
#include "god.h"
#include "objlibrary.h"
#include "soldier.h"
#include "playertype.h"

bool GameMaster::_isGameMaster = false;

void GameMaster::BecomeGameMaster(void) {
    _isGameMaster = !_isGameMaster;
    if (_isGameMaster) {
        if (COMBAT_STAR != NULL) {
            cGod::Reinitialize_Ai_On_Star();
        }
          
        //  todo: spawn in a dummy invis soldier and set fly mode so we can explore?
        PhysicalGameObj* newPlayer = ObjectLibraryManager::Create_Object("Walk-Thru");
        SoldierGameObj* soldier = newPlayer->As_SoldierGameObj();
        soldier->Peek_Model()->Set_Hidden(true);
        soldier->Toggle_Fly_Mode();
        soldier->Set_Player_Type(PLAYERTYPE_SPECTATOR);
        ControlObject(newPlayer);
    }
}

void GameMaster::ShowEditPanel(PhysicalGameObj* targetObject) {
    //  todo: something similar to the edit vehicle console command for whatever
    //  unit we looking at ig?
}

void GameMaster::ControlObject(PhysicalGameObj* targetObject) {
    //  figure out if its a soldier or vehicle
    SoldierGameObj* soldier = targetObject->As_SoldierGameObj();
    VehicleGameObj* vehicle = targetObject->As_VehicleGameObj();
    if (soldier != NULL)
    {
        CombatManager::Set_The_Star(soldier);
        soldier->Control_Enable (true);
        soldier->Set_Control_Owner (CombatManager::Get_My_Id ());
    } else if (vehicle != NULL) {
        //  we probably create a new character, set the player type to whatever the
        //  vehicle is, then hijack it.
    }
}

bool GameMaster::IsGameMaster()
{
return _isGameMaster;
}