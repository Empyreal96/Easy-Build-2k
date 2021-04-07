

/*++

Copyright (c) 1998-2002 Microsoft Corporation

Module Name:

    Http.h

Abstract:

    This header corresponds to the HTTP API specification

Revision History:

--*/


#ifndef __HTTP_H__
#define __HTTP_H__


#include <winsock2.h>
#include <ws2tcpip.h>


#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

//
// Flags for HttpInitialize() and HttpTerminate()
//

//
// HTTP_INITIALIZE_SERVER - Initializes the HTTP API layer and driver for
//                          server applications.
//
// HTTP_INITIALIZE_CONFIG - Initializes the HTTP API layer and driver for
//                          applications that will modify the HTTP
//                          configuration.
//
// Notes -
//
// 1. These flags can be used in combination.
//
// 2. HttpTerminate() must be called for each call to HttpInitialize() made
//    with each flag set when invoking HttpInitialize.  For example, one
//    could make two calls to HttpInitialize() setting HTTP_INITIALIZE_SERVER
//    the first time and HTTP_INITIALIZE_CONFIG the second time.  One call
//    to HttpTerminate() with both flags set suffices to clean up both
//    calls to HttpInitialize().
//

#define HTTP_INITIALIZE_SERVER          0x00000001
#define HTTP_INITIALIZE_CONFIG          0x00000002

//
// Flags for HttpReceiveHttpRequest().
//
// HTTP_RECEIVE_REQUEST_FLAG_COPY_BODY - Specifies that the caller would like
// any available entity body to be copied along with the protocol headers.
//

#define HTTP_RECEIVE_REQUEST_FLAG_COPY_BODY         0x00000001




//
// Flags for HttpSendHttpResponse() and HttpSendResponseEntityBody().
//
// HTTP_SEND_RESPONSE_FLAG_DISCONNECT - Specifies that the network connection
// should be disconnected immediately after sending the response, overriding
// the HTTP protocol's persistent connection features, such as
// "Connection: keep-alive".
//
// HTTP_SEND_RESPONSE_FLAG_MORE_DATA - Specifies that additional entity body
// data will be sent by the caller.
//
// HTTP_SEND_RESPONSE_FLAG_BUFFER_DATA - Specifies that a caller wants the
// response to complete as soon as possible at the cost by buffering partial
// or the entire response.
//

#define HTTP_SEND_RESPONSE_FLAG_DISCONNECT          0x00000001
#define HTTP_SEND_RESPONSE_FLAG_MORE_DATA           0x00000002
#define HTTP_SEND_RESPONSE_FLAG_BUFFER_DATA         0x00000004




//
// Flags for HttpFlushResponseCache().
//
// HTTP_FLUSH_RESPONSE_FLAG_RECURSIVE - Flushes the specified URL and all
// hierarchally-related sub-URLs from the response or fragment cache.
//

#define HTTP_FLUSH_RESPONSE_FLAG_RECURSIVE          0x00000001




//
// Opaque identifiers for various kernel objects.
//

typedef ULONGLONG      HTTP_OPAQUE_ID,         *PHTTP_OPAQUE_ID;

typedef HTTP_OPAQUE_ID HTTP_REQUEST_ID,        *PHTTP_REQUEST_ID;
typedef HTTP_OPAQUE_ID HTTP_CONNECTION_ID,     *PHTTP_CONNECTION_ID;
typedef HTTP_OPAQUE_ID HTTP_RAW_CONNECTION_ID, *PHTTP_RAW_CONNECTION_ID;

#define HTTP_NULL_ID            (0ui64)
#define HTTP_IS_NULL_ID(pid)    (HTTP_NULL_ID == *(pid))
#define HTTP_SET_NULL_ID(pid)   (*(pid) = HTTP_NULL_ID)


//
// This structure defines a file byte range.
//
// If the Length field is HTTP_BYTE_RANGE_TO_EOF then the remainder of the
// file (everything after StartingOffset) is sent.
//

#define HTTP_BYTE_RANGE_TO_EOF ((ULONGLONG)-1)

typedef struct _HTTP_BYTE_RANGE
{
    ULARGE_INTEGER StartingOffset;
    ULARGE_INTEGER Length;

} HTTP_BYTE_RANGE, *PHTTP_BYTE_RANGE;


//
// The type for HTTP protocol version numbers.
//

typedef struct _HTTP_VERSION
{
    USHORT MajorVersion;
    USHORT MinorVersion;

} HTTP_VERSION, *PHTTP_VERSION;


//
// Some useful macros for HTTP protocol version manipulation.
//

#define HTTP_VERSION_UNKNOWN    { 0, 0 }
#define HTTP_VERSION_0_9        { 0, 9 }
#define HTTP_VERSION_1_0        { 1, 0 }
#define HTTP_VERSION_1_1        { 1, 1 }

#define HTTP_SET_VERSION(version, major, minor)             \
do {                                                        \
    (version).MajorVersion = (major);                       \
    (version).MinorVersion = (minor);                       \
} while (0, 0)

