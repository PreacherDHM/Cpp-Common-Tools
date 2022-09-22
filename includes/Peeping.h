#ifndef PEEPING_H
#define PEEPING_H
#include <ctime>
#include <stdio.h>
#include <Debugging.h>
#include <sys/select.h>

#define __GET_NAME(v) #v

#define DEBUGING
#ifdef DEBUGING
#include <iostream>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#define ___Color_Object "\033[031m"
#define ___Color_Data "\033[0;36m"
#define ___Color_Time "\033[1;33m"
#define ___NOCL "\033[0m"
#define ___File_Format_PEEP(time, data, var, file, lineNumber) fprintf(file, "%ld|%d: %s = %X |\n",time,lineNumber, var, data ); 
#define ___FILE_FORMAT_BREAK_POINT(time, line, file, lineNumber) fprintf(file, "%ld|BREAK_POINT: %d: %s |\n", time, lineNumber, line);


/*
 * log file structer
 *
 * TIME: Time stamp
 *
 * object1: address : data hex : data desible;
 */
struct PeepLog {
    FILE *log;
};

static PeepLog __log = PeepLog();
static void ___initDebug() {
    __log.log = fopen("./Debuging.log", "w+");
    if (__log.log == NULL) { pError("PEEP", "DEBUG FILE DID NOT INIT"); return; }
    pInfo("PEEP", "Writing/creating new file");
}
/* grasfuly ending the log file */
static void ___endDebug() {
    pInfo("PEEP", "Closeing Log file");
    fclose(__log.log);
}
/* wrighting data to the log file with a time stamp */
static void ___writeDataPeep(long timeStamp, int dataPtr, const char *varName, int lineNumber){
    ___File_Format_PEEP(timeStamp, dataPtr, varName,__log.log, lineNumber);
}

static void ___writeDataBreakPoint(long timeStamp, const char *line,int lineNumber){
    ___FILE_FORMAT_BREAK_POINT(timeStamp, line,__log.log, lineNumber);
}
#define CTRL_KEY(k) ((k)&0x1f)
static char __c;
//gets input from terminal
static void CInput() {
    fputs("\e[?25l", stdout);
    __c = '\0';
    char seq[3];
    read(STDIN_FILENO, &__c, 1);
    if ((int)__c == 127) {
        __c = '1';
        return;
    }
    if (__c == '\0')
        return;

    if (__c == '\x1b') {
        char seq[3];
    if (read(STDIN_FILENO, &seq[0], 1) != 1) {
        __c = '\x1b';
        return;
    }

    if (read(STDIN_FILENO, &seq[1], 1) != 1) {
        __c = '\x1b';
        return;
    }

    if (seq[0] == '[') {
        if (read(STDIN_FILENO, &seq[2], 1) != 1) {
            __c = '\x1b';
        return;
        };
        if (seq[2] == '~') {
            if (seq[1] == '3') {
                __c = '1';
                return;
            }
        }
    }

    __c = '\x1b';
    return;
    }
    if (__c == '\b') {
    }
}

inline void canonOff() {
    struct termios term;
    tcgetattr(1, &term);
    term.c_lflag &= ~ICANON;
    tcsetattr(1, TCSANOW, &term);
}

inline void canonOn() {
    struct termios term;
    tcgetattr(1, &term);
    term.c_lflag |= ICANON;
    tcsetattr(1, TCSANOW, &term);
}

inline void echoOff() {
    struct termios term;
    tcgetattr(1, &term);
    term.c_lflag &= ~ECHO;
    tcsetattr(1, TCSANOW, &term);
}

inline void echoOn() {
    struct termios term;
    tcgetattr(1, &term);
    term.c_lflag |= ECHO;
    tcsetattr(1, TCSANOW, &term);
}


static long __timeStamp(){
    struct timespec ts;
    timespec_get(&ts,TIME_UTC);
    
    return  1000000 * ts.tv_sec + ts.tv_nsec;
}
#define INIT_LOG_FILE ___initDebug();
#define BREAK_POINT(line) { ___writeDataBreakPoint(__timeStamp(), #line, __LINE__); printf("| \033[1;37m%s\033[0m | \033[0;31m%d\033[0m | \033[0;33m%s \033[1;36m<--- \033[4;37mBREAK POINT\033[0m\n", __FILE_NAME__, __LINE__, #line); canonOff(); echoOff(); while (true) { CInput(); if (__c == 'b') { canonOn(); echoOn(); fputs("\r\e[?25h", stdout); break; }};}line;
#define PEEP(var) { ___writeDataPeep(__timeStamp(), var, #var, __LINE__); printf("TIME: %s%ld%s| \033[031mNAME \033[0;36m%s\033[0m | \033[031mADDRESS \033[0;36m%x \033[0m| \033[031mHEX \033[0;36m%x\033[0m| \033[031mDES \033[0;36m%i \033[0m|\n",___Color_Time, __timeStamp(), ___NOCL, __GET_NAME(var), &var, var, var);}
#else
#define PEEP(var)
#define BREAK_POINT(line) #line
#define INIT_LOG_FILE
#endif
#endif // end of header
