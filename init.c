void SpawnObject(string objectName, vector position, vector orientation) {
    Object obj;
    obj = Object.Cast(GetGame().CreateObject(objectName, "0 0 0"));
    obj.SetPosition(position);
    obj.SetOrientation(orientation);
    //Force collision update
    vector roll = obj.GetOrientation();
    roll [ 2 ] = roll [ 2 ] - 1;
    obj.SetOrientation( roll );
    roll [ 2 ] = roll [ 2 ] + 1;
    obj.SetOrientation( roll );

    // Force update collisions
    if (obj.CanAffectPathgraph()) {
        obj.SetAffectPathgraph(true, false);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(GetGame().UpdatePathgraphRegionByObject, 100, false, obj);
    }
}

void main() {
    SpawnObject( "SignBoard_Stone", "4620.000000 339.589233 10360.000000", "0.000000 0.000000 0.000000" );
    SpawnObject( "SignBoard_Coal", "4630.000000 339.589233 10359.974609", "0.000000 0.000000 0.000000" );
    SpawnObject( "SignBoard_Copper", "4640.000000 339.589233 10360.000000", "0.000000 0.000000 0.000000" );
    SpawnObject( "SignBoard_Iron", "4650.000000 339.589233 10360.000000", "0.000000 0.000000 0.000000" );
    SpawnObject( "SignBoard_Gold", "4670.000000 339.589233 10360.000000", "0.000000 0.000000 0.000000" );
    SpawnObject( "SignBoard_Diamond", "4680.000000 339.589233 10360.000000", "0.000000 0.000000 0.000000" );
    SpawnObject( "DZL_sign_relic_tree", "4620.000000 339.609009 10340.000000", "0.000000 0.000000 0.000000" ); //Steinverarbeitung
    //SpawnObject( "DZL_sign_relic_tree", "4630.000000 339.609009 10340.000000", "0.000000 0.000000 0.000000" );
    SpawnObject( "DZL_sign_relic_tree", "4640.000000 339.609009 10340.000000", "0.000000 0.000000 0.000000" ); //Kupferschmelze
    SpawnObject( "DZL_sign_relic_tree", "4650.000000 339.609009 10340.000000", "0.000000 0.000000 0.000000" ); //Eisenschmelze
    SpawnObject( "DZL_sign_relic_tree", "4660.000000 339.609009 10340.000000", "0.000000 0.000000 0.000000" ); //Silberschmelze
    SpawnObject( "DZL_sign_relic_tree", "4670.000000 339.609009 10340.000000", "0.000000 0.000000 0.000000" ); //Goldschmelze
    SpawnObject( "DZL_sign_relic_tree", "4680.000000 339.609009 10340.000000", "0.000000 0.000000 0.000000" ); //Diamantenschleiferei
    // SpawnObject( "bldr_Misc_Tree_Pavement1", "4650.000000 338.825012 10320.000000", "0.000000 0.000000 0.000000" ); //Playerspawn
    // SpawnObject( "bldr_Misc_Tree_Pavement2", "4660.000000 339.282990 10325.000000", "0.000000 0.000000 0.000000" ); //Trader
    // SpawnObject( "bldr_Misc_Tree_Pavement2", "4660.000000 339.282990 10315.000000", "0.000000 0.000000 0.000000" ); //Licenzhändler
    // SpawnObject( "bldr_Misc_Tree_Pavement2", "4660.000000 339.282990 10305.000000", "0.000000 0.000000 0.000000" ); //Bänker
    SpawnObject( "Land_House_1W03", "4640.000000 341.737000 10300.000000", "-59.999996 0.000000 0.000000" );
    SpawnObject( "DZL_sign_parking", "4630.000000 339.500000 10320.000000", "-90.000000 0.000000 0.000000" );
    // SpawnObject( "OffroadHatchback_Blue", "4634.000000 338.049988 10319.981445", "90.000000 0.000000 0.000000" ); //Fahrzeugspawn


    //INIT WEATHER BEFORE ECONOMY INIT------------------------
    Weather weather = g_Game.GetWeather();

    weather.MissionWeather(true);    // false = use weather controller from Weather.c

    weather.GetRain().SetLimits( 0.0, 0.0 );
    weather.GetOvercast().SetLimits( 0.0, 0.0 );
    weather.GetFog().SetLimits( 0.0, 0.01 );

    weather.GetOvercast().SetForecastChangeLimits( 0.0, 0.1 );
    weather.GetRain().SetForecastChangeLimits( 0.0, 0.0 );
    weather.GetFog().SetForecastChangeLimits( 0.0, 0.0 );

    weather.GetOvercast().SetForecastTimeLimits( 1800, 1800 );
    weather.GetRain().SetForecastTimeLimits( 600, 600 );
    weather.GetFog().SetForecastTimeLimits( 1800, 1800 );

    weather.GetOvercast().Set( Math.RandomFloatInclusive(0.0, 0.3), 0, 0);
    weather.GetRain().Set( Math.RandomFloatInclusive(0.0, 0.0), 0, 0);
    weather.GetFog().Set( Math.RandomFloatInclusive(0.0, 0.1), 0, 0);

    weather.SetWindMaximumSpeed(15);
    weather.SetWindFunctionParams(0.1, 0.3, 50);

    //INIT ECONOMY--------------------------------------
    Hive ce = CreateHive();
    if ( ce )
        ce.InitOffline();

    //DATE RESET AFTER ECONOMY INIT-------------------------
    int year, month, day, hour, minute;
    int reset_month = 9, reset_day = 20;
    GetGame().GetWorld().GetDate(year, month, day, hour, minute);

    if ((month == reset_month) && (day < reset_day)) {
        GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
    } else {
        if ((month == reset_month + 1) && (day > reset_day)) {
            GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
        } else {
            if ((month < reset_month) || (month > reset_month + 1)) {
                GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
            }
        }
    }
}

