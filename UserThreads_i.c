/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Aug 17 19:08:49 2007
 */
/* Compiler settings for C:\VisualCStudy\UserThreads\UserThreads.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_IBarCodeReader = {0x9E0A0ADC,0x3413,0x442C,{0xA4,0x54,0xC4,0xEF,0x58,0x74,0xF8,0xD9}};


const IID LIBID_UserThreadsLib = {0x3E60D31D,0x0B0C,0x46B1,{0xBA,0x00,0x03,0x8E,0x84,0x8B,0xF7,0xC1}};


const CLSID CLSID_BarCodeReader = {0xDE856718,0x3667,0x4989,{0x9D,0xEA,0x20,0x9E,0x39,0x43,0xE0,0x79}};


#ifdef __cplusplus
}
#endif