#define HTTP_EQUAL_VERSION(version, major, minor)           \
    ((version).MajorVersion == (major) &&                   \
     (version).MinorVersion == (minor))

#define HTTP_GREATER_VERSION(version, major, minor)         \
    ((version).MajorVersion > (major) ||                    \
     ((version).MajorVersion == (major) &&                  \
      (version).MinorVersion > (minor)))

#define HTTP_LESS_VERSION(version, major, minor)            \
    ((version).MajorVersion < (major) ||                    \
     ((version).MajorVersion == (major) &&                  \
      (version).MinorVersion < (minor)))

#define HTTP_NOT_EQUAL_VERSION(version, major, minor)       \
    (!HTTP_EQUAL_VERSION(version, major, minor))

#define HTTP_GREATER_EQUAL_VERSION(version, major, minor)   \
    (!HTTP_LESS_VERSION(version, major, minor))

#define HTTP_LESS_EQUAL_VERSION(version, major, minor)      \
    (!HTTP_GREATER_VERSION(version, major, minor))


//
// The enum type for HTTP verbs.
//

typedef enum _HTTP_VERB
{
    HttpVerbUnparsed,
    HttpVerbUnknown,
    HttpVerbInvalid,
    HttpVerbOPTIONS,
    HttpVerbGET,
    HttpVerbHEAD,
    HttpVerbPOST,
    HttpVerbPUT,
    HttpVerbDELETE,
    HttpVerbTRACE,
    HttpVerbCONNECT,
    HttpVerbTRACK,  // used by Microsoft Cluster Server for a non-logged trace
    HttpVerbMOVE,
    HttpVerbCOPY,
    HttpVerbPROPFIND,
    HttpVerbPROPPATCH,
    HttpVerbMKCOL,
    HttpVerbLOCK,
    HttpVerbUNLOCK,
    HttpVerbSEARCH,

    HttpVerbMaximum

} HTTP_VERB, *PHTTP_VERB;


//
// Symbols for all HTTP/1.1 headers and other tokens. Notice request +
// response values overlap. Make sure you know which type of header array
// you are indexing.
//
// These values are used as offsets into arrays and as token values in
// HTTP_KNOWN_HEADER arrays in HTTP_REQUEST_HEADERS and HTTP_RESPONSE_HEADERS.
//
// See RFC 2616, HTTP/1.1, for further explanation of most of these headers.
//

typedef enum _HTTP_HEADER_ID
{
    HttpHeaderCacheControl          = 0,    // general-header [section 4.5]
    HttpHeaderConnection            = 1,    // general-header [section 4.5]
    HttpHeaderDate                  = 2,    // general-header [section 4.5]
    HttpHeaderKeepAlive             = 3,    // general-header [not in rfc]
    HttpHeaderPragma                = 4,    // general-header [section 4.5]
    HttpHeaderTrailer               = 5,    // general-header [section 4.5]
    HttpHeaderTransferEncoding      = 6,    // general-header [section 4.5]
    HttpHeaderUpgrade               = 7,    // general-header [section 4.5]
    HttpHeaderVia                   = 8,    // general-header [section 4.5]
    HttpHeaderWarning               = 9,    // general-header [section 4.5]

    HttpHeaderAllow                 = 10,   // entity-header  [section 7.1]
    HttpHeaderContentLength         = 11,   // entity-header  [section 7.1]
    HttpHeaderContentType           = 12,   // entity-header  [section 7.1]
    HttpHeaderContentEncoding       = 13,   // entity-header  [section 7.1]
    HttpHeaderContentLanguage       = 14,   // entity-header  [section 7.1]
    HttpHeaderContentLocation       = 15,   // entity-header  [section 7.1]
    HttpHeaderContentMd5            = 16,   // entity-header  [section 7.1]
    HttpHeaderContentRange          = 17,   // entity-header  [section 7.1]
    HttpHeaderExpires               = 18,   // entity-header  [section 7.1]
    HttpHeaderLastModified          = 19,   // entity-header  [section 7.1]


    // Request Headers

    HttpHeaderAccept                = 20,   // request-header [section 5.3]
    HttpHeaderAcceptCharset         = 21,   // request-header [section 5.3]
    HttpHeaderAcceptEncoding        = 22,   // request-header [section 5.3]
    HttpHeaderAcceptLanguage        = 23,   // request-header [section 5.3]
    HttpHeaderAuthorization         = 24,   // request-header [section 5.3]
    HttpHeaderCookie                = 25,   // request-header [not in rfc]
    HttpHeaderExpect                = 26,   // request-header [section 5.3]
    HttpHeaderFrom                  = 27,   // request-header [section 5.3]
    HttpHeaderHost                  = 28,   // request-header [section 5.3]
    HttpHeaderIfMatch               = 29,   // request-header [section 5.3]

    HttpHeaderIfModifiedSince       = 30,   // request-header [section 5.3]
    HttpHeaderIfNoneMatch           = 31,   // request-header [section 5.3]
    HttpHeaderIfRange               = 32,   // request-header [section 5.3]
    HttpHeaderIfUnmodifiedSince     = 33,   // request-header [section 5.3]
    HttpHeaderMaxForwards           = 34,   // request-header [section 5.3]
    HttpHeaderProxyAuthorization    = 35,   // request-header [section 5.3]
    HttpHeaderReferer               = 36,   // request-header [section 5.3]
    HttpHeaderRange                 = 37,   // request-header [section 5.3]
    HttpHeaderTe                    = 38,   // request-header [section 5.3]
    HttpHeaderTranslate             = 39,   // request-header [webDAV, not in rfc 2518]

    HttpHeaderUserAgent             = 40,   // request-header [section 5.3]

    HttpHeaderRequestMaximum        = 41,


    // Response Headers

    HttpHeaderAcceptRanges          = 20,   // response-header [section 6.2]
    HttpHeaderAge                   = 21,   // response-header [section 6.2]
    HttpHeaderEtag                  = 22,   // response-header [section 6.2]
    HttpHeaderLocation              = 23,   // response-header [section 6.2]
    HttpHeaderProxyAuthenticate     = 24,   // response-header [section 6.2]
    HttpHeaderRetryAfter            = 25,   // response-header [section 6.2]
    HttpHeaderServer                = 26,   // response-header [section 6.2]
    HttpHeaderSetCookie             = 27,   // response-header [not in rfc]
    HttpHeaderVary                  = 28,   // response-header [section 6.2]
    HttpHeaderWwwAuthenticate       = 29,   // response-header [section 6.2]

    HttpHeaderResponseMaximum       = 30,


    HttpHeaderMaximum               = 41

} HTTP_HEADER_ID, *PHTTP_HEADER_ID;