class CustomMission: MissionServer {
    void SetRandomHealth(EntityAI itemEnt) {
        if ( itemEnt ) {
            float rndHlt = Math.RandomFloat( 0.25, 0.65 )
                           itemEnt.SetHealth01( "", "", rndHlt );
        }
    }

    override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName) {
        Entity playerEnt;
        playerEnt = GetGame().CreatePlayer( identity, characterName, pos, 0, "NONE" );
        Class.CastTo( m_player, playerEnt );

        GetGame().SelectPlayer( identity, m_player );

        return m_player;
    }

    override void StartingEquipSetup(PlayerBase player, bool clothesChosen) {

        switch(player.GetIdentity().GetPlainId()) {

        case "76561198196317725": //TheBuster
        case "76561198053709060": //*Sense
        case "76561198016406177": //Toxic

            player.RemoveAllItems();

            player.GetInventory().CreateInInventory("DZL_M65Jacket_Black");
            player.GetInventory().CreateInInventory("CargoPants_Black");
            player.GetInventory().CreateInInventory("Sneakers_Black");
            player.GetInventory().CreateInInventory("WorkingGloves_Black");

            EntityAI weapon = player.GetInventory().CreateInInventory("M4A1");
            player.GetInventory().CreateInInventory("Mag_STANAG_30Rnd");

            EntityAI melee1 = player.GetInventory().CreateInInventory("Pickaxe");
            EntityAI melee2 = player.GetInventory().CreateInInventory("Crowbar");
            EntityAI melee3 = player.GetInventory().CreateInInventory("CombatKnife");

            player.GetInventory().CreateInInventory("TacticalBaconCan_Opened");
            player.GetInventory().CreateInInventory("TacticalBaconCan_Opened");
            player.GetInventory().CreateInInventory("Canteen");

            player.SetQuickBarEntityShortcut(weapon, 0, true);
            player.SetQuickBarEntityShortcut(melee1, 1, true);
            player.SetQuickBarEntityShortcut(melee2, 2, true);
            player.SetQuickBarEntityShortcut(melee3, 3, true);

            player.SetPosition("4650.000000 338.825012 10320.000000");

            break;
        }
    }
};

Mission CreateCustomMission(string path) {
    return new CustomMission();
}