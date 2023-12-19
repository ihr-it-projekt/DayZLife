class DZLCarTuneConfig {
    string type;
    ref array<ref CarTuneAttachment> tunedAttachments;

    void DZLCarTuneConfig(string type, array<ref CarTuneAttachment> tunedAttachments) {
        this.type = type;
        this.tunedAttachments = tunedAttachments;
    }
}