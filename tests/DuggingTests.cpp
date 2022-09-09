#include "Debugging.h"
#include <gtest/gtest.h>
#include <CommonLib.h>

//TEST(Debugging, PrintInfo){
//    pInfo("TESTING", "This is testing the pInfo");
//    ASSERT_EQ(1,1);
//}
//
//TEST(Debugging, PrintError){
//    pError("TEST", "This is testing the print pError");
//    ASSERT_EQ(1,1);
//}
//TEST(Debugging,  PrintCatagory) {
//    pCat("Debugging", "TESTING", "This is testing pCat");
//    ASSERT_EQ(1,1);
//}
//
//TEST(Debugging, PrintLists) {
//    pList("Debugging", "Testing", 15, 
//            "testingthththth",
//            "testing",
//            "testing",
//            "testing",
//            "testing",
//            "testing",
//            "testing",
//            "testing",
//            "testing",
//            "testing",
//            "testing",
//            "testing",
//            "testing",
//            "testing",
//            "ththttesting");
//    ASSERT_EQ(1,1);
//}
//
//TEST(Debugging, PrintChart){
//    const char* types[3] = {"This is a resising test for the catagories","Testing 2", "Testing 3"};
//    pChart(types, CHART_TYPE_COLOMS, 3, 6, "Item1", "Item2", "Item3", "Item", "Item", "This is a resising test for the items", "Item");
//    ASSERT_EQ(1,1);
//}

int main() {
    const char* types[3] = {"This is a resising test for the catagories","Testing 2", "Testing 3"};
    pChart(types, CHART_TYPE_COLOMS, 3, 6, "Item1", "Item2", "Item3", "Item", "Item", "This is a resising test for the items", "Item");
	return 0;
}