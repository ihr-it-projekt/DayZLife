modded class CraftFenceKit {

    override bool CanDo(ItemBase ingredients[], PlayerBase player) {
        if (player.GetConfig() && player.GetConfig().baseBuildingConfig) {
            DZLBaseBuildingConfig config = player.GetConfig().baseBuildingConfig;

            if (config.canCraftFenceKit) {
                return super.CanDo(ingredients, player);
            }
        }

        return false;
    }
}