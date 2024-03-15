modded class CraftWatchtowerKit {
    override bool CanDo(ItemBase ingredients[], PlayerBase player) {
        if(player.GetDZLConfig() && player.GetDZLConfig().baseBuildingConfig) {
            DZLBaseBuildingConfig config = player.GetDZLConfig().baseBuildingConfig;

            if(config.canCraftWatchtowerKit) {
                return super.CanDo(ingredients, player);
            }
        }

        return false;
    }
}