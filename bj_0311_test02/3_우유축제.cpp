/*
우유거리
1. 우유거리가 직선으로 1~1000 까지 있을 수 있다.
	1.1 거리마다 가게가 1개 있고, 0,1,2 딸기, 초코, 바나나를 판다.
2. 사람은 1부터 거리가 끝날 때까지 우유를 마실 수 있지만 규칙이 있다.
	2.1 첫번째는 딸기만을 먹는다.
	2.2 이 전에 먹었던 우유(0, 1, 2)에 ( Pre + 1 )% 3 만 먹을 수 있다.
	2.3 먹을수없으면 지나친다. 지나치면 다신 그 가게를 들릴 수 없다.
3. 마실 수 있는 우유 개수를 출력한다.
---------------------
배열 1개로, 가게에 따른 우유정보를 넣을 수 있다.

*/

#include <stdio.h>


int main()
{
	int nInputSize(0);
	int *pStoreData(nullptr);

	int nDrinkCount(0);
	int nPreMilkType(0);
	int nDrinkAbleType(0);

	freopen("input.txt", "r", stdin);
	//
	scanf("%d", &nInputSize);
	pStoreData = new int[nInputSize] {};
	
	for (int i = 0; i < nInputSize; ++i)
	{
		scanf("%d", &pStoreData[i]);
	}
	//
	nPreMilkType = 2;
	nDrinkAbleType = 0;
	for (int i = 0; i < nInputSize; ++i)
	{
		if (pStoreData[i] == nDrinkAbleType)
		{
			nPreMilkType = nDrinkAbleType;
			nDrinkAbleType = (pStoreData[i] + 1) % 3;
			++nDrinkCount;
		}

	}

	printf("%d\n", nDrinkCount);

	//
	delete[] pStoreData;
	pStoreData = nullptr;
	return 0;
}