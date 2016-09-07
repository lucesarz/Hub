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
#include <unistd.h>

using namespace std;

void* MasterRec(void* master);
bool running(void);
void* SendData(void* slave);

int main ( int argc, char *argv[] )
{
    //declaring the master hub.
    MasterHub *Master = new MasterHub();
    Hub *Slave1;
    Slave1 = Master->CreateSlave();
    pthread_t t[2];
    pthread_create(&t[0],NULL,SendData, (void*)Slave1);
    pthread_create(&t[1],NULL,MasterRec, (void*)Master);
    printf("Threads started\n");
    pthread_join(t[0],NULL);


    return 0;
}

void* MasterRec(void*  m)
{
    printf("Entered receive thread\n");
    MasterHub* master;
    HUBSig data = 0;
    master = (MasterHub*)m;
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

void* SendData(void* s)
{
    printf("Entered Send Thread\n");
    Hub* slave;
    int t = 0;
    slave = (Hub*)s;
    HUBSig array[1024];
    for(int i = 0; i < 1024; i++)
    {
        array[i] = i + 1;
    }
    while(running)
    {
        if(!slave->SendSig(array[t]))
        {
            usleep(1);
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
