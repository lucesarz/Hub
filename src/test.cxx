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
#include <pthread.h>

using namespace std;
    int
main ( int argc, char *argv[] )
{
    //declaring the master hub.
    MasterHub *Master = new MasterHub();
    Hub *Slave1;
    Slave1 = Master->CreateSlave();
    pthread_t t[2];
    pthread_create(&t[0],NULL,SendData,(void*)Slave1);
    pthread_create(&t[1],NULL,MasterSend,(void*)Master);
    pthread_join(&t[0],NULL);


    return 0;
}

void* MasterRec(void*  master)
{
    master = (MasterHub*)master;
    int i = 0;
    while(running())
    {
        master->MasterRecData(i++);
        if(i == 3)
        {
            i = 0;
        }
    }
}

void* SendData(void* slave)
{
    int t = 0;
    slave = (Hub*)slave;
    int array[1024];
    for(int i = 0; i < 1024; i++)
    {
        array[i] = i + 1;
    }
    while(running)
    {
        slave->SendData(array[t])
        if(t++ ==1023)
        {
            t =0;
        }
    }
}

bool running(void)
{
    //Looks unecessary but will change.
    return true;
}
//TEST 
















/* ----------  end of function main  ---------- */
