/*
* 
* Copyright (c) 1998,1999 Microsoft Corporation. All rights reserved.
* 
*/
//                                                                           
//                                                                           
// MSXML specific errors                           
//                                                                           
//                                                                           
//                                                                           
//                                                                           
// New MSXML specific errors                           
//                                                                           
//                                                                           
// -------- READ ME !!!! -------------
//
// The broken unix mc compiler (a perl script) needs the symbolic name
// and Severity on the same lone as the Message ID, to do otherwise will break
// it. Language can be on a seperate line
//
// -----------------------------------


// Hack to get rid of build warning
#ifdef FACILITY_INTERNET
#undef FACILITY_INTERNET
#endif

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


//
// Define the severity codes
//


//
// MessageId: XML_ERROR_MASK
//
// MessageText:
//
//  XML_ERROR_MASK
//
#define XML_ERROR_MASK                   0xC00CE000L

//
// MessageId: XML_IOERROR
//
// MessageText:
//
//  Error opening input file: '%1'.
//
#define XML_IOERROR                      0xC00CE001L

//
// MessageId: XML_ENTITY_UNDEFINED
//
// MessageText:
//
//  Reference to undefined entity '%1'.
//
#define XML_ENTITY_UNDEFINED             0xC00CE002L

//
// MessageId: XML_INFINITE_ENTITY_LOOP
//
// MessageText:
//
//  Entity '%1' contains an infinite entity reference loop.
//
#define XML_INFINITE_ENTITY_LOOP         0xC00CE003L

//
// MessageId: XML_NDATA_INVALID_PE
//
// MessageText:
//
//  Cannot use the NDATA keyword in a parameter entity declaration.
//
#define XML_NDATA_INVALID_PE             0xC00CE004L

//
// MessageId: XML_REQUIRED_NDATA
//
// MessageText:
//
//  Cannot use a general parsed entity '%1' as the value for attribute '%2'.
//
#define XML_REQUIRED_NDATA               0xC00CE005L

//
// MessageId: XML_NDATA_INVALID_REF
//
// MessageText:
//
//  Cannot use unparsed entity '%1' in an entity reference.
//
#define XML_NDATA_INVALID_REF            0xC00CE006L

//
// MessageId: XML_EXTENT_IN_ATTR
//
// MessageText:
//
//  Cannot reference an external general parsed entity '%1' in an attribute value.
//
#define XML_EXTENT_IN_ATTR               0xC00CE007L

//
// MessageId: XML_STOPPED_BY_USER
//
// MessageText:
//
//  XML parser stopped by user.
//
#define XML_STOPPED_BY_USER              0xC00CE008L

//
// MessageId: XML_PARSING_ENTITY
//
// MessageText:
//
//  Error while parsing entity '%1'. %2
//
#define XML_PARSING_ENTITY               0xC00CE009L

//
// MessageId: XML_E_MISSING_PE_ENTITY
//
// MessageText:
//
//  Parameter entity must be defined before it is used.
//
#define XML_E_MISSING_PE_ENTITY          0xC00CE00AL

//
// MessageId: XML_E_MIXEDCONTENT_DUP_NAME
//
// MessageText:
//
//  The same name must not appear more than once in a single mixed-content declaration: '%1'. 
//
#define XML_E_MIXEDCONTENT_DUP_NAME      0xC00CE00BL

//
// MessageId: XML_NAME_COLON
//
// MessageText:
//
//  Entity, EntityRef, PI, Notation names, or NMToken cannot contain a colon.
//
#define XML_NAME_COLON                   0xC00CE00CL

//
// MessageId: XML_ELEMENT_UNDECLARED
//
// MessageText:
//
//  The element '%1' is used but not declared in the DTD/Schema.
//
#define XML_ELEMENT_UNDECLARED           0xC00CE00DL

//
// MessageId: XML_ELEMENT_ID_NOT_FOUND
//
// MessageText:
//
//  The attribute '%1' references the ID '%2' which is not defined anywhere in the document.
//
#define XML_ELEMENT_ID_NOT_FOUND         0xC00CE00EL

//
// MessageId: XML_DEFAULT_ATTRIBUTE
//
// MessageText:
//
//  Error in default attribute value defined in DTD/Schema.
//
#define XML_DEFAULT_ATTRIBUTE            0xC00CE00FL

//
// MessageId: XML_XMLNS_RESERVED
//
// MessageText:
//
//  Reserved namespace '%1' can not be redeclared.
//
#define XML_XMLNS_RESERVED               0xC00CE010L

//
// MessageId: XML_EMPTY_NOT_ALLOWED
//
// MessageText:
//
//  Element cannot be empty according to the DTD/Schema.
//
#define XML_EMPTY_NOT_ALLOWED            0xC00CE011L

//
// MessageId: XML_ELEMENT_NOT_COMPLETE
//
// MessageText:
//
//  Element content is incomplete according to the DTD/Schema.
//
#define XML_ELEMENT_NOT_COMPLETE         0xC00CE012L

//
// MessageId: XML_ROOT_NAME_MISMATCH
//
// MessageText:
//
//  The name of the top most element must match the name of the DOCTYPE declaration.
//
#define XML_ROOT_NAME_MISMATCH           0xC00CE013L

//
// MessageId: XML_INVALID_CONTENT
//
// MessageText:
//
//  Element content is invalid according to the DTD/Schema.
//
#define XML_INVALID_CONTENT              0xC00CE014L

//
// MessageId: XML_ATTRIBUTE_NOT_DEFINED
//
// MessageText:
//
//  The attribute '%1' on this element is not defined in the DTD/Schema.
//
#define XML_ATTRIBUTE_NOT_DEFINED        0xC00CE015L

//
// MessageId: XML_ATTRIBUTE_FIXED
//
// MessageText:
//
//  Attribute '%1' has a value which does not match the fixed value defined in the DTD/Schema.
//
#define XML_ATTRIBUTE_FIXED              0xC00CE016L

//
// MessageId: XML_ATTRIBUTE_VALUE
//
// MessageText:
//
//  Attribute '%1' has an invalid value according to the DTD/Schema.
//
#define XML_ATTRIBUTE_VALUE              0xC00CE017L

//
// MessageId: XML_ILLEGAL_TEXT
//
// MessageText:
//
//  Text is not allowed in this element according to DTD/Schema.
//
#define XML_ILLEGAL_TEXT                 0xC00CE018L

