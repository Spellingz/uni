#include <stdio.h>

int main(void)
{
  int input, c;
  int antal = 0;

  scanf("%d %d", &input, &c);

  int n = input;
  int digits = 0;

  while (n>0)
  {
    n /= 10;
    digits++;
  }
  printf("Antal Digits: %d \n", digits);


  for (int j = 0; j < input; j++)
  {
    int focusNum = j;
    for (int i = 0; i < digits; i++)
    {
      int focusChar = focusNum%10;
      if (focusChar == c)
      {
        antal++;
        break;
      }
      focusNum /= 10;
    }
  }

  printf("Antal: %d", antal);
  
  return 0;
} 
