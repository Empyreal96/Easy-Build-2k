/*++ BUILD Version: 0001    // Increment this if a change has global effects

Copyright (c) 1992  Microsoft Corporation

Module Name:

    snmpelmg.h

Abstract:

    Definitions for SNMP Event Log messages.

Author:

    Randy G. Braze  16-October-1994

Revision History:

Notes:



--*/

#ifndef SNMPELMSG_H
#define SNMPELMSG_H


/////////////////////////////////////////////////////////////////////////
//
// Initialization and Registry Messages (1000-1999)
//
/////////////////////////////////////////////////////////////////////////

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


//
// Define the severity codes
//
#define SNMPELEA_WARNING                 0x2
#define SNMPELEA_SUCCESS                 0x0
#define SNMPELEA_INFORMATIONAL           0x1
#define SNMPELEA_ERROR                   0x3


//
// MessageId: SNMPELEA_NO_REGISTRY_PARAMETERS
//
// MessageText:
//
//  Error opening registry for Parameter information; defaults used for all parameters.
//  Return code from RegOpenKeyEx is %1.
//
#define SNMPELEA_NO_REGISTRY_PARAMETERS  0x800003E8L

//
// MessageId: SNMPELEA_NO_REGISTRY_LOG_NAME
//
// MessageText:
//
//  Error opening registry for EventLogFiles information. Extension agent cannot run.
//  Return code from RegOpenKeyEx is %1.
//
#define SNMPELEA_NO_REGISTRY_LOG_NAME    0xC00003E9L

//
// MessageId: SNMPELEA_NO_REGISTRY_EVENT_LOGS
//
// MessageText:
//
//  No Event Logs were specified for event scanning.
//  Extension agent is terminating.
//
#define SNMPELEA_NO_REGISTRY_EVENT_LOGS  0xC00003EAL

//
// MessageId: SNMPELEA_NO_REGISTRY_TRACE_FILE_PARAMETER
//
// MessageText:
//
//  TraceFileName parameter not located in registry;
//  Default trace file used is %1.
//
#define SNMPELEA_NO_REGISTRY_TRACE_FILE_PARAMETER 0x800003EBL

//
// MessageId: SNMPELEA_NO_REGISTRY_TRIM_FLAG_PARAMETER
//
// MessageText:
//
//  TrimFlag parameter not located in registry;
//  Default value used is %1.
//
#define SNMPELEA_NO_REGISTRY_TRIM_FLAG_PARAMETER 0x800003ECL

//
// MessageId: SNMPELEA_NO_REGISTRY_TRIM_MESSAGE_PARAMETER
//
// MessageText:
//
//  TrimMessage parameter not located in registry;
//  Default value used is %1.
//
#define SNMPELEA_NO_REGISTRY_TRIM_MESSAGE_PARAMETER 0x800003EDL

//
// MessageId: SNMPELEA_NO_REGISTRY_TRAP_SIZE_PARAMETER
//
// MessageText:
//
//  MaxTrapSize parameter not located in registry;
//  Default value used is %1.
//
#define SNMPELEA_NO_REGISTRY_TRAP_SIZE_PARAMETER 0x800003EEL

//
// MessageId: SNMPELEA_NO_REGISTRY_THRESHOLDENABLED_PARAMETER
//
// MessageText:
//
//  ThresholdEnabled parameter not located in registry;
//  Default value used is %1.
//
#define SNMPELEA_NO_REGISTRY_THRESHOLDENABLED_PARAMETER 0x800003EFL

//
// MessageId: SNMPELEA_NO_REGISTRY_THRESHOLD_PARAMETER
//
// MessageText:
//
//  Threshold parameter not located in registry;
//  Default value used is %1.
//
#define SNMPELEA_NO_REGISTRY_THRESHOLD_PARAMETER 0x800003F0L

//
// MessageId: SNMPELEA_NO_REGISTRY_THRESHOLDCOUNT_PARAMETER
//
// MessageText:
//
//  ThresholdCount parameter not located in registry;
//  Default value used is %1.
//
#define SNMPELEA_NO_REGISTRY_THRESHOLDCOUNT_PARAMETER 0x800003F1L

//
// MessageId: SNMPELEA_REGISTRY_LOW_THRESHOLDCOUNT_PARAMETER
//
// MessageText:
//
//  ThresholdCount parameter is an invalid value in the registry;
//  Default value used is %1.
//
#define SNMPELEA_REGISTRY_LOW_THRESHOLDCOUNT_PARAMETER 0x800003F2L

