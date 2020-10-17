class SpawnCalculator
{
    static vector GetPosition(vector position, vector rotation, vector relativePosition) {
		vector basePosition;
		basePosition[0] = position[0] + relativePosition[0];
		basePosition[1] = position[1] + relativePosition[1];
		basePosition[2] = position[2] + relativePosition[2];
		
		TrieAngel trieAngel = TrieAngel.CreateFromVector(basePosition);
		
		
		return GetNewPositions(trieAngel.c, trieAngel.a, trieAngel.b, trieAngel.beta, trieAngel.alpha); 
    }

    
	// http://www-lehre.inf.uos.de/~cg/2010/PDF/kap-06.pdf
    private static vector GetNewPositions(float length, float x, float y, float beta, float alpha) {
		float x1 = x * Math.Cos(beta) - y * Math.Sin(beta);
		float y1 = x * Math.Sin(beta) - y * Math.Cos(beta);
		
		vector newPos;
		
		newPos[0] = x1;
		newPos[1] = 0;
		newPos[2] = y1;
		
		return newPos;
	}
	

}
