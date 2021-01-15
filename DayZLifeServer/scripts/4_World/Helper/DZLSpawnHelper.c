class DZLSpawnHelper
{

    static bool SpawnContainer(vector position, vector orientation, string gameObjectName) {
        Container_Base obj = Container_Base.Cast(GetGame().CreateObject(gameObjectName, position));
        if (!obj) {
            return false;
        }

        obj.SetFlags(EntityFlags.STATIC, false);
        DZLSpawnHelper.SetPositionAndOrientation(obj, position, orientation);

		return true;
    }

    static DZLDatabase SpawnDataBase() {
		InventoryLocation il = new InventoryLocation;
        vector mat[4];
        Math3D.MatrixIdentity4(mat);
        mat[3] = DZLDatabase.POSITION;
        il.SetGround(NULL, mat);
         
        DZLDatabase obj = DZLDatabase.Cast(SpawnEntity("DZLDatabase", il, ECE_PLACE_ON_SURFACE, RF_DEFAULT));
		
        if (!obj) {
            DebugMessageDZL("Can not spawn db object");
            return null;
        }

        obj.SetFlags(EntityFlags.STATIC, false);
		DebugMessageDZL("Has spawned DB object");
        DZLSpawnHelper.SetPositionAndOrientation(obj, DZLDatabase.POSITION, "0 0 0");
        
		return obj;
    }

    static PlayerBase SpawnActionPoint(vector pos, vector orientation, string gameObjectName, bool isBanking, bool isLicence, bool isTrader, bool isLoadOut, bool isGarage) {
        //pos[1] = GetGame().SurfaceY(pos[0], pos[2]);
        Object game_obj = GetGame().CreateObject(gameObjectName, pos, false, false, true);
        if (!game_obj) {
           return null;
        }

        PlayerBase character = PlayerBase.Cast(game_obj);

        character.SetAllowDamage(false);
        DZLSpawnHelper.SetPositionAndOrientation(character, pos, orientation);
        character.IsDZLBank = isBanking;
        character.IsLicencePoint = isLicence;
        character.IsTrader = isTrader;
        character.IsLoadOut = isLoadOut;
        character.IsGarage = isGarage;

        return character;
    }

    static void SetPositionAndOrientation(Entity game_obj, vector position, vector orientation) {
        game_obj.SetPosition(position);
        game_obj.SetOrientation(orientation);
        game_obj.SetOrientation(game_obj.GetOrientation()); //Collision fix
        game_obj.Update();
        game_obj.SetAffectPathgraph(true, false);
        if( game_obj.CanAffectPathgraph() ) {
            GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater( GetGame().UpdatePathgraphRegionByObject, 100, false, game_obj );
        }
    }

    static EntityAI Add(EntityAI parent, DZLStoreItem itemInStock, ref InventoryLocation inventoryLocation = null) {
        EntityAI item;

        if (!inventoryLocation) {
            inventoryLocation = new InventoryLocation;
        }

        if (parent.GetInventory().FindFirstFreeLocationForNewEntity(itemInStock.type, FindInventoryLocationType.ANY, inventoryLocation)) {
            item = parent.GetInventory().CreateInInventory(itemInStock.type);
        }

        if(!item) {
            item = parent.GetInventory().CreateAttachment(itemInStock.type);
        }

        if(!item) {
            item = parent.GetInventory().CreateEntityInCargo(itemInStock.type);
        }

        if (!item) return null;

        item.SetHealth(itemInStock.health);

        ItemBase castItem;
        if(item.IsMagazine()) {
            Magazine mag = Magazine.Cast(item);

            if (!mag) {
                return item;
            }
            mag.ServerSetAmmoCount(itemInStock.GetQuantity());
        } else if(item.IsAmmoPile()) {
            Ammunition_Base ammo = Ammunition_Base.Cast(item);

            if (!ammo) {
                return item;
            }
            ammo.ServerSetAmmoCount(itemInStock.GetQuantity());
        } else if (ItemBase.CastTo(castItem, item)) {
            castItem.SetQuantity(itemInStock.GetQuantity(), true, true);
        }

        if(itemInStock.attached.Count() > 0) {
            foreach(DZLStoreItem itemAttached: itemInStock.attached) {
                DZLSpawnHelper.Add(item, itemAttached, inventoryLocation);
            }
        }

        return item;
    }
}
