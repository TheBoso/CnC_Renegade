
#include "GameMaster.h"
S
#include "combat.h"
#include "smartgameobj.h"

bool GameMaster::_isGameMaster = false;



 void GameMaster::BecomeGameMaster() 
{
    _isGameMaster = !_isGameMaster;
    if (_isGameMaster) 
    {
        if(COMBAT_STAR != NULL)
        {
          cGod::Reinitialize_Ai_On_Star();
        }
        //  todo: spawn in a dummy invis soldier and set fly mode so we can explore?
        CombatManager::Set_The_Star(NULL);
    }
}

void GameMaster::ShowEditPanel(PhysicalGameObj* targetObject)
{
//  todo: something similar to the edit vehicle console command for whatever unit we looking at ig?
}

 void GameMaster::ControlObject(PhysicalGameObj* targetObject)
 {
     //  figure out if its a soldier or vehicle
SoldierGameObj* soldier = targetObject->As_SoldierGameObj();
VehicleGameObj* vehicle = targetObject->As_VehicleGameObj();
if(soldier != NULL)
{
ComabtManager::Set_The_Soldier(soldier);
}
else if(vehicle != NULL)
{
//  we probably create a new character, set the player type to whatever the vehicle is, then hijack it.
}
}