//
// MessageId: SNMPELEA_NO_REGISTRY_THRESHOLDTIME_PARAMETER
//
// MessageText:
//
//  ThresholdTime parameter not located in registry;
//  Default value used is %1.
//
#define SNMPELEA_NO_REGISTRY_THRESHOLDTIME_PARAMETER 0x800003F3L

//
// MessageId: SNMPELEA_REGISTRY_LOW_THRESHOLDTIME_PARAMETER
//
// MessageText:
//
//  ThresholdTime parameter is an invalid value in the registry;
//  Default value used is %1.
//
#define SNMPELEA_REGISTRY_LOW_THRESHOLDTIME_PARAMETER 0x800003F4L

//
// MessageId: SNMPELEA_REGISTRY_TRACE_FILE_PARAMETER_TYPE
//
// MessageText:
//
//  TraceFileName parameter is of the wrong type in the registry;
//  Default trace file used is %1.
//
#define SNMPELEA_REGISTRY_TRACE_FILE_PARAMETER_TYPE 0x800003F5L

//
// MessageId: SNMPELEA_REGISTRY_TRACE_LEVEL_PARAMETER_TYPE
//
// MessageText:
//
//  TraceLevel parameter is of the wrong type in the registry;
//  Default trace level used is %1.
//
#define SNMPELEA_REGISTRY_TRACE_LEVEL_PARAMETER_TYPE 0x800003F6L

//
// MessageId: SNMPELEA_NO_REGISTRY_TRACE_LEVEL_PARAMETER
//
// MessageText:
//
//  TraceLevel parameter not located in registry;
//  Default trace level used is %1.
//
#define SNMPELEA_NO_REGISTRY_TRACE_LEVEL_PARAMETER 0x800003F7L

//
// MessageId: SNMPELEA_ERROR_REGISTRY_PARAMETER_ENUMERATE
//
// MessageText:
//
//  Error reading Parameter key information from the registry.
//  Return code from RegEnumValue is %1. Index value is %2.
//  Extension agent terminating.
//
#define SNMPELEA_ERROR_REGISTRY_PARAMETER_ENUMERATE 0xC00003F8L

//
// MessageId: SNMPELEA_ERROR_REGISTRY_LOG_NAME_ENUMERATE
//
// MessageText:
//
//  Error reading EventLogFiles key information from the registry.
//  Return code from RegEnumValue is %1. Index value is %2.
//  Extension agent terminating.
//
#define SNMPELEA_ERROR_REGISTRY_LOG_NAME_ENUMERATE 0xC00003F9L

//
// MessageId: SNMPELEA_NO_REGISTRY_BASEOID_PARAMETER
//
// MessageText:
//
//  No BaseEnterpriseOID parameter found in registry.
//  Extension agent terminating.
//
#define SNMPELEA_NO_REGISTRY_BASEOID_PARAMETER 0xC00003FAL

//
// MessageId: SNMPELEA_NO_REGISTRY_SUPVIEW_PARAMETER
//
// MessageText:
//
//  No SupportedView parameter found in registry.
//  Extension agent terminating.
//
#define SNMPELEA_NO_REGISTRY_SUPVIEW_PARAMETER 0xC00003FBL

//
// MessageId: SNMPELEA_REGISTRY_INIT_ERROR
//
// MessageText:
//
//  Error processing registry parameters.
//  Extension agent terminating.
//
#define SNMPELEA_REGISTRY_INIT_ERROR     0xC00003FCL

//
// MessageId: SNMPELEA_BASEOID_CONVERT_ERROR
//
// MessageText:
//
//  Unable to convert BaseEnterpriseOID from string to ASN.1 OID.
//  Extension agent terminating.
//
#define SNMPELEA_BASEOID_CONVERT_ERROR   0xC00003FDL

//
// MessageId: SNMPELEA_CANT_CONVERT_ENTERPRISE_OID
//
// MessageText:
//
//  Unable to convert EnterpriseOID from string to ASN.1 OID.
//  Trap cannot be sent.
//
#define SNMPELEA_CANT_CONVERT_ENTERPRISE_OID 0xC00003FEL

//
// MessageId: SNMPELEA_SUPVIEW_CONVERT_ERROR
//
// MessageText:
//
//  Unable to convert SupportedView from string to ASN.1 OID.
//  Extension agent terminating.
//
#define SNMPELEA_SUPVIEW_CONVERT_ERROR   0xC00003FFL

//
// MessageId: SNMPELEA_NO_REGISTRY_PRIM_DLL
//
// MessageText:
//
//  Unable to locate ParameterMessageFile for %1. RegOpenKeyEx returned %2.
//
#define SNMPELEA_NO_REGISTRY_PRIM_DLL    0x40000400L

