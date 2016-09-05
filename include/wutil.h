#ifndef __WUTIL_H__2012_09_06__
#define __WUTIL_H__2012_09_06__

#ifdef __cplusplus
#	define NAMESAPCE_BEGIN(x) namespace x {
#	define NAMESAPCE_END }
#else
#	define NAMESAPCE_BEGIN(x)
#	define NAMESAPCE_END
#endif // C++

//////////////////////////////////////////////////////////////////////////
NAMESAPCE_BEGIN(strsutil)

static BOOL StringToInt(LPCTSTR pszValue, int* pValue)
{
	if (pszValue == NULL || *pszValue == '\0')
		return FALSE;

	int nValue = 0;
	size_t len = _tcslen(pszValue);
	if (len == 1 && *pszValue == '0')
	{	
		*pValue = 0;
		return TRUE;
	}

	nValue = _ttoi(pszValue);
	if (nValue == 0)
		return FALSE;

	*pValue = nValue;
	return TRUE;
}

static BOOL StringToDouble(LPCSTR pszValue, double* pValue)
{
	if (pszValue == NULL || *pszValue == '\0')
		return FALSE;

	double fValue = 0.0;
	size_t len = strlen(pszValue);
	size_t i=0;
	if (pszValue[0] == '-')
		i = 1;

	for (; i<len; ++i)
	{
		if (pszValue[i] == '.')
			continue;
		if (!::isdigit(pszValue[i]))
			return FALSE;
	}

	fValue = atof(pszValue);

	*pValue = fValue;
	return TRUE;
}

static BOOL ValidIPAddress(const char* pszIP)
{
	char szValue[64] = {0};
	strcpy(szValue, pszIP);

	int nDot = 0;
	char sz[20] = {0};
	char* pLast = szValue;
	char* pDot = strchr(pLast, '.');
	if (pDot == NULL)
		return FALSE;

	while (1)
	{
		memset(sz, 0, sizeof(sz));
		if (pDot == NULL)
		{
			strcpy(sz, pLast);
		}
		else
		{
			++nDot;
			if (nDot > 3)
				return FALSE;

			strncpy(sz, pLast, pDot - pLast);
		}

		size_t nLen = strlen(sz);
		if (nLen == 0 || nLen > 3)
			return FALSE;

		for (size_t i=0; i<nLen; ++i)
		{
			if (!::isdigit(sz[i]))
				return FALSE;
		}

		int val = atoi(sz);
		if (val > 255 || val < 0)
			return FALSE;

		if (nDot == 1)					
		{
			if (val == 0)
				return FALSE;
		}

		if (pDot == NULL)
			break;

		++pDot;
		if (pDot == NULL)
			break;

		pLast = pDot;
		pDot = strchr(pDot, '.');
	}

	if (nDot != 3)
		return FALSE;

	return TRUE;
}

// �滻�ַ������ִ�Сд
static void StringReplaceCh(LPTSTR src, TCHAR find, TCHAR rep)
{
	if (src == NULL || *src == '\0' || find == rep)
		return;

	LPTSTR p = _tcschr(src, find); // �ҵ���һ���ַ�
	while (p != NULL)
	{
		if (rep == '\0')
		{
			// ����滻���ַ��ǽ�����
			// ��������ַ���ǰ��
			LPTSTR tp = p;
			while (*tp != '\0')
			{
				*tp = *(tp+1);
				++tp;
			}
		}
		else
		{
			*p = rep;
			++p;
		}

		p = _tcschr(p, find);
	}
}

