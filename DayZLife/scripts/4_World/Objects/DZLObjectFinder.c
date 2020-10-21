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

		DebugMessageDZL("has found count objects: " + geom.Count().ToString());

        Object obj;

        obj = CheckForObject(geom);
      
        return obj;
    }


    Container_Base GetContainerAt(vector from, vector to, string typeToSearch, Object ignore = NULL, float radius = 0.1, Object with = NULL){
        vector contact_pos;
        vector contact_dir;
        int contact_component;

        set< Object > geom = new set< Object >;

        DayZPhysics.RaycastRV(from, to, contact_pos, contact_dir, contact_component, geom, with, ignore, false, false, ObjIntersectGeom, radius);

		DebugMessageDZL("has found count objects: " + geom.Count().ToString());

        Object obj = CheckForContainer(geom, typeToSearch);
        if (!obj) return null;

        return Container_Base.Cast(obj);
    }

    private Object CheckForContainer(set< Object > geom, string typeToSearch) {
        for (int newObject = 0; newObject < geom.Count(); ++newObject){
           Object obj = geom.Get(newObject);
		   DebugMessageDZL("Has found: " + obj.GetType() + "search for: " +typeToSearch);
           if (obj.GetType() == typeToSearch) {
               return obj;
               break;
           }
       }
        
       return null;
    }

    private Object CheckForObject(set< Object > geom) {
        for (int newObject = 0; newObject < geom.Count(); ++newObject){
            Object obj = geom.Get(newObject);
            foreach(DZLHouseDefinition housedef: houseDefinitions) {
                DebugMessageDZL(obj.GetType());
                if (obj.GetType() == housedef.houseType) {
                    return obj;
                    break;
                }
            }
        }
        return null;
    }

}