//
// MessageId: SNMPELEA_CANT_LOAD_PRIM_DLL
//
// MessageText:
//
//  Unable to load PrimaryModule %1. LoadLibraryEx returned %2.
//
#define SNMPELEA_CANT_LOAD_PRIM_DLL      0xC0000401L

//
// MessageId: SNMPELEA_SET_VALUE_FAILED
//
// MessageText:
//
//  Unable to set Threshold key in registry. Processing will continue.
//  Return code from RegSetValueEx is %1.
//
#define SNMPELEA_SET_VALUE_FAILED        0x80000402L


/////////////////////////////////////////////////////////////////////////
//
// Control Messages (2000-2999)
//
/////////////////////////////////////////////////////////////////////////

//
// MessageId: SNMPELEA_ERROR_CREATING_STOP_AGENT_EVENT
//
// MessageText:
//
//  Error creating the stop extension agent event.
//  Return code from CreateEvent is %1.
//
#define SNMPELEA_ERROR_CREATING_STOP_AGENT_EVENT 0xC00007D0L

//
// MessageId: SNMPELEA_ERROR_CREATING_STOP_LOG_EVENT
//
// MessageText:
//
//  Error creating the stop log processing routine termination event.
//  Return code from CreateEvent is %1.
//
#define SNMPELEA_ERROR_CREATING_STOP_LOG_EVENT 0xC00007D1L

//
// MessageId: SNMPELEA_ERROR_CREATING_EVENT_NOTIFY_EVENT
//
// MessageText:
//
//  Error creating the log event notification event.
//  Return code from CreateEvent is %1.
//
#define SNMPELEA_ERROR_CREATING_EVENT_NOTIFY_EVENT 0xC00007D2L

//
// MessageId: SNMPELEA_ERROR_CREATING_REG_CHANGE_EVENT
//
// MessageText:
//
//  Error creating the registry key change notify event.
//  Return code from CreateEvent is %1.
//  Initialization will continue, but registry changes will not be updated until SNMP is stopped and restarted.
//
#define SNMPELEA_ERROR_CREATING_REG_CHANGE_EVENT 0x800007D3L

//
// MessageId: SNMPELEA_REG_NOTIFY_CHANGE_FAILED
//
// MessageText:
//
//  RegNotifyChangeKeyValue failed with a return code of %1.
//  Initialization will continue, but registry changes will not be updated until SNMP is stopped and restarted.
//
#define SNMPELEA_REG_NOTIFY_CHANGE_FAILED 0x400007D4L

//
// MessageId: SNMPELEA_ERROR_CREATING_LOG_THREAD
//
// MessageText:
//
//  Error creating the log processing routine service thread.
//  Return code from CreateThread is %1.
//
#define SNMPELEA_ERROR_CREATING_LOG_THREAD 0xC00007D5L

//
// MessageId: SNMPELEA_ERROR_CLOSING_STOP_AGENT_HANDLE
//
// MessageText:
//
//  Error closing the stop agent event handle %1.
//  Return code from CloseHandle is %2.
//
#define SNMPELEA_ERROR_CLOSING_STOP_AGENT_HANDLE 0x800007D6L

//
// MessageId: SNMPELEA_ERROR_CLOSING_STOP_LOG_EVENT_HANDLE
//
// MessageText:
//
//  Error closing the stop log processing routine event handle %1.
//  Return code from CloseHandle is %2.
//
#define SNMPELEA_ERROR_CLOSING_STOP_LOG_EVENT_HANDLE 0x800007D7L

//
// MessageId: SNMPELEA_ERROR_CLOSING_REG_CHANGED_EVENT_HANDLE
//
// MessageText:
//
//  Error closing the registry key changed event handle %1.
//  Return code from CloseHandle is %2.
//
#define SNMPELEA_ERROR_CLOSING_REG_CHANGED_EVENT_HANDLE 0x800007D8L

//
// MessageId: SNMPELEA_ERROR_CLOSING_REG_PARM_KEY
//
// MessageText:
//
//  Error closing the registry Parameter key handle %1.
//  Return code from RegCloseKey is %2.
//
#define SNMPELEA_ERROR_CLOSING_REG_PARM_KEY 0x800007D9L

//
// MessageId: SNMPELEA_ERROR_CLOSING_STOP_LOG_THREAD_HANDLE
//
// MessageText:
//
//  Error closing the stop log processing routine thread handle %1.
//  Return code from CloseHandle is %2.
//
#define SNMPELEA_ERROR_CLOSING_STOP_LOG_THREAD_HANDLE 0x800007DAL

//
// MessageId: SNMPELEA_ERROR_WAIT_AGENT_STOP_EVENT
//
// MessageText:
//
//  Error waiting for extension agent shutdown request event %1.
//  Return code from WaitForSingleObject is %2.
//  Extension agent did not initialize.
//
#define SNMPELEA_ERROR_WAIT_AGENT_STOP_EVENT 0xC00007DBL

