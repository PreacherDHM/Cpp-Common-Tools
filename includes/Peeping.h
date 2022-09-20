#ifndef PEEPING_H
#define PEEPING_H
#include <ctime>
#define __GET_NAME(v) #v
#include <stdio.h>

#define ___Color_Object "\033[031m"
#define ___Color_Data "\033[0;36m"
#define ___Color_Time "\033[1;33m"
#define ___NOCL "\033[0m"
/*
 * log file structer
 * TIME: Time stamp
 * object1: address : data hex : data desible;
 * */
struct PeepLog {
    FILE* log;
    int timeStamp;
    int* data[];
};

/* wrighting data to the log file with a time stamp */
inline void wrightData(int timeStamp, int* dataPtr, const char* varName) {

};
/* grasfule shutdown of the log file */
inline void closeFile() {

};
#ifdef DEBUGING
#define PEEP(var) {time_t now = time(0); char* dt = ctime(&now); printf("TIME: %s%s%s| \033[031mNAME \033[0;36m%s\033[0m | \033[031mADDRESS \033[0;36m%x \033[0m| \033[031mHEX \033[0;36m%x \033[0m| \033[031mDES \033[0;36m%i \033[0m|\n",___Color_Time, dt, ___NOCL,  __GET_NAME(var), &var, var, var); }
#else
#endif
#endif
