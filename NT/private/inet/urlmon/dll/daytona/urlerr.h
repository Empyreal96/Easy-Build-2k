/*++

Copyright (c) 1995-1997  Microsoft Corporation

Module Name:

    urlmon.mc

Abstract:

    Contains internationalizable message text for URLMON DLL error codes

--*/
 AS: Why are the severity names nonstandard (as per winerror.h?)
     Take out to use default.              
//                                                                           
//                                                                           
// WinINet and protocol specific errors are mapped to one of the following   
// error which are returned in IBSC::OnStopBinding                           
//                                                                           
//                                                                           
//
//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//
#define FACILITY_INTERNET                0xC
#define FACILITY_CODE_DOWNLOAD           0xB


//
// Define the severity codes
//


//
// MessageId: INET_E_INVALID_URL
//
// MessageText:
//
//  The URL is invalid.
//
#define INET_E_INVALID_URL               0x800C0002L

//
// MessageId: INET_E_NO_SESSION
//
// MessageText:
//
//  No Internet session has been established.
//
#define INET_E_NO_SESSION                0x800C0003L

//
// MessageId: INET_E_CANNOT_CONNECT
//
// MessageText:
//
//  Unable to connect to the target server.
//
#define INET_E_CANNOT_CONNECT            0x800C0004L

//
// MessageId: INET_E_RESOURCE_NOT_FOUND
//
// MessageText:
//
//  The system cannot locate the resource specified.
//
#define INET_E_RESOURCE_NOT_FOUND        0x800C0005L

//
// MessageId: INET_E_OBJECT_NOT_FOUND
//
// MessageText:
//
//  The system cannot locate the object specified.
//
#define INET_E_OBJECT_NOT_FOUND          0x800C0006L

//
// MessageId: INET_E_DATA_NOT_AVAILABLE
//
// MessageText:
//
//  No data is available for the requested resource.
//
#define INET_E_DATA_NOT_AVAILABLE        0x800C0007L

//
// MessageId: INET_E_DOWNLOAD_FAILURE
//
// MessageText:
//
//  The download of the specified resource has failed.
//
#define INET_E_DOWNLOAD_FAILURE          0x800C0008L

//
// MessageId: INET_E_AUTHENTICATION_REQUIRED
//
// MessageText:
//
//  Authentication is required to access this resource.
//
#define INET_E_AUTHENTICATION_REQUIRED   0x800C0009L

//
// MessageId: INET_E_NO_VALID_MEDIA
//
// MessageText:
//
//  The server could not recognize the provided mime type.
//
#define INET_E_NO_VALID_MEDIA            0x800C000AL

//
// MessageId: INET_E_CONNECTION_TIMEOUT
//
// MessageText:
//
//  The operation was timed out.
//
#define INET_E_CONNECTION_TIMEOUT        0x800C000BL

//
// MessageId: INET_E_INVALID_REQUEST
//
// MessageText:
//
//  The server did not understand the request, or the request was invalid.
//
#define INET_E_INVALID_REQUEST           0x800C000CL

//
// MessageId: INET_E_UNKNOWN_PROTOCOL
//
// MessageText:
//
//  The specified protocol is unknown.
//
#define INET_E_UNKNOWN_PROTOCOL          0x800C000DL

//
// MessageId: INET_E_SECURITY_PROBLEM
//
// MessageText:
//
//  A security problem occurred.
//
#define INET_E_SECURITY_PROBLEM          0x800C000EL

//
// MessageId: INET_E_CANNOT_LOAD_DATA
//
// MessageText:
//
//  The system could not load the persisted data.
//
#define INET_E_CANNOT_LOAD_DATA          0x800C000FL

//
// MessageId: INET_E_CANNOT_INSTANTIATE_OBJECT
//
// MessageText:
//
//  Unable to instantiate the object.
//
#define INET_E_CANNOT_INSTANTIATE_OBJECT 0x800C0010L

//
// MessageId: INET_E_REDIRECT_FAILED
//
// MessageText:
//
//  A redirection problem occured.
//
#define INET_E_REDIRECT_FAILED           0x800C0014L