//
// Structure defining format of a known HTTP header.
// Name is from HTTP_HEADER_ID.
//

typedef struct _HTTP_KNOWN_HEADER
{
    USHORT RawValueLength;     // in bytes not including the NUL
    PCSTR  pRawValue;

} HTTP_KNOWN_HEADER, *PHTTP_KNOWN_HEADER;

//
// Structure defining format of an unknown header.
//

typedef struct _HTTP_UNKNOWN_HEADER
{
    USHORT NameLength;          // in bytes not including the NUL
    USHORT RawValueLength;      // in bytes not including the NUL
    PCSTR  pName;               // The header name (minus the ':' character)
    PCSTR  pRawValue;           // The header value

} HTTP_UNKNOWN_HEADER, *PHTTP_UNKNOWN_HEADER;


//
// This enum defines a data source for a particular chunk of data.
//

typedef enum _HTTP_DATA_CHUNK_TYPE
{
    HttpDataChunkFromMemory,
    HttpDataChunkFromFileHandle,
    HttpDataChunkFromFragmentCache,

    HttpDataChunkMaximum

} HTTP_DATA_CHUNK_TYPE, *PHTTP_DATA_CHUNK_TYPE;


//
// This structure describes an individual data chunk.
//

typedef struct _HTTP_DATA_CHUNK
{
    //
    // The type of this data chunk.
    //

    HTTP_DATA_CHUNK_TYPE DataChunkType;

    //
    // The data chunk structures, one per supported data chunk type.
    //

    union
    {
        //
        // From-memory data chunk.
        //

        struct
        {
            PVOID pBuffer;
            ULONG BufferLength;

        } FromMemory;

        //
        // From-file handle data chunk.
        //

        struct
        {
            HTTP_BYTE_RANGE ByteRange;
            HANDLE          FileHandle;

        } FromFileHandle;

        //
        // From-fragment cache data chunk.
        //

        struct
        {
            USHORT FragmentNameLength;      // in bytes not including the NUL
            PCWSTR pFragmentName;

        } FromFragmentCache;

    };

} HTTP_DATA_CHUNK, *PHTTP_DATA_CHUNK;


//
// Structure defining format of request headers.
//

typedef struct _HTTP_REQUEST_HEADERS
{
    //
    // The array of unknown HTTP headers and the number of
    // entries in the array.
    //

    USHORT               UnknownHeaderCount;
    PHTTP_UNKNOWN_HEADER pUnknownHeaders;

    // 
    // Trailers - we don't use these currently, reserved for a future release
    //
    USHORT               TrailerCount;   // Reserved, must be 0
    PHTTP_UNKNOWN_HEADER pTrailers;      // Reserved, must be NULL


    //
    // Known headers.
    //

    HTTP_KNOWN_HEADER    KnownHeaders[HttpHeaderRequestMaximum];

} HTTP_REQUEST_HEADERS, *PHTTP_REQUEST_HEADERS;


//
// Structure defining format of response headers.
//

typedef struct _HTTP_RESPONSE_HEADERS
{
    //
    // The array of unknown HTTP headers and the number of
    // entries in the array.
    //

    USHORT               UnknownHeaderCount;
    PHTTP_UNKNOWN_HEADER pUnknownHeaders;

    // 
    // Trailers - we don't use these currently, reserved for a future release
    //
    USHORT               TrailerCount;   // Reserved, must be 0
    PHTTP_UNKNOWN_HEADER pTrailers;      // Reserved, must be NULL

    //
    // Known headers.
    //

    HTTP_KNOWN_HEADER    KnownHeaders[HttpHeaderResponseMaximum];

} HTTP_RESPONSE_HEADERS, *PHTTP_RESPONSE_HEADERS;


