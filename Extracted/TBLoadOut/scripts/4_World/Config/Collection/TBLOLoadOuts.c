class TBLOLoadOuts
{
	string version = "1";
    ref array<ref TBLOLoadOutCategory> loadOutCategories;
    ref array<ref TBLOLoadOutPosition> loadOutPosition;
    int coolDownUsageInSeconds = 100;

    void TBLOLoadOuts() {
        if (!Load()) {
            loadOutPosition = new array<ref TBLOLoadOutPosition>;
            loadOutCategories = new array<ref TBLOLoadOutCategory>;

            array<ref TBLOLoadOutType> loadOutSubAttachments = new array<ref TBLOLoadOutType>;
            array<ref TBLOLoadOutType> loadOutTypes = new array<ref TBLOLoadOutType>;
			array<ref TBLOLoadOutType> loadOutAttachments;
            
            loadOutPosition.Insert(new TBLOLoadOutPosition("6572.2001953125 6.0 2466.699951171875", "0 0 0"));
            loadOutTypes.Insert(new TBLOLoadOutType("PoliceCap"));
            loadOutAttachments = new array<ref TBLOLoadOutType>;
            loadOutAttachments.Insert(new TBLOLoadOutType("Deagle"));
            loadOutAttachments.Insert(new TBLOLoadOutType("Mag_Deagle_9rnd"));
            loadOutAttachments.Insert(new TBLOLoadOutType("Mag_Deagle_9rnd"));
            loadOutAttachments.Insert(new TBLOLoadOutType("Mag_Deagle_9rnd"));
            loadOutAttachments.Insert(new TBLOLoadOutType("Mag_Deagle_9rnd"));
            loadOutTypes.Insert(new TBLOLoadOutType("PoliceJacketOrel", loadOutAttachments));
            loadOutAttachments = new array<ref TBLOLoadOutType>;
            loadOutAttachments.Insert(new TBLOLoadOutType("SodaCan_Cola"));
            loadOutAttachments.Insert(new TBLOLoadOutType("SodaCan_Cola"));
            loadOutAttachments.Insert(new TBLOLoadOutType("SpaghettiCan"));
            loadOutAttachments.Insert(new TBLOLoadOutType("Apple"));
            loadOutTypes.Insert(new TBLOLoadOutType("PolicePantsOrel", loadOutAttachments));
            loadOutTypes.Insert(new TBLOLoadOutType("PoliceVest"));
            loadOutTypes.Insert(new TBLOLoadOutType("JungleBoots_Black"));
            loadOutCategories.Insert(new TBLOLoadOutCategory("cat1", loadOutTypes));

            loadOutTypes = new array<ref TBLOLoadOutType>;
            loadOutAttachments = new array<ref TBLOLoadOutType>;
            loadOutAttachments.Insert(new TBLOLoadOutType("GorkaHelmetVisor"));
            loadOutTypes.Insert(new TBLOLoadOutType("GorkaHelmet", loadOutAttachments));
            loadOutTypes.Insert(new TBLOLoadOutType("BalaclavaMask_Green"));
            loadOutAttachments = new array<ref TBLOLoadOutType>;
            loadOutAttachments.Insert(new TBLOLoadOutType("Deagle"));
            loadOutAttachments.Insert(new TBLOLoadOutType("Mag_Deagle_9rnd"));
            loadOutAttachments.Insert(new TBLOLoadOutType("Mag_Deagle_9rnd"));
            loadOutAttachments.Insert(new TBLOLoadOutType("Mag_Deagle_9rnd"));
            loadOutAttachments.Insert(new TBLOLoadOutType("Mag_Deagle_9rnd"));
            loadOutTypes.Insert(new TBLOLoadOutType("M65Jacket_Tan", loadOutAttachments));
            loadOutAttachments = new array<ref TBLOLoadOutType>;
            loadOutAttachments.Insert(TBLOLoadOutType("CombatKnife"));
            loadOutAttachments.Insert(TBLOLoadOutType("SodaCan_Cola"));
            loadOutAttachments.Insert(TBLOLoadOutType("SodaCan_Cola"));
            loadOutAttachments.Insert(TBLOLoadOutType("SpaghettiCan"));
            loadOutAttachments.Insert(TBLOLoadOutType("Apple"));
            loadOutAttachments.Insert(TBLOLoadOutType("Battery9V"));
            loadOutTypes.Insert(new TBLOLoadOutType("CargoPants_Green", loadOutAttachments));
            loadOutTypes.Insert(new TBLOLoadOutType("CombatBoots_Black"));
            loadOutAttachments = new array<ref TBLOLoadOutType>;
            loadOutAttachments.Insert(new TBLOLoadOutType("PlateCarrierPouches"));
            loadOutAttachments.Insert(new TBLOLoadOutType("PlateCarrierHolster"));
            loadOutTypes.Insert(new TBLOLoadOutType("PlateCarrierVest", loadOutAttachments));
            loadOutAttachments = new array<ref TBLOLoadOutType>;
            loadOutAttachments.Insert(new TBLOLoadOutType("AK74_Hndgrd"));
            loadOutAttachments.Insert(new TBLOLoadOutType("AK74_WoodBttstck"));

            loadOutSubAttachments = new array<ref TBLOLoadOutType>;
            loadOutSubAttachments.Insert(new TBLOLoadOutType("Battery9V"));

            loadOutAttachments.Insert(new TBLOLoadOutType("PSO11Optic", loadOutSubAttachments));
            loadOutAttachments.Insert(new TBLOLoadOutType("Mag_AKM_Drum75Rnd"));
            loadOutAttachments.Insert(new TBLOLoadOutType("AK_Suppressor"));
            loadOutTypes.Insert(new TBLOLoadOutType("AKM", loadOutAttachments, 0));
            loadOutCategories.Insert(new TBLOLoadOutCategory("cat2", loadOutTypes));

            Save();
        }

        if (version == "1") {
            foreach(TBLOLoadOutCategory cat: loadOutCategories) {
                foreach(TBLOLoadOutPosition pos: loadOutPosition) {
                    pos.AddCategory(cat.name);
                }
            }

            version = "2";

            Save();
        }

        if (version == "2") {
            version = "3";
            coolDownUsageInSeconds = 100;

            foreach(TBLOLoadOutCategory catToUpdate: loadOutCategories) {
                catToUpdate.UpdateV3();
            }
            Save();
        }
    }

    private bool Load(){
        if (GetGame().IsServer() && FileExist(TB_SERVER_FOLDER_CONFIG + "LoadOut.json")) {
            JsonFileLoader<TBLOLoadOuts>.JsonLoadFile(TB_SERVER_FOLDER_CONFIG + "LoadOut.json", this);
            return true;
        }
        return false;
    }

    private void Save(){
        if (GetGame().IsServer()) {
            CheckTBLOConfigPath();
            JsonFileLoader<TBLOLoadOuts>.JsonSaveFile(TB_SERVER_FOLDER_CONFIG + "LoadOut.json", this);
        }
    }
}
