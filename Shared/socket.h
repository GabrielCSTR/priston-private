#pragma once

#define WNDPROC_SOCKETACCEPT( window, socket, address )		(SendMessageA( window, WM_SOCKETACCEPT, (WPARAM)socket, (LPARAM)address ))
#define WNDPROC_SOCKETPACKET( window, socketdata, packet )	(PostMessageA( window, WM_SOCKETPACKET, (WPARAM)socketdata, (LPARAM)packet ))
#define WNDPROC_SOCKETCLOSE( window, socketdata )			(PostMessageA( window, WM_SOCKETCLOSE, (WPARAM)socketdata, (LPARAM)NULL ))

class User;
class SocketData;

struct PacketSending
{
	union
	{
		BOOL	  bInUse;
		UINT	  uCount;
	};
	UINT		  uSize;
	BYTE		  baPacket[MAX_PKTSIZ];
};

struct PacketReceiving
{
	BOOL		  bInUse;
	BOOL		  bDelete;
	BYTE		  baPacket[MAX_PKTSIZ];
};

struct PacketReserved
{
public:
	PacketReserved(SocketData * _pSocketData, PacketReceiving * _pPacketReceiving) : pSocketData(_pSocketData), pPacketReceiving(_pPacketReceiving) {}

public:
	SocketData		* pSocketData;
	PacketReceiving	* pPacketReceiving;
};

class SocketData
{
public:
	//Attributes
	SocketData			* pcThis;

	//Status Flags
	bool				  bInUse;
	bool				  bConnecting;
	bool				  bConnected;
	bool				  bReserved;

	//This Socket Information
	SOCKET				  s;
	User				* u;

	//Remote Host
	char				  szIP[32];
	long				  lIP;
	int					  iPort;

	//Time last Received Packet
	DWORD				  dwTimeLastPacketReceived;

	//Receiving Packets
	UINT				  iDefReceivePacket;
	UINT				  iMaxReceivePacket;
	HANDLE				  hReceiveThread;
	HANDLE				  hReceiveThreadSignal;
	CMutex				* pcReceiveMutex;
	UINT				  iReceiveWheel;
	PacketReceiving		* psaPacketReceiving;

	//Sending Packets
	UINT				  iDefSendPacket;
	UINT				  iMaxSendPacket;
	HANDLE				  hSendEvent;
	HANDLE				  hSendThread;
	HANDLE				  hSendThreadSignal;
	CMutex				* pcSendMutex;
	UINT				  iSendWheel;
	UINT				  iSendingWheel;
	PacketSending		* psaPacketSending;
	BOOL				  bBlockSend;
	DWORD				  dwBulkThreadId;
	PacketSending		  sBulkPacket;

	//Encryption
	bool				  bKeySet;
	BYTE				  baKeySet[NUM_ENCKEYS];
	BYTE				  bNextKey;
	int					  iIPIndex;

	//Pinging
	bool				  bPing;
	DWORD				  dwPingTime;
	int					  iPing;

	//Counting
	UINT				  iCountIN;
	UINT				  iCountOUT;
	UINT				  iCountOUTB;

	//Error Handling
	int					  iRecvRet;
	int					  iRecvEC;
	int					  iSendRet;
	int					  iSendEC;

	BOOL				  bKeepAlive;
public:
	//Operations
	SocketData();
	~SocketData();

	void				  Prepare(UINT iMaxSendPacket, UINT iMaxReceivePacket);

	//Initializing
	void				  Init();
	void				  UnInit();

	//Connection
	bool				  Connect(const char * pszIP, int iPort);
	void				  Open(SOCKET s, sockaddr_in * addr);
	void				  Ping(DWORD dwTime);
	void				  Close();

	//Receiving
	PacketReceiving		* FreePacketReceiving();
	void				  FreePacketReceiving(PacketReceiving * pp);

	PacketReceiving		* ReceivePacket();

	//Sending
	PacketSending		* NextPacketSending();
	void				  FreePacketSending(PacketSending * pp);

private:
	//Inner Packet Sending Methods
	BOOL				  Send(BYTE * pbData, UINT uSize);
	BOOL				  SendData(BYTE * pbData, UINT uSize);

	//Automatic Bulk Sending
	PacketSending		* FindAutomaticBulk(UINT uSizeNeeded);

public:
	//Packet Sending Method that should only be used from Sending Thread
	BOOL				  Send(PacketSending * pp);

	//Packet Sending Methods that should be used from outside
	BOOL				  SendPacket(Packet * p, BOOL bEncrypted = FALSE);
	BOOL				  SendPacketBlank(PKTHDR iHeader, BOOL bEncrypted = FALSE);

	//Forced Bulk Sending
	BOOL				  StartBulkSend();
	BOOL				  FlushBulkSend();
	BOOL				  StopBulkSend();

	//Encryption
	void				  SendKeySet(BYTE bObfuscator);
	void				  ReceiveKeySet(PacketKeySet * p);

	BYTE				  GetNextIPIndex();
	BYTE				  ValIPIndex(BYTE iIndex, Packet * p);
	void				  EncryptPacket(Packet * p);
	void				  DecryptPacket(Packet * p);
	bool				  PacketEncrypted(Packet * p);

	//Getters & Setters
	void				  SetPing(int i) { iPing = i; bPing = false; }
	int					  GetPing(DWORD dwTime);
};
