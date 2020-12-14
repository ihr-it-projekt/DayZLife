modded class PluginRecipesManagerBase
{
	override void RegisterRecipies()
	{
		super.RegisterRecipies();
		UnregisterRecipe("SplitStones");
		UnregisterRecipe("CraftFenceKit");
		UnregisterRecipe("CraftWatchtowerKit");
		UnregisterRecipe("CraftWoodenPlank");
		UnregisterRecipe("SawWoodenLog");
		UnregisterRecipe("CraftWoodenCrate");
		UnregisterRecipe("DeCraftWoodenCrate");
		UnregisterRecipe("CraftTerritoryFlagKit");
		UnregisterRecipe("CraftShelterKit");
	}
};