//
// MessageId: XML_MULTI_FIXED_VALUES
//
// MessageText:
//
//  An attribute declaration cannot contain multiple fixed values: '%1'.
//
#define XML_MULTI_FIXED_VALUES           0xC00CE019L

//
// MessageId: XML_NOTATION_DEFINED
//
// MessageText:
//
//  The notation '%1' is already declared.
//
#define XML_NOTATION_DEFINED             0xC00CE01AL

//
// MessageId: XML_ELEMENT_DEFINED
//
// MessageText:
//
//  The element '%1' is already declared.
//
#define XML_ELEMENT_DEFINED              0xC00CE01BL

//
// MessageId: XML_ELEMENT_UNDEFINED
//
// MessageText:
//
//  Reference to undeclared element: '%1'.
//
#define XML_ELEMENT_UNDEFINED            0xC00CE01CL

//
// MessageId: XML_XMLNS_UNDEFINED
//
// MessageText:
//
//  Reference to undeclared namespace prefix: '%1'.
//
#define XML_XMLNS_UNDEFINED              0xC00CE01DL

//
// MessageId: XML_XMLNS_FIXED
//
// MessageText:
//
//  Attribute '%1' must be a #FIXED attribute.
//
#define XML_XMLNS_FIXED                  0xC00CE01EL

//
// MessageId: XML_E_UNKNOWNERROR
//
// MessageText:
//
//  Unknown error: %1.
//
#define XML_E_UNKNOWNERROR               0xC00CE01FL

//
// MessageId: XML_REQUIRED_ATTRIBUTE_MISSING
//
// MessageText:
//
//  Required attribute '%1' is missing.
//
#define XML_REQUIRED_ATTRIBUTE_MISSING   0xC00CE020L

//
// MessageId: XML_MISSING_NOTATION
//
// MessageText:
//
//  Declaration '%1' contains reference to undefined notation '%2'.
//
#define XML_MISSING_NOTATION             0xC00CE021L

//
// MessageId: XML_ATTLIST_DUPLICATED_ID
//
// MessageText:
//
//  Cannot define multiple ID attributes on the same element.
//
#define XML_ATTLIST_DUPLICATED_ID        0xC00CE022L

//
// MessageId: XML_ATTLIST_ID_PRESENCE
//
// MessageText:
//
//  An attribute of type ID must have a declared default of #IMPLIED or #REQUIRED.
//
#define XML_ATTLIST_ID_PRESENCE          0xC00CE023L

//
// MessageId: XML_XMLLANG_INVALIDID
//
// MessageText:
//
//  The language ID "%1" is invalid.
//
#define XML_XMLLANG_INVALIDID            0xC00CE024L

//
// MessageId: XML_PUBLICID_INVALID
//
// MessageText:
//
//  The public ID "%1" is invalid.
//
#define XML_PUBLICID_INVALID             0xC00CE025L

//
// MessageId: XML_DTD_EXPECTING
//
// MessageText:
//
//  Expecting: %1.
//
#define XML_DTD_EXPECTING                0xC00CE026L

//
// MessageId: XML_NAMESPACE_URI_EMPTY
//
// MessageText:
//
//  Only a default namespace can have an empty URI.
//
#define XML_NAMESPACE_URI_EMPTY          0xC00CE027L

//
// MessageId: XML_LOAD_EXTERNALENTITY
//
// MessageText:
//
//  Could not load '%1'.
//
#define XML_LOAD_EXTERNALENTITY          0xC00CE028L

//
// MessageId: XML_BAD_ENCODING
//
// MessageText:
//
//  Unable to save character to '%1' encoding.
//
#define XML_BAD_ENCODING                 0xC00CE029L

//
// Schema Error Messages
//
//
// MessageId: SCHEMA_ATTRIBUTEVALUE_NOSUPPORT
//
// MessageText:
//
//  A namespace was found but not supported at current location.
//
#define SCHEMA_ATTRIBUTEVALUE_NOSUPPORT  0xC00CE100L

//
// MessageId: SCHEMA_SCHEMAROOT_EXPECTED
//
// MessageText:
//
//  Incorrect definition for the root element in schema.
//
#define SCHEMA_SCHEMAROOT_EXPECTED       0xC00CE101L

//
// MessageId: SCHEMA_ELEMENT_NOSUPPORT
//
// MessageText:
//
//  Element "%1" is not allowed in this context.
//
#define SCHEMA_ELEMENT_NOSUPPORT         0xC00CE102L

//
// MessageId: SCHEMA_ETNAME_MISSING
//
// MessageText:
//
//  An ElementType declaration must contain a "name" attribute.
//
#define SCHEMA_ETNAME_MISSING            0xC00CE103L

//
// MessageId: SCHEMA_ETYPE_MISSING
//
// MessageText:
//
//  An element declaration must contain a "type" attribute.
//
#define SCHEMA_ETYPE_MISSING             0xC00CE104L

//
// MessageId: SCHEMA_ETORDER_UNKNOWN
//
// MessageText:
//
//  Schema only supports order type "seq", "one" and "many".
//
#define SCHEMA_ETORDER_UNKNOWN           0xC00CE105L

//
// MessageId: SCHEMA_ELEMENTDT_NOSUPPORT
//
// MessageText:
//
//  Content must be "textOnly" when using datatype on an Element Type.
//
#define SCHEMA_ELEMENTDT_NOSUPPORT       0xC00CE106L

//
// MessageId: SCHEMA_ETORDER_DISABLED
//
// MessageText:
//
//  Order must be "many" when content is "mixed".
//
#define SCHEMA_ETORDER_DISABLED          0xC00CE107L

//
// MessageId: SCHEMA_ETCONTENT_UNKNOWN
//
// MessageText:
//
//  Content must be of type "empty","eltOnly","textOnly" or "mixed".
//
#define SCHEMA_ETCONTENT_UNKNOWN         0xC00CE108L

//
// MessageId: SCHEMA_ETMODEL_UNKNOWN
//
// MessageText:
//
//  The value of model must be either "open" or "closed".
//
#define SCHEMA_ETMODEL_UNKNOWN           0xC00CE109L

//
// MessageId: SCHEMA_ELEMENT_DISABLED
//
// MessageText:
//
//  Cannot contain child elements because content is set to "textOnly".
//
#define SCHEMA_ELEMENT_DISABLED          0xC00CE10AL

