//
// FILE NAME: CIDXML.Cpp
//
// AUTHOR: Dean Roddey
//
// CREATED: 08/20/1999
//
// COPYRIGHT: $_CIDLib_CopyRight_$
//
//  $_CIDLib_CopyRight2_$
//
// DESCRIPTION:
//
//  This is the main file of the facility.
//
// CAVEATS/GOTCHAS:
//
// LOG:
//
//  $_CIDLib_Log_$
//



// ---------------------------------------------------------------------------
//  For this file we want to pre instantiate some collections, but not for any
//  other files. Only this file defines this toke, which prevents the use of the
//  extern declaration.
// ---------------------------------------------------------------------------
#define CIDXML_PREINST 1



// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include    "CIDXML_.hpp"


// ---------------------------------------------------------------------------
//  We pre-generate some template classes
// ---------------------------------------------------------------------------
template class CIDXMLEXP TCntPtr<const TXMLEntitySrc>;
template class CIDXMLEXP TRefVector<TXMLTreeAttr>;
template class CIDXMLEXP TRefVector<TXMLTreeElement>;
template class CIDXMLEXP TRefVector<TXMLTreeNode>;
template class CIDXMLEXP TRefVector<TXMLTreeText>;
template class CIDXMLEXP TKeyedHashSet<tCIDXML::TEntitySrcRef, TString, TStringKeyOps>;
template class CIDXMLEXP TVector<TXMLAttr>;
template class CIDXMLEXP TVector<TXMLTreeParser::TErrInfo>;

// These don't need to be exported, they are used internally
template class TSimplePoolJan<TString>;


// ---------------------------------------------------------------------------
//  Provide RTTI Decl macros for all our classes that don't have a Cpp file
//  for us.
// ---------------------------------------------------------------------------
RTTIDecls(TAttrDefCursor,TObject)
RTTIDecls(TXMLContentModel,TObject)
RTTIDecls(TXMLElemDecl,TObject)



// ---------------------------------------------------------------------------
//  Global functions
// ---------------------------------------------------------------------------
TFacCIDXML& facCIDXML()
{
    static TFacCIDXML* pfacCIDXML = nullptr;
    if (!pfacCIDXML)
    {
        TBaseLock lockInit;
        if (!pfacCIDXML)
            pfacCIDXML = new TFacCIDXML;
    }
    return *pfacCIDXML;
}

