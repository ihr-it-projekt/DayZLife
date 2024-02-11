modded class ActionCloseDoors {
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        bool canClose = super.ActionCondition(player, target, item);

        Building building = Building.Cast(target.GetObject());

        if(building && canClose) {
			int doorIndex = building.GetDoorIndex(target.GetComponentIndex());			
            canClose = DZLCanDoDoorAction.canDoByJob(building, player, doorIndex);
        }

        return canClose;
    }

}
