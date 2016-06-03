#pragma once
#include "baselayer.h"
class CIpLayer :
	public CBaseLayer
{
public:

	typedef struct _IP_HEADER 
	{
		unsigned char	ip_version;
		unsigned char	ip_tos;
		unsigned short	ip_len;
		unsigned short	ip_id;
		unsigned short	ip_fragoff;
		unsigned char	ip_ttl;
		unsigned char	ip_proto;
		unsigned short	ip_cksum;
		unsigned char   ip_dst[4];
		unsigned char   ip_src[4];
		unsigned char	*ip_data;
	} IP_HEADER , *PIP_HEADER ;

	IP_HEADER   m_sHeader ;

	typedef struct _STATIC_ROUTING_TABLE{
		unsigned char		destination[4];
		unsigned char		netmask[4];
		unsigned char		gateway[4];
		char				flag[10];
		char				interfaceDevice[200];		
		int					metric;		
	}STATIC_ROUTING_TABLE, *PSTATIC_ROUTING_TABLE;
	
	PSTATIC_ROUTING_TABLE m_routingTable[MAX_STATIC_ROUTING_TABLE];

	void         ResetHeader();
	void         AddRoutingTable(int seq,unsigned char *networkIP , unsigned char *maskIP , unsigned char *gateway, CString checked_flag, CString interfaceName, int metric_num);
	BOOL         Send( unsigned char* ppayload, int nlength , int type);
	BOOL         Receive( unsigned char* ppayload);
	BOOL		 searchingRoutingTable(unsigned char* ipDst,int isARPReply);
	unsigned char* subnetMasking(unsigned char *hostIp);
	unsigned char* getHostNetworkIp(unsigned char *ipDst);
	unsigned char myIp[4];
	unsigned char mySubnetMask[4];
	unsigned char myGateWay[4];
	int routingTableCount;

	CIpLayer(char* pName);
	~CIpLayer(void);
};