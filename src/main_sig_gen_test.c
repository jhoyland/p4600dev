
/* Bring in standard I/O so we can output the PNG to a file */
#include <stdio.h>
#include <visa.h>
#include <stdlib.h>  
  
  
#define VIERRORMSG(V,M) if ((V)!=VI_SUCCESS) { fprintf(stderr, "[ERROR] " M "\n"); exit(1); }  
  
  
int  
main(void)  
{  
  char buf[300];  
  ViSession viDG1022;  
  ViStatus viStatus;  
  ViSession defaultRM;  
  ViFindList fList;
  ViUInt32 numInst;
  ViChar desc[VI_FIND_BUFLEN];
  ViChar resultBuffer[256];
  ViUInt32 resultCount;
  
  printf("DG1022 Test Program\n");  
  // Open session to USB device  
  viStatus=viOpenDefaultRM(&defaultRM);  
  VIERRORMSG(viStatus,"Opening default resource manager");

  viStatus=viFindRsrc(defaultRM,"USB[0-9]::0x0400?*INSTR",&fList,&numInst,desc);
  VIERRORMSG(viStatus,"Finding resources");

    viStatus = viOpen(defaultRM,desc,VI_NULL,VI_NULL,&viDG1022);
    if(viStatus==VI_SUCCESS)
    {
      printf("\nOpened:%s",desc);

      viStatus = viWrite(viDG1022,"*IDN?\n",6,&resultCount);
      sleep(5);
      viStatus = viRead(viDG1022,resultBuffer,256,&resultCount);
      if(viStatus==VI_SUCCESS)
      { 
      printf("\nReturned: %s",resultBuffer);
      viStatus = viWrite(viDG1022,"FUNC SQU\n",9,&resultCount);
      sleep(5);
      VIERRORMSG(viStatus,"Setting sin function");
      viStatus = viWrite(viDG1022,"FREQ 20000\n",11,&resultCount);
      sleep(5);
      VIERRORMSG(viStatus,"Setting frequency");
      viStatus = viWrite(viDG1022,"VOLT:UNIT VPP\n",14,&resultCount);
      sleep(5);
      VIERRORMSG(viStatus,"Setting volt unit");
      viStatus = viWrite(viDG1022,"VOLT 2.5\n",9,&resultCount);
      sleep(5);
      VIERRORMSG(viStatus,"Setting volt output");
      viStatus = viWrite(viDG1022,"VOLT:OFFS 0.5\n",14,&resultCount);
      sleep(5);
      VIERRORMSG(viStatus,"Setting offset");
      viStatus = viWrite(viDG1022,"PHAS 10\n",8,&resultCount);
      sleep(5);
      VIERRORMSG(viStatus,"Setting phase");
      viStatus = viWrite(viDG1022,"OUTP ON\n",8,&resultCount);
      sleep(5);
      VIERRORMSG(viStatus,"Turning on output");
      viStatus = viWrite(viDG1022,"APPL?\n",6,&resultCount);
      sleep(5);
    }
    else
    {
      printf("\nError");
    }

    }


    viClose(viDG1022);
    viClose(fList);
    viClose(defaultRM);
  
  return(0);  
}  