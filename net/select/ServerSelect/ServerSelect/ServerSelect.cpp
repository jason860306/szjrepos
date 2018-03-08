#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <winsock2.h>
#include <vector>

#include "ServerSelect.h"

int main(int argc, char *argv[])
{
     //Validate the input
     if (argc < 2) 
     {
          printf("\nUsage: %s port.", argv[0]);
          goto error;
     }

     // Initialize Winsock
     WSADATA wsaData;

     int nResult;

     nResult = WSAStartup(MAKEWORD(2,2), &wsaData);

     if (NO_ERROR != nResult)
     {
          printf("\nError occurred while executing WSAStartup().");
          return 1; //error
     }
     else
     {
          printf("\nWSAStartup() successful.");
     }

     SOCKET ListenSocket; 
     int    nPortNo;

     struct sockaddr_in ServerAddress;

     //Create a socket
     ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

     if (INVALID_SOCKET == ListenSocket) 
     {
          printf("\nError occurred while opening socket: %ld.", WSAGetLastError());
          goto error;
     }
     else
     {
          printf("\nsocket() successful.");
     }

     //Cleanup and Init with 0 the ServerAddress
     ZeroMemory((char *)&ServerAddress, sizeof(ServerAddress));

     //Port number will be supplied as a commandline argument
     nPortNo = atoi(argv[1]);

     //Fill up the address structure
     ServerAddress.sin_family = AF_INET;
     ServerAddress.sin_addr.s_addr = INADDR_ANY; //WinSock will supply address
     ServerAddress.sin_port = htons(nPortNo);    //comes from commandline

     //Assign local address and port number
     if (SOCKET_ERROR == bind(ListenSocket, (struct sockaddr *) &ServerAddress, sizeof(ServerAddress))) 
     {
          closesocket(ListenSocket);

          printf("\nError occurred while binding.");
          goto error;
     }
     else
     {
          printf("\nbind() successful.");
     }

     //Make the socket a listening socket
     if (SOCKET_ERROR == listen(ListenSocket,SOMAXCONN))
     {
          closesocket(ListenSocket);

          printf("\nError occurred while listening.");
          goto error;
     }
     else
     {
          printf("\nlisten() successful.");
     }

     //This function will take are of multiple clients using select()/accept()
     AcceptConnections(ListenSocket);

     //Close open sockets
     closesocket(ListenSocket);

     //Cleanup Winsock
     WSACleanup();
     return 0; //success

error:
     // Cleanup Winsock
     WSACleanup();
     return 1; //error
}

//Initialize the Sets
void InitSets(SOCKET ListenSocket) 
{
     //Initialize
     FD_ZERO(&g_ReadSet);
     FD_ZERO(&g_WriteSet);
     FD_ZERO(&g_ExceptSet);

     //Assign the ListenSocket to Sets
     FD_SET(ListenSocket, &g_ReadSet);
     FD_SET(ListenSocket, &g_ExceptSet);

     //Iterate the client context list and assign the sockets to Sets
     CClientContext   *pClientContext  = GetClientContextHead();

     while(pClientContext)
     {
          if(pClientContext->GetSentBytes() < pClientContext->GetTotalBytes())
          {
               //We have data to send
               FD_SET(pClientContext->GetSocket(), &g_WriteSet);
          }
          else
          {
               //We can read on this socket
               FD_SET(pClientContext->GetSocket(), &g_ReadSet);
          }

          //Add it to Exception Set
          FD_SET(pClientContext->GetSocket(), &g_ExceptSet); 

          //Move to next node on the list
          pClientContext = pClientContext->GetNext();
     }
}


