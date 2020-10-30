class DZLDisplayHelper
{
    static string GetItemDisplayName(string itemClassname){
        string displayName;
        string cfg = CFG_VEHICLESPATH + " " + itemClassname + " displayName";
        GetGame().ConfigGetText(cfg, displayName);

        if (displayName == "") {
            displayName = itemClassname;
        }

        return displayName;
    }

}