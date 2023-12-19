class DZLTuningActionObject: DZLBaseActionObject {
    void DZLTuningActionObject() {
        this.isTuningPoint = true;
    }

    override void SetActions() {
        super.SetActions();

        AddAction(DZLActionOpenTuningMenu);
    }
}