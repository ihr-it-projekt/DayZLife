modded class CraftShelterKit {
    override bool CanDo(ItemBase ingredients[], PlayerBase player) {
        if (player.GetConfig() && player.GetConfig().baseBuildingConfig) {
            DZLBaseBuildingConfig config = player.GetConfig().baseBuildingConfig;

            if (config.canCraftShelterKit) {
                return super.CanDo(ingredients, player);
            }
        }

        return false;
    }
}