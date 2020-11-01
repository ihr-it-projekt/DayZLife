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
			 default:
				 break;
		}
		 
	 }
	
 }