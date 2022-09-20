#ifndef DEBUGGING_H
#define DEBUGGING_H
//Start Coding Debugging. 
#include <cstdarg>
#include <stdio.h>
#include <cstring>

//Windows terminal init
#ifdef _WIN64
#include <Windows.h>

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
static DWORD ___outModeInit;
static HANDLE ___stdoutHandle;
static bool ___ran = false;
#define ___INIT() if(!___ran){ ___ran = true;  DWORD outMode = 0; ___stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE); if (___stdoutHandle == INVALID_HANDLE_VALUE) { exit(GetLastError()); } if (!GetConsoleMode(___stdoutHandle, &outMode)) { exit(GetLastError()); } ___outModeInit = outMode; outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING; if (!SetConsoleMode(___stdoutHandle, outMode)) { exit(GetLastError()); } printf("\x1b[0m"); }
#else
#define ___INIT()
#endif

#define P_COLOR_INFO "\033[0;36m"
#define P_COLOR_ERROR "\033[0;31m"
#define P_COLOR_CAT "\033[1;36m"
#define P_COLOR_CAT_MESSAGE "\033[4;32m"

#define P_COLOR_TAG "\033[1;33m"
#define P_COLOR_NC "\033[0m"

#define pInfo(tag, message)  ___INIT(); printf("[%sINFO%s]%s %s%s: %s\n",P_COLOR_INFO,P_COLOR_NC, P_COLOR_TAG,  tag, P_COLOR_NC, message)
#define pError(tag, message) ___INIT(); printf("[%sERROR%s]%s %s%s: %s\n",P_COLOR_ERROR,P_COLOR_NC,P_COLOR_TAG, tag, P_COLOR_NC, message)  
#define pCat(Catagory, tag, message) ___INIT(); printf("[%s%s%s]%s %s%s: %s%s%s\n",P_COLOR_CAT,Catagory,P_COLOR_NC,P_COLOR_TAG, tag, P_COLOR_NC,P_COLOR_CAT_MESSAGE, message, P_COLOR_NC)

//pChart configuration types
#define CHART_TYPE_COLOMS 0
#define CHART_TYPE_ROWS 1
//pChat null phrase/char
#define CHART_NULL_CHAR "#"
#define ___Col_start() printf("|")
#define ___Col_end() printf("|")
#define ___Col_print(color, Item) printf(" %s%s%s", color, Item, P_COLOR_NC)
#define ___Col_Next() printf("\n")
#define ___Col_Spacing(spacing, spaceChar) for(int ss = 0; ss < spacing; ss++) { printf(spaceChar); }
#define ___Col_Center(spacing, spaceChar, color, Str) { for(int ss = 0; ss < spacing + 1; ss++) {  if(ss == (spacing/2 ) - (strlen(Str)/2)) { ss += strlen(Str); ___Col_print(color,Str);  }printf(spaceChar);} }
#define ___Col_Seperator(spaceSize, lableCount) for(int x = 0; x < lableCount; x++) { ___Col_start(); printf(":"); for(int i = 0; i < spaceSize[x]; i++) { printf("-"); } printf(":"); } ___Col_end();
//Currently not being used ___INIT_COL_AND_SIZE
#define ___INIT_COL_AND_SIZE for( int x = 0; x < CatArgs; x++) { int strSize = strlen(Catagories[x]); if(CatagorySizes[x] < strSize) { CatagorySizes[x] = strSize; }} for(int i = 0; i < CatArgs; i++) { CatagorySizes[i] = itemSize; } for(int i = 0; i < itemCount; i+= CatArgs) { for( int x = 0; x < CatArgs; x++) { strSize = strlen(items[i + x]); if(CatagorySizes[x] < strSize) { CatagorySizes[x] = strSize; }}}

inline void pList(const char* Catagory, const char* tag, const int itemCount, const char* item...){
    va_list args;
    int len = 0;
    va_start(args, item);
    while(len < itemCount-1) { 
        if(len == 0){
            pCat(Catagory, tag, item);
        }
        pCat(Catagory, tag, va_arg(args, char*));
        len++;
    }
};

