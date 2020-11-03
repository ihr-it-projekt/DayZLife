class CfgPatches
{
	class DZL_Misc
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data"
		};
	};
};
class CfgVehicles
{
	class Stone;
	class Pot;
	class DZL_Ore_Gold: Stone
	{
		scope=2;
		displayName="Golderz";
		descriptionShort="Golderz";
		model="\DZL_Misc\Gold\DZL_Ore_Gold.p3d";
		weight=4000;
		itemSize[]={2,2};
	};
	class DZL_Ore_Copper: Stone
	{
		scope=2;
		displayName="Copper";
		descriptionShort="Copper";
		model="\DZL_Misc\Copper\DZL_Ore_Copper.p3d";
		weight=4000;
		itemSize[]={2,2};
	};
	class DZL_Ore_Coal: Stone
	{
		scope=2;
		displayName="Coal";
		descriptionShort="Coal";
		model="\DZL_Misc\Coal\DZL_Ore_Coal.p3d";
		weight=4000;
		itemSize[]={2,2};
	};
	class DZL_Ore_Iron: Stone
	{
		scope=2;
		displayName="Iron";
		descriptionShort="Iron";
		model="\DZL_Misc\Iron\DZL_Ore_Iron.p3d";
		weight=4000;
		itemSize[]={2,2};
	};
	class DZL_Bucket: Pot
	{
		scope=1;
		displayName="Bucket";
		descriptionShort="Bucket";
		model="\DZ\structures\furniture\decoration\bucket\bucket.p3d";
		weight=1000;
		itemSize[]={2,3};
		itemsCargoSize[]={0,0};
		canBeDigged=0;
	};
	//Item Platzhalter
	class DZL_WoodenLog: Stone
	{
		scope=2;
		displayName="WoodenLog";
		descriptionShort="Platzhalter";
		weight=4000;
		itemSize[]={2,2};
	};
	class DZL_Scrap_1: Stone
	{
		scope=2;
		displayName="Scrap";
		descriptionShort="Platzhalter";
		weight=4000;
		itemSize[]={2,2};
	};
	class DZL_Scrap_2: Stone
	{
		scope=2;
		displayName="Scrap";
		descriptionShort="Platzhalter";
		weight=4000;
		itemSize[]={2,2};
	};
	class DZL_Scrap_3: Stone
	{
		scope=2;
		displayName="Scrap";
		descriptionShort="Platzhalter";
		weight=4000;
		itemSize[]={2,2};
	};
	class DZL_Scrap_4: Stone
	{
		scope=2;
		displayName="Scrap";
		descriptionShort="Platzhalter";
		weight=4000;
		itemSize[]={2,2};
	};
	class DZL_Scrap_5: Stone
	{
		scope=2;
		displayName="Scrap";
		descriptionShort="Platzhalter";
		weight=4000;
		itemSize[]={2,2};
	};
	class DZL_Scrap_6: Stone
	{
		scope=2;
		displayName="Scrap";
		descriptionShort="Platzhalter";
		weight=4000;
		itemSize[]={2,2};
	};
	class DZL_Scrap_7: Stone
	{
		scope=2;
		displayName="Scrap";
		descriptionShort="Platzhalter";
		weight=4000;
		itemSize[]={2,2};
	};
	class DZL_Scrap_8: Stone
	{
		scope=2;
		displayName="Scrap";
		descriptionShort="Platzhalter";
		weight=4000;
		itemSize[]={2,2};
	};
	class DZL_Scrap_9: Stone
	{
		scope=2;
		displayName="Scrap";
		descriptionShort="Platzhalter";
		weight=4000;
		itemSize[]={2,2};
	};
	class DZL_Scrap_10: Stone
	{
		scope=2;
		displayName="Scrap";
		descriptionShort="Platzhalter";
		weight=4000;
		itemSize[]={2,2};
	};
};
