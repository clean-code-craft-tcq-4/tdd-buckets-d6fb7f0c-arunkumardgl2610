#include <math.h>
#include <stdio.h>

#define invalid -1

int ConvertA2DData(int MaxAmp,int A2DValue,int BitResolution)
{
  int Ampere = invalid;
  A2DValue = abs(A2DValue);
  int MaxA2DValue = pow(2,BitResolution) - 2;
  
  if(A2DValue <= MaxA2DValue)
  {
    float ConvertedValue = (float)MaxAmp * (float)A2DValue / (float)MaxA2DValue;
    Ampere = round(ConvertedValue);
  }
  return Ampere;
}

void ConvertA2DToAmpere(int CurrentValueArray[],int ArraySize,int MaxAmp,int BitResolution,int *AmpereArray)
{
  int Count = 0;
  for(int Index=0;Index < ArraySize;Index++)
  {
    int Ampere = ConvertA2DData(MaxAmp,CurrentValueArray[Index],BitResolution);
    
    if(Ampere != -1)
    {
      AmpereArray[Count] = Ampere;
      Count++;
    }
  }
}
