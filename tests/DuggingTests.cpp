#define DEBUGING
#include "Debugging.h"
#include "Peeping.h"

int main() {
    INIT_LOG_FILE
    const char* types[3] = {"This is a resising test for the catagories","Testing 2", "Testing 3"};
    pChart(types, CHART_TYPE_COLOMS, 3, 6, "Item1", "Item2", "Item3", "Item", "Item", "This is a resising test for the items", "Item");
    printf("\n");
    pChart(types, CHART_TYPE_ROWS, 3, 9, "Item1", "Item2","Item2","Item2","Item2", "Item3", "Item", "Item", "This is a resising test for the items", "Item");
    int i = 255;
    const int y = 255;
    char* test = "testingggg";
    PEEP(i);
    BREAK_POINT(PEEP(y););
	return 0;
}