// �滻�ַ��������ִ�Сд
static void StringReplaceStr(LPTSTR src, LPCTSTR find, LPCTSTR rep)
{
	if (src == NULL || *src == '\0' 
		|| find == NULL || *find == '\0' 
		|| rep == NULL
		|| _tcscmp(find, rep) == 0)
		return;
	
	size_t i;
	size_t nFindLen = _tcslen(find);
	size_t nRepLen = _tcslen(rep);
	LPCTSTR prep;
	LPTSTR pdst; 
	LPTSTR p0,p;
	LPTSTR pfind = _tcsstr(src, find); // ���ҵ��ĵ�һ���ַ�
	LPTSTR pSrcEnd = _tcschr(src, '\0'); // Դ��ĩβ
	size_t nDiff; // ���Һ��滻�Ĵ����Ȳ�
	BOOL bRepLen; // �Ƿ����滻�Ĵ��Ȳ��ҵĴ�Ҫ��

	if (nFindLen < nRepLen)
	{
		bRepLen = TRUE;
		nDiff = nRepLen - nFindLen;
	}
	else
	{
		bRepLen = FALSE;
		nDiff = nFindLen - nRepLen;
	}

	while (pfind != NULL)
	{
		pdst = pfind;
		prep = rep;

		if (bRepLen)
		{
			// ���ҵĴ�����С���滻�ĳ���
			// ��ʱ����Ҫ����Դ�ַ��������ˣ����Դ�������Դ�ַ�������Ҫ�㹻��
			// �Ȱ��滻�ַ�����Ĵ��Ƶ����棬�����㹻�Ŀռ���滻�Ĵ�
			p0 = pdst+nFindLen;
			p = pSrcEnd;
			pdst = p+nDiff;

			while (p >= p0)
			{
				*pdst = *p;
				--pdst;
				--p;
			}

			// �滻��
			pdst = pfind;
			for (i=0; i<nRepLen; ++i)
			{
				*pdst = *prep;
				++pdst;
				++prep;
			}

			pSrcEnd += nDiff;
		}
		else
		{
			// ���ҵĴ����ȴ��ڵ����滻�ĳ���
			// ���滻
			for (i=0; i<nRepLen; ++i)
			{
				*pdst = *prep;
				++pdst;
				++prep;
			}

			// �Ѻ���Ĵ��Ƶ�ǰ��
			if (nDiff > 0)
			{
				p = pdst+nDiff;
				while (1)
				{
					*pdst = *p;
					if (*pdst == '\0')
						break;

					++pdst;
					++p;
				}

				pSrcEnd -= nDiff;
			}
		}

		pfind += nFindLen;
		if (pfind >= pSrcEnd)
			break; // �������ֻ������ڲ��ҵĴ����ȱ��滻�Ĵ�����Ҫ��Ҳ����������

		pfind = _tcsstr(pfind, find);
	}
}

// ���ܣ��Ƴ�ǰ�����Ŀո񣬲����Ƴ��м�Ŀո�
static void StringTrim(LPTSTR src)
{
	if (src == NULL || *src == '\0')
		return;

	TCHAR space = ' '; // �ո��

	// ���Ƴ�����Ŀո�
	LPTSTR p = _tcschr(src, '\0');
	--p;
	while (p != src)
	{
		if (*p != space)
		{
			++p;
			*p = '\0';
			break;
		}
		--p;
	}

	// ���Ƴ�ǰ��Ŀո�
	size_t n = 0; // ͳ��ǰ��Ŀո�����
	p = src;
	while (*p == space && *p != '\0')
	{
		++n;
		++p;
	}

	// ��������ַ���ǰ��
	if (n == 0)
		return;

	LPTSTR tp;
	p = src;
	tp = p+n;
	while (1)
	{
		*p = *tp;
		if (*tp == '\0')
			break;

		++tp;
		++p;
	}
}

// ���ܣ���ȡ�ļ���׺��
static BOOL GetFileExtention(LPCTSTR pszFileName, LPTSTR pszFileExt)
{
	if (pszFileName == NULL || *pszFileName == '\0')
		return FALSE;

	size_t nLen = _tcslen(pszFileName);
	LPCTSTR p = pszFileName + nLen;
	for (size_t i=0; i<nLen; ++i,--p)
	{
		if (*p == '.') // �ҵ����һ���ַ�'.'
		{
			++p;
			_tcscpy(pszFileExt, p);
			return TRUE;
		}
	}

	return FALSE;
}

// ���ܣ���ȡ�ļ�����������׺��
static BOOL GetFileName(LPTSTR pszDst, LPCTSTR pszSrc)
{
	if (pszSrc == NULL || *pszSrc == '\0')
		return FALSE;

	BOOL bPath = FALSE; // �Ƿ���·��
	size_t nLen = _tcslen(pszSrc);
	LPCTSTR p = pszSrc + nLen - 1;
	if (*p == '\\')
		return FALSE; // û���ļ�����ֻ�Ǹ�Ŀ¼

	--p;
	for (size_t i=0; i<nLen; ++i,--p)
	{
		if (*p == '\\') // �ҵ����һ���ַ�'\'
		{
			++p;
			bPath = TRUE;
			break;
		}
	}

	if (!bPath)
	{
		// ֻ���ļ���
		p = pszSrc;
	}

	_tcscpy(pszDst, p);
	return TRUE;
}


