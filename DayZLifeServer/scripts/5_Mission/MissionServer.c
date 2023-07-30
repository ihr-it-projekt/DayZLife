modded class MissionServer {

    private ref DZLEventManager manager;
    private ref DZLBuilderManager builderManager;
	private ref Timer paycheckTimer;
	private ref Timer storageTimer;
	private ref DZLCheckController checkController;
	private ref DZLStorageController storageController;

	void MissionServer() {
        DebugMessageDZL("Load DayZLifeServer");
        paycheckTimer = new Timer;
        storageTimer = new Timer;
	}

	override void OnInit() {
	    super.OnInit();

        manager = new DZLEventManager;
        builderManager = new DZLBuilderManager;
        checkController = new DZLCheckController;
        storageController = new DZLStorageController;

        DZLLockedHouses.OnServerStart();
        paycheckTimer.Run(60, checkController, "Check", null, true);
        storageTimer.Run(60, storageController, "Check", null, true);
        builderManager.Create();
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
			float factorShock = 1.0;
			float factorBlood = 1.0;
			float factorHealth = 1.0;
			if (dzlPlayer.WillHealByMedic()) {
			    factorHealth = 0.5;
			    factorBlood = 0.4;
			    factorShock = 0;
				array<string> damageZone = new array<string>;
			
				damageZone.Insert("RightFoot");
				damageZone.Insert("LeftFoot");
				damageZone.Insert("LeftForeArmRoll");
				damageZone.Insert("RightForeArmRoll");
				damageZone.Insert("Neck");
				damageZone.Insert("Spine2");
				damageZone.Insert("Head");
				
				int randCut = Math.RandomIntInclusive(0, 6);
				
				for(int x = 0; x < randCut; x++) {
					string damageZ = damageZone.GetRandomElement();
					m_player.GetBleedingManagerServer().AttemptAddBleedingSourceBySelection(damageZ);
					factorBlood += 0.1;
				}
			}
			
			m_player.SetHealth01("GlobalHealth", "Health", factorHealth);
            m_player.SetHealth01("GlobalHealth", "Shock", factorShock);
            m_player.SetHealth01("GlobalHealth", "Blood", factorBlood);
		} else {
		    super.OnClientNewEvent(identity, pos, ctx);
		    GetGame().RPCSingleParam(null, DAY_Z_LIFE_NEW_SPAWN_CLIENT, null, true, identity);
		}
		
        dzlPlayer.ResetDeadState();
        DZLDatabaseLayer.Get().GetEmergencies().Remove(identity.GetId());

		return m_player;
	}
}
