class DZLLoadOuts {
    string version = "2";
    string jobId;
    ref array<ref DZLLoadOutCategory> loadOutCategories = new array<ref DZLLoadOutCategory>;
    ref array<ref DZLLoadOutPosition> loadOutPosition = new array<ref DZLLoadOutPosition>;
    [NonSerialized()]string folderPath = "";

    void DZLLoadOuts(string _jobId) {};
}
