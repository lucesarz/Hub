/*
 * =====================================================================================
 *
 *       Filename:  MasterHub.cxx
 *
 *    Description:  MasterHub Defs and Methods
 *
 *        Version:  1.0
 *        Created:  06/10/2016 09:03:21 AM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  luke
 *        Company:  Van Der Co
 *
 * =====================================================================================
 */
/*=============================================
 * For the most part this is self explanitory
 *=============================================
 */
#include <include/Hub.h>
#include <include/hubDefs.h>
#include <include/MasterHub.h>
#include <include/queue.h>
//init static var TODO:
//need to allocate these arrays? seg fault coming from here I believe.
MasterHub::MasterHub()
{
    //init HId and master pointer
    HId = ++HubCnt;
    pMaster = this;
    //init queues
    for(int i = 0;i<SLAVESIZE*2;i++)
        SlaveQList[i] = new HIQueue; 
    for(int i = 0;i<SLAVESIZE;i++)
        SSlaveQList[i] = new HSQueue;
    pSendDataQ = NULL;
    pRecDataQ = NULL;
    pStringQ = NULL;
}
//Master Hub's destructor
MasterHub::~MasterHub()
{
    delete pMaster;
    delete pSendDataQ;
    delete pRecDataQ;
    delete pStringQ;
    for(int i = SLAVESIZE; i< SLAVESIZE; i++)
    {
        delete pSlave[i];
        delete SlaveQList[i];
    }
    for(int i = SLAVESIZE * 2; i<SLAVESIZE; i++)
        delete SSlaveQList[i];
}
/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * *Methord to create a slave.  Returns a pointer to that slave Hub
 * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 */
Hub* MasterHub::CreateSlave()
{   
    //ERROR CHECKING
    if(HubCnt >= 10)
        return NULL;
    Hub* slave;
    HubCnt++;
    slave = new Hub(this,SlaveQList[HubCnt],SlaveQList[HubCnt+1],SSlaveQList[HubCnt]);
    pSlave[HubCnt] = slave;
    return slave;
}
//Method for the master hub to send data to the slaves
bool MasterHub::MasterSend(HUBId destId,HUBSig data)
{
    pSendDataQ = SlaveQList[destId+1];
    if(pSendDataQ == NULL)
        //ODD ERROR
        return false;
    return SendSig(data);
}
//Method for the master hub to receive data from the slaves
HUBSig MasterHub::MasterRecSig(HUBId fromId)
{
    pRecDataQ = SlaveQList[fromId];
    if(pRecDataQ == NULL)
        return -1;
    return RecSig();
}
//method for the master hub to receive string data from slaves
HUBData MasterHub::MasterRecData(HUBId fromId)
{
    HUBData data;
    pStringQ = SSlaveQList[fromId];
    if(pStringQ == NULL)
        return "ERR";
    if(pStringQ->dequeue(data))
        return data;
}











