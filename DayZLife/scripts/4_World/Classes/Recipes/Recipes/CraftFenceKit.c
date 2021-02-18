modded class CraftFenceKit
{

    override bool CanDo(ItemBase ingredients[], PlayerBase player) {
        DZLBaseBuildingConfig config;
        if(GetGame().IsServer()) {
            config = DZLConfig.Get().baseBuildingConfig;
        } else {
            if (player.config && player.config.baseBuildingConfig) {
                config = player.config.baseBuildingConfig;
            } else {
                return false;
            }
        }

        if (config && config.canCraftFenceKit) {
            return super.CanDo(ingredients, player);
        }

        return false;
    }
}