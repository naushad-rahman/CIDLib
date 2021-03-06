//
// FILE NAME: CIDXML_EntityDecl.Cpp
//
// AUTHOR: Dean Roddey
//
// CREATED: 08/21/1999
//
// COPYRIGHT: $_CIDLib_CopyRight_$
//
//  $_CIDLib_CopyRight2_$
//
// DESCRIPTION:
//
//  This file implements the TXMLEntityDecl class.
//
// CAVEATS/GOTCHAS:
//
// LOG:
//
//  $_CIDLib_Log_$
//


// ---------------------------------------------------------------------------
//  Facility specific includes
// ---------------------------------------------------------------------------
#include    "CIDXML_.hpp"


// ---------------------------------------------------------------------------
//  Magic RTTI macros
// ---------------------------------------------------------------------------
RTTIDecls(TXMLEntityDecl,TObject)



// ---------------------------------------------------------------------------
//  CLASS: TXMLEntityDecl
// PREFIX: xdecl
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
//  TXMLEntityDecl: Constructors and Destructor
// ---------------------------------------------------------------------------
TXMLEntityDecl::~TXMLEntityDecl()
{
}


// ---------------------------------------------------------------------------
//  TXMLEntityDecl: Public, non-virtual methods
// ---------------------------------------------------------------------------
tCIDLib::TBoolean TXMLEntityDecl::bIsExternal() const
{
    // If it has a system id, its an external entity
    return !m_strSystemId.bIsEmpty();
}

tCIDLib::TBoolean TXMLEntityDecl::bIsInternal() const
{
    // If it has a system id, its not an internal entity
    return m_strSystemId.bIsEmpty();
}

tCIDLib::TBoolean TXMLEntityDecl::bIsSpecial() const
{
    return m_bSpecial;
}

tCIDLib::TBoolean
TXMLEntityDecl::bIsSpecial(const tCIDLib::TBoolean bNewValue)
{
    m_bSpecial = bNewValue;
    return m_bSpecial;
}

tCIDLib::TBoolean TXMLEntityDecl::bIsUnparsed() const
{
    // If we have a notation, its not a parsed entity
    return !m_strNotationName.bIsEmpty();
}

tCIDLib::TCard4 TXMLEntityDecl::c4Id() const
{
    return m_c4Id;
}

tCIDLib::TCard4 TXMLEntityDecl::c4Id(const tCIDLib::TCard4 c4NewId)
{
    m_c4Id = c4NewId;
    return m_c4Id;
}

const TString& TXMLEntityDecl::strName() const
{
    return m_strName;
}

const TString& TXMLEntityDecl::strName(const TString& strName)
{
    m_strName = strName;
    return m_strName;
}

const TString& TXMLEntityDecl::strName(const tCIDLib::TCh* const pszName)
{
    m_strName = pszName;
    return m_strName;
}

const TString& TXMLEntityDecl::strValue() const
{
    return m_strValue;
}

const TString& TXMLEntityDecl::strValue(const TString& strValue)
{
    m_strValue = strValue;
    return m_strValue;
}

const TString& TXMLEntityDecl::strValue(const tCIDLib::TCh* const pszValue)
{
    m_strValue = pszValue;
    return m_strValue;
}

const TString& TXMLEntityDecl::strNotationName() const
{
    return m_strNotationName;
}

const TString& TXMLEntityDecl::strNotationName(const TString& strName)
{
    m_strNotationName = strName;
    return m_strNotationName;
}

const TString&
TXMLEntityDecl::strNotationName(const tCIDLib::TCh* const pszName)
{
    m_strNotationName = pszName;
    return m_strNotationName;
}

const TString& TXMLEntityDecl::strPublicId() const
{
    return m_strPublicId;
}

const TString& TXMLEntityDecl::strPublicId(const TString& strId)
{
    m_strPublicId = strId;
    return m_strPublicId;
}

const TString& TXMLEntityDecl::strPublicId(const tCIDLib::TCh* const pszId)
{
    m_strPublicId = pszId;
    return m_strPublicId;
}

const TString& TXMLEntityDecl::strSystemId() const
{
    return m_strSystemId;
}

const TString& TXMLEntityDecl::strSystemId(const TString& strId)
{
    m_strSystemId = strId;
    return m_strSystemId;
}

const TString& TXMLEntityDecl::strSystemId(const tCIDLib::TCh* const pszId)
{
    m_strSystemId = pszId;
    return m_strSystemId;
}



// ---------------------------------------------------------------------------
//  TXMLEntityDecl: Hidden constructors and operators
// ---------------------------------------------------------------------------
TXMLEntityDecl::TXMLEntityDecl() :

    m_bSpecial(kCIDLib::False)
    , m_c4Id(0)
    , m_c4ValueLen(0)
{
}

TXMLEntityDecl::TXMLEntityDecl(const TString& strEntityName) :

    m_bSpecial(kCIDLib::False)
    , m_c4Id(0)
    , m_c4ValueLen(0)
    , m_strName(strEntityName)
{
}

TXMLEntityDecl::TXMLEntityDecl( const   TString&    strEntityName
                                , const TString&    strEntityValue) :

    m_bSpecial(kCIDLib::False)
    , m_c4Id(0)
    , m_c4ValueLen(0)
    , m_strName(strEntityName)
    , m_strValue(strEntityValue)
{
}

TXMLEntityDecl::TXMLEntityDecl(const tCIDLib::TCh* const pszEntityName) :

    m_bSpecial(kCIDLib::False)
    , m_c4Id(0)
    , m_c4ValueLen(0)
    , m_strName(pszEntityName)
{
}

TXMLEntityDecl::TXMLEntityDecl( const   tCIDLib::TCh* const pszEntityName
                                , const tCIDLib::TCh* const pszEntityValue) :

    m_bSpecial(kCIDLib::False)
    , m_c4Id(0)
    , m_c4ValueLen(0)
    , m_strName(pszEntityName)
    , m_strValue(pszEntityValue)
{
}

TXMLEntityDecl::TXMLEntityDecl(const TXMLEntityDecl& xdeclToCopy) :

    m_bSpecial(kCIDLib::False)
    , m_c4Id(xdeclToCopy.m_c4Id)
    , m_c4ValueLen(xdeclToCopy.m_c4ValueLen)
    , m_strName(xdeclToCopy.m_strName)
    , m_strValue(xdeclToCopy.m_strValue)
    , m_strNotationName(xdeclToCopy.m_strNotationName)
    , m_strPublicId(xdeclToCopy.m_strPublicId)
    , m_strSystemId(xdeclToCopy.m_strSystemId)
{
}

TXMLEntityDecl& TXMLEntityDecl::operator=(const TXMLEntityDecl& xdeclToAssign)
{
    if (this == &xdeclToAssign)
        return *this;

    m_bSpecial          = xdeclToAssign.m_bSpecial;
    m_c4Id              = xdeclToAssign.m_c4Id;
    m_c4ValueLen        = xdeclToAssign.m_c4ValueLen;
    m_strName           = xdeclToAssign.m_strName;
    m_strValue          = xdeclToAssign.m_strValue;
    m_strNotationName   = xdeclToAssign.m_strNotationName;
    m_strPublicId       = xdeclToAssign.m_strPublicId;
    m_strSystemId       = xdeclToAssign.m_strSystemId;

    return *this;
}

