class DZLSpawnCalculator
{
    static vector GetPosition(vector position, vector rotation, vector relativePosition) {
		DZLTrieAngel trieAngel = DZLTrieAngel.CreateFromVector(relativePosition);

		vector newRelativePos = GetNewPositions(trieAngel.c, trieAngel.a, trieAngel.b, trieAngel.beta, trieAngel.alpha);

        newRelativePos[0] = position[0] + newRelativePos[0];
        newRelativePos[1] = position[1] + newRelativePos[1];
        newRelativePos[2] = position[2] + newRelativePos[2];

        return newRelativePos;
    }
	
	

    
	// http://www-lehre.inf.uos.de/~cg/2010/PDF/kap-06.pdf
    private static vector GetNewPositions(float length, float x, float y, float beta, float alpha) {
		float x1 = x * Math.Cos(beta) - y * Math.Sin(beta);
		float y1 = x * Math.Sin(beta) + y * Math.Cos(beta);

		vector newPos;

		newPos[0] = x1;
		newPos[1] = 0;
		newPos[2] = y1;
		
		return newPos;
	}
	

}
