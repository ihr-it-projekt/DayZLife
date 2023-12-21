modded class PlayerBase {
    override void IncreaseDiseaseCount() {
        m_DiseaseCount = 0;
    }

    override void DecreaseDiseaseCount() {
        m_DiseaseCount = 0;
    }

    bool HasDisease() {
        return false;
    }
}