//
// MessageId: SNMPELEA_ERROR_SET_AGENT_STOP_EVENT
//
// MessageText:
//
//  Error setting the extension agent shutdown event %1.
//  Return code from SetEvent is %2.
//
#define SNMPELEA_ERROR_SET_AGENT_STOP_EVENT 0xC00007DCL

//
// MessageId: SNMPELEA_ERROR_SET_LOG_STOP_EVENT
//
// MessageText:
//
//  Error setting the log processing routine shutdown event %1.
//  Return code from SetEvent is %2.
//
#define SNMPELEA_ERROR_SET_LOG_STOP_EVENT 0xC00007DDL

//
// MessageId: SNMPELEA_ERROR_TERMINATE_LOG_THREAD
//
// MessageText:
//
//  Error terminating the log processing routine %1.
//  Return code from TerminateThread is %2.
//
#define SNMPELEA_ERROR_TERMINATE_LOG_THREAD 0xC00007DEL

//
// MessageId: SNMPELEA_ERROR_WAIT_LOG_THREAD_STOP
//
// MessageText:
//
//  Error waiting for the log processing routine thread %1 to terminate.
//  Return code from WaitForSingleObject is %2.
//
#define SNMPELEA_ERROR_WAIT_LOG_THREAD_STOP 0x800007DFL

//
// MessageId: SNMPELEA_LOG_THREAD_STOP_WAIT_30
//
// MessageText:
//
//  The log processing routine thread %1 failed to terminate within 30 seconds.
//  Thread will be terminated.
//
#define SNMPELEA_LOG_THREAD_STOP_WAIT_30 0x800007E0L

//
// MessageId: SNMPELEA_WAIT_LOG_STOP_UNKNOWN_RETURN
//
// MessageText:
//
//  An unknown value %2 was returned while waiting for log processing routine thread %1 termination.
//  Thread state is unknown.
//
#define SNMPELEA_WAIT_LOG_STOP_UNKNOWN_RETURN 0x800007E1L

//
// MessageId: SNMPELEA_STARTED
//
// MessageText:
//
//  SNMP Event Log Extension Agent is starting.
//
#define SNMPELEA_STARTED                 0x400007E2L

//
// MessageId: SNMPELEA_ABNORMAL_INITIALIZATION
//
// MessageText:
//
//  SNMP Event Log Extension Agent did not initialize correctly.
//
#define SNMPELEA_ABNORMAL_INITIALIZATION 0xC00007E3L

//
// MessageId: SNMPELEA_STOPPED
//
// MessageText:
//
//  SNMP Event Log Extension Agent has terminated.
//
#define SNMPELEA_STOPPED                 0x400007E4L


/////////////////////////////////////////////////////////////////////////
//
// Main Routine Messages (3000-3999)
//
/////////////////////////////////////////////////////////////////////////

//
// MessageId: SNMPELEA_LOG_HANDLE_INVALID
//
// MessageText:
//
//  Error positioning to end of log file -- handle is invalid.
//  Handle specified is %1.
//
#define SNMPELEA_LOG_HANDLE_INVALID      0xC0000BB8L

//
// MessageId: SNMPELEA_ERROR_LOG_END
//
// MessageText:
//
//  Log file not positioned at end.
//
#define SNMPELEA_ERROR_LOG_END           0x80000BB9L

//
// MessageId: SNMPELEA_ERROR_LOG_BUFFER_ALLOCATE
//
// MessageText:
//
//  Error positioning to end of log file -- log buffer allocation failed.
//  Handle specified is %1.
//
#define SNMPELEA_ERROR_LOG_BUFFER_ALLOCATE 0xC0000BBAL

//
// MessageId: SNMPELEA_ERROR_LOG_GET_OLDEST_RECORD
//
// MessageText:
//
//  Error positioning to end of log file -- can't get oldest log record.
//  Handle specified is %1. Return code from GetOldestEventLogRecord is %2.
//
#define SNMPELEA_ERROR_LOG_GET_OLDEST_RECORD 0xC0000BBBL

//
// MessageId: SNMPELEA_ERROR_LOG_GET_NUMBER_RECORD
//
// MessageText:
//
//  Error positioning to end of log file -- can't get number of log records.
//  Handle specified is %1. Return code from GetNumberOfEventLogRecords is %2.
//
#define SNMPELEA_ERROR_LOG_GET_NUMBER_RECORD 0xC0000BBCL