//
// MessageId: SCHEMA_ELEMENT_MISSING
//
// MessageText:
//
//  Must provide at least one "element" in a group.
//
#define SCHEMA_ELEMENT_MISSING           0xC00CE10BL

//
// MessageId: SCHEMA_ATTRIBUTE_NOTSUPPORT
//
// MessageText:
//
//  The attribute "%1" on an %2 is not supported.
//
#define SCHEMA_ATTRIBUTE_NOTSUPPORT      0xC00CE10CL

// AttributeType & attribute
//
// MessageId: SCHEMA_ATNAME_MISSING
//
// MessageText:
//
//  AttributeType declaration must contain a "name" attribute.
//
#define SCHEMA_ATNAME_MISSING            0xC00CE10DL

//
// MessageId: SCHEMA_ATNAME_DUPLICATED
//
// MessageText:
//
//  Duplicated attribute declaration.  
//
#define SCHEMA_ATNAME_DUPLICATED         0xC00CE10EL

//
// MessageId: SCHEMA_ATREQUIRED_INVALID
//
// MessageText:
//
//  Invalid value for "required" attribute.
//
#define SCHEMA_ATREQUIRED_INVALID        0xC00CE111L

//
// MessageId: SCHEMA_DTTYPE_UNKNOWN
//
// MessageText:
//
//  Unknown Attribute datatype.
//
#define SCHEMA_DTTYPE_UNKNOWN            0xC00CE112L

//
// MessageId: SCHEMA_DTTYPE_DUPLICATED
//
// MessageText:
//
//  Duplicated datatype declaration.
//
#define SCHEMA_DTTYPE_DUPLICATED         0xC00CE113L

//
// MessageId: SCHEMA_ENUMERATION_MISSING
//
// MessageText:
//
//  An element with a "values" attribute must contain a type attribute of the value "enumeration".
//
#define SCHEMA_ENUMERATION_MISSING       0xC00CE114L

//
// MessageId: SCHEMA_DTVALUES_MISSING
//
// MessageText:
//
//  Must provide a "values" attribute on an element that contains a type attribute of the value "enumeration".
//
#define SCHEMA_DTVALUES_MISSING          0xC00CE115L

//
// MessageId: SCHEMA_ATYPE_MISSING
//
// MessageText:
//
//  Attribute declaration must contain a "type" attribute.
//
#define SCHEMA_ATYPE_MISSING             0xC00CE116L

//
// MessageId: SCHEMA_ATYPE_UNDECLARED
//
// MessageText:
//
//  The specified attribute must first be declared using an AttributeType declaration.
//
#define SCHEMA_ATYPE_UNDECLARED          0xC00CE117L

//
// MessageId: SCHEMA_GROUP_DISABLED
//
// MessageText:
//
//  A "group" is not allowed within an ElementType that has a "textOnly" content model.
//
#define SCHEMA_GROUP_DISABLED            0xC00CE118L

//
// MessageId: SCHEMA_GMATTRIBUTE_NOTSUPPORT
//
// MessageText:
//
//  The attribute "%1" on a group is not supported.
//
#define SCHEMA_GMATTRIBUTE_NOTSUPPORT    0xC00CE119L

//
// MessageId: SCHEMA_DTVALUES_VALUES_MISSING
//
// MessageText:
//
//  The values for enumeration type are missing.
//
#define SCHEMA_DTVALUES_VALUES_MISSING   0xC00CE11AL

//
// MessageId: SCHEMA_ATTRIBUTE_DEFAULTVALUE
//
// MessageText:
//
//  The default value "%1" is invalid.
//
#define SCHEMA_ATTRIBUTE_DEFAULTVALUE    0xC00CE11BL

//
// MessageId: SCHEMA_DTTYPE_DISABLED
//
// MessageText:
//
//  Datatype is not allowed when content model is not "textOnly".
//
#define SCHEMA_DTTYPE_DISABLED           0xC00CE11CL

//
// MessageId: SCHEMA_ELEMENT_EMPTY
//
// MessageText:
//
//  Child element is not allowed when content model is "empty".
//
#define SCHEMA_ELEMENT_EMPTY             0xC00CE11DL

//
// MessageId: SCHEMA_ELEMENT_DATATYPE
//
// MessageText:
//
//  Child element is not allowed when datatype is set.
//
#define SCHEMA_ELEMENT_DATATYPE          0xC00CE11FL

//
// MessageId: SCHEMA_DTTYPE_MISSING
//
// MessageText:
//
//  Type is missing on the datatype element.
//
#define SCHEMA_DTTYPE_MISSING            0xC00CE120L

//
// MessageId: SCHEMA_MINOCCURS_INVALIDVALUE
//
// MessageText:
//
//  The value of attribute "minOccurs" should be "0" or "1".
//
#define SCHEMA_MINOCCURS_INVALIDVALUE    0xC00CE121L

//
// MessageId: SCHEMA_MAXOCCURS_INVALIDVALUE
//
// MessageText:
//
//  The value of attribute "maxOccurs" should be "1" or "*".
//
#define SCHEMA_MAXOCCURS_INVALIDVALUE    0xC00CE122L

//
// MessageId: SCHEMA_MAXOCCURS_MUSTBESTAR
//
// MessageText:
//
//  The value of attribute "maxOccurs" must be "*" when attribute "order" is set to "many".
//
#define SCHEMA_MAXOCCURS_MUSTBESTAR      0xC00CE123L

//
// MessageId: SCHEMA_ELEMENTDT_EMPTY
//
// MessageText:
//
//  The value of data type attribute can not be empty.
//
#define SCHEMA_ELEMENTDT_EMPTY           0xC00CE124L

//
// MessageId: SCHEMA_DOCTYPE_INVALID
//
// MessageText:
//
//  DOCTYPE is not allowed in Schema.
//
#define SCHEMA_DOCTYPE_INVALID           0xC00CE125L

//
//
// DOM Object Model specific errors                           
//
//
//
// MessageId: XMLOM_DUPLICATE_ID
//
// MessageText:
//
//  The ID '%1' is duplicated.
//
#define XMLOM_DUPLICATE_ID               0xC00CE200L

//
// MessageId: XMLOM_DATATYPE_PARSE_ERROR
//
// MessageText:
//
//  Error parsing '%1' as %2 datatype.
//
#define XMLOM_DATATYPE_PARSE_ERROR       0xC00CE201L

