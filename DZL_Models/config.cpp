class CfgPatches
{
	class DZL_Models
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
	//ATM
	class DZL_ATM_Blue: HouseNoDestruct
	{
		scope=2;
		model="\DZL_Models\ATM\ATM_Blue.p3d";
	};
	class DZL_ATM_Red: HouseNoDestruct
	{
		scope=2;
		model="\DZL_Models\ATM\ATM_Red.p3d";
	};
	class DZL_ATM_Yellow: HouseNoDestruct
	{
		scope=2;
		model="\DZL_Models\ATM\ATM_Yellow.p3d";
	};
};