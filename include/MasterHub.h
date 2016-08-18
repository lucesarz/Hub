#if !defined(_MasterHub_h_)  ///< test  to prevent repeat inclusion
#define      _MasterHub_h_   ///< define it
/*
 * =====================================================================================
 *
 *       Filename:  MasterHub.h
 *
 *    Description:  The Master Hub class.  This guy is the big daddy that makes
 *                  the important decisions based on data received from the 
 *                  slaves.  
 *
 *        Version:  1.0
 *        Created:  06/10/2016 08:30:35 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  ekl, fudg 
 *        Company:  Van Der Co
 *
 * =====================================================================================
 */

#include "Hub.h"
#include "hubDefs.h"

class MasterHub: public Hub
{
    public:
        //Constructor
        MasterHub();

        //Desructor
        ~MasterHub();
        
        Hub*            CreateSlave();
     /* void inline     SetISendQueue(HIQueue* slave) {pSendDataQ = slave;}
        void inline     SetIRecQueue(HIQueue* slave) {pRecDataQ = slave;}
        void inline     SetSRecQueue(HSQueue* slave) {pRecStringQ = slave;}*/
        bool            MasterSend(HUBId,HUBSig);
        HUBSig          MasterRecSig(HUBId);
        HUBData         MasterRecData(HUBId);
    private:
        //slave queue list
        HIQueue         *SlaveQList[SLAVESIZE*2];
        HSQueue         *SSlaveQList[SLAVESIZE];        
};

#endif
