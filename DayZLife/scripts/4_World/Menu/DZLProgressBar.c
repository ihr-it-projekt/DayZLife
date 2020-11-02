class DZLProgressBar: UIScriptedMenu
{
    private ref DZLUIItemCreator creator;
    private PlayerBase player;
    private DZLPlayer dzlPlayer;
    private DZLLicence licence;
	private ProgressBarWidget progressBar;
	private TextWidget status;
	private ref Timer timer;
	private int iterations;

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
		iterations = 0;
		
		return layoutRoot;
    }

    override void OnShow() {
        timer.Run(1, this, "CheckDuration", null, true);
		GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_INVENTORY);
        GetGame().GetUIManager().ShowCursor(true);
        GetGame().GetInput().ChangeGameFocus(1);
		
		SetLicence(player.GetLicenceByPosition());
        progressBar.SetCurrent(0);
        status.SetText("0");
    }
	
	void CheckDuration() {
	    DebugMessageDZL("licence.durationForCrafting " + licence.durationForCrafting);
	    iterations++;
		if (iterations >= licence.durationForCrafting) {
		    progressBar.SetCurrent(100);
            status.SetText("100");
			GetGame().RPCSingleParam(player, DAY_Z_LIFE_BUY_LICENCE_USE, new Param2<PlayerBase, string>(player, licence.id), true);
			OnHide();
		} else {
            vector playerPosition = player.GetPosition();

		    if (vector.Distance(licence.position, playerPosition) > licence.range){
		        OnHide();
		        return;
		    }

			float percent = iterations / licence.durationForCrafting  * 100;
			
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