// Routing_Add_Dlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "DC_ARP_7.h"
#include "Routing_Add_Dlg.h"
#include "afxdialogex.h"
#include "IpLayer.h"

// Routing_Add_Dlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(Routing_Add_Dlg, CDialogEx)

Routing_Add_Dlg::Routing_Add_Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Routing_Add_Dlg::IDD, pParent)
{

}

Routing_Add_Dlg::~Routing_Add_Dlg()
{

}

void Routing_Add_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, Destination, dst_IP);
	DDX_Control(pDX, Netmask, netmask_IP);
	DDX_Control(pDX, Gateway, Gateway_IP);
	DDX_Check(pDX, c_up, check_up);
	DDX_Check(pDX, c_gateway, check_gateway);
	DDX_Check(pDX, c_host, check_host);
	DDX_Control(pDX, e_metric, metric_hop);
}
BOOL Routing_Add_Dlg::OnInitDialog(){

	CDialogEx::OnInitDialog();

	dst_IP.SetWindowText("192.168.0.0");
	netmask_IP.SetWindowText("255.255.255.0");
	Gateway_IP.SetWindowText("연결됨");


	return TRUE;
}

BEGIN_MESSAGE_MAP(Routing_Add_Dlg, CDialogEx)
	ON_BN_CLICKED(add_Route_Table, &Routing_Add_Dlg::OnBnClickedaddRouteTable)

END_MESSAGE_MAP()


// Routing_Add_Dlg 메시지 처리기입니다.


void Routing_Add_Dlg::OnBnClickedaddRouteTable()
{

	CDialogEx::OnOK();
}


