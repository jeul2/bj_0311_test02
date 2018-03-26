/*
1.입력 <=1000 개의 비트. 0과 1로 이루어진 데이터
	1.1 최초입력 비트
	1.2 N연산 후 예상 출력비트

2.연산. 1번 연산시 0을 1로, 1을 0으로 입력
	2.1 1번 연산은 정반대, 2번 연산은 입력과 동일..
	2.2 N번 연산 = N % 2번 연산과 동일.

3.최초입력비트로 N 연산 수행후 1.2의 출력비트와 동일하면 삭제완료/ 그렇지않으면 삭제실패

*/

#include <stdio.h>
#include <string.h>

class C_BITDATA
{
private:
	int m_nData[1000];
	int m_nSize;

public:
	C_BITDATA();
	~C_BITDATA();
	C_BITDATA(const C_BITDATA &) = delete;
	const C_BITDATA& operator =(const C_BITDATA &) = delete;

public:
	void init(int nSize);

public:
	void setData(int nData, int nSize);
	void getData(int *pData, int nSize);

};

int main()
{
	C_BITDATA cData;

	int nCalculNum(0);
	int nInputSize(0);
	char arData[1000 + 1]{};
	int nInput(0);
	int nOutput(0);

	bool bIsSame(true);
	
	freopen("input.txt", "r", stdin);
	//
	scanf("%d", &nCalculNum);
	scanf("%s", arData);
	nInputSize = strlen(arData);
	////

	cData.init(nInputSize);

	for (int i = 0; i < nInputSize; ++i)
	{
		nInput = (int)arData[i];
		cData.setData(nInput, i);
	}

	//
	scanf("%s", arData);
	nCalculNum %= 2;

	for (int i = 0; i < nInputSize; ++i)
	{
		if (nCalculNum == 0)
		{
			cData.getData(&nOutput, i);
			if (nOutput != (int)arData[i])
			{
				bIsSame = false;
				break;
			}

		}
		else
		{
			cData.getData(&nOutput, i);
			if (nOutput == (int)arData[i])
			{
				bIsSame = false;
				break;
			}

		}

	}
	
	if (bIsSame == true)
	{
		printf("Deletion succeeded\n");
	}
	else
	{
		printf("Deletion failed\n");
	}


	return 0;
}

C_BITDATA::C_BITDATA()
{
}

C_BITDATA::~C_BITDATA()
{
}

void C_BITDATA::init(int nSize)
{
	m_nSize = nSize;
	for (int i = 0; i < nSize; ++i)
	{
		m_nData[i] = 0;
	}
}

void C_BITDATA::setData(int nData, int nSize)
{
	m_nData[nSize] = nData;
}

void C_BITDATA::getData(int * pData, int nSize)
{
	*pData = m_nData[nSize];
}