//
// MessageId: XMLOM_NAMESPACE_CONFLICT
//
// MessageText:
//
//  There was a Namespace conflict for the '%1' Namespace.
//
#define XMLOM_NAMESPACE_CONFLICT         0xC00CE202L

//
// MessageId: XMLOM_OBJECT_EXPAND_NOTIMPL
//
// MessageText:
//
//  Unable to expand an attribute with Object value
//
#define XMLOM_OBJECT_EXPAND_NOTIMPL      0xC00CE204L

//
// MessageId: XMLOM_DTDT_DUP
//
// MessageText:
//
//  Can not have 2 datatype attributes on one element.
//
#define XMLOM_DTDT_DUP                   0xC00CE205L

//
// MessageId: XMLOM_INSERTPOS_NOTFOUND
//
// MessageText:
//
//  Insert position node not found
//
#define XMLOM_INSERTPOS_NOTFOUND         0xC00CE206L

//
// MessageId: XMLOM_NODE_NOTFOUND
//
// MessageText:
//
//  Node not found
//
#define XMLOM_NODE_NOTFOUND              0xC00CE207L

//
// MessageId: XMLOM_INVALIDTYPE
//
// MessageText:
//
//  This operation can not be performed with a Node of type %1.
//
#define XMLOM_INVALIDTYPE                0xC00CE208L

//
// MessageId: XMLOM_INVALID_XMLDECL_ATTR
//
// MessageText:
//
//  '%1' is not a valid attribute on the XML Declaration.
//  Only 'version', 'encoding', or 'standalone' attributes are allowed.
//
#define XMLOM_INVALID_XMLDECL_ATTR       0xC00CE209L

//
// MessageId: XMLOM_INVALID_INSERT_PARENT
//
// MessageText:
//
//  Inserting a Node or its ancestor under itself is not allowed.
//
#define XMLOM_INVALID_INSERT_PARENT      0xC00CE20AL

//
// MessageId: XMLOM_INVALID_INSERT_POS
//
// MessageText:
//
//  Insert position Node must be a Child of the Node to insert under.
//
#define XMLOM_INVALID_INSERT_POS         0xC00CE20BL

//
// MessageId: XMLOM_NO_ATTRIBUTES
//
// MessageText:
//
//  Attributes are not allowed on Nodes of type '%1'.
//
#define XMLOM_NO_ATTRIBUTES              0xC00CE20CL

//
// MessageId: XMLOM_NOTCHILD
//
// MessageText:
//
//  The parameter Node is not a child of this Node.
//
#define XMLOM_NOTCHILD                   0xC00CE20DL

//
// MessageId: XMLOM_CREATENODE_NEEDNAME
//
// MessageText:
//
//  createNode requires a name for given NodeType.
//
#define XMLOM_CREATENODE_NEEDNAME        0xC00CE20EL

//
// MessageId: XMLOM_UNEXPECTED_NS
//
// MessageText:
//
//  Unexpected NameSpace parameter.
//
#define XMLOM_UNEXPECTED_NS              0xC00CE20FL

//
// MessageId: XMLOM_MISSING_PARAM
//
// MessageText:
//
//  Required parameter is missing (or null/empty).
//
#define XMLOM_MISSING_PARAM              0xC00CE210L

//
// MessageId: XMLOM_INVALID_NAMESPACENODE
//
// MessageText:
//
//  NameSpace Node is invalid.
//
#define XMLOM_INVALID_NAMESPACENODE      0xC00CE211L

//
// MessageId: XMLOM_READONLY
//
// MessageText:
//
//  Attempt to modify a read-only node.
//
#define XMLOM_READONLY                   0xC00CE212L

//
// MessageId: XMLOM_ACCESSDENIED
//
// MessageText:
//
//  Access Denied.
//
#define XMLOM_ACCESSDENIED               0xC00CE213L

//
// MessageId: XMLOM_ATTRMOVE
//
// MessageText:
//
//  Attributes must be removed before adding them to a different node.
//
#define XMLOM_ATTRMOVE                   0xC00CE214L

//
// MessageId: XMLOM_BADVALUE
//
// MessageText:
//
//  Invalid data for a node of type '%1'.
//
#define XMLOM_BADVALUE                   0xC00CE215L

//
// MessageId: XMLOM_USERABORT
//
// MessageText:
//
//  Operation aborted by caller.
//
#define XMLOM_USERABORT                  0xC00CE216L

//
// MessageId: XMLOM_NEXTNODEABORT
//
// MessageText:
//
//  Unable to recover node list iterator position.
//
#define XMLOM_NEXTNODEABORT              0xC00CE217L

//
// MessageId: XMLOM_INVALID_INDEX
//
// MessageText:
//
//  The offset must be 0 or a positive number that is not greater than the number of characters in the data.
//
#define XMLOM_INVALID_INDEX              0xC00CE218L

//
// MessageId: XMLOM_INVALID_ATTR
//
// MessageText:
//
//  The provided node is not a specified attribute on this node.
//
#define XMLOM_INVALID_ATTR               0xC00CE219L

//
//
// MessageId: XMLOM_INVALID_ONDOCTYPE
//
// MessageText:
//
//  This operation can not be performed on DOCTYPE node.
//
#define XMLOM_INVALID_ONDOCTYPE          0xC00CE21AL

//
// MessageId: XMLOM_INVALID_MODEL
//
// MessageText:
//
//  Cannot mix different threading models in document.
//
#define XMLOM_INVALID_MODEL              0xC00CE21BL

//
// MessageId: XMLOM_INVALID_DATATYPE
//
// MessageText:
//
//  Datatype '%1' is not supported.
//
#define XMLOM_INVALID_DATATYPE           0xC00CE21CL

// XSL Error Messages
//
//
// MessageId: XSL_PROCESSOR_STACKOVERFLOW
//
// MessageText:
//
//  The XSL processor stack has overflowed - probable cause is infinite template recursion.
//
#define XSL_PROCESSOR_STACKOVERFLOW      0xC00CE300L

//
// MessageId: XSL_PROCESSOR_UNEXPECTEDKEYWORD
//
// MessageText:
//
//  Keyword %1 may not be used here.
//
#define XSL_PROCESSOR_UNEXPECTEDKEYWORD  0xC00CE301L

