// Routing_Add_Dlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "DC_ARP_7.h"
#include "Routing_Add_Dlg.h"
#include "afxdialogex.h"
#include "IpLayer.h"
#include "Packet32.h"
#include "afxmt.h"
#include <typeinfo>
// Routing_Add_Dlg ��ȭ �����Դϴ�.

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
	DDX_Control(pDX, interfaceList, interface_List);
}
BOOL Routing_Add_Dlg::OnInitDialog(){

	CDialogEx::OnInitDialog();

	dst_IP.SetWindowText("192.168.0.0");
	netmask_IP.SetWindowText("255.255.255.0");

	UpdateData(TRUE);
	
	GetMacAddr();

	return TRUE;
}

void Routing_Add_Dlg::GetMacAddr(){

    pcap_if_t *d;
    int i=0;
    char errbuf[PCAP_ERRBUF_SIZE];
	char temp[200];
    
    /* Retrieve the device list from the local machine */
    if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &alldevs, errbuf) == -1)
    {
        fprintf(stderr,"Error in pcap_findalldevs_ex: %s\n", errbuf);
        exit(1);
    }
    
    /* Print the list */
    for(d= alldevs; d != NULL; d= d->next)
    {
        if (d->description){
			sprintf(temp,"%d",i++);
			strcat(temp," - ");
			strcat(temp,d->description); 
			interface_List.AddString(temp);
			interface_List.SetCurSel(0);
		}
        else
            printf(" (No description available)\n");
    }
    
    if (i == 0)
    {
        printf("\nNo interfaces found! Make sure WinPcap is installed.\n");
        return;
    }
	g_nicName = alldevs[0].name; //test�ؾ���
    /* We don't need any more the device list. Free it */
    pcap_freealldevs(alldevs);
	i = 0;
	//interface_List.AddString(m_Addr[i]->MacAddrDescrip);

	
}

BEGIN_MESSAGE_MAP(Routing_Add_Dlg, CDialogEx)
	ON_BN_CLICKED(add_Route_Table, &Routing_Add_Dlg::OnBnClickedaddRouteTable)

END_MESSAGE_MAP()


// Routing_Add_Dlg �޽��� ó�����Դϴ�.


void Routing_Add_Dlg::OnBnClickedaddRouteTable()
{
	BYTE nField0 , nField1 , nField2 , nField3;            //IP�� �߶� �����ϱ� ���� �ӽú���
	CString ip_Address;                              //IP �ּ� ��ü�� ���� ����
	dst_IP.GetAddress(nField0 , nField1 ,nField2 , nField3 );         //���Ͻ� ���̾�α׿��� �Է��� ������ �ּҸ� ������ ������ ����
	unsigned char ipAddress[4];

	ipAddress[0] = nField0;                        //���ҵ� ������ �ּҸ� �ϳ��ϳ� �Է��� ��ü���� IP�ּҸ� �ϼ�
	ipAddress[1] = nField1;
	ipAddress[2] = nField2;
	ipAddress[3] = nField3;
	memcpy(net_Ip,ipAddress,4);

	netmask_IP.GetAddress(nField0 , nField1 ,nField2 , nField3 );
	ipAddress[0] = nField0;                        //���ҵ� ������ �ּҸ� �ϳ��ϳ� �Է��� ��ü���� IP�ּҸ� �ϼ�
	ipAddress[1] = nField1;
	ipAddress[2] = nField2;
	ipAddress[3] = nField3;
	memcpy(net_maskIp,ipAddress,4);

	Gateway_IP.GetAddress(nField0 , nField1 ,nField2 , nField3 );
	ipAddress[0] = nField0;                        //���ҵ� ������ �ּҸ� �ϳ��ϳ� �Է��� ��ü���� IP�ּҸ� �ϼ�
	ipAddress[1] = nField1;
	ipAddress[2] = nField2;
	ipAddress[3] = nField3;
	memcpy(gateway,ipAddress,4);
	
	

	CDialogEx::OnOK();
}


