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
	class DZL_ATM_Blue: HouseNoDestruct
	{
		scope=1;
		model="\DZL_Models\ATM\ATM_Blue.p3d";
	};
	class DZL_ATM_Red: HouseNoDestruct
	{
		scope=1;
		model="\DZL_Models\ATM\ATM_Red.p3d";
	};
	class DZL_ATM_Yellow: HouseNoDestruct
	{
		scope=1;
		model="\DZL_Models\ATM\ATM_Yellow.p3d";
	};
	class DZL_Parking_Meter: HouseNoDestruct
	{
		scope=1;
		model="\DZL_Models\ParkingMeter2\ParkingMeter.p3d";
	};
	class DZL_Trader: HouseNoDestruct
	{
		scope=1;
		model="\DZ\structures\furniture\generalstore\pultskasou.p3d";
	};
};