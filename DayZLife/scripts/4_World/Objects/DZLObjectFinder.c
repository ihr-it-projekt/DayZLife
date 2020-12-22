class DZLObjectFinder
{
   	ref array<ref DZLHouseDefinition> houseDefinitions;

    void SetConfig(ref array<ref DZLHouseDefinition> houseDefinitions) {
        this.houseDefinitions = houseDefinitions;
    }

    Object GetObjectsAt(vector from, vector to, Object ignore = NULL, float radius = 0.5, Object with = NULL){
        vector contact_pos;
        vector contact_dir;
        int contact_component;

        set< Object > geom = new set< Object >;

        DayZPhysics.RaycastRV(from, to, contact_pos, contact_dir, contact_component, geom, with, ignore, false, false, ObjIntersectGeom, radius);

        Object obj;

        obj = CheckForObject(geom);
      
        return obj;
    }

    void DeleteContainerAt(vector from, vector to, string typeToSearch, Object ignore = NULL, float radius = 0, Object with = NULL,int tries = 0){
        vector contact_pos;
        vector contact_dir;
        int contact_component;

        set< Object > geom = new set< Object >;

        DayZPhysics.RaycastRV(from, to, contact_pos, contact_dir, contact_component, geom, with, ignore, false, false, ObjIntersectGeom, radius);
        DebugMessageDZL(" geom.Count() " +  geom.Count().ToString());
		Object obj;
        
		if (0 == geom.Count()) {
           if (tries == 3) {
                return;
           }
           DeleteContainerAt(from, to, typeToSearch, obj, radius + 0.5, null, tries + 1);
           return;
        } else {
            for (int newObject = 0; newObject < geom.Count(); ++newObject){
                obj = geom.Get(newObject);
                DebugMessageDZL("obj.GetType() " + obj.GetType());
                DebugMessageDZL("typeToSearch " + typeToSearch);
                if (obj.GetType() == typeToSearch) {
                   GetGame().ObjectDelete(obj);
                   return;
                } else {
                   if (tries == 3) {
                        return;
                   }
                   DeleteContainerAt(from, to, typeToSearch, obj, radius + 0.5, null, tries + 1);
                   return;
                }
            }
        }

    }

    private Object CheckForObject(set< Object > geom) {
        for (int newObject = 0; newObject < geom.Count(); ++newObject){
            Object obj = geom.Get(newObject);
            foreach(DZLHouseDefinition housedef: houseDefinitions) {
                if (obj.GetType() == housedef.houseType) {
                    return obj;
                    break;
                }
            }
        }
        return null;
    }

}
