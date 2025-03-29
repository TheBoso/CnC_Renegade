#include "DefinitionListDialog.h"

#include <dinput.h>

#include "definition.h"
#include "definitionmgr.h"
#include "dialogmgr.h"
#include "mousemgr.h"
#include "input.h"
#include "stylemgr.h"
#include "wwstring.h"
#include "GameMaster.h"
#include "listctrl.h"
#include "resource.h"

// Define the static member variable
DefinitionListDialog* DefinitionListDialog::gInstance = nullptr;

DefinitionListDialog::DefinitionListDialog()
    : PopupDialogClass(IDD_DEFINITION_LIST)
    , mDefinitionList(nullptr)
    , mIsVisible(false)
{
    gInstance = this;
}

DefinitionListDialog::~DefinitionListDialog()
{
    if (gInstance == this)
        gInstance = nullptr;
}

void DefinitionListDialog::DoDialog(void)
{
    // Only show dialog if we are the GameMaster
    if (!GameMaster::IsGameMaster())
        return;

    if (!gInstance)
    {
        START_DIALOG(DefinitionListDialog);
    }
}

void DefinitionListDialog::On_Init_Dialog(void)
{
    // Get the list control
    ListCtrlClass* list_ctrl = (ListCtrlClass*)Get_Dlg_Item(IDC_DEFINITION_LIST);
    if (list_ctrl)
    {
        mDefinitionList = list_ctrl;
        // Add a column for definition names
        mDefinitionList->Add_Column(L"Definition Name", 380, Vector3(1.0f, 1.0f, 1.0f));

        // Populate the list with definitions
        PopulateDefinitionList();
    }

    PopupDialogClass::On_Init_Dialog();
    mIsVisible = true;
}

void DefinitionListDialog::On_Destroy(void)
{
    mDefinitionList = nullptr;
    mIsVisible = false;
}

void DefinitionListDialog::On_Frame_Update(void)
{
    // Check if tab key is released
    if (!Input::Is_Button_Down(DIK_TAB))
    {
        End_Dialog();
    }
}

void DefinitionListDialog::On_Command(int ctrl_id, int message_id, DWORD param)
{
    if (ctrl_id == IDC_DEFINITION_LIST && message_id == 0) // List control selection changed
    {
        OnDefinitionSelected(param);
    }
}

void DefinitionListDialog::PopulateDefinitionList(void)
{
    if (!mDefinitionList)
        return;

    // Clear existing items
    mDefinitionList->Delete_All_Entries();

    // Get all definitions
    DefinitionClass* def = DefinitionMgrClass::Get_First();
    while (def)
    {
        // Add definition name to list
        WideStringClass name;
        name.Convert_From(def->Get_Name());
        mDefinitionList->Insert_Entry(-1, name);
        def = DefinitionMgrClass::Get_Next(def);
    }
}

void DefinitionListDialog::OnDefinitionSelected(int index)
{
    if (!mDefinitionList || index < 0)
        return;

    // Get the selected definition
    DefinitionClass* def = DefinitionMgrClass::Get_First();
    for (int i = 0; i < index && def; i++)
    {
        def = DefinitionMgrClass::Get_Next(def);
    }

    if (def)
    {
        // Set the GameMaster's selected definition
        GameMaster::SetSelectedDef(def);
        End_Dialog();
    }
} 