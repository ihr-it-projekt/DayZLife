class DZLLoadOuts {
    string version = "2";
    string jobId;
    ref array<ref DZLLoadOutCategory> loadOutCategories = new array<ref DZLLoadOutPosition>;
    ref array<ref DZLLoadOutPosition> loadOutPosition = new array<ref DZLLoadOutCategory>;
}