//
// Structure defining format of transport address. Use pLocalAddress->sa_family
// to determine whether this is an IPv4 address (AF_INET) or IPv6 (AF_INET6).
// 
// pRemoteAddress->sa_family will be the same as pLocalAddress->sa_family.
//
// SOCKADDRs are always in network order, not host order.
//

typedef struct _HTTP_TRANSPORT_ADDRESS
{
    PSOCKADDR      pRemoteAddress;
    PSOCKADDR      pLocalAddress;

} HTTP_TRANSPORT_ADDRESS, *PHTTP_TRANSPORT_ADDRESS;


//
// Structure defining format of cooked URL.
//

typedef struct _HTTP_COOKED_URL
{
    //
    // Pointers overlap and point into pFullUrl. NULL if not present.
    //

    USHORT FullUrlLength;       // in bytes not including the NUL
    USHORT HostLength;          // in bytes (no NUL)
    USHORT AbsPathLength;       // in bytes (no NUL)
    USHORT QueryStringLength;   // in bytes (no NUL)

    PCWSTR pFullUrl;     // points to "http://hostname:port/abs/.../path?query"
    PCWSTR pHost;        // points to the first char in the hostname
    PCWSTR pAbsPath;     // Points to the 3rd '/' char
    PCWSTR pQueryString; // Points to the 1st '?' char or NULL

} HTTP_COOKED_URL, *PHTTP_COOKED_URL;


//
// An opaque context for URLs
//

typedef ULONGLONG HTTP_URL_CONTEXT;


//
// SSL Client certificate information.
//

typedef struct _HTTP_SSL_CLIENT_CERT_INFO
{
    ULONG   CertFlags;
    ULONG   CertEncodedSize;
    PUCHAR  pCertEncoded;
    HANDLE  Token;
    BOOLEAN CertDeniedByMapper;

} HTTP_SSL_CLIENT_CERT_INFO, *PHTTP_SSL_CLIENT_CERT_INFO;

//
// Data computed during SSL handshake.
//

typedef struct _HTTP_SSL_INFO
{
    USHORT ServerCertKeySize;
    USHORT ConnectionKeySize;
    ULONG  ServerCertIssuerSize;
    ULONG  ServerCertSubjectSize;

    PCSTR  pServerCertIssuer;
    PCSTR  pServerCertSubject;

    PHTTP_SSL_CLIENT_CERT_INFO pClientCertInfo;
    ULONG                      SslClientCertNegotiated;

} HTTP_SSL_INFO, *PHTTP_SSL_INFO;

//
// The structure of an HTTP request.
//

typedef struct _HTTP_REQUEST
{
    //
    // Request flags (see HTTP_REQUEST_FLAG_* definitions below).
    //

    ULONG Flags;

    //
    // An opaque request identifier. These values are used by the driver
    // to correlate outgoing responses with incoming requests.
    //

    HTTP_CONNECTION_ID ConnectionId;
    HTTP_REQUEST_ID    RequestId;

    //
    // The context associated with the URL prefix.
    //

    HTTP_URL_CONTEXT UrlContext;

    //
    // The HTTP version number.
    //

    HTTP_VERSION Version;

    //
    // The request verb.
    //

    HTTP_VERB Verb;

    //
    // The length of the verb string if the Verb field is HttpVerbUnknown.
    //

    USHORT UnknownVerbLength;           // in bytes not including the NUL

    //
    // The length of the raw (uncooked) URL
    //

    USHORT RawUrlLength;                // in bytes not including the NUL

    //
    // Pointer to the verb string if the Verb field is HttpVerbUnknown.
    //

    PCSTR  pUnknownVerb;

    //
    // Pointer to the raw (uncooked) URL
    //

    PCSTR  pRawUrl;

    //
    // The canonicalized Unicode URL
    //

    HTTP_COOKED_URL CookedUrl;

    //
    // Local and remote transport addresses for the connection.
    //

    HTTP_TRANSPORT_ADDRESS Address;

    //
    // The request headers.
    //

    HTTP_REQUEST_HEADERS Headers;

    //
    // The total number of bytes received from network for this request.
    //

    ULONGLONG BytesReceived;

    //
    // pEntityChunks is an array of EntityChunkCount HTTP_DATA_CHUNKs. The
    // entity body is copied only if HTTP_RECEIVE_REQUEST_FLAG_COPY_BODY
    // was passed to HttpReceiveHttpRequest().
    //

    USHORT           EntityChunkCount;
    PHTTP_DATA_CHUNK pEntityChunks;

    //
    // SSL connection information.
    //

    HTTP_RAW_CONNECTION_ID RawConnectionId;
    PHTTP_SSL_INFO         pSslInfo;

} HTTP_REQUEST, *PHTTP_REQUEST;


