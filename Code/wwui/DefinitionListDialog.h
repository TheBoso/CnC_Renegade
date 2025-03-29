#pragma once

#include "popupdialog.h"

class DefinitionListDialog : public PopupDialogClass
{
public:
    DefinitionListDialog();
    virtual ~DefinitionListDialog();

    static void DoDialog(void);

protected:
    virtual void On_Init_Dialog(void);
    virtual void On_Destroy(void);
    virtual void On_Frame_Update(void);
    virtual void On_Command(int ctrl_id, int message_id, DWORD param);

private:
    void PopulateDefinitionList(void);
    void OnDefinitionSelected(int index);

    static DefinitionListDialog* gInstance;
    ListCtrlClass* mDefinitionList;
    bool mIsVisible;
}; 