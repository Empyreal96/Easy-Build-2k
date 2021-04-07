#ifndef EXDISPID_H_
//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//  Copyright 1995-1998 Microsoft Corporation. All Rights Reserved.
//
//  File: exdispid.h
//
//--------------------------------------------------------------------------


//
// Dispatch IDS for IExplorer Dispatch Events.
//
#define DISPID_BEFORENAVIGATE     100   // this is sent before navigation to give a chance to abort
#define DISPID_NAVIGATECOMPLETE   101   // in async, this is sent when we have enough to show
#define DISPID_STATUSTEXTCHANGE   102
#define DISPID_QUIT               103
#define DISPID_DOWNLOADCOMPLETE   104
#define DISPID_COMMANDSTATECHANGE 105
#define DISPID_DOWNLOADBEGIN      106
#define DISPID_NEWWINDOW          107   // sent when a new window should be created
#define DISPID_PROGRESSCHANGE     108   // sent when download progress is updated
#define DISPID_WINDOWMOVE         109   // sent when main window has been moved
#define DISPID_WINDOWRESIZE       110   // sent when main window has been sized
#define DISPID_WINDOWACTIVATE     111   // sent when main window has been activated
#define DISPID_PROPERTYCHANGE     112   // sent when the PutProperty method is called
#define DISPID_TITLECHANGE        113   // sent when the document title changes
#define DISPID_TITLEICONCHANGE    114   // sent when the top level window icon may have changed.

#define DISPID_FRAMEBEFORENAVIGATE    200
#define DISPID_FRAMENAVIGATECOMPLETE  201
#define DISPID_FRAMENEWWINDOW         204

#define DISPID_BEFORENAVIGATE2      250   // hyperlink clicked on
#define DISPID_NEWWINDOW2           251
#define DISPID_NAVIGATECOMPLETE2    252   // UIActivate new document
#define DISPID_ONQUIT               253
#define DISPID_ONVISIBLE            254   // sent when the window goes visible/hidden
#define DISPID_ONTOOLBAR            255   // sent when the toolbar should be shown/hidden
#define DISPID_ONMENUBAR            256   // sent when the menubar should be shown/hidden
#define DISPID_ONSTATUSBAR          257   // sent when the statusbar should be shown/hidden
#define DISPID_ONFULLSCREEN         258   // sent when kiosk mode should be on/off
#define DISPID_DOCUMENTCOMPLETE     259   // new document goes ReadyState_Complete
#define DISPID_ONTHEATERMODE        260   // sent when theater mode should be on/off
#define DISPID_ONADDRESSBAR         261   // sent when the address bar should be shown/hidden
#define DISPID_WINDOWSETRESIZABLE   262   // sent to set the style of the host window frame
#define DISPID_WINDOWCLOSING        263   // sent before script window.close closes the window 
#define DISPID_WINDOWSETLEFT        264   // sent when the put_left method is called on the WebOC
#define DISPID_WINDOWSETTOP         265   // sent when the put_top method is called on the WebOC
#define DISPID_WINDOWSETWIDTH       266   // sent when the put_width method is called on the WebOC
#define DISPID_WINDOWSETHEIGHT      267   // sent when the put_height method is called on the WebOC 
#define DISPID_CLIENTTOHOSTWINDOW   268   // sent during window.open to request conversion of dimensions
#define DISPID_SETSECURELOCKICON    269   // sent to suggest the appropriate security icon to show
#define DISPID_FILEDOWNLOAD         270   // Fired to indicate the File Download dialog is opening
#define DISPID_NAVIGATEERROR        271   // Fired to indicate the a binding error has occured
#define DISPID_PRIVACYIMPACTEDSTATECHANGE   272  // Fired when the user's browsing experience is impacted
#define DISPID_NEWWINDOW3           273

// Printing events
#define DISPID_PRINTTEMPLATEINSTANTIATION   225   // Fired to indicate that a print template is instantiated
#define DISPID_PRINTTEMPLATETEARDOWN        226   // Fired to indicate that a print templete is completely gone 
#define DISPID_UPDATEPAGESTATUS             227   // Fired to indicate that the spooling status has changed

// define the events for the shell wiwndow list
#define DISPID_WINDOWREGISTERED     200     // Window registered
#define DISPID_WINDOWREVOKED        201     // Window Revoked

#define DISPID_RESETFIRSTBOOTMODE       1
#define DISPID_RESETSAFEMODE            2
#define DISPID_REFRESHOFFLINEDESKTOP    3
#define DISPID_ADDFAVORITE              4
#define DISPID_ADDCHANNEL               5
#define DISPID_ADDDESKTOPCOMPONENT      6
#define DISPID_ISSUBSCRIBED             7
#define DISPID_NAVIGATEANDFIND          8
#define DISPID_IMPORTEXPORTFAVORITES    9
#define DISPID_AUTOCOMPLETESAVEFORM     10
#define DISPID_AUTOSCAN                 11
#define DISPID_AUTOCOMPLETEATTACH       12
#define DISPID_SHOWBROWSERUI            13
#define DISPID_SHELLUIHELPERLAST        13

#define DISPID_ADVANCEERROR             10
#define DISPID_RETREATERROR             11
#define DISPID_CANADVANCEERROR          12
#define DISPID_CANRETREATERROR          13
#define DISPID_GETERRORLINE             14
#define DISPID_GETERRORCHAR             15
#define DISPID_GETERRORCODE             16
#define DISPID_GETERRORMSG              17
#define DISPID_GETERRORURL              18
#define DISPID_GETDETAILSSTATE          19
#define DISPID_SETDETAILSSTATE          20
#define DISPID_GETPERERRSTATE           21
#define DISPID_SETPERERRSTATE           22
#define DISPID_GETALWAYSSHOWLOCKSTATE   23

// Dispatch IDS for ShellFavoritesNameSpace Dispatch Events.
//
#define DISPID_FAVSELECTIONCHANGE       1
#define DISPID_SELECTIONCHANGE          2
#define DISPID_DOUBLECLICK              3
#define DISPID_INITIALIZED              4

#define DISPID_MOVESELECTIONUP          1
#define DISPID_MOVESELECTIONDOWN        2
#define DISPID_RESETSORT                3
#define DISPID_NEWFOLDER                4
#define DISPID_SYNCHRONIZE              5
#define DISPID_IMPORT                   6
#define DISPID_EXPORT                   7
#define DISPID_INVOKECONTEXTMENU        8
#define DISPID_MOVESELECTIONTO          9
#define DISPID_SUBSCRIPTIONSENABLED     10
#define DISPID_CREATESUBSCRIPTION       11
#define DISPID_DELETESUBSCRIPTION       12
#define DISPID_SETROOT                  13
#define DISPID_ENUMOPTIONS              14
#define DISPID_SELECTEDITEM             15
#define DISPID_ROOT                     16
#define DISPID_DEPTH                    17
#define DISPID_MODE                     18
#define DISPID_FLAGS                    19
#define DISPID_TVFLAGS                  20
#define DISPID_NSCOLUMNS                21
#define DISPID_COUNTVIEWTYPES           22
#define DISPID_SETVIEWTYPE              23
#define DISPID_SELECTEDITEMS            24
#define DISPID_EXPAND                   25
#define DISPID_UNSELECTALL              26

#define EXDISPID_H_
#endif // EXDISPID_H_
