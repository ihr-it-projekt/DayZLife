class DZLSpawnPositionMenu : DZLBaseMenu
{
	private MapWidget spawnMap;
	private TextListboxWidget spawnPoints;
	private ButtonWidget randomSpawn;
	private ButtonWidget spawn;
	private string jobId;
	private XComboBoxWidget jobSelection;
	private ref array<string> activeJobIds;
	
	void DZLSpawnPositionMenu() {
		hasCloseButton = false;
		Construct();
	}

	void ~DZLSpawnPositionMenu() {
	    Destruct();
	}

	override void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_NEW_SPAWN_RESPONSE) {
            GetGame().GetMission().GetHud().ShowHud(true);
            GetGame().GetMission().GetHud().ShowQuickBar(true);
            OnHide();
        }
	}

    override Widget Init() {
        layoutPath = "DayZLife/layout/SpawnMenu/SpawnMenu.layout";
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
		jobSelection.AddItem("#Medic");
		jobSelection.AddItem("#Cop");
		
		UpdateSpawnPoints();
	}

    override bool OnClick(Widget w, int x, int y, int button) {
		if (super.OnClick(w, x, y, button)) return true;
		
		int index;
		DZLSpawnPoint point;

        if (w == randomSpawn) {
			index = Math.RandomIntInclusive(0, spawnPoints.GetNumItems() - 1);
			
			spawnPoints.GetItemData(index, 0, point);
			
			SendSpawnLocation(point, player);

			return true;
        } else if (w == spawn) {
            index = spawnPoints.GetSelectedRow();

            if (index == -1)return true;

            spawnPoints.GetItemData(index, 0, point);

            SendSpawnLocation(point, player);

            return true;
        } else if (w == spawnPoints) {
			index = spawnPoints.GetSelectedRow();
			
			if (index == -1)return true;				
						
			spawnPoints.GetItemData(index, 0, point);
			
			DZLDisplayHelper.UpdateMap(spawnMap, point.point);
			
			spawn.Show(true);

			return true;
        } else if(w == jobSelection) {
			index = jobSelection.GetCurrentItem();
			
			if (index == -1) return true;
			
			jobId = activeJobIds.Get(index);
			
			UpdateSpawnPoints();
		}

        return false;
    }

    void SendSpawnLocation(DZLSpawnPoint point, PlayerBase player) {
        GetGame().RPCSingleParam(player, DAY_Z_LIFE_NEW_SPAWN, new Param3<string, PlayerBase, string>(point.id, player, jobId), true);
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
