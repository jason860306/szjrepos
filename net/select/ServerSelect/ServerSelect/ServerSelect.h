#ifndef _SERVER_SELECT_H_
#define _SERVER_SELECT_H_

//Disable deprecation warnings
#pragma warning(disable: 4996)

//Buffer Length 
#define MAX_BUFFER_LEN 256

class CClientContext  //To store and manage client related information
{
private:

     int               m_nTotalBytes;
     int               m_nSentBytes;
     SOCKET            m_Socket;  //accepted socket
     char              m_szBuffer[MAX_BUFFER_LEN];
     CClientContext   *m_pNext; //this will be a singly linked list

public:

     //Get/Set calls
     void SetTotalBytes(int n)
     {
          m_nTotalBytes = n;
     }

     int GetTotalBytes()
     {
          return m_nTotalBytes;
     }

     void SetSentBytes(int n)
     {
          m_nSentBytes = n;
     }

     void IncrSentBytes(int n)
     {
          m_nSentBytes += n;
     }

     int GetSentBytes()
     {
          return m_nSentBytes;
     }

     void SetSocket(SOCKET s)
     {
          m_Socket = s;
     }

     SOCKET GetSocket()
     {
          return m_Socket;
     }

     void SetBuffer(char *szBuffer)
     {
          strcpy(m_szBuffer, szBuffer);
     }

     void GetBuffer(char *szBuffer)
     {
          strcpy(szBuffer, m_szBuffer);
     }

     char* GetBuffer()
     {
          return m_szBuffer;
     }

     void ZeroBuffer()
     {
          ZeroMemory(m_szBuffer, MAX_BUFFER_LEN);
     }

     CClientContext* GetNext()
     {
          return m_pNext;
     }

     void SetNext(CClientContext *pNext)
     {
          m_pNext = pNext;
     }

     //Constructor
     CClientContext()
     {
          m_Socket =  SOCKET_ERROR;
          ZeroMemory(m_szBuffer, MAX_BUFFER_LEN);
          m_nTotalBytes = 0;
          m_nSentBytes = 0;
          m_pNext = NULL;
     }

     //destructor
     ~CClientContext()
     {
          closesocket(m_Socket);
     }
};

//Head of the client context singly linked list
CClientContext    *g_pClientContextHead = NULL;

//Global FD Sets
fd_set g_ReadSet, g_WriteSet, g_ExceptSet;

//global functions
void AcceptConnections(SOCKET ListenSocket);
void InitSets(SOCKET ListenSocket);
int GetSocketSpecificError(SOCKET Socket);
CClientContext* GetClientContextHead();
void AddClientContextToList(CClientContext *pClientContext);
CClientContext* DeleteClientContext(CClientContext *pClientContext);

#endif