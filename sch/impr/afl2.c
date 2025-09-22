#include <stdio.h>


int countDigits(int input)
{
  int digits = 0;
  while (input>0)
  {
    input /= 10;
    digits++;
  }
  printf("Digits: %d \n", digits);
  return digits;
}

int main(void)
{
  int input, c;
  int antal = 0;

  scanf("%d %d", &input, &c);

  int digits = countDigits(input);

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

