class DZLSpawnPositionMenu : DZLBaseMenu
{
	private MapWidget spawnMap;
	private TextListboxWidget spawnPoints;
	private ButtonWidget randomSpawn;
	private ButtonWidget spawn;
	private string jobId;
	
	void DZLSpawnPositionMenu(string jobId) {
		this.jobId = jobId;
	}

    override Widget Init() {
        layoutPath = "DayZLife/layout/SpawnMenu/SpawnMenu.layout";
        showCourser = false;
        hasCloseButton = false;

        super.Init();

		spawnMap = creator.GetMapWidget("map");
		spawnPoints = creator.GetTextListboxWidget("spawnPoints");
        randomSpawn = creator.GetButtonWidget("randomButton");
        spawn = creator.GetButtonWidget("spawnButton");
		
		spawn.Show(false);
		
		return layoutRoot;
    }
	
	override void OnShow() {
	    super.OnShow();
		
		DZLJobSpawnPoints spawnPointCollection = config.jobConfig.GetJobSpanwPointById(jobId);
		
		foreach(DZLSpawnPoint point: spawnPointCollection.spawnPoints) {
			spawnPoints.AddItem(point.name, point, 0);
		}

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
        }

        return false;
    }

    void SendSpawnLocation(DZLSpawnPoint point, PlayerBase player) {
        GetGame().RPCSingleParam(player, DAY_Z_LIFE_NEW_SPAWN, new Param3<string, PlayerBase, string>(point.id, player, jobId), true);
    }

}