//This function will loop on while it will manage multiple clients using select()
void AcceptConnections(SOCKET ListenSocket)
{
     while (true)
     {
          InitSets(ListenSocket);

          if (select(0, &g_ReadSet, &g_WriteSet, &g_ExceptSet, 0) > 0) 
          {
               //One of the socket changed state, let's process it.

               //ListenSocket?  Accept the new connection
               if (FD_ISSET(ListenSocket, &g_ReadSet)) 
               {
                    sockaddr_in ClientAddress;
                    int nClientLength = sizeof(ClientAddress);

                    //Accept remote connection attempt from the client
                    SOCKET Socket = accept(ListenSocket, (sockaddr*)&ClientAddress, &nClientLength);

                    if (INVALID_SOCKET == Socket)
                    {
                         printf("\nError occurred while accepting socket: %ld.", GetSocketSpecificError(ListenSocket));
                    }

                    //Display Client's IP
                    printf("\nClient connected from: %s", inet_ntoa(ClientAddress.sin_addr)); 

                    //Making it a non blocking socket
                    u_long nNoBlock = 1;
                    ioctlsocket(Socket, FIONBIO, &nNoBlock);

                    CClientContext   *pClientContext  = new CClientContext;
                    pClientContext->SetSocket(Socket);

                    //Add the client context to the list
                    AddClientContextToList(pClientContext);
               }

               //Error occured for ListenSocket?
               if (FD_ISSET(ListenSocket, &g_ExceptSet)) 
               {
                    printf("\nError occurred while accepting socket: %ld.", GetSocketSpecificError(ListenSocket));
                    continue;
               }

               //Iterate the client context list to see if any of the socket there has changed its state
               CClientContext   *pClientContext  = GetClientContextHead();

               while (pClientContext)
               {
                    //Check in Read Set
                    if (FD_ISSET(pClientContext->GetSocket(), &g_ReadSet))
                    {
                         int nBytes = recv(pClientContext->GetSocket(), pClientContext->GetBuffer(), MAX_BUFFER_LEN, 0);

                         if ((0 == nBytes) || (SOCKET_ERROR == nBytes))
                         {
                              if (0 != nBytes) //Some error occured, client didn't close the connection
                              {
                                   printf("\nError occurred while recieving on the socket: %d.", GetSocketSpecificError(pClientContext->GetSocket()));
                              }

                              //In either case remove the client from list
                              pClientContext = DeleteClientContext(pClientContext);
                              continue;
                         }

                         //Set the buffer
                         pClientContext->SetTotalBytes(nBytes);
                         pClientContext->SetSentBytes(0);

                         printf("\nThe following message was received: %s", pClientContext->GetBuffer());
                    }

                    //Check in Write Set
                    if (FD_ISSET(pClientContext->GetSocket(), &g_WriteSet))
                    {
                         int nBytes = 0;

                         if (0 < (pClientContext->GetTotalBytes() - pClientContext->GetSentBytes()))
                         {
                              nBytes = send(pClientContext->GetSocket(), (pClientContext->GetBuffer() + pClientContext->GetSentBytes()), (pClientContext->GetTotalBytes() - pClientContext->GetSentBytes()), 0);

                              if (SOCKET_ERROR == nBytes)
                              {
                                   printf("\nError occurred while sending on the socket: %d.", GetSocketSpecificError(pClientContext->GetSocket()));

                                   pClientContext = DeleteClientContext(pClientContext);
                                   continue;
                              }
                              if (nBytes == (pClientContext->GetTotalBytes() - pClientContext->GetSentBytes()))
                              {
                                   //We are done sending the data, reset Buffer Size
                                   pClientContext->SetTotalBytes(0);
                                   pClientContext->SetSentBytes(0);
                              }
                              else
                              {
                                   pClientContext->IncrSentBytes(nBytes);
                              }
                         }
                    }

                    //Check in Exception Set
                    if (FD_ISSET(pClientContext->GetSocket(), &g_ExceptSet))
                    {
                         printf("\nError occurred on the socket: %d.", GetSocketSpecificError(pClientContext->GetSocket()));

                         pClientContext = DeleteClientContext(pClientContext);
                         continue;
                    }

                    //Move to next node on the list
                    pClientContext = pClientContext->GetNext();
               }//while
          }
          else //select
          {
               printf("\nError occurred while executing select(): %ld.", WSAGetLastError());
               return; //Get out of this function
          }
     }
}

//When using select() multiple sockets may have errors
//This function will give us the socket specific error
//WSAGetLastError() can't be relied upon
int GetSocketSpecificError(SOCKET Socket)
{
     int nOptionValue;
     int nOptionValueLength = sizeof(nOptionValue);

     //Get error code specific to this socket
     getsockopt(Socket, SOL_SOCKET, SO_ERROR, (char*)&nOptionValue, &nOptionValueLength);

     return nOptionValue;
}

//Get the head node pointer
CClientContext* GetClientContextHead()
{
     return g_pClientContextHead;
}

//Add a new client context to the list
void AddClientContextToList(CClientContext *pClientContext)
{
     //Add the new client context right at the head
     pClientContext->SetNext(g_pClientContextHead);
     g_pClientContextHead = pClientContext;
}

//This function will delete the node and will return the next node of the list
CClientContext * DeleteClientContext(CClientContext *pClientContext)
{
     //See if we have to delete the head node
     if (pClientContext == g_pClientContextHead) 
     {
          CClientContext *pTemp = g_pClientContextHead;
          g_pClientContextHead = g_pClientContextHead->GetNext();
          delete pTemp;
          return g_pClientContextHead;
     }

     //Iterate the list and delete the appropriate node
     CClientContext *pPrev = g_pClientContextHead;
     CClientContext *pCurr = g_pClientContextHead->GetNext();

     while (pCurr)
     {
          if (pCurr == pClientContext)
          {
               CClientContext *pTemp = pCurr->GetNext();
               pPrev->SetNext(pTemp);
               delete pCurr;
               return pTemp;
          }

          pPrev = pCurr;
          pCurr = pCurr->GetNext();
     }

     return NULL;
}