//
// MessageId: XSL_PROCESSOR_BADROOTELEMENT
//
// MessageText:
//
//  The root element of XSL stylesheet must be <xsl:document> or <xsl:template>.
//
#define XSL_PROCESSOR_BADROOTELEMENT     0xC00CE303L

//
// MessageId: XSL_PROCESSOR_KEYWORDMAYNOTFOLLOW
//
// MessageText:
//
//  Keyword %1 may not follow %2.
//
#define XSL_PROCESSOR_KEYWORDMAYNOTFOLLOW 0xC00CE304L

//
// MessageId: XSL_PROCESSOR_INVALIDSCRIPTENGINE
//
// MessageText:
//
//  %1 is not a scripting language.
//
#define XSL_PROCESSOR_INVALIDSCRIPTENGINE 0xC00CE305L

//
// MessageId: MSG_E_FORMATINDEX_BADINDEX
//
// MessageText:
//
//  The value passed in to formatIndex needs to be greater than 0.
//
#define MSG_E_FORMATINDEX_BADINDEX       0xC00CE306L

//
// MessageId: MSG_E_FORMATINDEX_BADFORMAT
//
// MessageText:
//
//  Invalid format string.
//
#define MSG_E_FORMATINDEX_BADFORMAT      0xC00CE307L

//
// MessageId: XSL_PROCESSOR_SCRIPTERROR_LINE
//
// MessageText:
//
//  line = %1, col = %2 (line is offset from the <xsl:script> tag).
//
#define XSL_PROCESSOR_SCRIPTERROR_LINE   0xC00CE308L

//
// MessageId: XSL_PROCESSOR_METHODERROR
//
// MessageText:
//
//  Error returned from property or method call.
//
#define XSL_PROCESSOR_METHODERROR        0xC00CE309L

//
//
// MessageId: MSG_E_SYSTEM_ERROR
//
// MessageText:
//
//  System error: %1.
//
#define MSG_E_SYSTEM_ERROR               0xC00CE30AL

//
// MessageId: XSL_KEYWORD_MAYNOTCONTAIN
//
// MessageText:
//
//  Keyword %1 may not contain %2.
//
#define XSL_KEYWORD_MAYNOTCONTAIN        0xC00CE30BL

// XQL Error Messages
//
//
// MessageId: MSG_E_EXPECTED_TOKEN
//
// MessageText:
//
//  Expected token %1 found %2.
//
#define MSG_E_EXPECTED_TOKEN             0xC00CE380L

//
// MessageId: MSG_E_UNEXPECTED_TOKEN
//
// MessageText:
//
//  Unexpected token %1.
//
#define MSG_E_UNEXPECTED_TOKEN           0xC00CE381L

//
// MessageId: XQL_EXPR_NOT_DOM_NODE
//
// MessageText:
//
//  Expression does not return a DOM node.
//
#define XQL_EXPR_NOT_DOM_NODE            0xC00CE382L

//
// MessageId: XQL_EXPR_NOT_QUERY_OR_INTEGER
//
// MessageText:
//
//  Expression must be a query or an integer constant.
//
#define XQL_EXPR_NOT_QUERY_OR_INTEGER    0xC00CE383L

//
// MessageId: XQL_INCOMPLETE_QUERY
//
// MessageText:
//
//  Incomplete query expression.
//
#define XQL_INCOMPLETE_QUERY             0xC00CE384L

//
// MessageId: XQL_UNKNOWN_METHOD
//
// MessageText:
//
//  Unknown method.
//
#define XQL_UNKNOWN_METHOD               0xC00CE385L

//
// MessageId: XQL_UNEXPECTED_CHAR
//
// MessageText:
//
//  Unexpected character in query string.
//
#define XQL_UNEXPECTED_CHAR              0xC00CE386L

//
// MessageId: XQL_QUERY_INVALID_HERE
//
// MessageText:
//
//  %1 may not appear to the right of / or // or be used with |.
//
#define XQL_QUERY_INVALID_HERE           0xC00CE387L

//
// MessageId: XQL_EXPR_NOT_STRING
//
// MessageText:
//
//  Expression must be a string constant.
//
#define XQL_EXPR_NOT_STRING              0xC00CE388L

//
// MessageId: XQL_METHOD_NOT_SUPPORTED
//
// MessageText:
//
//  Object does not support this method.
//
#define XQL_METHOD_NOT_SUPPORTED         0xC00CE389L

//
// MessageId: XQL_INVALID_CAST
//
// MessageText:
//
//  Expression can't be cast to this data type.
//
#define XQL_INVALID_CAST                 0xC00CE38AL

//
// MessageId: XMLISLANDS_NOSCRIPTLETS
//
// MessageText:
//
//  The XML script engine does not support script fragments.  This error was probably caused by having a script tag with the language attribute set to "XML" or the text attribute set to "text/xml" before any other script tag on the page.
//
#define XMLISLANDS_NOSCRIPTLETS          0xC00CE38CL

//
// MessageId: XQL_EXPR_NOT_QUERY_OR_STRING
//
// MessageText:
//
//  Parameter must be a query or a string constant.
//
#define XQL_EXPR_NOT_QUERY_OR_STRING     0xC00CE38DL

//
// MessageId: XQL_EXPR_NOT_INTEGER
//
// MessageText:
//
//  Parameter must be a integer constant.
//
#define XQL_EXPR_NOT_INTEGER             0xC00CE38EL

//
// MIMETYPE Viewer Errors
//
//
// MessageId: XMLMIME_ERROR
//
// MessageText:
//
//  <%1TABLE width=400>
//  <%1P style="font:13pt/15pt verdana"> The XML page cannot be displayed
//  <%1P style="font:8pt/11pt verdana">Cannot view XML input using %3 style sheet.
//  Please correct the error and then click the 
//  <%1a href="javascript:location.reload()" target="_self">
//  Refresh</%1a> button, or try again later.
//  <%1HR><%1P style="font:bold 8pt/11pt verdana">%2</%1P><%1/TABLE>
//  <%1pre style="font:10pt/12pt"><%1font color="blue">%4</%1font></%1pre>
//
#define XMLMIME_ERROR                    0xC00CE400L

//
// MessageId: XMLMIME_LINEPOS
//
// MessageText:
//
//  Line %1, Position %2
//
#define XMLMIME_LINEPOS                  0xC00CE401L

