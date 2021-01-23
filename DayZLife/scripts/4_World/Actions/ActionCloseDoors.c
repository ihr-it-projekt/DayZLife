modded class ActionCloseDoors
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item){
        bool canClose = super.ActionCondition(player, target, item);

        Building building = Building.Cast(target.GetObject());

        if (building && canClose) {
            DZLCopHouseDefinition definition;
            DZLPlayer dzlPlayer =  player.GetDZLPlayer();
            if (GetGame().IsServer()) {
               definition = DZLConfig.Get().houseConfig.GetCopHouseDefinition(building);
            } else if (player && player.config && player.config.houseConfig) {
               definition = player.config.houseConfig.GetCopHouseDefinition(building);
            } else {
                return false;
            }

            if(definition) {
                canClose = dzlPlayer.IsActiveAsCop();
            }
        }

        return canClose;
    }
}
