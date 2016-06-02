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

	//memcpy(maskedNetIp,subnetMasking(pDatagram->ip_dst),4); //������ IP�� ����ŷ�Ͽ� ��Ʈ��ũ Ip�� ����.

	return searchingRoutingTable(pDatagram->ip_dst);
}

BOOL CIpLayer::searchingRoutingTable(unsigned char* ipDst){
	CARPLayer *arplayer = new CARPLayer("ARPLayer");
	unsigned char* maskedNetIp;
	unsigned char check_ARP[] = "A";
	char flag_g = 'G';

	for(int i = 0; m_routingTable[i]!=NULL;i++){ //�������� ����� ���� ���ǹ�����
		maskedNetIp = subnetMasking(ipDst);
		if(memcmp(m_routingTable[i]->destination,maskedNetIp,4)==0){ // netId�� ��������̺� ���� ��
			if(m_routingTable[i]->flag[1]==flag_g){
				g_nicName = AdapterList[m_routingTable[i]->interfaceDevice[0]]; //������ �´ٸ� �ɲ���
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

void CIpLayer::AddRoutingTable(int seq,unsigned char *networkIP , unsigned char *maskIP , unsigned char *gateway)
{   //�Է¹��� ����� Routing table�� �߰�
	memcpy(m_routingTable[seq]->destination,networkIP,4);
	memcpy(m_routingTable[seq]->destination,maskIP,4);
	memcpy(m_routingTable[seq]->destination,networkIP,4);
}

