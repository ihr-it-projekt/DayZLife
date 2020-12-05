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

    static void UpdateMap(MapWidget mapWidget, vector pos) {
        mapWidget.ClearUserMarks();
        mapWidget.SetScale(0.1);
        mapWidget.SetMapPos(pos);
        mapWidget.AddUserMark(pos, "", ARGB(255,0,255,0), "set:dayz_gui image:cartridge_pistol");
    }


}
