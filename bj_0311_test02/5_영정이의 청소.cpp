/*
1.공간크기 Row, Col와 곰팡이의 개수 N을 입력
	1.1 N만큼 좌표데이터 (Col, Row)가 주어짐, 중복되지 않음
2.곰팡이 번식원리
	2.1 곰팡이는 주변위 대각선 ++ -- +- -+로 번식을 한다.
	2.2 번식이 완료할시 곰팡이는 사라진다.
	2.2 만약 사라질 곰팡이 중 그 자리에 번식을 했다면, 사라지지 않는다. 

3.곰팡이가 전체공간을 차지할 가능성이 있으면 YES, 아니면 NO이다.
-------------
언제 다 차지하는지, 차지하지 않는지는 중요치 않다.
그 전전날과 번식 후가 변화가 없다면, 더 이상 프로세스를 진행할 이유가 없다.
또한 전날과 번식 후가 변화가 없다면, 완전히 다 전체를 차지한 것이다.
------------
공간정보를 담는 배열 x, y

곰팡이가 없는 곳 0
곰팡이가 현재 있는 곳 1
곰팡이가 그 전날 있는 곳 ?

*/

#include <stdio.h>

struct S_POSITION
{
	int nRow;
	int nCol;
};

class C_QUEUE
{
private:
	S_POSITION * m_pData;
	int m_nHead;
	int m_nTail;
	int m_nSize;
	int m_nMaxSize;
public:
	C_QUEUE();
	~C_QUEUE();
public:
	void initialize(int nQueueSize);
	void release();
public:
	void enqueue(int nRow, int nCol);
	void dequeue(int *pRow, int *pCol);
	void getSize(int *pRes);
};

class C_VISITDATA
{
private:
	int **m_ppNextData;
	int **m_ppPreData;
	int **m_ppData;
	int m_nMaxRow;
	int m_nMaxCol;
public:
	C_VISITDATA();
	~C_VISITDATA();
public:
	void initialize(int nMaxRow, int nMaxCol);
	void release();
	void getMaxData(int *pRow, int *pCol);
	int getNextData(int nRow, int nCol);
private:
	bool isVisit(int **ppSrc, int nRow, int nCol);
	void setVisit(int **ppSrc, int nRow, int nCol, int nData);
	void changeVisitDatas(int **ppSrc, int **ppRes);
	void cleanData(int **ppSrc);
public:
	bool isVisitCurrent(int nRow, int nCol);
	bool isVisitNext(int nRow, int nCol);
	void setVisitCurrent(int nRow, int nCol, int nData);
	void setVisitNext(int nRow, int nCol, int nData);
	void updateData();
	int compareDatas(int *pResCode);
};

class C_MOLD
{
private:
	C_VISITDATA * m_pVisit;
	C_QUEUE *m_pQueue;
public:
	C_MOLD();
	~C_MOLD();
public:
	void initialize(C_VISITDATA &cVisit, C_QUEUE &cQueue);
	void release();
private:
	bool isSpread(int nRow, int nCol);
	void vanishCurrent(int nRow, int nCol);
public:
	void proceed();
	void showMold();
};

int main()
{
	C_QUEUE cQueue;
	C_VISITDATA cVisit;
	C_MOLD cMold;

	int nInput(0);
	int nMaxRow(0);
	int nMaxCol(0);
	int nRow(0);
	int nCol(0);

	//
	freopen("input.txt", "r", stdin);
	scanf("%d %d %d", &nMaxRow, &nMaxCol, &nInput);

	cVisit.initialize(nMaxRow, nMaxCol);
	cQueue.initialize(100000);

	for (int i = 0; i < nInput; ++i)
	{
		scanf("%d %d", &nRow, &nCol);
		cQueue.enqueue(nRow, nCol);
	}

	cMold.initialize(cVisit, cQueue);
	cMold.proceed();
	cMold.release();

	cVisit.release();
	cQueue.release();

	return 0;
}

C_QUEUE::C_QUEUE()
	: m_nHead(0), m_nSize(0), m_nTail(0), m_pData(nullptr), m_nMaxSize(0)
{
}

C_QUEUE::~C_QUEUE()
{
}

void C_QUEUE::initialize(int nQueueSize)
{
	m_nMaxSize = nQueueSize;
	m_nHead = 0;
	m_nSize = 0;
	m_nTail = -1;
	m_pData = new S_POSITION[m_nMaxSize]{};
}

