 modded class MissionGameplay
 {


 	 override void OnKeyRelease(int key) {
 	    PlayerBase player = PlayerBaseHelper.GetPlayer();

 	    if (!player) return;

		super.OnKeyRelease(key);
		 switch (key){
			case KeyCode.KC_ESCAPE:
				player.CloseMenu();
				break;
			case KeyCode.KC_LCONTROL + KeyCode.KC_RCONTROL:
				GetGame().GetUIManager().ShowScriptedMenu(player.GetAlmanacMenu(), NULL);
				break;
			default:
				break;
		}
		 
	 }
	
 }
