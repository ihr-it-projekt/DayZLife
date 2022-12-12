class TBLODisplayHelper
{
    static EntityAI previewItem;

    static string GetItemDisplayName(string itemClassname){
        TStringArray configs = new TStringArray;
        configs.Insert(CFG_VEHICLESPATH);
        configs.Insert(CFG_WEAPONSPATH);
        configs.Insert(CFG_MAGAZINESPATH);
        configs.Insert("CfgNonAIVehicles");
        configs.Insert("CfgAmmo");

        string displayName;
        foreach (string itemName: configs){
            string cfg = itemName + " " + itemClassname + " displayName";
            GetGame().ConfigGetText(cfg, displayName);

            if (displayName != ""){
                displayName.Replace("$UNT$", "");

                break;
            }
        }

        if (displayName == "") {
            displayName = itemClassname;
        }

        return displayName;
    }
}
