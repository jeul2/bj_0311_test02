/*
1. ����ũ�� ���� ����ŭ �Ǻ���ġ���� �� N�� �־�����.
	1.1 N�� ���� �ٸ� �Ǻ���ġ ���� ������ �̷�����ִ�.
	2.2 N�� �̷�� �Ǻ���ġ�� ����� ���� 1�� �̻��� �� �ִ�.

2. ���� ���� ���� ������ N�� �̷�� �Ǻ���ġ ������ ã�´�.

3. ã�� �Ǻ���ġ������ ���� ������� ����Ѵ�.
---------
N���� ���� �Ǻ���ġ�� ���� �� �ʿ��ϴ�.
�ϴ� f1=1 , f2= 1�̹Ƿ�, N�� 1�� 2�� �� �̷������.
1�� f1�� �� �� �ְ�, f2�� �� �� �ִ�.
�� ���� ���� 2, 3, 5.. �� ���� ������ ���� �� �ִ�.

N�� �Ǻ���ġ �� �̸�, �ش� �Ǻ���ġ ���� � ������ �ְ�, N���� �Ǻ���ġ���� �� ���� �����Ѵ�.
N�� �Ǻ���ġ ���� �ƴϸ�, N�� ���� ������ �Ǻ���ġ ���� ã��,�̸� � ������ �ְ�, N���� �Ǻ���ġ���� �� ���� �����Ѵ�.
�̸� �ݺ��Ѵ�.
N = 0�̸� �����Ѵ�.
-------
N�� ������ �Ǻ���ġ���� ã�� ���.
�Ǻ���ġ������ �����ϴ� ���.
����� �Ǻ���ġ���� ���� ������ ����ϴ� ���.
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