void C_QUEUE::release()
{
	delete[] m_pData;
	m_pData = nullptr;
}

void C_QUEUE::enqueue(int nRow, int nCol)
{
	if (m_nSize >= m_nMaxSize)
	{
		printf("overflow error\n");
		return;
	}
	++m_nTail;
	m_pData[m_nTail].nRow = nRow;
	m_pData[m_nTail].nCol = nCol;
	++m_nSize;
	//
	printf("[%d %d] push\n", nRow, nCol);
}

void C_QUEUE::dequeue(int * pRow, int * pCol)
{
	if (m_nSize <= 0)
	{
		printf("underflow\n");
		return;
	}

	*pRow = m_pData[m_nHead].nRow;
	*pCol = m_pData[m_nHead].nCol;

	m_pData[m_nHead].nRow = 0;
	m_pData[m_nHead].nCol = 0;

	++m_nHead;
	--m_nSize;
}

void C_QUEUE::getSize(int * pRes)
{
	*pRes = m_nSize;
}

C_VISITDATA::C_VISITDATA()
	: m_nMaxCol(0), m_nMaxRow(0), m_ppData(nullptr), m_ppPreData(nullptr), m_ppNextData(nullptr)
{
}

C_VISITDATA::~C_VISITDATA()
{
}

void C_VISITDATA::initialize(int nMaxRow, int nMaxCol)
{
	m_nMaxRow = nMaxRow + 1;//
	m_nMaxCol = nMaxCol + 1;//

	m_ppData = new int*[m_nMaxRow] {};
	m_ppPreData = new int*[m_nMaxRow] {};
	m_ppNextData = new int*[m_nMaxRow] {};

	for (int i = 0; i < m_nMaxCol; ++i)
	{
		m_ppData[i] = new int[m_nMaxCol] {};
		m_ppPreData[i] = new int[m_nMaxCol] {};
		m_ppNextData[i] = new int[m_nMaxCol] {};
	}
}

void C_VISITDATA::release()
{
	for (int i = 0; i < m_nMaxCol; ++i)
	{
		delete[] m_ppData[i];
		m_ppData[i] = nullptr;
		delete[] m_ppPreData[i];
		m_ppPreData[i] = nullptr;
		delete[] m_ppNextData[i];
		m_ppNextData[i] = nullptr;
	}

	delete[] m_ppData;
	m_ppData = nullptr;
	delete[] m_ppPreData;
	m_ppPreData = nullptr;
	delete[] m_ppNextData;
	m_ppNextData = nullptr;
}

void C_VISITDATA::getMaxData(int * pRow, int * pCol)
{
	*pRow = m_nMaxRow;
	*pCol = m_nMaxCol;
}

int C_VISITDATA::getNextData(int nRow, int nCol)
{
	return m_ppNextData[nRow][nCol];
}

