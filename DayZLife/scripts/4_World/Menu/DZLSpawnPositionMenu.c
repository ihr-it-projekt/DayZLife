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
	}

    override Widget Init() {
        layoutPath = "DayZLife/layout/SpawnMenu/SpawnMenu.layout";
        activeJobIds = new array<string>;

		DebugMessageDZL("6");
        super.Init();
        DebugMessageDZL("7");
		spawnMap = creator.GetMapWidget("map");
		spawnPoints = creator.GetTextListboxWidget("spawnPoints");
        randomSpawn = creator.GetButtonWidget("randomButton");
        spawn = creator.GetButtonWidget("spawnButton");
		jobSelection = creator.GetXComboBoxWidget("spawn");
		
		
		spawn.Show(false);
		DebugMessageDZL("5");
		return layoutRoot;
    }
	
	override void OnShow() {
		DebugMessageDZL("1");
	    super.OnShow();
	    DebugMessageDZL("3");
		jobId = config.jobIds.Get(0);
		
		foreach(string configJobId: config.jobIds) {
			activeJobIds.Insert(configJobId);
		}
		
		UpdateSpawnPoints();
		DebugMessageDZL("4");
	}

    override bool OnClick(Widget w, int x, int y, int button) {
		int index;
		DZLSpawnPoint point;
		
        if (super.OnClick(w, x, y, button)) return true;

        if (w == randomSpawn) {
			index = Math.RandomIntInclusive(0, spawnPoints.GetNumItems() - 1);
			
			spawnPoints.GetItemData(index, 0, point);
			
			SendSpawnLocation(point, player);

			return true;
        } else if (w == spawn) {
            index = spawnPoints.GetSelectedRow();

            if (index != -1)return true;

            spawnPoints.GetItemData(index, 0, point);

            SendSpawnLocation(point, player);

            return true;
        } else if (w == spawnPoints) {
			index = spawnPoints.GetSelectedRow();
			
			if (index != -1)return true;				
						
			spawnPoints.GetItemData(index, 0, point);
			
			DZLDisplayHelper.UpdateMap(spawnMap, point.point);

			return true;
        } else if(jobSelection == w) {
			index = jobSelection.GetCurrentItem();
			
			if (index != -1)return true;		
			
			jobId = activeJobIds.Get(index);
			
			UpdateSpawnPoints();
		}

        return false;
    }

    void SendSpawnLocation(DZLSpawnPoint point, PlayerBase player) {
        GetGame().RPCSingleParam(player, DAY_Z_LIFE_NEW_SPAWN, new Param3<string, PlayerBase, string>(point.id, player, jobId), true);
    }
	
	private void UpdateSpawnPoints() {
	    DebugMessageDZL("9");
		DZLJobSpawnPoints spawnPointCollection = config.GetJobSpanwPointById(jobId);
		
		spawnPoints.ClearItems();
		foreach(DZLSpawnPoint point: spawnPointCollection.spawnPoints) {
			spawnPoints.AddItem(point.name, point, 0);
		}
	    DebugMessageDZL("8");
	}
	
}
