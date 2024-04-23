class DZLSpawnHelper {

    static bool SpawnContainer(vector position, vector orientation, string gameObjectName) {
        Container_Base obj = Container_Base.Cast(GetGame().CreateObject(gameObjectName, position));
        if(!obj) {
            return false;
        }

        obj.SetFlags(EntityFlags.STATIC, false);
        DZLSpawnHelper.SetPositionAndOrientation(obj, position, orientation);

        return true;
    }

    static Object SpawnActionPoint(vector pos, vector orientation, string gameObjectName) {
        //pos[1] = GetGame().SurfaceY(pos[0], pos[2]);
        Object game_obj = GetGame().CreateObject(gameObjectName, pos, false, false, true);
        if(!game_obj) {
            return null;
        }

        game_obj.SetAllowDamage(false);
        DZLSpawnHelper.SetPositionAndOrientation(game_obj, pos, orientation);

        return game_obj;
    }

    static void SetPositionAndOrientation(Object game_obj, vector position, vector orientation) {
        game_obj.SetPosition(position);
        game_obj.SetOrientation(orientation);
        game_obj.SetOrientation(game_obj.GetOrientation()); //Collision fix
        game_obj.Update();
        game_obj.SetAffectPathgraph(true, false);
        if(game_obj.CanAffectPathgraph()) {
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(GetGame().UpdatePathgraphRegionByObject, 100, false, game_obj);
        }
    }

    static bool Add(EntityAI parent, DZLStoreItem itemInStock, ref InventoryLocation inventoryLocation = null) {
        EntityAI item;
        bool spawnOnGround = false;

        if(!inventoryLocation) {
            inventoryLocation = new InventoryLocation;
        }

        if(parent.GetInventory().FindFirstFreeLocationForNewEntity(itemInStock.type, FindInventoryLocationType.ANY, inventoryLocation)) {
            item = parent.GetInventory().CreateInInventory(itemInStock.type);
        }

        if(!item) {
            item = parent.GetInventory().CreateAttachment(itemInStock.type);
        }

        if(!item) {
            item = parent.GetInventory().CreateEntityInCargo(itemInStock.type);
        }

        if(!item) {
            spawnOnGround = true;
            item = parent.SpawnEntityOnGroundPos(itemInStock.type, parent.GetPosition());
        }

        if(!item) return spawnOnGround;

        item.SetHealth(itemInStock.health);

        ItemBase castItem;
        if(item.IsMagazine()) {
            Magazine mag = Magazine.Cast(item);

            if(!mag) {
                return spawnOnGround;
            }
            mag.ServerSetAmmoCount(itemInStock.GetQuantity());
        } else if(item.IsAmmoPile()) {
            Ammunition_Base ammo = Ammunition_Base.Cast(item);

            if(!ammo) {
                return spawnOnGround;
            }
            ammo.ServerSetAmmoCount(itemInStock.GetQuantity());
        } else if(ItemBase.CastTo(castItem, item)) {
            castItem.SetQuantity(itemInStock.GetQuantity(), true, true);
        }

        if(itemInStock.attached.Count() > 0) {
            foreach(DZLStoreItem itemAttached: itemInStock.attached) {
                if(DZLSpawnHelper.Add(item, itemAttached, inventoryLocation) && !spawnOnGround) {
                    spawnOnGround = true;
                }
            }
        }

        return spawnOnGround;
    }


static ref DZLZone DZLSearchForFreePositionAndOrientation(vector position, vector orientation = "0 0 0", vector boxForDetection = "5.0 3.5 5.0", int tries = 1) {
    position[1] = GetGame().SurfaceY(position[0], position[2]);

    array<Object> excludedObjects = new array<Object>;
    array<Object> nearbyObjects = new array<Object>;

    bool colliding = GetGame().IsBoxColliding(position, orientation, boxForDetection, excludedObjects, nearbyObjects);
    if(!colliding) return new DZLZone(position, orientation);

    excludedObjects = null;
    nearbyObjects = null;

    if(DZLSearchRotation(position, orientation, boxForDetection)) return new DZLZone(position, orientation);

    if(10 < tries) ++tries;
    if(20 < tries) ++tries;
    if(30 < tries) ++tries;
    if(40 < tries) ++tries;
    ++tries;

    float x = 0.1 * tries * Math.Cos(tries);
    float y = 0.1 * tries * Math.Sin(tries);

    position[0] = position[0] + x;
    position[2] = position[2] + y;

    return DZLSearchForFreePositionAndOrientation(position, orientation, boxForDetection, tries);
}

static bool DZLSearchRotation(vector position,out vector orientation, vector boxForDetection = "3.0 3.0 3.0", int tries = 1) {
    position[1] = GetGame().SurfaceY(position[0], position[2]);
    array<Object> excludedObjects = new array<Object>;
    array<Object> nearbyObjects = new array<Object>;
    bool colliding = GetGame().IsBoxColliding(position, orientation, boxForDetection, excludedObjects, nearbyObjects);
    if(!colliding) return true;

    excludedObjects = null;
    nearbyObjects = null;

    orientation[0] = orientation[0] + 10.0;

    if(orientation[0] > 360) return false;

    return DZLSearchRotation(position, orientation, boxForDetection, tries + 1);
}
}
