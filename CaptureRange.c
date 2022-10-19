#include "CaptureRange.h"
#include <stdlib.h>

static int RangeValue[20][4];

int CmpSamples(const void * Value1,const void * Value2)
{
   return (*(int *)Value1 - *(int *)Value2);
}

int CalcRange(int ContinuedCnt,int RangeCnt,int FirstSample,int LastSample)
{
  if(ContinuedCnt != 0)
  {
    RangeCnt++;
    printf("Range,Readings\n");
    printf("%d - %d, %d",FirstSample,LastSample,ContinuedCnt + 1);
    RangeValue[RangeCnt][0] = FirstSample;
    RangeValue[RangeCnt][1] = LastSample;
    RangeValue[RangeCnt][2] = ContinuedCnt + 1;
  }
 return RangeCnt;
}

int IsConsecutive(int Difference)
{
   int consecutive = 0;
   if((Difference == 0) || (Difference == 1))
      consecutive = 1;
   
   return consecutive;
}
      
   
      
int * DetectRange(int CurrentSamples[],int CurrentSamplesSize)
{
  int ContinuedCnt = 0;
  int Consecutive = 0;
  int RangeCnt = 0;
  int FirstSample = CurrentSamples[0];
  int LastSample = CurrentSamples[0];
  int Index = 0;
  int SampleDiff = 0;
  
  qsort(CurrentSamples,CurrentSamplesSize,sizeof(int),CmpSamples);
  
  for(Index=0;Index<CurrentSamplesSize;Index++)
  {
     SampleDiff = CurrentSamples[Index+1] - CurrentSamples[Index];     
    if(IsConsecutive(SampleDiff) == 1)
    {
       ContinuedCnt++;
       LastSample = CurrentSamples[Index + 1];
    }
    else
    {
      RangeCnt = CalcRange(ContinuedCnt,RangeCnt,FirstSample,LastSample);
      FirstSample = CurrentSamples[Index + 1];
      LastSample =  CurrentSamples[Index];
      ContinuedCnt = 0;
    }
  }
  RangeValue[RangeCnt][3] = RangeCnt;
  return &RangeValue[0][0]; 
}
