#pragma once
#include "afxwin.h"


// YexlSUipDlg �Ի���

class YexlSUipDlg : public CDialogEx
{
	DECLARE_DYNAMIC(YexlSUipDlg)

public:
	YexlSUipDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~YexlSUipDlg();

// �Ի�������
	enum { IDD = IDD_SUIP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// Ҷ�����suip���
	CStatic m_oSu;
	// ��ʡ��Ĳ�����ӿؼ�
	CStatic m_add;
	// ���������Ҷ������λ�֮��
	CButton m_btn;
	afx_msg void OnBnClickedStart();
};
