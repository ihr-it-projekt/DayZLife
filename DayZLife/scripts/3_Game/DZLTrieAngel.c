class DZLTrieAngel
{
    float a;
    float b;
    float c;
    float alpha;
    float beta;
    float gama;

    void DZLTrieAngel(float a, float b, float c, float alpha, float beta, float gama) {
        this.a = a;
        this.b = b;
        this.c = c;
        this.alpha = alpha;
        this.beta = beta;
        this.gama = gama;
    }

    static DZLTrieAngel CreateFromVector(vector position) {
        float _a = position[0]; //10
        float _b = position[2]; //20
        float _c = Math.Sqrt(_a * _a + _b * _b);

        float _beta = Math.Cos(_a/_c);
        float _alpha = 90;
        float _gama = 180 - _alpha - _beta;

        return new DZLTrieAngel(_a, _b, _c, _alpha, _beta, _gama);
    }

}