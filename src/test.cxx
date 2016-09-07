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

void* MasterRec(MasterHub* master);
void* running();
void* SendData(Hub* slave);

int main ( int argc, char *argv[] )
{
    //declaring the master hub.
    MasterHub *Master = new MasterHub();
    Hub *Slave1;
    Slave1 = Master->CreateSlave();
    pthread_t t[2];
    pthread_create(&t[0],NULL,SendData, Slave1);
    pthread_create(&t[1],NULL,MasterRec, Master);
    pthread_join(t[0],NULL);


    return 0;
}

void* MasterRec(MasterHub*  master)
{
    HUBSig data = 0;
    master = (MasterHub*)master;
    int i = 0;
    while(running())
    {
        data = master->MasterRecSig(i);
        if(data != 0)
        {
            printf("data: %lx\n",data);
            data = 0;
        }
        if(i++ == 3)
        {
            i = 0;
        }
    }
}

void* SendData(Hub* slave)
{
    int t = 0;
    slave = (Hub*)slave;
    int array[1024];
    struct timespec* t;
    t->tv_sec = 0;
    t->tv_nsec = 5;
    for(int i = 0; i < 1024; i++)
    {
        array[i] = i + 1;
    }
    while(running)
    {
        if(!slave->SendData(array[t]))
        {
            nanosleep(t,NULL);
        }
        if(t++ ==1023)
        {
            t =0;
        }
    }
}

bool running(void)
{
    //Looks unecessary but will change later to have stipulations.
    return true;
}
















/* ----------  end of function main  ---------- */
