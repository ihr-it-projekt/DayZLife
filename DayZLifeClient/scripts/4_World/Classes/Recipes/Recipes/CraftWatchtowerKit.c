modded class CraftWatchtowerKit {
    override bool CanDo(ItemBase ingredients[], PlayerBase player) {
        if (player.GetConfig() && player.GetConfig().baseBuildingConfig) {
            DZLBaseBuildingConfig config = player.GetConfig().baseBuildingConfig;

            if (config.canCraftWatchtowerKit) {
                return super.CanDo(ingredients, player);
            }
        }

        return false;
    }
}