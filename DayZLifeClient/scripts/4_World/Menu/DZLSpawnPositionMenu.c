class DZLSpawnPositionMenu : DZLBaseMenu {
    private MapWidget spawnMap;
    private TextListboxWidget spawnPoints;
    private ButtonWidget randomSpawn;
    private ButtonWidget spawn;
    private string jobId;
    private XComboBoxWidget jobSelection;
    private ref array<string> activeJobIds;

    private int medicIndex = -1;
    private int copIndex = -1;
    private int transportIndex = -1;
    private int armyIndex = -1;


    void DZLSpawnPositionMenu() {
        hasCloseButton = false;
        Construct();
    }

    void ~DZLSpawnPositionMenu() {
        Destruct();
    }

    override void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if(rpc_type == DAY_Z_LIFE_NEW_SPAWN_RESPONSE) {
            GetGame().GetMission().GetHud().ShowHud(true);
            GetGame().GetMission().GetHud().ShowQuickBar(true);
            OnHide();
        }
    }

    override Widget Init() {
        layoutPath = "DayZLifeClient/layout/SpawnMenu/SpawnMenu.layout";
        activeJobIds = new array<string>;

        super.Init();
        spawnMap = creator.GetMapWidget("map");
        spawnPoints = creator.GetTextListboxWidget("spawnPoints");
        randomSpawn = creator.GetButtonWidget("randomButton");
        spawn = creator.GetButtonWidget("spawnButton");
        jobSelection = creator.GetXComboBoxWidget("spawn");

        spawn.Show(false);
        return layoutRoot;
    }

    override void OnShow() {
        super.OnShow();
        GetGame().GetMission().GetHud().ShowHud(false);
        GetGame().GetMission().GetHud().ShowQuickBar(false);

        jobId = config.jobIds.Get(0);

        foreach(string configJobId: config.jobIds) {
            activeJobIds.Insert(configJobId);
        }

        jobSelection.ClearAll();
        jobSelection.AddItem("#Civ");

        if(player.GetDZLPlayer().IsMedic()) {
            medicIndex = jobSelection.AddItem("#Medic");
        }

        if(player.GetDZLPlayer().IsCop()) {
            copIndex = jobSelection.AddItem("#Cop");
        }

        if(player.GetDZLPlayer().IsTransport()) {
            transportIndex = jobSelection.AddItem("Transport");
        }

        if(player.GetDZLPlayer().IsArmy()) {
            armyIndex = jobSelection.AddItem("#Army");
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

            if(medicIndex == index) {
                index = 1;
            } else if(copIndex == index) {
                index = 2;
            } else if(transportIndex == index) {
                index = 2;
            } else if(armyIndex == index) {
                index = 3;
            }

            jobId = activeJobIds.Get(index);

            UpdateSpawnPoints();
        }

        return false;
    }

    void SendSpawnLocation(DZLSpawnPoint point, PlayerBase player) {
        player.SetIsSpawned();
        GetGame().RPCSingleParam(player, DAY_Z_LIFE_NEW_SPAWN, new Param2<string, string>(point.GetId(), jobId), true);
    }

    override void OnHide() {
        super.OnHide();
        GetGame().GetMission().GetHud().ShowHud(true);
        GetGame().GetMission().GetHud().ShowQuickBar(true);
    }

    private void UpdateSpawnPoints() {
        DZLJobSpawnPoints spawnPointCollection = config.GetJobSpanwPointById(jobId);

        spawnPoints.ClearItems();
        foreach(DZLSpawnPoint point: spawnPointCollection.spawnPoints) {
            spawnPoints.AddItem(point.name, point, 0);
        }

        spawnMap.ClearUserMarks();
        spawnMap.SetScale(0.1);
    }

}
