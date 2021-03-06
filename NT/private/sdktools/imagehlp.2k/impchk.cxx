#include <windows.h>
#include <winnt.h>
#include <imagehlp.h>
#include <stdio.h>
#include <stdlib.h>

LOADED_IMAGE Image;

int __cdecl CompareNames (const void *pv1, const void *pv2)
{
    return(strcmp((const char *)pv1, *(const char **)pv2));
}

char *rgszBetaAPIs[] = {
    "ABProviderInit",
    "AddInksetInterval",
    "AddPenDataHRC",
    "AddPenInputHRC",
    "AddPointsPenData",
    "AddPropertySheet",
    "AddWordsHWL",
    "AnimateProc",
    "AssociateProperties",
    "AtomicVirtualEvent",
    "BeginEnumStrokes",
    "BoundingRectFromPoints",
    "BroadcastSystemMessage",
    "BrowseCallbackProc",
    "BuildDisplayTable",
    "CallWndRetProc",
    "CascadeWindows",
    "ChangeIdleRoutine",
    "CharacterToSymbol",
    "CheckColorsInGamut",
    "CheckMenuRadioItem",
    "CheckParameters",
    "CloseIMsgSession",
    "CloseProperties",
    "ColorMatchToTarget",
    "CommConfigDialog",
    "CompactPenData",
    "CompressPenData",
    "ConfigHREC",
    "ConfigRecognizer",
    "CopyImage",
    "CorrectWriting",
    "CorrectWritingEx",
    "CreateColorSpace",
    "CreateCompatibleHRC",
    "CreateHWL",
    "CreateIProp",
    "CreateIconFromResourceEx",
    "CreateInkset",
    "CreateInksetHRCRESULT",
    "CreatePenData",
    "CreatePenDataEx",
    "CreatePenDataHRC",
    "CreatePenDataRegion",
    "CreateTable",
    "CreateToolhelp32Snapshot",
    "DPtoTP",
    "DeleteColorSpace",
    "DeregisterIdleRoutine",
    "DestroyHRC",
    "DestroyHRCRESULT",
    "DestroyHWL",
    "DestroyInkset",
    "DestroyPenData",
    "DictionarySearch",
    "DisplayGuesses",
    "DoDefaultPenInput",
    "DrawAnimatedRects",
    "DrawArrow",
    "DrawCaption",
    "DrawMirrorImage",
    "DrawPenData",
    "DrawPenDataEx",
    "DrawPenDataFmt",
    "DrawState",
    "DrawStateProc",
    "DrawTextEx",
    "DuplicatePenData",
    "EditProperties",
    "EmulatePen",
    "EnableGestureSetHRC",
    "EnableIdleRoutine",
    "EnableSystemDictionaryHRC",
    "EndEnumStrokes",
    "EndPenInputHRC",
    "EnumFontFamExProc",
    "EnumFontFamiliesEx",
    "EnumICMProfiles",
    "EnumICMProfilesProc",
    "EnumProperties",
    "EnumPropertyLibs",
    "EnumPropertySheets",
    "EnumRegisterWordProc",
    "EnumSymbols",
    "EnumSymbolsCallback",
    "ExtractPenDataPoints",
    "ExtractPenDataStrokes",
    "FAbsTimeInInterval",
    "FBadColumnSet",
    "FBadEntryList",
    "FBadProp",
    "FBadPropTag",
    "FBadRestriction",
    "FBadRglpNameID",
    "FBadRglpszW",
    "FBadRow",
    "FBadRowSet",
    "FBadSortOrderSet",
    "FBinFromHex",
    "FEQAbsTime",
    "FEqualNames",
    "FIntervalInInterval",
    "FIntervalXInterval",
    "FLEAbsTime",
    "FLTAbsTime",
    "FPropCompareProp",
    "FPropContainsProp",
    "FPropExists",
    "FindWindowEx",
    "FirstSymbolFromGraph",
    "FlushProperties",
    "FreeImageColorMatcher",
    "FreePadrlist",
    "FreePropertyLib",
    "FreePropertySheets",
    "FreeProws",
    "FtAddFt",
    "FtMulDw",
    "FtMulDwDw",
    "FtNegFt",
    "FtSubFt",
    "FtgRegisterIdleRoutine",
    "GetAlphabetHRC",
    "GetAlphabetPriorityHRC",
    "GetAlternateWordsHRCRESULT",
    "GetAttribIMsgOnIStg",
    "GetBoxMappingHRCRESULT",
    "GetBoxResultsHRC",
    "GetCharacterPlacement",
    "GetClassInfoEx",
    "GetColorSpace",
    "GetCommConfig",
    "GetDefaultCommConfig",
    "GetDeviceGammaRamp",
    "GetFontLanguageInfo",
    "GetGlobalRC",
    "GetGuideHRC",
    "GetHRECFromHRC",
    "GetHotspotsHRCRESULT",
    "GetICMProfile",
    "GetInksetInterval",
    "GetInksetIntervalCount",
    "GetInstance",
    "GetInternationalHRC",
    "GetKeyboardLayout",
    "GetKeyboardLayoutList",
    "GetLogColorSpace",
    "GetMaxResultsHRC",
    "GetMenuDefaultItem",
    "GetMenuItemInfo",
    "GetMenuItemRect",
    "GetPenAppFlags",
    "GetPenAsyncState",
    "GetPenDataAttributes",
    "GetPenDataInfo",
    "GetPenDataStroke",
    "GetPenHwEventData",
    "GetPenInput",
    "GetPenMiscInfo",
    "GetPenResource",
    "GetPointsFromPenData",
    "GetProperties",
    "GetResultsHRC",
    "GetStrokeAttributes",
    "GetStrokeTableAttributes",
    "GetSymbolCount",
    "GetSymbolCountHRCRESULT",
    "GetSymbolMaxLength",
    "GetSymbolsHRCRESULT",
    "GetSysColorBrush",
    "GetSystemPowerStatus",
    "GetTextCharsetInfo",
    "GetVersionPenWin",
    "GetWordlistCoercionHRC",
    "GetWordlistHRC",
    "HPProviderInit",
    "Heap32First",
    "Heap32ListFirst",
    "Heap32ListNext",
    "Heap32Next",
    "HexFromBin",
    "HitTestPenData",
    "HrAddColumnsEx",
    "HrAllocAdviseSink",
    "HrComposeEID",
    "HrComposeMsgID",
    "HrDecomposeEID",
    "HrDecomposeMsgID",
    "HrEntryIDFromSz",
    "HrGetOneProp",
    "HrIStorageFromStream",
    "HrQueryAllRows",
    "HrSetOneProp",
    "HrSzFromEntryID",
    "HrThisThreadAdviseSink",
    "HrValidateIPMSubtree",
    "ImmAssociateContext",
    "ImmConfigureIME",
    "ImmCreateContext",
    "ImmDestroyContext",
    "ImmEnumRegisterWord",
    "ImmEscape",
    "ImmGetCandidateList",
    "ImmGetCandidateListCount",
    "ImmGetCandidateWindow",
    "ImmGetCompositionFont",
    "ImmGetCompositionString",
    "ImmGetCompositionWindow",
    "ImmGetContext",
    "ImmGetConversionList",
    "ImmGetConversionStatus",
    "ImmGetDefaultIMEWnd",
    "ImmGetDescription",
    "ImmGetGuideLine",
    "ImmGetIMEFileName",
    "ImmGetOpenStatus",
    "ImmGetProperty",
    "ImmGetRegisterWordStyle",
    "ImmGetStatusWindowPos",
    "ImmGetVirtualKey",
    "ImmInstallIME",
    "ImmIsIME",
    "ImmIsUIMessage",
    "ImmNotifyIME",
    "ImmRegisterWord",
    "ImmReleaseContext",
    "ImmSetCandidateWindow",
    "ImmSetCompositionFont",
    "ImmSetCompositionString",
    "ImmSetCompositionWindow",
    "ImmSetConversionStatus",
    "ImmSetOpenStatus",
    "ImmSetStatusWindowPos",
    "ImmSimulateHotKey",
    "ImmUnregisterWord",
    "InfoWndProc",
    "InitRC",
    "InputWndProc",
    "InsertMenuItem",
    "InsertPenData",
    "InsertPenDataPoints",
    "InsertPenDataStroke",
    "InstallRecognizer",
    "IsPenAware",
    "IsPenEvent",
    "KKConvert",
    "LPropCompareProp",
    "LaunchWizard",
    "LoadImage",
    "LoadImageColorMatcher",
    "LoadPropertyLib",
    "LoadPropertySheets",
    "LookupIconIdFromDirectoryEx",
    "MAPIAddress",
    "MAPIAdminProfiles",
    "MAPIAllocateBuffer",
    "MAPIAllocateMore",
    "MAPIDeInitIdle",
    "MAPIDeleteMail",
    "MAPIDetails",
    "MAPIFindNext",
    "MAPIFreeBuffer",
    "MAPIGetDefaultMalloc",
    "MAPIInitIdle",
    "MAPIInitialize",
    "MAPILogoff",
    "MAPILogon",
    "MAPILogonEx",
    "MAPIMessage",
    "MAPIOpenFormMgr",
    "MAPIOpenLocalFormContainer",
    "MAPIReadMail",
    "MAPIRecip",
    "MAPIResolveName",
    "MAPISaveMail",
    "MAPISendDocuments",
    "MAPISendMail",
    "MAPIUnintialize",
    "MSProviderInit",
    "MakeAbsTime",
    "MapStorageSCode",
    "MapVirtualKeyEx",
    "MapiFile",
    "MapiFileDesc",
    "MapiFileTagExt",
    "MapiMessage",
    "MapiRecipDesc",
    "MenuItemFromPoint",
    "MessageBoxIndirect",
    "MetricScalePenData",
    "Module32First",
    "Module32Next",
    "OffsetPenData",
    "OpenIMsgOnIStg",
    "OpenIMsgOnIStorage",
    "OpenIMsgSession",
    "OpenProperties",
    "OpenStreamOnFile",
    "OpenTnefStream",
    "OpenTnefStreamEx",
    "PPChangePassword",
    "PPGetPasswordStatus",
    "PaintDesktop",
    "PeekPenInput",
    "PenDataFromBuffer",
    "PenDataToBuffer",
    "PostVirtualKeyEvent",
    "PostVirtualMouseEvent",
    "PpropFindProp",
    "PreprocessMessage",
    "Process32First",
    "Process32Next",
    "ProcessHRC",
    "ProcessWriting",
    "PropCopyMore",
    "PwdChangePassword",
    "PwdGetPasswordStatus",
    "PwdSetPasswordStatus",
    "RTFSync",
    "RawWndProc",
    "ReadHWL",
    "Recognize",
    "RecognizeData",
    "RedisplayPenData",
    "RegisterClassEx",
    "RegisterPenApp",
    "RemovePenDataStrokes",
    "RemovePreprocessInfo",
    "RemovePropertySheet",
    "ResizePenData",
    "ResultsHookHREC",
    "SAVEOPTS",
    "SAndRestriction",
    "SAppTimeArray",
    "SBinary",
    "SBinaryArray",
    "SBitMaskRestriction",
    "SCommentRestriction",
    "SComparePropsRestriction",
    "SContentRestriction",
    "SCurrencyArray",
    "SDateTimeArray",
    "SDoubleArray",
    "SExistRestriction",
    "SGuidArray",
    "SHAddToRecentDocs",
    "SHAppBarMessage",
    "SHBrowseForFolder",
    "SHChangeNotify",
    "SHFileOperation",
    "SHFreeNameMappings",
    "SHGetDesktopFolder",
    "SHGetFileInfo",
    "SHGetInstanceExplorer",
    "SHGetMalloc",
    "SHGetNameMappingCount",
    "SHGetNameMappingPtr",
    "SHGetPathFromIDList",
    "SHGetSpecialFolderLocation",
    "SHLoadInProc",
    "SLPSTRArray",
    "SLargeIntegerArray",
    "SLongArray",
    "SMAPIFormInfoArray",
    "SMAPIFormProp",
    "SMAPIFormPropArray",
    "SMAPIFormPropEnumVal",
    "SMAPIVerb",
    "SMAPIVerbArray",
    "SMessageClassArray",
    "SNotRestriction",
    "SOBailOut",
    "SOBeginTable",
    "SOEndColumnInfo",
    "SOEndFieldInfo",
    "SOEndFontTable",
    "SOEndPalette",
    "SOEndTabStops",
    "SOEndTable",
    "SOGetInfo",
    "SOGetScanLineBuffer",
    "SOPutBitmapHeader",
    "SOPutBreak",
    "SOPutChar",
    "SOPutCharAttr",
    "SOPutCharFontById",
    "SOPutCharFontByName",
    "SOPutCharHeight",
    "SOPutCharX",
    "SOPutColumnInfo",
    "SOPutDataCell",
    "SOPutEmbeddedObject",
    "SOPutField",
    "SOPutFieldInfo",
    "SOPutFontTableEntry",
    "SOPutHdrEntry",
    "SOPutMoreText",
    "SOPutMoreVarField",
    "SOPutPaletteEntry",
    "SOPutParaAlign",
    "SOPutParaIndents",
    "SOPutParaMargins",
    "SOPutParaSpacing",
    "SOPutScanLineData",
    "SOPutSectionName",
    "SOPutSectionType",
    "SOPutSpecialCharX",
    "SOPutSubdocInfo",
    "SOPutTabStop",
    "SOPutTableCellInfo",
    "SOPutTableRowFormat",
    "SOPutTextCell",
    "SOPutVarField",
    "SOPutVectorHeader",
    "SOSetDateBase",
    "SOStartColumnInfo",
    "SOStartFieldInfo",
    "SOStartFontTable",
    "SOStartPalette",
    "SOStartTabStops",
    "SOVectorAttr",
    "SOVectorObject",
    "SOrRestriction",
    "SPropAttrArray",
    "SPropProblem",
    "SPropProblemArray",
    "SPropTagArray",
    "SPropValue",
    "SPropertyRestriction",
    "SRealArray",
    "SRestriction",
    "SRow",
    "SRowSet",
    "SShortArray",
    "SSizeRestriction",
    "SSortOrder",
    "SSortOrderSet",
    "SSubRestriction",
    "STnefProblem",
    "STnefProblemArray",
    "SUUserPopData",
    "SUUserPushData",
    "SUUserRetrieveData",
    "SUUserSaveData",
    "SWStringArray",
    "ScBinFromHexBounded",
    "ScCopyNotifications",
    "ScCopyProps",
    "ScCountNotifications",
    "ScCountProps",
    "ScDupPropset",
    "ScLocalPathFromUNC",
    "ScRelocNotifications",
    "ScRelocProps",
    "ScUNCFromLocalPath",
    "SetAlphabetHRC",
    "SetAlphabetPriorityHRC",
    "SetAttribIMsgOnIStg",
    "SetBoxAlphabetHRC",
    "SetColorSpace",
    "SetCommConfig",
    "SetDefaultCommConfig",
    "SetDeviceGammaRamp",
    "SetGlobalRC",
    "SetGuideHRC",
    "SetICMMode",
    "SetICMProfile",
    "SetInternationalHRC",
    "SetMaxResultsHRC",
    "SetMenuDefaultItem",
    "SetMenuItemInfo",
    "SetMessageExtraInfo",
    "SetPenAppFlags",
    "SetPenHook",
    "SetPenHookCallback",
    "SetPenMiscInfo",
    "SetProperties",
    "SetRecogHook",
    "SetResultsHookHREC",
    "SetStrokeAttributes",
    "SetStrokeTableAttributes",
    "SetSystemPowerState",
    "SetWordlistCoercionHRC",
    "SetWordlistHRC",
    "Shell_NotifyIcon",
    "ShowKeyboard",
    "ShowWindowAsync",
    "StartInking",
    "StartPenInput",
    "StopInking",
    "StopPenInput",
    "SymbolToCharacter",
    "TPtoDP",
    "TargetPoints",
    "Thread32First",
    "Thread32Next",
    "TileWindows",
    "ToAsciiEx",
    "Toolhelp32ReadProcessMemory",
    "TrackPopupMenuEx",
    "TrainContext",
    "TrainHREC",
    "TrainInk",
    "TranslateCharsetInfo",
    "TrimPenData",
    "UnhookResultsHookHREC",
    "UninstallRecognizer",
    "UpdatePenInfo",
    "ValidateParameters",
    "VkKeyScanEx",
    "VwStreamCloseFunc",
    "VwStreamOpenFunc",
    "VwStreamReadFunc",
    "VwStreamReadRecordFunc",
    "VwStreamSectionFunc",
    "VwStreamSeekFunc",
    "VwStreamTellFunc",
    "WrapCompressedRTFStream",
    "WrapStoreEntryID",
    "WriteHWL",
    "XPProviderInit",
    "attAttachRenddata",
    "attConversationID",
    "attFrom",
    "attMAPIProps",
    "attMessageStatus",
    "attOriginalMessageClass",
    "attOwner",
    "attParentID",
    "attPriority",
    "attRecipTable",
    "attSentFor",
    "dwDiffAT",
    "dwDurInterval",
    "lineAccept",
    "lineAddProvider",
    "lineAddToConference",
    "lineAnswer",
    "lineBlindTransfer",
    "lineCallbackFunc",
    "lineClose",
    "lineCompleteCall",
    "lineCompleteTransfer",
    "lineConfigDialog",
    "lineConfigDialogEdit",
    "lineConfigProvider",
    "lineDeallocateCall",
    "lineDevSpecific",
    "lineDevSpecificFeature",
    "lineDial",
    "lineDrop",
    "lineForward",
    "lineGatherDigits",
    "lineGenerateDigits",
    "lineGenerateTone",
    "lineGetAddressCaps",
    "lineGetAddressID",
    "lineGetAddressStatus",
    "lineGetAppPriority",
    "lineGetCallInfo",
    "lineGetCallStatus",
    "lineGetConfRelatedCalls",
    "lineGetCountry",
    "lineGetDevCaps",
    "lineGetDevConfig",
    "lineGetID",
    "lineGetIcon",
    "lineGetLineDevStatus",
    "lineGetNewCalls",
    "lineGetNumRings",
    "lineGetProviderList",
    "lineGetRequest",
    "lineGetStatusMessages",
    "lineGetTranslateCaps",
    "lineHandoff",
    "lineHold",
    "lineInitialize",
    "lineMakeCall",
    "lineMonitorDigits",
    "lineMonitorMedia",
    "lineMonitorTones",
    "lineNegotiateAPIVersion",
    "lineNegotiateExtVersion",
    "lineOpen",
    "linePark",
    "linePickup",
    "linePrepareAddToConference",
    "lineRedirect",
    "lineRegisterRequestRecipient",
    "lineReleaseUserUserInfo",
    "lineRemoveFromConference",
    "lineRemoveProvider",
    "lineSecureCall",
    "lineSendUserUserInfo",
    "lineSetAppPriority",
    "lineSetAppSpecific",
    "lineSetCallParams",
    "lineSetCallPrivilege",
    "lineSetCurrentLocation",
    "lineSetDevConfig",
    "lineSetMediaControl",
    "lineSetMediaMode",
    "lineSetNumRings",
    "lineSetStatusMessages",
    "lineSetTerminal",
    "lineSetTollList",
    "lineSetupConference",
    "lineSetupTransfer",
    "lineShutdown",
    "lineSwapHold",
    "lineTranslateAddress",
    "lineTranslateDialog",
    "lineUncompleteCall",
    "lineUnhold",
    "lineUnpark",
    "phoneCallbackFunc",
    "phoneClose",
    "phoneConfigDialog",
    "phoneDevSpecific",
    "phoneGetButtonInfo",
    "phoneGetData",
    "phoneGetDevCaps",
    "phoneGetDisplay",
    "phoneGetGain",
    "phoneGetHookSwitch",
    "phoneGetID",
    "phoneGetIcon",
    "phoneGetLamp",
    "phoneGetRing",
    "phoneGetStatus",
    "phoneGetStatusMessages",
    "phoneGetVolume",
    "phoneInitialize",
    "phoneNegotiateAPIVersion",
    "phoneNegotiateExtVersion",
    "phoneOpen",
    "phoneSetButtonInfo",
    "phoneSetData",
    "phoneSetDisplay",
    "phoneSetGain",
    "phoneSetHookSwitch",
    "phoneSetLamp",
    "phoneSetRing",
    "phoneSetStatusMessages",
    "phoneSetVolume",
    "phoneShutdown",
    "tapiGetLocationInfo",
    "tapiRequestDrop",
    "tapiRequestMakeCall",
    "tapiRequestMediaCall",
    "ulValidateParameters"
};

