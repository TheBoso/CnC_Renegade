#if defined(_MSC_VER)
#pragma once
#endif

class PhysicalGameObj;
class GameMaster
{
    public:
    static void BecomeGameMaster(void);
    static void ControlObject(PhysicalGameObj* targetObject);
    static void ShowEditPanel(PhysicalGameObj* targetObject);

    static bool IsGameMaster()
    {
        return _isGameMaster;
    }
    
    private:
    static bool _isGameMaster;


};  