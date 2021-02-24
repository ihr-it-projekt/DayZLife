modded class ActionCloseDoors
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item){
        bool canClose = super.ActionCondition(player, target, item);

        Building building = Building.Cast(target.GetObject());

        if (building && canClose) {
            DZLJobHouseDefinition definition;
            DZLJobHouseDefinition medicDefinition;
            DZLPlayer dzlPlayer =  player.GetDZLPlayer();
            if (GetGame().IsServer()) {
                definition = DZLConfig.Get().houseConfig.GetCopHouseDefinition(building);
                if (!definition) {
                    medicDefinition = DZLConfig.Get().houseConfig.GetMedicHouseDefinition(building);
                }
            } else if (player && player.GetConfig() && player.GetConfig().houseConfig) {
                definition = player.GetConfig().houseConfig.GetCopHouseDefinition(building);
                if (!definition) {
                    medicDefinition = player.GetConfig().houseConfig.GetMedicHouseDefinition(building);
                }
            } else {
                return false;
            }

            if(definition) {
                canClose = dzlPlayer.IsActiveAsCop();
            } else if (medicDefinition) {
                canClose = dzlPlayer.IsActiveAsMedic();
            }
        }

        return canClose;
    }
}
