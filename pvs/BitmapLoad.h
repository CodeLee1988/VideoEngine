// weil - 20121010
// ����24λ���ɫλͼ��
#pragma once

class CBitmapLoad
{
public:
	CBitmapLoad();
	~CBitmapLoad();

public:
	BOOL Load(const char* lpszFilePathName);
	BOOL Destroy();
	BOOL Copy(void* _dst) const;
	unsigned char* GetData() const;
	void GetSize(int* pWidth, int* pHeight) const;
	unsigned long GetDataSize() const;

private:
	char m_szFilePathName[MAX_PATH];
	unsigned char* m_pBuffer;
	int m_nWidth;
	int m_nHeight;
	unsigned long m_nSize;
};
