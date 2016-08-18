/*
 * =====================================================================================
 *
 *       Filename:  test.cxx
 *
 *    Description:  test code for the hub framework
 *
 *        Version:  1.0
 *        Created:  06/08/2016 02:10:02 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  luke
 *        Company:  Van Der Co
 *
 * =====================================================================================
 */
#include <include/hubDefs.h>
#include <include/Hub.h>
#include <include/MasterHub.h>
using namespace std;
    int
main ( int argc, char *argv[] )
{
    //Let's declare me a Master and print some basic info
    MasterHub *Master = new MasterHub();
    Hub *Slave1;
    Slave1 = Master->CreateSlave();
    
    printf("HId1 : %lx, HId2 : %lx\n",Master->GetHubId(),Slave1->GetHubId());
    printf("Master's master is : %lx, Slave1's master is : %lx\n",Master->GetMasterId(),Slave1->GetMasterId());

    //Now let's try the queue's a little bit and try the PrintQueue functions in Hub

    HUBSig data0 = 0x45;
    HUBSig data1 = 0x36;
    HUBSig data2 = 0x16;
    HUBSig rec0, rec1,rec2;

    Slave1->SendSig(data0);
    Slave1->SendSig(data1);
    Slave1->SendSig(data2);
    printf("test\n");
    rec0 = Master->MasterRecSig(2);
    rec1 = Master->MasterRecSig(2);
    rec2 = Master->MasterRecSig(2);
    printf("rec0 = 0x%lx, rec1 = 0x%lx, rec = 0x%lx\n",rec0,rec1,rec2);
//GIT TEST COMMENT
    


    return 0;
}	


















/* ----------  end of function main  ---------- */
