// Routing_Add_Dlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "DC_ARP_7.h"
#include "Routing_Add_Dlg.h"
#include "afxdialogex.h"
#include "IpLayer.h"
#include "Packet32.h"
#include "afxmt.h"

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
	DDX_Control(pDX, interfaceList, interface_List);
}
BOOL Routing_Add_Dlg::OnInitDialog(){

	CDialogEx::OnInitDialog();

	dst_IP.SetWindowText("192.168.0.0");
	netmask_IP.SetWindowText("255.255.255.0");
	Gateway_IP.SetWindowText("연결됨");

	UpdateData(TRUE);
	
	GetMacAddr();

	return TRUE;
}

void Routing_Add_Dlg::GetMacAddr(){
	
	pcap_if_t *alldevs;
    pcap_if_t *d;
    int i=0;
    char errbuf[PCAP_ERRBUF_SIZE];
    
    /* Retrieve the device list from the local machine */
    if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL /* auth is not needed */, &alldevs, errbuf) == -1)
    {
        fprintf(stderr,"Error in pcap_findalldevs_ex: %s\n", errbuf);
        exit(1);
    }
    
    /* Print the list */
    for(d= alldevs; d != NULL; d= d->next)
    {
        if (d->description)
			interface_List.AddString(d->description);
        else
            printf(" (No description available)\n");
    }
    
    if (i == 0)
    {
        printf("\nNo interfaces found! Make sure WinPcap is installed.\n");
        return;
    }

    /* We don't need any more the device list. Free it */
    pcap_freealldevs(alldevs);
			interface_List.AddString(m_Addr[i]->MacAddrDescrip);

	
}

unsigned char* Routing_Add_Dlg::IpAddrStoN(char* IpString)
{
	unsigned char *result=(unsigned char*)malloc(sizeof(char)*4);	
	char *temp=IpString;
	char ip[4];
	int n=0;	
	
	while(*temp!='\0'){	
		while(*temp != '.' && *temp !='\0'){	//'.'단위로 나누어서 문자를 10진수숫자로 바꾼다.
			ip[n++]= *temp;						//숫자로 바뀐값을 변수에 저장해서 리턴
			temp++;
		}
		ip[n]='\0';		
		n=0;
		*result=(unsigned char)strtol(ip,NULL,10);
		result++;
		if(*temp=='\0'){
			result-=4;							//4바이트 
			return result;
		}
		temp++;
	}
	AfxMessageBox("IP주소 바꾸다가 에러 발생-_-;");
	return NULL;
}

char* Routing_Add_Dlg::MacAddrNtoS(unsigned char *MAC)
{
	char *Result=(char*)malloc(sizeof(char)*20);
	sprintf(Result,"%.2X:%.2X:%.2X:%.2X:%.2X:%.2X",MAC[0],MAC[1],MAC[2],MAC[3],MAC[4],MAC[5]);
	return Result;
}
BEGIN_MESSAGE_MAP(Routing_Add_Dlg, CDialogEx)
	ON_BN_CLICKED(add_Route_Table, &Routing_Add_Dlg::OnBnClickedaddRouteTable)

END_MESSAGE_MAP()


// Routing_Add_Dlg 메시지 처리기입니다.


void Routing_Add_Dlg::OnBnClickedaddRouteTable()
{

	CDialogEx::OnOK();
}


