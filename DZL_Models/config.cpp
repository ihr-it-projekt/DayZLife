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
	class DZLBaseActionObject;
	class DZL_ATM_Blue: DZLBaseActionObject
	{
		scope=1;
		model="\DZL_Models\ATM\ATM_Blue.p3d";
	};
	class DZL_ATM_Red: DZLBaseActionObject
	{
		scope=1;
		model="\DZL_Models\ATM\ATM_Red.p3d";
	};
	class DZL_ATM_Yellow: DZLBaseActionObject
	{
		scope=1;
		model="\DZL_Models\ATM\ATM_Yellow.p3d";
	};
	class DZL_Parking_Meter: DZLBaseActionObject
	{
		scope=1;
		model="\DZL_Models\ParkingMeter2\ParkingMeter.p3d";
	};
	class DZL_Trader: DZLBaseActionObject
	{
		scope=1;
		model="\DZ\structures\furniture\generalstore\pultskasou.p3d";
	};
};