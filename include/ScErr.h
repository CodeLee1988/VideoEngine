#ifndef SC_ERR_H
#define SC_ERR_H


//������Ϣ��ʶ
typedef enum
{
	SC_ErrSuccess = 0 ,		//�ɹ�
	SC_ErrNullReturn = 1,		//�շ���
	SC_ErrParamerErr = 2,		//��������
	SC_ErrPathNotFound = 3,		//����·��������
	SC_ErrNotExist = 4,		    //������
	SC_ErrTypeErr = 5,			//���ʹ���
	SC_ErrOpenFileFailed = 6,	//���ļ�ʧ��
	SC_ErrInfoTooLong = 7,		//��Ϣ̫��
	SC_ErrMemoryAlloc = 8,		//�ڴ����ʧ��s
	SC_ErrCreateFailed = 9,		//����ʧ��
	SC_ErrVersionNotSupport = 10,	//��֧�ֵİ汾
	SC_ErrLogicError = 11,		//�߼�����
	SC_ErrCantConnectMediaSource = 12,	//�޷�������ƵԴ
	SC_ErrUnknow = 13,			//δ֪����
	SC_ErrGetFrameFromMSFaile = 14,	//
	SC_ErrFreeFrameFaile = 15,    
	SC_ErrLockAuthen = 16,       
	SC_ErrLockPasswd = 17,      
	SC_ErrTimeOut = 18, //��ʱ
	SC_ErrSendErr = 19,  //���ʹ���
	SC_ErrAlreadyExisted = 20,    //�Ѿ�����
	SC_ErrFULL = 21,			 //����
	SC_ErrRefused = 22,			 //�ܾ�
	Sc_ErrEmpty = 23,			 //�յ�
	SC_ErrMemNotEnough  = 24,//�ڴ治��
	SC_ErrYes = 25,//��
	SC_ErrNo = 26,   //����
	SC_ErrReceiveDataErr = 27,//�������ݴ���
	SC_ErrDataTransErr = 28, //����ת������
	SC_ErrDataOverflow = 29,
	SC_ErrNoResources = 30,  //û����Ҫ����Դ
	SC_ErrUserNamePWDWrong = 31,  //�û�������ʧ��
	SC_ErrUserNoPrivilege = 32,	  //û��Ȩ��
	SC_UnInit = 33,//û�г�ʼ��
	SC_ErrDataBaseErr = 34,            //���ݿ�������ӻ��������
	SC_ErrPrivilegeOccupied = 35,  //Ȩ�ޱ�ռ��
	SC_Err_MergJpg_ReadJpgHearderError = 1000, //��ȡJpegͷʧ�� songj
	SC_Err_MergJpg_ReadJpgTableError   =1001, //������, huffman��һ��
}ScErr;
#define SC_ErrNodeNotExist SC_ErrNotExist


#endif 