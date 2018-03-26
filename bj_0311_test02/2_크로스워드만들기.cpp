/*
1.입력으로 A B단어가 주어진다. 각각은 최대 30대문자알파벳이다.
	1.1 A는 가로, B는 세로이고, 한 단어를 공유한다.(공유 단어가 여러개면 가장 빠른거?)
2.A크기 * B크기 만큼의 배열을 만들고, 연결시킨 것을 시각화 해서 출력한다.
---------
str[30 + 1], str[30 + 1]

str1, str2에서 공유되는 알파벳들을 찾는다.[A~Z]
이들중 가장 먼저 나오는 것의 위치를 str1, str2에서 각각 찾아서 공유점을 찾는다.

*/

#include <stdio.h>
#include <string.h>

class C_WORD
{
private:
	char *m_pWord;
	int m_nLength;
public:
	C_WORD();
	C_WORD(const C_WORD &) = delete;
	const C_WORD& operator =(const C_WORD&) = delete;
	~C_WORD();
public:
	void initialize(const char *pSrc,int nLength);
	void release();
public:
	int getWordLength();
	char getAlphabet(int nPosition);
	bool isIncludedChar(char nTarget);
public:
	void getCharPosition(char nTarget, int *pPosition);
};

class C_CROSSWORD
{
private:
	char **m_ppMap;
	int m_nRowSize;
	int m_nColSize;
public:
	C_CROSSWORD();
	C_CROSSWORD(const C_CROSSWORD &) = delete;
	const C_CROSSWORD& operator =(const C_CROSSWORD &) = delete;
	~C_CROSSWORD();
public:
	void initialize(int nRowSize, int nColSize);
	void release();
public:
	void setData(int nRow, int nCol, char chData);
	void printCrossWord();
};

int main()
{
	C_WORD cWord1;
	C_WORD cWord2;
	C_CROSSWORD cCrossWord;

	char arData[30 + 1]{};
	int nLengthData(0);
	char chData('\0');

	char chSharedChar('\0');
	int nTargetRow(0);
	int nTargetCol(0);

	freopen("input.txt", "r", stdin);
	//
	scanf("%s", arData);
	nLengthData = strlen(arData);
	cWord1.initialize(arData, nLengthData);

	scanf("%s", arData);
	nLengthData = strlen(arData);
	cWord2.initialize(arData, nLengthData);
	//

	nLengthData = cWord1.getWordLength();
	for (int i = 0; i < nLengthData; ++i)
	{
		chData = cWord1.getAlphabet(i);
		if (chData >= 'A' && chData <= 'Z')
		{
			if (cWord2.isIncludedChar(chData))
			{
				chSharedChar = chData;
				break;
			}
		}
		else
			printf("error\n");
	}

	cWord1.getCharPosition(chSharedChar, &nTargetCol);
	cWord2.getCharPosition(chSharedChar, &nTargetRow);
	//
	cCrossWord.initialize(cWord2.getWordLength(), cWord1.getWordLength());
	nLengthData = 0;

	nLengthData = cWord1.getWordLength();
	for (int i = 0; i < nLengthData; ++i)
	{
		cCrossWord.setData(nTargetRow, i, cWord1.getAlphabet(i));
	}

	nLengthData = cWord2.getWordLength();
	for (int i = 0; i < nLengthData; ++i)
	{
		cCrossWord.setData(i, nTargetCol, cWord2.getAlphabet(i));
	}

	cCrossWord.printCrossWord();

	cWord1.release();
	cWord2.release();
	cCrossWord.release();

	return 0;
}

C_WORD::C_WORD()
	: m_nLength(0), m_pWord(nullptr)
{
}

C_WORD::~C_WORD()
{
}

void C_WORD::initialize(const char * pSrc, int nLength)
{
	m_nLength = nLength;
	m_pWord = new char[m_nLength] {};
	for (int i = 0; i < m_nLength; ++i)
	{
		m_pWord[i] = pSrc[i];
	}
}

void C_WORD::release()
{
	delete[] m_pWord;
	m_pWord = nullptr;
}

int C_WORD::getWordLength()
{
	return m_nLength;
}

char C_WORD::getAlphabet(int nPosition)
{
	return m_pWord[nPosition];
}

bool C_WORD::isIncludedChar(char nTarget)
{
	for (int i = 0; i < m_nLength; ++i)
	{
		if (m_pWord[i] == nTarget)
		{
			return true;
		}
	}
	return false;
}

void C_WORD::getCharPosition(char nTarget, int *pPosition)
{
	char chCompare('\0');
	for (int i = 0; i < m_nLength; ++i)
	{
		chCompare = C_WORD::getAlphabet(i);
		if (chCompare == nTarget)
		{
			*pPosition = i;
			return;
		}
	}
}

C_CROSSWORD::C_CROSSWORD()
	: m_ppMap(nullptr), m_nRowSize(0), m_nColSize(0)
{
}

C_CROSSWORD::~C_CROSSWORD()
{
}

void C_CROSSWORD::initialize(int nRowSize, int nColSize)
{
	m_nRowSize = nRowSize;
	m_nColSize = nColSize;

	m_ppMap = new char*[m_nRowSize] {};
	for (int i = 0; i < m_nRowSize; ++i)
	{
		m_ppMap[i] = new char[m_nColSize] {};
	}

	for (int i = 0; i < m_nRowSize; ++i)
	{
		for (int j = 0; j < m_nColSize; ++j)
		{
			m_ppMap[i][j] = '.';
		}
	}

}

void C_CROSSWORD::release()
{
	for (int i = 0; i < m_nRowSize; ++i)
	{
		delete[] m_ppMap[i];
		m_ppMap[i] = nullptr;
	}
	delete[] m_ppMap;
	m_ppMap = nullptr;
}

void C_CROSSWORD::setData(int nRow, int nCol, char chData)
{
	m_ppMap[nRow][nCol] = chData;
}

void C_CROSSWORD::printCrossWord()
{
	for (int i = 0; i < m_nRowSize; ++i)
	{
		for (int j = 0; j < m_nColSize; ++j)
		{
			printf("%c", m_ppMap[i][j]);
		}
		printf("\n");
	}
}
