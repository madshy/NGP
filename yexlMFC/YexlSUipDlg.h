#pragma once
#include "afxwin.h"


// YexlSUipDlg 对话框

class YexlSUipDlg : public CDialogEx
{
	DECLARE_DYNAMIC(YexlSUipDlg)

public:
	YexlSUipDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~YexlSUipDlg();

// 对话框数据
	enum { IDD = IDD_SUIP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 叶旭龄的suip输出
	CStatic m_oSu;
	// 麻省洋的测试添加控件
	CStatic m_add;
	// 点击开启与叶旭龄的梦幻之旅
	CButton m_btn;
	afx_msg void OnBnClickedStart();
};
