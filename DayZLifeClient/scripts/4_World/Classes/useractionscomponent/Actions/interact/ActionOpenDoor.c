modded class ActionOpenDoors {

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        if(!super.ActionCondition(player, target, item)) return false;

#ifdef DeerIsleScripts
        if(Jmc_Security_Door.Cast(target.GetObject()) || Jmc_Security_Door_Carrier.Cast(target.GetObject())) return false;
#endif

#ifdef Banov_Misc
        if(land_bunker_door_base.Cast(target.GetObject())) return false;
#endif

        BuildingBase building = BuildingBase.Cast(target.GetObject());
        int doorIndex = building.GetDoorIndex(target.GetComponentIndex());

        if(!DZLCanDoDoorAction.IsJobDoor(building)) return true;

        return DZLCanDoDoorAction.canDoByJob(building, player);
    }

}
