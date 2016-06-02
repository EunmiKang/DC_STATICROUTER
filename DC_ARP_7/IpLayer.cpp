#include "StdAfx.h"
#include "IpLayer.h"
#include "ARPLayer.h"


CIpLayer::CIpLayer(char* pName)
   :CBaseLayer( pName )
{
   ResetHeader();
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
	memset(m_routingTable,0,sizeof(m_routingTable));
}
BOOL CIpLayer::Send( unsigned char* ppayload, int nlength , int type)
{
	BOOL bSuccess=FALSE;

	return bSuccess;
}

BOOL CIpLayer::Receive( unsigned char* ppayload)
{
	PIP_HEADER pDatagram = (PIP_HEADER) ppayload;

	//memcpy(maskedNetIp,subnetMasking(pDatagram->ip_dst),4); //목적지 IP를 마스킹하여 네트워크 Ip를 얻어낸다.

	return searchingRoutingTable(pDatagram->ip_dst);
}

BOOL CIpLayer::searchingRoutingTable(unsigned char* ipDst){
	unsigned char* maskedNetIp;

	for(int i = 0; i < sizeof(m_routingTable)/sizeof(m_routingTable[0]);i++){
		
		mySubnetMask[0] = m_routingTable[i]->netmask[0];
		mySubnetMask[1] = m_routingTable[i]->netmask[1];
		mySubnetMask[2] = m_routingTable[i]->netmask[2];
		mySubnetMask[3] = m_routingTable[i]->netmask[3];

		maskedNetIp = subnetMasking(ipDst);
		if(memcmp(m_routingTable[i]->destination,maskedNetIp,4)==0){ // netId가 라우팅테이블에 있을 때
			//if(m_routingTable)
		}else{ //없을 때

		}
	return TRUE;
	}
}

unsigned char* CIpLayer::subnetMasking(unsigned char *hostIp){
	unsigned char result[4];
	result[0] = mySubnetMask[0] & hostIp[0];
	result[1] = mySubnetMask[1] & hostIp[1];
	result[2] = mySubnetMask[2] & hostIp[2];
	result[3] = mySubnetMask[3] & hostIp[3];
	return result;
}

