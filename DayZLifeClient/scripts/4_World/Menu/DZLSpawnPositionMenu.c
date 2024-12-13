class DZLSpawnPositionMenu : DZLBaseMenu {
    private MapWidget spawnMap;
    private TextListboxWidget spawnPoints;
    private ButtonWidget randomSpawn;
    private ButtonWidget spawn;
    private int currentJobIndex = 0;
    private XComboBoxWidget jobSelection;
    private Widget warnText;
    bool isOpenOverMenu = false;

    private ref map<int, string> jobIndex = new map<int, string>;

    void DZLSpawnPositionMenu() {
        canClose = false;
        showHud = false;
        showQuickBar = false;
    }

    override void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if(rpc_type == DZL_RPC.NEW_SPAWN_RESPONSE) {
            g_Game.GetMission().GetHud().ShowHud(true);
            g_Game.GetMission().GetHud().ShowQuickBar(true);
            OnHide();
        }
    }

    override Widget Init() {
        layoutPath = "DayZLifeClient/layout/SpawnMenu/SpawnMenu.layout";

        super.Init();
        spawnMap = creator.GetMapWidget("map");
        spawnPoints = creator.GetTextListboxWidget("spawnPoints");
        randomSpawn = creator.GetButtonWidget("randomButton");
        spawn = creator.GetButtonWidget("spawnButton");
        jobSelection = creator.GetXComboBoxWidget("spawn");
        warnText = creator.GetWidget("warnText");

        spawn.Show(false);
        return layoutRoot;
    }

    override void OnShow() {
        super.OnShow();
        closeButton.Show(isOpenOverMenu);
        warnText.Show(isOpenOverMenu);


        jobSelection.ClearAll();
        jobIndex.Insert(jobSelection.AddItem("#Civil"), DAY_Z_LIFE_JOB_CIVIL);

        foreach(string jobName: config.jobConfig.paycheck.jobNames) {
            if(player.GetDZLPlayer().CanUseJob(jobName)) {
                jobIndex.Insert(jobSelection.AddItem("#" + jobName), jobName);
            }
        }

        UpdateSpawnPoints();
    }

    override bool OnClick(Widget w, int x, int y, int button) {
        if(super.OnClick(w, x, y, button)) return true;

        int index;
        DZLSpawnPoint point;

        if(w == randomSpawn) {
            index = Math.RandomIntInclusive(0, spawnPoints.GetNumItems() - 1);

            spawnPoints.GetItemData(index, 0, point);

            SendSpawnLocation(point, player);

            return true;
        } else if(w == spawn) {
            index = spawnPoints.GetSelectedRow();

            if(index == -1)return true;

            spawnPoints.GetItemData(index, 0, point);

            SendSpawnLocation(point, player);

            return true;
        } else if(w == spawnPoints) {
            index = spawnPoints.GetSelectedRow();

            if(index == -1)return true;

            spawnPoints.GetItemData(index, 0, point);

            DZLDisplayHelper.UpdateMap(spawnMap, point.point);

            spawn.Show(true);

            return true;
        } else if(w == jobSelection) {
            index = jobSelection.GetCurrentItem();
            if(index == -1) return true;

            currentJobIndex = index;

            UpdateSpawnPoints();
        }

        return false;
    }

    void SendSpawnLocation(DZLSpawnPoint point, PlayerBase _player) {
        string jobId = jobIndex.Get(currentJobIndex);
        g_Game.RPCSingleParam(_player, DZL_RPC.NEW_SPAWN, new Param2<string, string>(point.GetId(), jobId), true);
    }

    override void OnHide() {
        super.OnHide();
        g_Game.GetMission().GetHud().ShowHud(true);
        g_Game.GetMission().GetHud().ShowQuickBar(true);
    }

    private void UpdateSpawnPoints() {
        string jobId = jobIndex.Get(currentJobIndex);
        DZLJobSpawnPoints spawnPointCollection = config.GetJobSpawnPointsByJobId(jobId);

        spawnPoints.ClearItems();
        foreach(DZLSpawnPoint point: spawnPointCollection.spawnPoints) {
            spawnPoints.AddItem(point.name, point, 0);
        }

        spawnMap.ClearUserMarks();
        spawnMap.SetScale(0.1);
    }

}
