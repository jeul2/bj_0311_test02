/*
�����Ÿ�
1. �����Ÿ��� �������� 1~1000 ���� ���� �� �ִ�.
	1.1 �Ÿ����� ���԰� 1�� �ְ�, 0,1,2 ����, ����, �ٳ����� �Ǵ�.
2. ����� 1���� �Ÿ��� ���� ������ ������ ���� �� ������ ��Ģ�� �ִ�.
	2.1 ù��°�� ���⸸�� �Դ´�.
	2.2 �� ���� �Ծ��� ����(0, 1, 2)�� ( Pre + 1 )% 3 �� ���� �� �ִ�.
	2.3 ������������ ����ģ��. ����ġ�� �ٽ� �� ���Ը� �鸱 �� ����.
3. ���� �� �ִ� ���� ������ ����Ѵ�.
---------------------
�迭 1����, ���Կ� ���� ���������� ���� �� �ִ�.

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