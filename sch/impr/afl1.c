#include <stdio.h>

int main(void)
{
  // DEFINE VARS
  int sec, min, hour, day, week;
 // double min, hour, day, week;
  
  // Main
  scanf("%d", &sec);
  
  min = sec/60 - sec%1;
  sec = sec%60;
  hour = min/60 - min%1;
  min = min%60;
  day = hour/24 - hour%1;
  hour = hour%24;
  week = day/7 - day%1;
  day = day%7;

  printf("sec: %d, min: %d, hour: %d, day: %d, week: %d", sec, min, hour, day, week);

  return 0;
}


