class DZLAccess {

    string id;
    ref map<string, bool> canManage = new map<string, bool>();

    void DZLAccess(string _id, array<string> jobs) {
        this.id = _id;

        foreach(string job: jobs) {
            canManage.Set(job, true);
        }

        canManage.Set(DAY_Z_LIFE_ACCESS_CARS, true);
        canManage.Set(DAY_Z_LIFE_ACCESS_PLAYERS, true);
    }

    void MigrateAccess(DZLPlayerAccess playerAccess) {

        canManage.Set(DAY_Z_LIFE_JOB_COP, playerAccess.CanManageCops());
        canManage.Set(DAY_Z_LIFE_JOB_MEDIC, playerAccess.CanManageMedic());
        canManage.Set(DAY_Z_LIFE_JOB_ARMY, playerAccess.CanManageArmy());
        canManage.Set(DAY_Z_LIFE_ACCESS_CARS, playerAccess.CanManageCars());
        canManage.Set(DAY_Z_LIFE_ACCESS_PLAYERS, playerAccess.CanManagePlayers());
    }

    bool HasAccess(string type) {
        return !!canManage.Get(type);
    }
}