//
// MessageId: SNMPELEA_ERROR_LOG_SEEK
//
// MessageText:
//
//  Error positioning to end of log file -- seek to end of log failed.
//  Handle specified is %1. Return code from ReadEventLog is %2.
//
#define SNMPELEA_ERROR_LOG_SEEK          0xC0000BBDL

//
// MessageId: SNMPELEA_ERROR_READ_LOG_EVENT
//
// MessageText:
//
//  Error reading log event record.
//  Handle specified is %1. Return code from ReadEventLog is %2.
//
#define SNMPELEA_ERROR_READ_LOG_EVENT    0x80000BBEL

//
// MessageId: SNMPELEA_ERROR_OPEN_EVENT_LOG
//
// MessageText:
//
//  Error opening event log file %1. Log will not be processed.
//  Return code from OpenEventLog is %2.
//
#define SNMPELEA_ERROR_OPEN_EVENT_LOG    0x80000BBFL

//
// MessageId: SNMPELEA_ERROR_PULSE_STOP_LOG_EVENT
//
// MessageText:
//
//  Error pulsing event for log processing routine shutdown event %1.
//  Return code from PulseEvent is %2.
//
#define SNMPELEA_ERROR_PULSE_STOP_LOG_EVENT 0x80000BC0L

//
// MessageId: SNMPELEA_CANT_ALLOCATE_WAIT_EVENT_ARRAY
//
// MessageText:
//
//  Insufficient memory available to allocate the wait event array.
//
#define SNMPELEA_CANT_ALLOCATE_WAIT_EVENT_ARRAY 0xC0000BC1L

//
// MessageId: SNMPELEA_REALLOC_LOG_EVENT_ARRAY
//
// MessageText:
//
//  Insufficient memory available to reallocate the log event array.
//
#define SNMPELEA_REALLOC_LOG_EVENT_ARRAY 0xC0000BC2L

//
// MessageId: SNMPELEA_ALLOC_EVENT
//
// MessageText:
//
//  Insufficient memory available to allocate dynamic variable.
//
#define SNMPELEA_ALLOC_EVENT             0xC0000BC3L

//
// MessageId: SNMPELEA_REALLOC_LOG_NAME_ARRAY
//
// MessageText:
//
//  Insufficient memory available to reallocate the log name array.
//
#define SNMPELEA_REALLOC_LOG_NAME_ARRAY  0xC0000BC4L

//
// MessageId: SNMPELEA_REALLOC_PRIM_HANDLE_ARRAY
//
// MessageText:
//
//  Insufficient memory available to reallocate the PrimaryModule handle array.
//
#define SNMPELEA_REALLOC_PRIM_HANDLE_ARRAY 0xC0000BC5L

//
// MessageId: SNMPELEA_REALLOC_INSERTION_STRINGS_FAILED
//
// MessageText:
//
//  Insufficient memory available to reallocate the insertion strings for secondary parameters.
//  Further secondary substitution has been terminated. Message will be formatted with strings as is.
//
#define SNMPELEA_REALLOC_INSERTION_STRINGS_FAILED 0xC0000BC6L

//
// MessageId: SNMPELEA_THRESHOLD_REACHED
//
// MessageText:
//
//  Performance threshold values have been reached.
//  Trap processing is being quiesed. Further traps will not be sent without operator intervention.
//
#define SNMPELEA_THRESHOLD_REACHED       0x40000BC7L

//
// MessageId: SNMPELEA_THRESHOLD_RESUMED
//
// MessageText:
//
//  Performance threshold values have been restored by operator intervention.
//  Trap processing has been resumed.
//
#define SNMPELEA_THRESHOLD_RESUMED       0x40000BC8L

//
// MessageId: SNMPELEA_THRESHOLD_SET
//
// MessageText:
//
//  Performance threshold values have been set by operator intervention.
//  Current settings indicate performance thresholds have been reached.
//  Trap processing is being quiesed. Further traps will not be sent without operator intervention.
//
#define SNMPELEA_THRESHOLD_SET           0x40000BC9L


/////////////////////////////////////////////////////////////////////////
//
// Log Processing Routine Messages (4000-4999)
//
/////////////////////////////////////////////////////////////////////////

//
// MessageId: SNMPELEA_TRAP_TOO_BIG
//
// MessageText:
//
//  The trap size of the requested event log exceeds the maximum length of an SNMP trap.
//
#define SNMPELEA_TRAP_TOO_BIG            0x80000FA0L

//
// MessageId: SNMPELEA_ERROR_CREATE_LOG_NOTIFY_EVENT
//
// MessageText:
//
//  Error creating event for log event notification.
//  Return code from CreateEvent is %1.
//
#define SNMPELEA_ERROR_CREATE_LOG_NOTIFY_EVENT 0xC0000FA1L

