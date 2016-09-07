#if !defined(_hubDefs_h_)
#define _hubDefs_h_
/*
 * =====================================================================================
 *
 *       Filename:  hubDefs.h
 *
 *    Description:  Some useful definitions for the hub class
 *
 *        Version:  1.0
 *        Created:  06/08/2016 12:07:18 PM
 *       Compiler:  gcc
 *
 *         Author:  Luke A Cesarz, University of MN, TC
 *        Company:  Van Der Co
 *
 * =====================================================================================
 */

/*
 **************************************************************************************
 * This file is going to be large.  Make sure to comment anything that can get
 * confusing. This is the main defenitions file for hub-stuff. The only stuff
 * that is to not go in here are QIC's
 * ************************************************************************************
 */
#include "queue.h"
#include <cstdio>
#include <string>
#include <cstddef>
#include <cstdlib>

typedef unsigned long long uns64;
typedef unsigned long uns32;
typedef uns32 HUBERR;
typedef std::string HUBData;
typedef uns32 HUBId;
typedef uns32 HUBSig;
typedef Queue<uns32> HIQueue;
typedef Queue<std::string> HSQueue;
//list of error codes
//the errors in the list are just examples
enum ErrorList
{
    ERROR_SENDDATA = -1,
    ERROR_RECDATA = -2,
    ERROR_REQDATA = -3,
};

//These two 'should' always be the same
#define MAXHUBS 10
#define SLAVESIZE 3 




/*
 *********************************************************************
 * Define all HUBSigs here.  These are important.  Name them nicely.
 *
 *********************************************************************
 */
#define STARTEDTASK                 0x00000000
#define PERFORMINGTASK              0x00000000
#define COMPLETEDTASK               0x00000000
#define RECEIVEDTASK                0x00000000
#define STARTEDTASK                 0x00000000
/**************************************************************
 * add more as needed.
#define STARTEDTASK                 0x00000000
#define PERFORMINGTASK              0x00000000
#define COMPLETEDTASK               0x00000000
#define RECEIVEDTASK                0x00000000
#define STARTEDTASK                 0x00000000
**************************************************************/

#endif