bool C_VISITDATA::isVisit(int ** ppSrc, int nRow, int nCol)
{
	if (ppSrc[nRow][nCol] != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void C_VISITDATA::setVisit(int ** pSrc, int nRow, int nCol, int nData)
{
	pSrc[nRow][nCol] = nData;
}

void C_VISITDATA::changeVisitDatas(int ** ppSrc, int ** ppRes)
{
	for (int i = 1; i < m_nMaxRow; ++i)
	{
		for (int j = 1; j < m_nMaxCol; ++j)
		{
			ppRes[i][j] = ppSrc[i][j];
		}
	}
}

void C_VISITDATA::cleanData(int ** ppSrc)
{
	for (int i = 1; i < m_nMaxRow; ++i)
	{
		for (int j = 1; j < m_nMaxCol; ++j)
		{
			ppSrc[i][j] = 0;
		}
	}
}

bool C_VISITDATA::isVisitCurrent(int nRow, int nCol)
{
	if (C_VISITDATA::isVisit(m_ppData, nRow, nCol))
	{
		return true;
	}
	else
		return false;
}

bool C_VISITDATA::isVisitNext(int nRow, int nCol)
{
	if (C_VISITDATA::isVisit(m_ppNextData, nRow, nCol) == true)
	{
		return true;
	}
	else
		return false;
}

void C_VISITDATA::setVisitCurrent(int nRow, int nCol, int nData)
{
	C_VISITDATA::setVisit(m_ppData, nRow, nCol, nData);
}

void C_VISITDATA::setVisitNext(int nRow, int nCol, int nData)
{
	C_VISITDATA::setVisit(m_ppNextData, nRow, nCol, nData);
}

void C_VISITDATA::updateData()
{
	C_VISITDATA::changeVisitDatas(m_ppData, m_ppPreData);
	C_VISITDATA::changeVisitDatas(m_ppNextData, m_ppData);
	C_VISITDATA::cleanData(m_ppNextData);
}

int C_VISITDATA::compareDatas(int *pResCode)
{
	int nComparePreToNext(0);
	int nCompareCurToNext(0);
	int nCount(0);
	int nFull(0);

	nFull = (m_nMaxCol - 1) * (m_nMaxRow - 1);

	for (int i = 1; i < m_nMaxRow; ++i)
	{
		for (int j = 1; j < m_nMaxCol; ++j)
		{
			if (m_ppPreData[i][j] != m_ppNextData[i][j])
			{
				nComparePreToNext = 1;
			}
			if (m_ppData[i][j] != m_ppNextData[i][j])
			{
				nCompareCurToNext = 1;
			}
			if (m_ppNextData[i][j] == 1)
			{
				++nCount;
			}
		}
	}

	if (nCount == nFull)
	{
		return 1;
	}
	else if (nCompareCurToNext == 1 || nComparePreToNext == 1)
	{
		return 0;
	}
	else
		return 2;
}

C_MOLD::C_MOLD()
	: m_pQueue(nullptr), m_pVisit(nullptr)
{
}

C_MOLD::~C_MOLD()
{
}

void C_MOLD::initialize(C_VISITDATA & cVisit, C_QUEUE & cQueue)
{
	m_pQueue = &cQueue;
	m_pVisit = &cVisit;
}

void C_MOLD::release()
{
	m_pQueue = nullptr;
	m_pVisit = nullptr;
}

bool C_MOLD::isSpread(int nRow, int nCol)
{
	int nMaxRow(0);
	int nMaxCol(0);

	m_pVisit->getMaxData(&nMaxRow, &nMaxCol);
	if (nRow > 0 && nRow < nMaxRow && nCol > 0 && nCol < nMaxCol)
	{
		return true;
	}
	else
		return false;
}

void C_MOLD::vanishCurrent(int nRow, int nCol)
{
	if (C_MOLD::m_pVisit->isVisitCurrent(nRow, nCol) == false)
	{
		m_pVisit->setVisitCurrent(nRow, nCol, 0);
	}
}


void C_MOLD::proceed()
{
	int nCount(0);
	int nRow(0); int nCol(0);
	int arFlagRow[4] = { 1, -1, 1, -1 };
	int arFlagCol[4] = { 1, 1, -1, -1 };
	int nVisitCode(0);

	while (nVisitCode == 0)
	{

		m_pQueue->getSize(&nCount);
		while (nCount != 0)
		{
			m_pQueue->dequeue(&nRow, &nCol);
			m_pVisit->setVisitCurrent(nRow, nCol, 1);
			for (int i = 0; i < 4; ++i)
			{
				if (C_MOLD::isSpread(nRow + arFlagRow[i], nCol + arFlagCol[i])
					&& m_pVisit->isVisitNext(nRow + arFlagRow[i], nCol + arFlagCol[i]) == false )
				{
					m_pVisit->setVisitNext(nRow + arFlagRow[i], nCol + arFlagCol[i], 1);
					m_pQueue->enqueue(nRow + arFlagRow[i], nCol + arFlagCol[i]);
				}
			}
			--nCount;
		}
		C_MOLD::showMold();
		
		m_pVisit->compareDatas(&nVisitCode);
		C_MOLD::m_pVisit->updateData();
	}

	if (nVisitCode == 1)
	{
		printf("YES\n");
	}
	else
		printf("NO\n");
}

void C_MOLD::showMold()
{
	int nMaxRow(0);
	int nMaxCol(0);
	m_pVisit->getMaxData(&nMaxRow, &nMaxCol);

	for (int i = 1; i < nMaxRow; ++i)
	{
		for (int j = 1; j < nMaxCol; ++j)
		{
			printf("[%d]", m_pVisit->getNextData(i, j));
		}
		printf("\n");
	}
	printf("-----------------------\n");
}