//
// MessageId: XMLMIME_SOURCENA
//
// MessageText:
//
//  The XML source file is unavailable for viewing.
//
#define XMLMIME_SOURCENA                 0xC00CE402L

//                                                                           
//                                                                           
// XMLPSR specific errors                           
//             
// I had to change the symbolic names to MSG_ so they didn't clash with
// the named defined in xmlparser.idl.  The important thing is that they
// have the same message id.                                                              
//                                                                           
// -------- READ ME !!!! -------------
//
// The broken unix mc compiler (a perl script) needs the symbolic name
// and Severity on the same line as the Message ID, to do otherwise will break
// it. Language can be on a seperate line
//
// -----------------------------------
// ----------- character level error codes -----------------------------
//
// MessageId: MSG_E_MISSINGEQUALS
//
// MessageText:
//
//  Missing equals sign between attribute and attribute value.
//
#define MSG_E_MISSINGEQUALS              0xC00CE501L

//
// MessageId: MSG_E_MISSINGQUOTE
//
// MessageText:
//
//  A string literal was expected, but no opening quote character was found.
//
#define MSG_E_MISSINGQUOTE               0xC00CE502L

//
// MessageId: MSG_E_COMMENTSYNTAX
//
// MessageText:
//
//  Incorrect syntax was used in a comment.
//
#define MSG_E_COMMENTSYNTAX              0xC00CE503L

//
// MessageId: MSG_E_BADSTARTNAMECHAR
//
// MessageText:
//
//  A name was started with an invalid character.
//
#define MSG_E_BADSTARTNAMECHAR           0xC00CE504L

//
// MessageId: MSG_E_BADNAMECHAR
//
// MessageText:
//
//  A name contained an invalid character.
//
#define MSG_E_BADNAMECHAR                0xC00CE505L

//
// MessageId: MSG_E_BADCHARINSTRING
//
// MessageText:
//
//  The character '<' cannot be used in an attribute value.
//
#define MSG_E_BADCHARINSTRING            0xC00CE506L

//
// MessageId: MSG_E_XMLDECLSYNTAX
//
// MessageText:
//
//  Invalid syntax for an xml declaration.
//
#define MSG_E_XMLDECLSYNTAX              0xC00CE507L

//
// MessageId: MSG_E_BADCHARDATA
//
// MessageText:
//
//  An Invalid character was found in text content.
//
#define MSG_E_BADCHARDATA                0xC00CE508L

//
// MessageId: MSG_E_MISSINGWHITESPACE
//
// MessageText:
//
//  Required white space was missing.
//
#define MSG_E_MISSINGWHITESPACE          0xC00CE509L

//
// MessageId: MSG_E_EXPECTINGTAGEND
//
// MessageText:
//
//  The character '>' was expected.
//
#define MSG_E_EXPECTINGTAGEND            0xC00CE50AL

//
// MessageId: MSG_E_BADCHARINDTD
//
// MessageText:
//
//  Invalid character found in DTD.
//
#define MSG_E_BADCHARINDTD               0xC00CE50BL

//
// MessageId: MSG_E_BADCHARINDECL
//
// MessageText:
//
//  An invalid character was found inside a DTD declaration.
//
#define MSG_E_BADCHARINDECL              0xC00CE50CL

//
// MessageId: MSG_E_MISSINGSEMICOLON
//
// MessageText:
//
//  A semi colon character was expected.
//
#define MSG_E_MISSINGSEMICOLON           0xC00CE50DL

//
// MessageId: MSG_E_BADCHARINENTREF
//
// MessageText:
//
//  An invalid character was found inside an entity reference.
//
#define MSG_E_BADCHARINENTREF            0xC00CE50EL

//
// MessageId: MSG_E_UNBALANCEDPAREN
//
// MessageText:
//
//  Unbalanced parentheses.
//
#define MSG_E_UNBALANCEDPAREN            0xC00CE50FL

//
// MessageId: MSG_E_EXPECTINGOPENBRACKET
//
// MessageText:
//
//  An opening '[' character was expected.
//
#define MSG_E_EXPECTINGOPENBRACKET       0xC00CE510L

//
// MessageId: MSG_E_BADENDCONDSECT
//
// MessageText:
//
//  Invalid syntax in a conditional section.
//
#define MSG_E_BADENDCONDSECT             0xC00CE511L

//
// MessageId: MSG_E_INTERNALERROR
//
// MessageText:
//
//  Internal error.
//
#define MSG_E_INTERNALERROR              0xC00CE512L

//
// MessageId: MSG_E_UNEXPECTED_WHITESPACE
//
// MessageText:
//
//  Whitespace is not allowed at this location.
//
#define MSG_E_UNEXPECTED_WHITESPACE      0xC00CE513L

//
// MessageId: MSG_E_INCOMPLETE_ENCODING
//
// MessageText:
//
//  End of file reached in invalid state for current encoding.
//
#define MSG_E_INCOMPLETE_ENCODING        0xC00CE514L

//
// MessageId: MSG_E_BADCHARINMIXEDMODEL
//
// MessageText:
//
//  Mixed content model cannot contain this character.
//
#define MSG_E_BADCHARINMIXEDMODEL        0xC00CE515L

//
// MessageId: MSG_E_MISSING_STAR
//
// MessageText:
//
//  Mixed content model must be defined as zero or more('*').
//
#define MSG_E_MISSING_STAR               0xC00CE516L

//
// MessageId: MSG_E_BADCHARINMODEL
//
// MessageText:
//
//  Invalid character in content model.
//
#define MSG_E_BADCHARINMODEL             0xC00CE517L

//
// MessageId: MSG_E_MISSING_PAREN
//
// MessageText:
//
//  Missing parenthesis.
//
#define MSG_E_MISSING_PAREN              0xC00CE518L

//
// MessageId: MSG_E_BADCHARINENUMERATION
//
// MessageText:
//
//  Invalid character found in ATTLIST enumeration.
//
#define MSG_E_BADCHARINENUMERATION       0xC00CE519L

//
// MessageId: MSG_E_PIDECLSYNTAX
//
// MessageText:
//
//  Invalid syntax in PI declaration.
//
#define MSG_E_PIDECLSYNTAX               0xC00CE51AL

