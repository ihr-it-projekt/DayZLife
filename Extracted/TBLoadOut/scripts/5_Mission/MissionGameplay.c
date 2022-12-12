modded class MissionGameplay
{
   	PlayerBase dzlPlayerBase;

	override void OnInit() {
		super.OnInit();
		TBLOPlayerClientDB.Get();
	}

    override void OnKeyRelease(int key) {
        dzlPlayerBase = TBLOPlayerBaseHelper.GetPlayer();

        if (!dzlPlayerBase) return;
        bool wasActionDone = false;
        switch (key){
            case KeyCode.KC_ESCAPE:
                wasActionDone = dzlPlayerBase.CloseMenu();
                break;
            default:
                break;
        }

        if (false == wasActionDone){
            super.OnKeyRelease(key);
        }
    }

 }