//
// MessageId: SNMPELEA_ERROR_LOG_NOTIFY
//
// MessageText:
//
//  Error requesting notification of change in log event %1.
//  Return code from ElfChangeNotify is %2.
//
#define SNMPELEA_ERROR_LOG_NOTIFY        0xC0000FA2L

//
// MessageId: SNMPELEA_ERROR_WAIT_ARRAY
//
// MessageText:
//
//  Error waiting on event array in log processing event routine.
//  Return code from WaitForMultipleObjects is %1.
//  Extension agent is terminating.
//
#define SNMPELEA_ERROR_WAIT_ARRAY        0xC0000FA3L

//
// MessageId: SNMPELEA_ERROR_CLOSE_WAIT_EVENT_HANDLE
//
// MessageText:
//
//  Error closing an event log wait event handle.
//  Event handle is %1. Return code from CloseHandle is %2.
//
#define SNMPELEA_ERROR_CLOSE_WAIT_EVENT_HANDLE 0xC0000FA4L

//
// MessageId: SNMPELEA_ERROR_LOG_BUFFER_ALLOCATE_BAD
//
// MessageText:
//
//  Error allocating memory for event log buffer.
//  Trap will not be sent.
//
#define SNMPELEA_ERROR_LOG_BUFFER_ALLOCATE_BAD 0x80000FA5L


/////////////////////////////////////////////////////////////////////////
//
// Format Routine Messages (5000-5999)
//
/////////////////////////////////////////////////////////////////////////

//
// MessageId: SNMPELEA_CANT_ALLOCATE_TRAP_BUFFER
//
// MessageText:
//
//  No memory was available to allocate the buffer for the trap to be processed.
//  Trap will not be sent.
//
#define SNMPELEA_CANT_ALLOCATE_TRAP_BUFFER 0x80001388L

//
// MessageId: SNMPELEA_CANT_ALLOCATE_EVENT_TYPE_STORAGE
//
// MessageText:
//
//  No memory was available to allocate the storage for the event type string.
//  Trap will not be sent.
//
#define SNMPELEA_CANT_ALLOCATE_EVENT_TYPE_STORAGE 0x80001389L

//
// MessageId: SNMPELEA_CANT_ALLOCATE_EVENT_CATEGORY_STORAGE
//
// MessageText:
//
//  No memory was available to allocate the storage for the event category string.
//  Trap will not be sent.
//
#define SNMPELEA_CANT_ALLOCATE_EVENT_CATEGORY_STORAGE 0x8000138AL

//
// MessageId: SNMPELEA_CANT_ALLOCATE_COMPUTER_NAME_STORAGE
//
// MessageText:
//
//  No memory was available to allocate the storage for the computer name string.
//  Trap will not be sent.
//
#define SNMPELEA_CANT_ALLOCATE_COMPUTER_NAME_STORAGE 0x8000138BL

//
// MessageId: SNMPELEA_CANT_ALLOCATE_VARBIND_ENTRY_STORAGE
//
// MessageText:
//
//  No memory was available to allocate the buffer for the varbind queue entry structure.
//  Trap will not be sent.
//
#define SNMPELEA_CANT_ALLOCATE_VARBIND_ENTRY_STORAGE 0x8000138CL

//
// MessageId: SNMPELEA_CANT_ALLOC_VARBIND_LIST_STORAGE
//
// MessageText:
//
//  No memory was available to allocate the buffer for the varbind list.
//  Trap will not be sent.
//
#define SNMPELEA_CANT_ALLOC_VARBIND_LIST_STORAGE 0x8000138DL

//
// MessageId: SNMPELEA_CANT_ALLOC_ENTERPRISE_OID
//
// MessageText:
//
//  No memory was available to allocate the buffer for the enterprise OID.
//  Trap will not be sent.
//
#define SNMPELEA_CANT_ALLOC_ENTERPRISE_OID 0x8000138EL

//
// MessageId: SNMPELEA_CANT_ALLOCATE_OID_ARRAY
//
// MessageText:
//
//  No memory was available to allocate the integer array for the enterprise OID.
//  Trap will not be sent.
//
#define SNMPELEA_CANT_ALLOCATE_OID_ARRAY 0x8000138FL

//
// MessageId: SNMPELEA_NON_NUMERIC_OID
//
// MessageText:
//
//  An attempt was made to convert a string to an OID, but the string contained non-numeric values.
//  The OID cannot be created. Trap will not be sent.
//
#define SNMPELEA_NON_NUMERIC_OID         0x80001390L