//
// MessageId: MSG_E_EXPECTINGCLOSEQUOTE
//
// MessageText:
//
//  A single or double closing quote character (\' or \") is missing.
//
#define MSG_E_EXPECTINGCLOSEQUOTE        0xC00CE51BL

//
// MessageId: MSG_E_MULTIPLE_COLONS
//
// MessageText:
//
//  Multiple colons are not allowed in a name.
//
#define MSG_E_MULTIPLE_COLONS            0xC00CE51CL

//
// MessageId: MSG_E_INVALID_DECIMAL
//
// MessageText:
//
//  Invalid character for decimal digit.
//
#define MSG_E_INVALID_DECIMAL            0xC00CE51DL

//
// MessageId: MSG_E_INVALID_HEXIDECIMAL
//
// MessageText:
//
//  Invalid character for hexidecimal digit.
//
#define MSG_E_INVALID_HEXIDECIMAL        0xC00CE51EL

//
// MessageId: MSG_E_INVALID_UNICODE
//
// MessageText:
//
//  Invalid unicode character value for this platform.
//
#define MSG_E_INVALID_UNICODE            0xC00CE51FL

//
// MessageId: MSG_E_WHITESPACEORQUESTIONMARK
//
// MessageText:
//
//  Expecting whitespace or '?'.
//
#define MSG_E_WHITESPACEORQUESTIONMARK   0xC00CE520L

// ----------- token level error codes -----------------------------
//
// MessageId: MSG_E_SUSPENDED
//
// MessageText:
//
//  The parser is suspended.
//
#define MSG_E_SUSPENDED                  0xC00CE550L

//
// MessageId: MSG_E_STOPPED
//
// MessageText:
//
//  The parser is stopped.
//
#define MSG_E_STOPPED                    0xC00CE551L

//
// MessageId: MSG_E_UNEXPECTEDENDTAG
//
// MessageText:
//
//  End tag was not expected at this location.
//
#define MSG_E_UNEXPECTEDENDTAG           0xC00CE552L

//
// MessageId: MSG_E_UNCLOSEDTAG
//
// MessageText:
//
//  The following tags were not closed: %1.
//
#define MSG_E_UNCLOSEDTAG                0xC00CE553L

//
// MessageId: MSG_E_DUPLICATEATTRIBUTE
//
// MessageText:
//
//  Duplicate attribute.
//
#define MSG_E_DUPLICATEATTRIBUTE         0xC00CE554L

//
// MessageId: MSG_E_MULTIPLEROOTS
//
// MessageText:
//
//  Only one top level element is allowed in an XML document.
//
#define MSG_E_MULTIPLEROOTS              0xC00CE555L

//
// MessageId: MSG_E_INVALIDATROOTLEVEL
//
// MessageText:
//
//  Invalid at the top level of the document.
//
#define MSG_E_INVALIDATROOTLEVEL         0xC00CE556L

//
// MessageId: MSG_E_BADXMLDECL
//
// MessageText:
//
//  Invalid xml declaration.
//
#define MSG_E_BADXMLDECL                 0xC00CE557L

//
// MessageId: MSG_E_MISSINGROOT
//
// MessageText:
//
//  XML document must have a top level element.
//
#define MSG_E_MISSINGROOT                0xC00CE558L

//
// MessageId: MSG_E_UNEXPECTEDEOF
//
// MessageText:
//
//  Unexpected end of file.
//
#define MSG_E_UNEXPECTEDEOF              0xC00CE559L

//
// MessageId: MSG_E_BADPEREFINSUBSET
//
// MessageText:
//
//  Parameter entities cannot be used inside markup declarations in an internal subset.
//
#define MSG_E_BADPEREFINSUBSET           0xC00CE55AL

//
// MessageId: MSG_E_PE_NESTING
//
// MessageText:
//
//  The replacement text for a parameter entity must be properly
//  nested with parenthesized groups.
//
#define MSG_E_PE_NESTING                 0xC00CE55BL

//
// MessageId: MSG_E_INVALID_CDATACLOSINGTAG
//
// MessageText:
//
//  The literal string ']]>' is not allowed in element content.
//
#define MSG_E_INVALID_CDATACLOSINGTAG    0xC00CE55CL

//
// MessageId: MSG_E_UNCLOSEDPI
//
// MessageText:
//
//  Processing instruction was not closed.
//
#define MSG_E_UNCLOSEDPI                 0xC00CE55DL

//
// MessageId: MSG_E_UNCLOSEDSTARTTAG
//
// MessageText:
//
//  Element was not closed.
//
#define MSG_E_UNCLOSEDSTARTTAG           0xC00CE55EL

//
// MessageId: MSG_E_UNCLOSEDENDTAG
//
// MessageText:
//
//  End element was missing the character '>'.
//
#define MSG_E_UNCLOSEDENDTAG             0xC00CE55FL

//
// MessageId: MSG_E_UNCLOSEDSTRING
//
// MessageText:
//
//  A string literal was not closed.
//
#define MSG_E_UNCLOSEDSTRING             0xC00CE560L

//
// MessageId: MSG_E_UNCLOSEDCOMMENT
//
// MessageText:
//
//  A comment was not closed.
//
#define MSG_E_UNCLOSEDCOMMENT            0xC00CE561L

//
// MessageId: MSG_E_UNCLOSEDDECL
//
// MessageText:
//
//  A declaration was not closed.
//
#define MSG_E_UNCLOSEDDECL               0xC00CE562L

//
// MessageId: MSG_E_UNCLOSEDMARKUPDECL
//
// MessageText:
//
//  A markup declaration was not closed.
//
#define MSG_E_UNCLOSEDMARKUPDECL         0xC00CE563L

//
// MessageId: MSG_E_UNCLOSEDCDATA
//
// MessageText:
//
//  A CDATA section was not closed.
//
#define MSG_E_UNCLOSEDCDATA              0xC00CE564L

//
// MessageId: MSG_E_BADDECLNAME
//
// MessageText:
//
//  Declaration has an invalid name.
//
#define MSG_E_BADDECLNAME                0xC00CE565L

//
// MessageId: MSG_E_BADEXTERNALID
//
// MessageText:
//
//  External ID is invalid.
//
#define MSG_E_BADEXTERNALID              0xC00CE566L

//
// MessageId: MSG_E_BADELEMENTINDTD
//
// MessageText:
//
//  An XML element is not allowed inside a DTD.
//
#define MSG_E_BADELEMENTINDTD            0xC00CE567L

