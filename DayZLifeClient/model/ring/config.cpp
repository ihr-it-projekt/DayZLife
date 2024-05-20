class CfgPatches
{
    class DZL_Jewelry
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
	class Inventory_Base;
	class DZL_Jewelry: Inventory_Base
	{
		scope=2;
		displayName="#Fancy_Ring";
		descriptionShort="An expensive fancy ring";
		model="DayZLifeClient\model\ring\DZL_Jewelry.p3d";
		rotationFlags=17;
		weight=21;
		soundImpactType="metal";
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
					healthLevels[]=
					{
						{
							1.0,
							{}
						},
						{
							0.69999999,
							{}
						},
						{
							0.5,
							{}
						},
						{
							0.30000001,
							{}
						},
						{
							0.0,
							{}
						}
					};
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class drop
				{
					soundset="wrench_drop_SoundSet";
					id=898;
				};
			};
		};
	};
};