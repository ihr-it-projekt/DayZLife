class DZLPlayerArrestListener
{
	DZLArrestConfig arrestConfig;
	ref Timer timerArrest;
	ref array<ref DZLEscapedPlayer> escapeePlayers = new array<ref DZLEscapedPlayer>;
	int copCount = 0;
	int civCount = 0;
	int medicCount = 0;
	
    void DZLPlayerArrestListener() {
        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
		arrestConfig = DZLConfig.Get().jobConfig.arrestConfig;
		
		timerArrest = new Timer;
		timerArrest.Run(60, this, "CheckPrisoners", null, true);
    }

    void ~DZLPlayerArrestListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (!DZLLicenceCheck.Get().HasActiveLicence(sender)) return;
        if (rpc_type == DAY_Z_LIFE_ARREST_PLAYER) {
            autoptr Param3<PlayerBase, PlayerBase, int> paramArrestPlayer;
            if (ctx.Read(paramArrestPlayer)){
                PlayerBase cop = paramArrestPlayer.param1;
                PlayerBase prisoner = paramArrestPlayer.param2;
                int arrestTime = paramArrestPlayer.param3;
				
				DZLPlayer copDzl = DZLDatabaseLayer.Get().GetPlayer(cop.GetIdentity().GetId());
				DZLPlayer prisonerDzl = DZLDatabaseLayer.Get().GetPlayer(prisoner.GetIdentity().GetId());
				
				if(!copDzl.IsActiveAsCop()) return;
				if(prisonerDzl.IsActiveAsCop()) return;
				
				prisonerDzl.ArrestPlayer(arrestTime);

				ChangeItems(prisoner, arrestConfig.prisonerItems, arrestConfig.shouldDeleteAllItemsOnPrissoner);

				GetGame().RPCSingleParam(prisoner, DAY_Z_LIFE_PLAYER_DATA_RESPONSE, new Param1<ref DZLPlayer>(prisonerDzl), true, prisoner.GetIdentity());
                GetGame().RPCSingleParam(cop, DAY_Z_LIFE_ARREST_PLAYER_RESPONSE, new Param1<bool>(true), true, sender);
				DZLSendMessage(prisoner.GetIdentity(), "#you_got_arrest_in_minutes: " + arrestTime.ToString());
				DZLSendMessage(cop.GetIdentity(), "#you_set_arrest_to_player_in_minutes: " + arrestTime.ToString());
            }
        } else if (rpc_type == DAY_Z_LIFE_GET_ESCAPED_PLAYERS) {
            autoptr Param1<PlayerBase> paramEscapedPlayer;
            if (ctx.Read(paramEscapedPlayer)){
                GetGame().RPCSingleParam(paramEscapedPlayer.param1, DAY_Z_LIFE_GET_ESCAPED_PLAYERS_RESPONSE, new Param4<ref array<ref DZLEscapedPlayer>, int, int, int>(escapeePlayers, copCount, medicCount, civCount), true, sender);
            }
        }
    }
	
	void CheckPrisoners() {
		array<Man> allPlayers = new array<Man>;
        GetGame().GetPlayers(allPlayers);
        escapeePlayers.Clear();
        civCount = 0;
        copCount = 0;
        medicCount = 0;

		foreach(Man player: allPlayers) {
			DZLPlayer dzlPlayer = DZLDatabaseLayer.Get().GetPlayer(player.GetIdentity().GetId());

			if(dzlPlayer.IsActiveAsCop()) {
			    copCount ++;
				continue;
			}

            if(dzlPlayer.IsActiveAsCivil()) {
			    civCount ++;
			}

            if(dzlPlayer.IsActiveAsMedic()) {
			    medicCount ++;
			}

			if (dzlPlayer.IsPlayerInArrest()) {
				vector playerPosition = player.GetPosition();
	
				bool isInPrison = false;
				foreach(vector position: arrestConfig.arrestAreas) {
				    if (vector.Distance(position, playerPosition) < arrestConfig.arrestAreaRadius){
						dzlPlayer.ArrestCountDown();
						GetGame().RPCSingleParam(player, DAY_Z_LIFE_PLAYER_DATA_RESPONSE, new Param1<ref DZLPlayer>(dzlPlayer), true, player.GetIdentity());
						isInPrison = true;
				        break;
				    }
				}
				if (!isInPrison) {
				    escapeePlayers.Insert(new DZLEscapedPlayer(DayZPlayer.Cast(player), dzlPlayer.arrestTimeInMinutes));
					continue;
				}
								
				if (!dzlPlayer.IsPlayerInArrest()) {
					ChangeItems(PlayerBase.Cast(player), arrestConfig.exPrisonerItems, arrestConfig.shouldDeleteAllItemsOnExPrissoner);
					
					vector randPosition = arrestConfig.exPrisonerAreas.GetRandomElement();
					
					if(randPosition) {
						player.SetPosition(randPosition);
					}
				}
			}
		}

		GetGame().RPCSingleParam(null, DAY_Z_LIFE_GET_ESCAPED_PLAYERS_RESPONSE, new Param4<ref array<ref DZLEscapedPlayer>, int, int, int>(escapeePlayers, copCount, medicCount, civCount), true);
	}

	private void ChangeItems(PlayerBase prisoner, array<string> items, bool shouldDeleteAllItems) {
		
		if (shouldDeleteAllItems) {
			prisoner.RemoveAllItems();
		}
		
		foreach(string type: items) {
			EntityAI item;
			InventoryLocation inventoryLocation = new InventoryLocation;
			if (prisoner.GetInventory().FindFirstFreeLocationForNewEntity(type, FindInventoryLocationType.ANY, inventoryLocation)) {
            	item = prisoner.GetHumanInventory().CreateInInventory(type);
	        } else if (!prisoner.GetHumanInventory().GetEntityInHands()) {
	            item = prisoner.GetHumanInventory().CreateInHands(type);
	        }
	
	        if (!item) {
	            item = prisoner.SpawnEntityOnGroundPos(type, prisoner.GetPosition());
	        }
		}
	
	}
}
