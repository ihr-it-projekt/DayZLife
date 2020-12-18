modded class ActionCloseDoors
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item){
        bool canClose = super.ActionCondition(player, target, item);

        Building building = Building.Cast(target.GetObject());

        if (building && canClose) {
            DZLCopHouseDefinition definition;
            DZLPlayer dzlPlayer;
            if (GetGame().IsServer()) {
               definition = DZLConfig.Get().houseConfig.GetCopHouseDefinition(building);
               dzlPlayer = DZLDatabaseLayer.Get().GetPlayer(player.GetIdentity().GetId());
            } else {
               definition = player.config.houseConfig.GetCopHouseDefinition(building);
               dzlPlayer = player.dzlPlayer;
            }

            if(definition) {
                canClose = dzlPlayer.IsActiveAsCop();
            }
        }

        return canClose;
    }
}
