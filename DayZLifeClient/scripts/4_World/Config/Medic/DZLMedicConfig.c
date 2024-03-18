class DZLMedicConfig {
    string version = "3";
    ref array<ref DZLBaseSpawnPoint> hospitalSpawnPoints = new array<ref DZLBaseSpawnPoint>;
    int priceHospitalHeal = 5000;
    int priceMedicHeal = 1000;
    float deleteDeadBodyTimeWhenHealedByMedic = 5;
    int minTimeBeforeHospital = 600;
    int minTimeBeforeHospitalWhenMinMedicNotOnline = 300;
    int minTimeBeforeKillButton = 20;
    int minMedicCountForHospitalTimer = 1;

}
