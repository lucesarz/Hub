#if !defined(_Hub_h_)  ///< test  to prevent repeat inclusion
#define      _Hub_h_   ///< define it
/*
 * =====================================================================================
 *
 *       Filename:  Hub.h
 *
 *    Description:  The Hub class definition.These generic hubs
 *                  communicate with eachother to perform tasks 
 *                  based on data received from other hubs.
 *
 *        Version:  1.0
 *        Created:  06/08/2016 08:44:39 AM
 *       Compiler:  gcc
 *
 *        Authors:  Luke A Cesarz, University of Minnesota TC
 *        Company:  Van Der Co 
 *
 * =====================================================================================
 */

#include "hubDefs.h"
#include <string>
/*
 * -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
 * Here lies the definition of the generic hub. The bear bones of the code.  Some of 
 * the items defined in here are only to be used in the master hub currently; why are 
 * they here then you ask? Because possibly one day we will use them in here.  
 *
 * Everything is defined in hubDefs.h
 *
 * The basics: A hub is a piece of code that has its own thread. It performs a task 
 * assigned to it by the master hub.  It can then communicate with the master hub by
 * sending data to it (uns32 or string) through 3 different possible queues.  The master 
 * then can make decisions based off of the data received from all the slave hubs, and 
 * its own task. It is a high level implementation of a state machine (kinda).  
 * Its prctical uses are not really clear yet.
 * -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
 *
 */
class Hub
{
    public:
        //Constructor
        Hub();
        Hub(Hub *Master,HIQueue* SQ, HIQueue* RQ, HSQueue* SSQ);
       
        //Destructor
        ~Hub();
        
        static uns32            HubCnt;
        //printf
        void                    Print();
        inline static uns32     GetHubCnt() { return HubCnt; }
        //get id of this
        inline HUBId            GetHubId() { return HId; }
        //get id of parent hub
        inline HUBId            GetMasterId() { return pMaster->GetHubId(); }
        //set Master
        inline void             SetMaster(Hub newMaster) { pMaster = &newMaster; }
        //get pointer of child hub
        inline Hub*             GetSlaveP(HUBId id) { return pSlave[id]; }
        //print the uns32 queue contents of the given slaveId
        void                    PrintSIQueue(HUBId);
        //print the uns32 receive queue of the given slave id
        void                    PrintRIQueue(HUBId);
        //print the string queue contents of the given slaveId
        void                    PrintSSQueue(HUBId); 
        //COMMUNITCATION FUNCTIONS:
        //send integer data fnc
        bool                    SendSig(HUBSig);
        //send string data fnc
        bool                    SendSData(HUBData);
        //request datafnc
        //HUBSig                ReqData(HUBId,Data);
        //receive data fnc
        HUBSig                  RecSig();

    protected:
        HUBId                   HId;
        Hub                     *pMaster;
        Hub                     *pSlave[SLAVESIZE];
        HIQueue                 *pSendDataQ;
        HIQueue                 *pRecDataQ;
        HSQueue                 *pStringQ;
};
#endif
