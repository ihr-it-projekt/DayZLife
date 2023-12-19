class DZLLoadoutMedicActionObject: DZLBaseActionObject {
    void DZLLoadoutMedicActionObject() {
        this.isMedicLoadOut = true;
    }

    override void SetActions() {
        super.SetActions();

        AddAction(ActionOpenLoadOutMenu);
    }
}