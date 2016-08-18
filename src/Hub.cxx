/*
 * =====================================================================================
 *
 *       Filename:  Hub.cxx
 *
 *    Description:  Initializations and methods
 *
 *        Version:  1.0
 *        Created:  06/09/2016 04:04:02 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  luke
 *        Company:  Van Der Co
 *
 * =====================================================================================
 */

#include <include/hubDefs.h>
#include <include/queue.h>
#include <include/Hub.h>
//init static variable hub count
/* *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * Default Constructor for Hub
 * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * */
uns32 Hub::HubCnt = 0;
Hub::Hub()
{   
    //The id is just the count for now
    HId = HubCnt;
    //init the master to NULL it will get set in CreateSlave()
    pMaster = this;    
    //init the slave list to NULLs
    for(int i = 0; i < SLAVESIZE; i++)    
    {   
        pSlave[i] = NULL;
    }   
    //init queues
    HIQueue SQ; 
    HIQueue RQ; 
    pSendDataQ = &SQ;
    pRecDataQ  = &RQ;
    pStringQ= NULL;
}
/* *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * Constructor for Hub
 * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * */
Hub::Hub(Hub *Master,HIQueue* SQ, HIQueue* RQ, HSQueue* SSQ)
{
    HId = HubCnt;
    pMaster = Master;
    for(int i = 0; i < SLAVESIZE; i++)
    {
        pSlave[i] = NULL;
    }
    //init queues
    pSendDataQ = SQ;
    pRecDataQ = RQ;
    pStringQ = SSQ;
}
/* *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * Destructor for Hub
 * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * */
Hub::~Hub()
{
    delete pMaster;
    delete pSendDataQ;
    delete pRecDataQ;
    delete pStringQ;
    for(int i = SLAVESIZE; i< SLAVESIZE; i++)
    {
        delete pSlave[i];
    }
}
/* *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * *Method to Print Hub info
 * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * */
void Hub::Print()
{
    printf("HId : 0x%lx, pMaster : %p, MasterId: %lx, HubCount : %lx\n", HId, pMaster, GetMasterId(), HubCnt);
    return ;
}
/* *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * *Method to Print the send queue of a given slaveId
 * *For debugging purposes
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * */
void Hub::PrintSIQueue(HUBId sid)
{
    HIQueue tmp;
    uns32 array[SLAVESIZE];
    int i;
    //initialize array
    for(int t = 0; t<SLAVESIZE; t++)
        array[t] = 0;
    //dequeue the members of the queue into the array
    while(GetSlaveP(sid)->pSendDataQ->dequeue(array[i]))
        i++;
    i = 0;
    //check if the array has any members if no, return
    if(array[0] == -1) 
    {   
        printf("The SendDataQ of slave %lx is empty\n",sid);
        return;
    }   
    else
    {   
        printf("SendDataQ of slave %lx (from left -> right being front -> back) : \n", sid);
    }   
    //print the queue members
    while(array[i] > 0)
    {   
        printf("SendQ[%d] = 0x%lx\n",i,array[i]);
        i++;
    }   
    //enqueue the array back in we are done
    while(array[i] > 0)
    {   
        GetSlaveP(sid)->pSendDataQ->enqueue(array[i]);
        i++;
    }   
}
/* *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * *Method to Print the receive queue of a given slaveId
 * *For debugging purposes
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * */
void Hub::PrintRIQueue(HUBId sid)
{
    HIQueue tmp;
    uns32 array[SLAVESIZE];
    int i;
    //initialize array
    for(int t = 0; t<SLAVESIZE; t++)
        array[t] = 0;
    //dequeue the members of the queue into the array
    while(GetSlaveP(sid)->pRecDataQ->dequeue(array[i]))
        i++;
    i = 0;
    //check if the array has any members if no, return
    if(array[0] == -1)
    {
        printf("TheRec DataQ of slave 0x%lx is empty\n",sid);
        return;
    }   
    else
    {
        printf("RecDataQ of slave 0x%lx (from left -> right being front -> back) : \n", sid);
    }   
    //print the queue members
    while(array[i] > 0)
    {
        printf("RecdQ[%d] = 0x%lx\n",i,array[i]);
        i++;
    }   
    //enqueue the array back in we are done
    while(array[i] > 0)
    {
        GetSlaveP(sid)->pRecDataQ->enqueue(array[i]);
        i++;
    }
}
/* *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * *Method to Print the queue of a given slaveId
 * *For debugging purposes
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * */
void Hub::PrintSSQueue(HUBId sid)
{
    HIQueue tmp;
    std::string array[SLAVESIZE];
    int i;
    //initialize array
    for(int t = 0; t<SLAVESIZE; t++)
        array[t] = "";
    //dequeue the members of the queue into the array
    while(GetSlaveP(sid)->pStringQ->dequeue(array[i]))
        i++;
    i = 0;
    //check if the array has any members if no, return
    if(array[0] == "")
    {
        printf("TheRec DataQ of slave %lx is empty\n",sid);
        return;
    }   
    else
    {
        printf("RecDataQ of slave %lx (from left -> right being front -> back) : \n", sid);
    }   
    //print the queue members
    while(array[i] != "")
    {
        printf("RecdQ[%d] = 0x%s\n",i,array[i].c_str());
        i++;
    }   
    //enqueue the array back in we are done
    while(array[i] != "")
    {
        GetSlaveP(sid)->pStringQ->enqueue(array[i]);
        i++;
    }
}
/* *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * *Method to Send a signal to the Master Hub.
 * *Basically enqueues some data on the queue for the master to grab it
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * */

bool Hub::SendSig(HUBSig data)
{
    if(pSendDataQ == NULL)
        //ERROR NOT REALLY SURE HOW IT GOT HERE
        return false;
    return pSendDataQ->enqueue(data);
}
bool Hub::SendSData(HUBData data)
{
    if(pSendDataQ == NULL)
        //ERROR NOT REALLY SURE HOW IT GOT HERE
        return false;
    return pStringQ->enqueue(data);
}
HUBSig Hub::RecSig()
{
    HUBSig data;
    if(pRecDataQ == NULL)
        //ERROR NOT REALLY SURE HOW IT GOT HERE
        return -1;
    pRecDataQ->dequeue(data);
    return data;
}





