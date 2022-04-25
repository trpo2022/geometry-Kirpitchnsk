#include "../thirdparty/ctest.h"
#include "../src/libgeometry/functions.c"
#include <math.h>

CTEST(ukazatel_test, check_test_OK)
{
    const char stroke[10] = "abcdefghkl";
    const char letter = 'e';
    
    const int result = ukazatel(stroke,letter,0);

    const int search = 4;
    ASSERT_EQUAL(search,result);
}
CTEST(countelement_test, check_test_OK)
{
    const char stroke2[10] = "auudefguul";
    const char letter2 = 'u';
    
    const int result2 = countelement(stroke2,letter2);

    const int number = 4;
    ASSERT_EQUAL(number,result2);
}
CTEST(line_intersection_test, check_test_OK)
{
    const double x1 = 1;
    const double y1 = 2;
    const double x2 = 4;
    const double y2 = 2;
    const double x3 = 3;
    const double y3 = 1;
    const double x4 = 3;
    const double y4 = 3;
    
    const int result3 = line_intersection(x1,x2,y1,y2,x3,x4,y3,y4);

    const int intersect = 1;
    ASSERT_EQUAL(intersect,result3);
}