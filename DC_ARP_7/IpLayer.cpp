#include "StdAfx.h"
#include "IpLayer.h"
#include "ARPLayer.h"
#include <string.h>

CIpLayer::CIpLayer(char* pName)
   :CBaseLayer( pName )
{
   ResetHeader();
   	for(int i=0;i<MAX_STATIC_ROUTING_TABLE;i++)
		m_routingTable[i]= (STATIC_ROUTING_TABLE*) malloc (sizeof(STATIC_ROUTING_TABLE));
	routingTableCount=0;
}


CIpLayer::~CIpLayer(void)
{
}

void CIpLayer::ResetHeader()
{
	
	memset(m_sHeader.ip_dst,0,6);
	memset(m_sHeader.ip_src,0,6);
	m_sHeader.ip_ttl = 0;
	m_sHeader.ip_proto = 0;
	memset(mySubnetMask,0,4);

	
}
BOOL CIpLayer::Send( unsigned char* ppayload, int nlength , int type)
{
	BOOL bSuccess=FALSE;

	return bSuccess;
}

BOOL CIpLayer::Receive( unsigned char* ppayload)
{
	PIP_HEADER pDatagram = (PIP_HEADER) ppayload;
	return searchingRoutingTable(pDatagram->ip_dst,0);
}

BOOL CIpLayer::searchingRoutingTable(unsigned char* ipDst,int isARPReply){
	CARPLayer *arplayer = new CARPLayer("ARPLayer");

	int l = 0;
	unsigned char maskedNetIp[4];
	unsigned char check_ARP[] = "A";
	char flag_g = 'G';
	if(ipDst[0]==0)
		return FALSE;
	for(int i = 0; i < routingTableCount;i++){ //문제점이 생길수 있음 조건문에서
		for(int j =0 ; j < 4; j++){
			mySubnetMask[j] = m_routingTable[i]->netmask[j];
			maskedNetIp[j] = mySubnetMask[j] & ipDst[j];
		}
		
		if(maskedNetIp[0]==0)
			return FALSE;
		if(maskedNetIp[2]==1) //디버그용 완성되면 지울것.
			return FALSE;
		unsigned char a = maskedNetIp[0];
		unsigned char b =maskedNetIp[1];
		unsigned char c =maskedNetIp[2];
		unsigned char d =maskedNetIp[3];
		if(memcmp(m_routingTable[i]->destination,maskedNetIp,4)==0){ // netId가 라우팅테이블에 있을 때
			if(isARPReply == 1 ){ //arp에서 온거
				return TRUE;
			}
			if(m_routingTable[i]->flag[1]==flag_g){
				int k = m_routingTable[i]->interfaceDevice[0]-48;
				for( l = 0 ; AdapterList[k][l] != '\0'; l++);
					g_nicName = CString(AdapterList[k],l);
				arplayer->setDstIpAddress(m_routingTable[i]->gateway);
				arplayer->Send(check_ARP,0);
				return TRUE;
			}else{
				arplayer->setDstIpAddress(ipDst);
				arplayer->Send(check_ARP,0);
				return TRUE;
			}
		}
	}
	return FALSE;

}

unsigned char* CIpLayer::subnetMasking(unsigned char *hostIp){
	unsigned char result[4];
	result[0] = mySubnetMask[0] & hostIp[0];
	result[1] = mySubnetMask[1] & hostIp[1];
	result[2] = mySubnetMask[2] & hostIp[2];
	result[3] = mySubnetMask[3] & hostIp[3];
	return result;
}

void CIpLayer::AddRoutingTable(int seq,unsigned char *networkIP , unsigned char *maskIP , unsigned char *gateway, CString checked_flag, CString interfaceName, int metric_num)
{   //입력받은 내용들 Routing table에 추가
	memcpy(m_routingTable[seq]->destination,networkIP,4);
	memcpy(m_routingTable[seq]->netmask,maskIP,4);
	memcpy(m_routingTable[seq]->gateway,gateway,4);
	memcpy(m_routingTable[seq]->flag,(LPSTR)(LPCSTR)checked_flag,checked_flag.GetLength());
	memcpy(m_routingTable[seq]->interfaceDevice,(LPSTR)(LPCSTR)interfaceName,interfaceName.GetLength());
	m_routingTable[seq]->metric = metric_num;
	routingTableCount++;
}