//
// MessageId: SNMPELEA_TIME_CONVERT_FAILED
//
// MessageText:
//
//  The event log time could not be converted from UCT to local time.
//  GetTimeZoneInformation returned a value of %1. UCT time will be used in this trap.
//
#define SNMPELEA_TIME_CONVERT_FAILED     0x40001391L

//
// MessageId: SNMPELEA_CANT_OPEN_REGISTRY_MSG_DLL
//
// MessageText:
//
//  Unable to open the registry key for event source for %1. RegOpenKeyEx returned %2.
//  Trap will not be sent.
//
#define SNMPELEA_CANT_OPEN_REGISTRY_MSG_DLL 0x80001392L

//
// MessageId: SNMPELEA_CANT_OPEN_REGISTRY_PARM_DLL
//
// MessageText:
//
//  Unable to open the registry key for event source for %1. RegOpenKeyEx returned %2.
//  Trap will not be sent.
//
#define SNMPELEA_CANT_OPEN_REGISTRY_PARM_DLL 0x80001393L

//
// MessageId: SNMPELEA_NO_REGISTRY_MSG_DLL
//
// MessageText:
//
//  Unable to locate EventMessageFile for event source for %1. RegOpenKeyEx returned %2.
//  Trap will not be sent.
//
#define SNMPELEA_NO_REGISTRY_MSG_DLL     0x80001394L

//
// MessageId: SNMPELEA_NO_REGISTRY_PARM_DLL
//
// MessageText:
//
//  Unable to locate ParameterMessageFile for event source for %1. RegOpenKeyEx returned %2.
//
#define SNMPELEA_NO_REGISTRY_PARM_DLL    0x40001395L

//
// MessageId: SNMPELEA_CANT_EXPAND_MSG_DLL
//
// MessageText:
//
//  Unable to expand file name in EventMessageFile for %1. Size needed is %2.
//  Trap will not be sent.
//
#define SNMPELEA_CANT_EXPAND_MSG_DLL     0x80001396L

//
// MessageId: SNMPELEA_CANT_EXPAND_PARM_DLL
//
// MessageText:
//
//  Unable to expand file name in ParameterMessageFile for %1. Size needed is %2.
//
#define SNMPELEA_CANT_EXPAND_PARM_DLL    0x40001397L

//
// MessageId: SNMPELEA_CANT_LOAD_MSG_DLL
//
// MessageText:
//
//  Unable to load file name in EventMessageFile for %1. LoadLibraryEx returned %2.
//  Trap will not be sent.
//
#define SNMPELEA_CANT_LOAD_MSG_DLL       0x80001398L

//
// MessageId: SNMPELEA_CANT_LOAD_PARM_DLL
//
// MessageText:
//
//  Unable to load file name in ParameterMessageFile for %1. LoadLibraryEx returned %2.
//
#define SNMPELEA_CANT_LOAD_PARM_DLL      0x40001399L

//
// MessageId: SNMPELEA_CANT_FORMAT_MSG
//
// MessageText:
//
//  Unable to format message %1. FormatMessage returned %2.
//  Trap will not be sent.
//
#define SNMPELEA_CANT_FORMAT_MSG         0x8000139AL

//
// MessageId: SNMPELEA_ERROR_FREEING_MSG_DLL
//
// MessageText:
//
//  An error occurred freeing message DLL. FreeLibrary returned %1.
//
#define SNMPELEA_ERROR_FREEING_MSG_DLL   0x4000139BL

//
// MessageId: SNMPELEA_SID_UNKNOWN
//
// MessageText:
//
//  Account name could not be located for this event. Unknown will be used.
//  LookupAccountSid returned %1.
//
#define SNMPELEA_SID_UNKNOWN             0x4000139CL

//
// MessageId: SNMPELEA_FREE_LOCAL_FAILED
//
// MessageText:
//
//  Local storage for buffer could not be freed. LocalFree returned %1. Potential memory leak.
//
#define SNMPELEA_FREE_LOCAL_FAILED       0x4000139DL

//
// MessageId: SNMPELEA_CANT_POST_NOTIFY_EVENT
//
// MessageText:
//
//  Unable to post event completion to handle %1. SetEvent returned %2.
//  Trap may not be sent.
//
#define SNMPELEA_CANT_POST_NOTIFY_EVENT  0x8000139EL

//
// MessageId: SNMPELEA_PARM_NOT_FOUND
//
// MessageText:
//
//  ParameterMessageFile did not contain a substitution string for %1. Error code was %2.
//
#define SNMPELEA_PARM_NOT_FOUND          0x4000139FL

//
// MessageId: SNMPELEA_PRIM_NOT_FOUND
//
// MessageText:
//
//  PrimaryModule did not contain a substitution string for %1. Error code was %2.
//  This secondary parameter will be removed.
//
#define SNMPELEA_PRIM_NOT_FOUND          0x400013A0L


