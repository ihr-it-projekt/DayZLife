 modded class MissionGameplay
 {
 	 override void OnKeyRelease(int key) {
		super.OnKeyRelease(key);
		 switch (key){
			 case KeyCode.KC_ESCAPE
				 PlayerBaseHelper.GetPlayer().CloseMenu();
				 break;
			 default:
				 break;
		}
		 
	 }
	
 }