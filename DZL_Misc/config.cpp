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
	class Pot;
	class HouseNoDestruct;
	class M65Jacket_Black;
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
	class DZL_sign_relic_tree: HouseNoDestruct
	{
		scope=1;
		model="\DZ\structures\signs\misc\sign_relic_tree.p3d";
	};
	class DZL_sign_parking: HouseNoDestruct
	{
		scope=1;
		model="\DZ\structures\signs\traffic\sign_parking.p3d";
	};
	class DZL_M65Jacket_Black: M65Jacket_Black
	{
		itemsCargoSize[]={10,10};
	};
};
	