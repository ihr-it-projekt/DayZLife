class DZLAdmin {
    // Deprecated Remove 14.03.2025
    private ref array<ref DZLPlayerAccess> access = new array<ref DZLPlayerAccess>();
    // end deprecated
    private ref array<ref DZLAccess> playerAccesses = new array<ref DZLAccess>();
    string version = "7";

    bool HasAccess(string _access, string ident) {
        foreach(DZLAccess playerAccess: playerAccesses) {
            if(!playerAccess) continue;
            if(playerAccess.id != ident) continue;

            return playerAccess.HasAccess(_access);

        }
        return false;
    }
}