/////////////////////////////////////////////////////////////////////////
//
// Format Routine Messages (6000-6999)
//
/////////////////////////////////////////////////////////////////////////

//
// MessageId: SNMPELEA_CREATE_MUTEX_ERROR
//
// MessageText:
//
//  OpenMutex failed for object %1, reason code %2.
//  Trap will not be sent.
//
#define SNMPELEA_CREATE_MUTEX_ERROR      0x80001770L

//
// MessageId: SNMPELEA_MUTEX_ABANDONED
//
// MessageText:
//
//  Mutex object has been abandoned.
//  Trap will not be sent.
//
#define SNMPELEA_MUTEX_ABANDONED         0x80001771L

//
// MessageId: SNMPELEA_RELEASE_MUTEX_ERROR
//
// MessageText:
//
//  Mutex object could not be released. Reason code is %1.
//  Trap may not be sent.
//
#define SNMPELEA_RELEASE_MUTEX_ERROR     0x80001772L

//
// MessageId: SNMPELEA_ERROR_WAIT_UNKNOWN
//
// MessageText:
//
//  WaitForMultipleObjects returned an unknown error condition.
//  Trap will not be sent.
//
#define SNMPELEA_ERROR_WAIT_UNKNOWN      0x80001773L

//
// MessageId: SNMPELEA_GET_EXIT_CODE_THREAD_FAILED
//
// MessageText:
//
//  GetExitCodeThread returned FALSE, reason code is %1.
//
#define SNMPELEA_GET_EXIT_CODE_THREAD_FAILED 0x80001774L

//
// MessageId: SNMPELEA_COUNT_TABLE_ALLOC_ERROR
//
// MessageText:
//
//  Error allocating storage for Count/Time table entry.
//  Trap will not be sent.
//
#define SNMPELEA_COUNT_TABLE_ALLOC_ERROR 0x80001775L

//
// MessageId: SNMPELEA_ERROR_ALLOC_VAR_BIND
//
// MessageText:
//
//  Error allocating storage for variable bindings.
//  Trap will not be sent.
//
#define SNMPELEA_ERROR_ALLOC_VAR_BIND    0x80001776L

//
// MessageId: SNMPELEA_INSERTION_STRING_ARRAY_ALLOC_FAILED
//
// MessageText:
//
//  Error allocating storage for message DLL insertion string array.
//  Trap will not be sent.
//
#define SNMPELEA_INSERTION_STRING_ARRAY_ALLOC_FAILED 0x80001777L

//
// MessageId: SNMPELEA_INSERTION_STRING_LENGTH_ARRAY_ALLOC_FAILED
//
// MessageText:
//
//  Error allocating storage for message DLL insertion string length array.
//  Trap will not be sent.
//
#define SNMPELEA_INSERTION_STRING_LENGTH_ARRAY_ALLOC_FAILED 0x80001778L

//
// MessageId: SNMPELEA_INSERTION_STRING_ALLOC_FAILED
//
// MessageText:
//
//  Error allocating storage for message DLL insertion strings.
//  Trap will not be sent.
//
#define SNMPELEA_INSERTION_STRING_ALLOC_FAILED 0x80001779L

//
// MessageId: SNMPELEA_TOO_MANY_INSERTION_STRINGS
//
// MessageText:
//
//  Too many insertion strings. First %1 used.
//
#define SNMPELEA_TOO_MANY_INSERTION_STRINGS 0x4000177AL

//
// MessageId: SNMPELEA_LOG_EVENT_IGNORED
//
// MessageText:
//
//  Cannot specify SNMP Event Log Extension Agent DLL events as trap generators.
//  This trap is ignored.
//
#define SNMPELEA_LOG_EVENT_IGNORED       0x8000177BL

//
// MessageId: SNMPELEA_CANT_COPY_VARBIND
//
// MessageText:
//
//  Unable to copy varbind entry during trap buffer trimming.
//  Trap will not be sent.
//
#define SNMPELEA_CANT_COPY_VARBIND       0x8000177CL

//
// MessageId: SNMPELEA_TRIM_TRAP_FAILURE
//
// MessageText:
//
//  Attempt to reduce trap buffer size failed.
//  Trap will not be sent.
//
#define SNMPELEA_TRIM_TRAP_FAILURE       0x8000177DL

//
// MessageId: SNMPELEA_TRIM_FAILED
//
// MessageText:
//
//  The amount of data required to be trimmed is larger than the entire trap.
//  Trap will not be sent.
//
#define SNMPELEA_TRIM_FAILED             0x8000177EL


#endif // SNMPELMSG

