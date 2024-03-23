class DZLCarTuneConfig {
    string type;
    ref array<ref CarTuneAttachment> tunedAttachments;

    void DZLCarTuneConfig(string _type, array<ref CarTuneAttachment> _tunedAttachments) {
        this.type = _type;
        this.tunedAttachments = _tunedAttachments;
    }
}