BOOL
VerifyImageImports(
    char *ImageName
    );

void __cdecl
main(
    int argc,
    char *argv[]
    )
{
    int i;
    if (argc < 2 ||
        (((argv[1][0] == '/') || (argv[1][0] == '-')) &&
         (argv[1][1] == '?'))) {
        puts("Usage: impchk <imagename>\n"
             "   where <imagename> is the image you want to check for beta API's");
    } else {
        i = 0;
        while (argc > 1) {
            argc--;
            i++;
            printf("Image: \"%s\" should %s marked as Beta\n",
                    argv[i],
                    VerifyImageImports(argv[i]) ? "be" : "not be");
        }
    }
}

BOOL
VerifyImageImports(
    char *ImageName
    )
{
    PIMAGE_IMPORT_DESCRIPTOR Imports;
    PIMAGE_THUNK_DATA tname;
    PIMAGE_THUNK_DATA ThunkNames;
    PIMAGE_IMPORT_BY_NAME ImportName;
    ULONG NumberOfThunks;
    ULONG i, cb;
    UCHAR NameBuffer[ 32 ];
    PIMAGE_NT_HEADERS NtHeaders;
    ULONG ImportSize;
    LPSTR ImportModule;
    BOOL rc = FALSE;

    if (MapAndLoad(ImageName, ".", &Image, TRUE, TRUE)) {
        Image.ModuleName = ImageName;

        //
        // Now locate and walk through and process the images imports
        //

        NtHeaders = ImageNtHeader( (PVOID)Image.MappedAddress );
        if (NtHeaders != NULL) {

            Imports = (PIMAGE_IMPORT_DESCRIPTOR)ImageDirectoryEntryToData(
                                                    (PVOID)Image.MappedAddress,
                                                    FALSE,
                                                    IMAGE_DIRECTORY_ENTRY_IMPORT,
                                                    &ImportSize
                                                    );
            for(;Imports;Imports++) {
                if (!Imports->Name) {
                    break;
                }

                ImportModule = (LPSTR) ImageRvaToVa( (PIMAGE_NT_HEADERS) Image.FileHeader,
                                            Image.MappedAddress,
                                            (ULONG) Imports->Name,
                                            &Image.LastRvaSection);

                if (ImportModule) {

                    ThunkNames = (PIMAGE_THUNK_DATA) ImageRvaToVa(
                                    (PIMAGE_NT_HEADERS)Image.FileHeader,
                                    Image.MappedAddress,
                                    (ULONG) Imports->OriginalFirstThunk,
                                    &Image.LastRvaSection);

                    if (!ThunkNames || ThunkNames->u1.Function == 0) {
                        //
                        // Skip this one if no thunks or first thunk is the terminating null thunk
                        //
                        continue;
                    }

                    //
                    NumberOfThunks = 0;
                    tname = ThunkNames;
                    while (tname->u1.AddressOfData) {
                        NumberOfThunks++;
                        tname++;
                    }

                    tname = ThunkNames;
                    for(i=0;i<NumberOfThunks;i++) {
                        if (!(BOOL)IMAGE_SNAP_BY_ORDINAL(tname->u1.Ordinal)) {
                            ImportName = (PIMAGE_IMPORT_BY_NAME)
                                    ImageRvaToVa((PIMAGE_NT_HEADERS)Image.FileHeader,
                                                 Image.MappedAddress,
                                                 (ULONG)(ULONG_PTR) tname->u1.AddressOfData,
                                                 &Image.LastRvaSection);
                            if (bsearch(ImportName->Name,
                                        rgszBetaAPIs,
                                        sizeof(rgszBetaAPIs) / sizeof(char *),
                                        sizeof(char *),
                                        CompareNames
                                       )) {
                                printf("%s: Imports \"%s\" from \"%s\"\n",
                                        ImageName,
                                        ImportName->Name,
                                        ImportModule);
                                rc = TRUE;
                            }
                        }

                        tname++;
                    }
                }
            }
        }

        UnMapAndLoad(&Image);
    }

    return(rc);
}
