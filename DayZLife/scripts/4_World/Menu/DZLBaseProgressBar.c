class DZLBaseProgressBar: UIScriptedMenu
{
    protected ref DZLUIItemCreator creator;
    protected PlayerBase player;
    protected DZLPlayer dzlPlayer;
	protected ProgressBarWidget progressBar;
	protected TextWidget status;
	protected ref Timer timer;
	protected int iterations;
	protected int duration;
	protected int maxRange;
	protected vector position;

   void SetPlayer(PlayerBase player) {
        this.player = player;
        this.dzlPlayer = player.dzlPlayer;
    }

    void UpdatePlayer(PlayerBase player) {
        SetPlayer(player);
    }
	
	void SetDuration(int duration) {
		this.duration = duration;
	}
	void SetMaxRange(int maxRange) {
		this.maxRange = maxRange;
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

        progressBar.SetCurrent(0);
        status.SetText("0");
    }
	
	void CheckDuration() {
	    iterations++;
		if (iterations >= duration) {
		    progressBar.SetCurrent(100);
            status.SetText("100");
			SendFinishEvent();
			OnHide();
		} else {
            vector playerPosition = player.GetPosition();

		    if (vector.Distance(position, playerPosition) > maxRange){
		        OnHide();
		        return;
		    }

			float percent = iterations / duration  * 100;
			
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

    void SendFinishEvent() {
    }
}