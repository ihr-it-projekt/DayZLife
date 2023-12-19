class DZLTraderConfig {
    ref DZLTraderPositionCollection positions;
    ref DZLTraderCategoryCollection categories;

    void DZLTraderConfig() {
        this.positions = new DZLTraderPositionCollection;
        this.categories = new DZLTraderCategoryCollection;
    }
}