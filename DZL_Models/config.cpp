class CfgPatches
{
	class DZL_Models
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DayZLife"
		};
	};
};

class CfgVehicles
{
	class HouseNoDestruct;
    class DZLBaseActionObject: HouseNoDestruct
    {
        scope=1;
    };
	class DZLBankActionObjectBlue: DZLBaseActionObject
	{
		model="\DZL_Models\ATM\ATM_Blue.p3d";
	};
	class DZLBankActionObjectRed: DZLBankActionObjectBlue
	{
		model="\DZL_Models\ATM\ATM_Red.p3d";
	};
	class DZLBankActionObjectYellow: DZLBankActionObjectBlue
	{
		model="\DZL_Models\ATM\ATM_Yellow.p3d";
	};
	class DZLParkingMeter: DZLBaseActionObject
	{
		model="\DZL_Models\ParkingMeter2\ParkingMeter.p3d";
	};
	class DZLTraderActionObject: DZLBaseActionObject
	{
		model="\DZ\structures\furniture\generalstore\pultskasou.p3d";
	};
	class DZLLicenseActionObject: DZLBaseActionObject
	{
		model="\DZ\structures\furniture\generalstore\pultskasou.p3d";
	};
    class DZLLoadoutMedicActionObject: DZLBaseActionObject
    {
        model="\DZL_Misc\Terminal\DZL_Terminal.p3d";
    };
    class DZLLoadoutCopActionObject: DZLBaseActionObject
    {
        model="\DZL_Misc\Terminal\DZL_Terminal.p3d";
    };
};