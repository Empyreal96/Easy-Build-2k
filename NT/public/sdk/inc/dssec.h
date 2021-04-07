#ifndef _DSSEC_H_
#define _DSSEC_H_

#include <aclui.h>  // LPSECURITYINFO


//+---------------------------------------------------------------------------
//
//  Function:   PFNREADOBJECTSECURITY
//
//  Synopsis:   Reads the security descriptor of a DS object
//
//  Arguments:  [IN  LPCWSTR]               --  ADS path of DS Object
//              [IN  SECURITY_INFORMATION]  --  Which SD parts to read
//              [OUT PSECURITY_DESCRIPTOR*] --  Return SD here. Caller frees with LocalFree
//              [IN  LPARAM]                --  Context param
//
//  Return:     HRESULT
//
//----------------------------------------------------------------------------
//
//  Function:   PFNWRITEOBJECTSECURITY
//
//  Synopsis:   Writes a security descriptor to a DS object
//
//  Arguments:  [IN  LPCWSTR]               --  ADS path of DS Object
//              [IN  SECURITY_INFORMATION]  --  Which SD parts to write
//              [OUT PSECURITY_DESCRIPTOR]  --  Security descriptor to write
//              [IN  LPARAM]                --  Context param
//
//  Return:     HRESULT
//
//----------------------------------------------------------------------------
typedef HRESULT (WINAPI *PFNREADOBJECTSECURITY)(LPCWSTR, SECURITY_INFORMATION, PSECURITY_DESCRIPTOR*, LPARAM);
typedef HRESULT (WINAPI *PFNWRITEOBJECTSECURITY)(LPCWSTR, SECURITY_INFORMATION, PSECURITY_DESCRIPTOR, LPARAM);

#define DSSI_READ_ONLY          0x00000001
#define DSSI_NO_ACCESS_CHECK    0x00000002
#define DSSI_NO_EDIT_SACL       0x00000004
#define DSSI_NO_EDIT_OWNER      0x00000008
#define DSSI_IS_ROOT            0x00000010
#define DSSI_NO_FILTER          0x00000020
#define DSSI_NO_READONLY_MESSAGE          0x00000040


//+---------------------------------------------------------------------------
//
//  Function:   DSCreateSecurityPage
//
//  Synopsis:   Creates a Security property page for a DS object
//
//  Arguments:  [IN  pwszObjectPath]    --  Full ADS path of DS object
//              [IN  pwszObjectClass]   --  Class of the object (optional)
//              [IN  dwFlags]           --  Combination of DSSI_* flags
//              [OUT phPage]            --  HPROPSHEETPAGE returned here
//              [IN  pfnReadSD]         --  Optional function for reading SD
//              [IN  pfnWriteSD]        --  Optional function for writing SD
//              [IN  LPARAM]            --  Passed to pfnReadSD/pfnWriteSD
//
//  Return:     HRESULT
//
//----------------------------------------------------------------------------
STDAPI
DSCreateSecurityPage(LPCWSTR pwszObjectPath,
                     LPCWSTR pwszObjectClass,
                     DWORD dwFlags,
                     HPROPSHEETPAGE *phPage,
                     PFNREADOBJECTSECURITY pfnReadSD,
                     PFNWRITEOBJECTSECURITY pfnWriteSD,
                     LPARAM lpContext);

typedef HRESULT (WINAPI *PFNDSCREATESECPAGE)(LPCWSTR,
                                             LPCWSTR,
                                             DWORD,
                                             HPROPSHEETPAGE*,
                                             PFNREADOBJECTSECURITY,
                                             PFNWRITEOBJECTSECURITY,
                                             LPARAM);


#endif  /* _DSSEC_H_ */
