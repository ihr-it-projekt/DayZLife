class DZLProgressBar: UIScriptedMenu
{
    private ref DZLUIItemCreator creator;
    private PlayerBase player;
    private DZLPlayer dzlPlayer;
    private DZLLicence licence;
	private ProgressBarWidget progressBar;
	private TextWidget status;
	private ref Timer timer;

    private void SetLicence(DZLLicence licence) {
		this.licence = licence;
    }

    void SetPlayer(PlayerBase player) {
        this.player = player;
        this.dzlPlayer = player.dzlPlayer;
    }

    void UpdatePlayer(PlayerBase player) {
        SetPlayer(player);
    }

    override Widget Init() {
        player = PlayerBaseHelper.GetPlayer();
        creator = new DZLUIItemCreator("DayZLife/layout/Processing/Processing_bar.layout");
		progressBar = creator.GetProgressBarWidget("Status_bar");
		status = creator.GetTextWidget("Status");

        layoutRoot = creator.GetLayoutRoot();
		
		timer = new Timer;
		
		return layoutRoot;
    }

    override void OnShow() {
        timer.Run(1, this, "CheckDuration", null, true);
		GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_INVENTORY);
        GetGame().GetUIManager().ShowCursor(true);
        GetGame().GetInput().ChangeGameFocus(1);
    }
	
	void CheckDuration() {
		if (timer.GetDuration() >= licence.durationForCrafting) {
			GetGame().RPCSingleParam(player, DAY_Z_LIFE_BUY_LICENCE_USE, new Param2<PlayerBase, string>(player, licence.id), true);
			OnHide();
		} else {
            vector playerPosition = player.GetPosition();

		    if (vector.Distance(licence.position, playerPosition) <= licence.range){
		        OnHide();
		        return;
		    }

			//  20 - 5 = 15 
			// 15 * secInPerc = procNoOffen 
			// 100 - proceNoOffe = procdone
		 
			float percent = 100 - ((licence.durationForCrafting - timer.GetDuration()) * (licence.durationForCrafting / 100));
			
			progressBar.SetCurrent(percent);
			status.SetText(percent.ToString());
		}
	}

    override void OnHide() {
        timer.Stop();
        super.OnHide();
        GetGame().GetUIManager().ShowCursor(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetMission().PlayerControlEnable(true);
        Close();
    }
}