//
// Values for HTTP_REQUEST::Flags. Zero or more of these may be ORed together.
//
// HTTP_REQUEST_FLAG_MORE_ENTITY_BODY_EXISTS - there is more entity body
// to be read for this request. Otherwise, there is no entity body or
// all of the entity body was copied into pEntityChunks.
//

#define HTTP_REQUEST_FLAG_MORE_ENTITY_BODY_EXISTS   0x00000001




//
// This structure describes an HTTP response.
//

typedef struct _HTTP_RESPONSE
{
    ULONG Flags;

    //
    // The raw HTTP protocol version number. 
    //

    HTTP_VERSION Version;

    //
    // The HTTP status code (e.g., 200).
    //

    USHORT StatusCode;

    //
    // The HTTP reason (e.g., "OK"). This MUST not contain
    // non-ASCII characters (i.e., all chars must be in range 0x20-0x7E).
    //

    USHORT ReasonLength;                 // in bytes not including the '\0'
    PCSTR  pReason;

    //
    // The response headers.
    //

    HTTP_RESPONSE_HEADERS Headers;

    //
    // pEntityChunks points to an array of EntityChunkCount HTTP_DATA_CHUNKs.
    //

    USHORT           EntityChunkCount;
    PHTTP_DATA_CHUNK pEntityChunks;

} HTTP_RESPONSE, *PHTTP_RESPONSE;

//
// Cache control.
//

//
// This enum defines the available cache policies.
//

typedef enum _HTTP_CACHE_POLICY_TYPE
{
    HttpCachePolicyNocache,
    HttpCachePolicyUserInvalidates,
    HttpCachePolicyTimeToLive,

    HttpCachePolicyMaximum

} HTTP_CACHE_POLICY_TYPE, *PHTTP_CACHE_POLICY_TYPE;


//
//  Only cache unauthorized GETs + HEADs.
//

typedef struct _HTTP_CACHE_POLICY
{
    HTTP_CACHE_POLICY_TYPE  Policy;
    ULONG                   SecondsToLive;

} HTTP_CACHE_POLICY, *PHTTP_CACHE_POLICY;




//
// Enum that is used with HttpSetServiceConfiguration(),
// HttpQueryServiceConfiguration(), and HttpDeleteServiceConfiguration() APIs.
//

typedef enum _HTTP_SERVICE_CONFIG_ID
{
    HttpServiceConfigIPListenList,    // Set, Query & Delete.
    HttpServiceConfigSSLCertInfo,     // Set, Query & Delete.
    HttpServiceConfigUrlAclInfo,      // Set, Query & Delete.
    HttpServiceConfigMax

} HTTP_SERVICE_CONFIG_ID, *PHTTP_SERVICE_CONFIG_ID;

//
// Generic Query enum that can be used with HttpQueryServiceConfiguration()
//

typedef enum _HTTP_SERVICE_CONFIG_QUERY_TYPE
{
    HttpServiceConfigQueryExact,
    HttpServiceConfigQueryNext,
    HttpServiceConfigQueryMax

} HTTP_SERVICE_CONFIG_QUERY_TYPE, *PHTTP_SERVICE_CONFIG_QUERY_TYPE;



//
// This data structure is used to define a key of the SSL certificate hash
// store.
//

typedef struct _HTTP_SERVICE_CONFIG_SSL_KEY
{
    PSOCKADDR pIpPort;
} HTTP_SERVICE_CONFIG_SSL_KEY, *PHTTP_SERVICE_CONFIG_SSL_KEY;

//
// This defines a record for the SSL config store.
//

typedef struct _HTTP_SERVICE_CONFIG_SSL_PARAM
{
    ULONG SslHashLength;      // Length of the SSL hash (in bytes)
    PVOID pSslHash;           // Pointer to the SSL hash
    GUID  AppId;              // A unique identifier that can be used to
                              // identify the app that has set this parameter

    PWSTR  pSslCertStoreName; // Store name to read the server certificate
                              // from; defaults to "MY". Certificate must be 
                              // stored in the LOCAL_MACHINE context.

    //
    // The following settings are used only for client certificates
    //

    //
    // DefaultCertCheckMode is a bit flag with the following semantics
    //  0x1     - Client certificate will not be verified for revocation
    //  0x2     - Only cached certificate revocation will be used.
    //  0x4     - Enable use of the DefaultRevocationFreshnessTime setting
    //  0x10000 - No usage check. 

    DWORD  DefaultCertCheckMode;

    //
    // DefaultRevocationFreshnessTime (seconds) - How often to check for 
    // an updated Certificate revocation list (CRL). If this value is 0 
    // then the new CRL is updated only if the previous one expires
    //

    DWORD  DefaultRevocationFreshnessTime;

    //
    // DefaultRevocationUrlRetrievalTimeout (milliseconds) - Timeout on 
    // attempt to retrieve certificate revocation list from the remote URL.
    //

    DWORD  DefaultRevocationUrlRetrievalTimeout;

    //
    // pDefaultSslCtlIdentifier - Restrict the certificate issuers that you 
    // want to trust. Can be a subset of the certificate issuers that are 
    // trusted by the machine.
    //

    PWSTR  pDefaultSslCtlIdentifier;

    // 
    // Store name under LOCAL_MACHINE where Ctl identified by 
    // pDefaultSslCtlIdentifier is stored.
    //

    PWSTR  pDefaultSslCtlStoreName;

    //
    // Default Flags - see HTTP_SERVICE_CONFIG_SSL_FLAG* below.
    //

    DWORD  DefaultFlags;

} HTTP_SERVICE_CONFIG_SSL_PARAM, *PHTTP_SERVICE_CONFIG_SSL_PARAM;