// ���ܣ���ȡ�ļ�������������׺��
static BOOL GetFileNameWithoutExtention(LPTSTR pszDst, LPCTSTR pszSrc)
{
	if (pszSrc == NULL || *pszSrc == '\0')
		return FALSE;

	BOOL bPath = FALSE; // �Ƿ���·��
	size_t nLen = _tcslen(pszSrc);
	LPCTSTR p = pszSrc + nLen - 1;
	if (*p == '\\')
		return FALSE; // û���ļ�����ֻ�Ǹ�Ŀ¼

	--p;
	for (size_t i=0; i<nLen; ++i,--p)
	{
		if (*p == '\\') // �ҵ����һ���ַ�'\'
		{
			++p;
			bPath = TRUE;
			break;
		}
	}

	if (!bPath)
	{
		// ֻ���ļ���
		p = pszSrc;
	}

	// �Ӻ���ǰ�ҵ�һ����
	LPCTSTR p1 = p + _tcslen(p);
	while (p1 > p)
	{
		--p1;
		if (*p1 == '.')
			break;
	}
	
	LPTSTR p2 = pszDst;
	nLen = p1 - p;
	_tcsncpy(p2, p, nLen);
	p2 += nLen;
	*p2 = '\0';

	return TRUE;
}

// ���ܣ�����ַ�������������������NULL���ߵ��Ĳ�������0�����Ը��ݷ���ֵ��ȡʵ����Ҫ�Ĵ�С
// ������pszSrc - Ҫ��ֵ��ַ���
//       szSeps - ��ֵķָ������飬ֻҪ������һ���ָ���һ�����ɲ��
//       pszDstBuf - ���֮����ַ������黺�棬ÿ��֮����һ������������������������������Ϊ������־
//       uSize - �����ַ���С
// ���أ�����ɹ�����ʵ���ַ�����С��������������
//       ������Ļ����СС��ʵ����Ҫ�Ĵ�С�򷵻�ʵ����Ҫ���ַ�����С��������������
//       ���ʧ�ܷ���0
static UINT SplitString(LPCTSTR pszSrc, LPCTSTR pszSeps, LPTSTR pszDstBuf, UINT uSize)
{
	if (pszSrc == NULL 
		|| *pszSrc == '\0'
		|| pszSeps == NULL)
	{	
		return 0;
	}

#define FindSpecifiedCh(chs/*�����ַ�����*/,\
	fchs/*ָ�������ַ����飬ֻҪ�ҵ�����һ���ͷ���*/,\
	p/*ָ���ҵ����ַ�ָ��*/,\
	i/*ָ���ҵ����ַ�����*/) \
	{\
		p = chs;\
		i = 0;\
		while (1)\
		{\
			if (*p == '\0')\
			{\
				p = NULL;\
				break;\
			}\
			\
			if (_tcschr(fchs, *p))\
				break;\
			\
			++p;\
			++i;\
		}\
	}

	int nSize = 0; // ʵ����Ҫ�Ļ����С
	int nBufferSize = uSize; // ����Ļ���Ĵ�С
	LPTSTR pBuffer = pszDstBuf; // �����ж�
	LPTSTR pBufferTemp = pBuffer; // ���ڿ���
	BOOL bNotEnough = FALSE; // �����С����
	int nLastLen = 0;
	LPCTSTR p = NULL;
	LPCTSTR p0 = pszSrc;

	if (pBuffer == NULL)
		bNotEnough = TRUE;

	// �ɲ��ñ�ͳ�ƴ�С�߿���
	// ��ÿ��ѭ������Ҫ�ж�һ�鴫��Ļ����Ƿ��㹻
	// ͳ��ʵ����Ҫ���ַ���С
	while (1)
	{
		FindSpecifiedCh(p0, pszSeps, p, nLastLen);

		if (nLastLen > 0)
		{
			nSize += nLastLen+1;

			if (!bNotEnough)
			{
				nBufferSize -= nLastLen+1;
				if (nBufferSize > 0)
				{
					_tcsncpy(pBufferTemp, p0, nLastLen);
					pBufferTemp += nLastLen;
					// ÿһ������������һ��������
					*pBufferTemp = '\0';
					++pBufferTemp;
				}
				else
				{
					*pBufferTemp = '\0';
					bNotEnough = TRUE; // ���治��
				}
			}
		}

		if (p == NULL)
		{
			break;
		}
		else
		{
			p0 = ++p;
		}
	}
	// ������һ��������
	++nSize;
	if (!bNotEnough)
	{
		if (nBufferSize >= 0)
		{
			*pBufferTemp = '\0';
		}
	}

	// Ҳ�ɲ�����ͳ�ƴ�С�󿽱�
	// �������ֵ��ַ��������ر���ʱ��Ͳ��ʺ���

	// �������Ļ���ָ��Ϊ�ջ��ߴ�С������
	// ����ʵ����Ҫ�Ĵ�С
	return nSize;
}
NAMESAPCE_END //strutil

