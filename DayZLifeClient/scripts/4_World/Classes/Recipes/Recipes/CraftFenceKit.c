modded class CraftFenceKit {

    override bool CanDo(ItemBase ingredients[], PlayerBase player) {
        if(player.GetDZLConfig() && player.GetDZLConfig().baseBuildingConfig) {
            DZLBaseBuildingConfig config = player.GetDZLConfig().baseBuildingConfig;

            if(config.canCraftFenceKit) {
                return super.CanDo(ingredients, player);
            }
        }

        return false;
    }
}