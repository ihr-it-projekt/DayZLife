class DZLObjectFinder
{
    ref DZLHouseServerConfig config;

    void SetConfig(DZLHouseServerConfig config) {
        this.config = config;
    }

    Object GetObjectsAt(vector from, vector to, Object ignore = NULL, float radius = 0.5, Object with = NULL){
        vector contact_pos;
        vector contact_dir;
        int contact_component;

        set< Object > geom = new set< Object >;
        set< Object > view = new set< Object >;

        DayZPhysics.RaycastRV(from, to, contact_pos, contact_dir, contact_component, geom, with, ignore, false, false, ObjIntersectGeom, radius);
        DayZPhysics.RaycastRV(from, to, contact_pos, contact_dir, contact_component, view, with, ignore, false, false, ObjIntersectView, radius);


		DebugMessageDZL("has found count objects: " + geom.Count().ToString());
		DebugMessageDZL("has found count objects: " + view.Count().ToString());

        Object obj;

        obj = CheckForObject(view);
        if (!obj) {
            obj = CheckForObject(geom);
        }

        if (obj.GetType() == "HouseInfoPoint") {
            obj = GetObjectsAt(from, to, obj);
        }

        return obj;
    }


    private Object CheckForObject(set< Object > geom) {
        for (int newObject = 0; newObject < geom.Count(); ++newObject){
            Object obj = geom.Get(newObject);
            foreach(DZLHouseDefinition housedef: config.houseConfigs) {
                DebugMessageDZL(obj.GetType());
                if (obj.GetType() == housedef.houseType || obj.GetType() == "HouseInfoPoint") {
                    return obj;
                    break;
                }
            }
        }
        return null;
    }

}