/*  pChart alows one to print out a chart in the console. there is two different
    modes:

    **CHART_TYPE_ROWS** and **CHART_TYPE_COLOMS**
    
- *CHART_TYPE_COLOMS* prints the lables on top and the items under thows coloms.
        | Lable 1 | Lable 2 |
        |:-------:|:-------:|
        | Item 1  | Item 2  |
        | Item 3  | Item 4  |
        | Item 5  | Item 6  |

- *CHART_TYPE_ROWS* puts the lables on each row and the items along the right side.
        | Lable 1 |:| item 1 | item 2 | item 3 |
        | Lable 2 |:| item 4 | item 5 | item 6 |
        | Lable 3 |:| item 7 | item 8 | item 9 |
*/
inline void pChart(const char** Catagories, const int chartType,const int CatArgs, const int itemCount, char* item...) {
    int CatagoryLen = CatArgs;
    int CatagoryCount = 0;
    int currentCount = 0;
    int itemSize = 15;
#ifdef _WIN64 //if it is a win64 OS then it will build this.
    int *CatagorySizes = new int[CatArgs];
    char** items = new char*[CatArgs];
    ___INIT();
#else //if its any other system then build this.
    const char* items[itemCount];
#endif
    int strSize;

    va_list args;
    va_start(args, item);
 

    for(int i = 0; i < itemCount; i++){
        if(i == 0) {
            items[i] = item;
            continue;
        }else {
            items[i] = va_arg(args, char*);
        }
    }


    va_end(args);

    //coloms mode
    if(chartType == CHART_TYPE_COLOMS) {
#ifdef _WIN64 // windows stuff to create an array
              //
        int CatagorySizes[] = new int[CatArgs];
#else //linux / gcc
        int CatagorySizes[CatArgs];
#endif
        for(int i = 0; i < CatArgs; i++) {
            CatagorySizes[i] = itemSize;
        }


        for( int x = 0; x < CatArgs; x++) {
            int strSize = strlen(Catagories[x]);
            if(CatagorySizes[x] < strSize) {
                CatagorySizes[x] = strSize;
            }
        }

        for(int i = 0; i < itemCount; i+= CatArgs) {
            for( int x = 0; x < CatArgs; x++) {
                strSize = strlen(items[i + x]);
                if(CatagorySizes[x] < strSize) {
                    CatagorySizes[x] = strSize;
                }
            }       
        }
        //printing lable
        while(CatagoryCount < CatagoryLen) {
            ___Col_start();
            ___Col_Center(CatagorySizes[CatagoryCount], " ", P_COLOR_TAG, Catagories[CatagoryCount]);
            CatagoryCount++;
        }
        //printing the seperator
        ___Col_end();
        ___Col_Next();
        ___Col_Seperator(CatagorySizes, CatagoryLen);
        ___Col_Next();
        ___Col_start();

        int b = 0;
        //Printing the items
        while(currentCount < itemCount) {
            if(b == CatArgs){
                ___Col_Next();
                ___Col_start();
                b = 0;
            }
            
            ___Col_Center(CatagorySizes[b], " ", P_COLOR_CAT, items[currentCount]);
            ___Col_end(); 
            currentCount++;
            b++;
        }
        ___Col_Next();
    }

    if(chartType == CHART_TYPE_ROWS) {
#ifdef _WIN64 // windows stuff to create an array
        int CatagorySizes[] = new int[CatArgs + 1];
#else //linux / gcc
        int CatagorySizes[CatArgs + 1];
#endif

        // Setting the deflat spacing size
        for(int i = 0; i < CatArgs + 1; i++) {
            CatagorySizes[i] = itemSize;
        }

        // first seeing if any of the catagorys are bigger then the defalt
        for( int x = 0; x < CatArgs; x++) {
            int strSize = strlen(Catagories[x]);
            if(CatagorySizes[x] < strSize) {
                CatagorySizes[x] = strSize;
            }
        }

        // second seeing if any of the items are bigger then any of the catagorys
        for(int i = 0; i < itemCount; i += CatArgs) {
            for( int x = 0; x < CatArgs; x++) {
                strSize = strlen(items[i + x]);
                if(CatagorySizes[x+ 1] < strSize) {
                    CatagorySizes[x + 1] = strSize;
                }
            }       
        }

        //outputing to console
        int lableCount = 0;
        for(int i = 0; i < itemCount; i += CatArgs){
            //print lable;
            printf("|");
            ___Col_Center(CatagorySizes[0], " ", P_COLOR_TAG, Catagories[lableCount]);
            printf("|%s->%s|",P_COLOR_ERROR, P_COLOR_NC);
            // print contents
            for(int x = 0; x < CatArgs; x++){
                ___Col_Center(CatagorySizes[x + 1], " ", P_COLOR_CAT, items[i+x]);
                ___Col_start();
            }
            printf("\n");
            lableCount++;
        }
    }
};

#endif
