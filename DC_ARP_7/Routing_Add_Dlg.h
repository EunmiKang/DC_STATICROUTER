#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// Routing_Add_Dlg ��ȭ �����Դϴ�.

class Routing_Add_Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(Routing_Add_Dlg)

public:
	Routing_Add_Dlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Routing_Add_Dlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = Routing_AddDlg };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedaddRouteTable();
	CIPAddressCtrl dst_IP;
	CIPAddressCtrl netmask_IP;
	CIPAddressCtrl Gateway_IP;
	CCheckListBox check_up;
	CCheckListBox check_gateway;
	CCheckListBox check_host;
	CComboBox interfaceList;
	CEdit metric_hop;
	afx_msg void OnEnChangemetric();
};
