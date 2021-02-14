class DZLRaidChecker
{
    private ref DZLBankingConfig config;
    private float time = 300;
    private int timeHappened = 0;
    private ref Timer raidTimer;
    private PlayerBase player;
    private DZLBankingPosition position;

    void DZLRaidChecker(PlayerBase player) {
        this.player = player;
        config = player.config.bankConfig;
        time = config.raidTimeBankInSeconds;
    }
    
    void Start(DZLBankingPosition position) {
		this.position = position;
        raidTimer = new Timer;
        timeHappened = 0;
        raidTimer.Run(1, this, "Finish", null, true);
    }
    
    void Finish() {
        if (time > timeHappened) {
            if (!isInNearOfBankAndLocationIsEnabled()) {
                raidTimer.Stop();
                GetGame().RPCSingleParam(player, DAY_Z_LIFE_BANK_RAID_CANCELED, null, true, player.GetIdentity());
                return;
            }

            if (timeHappened % 300 == 1) {
                int leftMinutes = (time - timeHappened) / 60;
                player.DisplayMessage("#bank_rob_will_finished_in " + leftMinutes.ToString());
            }
            
            timeHappened++;
            return;
        }

        raidTimer.Stop();
        GetGame().RPCSingleParam(player, DAY_Z_LIFE_BANK_RAID_FINISHED, null, true, player.GetIdentity());
    }

    private bool isInNearOfBankAndLocationIsEnabled() {
        if (!player) {
            return false;
        }

        if (!player.IsAlive() || player.IsRestrained() || player.IsUnconscious()) {
            return false;
        }

        vector playerPosition = player.GetPosition();
        if (!playerPosition) {
            return false;
        }

        return position && position.position && vector.Distance(position.position, playerPosition) <= config.maximumRaidDistanceToBank);
    }
}