modded class CraftTerritoryFlagKit
{
    override bool CanDo(ItemBase ingredients[], PlayerBase player) {
        if (player.GetConfig() && player.GetConfig().baseBuildingConfig) {
        	DZLBaseBuildingConfig config = player.GetConfig().baseBuildingConfig;
       
        	if (config.canCraftTerritoryFlagKit) {
            	return super.CanDo(ingredients, player);
			}
        }

        return false;
    }
}