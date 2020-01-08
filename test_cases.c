#include "isam.c"
#include <stdio.h>
#include <string.h>
int test_status[] = {0,0,0};
void test_new_ISAM()
{ 
    char* DB_name = "test";
    int record_count = 1;
    test_status[2]++;

    puts("**Creating Database");
    ISAM DB = new_ISAM(DB_name, record_count, record_count);

    puts("**Testing Ouput");
    //test name
    if(strcmp(DB->name, DB_name) == 0)
    {
        puts("++Name Test Passed");
        test_status[0]++;
    }
    else
    {
        puts("--Name Test Failed");
        test_status[1]++;
    }
    //test record counts
    if(DB->max_records == record_count)
    {
        puts("++Record Count Test Passed");
        test_status[0]++;
    }
    else
    {
        puts("--Record Count Test Failed");
        test_status[1]++;
    }
    
    if(DB->max_overflow == record_count)
    {
        puts("++Overflow Record Test Passed");
        test_status[0]++;
    }
    else
    {
        puts("--Overflow Record Test Failed");
        test_status[1]++;
    }

    if(DB->max_total_records == record_count*2)
    {
        puts("++Total Record Count Test Passed");
        test_status[0]++;
    }
    else
    {
        puts("--Total Record Count Test Failed");
        test_status[1]++;
    }
    
    
}

int main()
{
    test_new_ISAM();
    printf("Tests Run: %d\nPassed Tests: %d, Failed Tests: %d", test_status[2], test_status[0], test_status[1]);
    return 0;
}
