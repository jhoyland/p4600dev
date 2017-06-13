
/* Bring in standard I/O so we can output the PNG to a file */
#include <stdio.h>
#include <visa.h>
#include <stdlib.h>  
  
  
#define VIERRORMSG(V,M) if ((V)!=VI_SUCCESS) { fprintf(stderr, "[ERROR] " M "\n"); exit(1); }  

char buf[300];  
ViSession viDG1022;  
ViStatus viStatus;  
ViSession defaultRM;  
ViFindList fList;
ViUInt32 numInst;
ViChar desc[VI_FIND_BUFLEN];
ViChar resultBuffer[256];
ViUInt32 resultCount;

int initialization(void)
{
  viStatus=viOpenDefaultRM(&defaultRM);  
  VIERRORMSG(viStatus,"Opening default resource manager");

  viStatus=viFindRsrc(defaultRM,"USB[0-9]::0x0400?*INSTR",&fList,&numInst,desc);
  VIERRORMSG(viStatus,"Finding resources");

  sleep(5);

  viStatus = viOpen(defaultRM,desc,VI_NULL,VI_NULL,&viDG1022);  

  sleep(5);

  if(viStatus==VI_SUCCESS)
  {
    printf("\nOpened:%s",desc);

    viStatus = viWrite(viDG1022,"*IDN?\n",6,&resultCount);
    sleep(5);
    viStatus = viRead(viDG1022,resultBuffer,256,&resultCount);
    if(viStatus==VI_SUCCESS)
    { 
      printf("\nReturned: %s",resultBuffer);
    }
    else
    {
      printf("\nError!\n");

      viClose(viDG1022);
      viClose(fList);
      viClose(defaultRM);

      return 1;
    }

  }

  return 0;
}

int 
setup(void)
{
  sleep(2);
  viStatus = viWrite(viDG1022,"APPL:SIN 20000,1,0\n",20,&resultCount);
  sleep(5);
  VIERRORMSG(viStatus,"Setting sin function");
  viStatus = viWrite(viDG1022,"OUTP ON\n",8,&resultCount);
  sleep(5);
  VIERRORMSG(viStatus,"Setting volt output");\
  return 0;
}

int
loop(void)
{
  double f0 = 20000;
  double df = 100000;
  double f = f0;
  char fbuff[22];
  for(int i = 1; i<=10; i++)
  {
    printf("\nSetting frequency = %0.f\n",f);
    sprintf(fbuff,"APPL:SIN %.0f,1,0\n",f);
    viStatus = viWrite(viDG1022,fbuff,22,&resultCount);
    sleep(1);
    f = f + df;
  }
  return 0;
}

int
cleanup(void)
{
  viStatus = viWrite(viDG1022,"OUTP OFF\n",8,&resultCount);
  sleep(2);
  VIERRORMSG(viStatus,"Setting volt output");\

      viClose(viDG1022);
      viClose(fList);
      viClose(defaultRM);
}

  
int  
main(void)  
{  

  
  printf("DG1022 Test Program\n");  
  // Open session to USB device  



  int r = 0;
  r = initialization();
  if(!r) r = setup();
  if(!r) r = loop();
  r = cleanup();



  
  return(0);  
}  