//
// MessageId: MSG_E_RESERVEDNAMESPACE
//
// MessageText:
//
//  The namespace prefix is not allowed to start with the reserved string "xml".
//
#define MSG_E_RESERVEDNAMESPACE          0xC00CE568L

//
// MessageId: MSG_E_EXPECTING_VERSION
//
// MessageText:
//
//  The 'version' attribute is required at this location.
//
#define MSG_E_EXPECTING_VERSION          0xC00CE569L

//
// MessageId: MSG_E_EXPECTING_ENCODING
//
// MessageText:
//
//  The 'encoding' attribute is required at this location.
//
#define MSG_E_EXPECTING_ENCODING         0xC00CE56AL

//
// MessageId: MSG_E_EXPECTING_NAME
//
// MessageText:
//
//  At least one name is required at this location.
//
#define MSG_E_EXPECTING_NAME             0xC00CE56BL

//
// MessageId: MSG_E_UNEXPECTED_ATTRIBUTE
//
// MessageText:
//
//  The specified attribute was not expected at this location.
//  The attribute may be case sensitive.
//
#define MSG_E_UNEXPECTED_ATTRIBUTE       0xC00CE56CL

//
// MessageId: MSG_E_ENDTAGMISMATCH
//
// MessageText:
//
//  End tag '%2' does not match the start tag '%1'.
//
#define MSG_E_ENDTAGMISMATCH             0xC00CE56DL

//
// MessageId: MSG_E_INVALIDENCODING
//
// MessageText:
//
//  System does not support the specified encoding.
//
#define MSG_E_INVALIDENCODING            0xC00CE56EL

//
// MessageId: MSG_E_INVALIDSWITCH
//
// MessageText:
//
//  Switch from current encoding to specified encoding not supported.
//
#define MSG_E_INVALIDSWITCH              0xC00CE56FL

//
// MessageId: MSG_E_EXPECTING_NDATA
//
// MessageText:
//
//  NDATA keyword is missing.
//
#define MSG_E_EXPECTING_NDATA            0xC00CE570L

//
// MessageId: MSG_E_INVALID_MODEL
//
// MessageText:
//
//  Content model is invalid.
//
#define MSG_E_INVALID_MODEL              0xC00CE571L

//
// MessageId: MSG_E_INVALID_TYPE
//
// MessageText:
//
//  Invalid type defined in ATTLIST.
//
#define MSG_E_INVALID_TYPE               0xC00CE572L

//
// MessageId: MSG_E_INVALIDXMLSPACE
//
// MessageText:
//
//  XML space attribute has invalid value.  Must specify 'default' or 'preserve'.
//
#define MSG_E_INVALIDXMLSPACE            0xC00CE573L

//
// MessageId: MSG_E_MULTI_ATTR_VALUE
//
// MessageText:
//
//  Multiple names found in attribute value when only one was expected.
//
#define MSG_E_MULTI_ATTR_VALUE           0xC00CE574L

//
// MessageId: MSG_E_INVALID_PRESENCE
//
// MessageText:
//
//  Invalid ATTDEF declaration.  Expected #REQUIRED, #IMPLIED or #FIXED.
//
#define MSG_E_INVALID_PRESENCE           0xC00CE575L

//
// MessageId: MSG_E_BADXMLCASE
//
// MessageText:
//
//  The name 'xml' is reserved and must be lower case.
//
#define MSG_E_BADXMLCASE                 0xC00CE576L

//
// MessageId: MSG_E_CONDSECTINSUBSET
//
// MessageText:
//
//  Conditional sections are not allowed in an internal subset.
//
#define MSG_E_CONDSECTINSUBSET           0xC00CE577L

//
// MessageId: MSG_E_CDATAINVALID
//
// MessageText:
//
//  CDATA is not allowed in a DTD.
//
#define MSG_E_CDATAINVALID               0xC00CE578L

//
// MessageId: MSG_E_INVALID_STANDALONE
//
// MessageText:
//
//  The standalone attribute must have the value 'yes' or 'no'.
//
#define MSG_E_INVALID_STANDALONE         0xC00CE579L

//
// MessageId: MSG_E_UNEXPECTED_STANDALONE
//
// MessageText:
//
//  The standalone attribute cannot be used in external entities.
//
#define MSG_E_UNEXPECTED_STANDALONE      0xC00CE57AL

//
// MessageId: MSG_E_DOCTYPE_IN_DTD
//
// MessageText:
//
//  Cannot have a DOCTYPE declaration in a DTD.
//
#define MSG_E_DOCTYPE_IN_DTD             0xC00CE57BL

//
// MessageId: MSG_E_MISSING_ENTITY
//
// MessageText:
//
//  Reference to undefined entity.
//
#define MSG_E_MISSING_ENTITY             0xC00CE57CL

//
// MessageId: MSG_E_ENTITYREF_INNAME
//
// MessageText:
//
//  Entity reference is resolved to an invalid name character.
//
#define MSG_E_ENTITYREF_INNAME           0xC00CE57DL

//
// MessageId: MSG_E_DOCTYPE_OUTSIDE_PROLOG
//
// MessageText:
//
//  Cannot have a DOCTYPE declaration outside of a prolog.
//
#define MSG_E_DOCTYPE_OUTSIDE_PROLOG     0xC00CE57EL

//
// MessageId: MSG_E_INVALID_VERSION
//
// MessageText:
//
//  Invalid version number.
//
#define MSG_E_INVALID_VERSION            0xC00CE57FL

//
// MessageId: MSG_E_DTDELEMENT_OUTSIDE_DTD
//
// MessageText:
//
//  Cannot have a DTD declaration outside of a DTD.
//
#define MSG_E_DTDELEMENT_OUTSIDE_DTD     0xC00CE580L

//
// MessageId: MSG_E_DUPLICATEDOCTYPE
//
// MessageText:
//
//  Cannot have multiple DOCTYPE declarations.
//
#define MSG_E_DUPLICATEDOCTYPE           0xC00CE581L

//
// MessageId: MSG_E_RESOURCE
//
// MessageText:
//
//  Error processing resource '%1'.
//
#define MSG_E_RESOURCE                   0xC00CE582L

//  DO NOT ADD ANYTHING OTHER THAN TOKENIZER ERRORS HERE -- SEE OTHER SECTIONS ABOVE...
