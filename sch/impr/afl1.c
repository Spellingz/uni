#include <stdio.h>

int main(void)
{
  // DEFINE VARS
  int sec, min, hour, day, week;
  
  // Main
  scanf("%d", &sec);
  
  min = sec/60;
  sec = sec%60;
  hour = min/60;
  min = min%60;
  day = hour/24;
  hour = hour%24;
  week = day/7;
  day = day%7;

  printf("week: %d, day: %d, hour: %d, min: %d, sec: %d", week, day, hour, min, sec);

  return 0;
}


