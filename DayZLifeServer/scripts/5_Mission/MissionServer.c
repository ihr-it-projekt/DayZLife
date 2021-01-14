modded class MissionServer {

    private ref DZLEventManager manager;
    private ref DZLBuilderManager builderManager;
	private ref Timer paycheckTimer;
	private ref DZLCheckController checkController;

	void MissionServer() {
        DebugMessageDZL("Load DayZLifeServer");
        paycheckTimer = new Timer;
	}

	override void OnInit() {
	    super.OnInit();
		DZLDatabase database = DZLSpawnHelper.SpawnDataBase();
		if (database) {
            manager = new DZLEventManager;
            builderManager = new DZLBuilderManager;
            checkController = new DZLCheckController;

            DZLLockedHouses.OnServerStart();
            paycheckTimer.Run(1, checkController, "Check", null, true);
            builderManager.Create();
        }
    }

	override PlayerBase OnClientNewEvent(PlayerIdentity identity, vector pos, ParamsReadContext ctx){
		DZLPlayer dzlPlayer = DZLDatabaseLayer.Get().GetPlayer(identity.GetId());
		if (dzlPlayer.WillHealByMedic() || dzlPlayer.WillHealByHospital()) {
		    DZLStoreItem playerData = dzlPlayer.GetPlayerData();

            string type = "SurvivorF_Judy";
			if (playerData) {
			    pos = playerData.positionOfStore;
			    type = playerData.type;
			}

			if (dzlPlayer.WillHealByHospital()) {
				DZLBaseSpawnPoint spawnPoint = DZLConfig.Get().medicConfig.hospitalSpawnPoints.GetRandomElement();
				pos = spawnPoint.point;
			}
			
		    CreateCharacter(identity, pos, ctx, type);

			if (playerData) {
                array<ref DZLStoreItem> items = playerData.GetAttached();
                foreach(DZLStoreItem item: items) {
                    DZLSpawnHelper.Add(m_player, item);
                }
			}
			float factor = 1.0;
			float factorShock = 1.0;
			if (dzlPlayer.WillHealByMedic()) {
			    factor = 0.5;
			    factorShock = 0;
			}
			m_player.SetHealth01("GlobalHealth", "Health", factor);
            m_player.SetHealth01("GlobalHealth", "Shock", factorShock);
            m_player.SetHealth01("GlobalHealth", "Blood", factor);

		} else {
		    super.OnClientNewEvent(identity, pos, ctx);
		    GetGame().RPCSingleParam(m_player, DAY_Z_LIFE_NEW_SPAWN_CLIENT, null, true, identity);
		}
		
        dzlPlayer.ResetDeadState();

		return m_player;
	}
}
