modded class MissionGameplay 
{
 	
	ref DZLHudMenu hudMenu;
	   
    void MissionGameplay() {
        DebugMessageDZL("Load Client");
        
	}

	void ~MissionGameplay() {

	}


    override void OnKeyRelease(int key)
	{
		super.OnKeyRelease(key);

		if (hudMenu){
			switch (key){
				case KeyCode.KC_ESCAPE:
					if (hudMenu.IsVisible()) {
						hudMenu.Close();
					} 
					break;

				case KeyCode.KC_TAB:
					if (hudMenu.IsVisible()) {
						hudMenu.Close();
					} else {
						GetGame().GetUIManager().ShowScriptedMenu(hudMenu, NULL);
					}

					break;
				default:
					break;
			}
		} else {
			switch (key){
				case KeyCode.KC_TAB:
					hudMenu = new DZLHudMenu;
					GetGame().GetUIManager().ShowScriptedMenu(hudMenu, NULL);
					break;
				default:
					break;
			}
				
		}

	}
	
}