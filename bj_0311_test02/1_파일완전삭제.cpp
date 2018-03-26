/*
1.�Է� <=1000 ���� ��Ʈ. 0�� 1�� �̷���� ������
	1.1 �����Է� ��Ʈ
	1.2 N���� �� ���� ��º�Ʈ

2.����. 1�� ����� 0�� 1��, 1�� 0���� �Է�
	2.1 1�� ������ ���ݴ�, 2�� ������ �Է°� ����..
	2.2 N�� ���� = N % 2�� ����� ����.

3.�����Էº�Ʈ�� N ���� ������ 1.2�� ��º�Ʈ�� �����ϸ� �����Ϸ�/ �׷��������� ��������

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
