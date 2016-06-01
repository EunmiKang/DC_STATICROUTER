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
}
BOOL CIpLayer::Send( unsigned char* ppayload, int nlength , int type)
{
	BOOL bSuccess=FALSE;

	return bSuccess;
}

BOOL CIpLayer::Receive( unsigned char* ppayload)
{
	PIP_HEADER pDatagram = (PIP_HEADER) ppayload;
	unsigned char* maskedNetIp;
	//memcpy(maskedNetIp,subnetMasking(pDatagram->ip_dst),4); //목적지 IP를 마스킹하여 네트워크 Ip를 얻어낸다.

	return searchingRoutingTable(pDatagram->ip_dst);
}

BOOL CIpLayer::searchingRoutingTable(unsigned char* ipDst){
	for(int i = 0; i < sizeof(CIpLayer::m_routingTable)/sizeof(CIpLayer::m_routingTable[0]);i++){

	}
	return TRUE;
}

unsigned char* CIpLayer::subnetMasking(unsigned char *hostIp){
	unsigned char result[4];
	result[0] = mySubnetMask[0] & hostIp[0];
	result[1] = mySubnetMask[1] & hostIp[1];
	result[2] = mySubnetMask[2] & hostIp[2];
	result[3] = mySubnetMask[3] & hostIp[3];
	return result;
}