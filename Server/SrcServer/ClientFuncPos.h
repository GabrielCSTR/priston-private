//Ŭ���̾�Ʈ ��� ������ �߰�
int	rsAddClientFuncPos( TRANS_CLIENT_FUNPOS	*lpClentFuncPos );
//Ŭ���̾�Ʈ ��� ������ �Լ� ( ���Ϸ� ���� )
int	rsRecvClientFuncPos( TRANS_CLIENT_FUNPOS	*lpClentFuncPos );
//Ŭ���̾�Ʈ ��� ������ ���
TRANS_CLIENT_FUNPOS *rsGetClientPos( int Version );
//Ŭ���̾�Ʈ ��� ������ ����
int	rsResetClientFuncPos();

//�޸� ýũ�� ����� ��ä�� Ŭ���̾�Ʈ�� ������
int rsSendFuncMemToClient( User *lpPlayInfo , DWORD dwFuncMem , DWORD	dwLen );
//üũ�� ��
int	rsCompClientFuncMem(User *lpPlayInfo , DWORD	dwFunc , DWORD dwChkSum );
//üũ�� ��2
int	rsCompClientFuncMem2(User *lpPlayInfo , DWORD dwFuncCode );
//Ŭ���̾�Ʈ �޸� ýũ ��� ����
int	rsCheckClientFuncMem(User *lpPlayInfo );