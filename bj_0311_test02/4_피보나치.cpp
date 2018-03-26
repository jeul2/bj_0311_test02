/*
1. 정수크기 제한 전만큼 피보나치수의 합 N이 주어진다.
	1.1 N은 서로 다른 피보나치 수의 합으로 이루어져있다.
	2.2 N을 이루는 피보나치의 경우의 수는 1개 이상일 수 있다.

2. 가장 작은 수의 합으로 N을 이루는 피보나치 수들을 찾는다.

3. 찾은 피보나치수들을 작은 순서대로 출력한다.
---------
N보다 작은 피보나치의 수가 다 필요하다.
일단 f1=1 , f2= 1이므로, N은 1과 2로 다 이루어진다.
1은 f1이 될 수 있고, f2도 될 수 있다.
그 외의 것은 2, 3, 5.. 이 들의 합으로 만들 수 있다.

N이 피보나치 수 이면, 해당 피보나치 수를 어떤 공간에 넣고, N에서 피보나치수를 뺀 값을 갱신한다.
N이 피보나치 수가 아니면, N과 가장 근접한 피보나치 수를 찾고,이를 어떤 공간에 넣고, N에서 피보나치수를 뺀 값을 갱신한다.
이를 반복한다.
N = 0이면 종료한다.
-------
N과 근접한 피보나치수를 찾는 기능.
피보나치수들을 저장하는 기능.
저장된 피보나치들을 작은 수부터 출력하는 기능.
*/

#include <stdio.h>
enum E_MAXFIBOINDEX { eMAXFIBOINDEX = 100};

int main()
{
	int nTestCaseNum(0);
	int nInputNumber(0);

	int arFibo[eMAXFIBOINDEX]{0, 1, 1, };
	int nFiboMaxIndex(0);

	int nData(0);
	int nFiboIndex(0);

	int arIndexData[eMAXFIBOINDEX]{};
	int nIndexDataCount(0);
	//
	freopen("input.txt", "r", stdin);
	//
	scanf("%d", &nTestCaseNum);
	for (int i = 0; i < nTestCaseNum; ++i)
	{


		scanf("%d", &nInputNumber);

		for (int i = 3; i <= eMAXFIBOINDEX; ++i)
		{
			arFibo[i] = arFibo[i - 2] + arFibo[i - 1];
			if (arFibo[i] > nInputNumber)
			{
				nFiboMaxIndex = i - 1;
				break;
			}
		}
		//
		nData = nInputNumber;
		nFiboIndex = nFiboMaxIndex;
		nIndexDataCount = 0;
		while (nData != 0)
		{
			for (int i = nFiboIndex; i != 0; --i)
			{
				if (nData >= arFibo[i])
				{
					nFiboIndex = i;
					break;
				}
			}

			nData -= arFibo[nFiboIndex];
			arIndexData[nIndexDataCount] = nFiboIndex;
			++nIndexDataCount;
		}

		//
		for (int i = 1; i <= nIndexDataCount; ++i)
		{
			printf("%d ", arFibo[arIndexData[nIndexDataCount - i]]);
		}
		printf("\n");

	}


	return 0;
}