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
            } else if (player && player.config && player.config.houseConfig) {
                definition = player.config.houseConfig.GetCopHouseDefinition(building);
                if (!definition) {
                    medicDefinition = player.config.houseConfig.GetMedicHouseDefinition(building);
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
