modded class CraftWatchtowerKit {
    override bool CanDo(ItemBase ingredients[], PlayerBase player) {
        DZLBaseBuildingConfig config = DZLConfig.Get().baseBuildingConfig;
        if(!config) return false;
        if(config.canCraftWatchtowerKit) return super.CanDo(ingredients, player);

        return false;
    }
}