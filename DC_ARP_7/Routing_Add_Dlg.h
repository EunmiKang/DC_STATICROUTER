#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "pcap.h"
#include "ntddndis.h"
#include "packet32.h"


// Routing_Add_Dlg ��ȭ �����Դϴ�.

class Routing_Add_Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(Routing_Add_Dlg)

public:
	Routing_Add_Dlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Routing_Add_Dlg();
	LPMAC_ADDR m_Addr[MAX_ADAPTER_INFO];
	unsigned char* IpAddrStoN(char* IpString);
	char* MacAddrNtoS(unsigned char *MAC);
	void GetMacAddr();
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
	BOOL check_up;
	BOOL check_gateway;
	BOOL check_host;
	CEdit metric_hop;


	CComboBox interface_List;
};
