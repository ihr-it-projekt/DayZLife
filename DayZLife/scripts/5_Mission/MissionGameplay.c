modded class MissionGameplay 
{
	private ref DZLBuyHouseMenu houseMenu;
	
    void MissionGameplay() {
		houseMenu = DZLBuyHouseMenu.GetInstance();
        DebugMessageDZL("Load Client");
	}
	
}