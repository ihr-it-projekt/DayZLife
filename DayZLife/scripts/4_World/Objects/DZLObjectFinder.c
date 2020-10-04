class DZLObjectFinder
{
    ref DZLHouseServerConfig config;

    void DZLObjectFinder(DZLHouseServerConfig config) {
        this.config = config;
    }

    Object GetObjectsAt(vector position, Object ignore = NULL, float radius = 2, Object with = NULL){
        vector contact_pos;
        vector contact_dir;
        int contact_component;

        set< Object > geom = new set< Object >;

        DayZPhysics.RaycastRV(position, position, contact_pos, contact_dir, contact_component, geom, with, ignore, false, false, ObjIntersectGeom, radius);

        
        for (int newObject = 0; newObject < geom.Count(); ++newObject){
			Object obj = geom.Get(newObject);
			foreach(DZLHouseDefinition housedef: config.houseConfigs) {
				if (obj.GetType() == housedef.houseType) {
					return obj;
					break;
				}	
			} 
		}
        

        return NULL;
    }

}