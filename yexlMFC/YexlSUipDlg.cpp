// YexlSUipDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "YexlMFC.h"
#include "YexlSUipDlg.h"
#include "afxdialogex.h"


// YexlSUipDlg 对话框

IMPLEMENT_DYNAMIC(YexlSUipDlg, CDialogEx)

YexlSUipDlg::YexlSUipDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(YexlSUipDlg::IDD, pParent)
{

}

YexlSUipDlg::~YexlSUipDlg()
{
}

void YexlSUipDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_OSU, m_oSu);
	DDX_Control(pDX, IDC_STATIC_ADD, m_add);
	DDX_Control(pDX, IDC_START, m_btn);
}


BEGIN_MESSAGE_MAP(YexlSUipDlg, CDialogEx)
	ON_BN_CLICKED(IDC_START, &YexlSUipDlg::OnBnClickedStart)
END_MESSAGE_MAP()


// YexlSUipDlg 消息处理程序


void YexlSUipDlg::OnBnClickedStart()
{
	// TODO:  在此添加控件通知处理程序代码
	CWnd *pParent = GetDlgItem(IDC_STATIC_ADD);
	int space = 15;
	int move = 50;
	int ID = 777;
	for (int i = 0; i < 2; ++i)
	{
		CEdit *pEdit = new CEdit;
		pEdit->Create(WS_CHILD | WS_VISIBLE | WS_BORDER, 
			{ 0, space + i * move, 50, move * (i +1) }, pParent, ++ID);
	}
}