//////////////////////////////////////////////////////////////////////////
NAMESAPCE_BEGIN(timesutil)

// to - since
static LONGLONG GetTotalMilliSeconds(const SYSTEMTIME* to, const SYSTEMTIME* since)
{
	// The FILETIME structure is a 64-bit value representing the number of 
	// 100-nanosecond intervals since January 1, 1601 (UTC).
	// FILETIME ��32λ�����
	FILETIME ftTo = {0, 0};
	FILETIME ftSince = {0, 0};
	// LARGE_INTEGER ��64λ�����
	LARGE_INTEGER timeTo, timeSince;

	// SYSTEMTIME - FILETIME
	SystemTimeToFileTime(to, &ftTo);
	SystemTimeToFileTime(since, &ftSince);

	// FILETIME - LARGE_INTEGER
	timeTo.LowPart = ftTo.dwLowDateTime;
	timeTo.HighPart = ftTo.dwHighDateTime;

	timeSince.LowPart = ftSince.dwLowDateTime;
	timeSince.HighPart = ftSince.dwHighDateTime;

	LONGLONG uTimes = (timeTo.QuadPart - timeSince.QuadPart)/10000; // ����

	return uTimes;
}

// OLE �Զ�������ʵ��Ϊ��ȷ��������
// ����������Ϊ 1899 �� 12 �� 30 ��֮ǰ��֮�����������С�����ֱ�ʾ�� 24 �������ʱ�䡣
static double GetOleDate(const SYSTEMTIME* pSysTime)
{
	double dt = 0;
	SYSTEMTIME stInter = {0};
	stInter.wYear = 1899;
	stInter.wMonth = 12;
	stInter.wDayOfWeek = 6;
	stInter.wDay = 30;
	
	int nOneDayMilliSecs = 86400000; // һ���ܺ�����
	LONGLONG nTotalMilliSecs = timesutil::GetTotalMilliSeconds(pSysTime, &stInter);
	int nDay = (int)(nTotalMilliSecs / nOneDayMilliSecs); // ��������
	double fDay = (double)(nTotalMilliSecs % nOneDayMilliSecs)/ nOneDayMilliSecs; // ���㲻��һ�첿��

	dt = nDay + fDay;
	return dt;
}
NAMESAPCE_END //timeutil

//////////////////////////////////////////////////////////////////////////
NAMESAPCE_BEGIN(filesutil)

// ��ȡ����ʣ��ռ䣨��λ��M��
static BOOL GetDiskFreeSpaceInMegabytes(TCHAR cDiskName, DWORD* pTotalNumberOfFreeMegabytes)
{
	BOOL fResult;
	TCHAR szDrive[4];
	DWORD dwSectPerClust,  // ÿ���ж��ٸ�����
		dwBytesPerSect,  // ÿ�����ж����ֽ�
		dwFreeClusters,  // ʣ���
		dwTotalClusters; // ������

	_stprintf(szDrive, _T("%c:\\"), cDiskName);

	fResult = ::GetDiskFreeSpace(szDrive, 
		&dwSectPerClust,
		&dwBytesPerSect,
		&dwFreeClusters, 
		&dwTotalClusters);

	// Process GetDiskFreeSpace results.
	if(fResult) 
	{
		__int64 i64FreeBytes = (__int64)dwFreeClusters*dwSectPerClust*dwBytesPerSect;
		*pTotalNumberOfFreeMegabytes = (DWORD)(i64FreeBytes/1048576);
	}

	return fResult;
}
// ��ȡ�����ܿռ䣨��λ��M��
static BOOL GetDiskTotalSpaceInMegabytes(TCHAR cDiskName, DWORD* pTotalNumberOfTotalMegabytes)
{
	BOOL fResult;
	TCHAR szDrive[4];
	DWORD dwSectPerClust,  // ÿ���ж��ٸ�����
		dwBytesPerSect,  // ÿ�����ж����ֽ�
		dwFreeClusters,  // ʣ���
		dwTotalClusters; // ������

	_stprintf(szDrive, _T("%c:\\"), cDiskName);

	fResult = ::GetDiskFreeSpace(szDrive, 
		&dwSectPerClust,
		&dwBytesPerSect,
		&dwFreeClusters, 
		&dwTotalClusters);

	// Process GetDiskFreeSpace results.
	if(fResult) 
	{
		__int64 i64TotalBytes = (__int64)dwTotalClusters*dwSectPerClust*dwBytesPerSect;
		*pTotalNumberOfTotalMegabytes = (DWORD)(i64TotalBytes/1048576);
	}

	return fResult;
}

