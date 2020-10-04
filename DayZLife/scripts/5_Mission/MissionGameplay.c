modded class MissionGameplay 
{
    void MissionGameplay() {
        DebugMessageDZL("Load Client");
        DLBuyHouseMenu.ClearInstance();
        DLBuyHouseMenu.GetInstance();
	}
	
	void ~MissionGameplay() {
        DLBuyHouseMenu.ClearInstance();
	}
}