#define HTTP_SERVICE_CONFIG_SSL_FLAG_USE_DS_MAPPER         0x00000001
#define HTTP_SERVICE_CONFIG_SSL_FLAG_NEGOTIATE_CLIENT_CERT 0x00000002
#define HTTP_SERVICE_CONFIG_SSL_FLAG_NO_RAW_FILTER         0x00000004

//
// This data structure is used by HttpSetServiceConfiguration() for the
// config ID HttpServiceConfigSSLCertInfo.  It's used to add a new record
// to the SSL store.
//

typedef struct _HTTP_SERVICE_CONFIG_SSL_SET
{
    HTTP_SERVICE_CONFIG_SSL_KEY   KeyDesc;
    HTTP_SERVICE_CONFIG_SSL_PARAM ParamDesc;
} HTTP_SERVICE_CONFIG_SSL_SET, *PHTTP_SERVICE_CONFIG_SSL_SET;

//
// This data structure is used by HttpQueryServiceConfiguration() for the
// config ID HttpServiceConfigSSLCertInfo. It's used to query a particular
// record from the SSL store.
//
// If QueryType is HttpServiceConfigQueryExact, then one particular record of
// the type HTTP_SERVICE_CONFIG_SSL_SET is returned. If the QueryType is
// HttpServiceConfigQueryNext, then the next instance of
// HTTP_SERVICE_CONFIG_SSL_SET is returned. In such cases, the dwToken field
// represents the cursor. For the first item,  dwToken has to be 0.
// For subsequent items, dwToken has to be incremented by 1,
// until ERROR_NO_MORE_ITEMS is returned.
//

typedef struct _HTTP_SERVICE_CONFIG_SSL_QUERY
{
    HTTP_SERVICE_CONFIG_QUERY_TYPE  QueryDesc;
    HTTP_SERVICE_CONFIG_SSL_KEY     KeyDesc;
    DWORD                           dwToken;
} HTTP_SERVICE_CONFIG_SSL_QUERY, *PHTTP_SERVICE_CONFIG_SSL_QUERY;

//
// Set/Delete IP Listen-Only List record
//
// Used as a parameter to both HttpSetServiceConfiguration() and 
// HttpDeleteServiceConfiguration() functions.
//

typedef struct _HTTP_SERVICE_CONFIG_IP_LISTEN_PARAM
{
    USHORT      AddrLength;
    PSOCKADDR   pAddress;
} HTTP_SERVICE_CONFIG_IP_LISTEN_PARAM, *PHTTP_SERVICE_CONFIG_IP_LISTEN_PARAM;

//
// Query IP Listen-Only List record.
//
// Parameter to HttpQueryServiceConfiguration() for the config ID 
// HttpServiceConfigIPListenList.  On successful return, AddrList 
// contains an array of AddrCount elements.  Caller must provide a
// large enough buffer to hold all elements in one call.
// 
// Caller may determine the type of each returned element by examining
// AddrList[i].ss_family. If it's AF_INET, use ((PSOCKADDR_IN) &AddrList[i]);
// otherwise, for AF_INET6, use ((PSOCKADDR_IN6) &AddrList[i])
// to select the appropriate address type.
// 

typedef struct _HTTP_SERVICE_CONFIG_IP_LISTEN_QUERY
{
    ULONG              AddrCount;
    SOCKADDR_STORAGE   AddrList[ANYSIZE_ARRAY];
} HTTP_SERVICE_CONFIG_IP_LISTEN_QUERY, *PHTTP_SERVICE_CONFIG_IP_LISTEN_QUERY;

//
// URL ACL
//
//
typedef struct _HTTP_SERVICE_CONFIG_URLACL_KEY
{
    PWSTR pUrlPrefix;

} HTTP_SERVICE_CONFIG_URLACL_KEY, *PHTTP_SERVICE_CONFIG_URLACL_KEY;

//
// This defines a record for the SSL config store.
//

typedef struct _HTTP_SERVICE_CONFIG_URLACL_PARAM
{
    PWSTR pStringSecurityDescriptor;
} HTTP_SERVICE_CONFIG_URLACL_PARAM, *PHTTP_SERVICE_CONFIG_URLACL_PARAM;


//
// This data structure is used by HttpSetServiceConfiguration for the config ID
// HttpServiceConfigUrlAclInfo. It is used to add a new record to the URL ACL 
// store.
//