// ���ܣ���ȡ��ǰ����ӳ���ļ����ڵ�·��
// ������pszPathBuffer-��ȡ·������
//		 nSize-·������(�ַ���)
// ���أ�����ɹ����ص�ǰ·�����ַ�������������������
//		 ���򷵻ص�ǰ·������Ҫ���ַ����ȣ�����������
static int GetCurrentPath(LPTSTR pszPathBuffer, int nSize)
{
	TCHAR path[_MAX_PATH];
	TCHAR drv[_MAX_DRIVE];
	TCHAR dir[_MAX_DIR];

	GetModuleFileName(NULL, path, _MAX_PATH);
	_tsplitpath(path, drv, dir, NULL, NULL);
	_tmakepath(path, drv, dir, NULL,NULL);

	int nLen = (int)_tcslen(path);
	if (pszPathBuffer != NULL && nSize > nLen)
		_tcscpy(pszPathBuffer, path);
	else
		++nLen;

	return nLen;
}

// ���ܣ������ް�ȫ����Ŀ¼������ָ��Ŀ¼������
// ˵��: ����ָ���������·�������ʹ�õ�ǰӳ��Ŀ¼
// ������pszDir-ָ��Ҫ������Ŀ¼
// ���أ�TRUE-�����ɹ��� FALSE-����ʧ��
static BOOL CreateSimpleDirectory(LPCTSTR pszDir)
{
	TCHAR cBackslash = '\\';
	TCHAR cSlash = '/';
	LPTSTR p = NULL;
	size_t len = 0;
	TCHAR szDir[MAX_PATH];
	_tcscpy(szDir, pszDir);

	// �����̷�
	p = _tcschr(szDir, ':');
	if (p == NULL)
	{
		// ���·��
		len = GetCurrentPath(szDir, MAX_PATH);
		int offset = 0;
		if (*pszDir == cBackslash || *pszDir == cSlash)
			++offset;
		_tcscat(szDir, pszDir+offset);
	}

	// ����'/'���滻��'\'
	p = _tcschr(szDir+len, cSlash); // �ҵ���һ���ַ�
	while (p != NULL)
	{
		*p = cBackslash;
		++p;

		p = _tcschr(p, cSlash);
	}

	BOOL fCheck = TRUE; // ���Ŀ¼�Ƿ����
	BOOL fCreate = TRUE; // �Ƿ���Ҫ����Ŀ¼

	// ĩβ����'\'
	len = _tcslen(szDir);
	p = szDir + (len-1);
	if (*p != cBackslash)
	{	
		*(++p) = cBackslash;
		*(++p) = '\0';
	}

	p = _tcschr(szDir, cBackslash); // ���ҵ�һ����Ҳ�����̷�
	if (p == NULL)
		return TRUE;

	p = _tcschr(++p, cBackslash); // ���ҵڶ������ӵڶ�����ʼ

	while (p != NULL)
	{
		// ��ʱ��ȡ����Ŀ¼
		*p = '\0';
		// ��ǰ��Ŀ¼�������򴴽�
		fCreate = TRUE; // ������Ҫ����
		if (fCheck)
		{
			if ( _taccess(szDir, 0) != 0)
				fCheck = FALSE; // �ü�Ŀ¼�����ڣ�������ȥ�ж��Ӽ�Ŀ¼�Ƿ����
			else
				fCreate = FALSE; // �ü�Ŀ¼�Ѿ�����
		}
		if (fCreate)
		{
			if (!::CreateDirectory(szDir, NULL))
				return FALSE; // �ü�Ŀ¼����ʧ�ܣ��Ӽ�Ŀ¼�϶���ʧ��
		}

		// �ָ�����Ŀ¼
		*p = cBackslash;

		// ����������һ��
		p = _tcschr(++p, cBackslash);
	}

	return TRUE;
}

NAMESAPCE_END //filesutil

#endif