modded class MissionGameplay{
    private bool holdRControl = false;
    private bool holdLControl = false;
	private UIScriptedMenu almanac;

    PlayerBase player

    override void OnKeyRelease(int key) {
        player = PlayerBaseHelper.GetPlayer();

        if (!player) return;

        switch (key){
            case KeyCode.KC_ESCAPE:
                player.CloseMenu();
                break;
            case KeyCode.KC_RCONTROL:
                holdRControl = false;
                break;
            case KeyCode.KC_LCONTROL:
                holdLControl = false;
                break;
            default:
                super.OnKeyRelease(key);
                break;
        }
    }

    override void OnKeyPress(int key) {
        player = PlayerBaseHelper.GetPlayer();
        if (!player) return;

        player = PlayerBaseHelper.GetPlayer();

        switch (key){
            case KeyCode.KC_RCONTROL:
                holdRControl = true;
				 
                if (holdRControl && holdLControl && !almanac && !GetGame().GetUIManager().IsCursorVisible()) {
                    almanac = GetGame().GetUIManager().ShowScriptedMenu(player.GetAlmanacMenu(), NULL);
                }

                break;
            case KeyCode.KC_LCONTROL:
                holdLControl = true;
                if (holdRControl && holdLControl && !almanac && !GetGame().GetUIManager().IsCursorVisible()) {
					almanac = GetGame().GetUIManager().ShowScriptedMenu(player.GetAlmanacMenu(), NULL);
                }

                break;
            default:
                super.OnKeyPress(key);
                break;
        }
    }
 }