typedef struct _HTTP_SERVICE_CONFIG_URLACL_SET
{
    HTTP_SERVICE_CONFIG_URLACL_KEY   KeyDesc;
    HTTP_SERVICE_CONFIG_URLACL_PARAM ParamDesc;
} HTTP_SERVICE_CONFIG_URLACL_SET, *PHTTP_SERVICE_CONFIG_URLACL_SET;


//
// This data structure is used by HttpQueryServiceConfiguration() for the
// config ID HttpServiceConfigUrlAclInfo. It's used to query a particular
// record from the URL ACL store.
//
// If QueryType is HttpServiceConfigQueryExact, then one particular record of
// the type HTTP_SERVICE_CONFIG_URLACL_SET is returned. If the QueryType is
// HttpServiceConfigQueryNext, then the next instance of
// HTTP_SERVICE_CONFIG_URLACL_SET is returned. In such cases, the dwToken field
// represents the cursor. For the first item,  dwToken has to be 0.
// For subsequent items, dwToken has to be incremented by 1,
// until ERROR_NO_MORE_ITEMS is returned.
//

typedef struct _HTTP_SERVICE_CONFIG_URLACL_QUERY
{
    HTTP_SERVICE_CONFIG_QUERY_TYPE  QueryDesc;
    HTTP_SERVICE_CONFIG_URLACL_KEY  KeyDesc;
    DWORD                           dwToken;
} HTTP_SERVICE_CONFIG_URLACL_QUERY, *PHTTP_SERVICE_CONFIG_URLACL_QUERY;

//
// Define our API linkage.
//

#if !defined(HTTPAPI_LINKAGE)
#define HTTPAPI_LINKAGE DECLSPEC_IMPORT
#endif  // !HTTPAPI_LINKAGE

//
// Initialize/Terminate APIs.
//

//
// Version number to be passed to HttpInitialize(). This is used to ensure
// compatibility between applications and httpapi.dll and http.sys.
//
// This must not be confused with the HTTP Protocol version.
//

typedef struct _HTTPAPI_VERSION 
{
    USHORT HttpApiMajorVersion;
    USHORT HttpApiMinorVersion;

} HTTPAPI_VERSION, *PHTTPAPI_VERSION;

#define HTTPAPI_VERSION_1 {1, 0}


// NOTE: MUST be called once before all other APIs

HTTPAPI_LINKAGE
ULONG
WINAPI
HttpInitialize(
    IN     HTTPAPI_VERSION Version,
    IN     ULONG           Flags,
    IN OUT PVOID           pReserved   // must be NULL
    );

// NOTE: MUST be called after final API call returns.

HTTPAPI_LINKAGE
ULONG
WINAPI
HttpTerminate(
    IN     ULONG Flags,
    IN OUT PVOID pReserved   // must be NULL
    );


//
// HTTP Request Queue handle
//

// NOTE: call CloseHandle() to release.
HTTPAPI_LINKAGE
ULONG
WINAPI
HttpCreateHttpHandle(
    OUT PHANDLE pReqQueueHandle,
    IN  ULONG   Options // Reserved must be 0
    );

//
// SSL APIs.
//

HTTPAPI_LINKAGE
ULONG
WINAPI
HttpReceiveClientCertificate(
    IN  HANDLE                     ReqQueueHandle,
    IN  HTTP_CONNECTION_ID         ConnectionId,
    IN  ULONG                      Flags,
    OUT PHTTP_SSL_CLIENT_CERT_INFO pSslClientCertInfo,
    IN  ULONG                      SslClientCertInfoSize,
    OUT PULONG                     pBytesReceived OPTIONAL,
    IN  LPOVERLAPPED               pOverlapped
    );

//
// URL Configuration APIs.
//

HTTPAPI_LINKAGE
ULONG
WINAPI
HttpAddUrl(
    IN HANDLE    ReqQueueHandle,
    IN PCWSTR    pUrlPrefix,
    IN PVOID     pReserved  // must be NULL
    );

HTTPAPI_LINKAGE
ULONG
WINAPI
HttpRemoveUrl(
    IN HANDLE ReqQueueHandle,
    IN PCWSTR pUrlPrefix
    );


//
// HTTP Server I/O APIs.
//

HTTPAPI_LINKAGE
ULONG
WINAPI
HttpReceiveHttpRequest(
    IN  HANDLE          ReqQueueHandle,
    IN  HTTP_REQUEST_ID RequestId,
    IN  ULONG           Flags,
    OUT PHTTP_REQUEST   pRequestBuffer,
    IN  ULONG           RequestBufferLength,
    OUT PULONG          pBytesReceived OPTIONAL,
    IN  LPOVERLAPPED    pOverlapped    OPTIONAL
    );

HTTPAPI_LINKAGE
ULONG
WINAPI
HttpReceiveRequestEntityBody(
    IN  HANDLE          ReqQueueHandle,
    IN  HTTP_REQUEST_ID RequestId,
    IN  ULONG           Flags,
    OUT PVOID           pBuffer,
    IN  ULONG           BufferLength,
    OUT PULONG          pBytesReceived OPTIONAL,
    IN  LPOVERLAPPED    pOverlapped    OPTIONAL
    );

