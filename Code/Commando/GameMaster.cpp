
#include "GameMaster.h"

#include <cstdio>

#include "combat.h"
#include "physicalgameobj.h"
#include "smartgameobj.h"
#include "god.h"
#include "objlibrary.h"
#include "soldier.h"
#include "playertype.h"
#include "soldier.h"
#include "vehicle.h"
#include "soldierobserver.h"

bool GameMaster::_isGameMaster = false;
bool GameMaster::_isPossessingOther = false;
SoldierGameObj* GameMaster::_cachedMasterSoldier; //  we need to somehow clean this up
int GameMaster::_lastVehiclePlayerType = PLAYERTYPE_NOD;
DefinitionClass* GameMaster::_selectedDefinition;

void GameMaster::BecomeGameMaster(void) {
	_isGameMaster = !_isGameMaster;
	if (_isGameMaster) {
		InitialSetup();
	}
}

void GameMaster::InitialSetup()
{
	EncyclopediaMgrClass::Reveal_All_Objects ();

	if (COMBAT_STAR != NULL)
	{
		ReleaseControl(true);
	}

	//  todo: spawn in a dummy invis soldier and set fly mode so we can explore?
	if (_cachedMasterSoldier == NULL)
	{
		PhysicalGameObj* newPlayer = ObjectLibraryManager::Create_Object("Walk-Thru");
		_cachedMasterSoldier = newPlayer->As_SoldierGameObj();
		_cachedMasterSoldier->Enable_Ghost_Collision(true);
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
	//  figure out if its a soldier or vehicle
	SoldierGameObj* soldier = targetObject->As_SoldierGameObj();
	VehicleGameObj* vehicle = targetObject->As_VehicleGameObj();
	if (soldier != NULL)
	{
		_cachedMasterSoldier->Control_Enable(false);
		ReleaseControl(false);
		soldier->Remove_Innate_Observer();
		soldier->Clear_Innate_Observer();
		

		// soldier->Start_Observers();
		soldier->Set_Control_Owner(CombatManager::Get_My_Id());
		soldier->Control_Enable(true);
		soldier->Reset_Controller();
		CombatManager::Set_The_Star(soldier);

		
		ActionParamsStruct parameters;
		soldier->Get_Action()->Begin_Hibernation();
		soldier->Get_Action()->Follow_Input(parameters);
		soldier->Generate_Control();


	}
	else if (vehicle != NULL)
	{
		if (_cachedMasterSoldier != NULL)
		{
			_lastVehiclePlayerType = vehicle->Get_Player_Type();
			_cachedMasterSoldier->Set_Player_Type(_lastVehiclePlayerType);
			vehicle->Add_Occupant(_cachedMasterSoldier);
			vehicle->Generate_Control();
		}
	}
}

bool GameMaster::IsGameMaster()
{
	return _isGameMaster;
}

bool GameMaster::IsPossessingOther()
{
	return IsGameMaster() && _cachedMasterSoldier != NULL && COMBAT_STAR != _cachedMasterSoldier;
}

void GameMaster::RevertToMasterObject()
{
	if (_cachedMasterSoldier == NULL)
	{
		return;
	}

	VehicleGameObj* vehicle = _cachedMasterSoldier->Get_Vehicle();
	_cachedMasterSoldier->Exit_Vehicle();
	if (vehicle != NULL)
	{
		vehicle->Set_Player_Type(_lastVehiclePlayerType);
		vehicle->Start_Observers();
	}
	_cachedMasterSoldier->Set_Player_Type(PLAYERTYPE_SPECTATOR);

	ReleaseControl(true);
	ControlObject(_cachedMasterSoldier);
	_cachedMasterSoldier->Enable_Ghost_Collision(true);
	_cachedMasterSoldier->Toggle_Fly_Mode();
}


void GameMaster::ReleaseControl(bool reinitAI) {
	SoldierGameObj* curr = COMBAT_STAR;
	if (_cachedMasterSoldier != NULL) {
		_cachedMasterSoldier->Set_Transform(curr->Get_Transform());
	}
	if (reinitAI) {
		//  cGod::Reinitialize_Ai_On_Star();
		SoldierObserverClass* innate_ai = curr->Get_Innate_Controller();
		if (innate_ai == NULL)
		{
			curr->Set_Innate_Observer(new SoldierObserverClass());
			curr->Add_Observer(curr->Get_Innate_Observer());
		}
	}

		curr->Set_Control_Owner(SmartGameObj::SERVER_CONTROL_OWNER);
		curr->Generate_Control();
		curr->Start_Observers();
}

bool GameMaster::IsInVehicle()
{
	if (_cachedMasterSoldier == NULL)
	{
		return false;
	}

	return _cachedMasterSoldier->Get_Vehicle() != NULL;
}

void GameMaster::Think()
{
	return;
	if (_isGameMaster == true && IsPossessingOther() == false && IsInVehicle() == false)
	{
		_cachedMasterSoldier->Set_Player_Type(PLAYERTYPE_SPECTATOR);
	}
}

void GameMaster::SpawnObject(Vector3& pos)
{
	if (_selectedDefinition != NULL)
	{
		PhysicalGameObj *game_obj = (PhysicalGameObj *) _selectedDefinition->Create();
		if (game_obj != NULL)
		{
			game_obj->Set_Position(pos);
			SoldierGameObj* soldier = game_obj->As_SoldierGameObj();
			if (soldier != NULL	)
			{
				soldier->Set_Innate_Observer(new SoldierObserverClass());
				soldier->Start_Observers();
			}
		}
		
		
	}
}

SoldierGameObj* GameMaster::TryGetCachedSoldier()
{
	return _cachedMasterSoldier;
}

void GameMaster::SetSelectedDef(DefinitionClass* def)
{
	_selectedDefinition = def;
}
