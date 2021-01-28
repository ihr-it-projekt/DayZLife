class DZLLoadOuts
{
	string version = "1";
    string jobId;
    ref array<ref DZLLoadOutCategory> loadOutCategories;
    ref array<ref DZLLoadOutPosition> loadOutPosition;

    void DZLLoadOuts(string jobId) {
        this.jobId = jobId;
        if (!Load()) {
            loadOutPosition = new array<ref DZLLoadOutPosition>;
            loadOutCategories = new array<ref DZLLoadOutCategory>;

            array<string> attachments = new array<string>;
            attachments.Insert("ManSuit_Black");
            attachments.Insert("SlacksPants_Black");
            attachments.Insert("ThickFramesGlasses");
            attachments.Insert("DressShoes_Black");

            loadOutPosition.Insert(new DZLLoadOutPosition("4665.000000 339.282990 10305.000000", "0 0 0", "SurvivorM_Boris", attachments));

            array<ref DZLLoadOutType> loadOutSubAttachments = new array<ref DZLLoadOutType>;

            array<ref DZLLoadOutType> loadOutTypes = new array<ref DZLLoadOutType>;
            loadOutTypes.Insert(new DZLLoadOutType("PoliceCap"));
            array<ref DZLLoadOutType> loadOutAttachments = new array<ref DZLLoadOutType>;
            loadOutAttachments.Insert(new DZLLoadOutType("Deagle"));
            loadOutAttachments.Insert(new DZLLoadOutType("Mag_Deagle_9rnd"));
            loadOutAttachments.Insert(new DZLLoadOutType("Mag_Deagle_9rnd"));
            loadOutAttachments.Insert(new DZLLoadOutType("Mag_Deagle_9rnd"));
            loadOutAttachments.Insert(new DZLLoadOutType("Mag_Deagle_9rnd"));
            loadOutTypes.Insert(new DZLLoadOutType("PoliceJacketOrel", loadOutAttachments));
            loadOutAttachments = new array<ref DZLLoadOutType>;
            loadOutAttachments.Insert(new DZLLoadOutType("SodaCan_Cola"));
            loadOutAttachments.Insert(new DZLLoadOutType("SodaCan_Cola"));
            loadOutAttachments.Insert(new DZLLoadOutType("SpaghettiCan"));
            loadOutAttachments.Insert(new DZLLoadOutType("Apple"));
            loadOutTypes.Insert(new DZLLoadOutType("PolicePantsOrel", loadOutAttachments));
            loadOutTypes.Insert(new DZLLoadOutType("PoliceVest"));
            loadOutTypes.Insert(new DZLLoadOutType("JungleBoots_Black"));
            loadOutCategories.Insert(new DZLLoadOutCategory("cat1", loadOutTypes));

            loadOutTypes = new array<ref DZLLoadOutType>;
            loadOutAttachments = new array<ref DZLLoadOutType>;
            loadOutAttachments.Insert(new DZLLoadOutType("GorkaHelmetVisor"));
            loadOutTypes.Insert(new DZLLoadOutType("GorkaHelmet", loadOutAttachments));
            loadOutTypes.Insert(new DZLLoadOutType("BalaclavaMask_Green"));
            loadOutAttachments = new array<ref DZLLoadOutType>;
            loadOutAttachments.Insert(new DZLLoadOutType("Deagle"));
            loadOutAttachments.Insert(new DZLLoadOutType("Mag_Deagle_9rnd"));
            loadOutAttachments.Insert(new DZLLoadOutType("Mag_Deagle_9rnd"));
            loadOutAttachments.Insert(new DZLLoadOutType("Mag_Deagle_9rnd"));
            loadOutAttachments.Insert(new DZLLoadOutType("Mag_Deagle_9rnd"));
            loadOutTypes.Insert(new DZLLoadOutType("M65Jacket_Tan", loadOutAttachments));
            loadOutAttachments = new array<ref DZLLoadOutType>;
            loadOutAttachments.Insert(DZLLoadOutType("CombatKnife"));
            loadOutAttachments.Insert(DZLLoadOutType("SodaCan_Cola"));
            loadOutAttachments.Insert(DZLLoadOutType("SodaCan_Cola"));
            loadOutAttachments.Insert(DZLLoadOutType("SpaghettiCan"));
            loadOutAttachments.Insert(DZLLoadOutType("Apple"));
            loadOutAttachments.Insert(DZLLoadOutType("Battery9V"));
            loadOutTypes.Insert(new DZLLoadOutType("CargoPants_Green", loadOutAttachments));
            loadOutTypes.Insert(new DZLLoadOutType("CombatBoots_Black"));
            loadOutAttachments = new array<ref DZLLoadOutType>;
            loadOutAttachments.Insert(new DZLLoadOutType("PlateCarrierPouches"));
            loadOutAttachments.Insert(new DZLLoadOutType("PlateCarrierHolster"));
            loadOutTypes.Insert(new DZLLoadOutType("PlateCarrierVest", loadOutAttachments));
            loadOutAttachments = new array<ref DZLLoadOutType>;
            loadOutAttachments.Insert(new DZLLoadOutType("AK74_Hndgrd"));
            loadOutAttachments.Insert(new DZLLoadOutType("AK74_WoodBttstck"));

            loadOutSubAttachments = new array<ref DZLLoadOutType>;
            loadOutSubAttachments.Insert(new DZLLoadOutType("Battery9V"));

            loadOutAttachments.Insert(new DZLLoadOutType("PSO11Optic", loadOutSubAttachments));
            loadOutAttachments.Insert(new DZLLoadOutType("Mag_AKM_Drum75Rnd"));
            loadOutAttachments.Insert(new DZLLoadOutType("AK_Suppressor"));
            loadOutTypes.Insert(new DZLLoadOutType("AKM", loadOutAttachments, 0));
            loadOutCategories.Insert(new DZLLoadOutCategory("cat2", loadOutTypes));

            Save();
        }
    }

    bool IsInZone(vector playerPosition) {
        if (!playerPosition) {
            return false;
        }

        foreach(DZLLoadOutPosition zone: loadOutPosition) {
            if(vector.Distance(zone.position, playerPosition) <= 2) {
                return true;
            }
        }
        return false;
    }

    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + jobId + "LoadOut.json")) {
            JsonFileLoader<DZLLoadOuts>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + jobId + "LoadOut.json", this);
            return true;
        }
        return false;
    }

    private void Save(){
        if (GetGame().IsServer()) {
            CheckDZLConfigPath();
            JsonFileLoader<DZLLoadOuts>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + jobId + "LoadOut.json", this);
        }
    }
}