HTTPAPI_LINKAGE
ULONG
WINAPI
HttpSendHttpResponse(
    IN  HANDLE              ReqQueueHandle,
    IN  HTTP_REQUEST_ID     RequestId,
    IN  ULONG               Flags,
    IN  PHTTP_RESPONSE      pHttpResponse,
    IN  PVOID               pReserved1          OPTIONAL, // must be NULL
    OUT PULONG              pBytesSent          OPTIONAL,
    OUT PVOID               pReserved2          OPTIONAL, // must be NULL
    IN  ULONG               Reserved3           OPTIONAL, // must be 0
    IN  LPOVERLAPPED        pOverlapped         OPTIONAL,
    IN  PVOID               pReserved4          OPTIONAL  // must be NULL 
    );

HTTPAPI_LINKAGE
ULONG
WINAPI
HttpSendResponseEntityBody(
    IN  HANDLE              ReqQueueHandle,
    IN  HTTP_REQUEST_ID     RequestId,
    IN  ULONG               Flags,
    IN  USHORT              EntityChunkCount    OPTIONAL,
    IN  PHTTP_DATA_CHUNK    pEntityChunks       OPTIONAL,
    OUT PULONG              pBytesSent          OPTIONAL,
    OUT PVOID               pReserved1          OPTIONAL, // must be NULL
    IN  ULONG               Reserved2           OPTIONAL, // must be 0
    IN  LPOVERLAPPED        pOverlapped         OPTIONAL,
    IN  PVOID               pReserved3          OPTIONAL  // must be NULL
    );

HTTPAPI_LINKAGE
ULONG
WINAPI
HttpWaitForDisconnect(
    IN  HANDLE                 ReqQueueHandle,
    IN  HTTP_CONNECTION_ID     ConnectionId,
    IN  LPOVERLAPPED           pOverlapped      OPTIONAL
    );


//
// Cache manipulation APIs.
//

HTTPAPI_LINKAGE
ULONG
WINAPI
HttpFlushResponseCache(
    IN HANDLE               ReqQueueHandle,
    IN PCWSTR               pUrlPrefix,
    IN ULONG                Flags,
    IN LPOVERLAPPED         pOverlapped         OPTIONAL
    );

HTTPAPI_LINKAGE
ULONG
WINAPI
HttpAddFragmentToCache(
    IN HANDLE               ReqQueueHandle,
    IN PCWSTR               pUrlPrefix,
    IN PHTTP_DATA_CHUNK     pDataChunk,
    IN PHTTP_CACHE_POLICY   pCachePolicy,
    IN LPOVERLAPPED         pOverlapped         OPTIONAL
    );

HTTPAPI_LINKAGE
ULONG
WINAPI
HttpReadFragmentFromCache(
    IN HANDLE               ReqQueueHandle,
    IN PCWSTR               pUrlPrefix,
    IN PHTTP_BYTE_RANGE     pByteRange          OPTIONAL,
    OUT PVOID               pBuffer,
    IN ULONG                BufferLength,
    OUT PULONG              pBytesRead          OPTIONAL,
    IN LPOVERLAPPED         pOverlapped         OPTIONAL
    );


//
// Server configuration APIs
//

HTTPAPI_LINKAGE
ULONG
WINAPI
HttpSetServiceConfiguration(
    IN HANDLE                  ServiceHandle,         // Reserved, MUST be NULL
    IN HTTP_SERVICE_CONFIG_ID  ConfigId,
    IN PVOID                   pConfigInformation,
    IN ULONG                   ConfigInformationLength,
    IN LPOVERLAPPED            pOverlapped            // Reserved, MUST be NULL
    );

HTTPAPI_LINKAGE
ULONG
WINAPI
HttpDeleteServiceConfiguration(
    IN HANDLE                  ServiceHandle,         // Reserved, MUST be NULL
    IN HTTP_SERVICE_CONFIG_ID  ConfigId,
    IN PVOID                   pConfigInformation,
    IN ULONG                   ConfigInformationLength,
    IN LPOVERLAPPED            pOverlapped            // Reserved, MUST be NULL
    );

HTTPAPI_LINKAGE
ULONG
WINAPI
HttpQueryServiceConfiguration(
    IN  HANDLE                 ServiceHandle,         // Reserved, MUST be NULL
    IN  HTTP_SERVICE_CONFIG_ID ConfigId,
    IN  PVOID                  pInputConfigInformation      OPTIONAL,
    IN  ULONG                  InputConfigInformationLength OPTIONAL,
    IN  OUT PVOID              pOutputConfigInformation,
    IN  ULONG                  OutputConfigInformationLength,
    OUT PULONG                 pReturnLength,
    IN LPOVERLAPPED            pOverlapped            // Reserved, MUST be NULL
    );




#ifdef __cplusplus
}   // extern "C"
#endif  // __cplusplus

#endif // __HTTP_H__
