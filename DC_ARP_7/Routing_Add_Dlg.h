#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "pcap.h"
#include "ntddndis.h"
#include "packet32.h"


// Routing_Add_Dlg 대화 상자입니다.

class Routing_Add_Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(Routing_Add_Dlg)

public:
	Routing_Add_Dlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Routing_Add_Dlg();
	LPMAC_ADDR m_Addr[MAX_ADAPTER_INFO];
	unsigned char* IpAddrStoN(char* IpString);
	char* MacAddrNtoS(unsigned char *MAC);
	void GetMacAddr();
// 대화 상자 데이터입니다.
	enum { IDD = Routing_AddDlg };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
