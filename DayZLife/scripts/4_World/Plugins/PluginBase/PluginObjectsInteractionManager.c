modded class PluginObjectsInteractionManager extends PluginBase
{
    override void Release(Object target){
        DebugMessageDZL("Release " + target.IsBuilding().ToString());
        if (!target.IsBuilding()) {
            super.Release(target);
        }
    }

}