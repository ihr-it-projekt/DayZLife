modded class CraftTerritoryFlagKit {
    override bool CanDo(ItemBase ingredients[], PlayerBase player) {
        if(player.GetDZLConfig() && player.GetDZLConfig().baseBuildingConfig) {
            DZLBaseBuildingConfig config = player.GetDZLConfig().baseBuildingConfig;

            if(config.canCraftTerritoryFlagKit) {
                return super.CanDo(ingredients, player);
            }
        }

        return false;
    }
}