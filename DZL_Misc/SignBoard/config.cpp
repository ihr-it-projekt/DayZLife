class CfgPatches
{
	class SignBoard
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
	class HouseNoDestruct;
	class SignBoard_Stone: HouseNoDestruct
	{
		scope=1;
		model="\DZL_Misc\SignBoard\SignBoard_Stone.p3d";
	};
	class SignBoard_Coal: HouseNoDestruct
	{
		scope=1;
		model="\DZL_Misc\SignBoard\SignBoard_Coal.p3d";
	};
	class SignBoard_Copper: HouseNoDestruct
	{
		scope=1;
		model="\DZL_Misc\SignBoard\SignBoard_Copper.p3d";
	};
	class SignBoard_Iron: HouseNoDestruct
	{
		scope=1;
		model="\DZL_Misc\SignBoard\SignBoard_Iron.p3d";
	};
	class SignBoard_Gold: HouseNoDestruct
	{
		scope=1;
		model="\DZL_Misc\SignBoard\SignBoard_Gold.p3d";
	};
	class SignBoard_Diamond: HouseNoDestruct
	{
		scope=1;
		model="\DZL_Misc\SignBoard\SignBoard_Diamond.p3d";
	};
};
