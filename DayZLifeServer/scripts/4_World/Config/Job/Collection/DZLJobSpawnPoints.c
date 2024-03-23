modded class DZLJobSpawnPoints {

    void DZLJobSpawnPoints(string jobId) {
        folderPath = DAY_Z_LIFE_SERVER_FOLDER_CONFIG + jobId + "\\";
        CheckDZLDataSubPath(folderPath);
        if(!Load()) {
            DZLSpawnPoint point;
            array<string> items = new array<string>;

            if(jobId == DAY_Z_LIFE_JOB_COP) {
                items = {"PoliceVest", "PoliceJacket", "PolicePants", "PoliceCap", "DressShoes_Black", "TelescopicBaton"};

                point = new DZLSpawnPoint("Police Station Chernogorsk", "6632.750977 11.370984 2592.997559", "-28.203798 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Police Station Elektrozavodsk", "10462.418945 10.105204 2271.804932", "68.419617 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Police Station Svetlojarsk", "13848.695313 24.675764 13212.036133", "128.822388 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Police Station Novodmitrovsk", "11486.428711 50.482922 14489.633789", "-70.562645 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Police Station Severograd", "7741.420898 122.455505 12631.818359", "100.479248 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Police Station Zelenogorsk", "2735.672607 210.621185 5377.391602", "28.748816 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Police Station Berezino", "12065.640625 57.869034 9057.484375", "134.757706 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Police Outpost Novoselki", "6195.730957 30.349514 2916.213135", "-153.080688 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Police Outpost Kamyshovo", "12050.808594 10.327807 3603.478271", "-137.151077 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Police Outpost Dolina", "11188.155273 80.861008 6598.448730", "-3.070054 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Police Outpost Berezino", "12926.571289 10.578716 10174.988281", "157.502136 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Police Outpost Novaya Petrovka", "3429.129395 197.304077 13016.505859", "85.535614 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Police Outpost Vybor", "3717.876953 315.595245 8923.975586", "-106.192551 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Police Outpost Novy Sobor", "7178.267090 297.714508 7672.066895", "60.293751 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Police Outpost Komarovo", "3576.188232 10.873785 2436.571045", "25.535524 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Police Outpost Nadezhdino", "5863.132813 142.545685 4684.122070", "-58.558037 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Police Outpost Staroye", "10151.223633 248.154800 5525.236328", "-141.274200 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Police Outpost Grishino", "6006.648438 271.538849 10356.491211", "-5.301322 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Police Outpost Gorka", "9538.000000 307.313110 8800.126953", "53.449543 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Police Outpost Krasnostav", "11060.768555 231.467606 12488.763672", "-95.663597 0 0", items);
                spawnPoints.Insert(point);

            } else if(jobId == DAY_Z_LIFE_JOB_MEDIC) {
                items = {"ParamedicJacket_Blue", "ParamedicPants_Blue", "Sneakers_White", "BandageDressing", "BandageDressing", "BandageDressing", "Morphine", "Morphine", "Morphine", "Epinephrine", "Epinephrine", "Epinephrine", "SalineBagIV", "SalineBagIV", "SalineBagIV", "TetracyclineAntibiotics", "CharcoalTablets", "VitaminBottle", "PainkillerTablets", "SurgicalGloves_LightBlue", "SurgicalMask"};
                point = new DZLSpawnPoint("Hospital Chernogorsk", "6460.642578 9.716865 2734.174561", "-35.551224 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Hospital Elektrozavodsk", "10288.325195 12.781819 2265.676270", "174.492218 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Hospital Berezino", "11913.635742 54.291801 9056.839844", "-131.009918 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Hospital Pavlovo", "2184.552002 91.581612 3353.090332", "105.095566 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Hospital Novodmitrovsk", "11394.348633 78.513062 14602.299805", "-54.714001 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Hospital Severograd", "8019.276367 114.149002 12732.478516", "-178.702087 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Medic Station Solnichniy", "13391.141602 6.642958 6325.412109", "34.405697 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Medic Station Berezino", "12784.613281 6.546667 10056.283203", "132.671509 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Medic Station Svetlojarsk", "13869.391602 20.997799 13126.976563", "-34.106239 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Medic Station Novaya Petrovka", "3466.028809 196.958252 13164.150391", "83.904434 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Medic Station Vybor", "3752.554199 312.510742 9021.624023", "-24.320047 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Medic Station Stary Sobor", "5999.912598 307.862762 7686.959473", "52.903572 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Medic Station Gorka", "9470.009766 304.953186 8827.878906", "-162.231049 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Medic Station Staroye", "10126.196289 246.007263 5505.813965", "123.815544 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Medic Station Zelenogorsk", "2746.510742 200.855423 5172.751953", "132.636261 0 0", items);
                spawnPoints.Insert(point);
            } else if(jobId == DAY_Z_LIFE_JOB_ARMY) {
                items = {"BDUPants", "BDUJacket", "MilitaryBelt", "TacticalGloves_Green", "MilitaryBoots_Black", "MilitaryBeret_Red", "M4A1"};
                point = new DZLSpawnPoint("North West Airfield", "4657.540039 343.892548 9586.001953", "64.744408 0.0 0.0", items);
                spawnPoints.Insert(point);
            } else {
                items = {"Jeans_Black", "Shirt_BlackCheck", "AthleticShoes_Black"};
                point = new DZLSpawnPoint("Train Station Chernogorsk", "6547.232910 14.080640 2617.040039", "-7.892493 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Train Station Elektrozavodsk", "10336.419922 6.144979 2120.515625", "-159.037292 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Train Station Kamyshovo", "11966.688477 6.357907 3556.739502", "-13.138873 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Train Station Solnichniy", "13359.731445 7.915360 6142.770508", "-87.118515 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Train Station Solnich", "13162.916992 6.358726 7100.083008", "68.426018 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Train Station Berezino", "12987.839844 6.166841 10240.698242", "-100.820023 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Train Station Svetlojarsk", "13984.972656 3.435675 13483.834961", "35.998260 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Train Station Novodmitrovsk", "11645.218750 58.210663 14112.760742", "161.405289 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Train Station Severograd", "7850.665039 140.101868 12413.544922", "-19.548033 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Train Station Novaya Petrovka", "3545.697998 220.242340 12561.092773", "-37.574173 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Train Station Vavilovo", "2008.193481 249.498199 11283.776367", "105.851578 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Train Station Zelenogorsk", "2478.369629 190.588913 5236.167969", "-32.896881 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Train Station Kamenka", "1884.486816 6.356084 2174.869629", "-14.907640 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Train Station Komarovo", "3664.931396 6.747039 2401.877197", "-18.534702 0 0", items);
                spawnPoints.Insert(point);

                point = new DZLSpawnPoint("Train Station Balota", "4407.020996 6.351238 2313.319336", "17.710466 0 0", items);
                spawnPoints.Insert(point);
            }
            Save();
        }

        if(version == "1") {
            version = "2";
            blockTimeForJobChange = 3600;
            Save();
        }
    }

    private bool Load() {
        if(FileExist(folderPath + "SpawnPoints.json")) {
            JsonFileLoader<DZLJobSpawnPoints>.JsonLoadFile(folderPath + "SpawnPoints.json", this);
            return true;
        }
        return false;
    }

    private void Save() {
        JsonFileLoader<DZLJobSpawnPoints>.JsonSaveFile(folderPath + "SpawnPoints.json", this);
    }
}
