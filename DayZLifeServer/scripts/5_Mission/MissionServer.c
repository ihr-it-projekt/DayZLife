modded class MissionServer {

    private ref DZLEventManager manager;
    private ref Timer paycheckTimer;
    private ref Timer storageTimer;
    private ref DZLCheckController checkController;
    private ref DZLStorageController storageController;

    void MissionServer() {
        paycheckTimer = new Timer;
        storageTimer = new Timer;
    }

    override void OnInit() {
        super.OnInit();

        CheckDZLDataPath();
        CheckDZLConfigPath();
        CheckDZLLogPath();

        manager = new DZLEventManager;
        checkController = new DZLCheckController;
        storageController = new DZLStorageController;

        paycheckTimer.Run(60, checkController, "Check", null, true);
        storageTimer.Run(60, storageController, "Check", null, true);

        DZLConfig.Get();
        DZLBuilderManager.Get().Create();
    }

    override PlayerBase OnClientNewEvent(PlayerIdentity identity, vector pos, ParamsReadContext ctx) {
        PlayerBase player = super.OnClientNewEvent(identity, pos, ctx);

#ifndef TBRevivePlayerServer
        g_Game.RPCSingleParam(null, DZL_RPC.NEW_SPAWN_CLIENT, null, true, identity);
#endif

        return player;
    }

}
