// ----------------------------------------------------------------------------
//  FILE: VideoDemoS_IntfServerBase.cpp
//  DATE: Wed, Jan 30 13:17:30 2019 -0500
//    ID: E1CCC9CBCFA1FDAF-29A8F7CB04763265
//
//  This file was generated by the Charmed Quark CIDIDL compiler. Do not make
//  changes by hand, because they will be lost if the file is regenerated.
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "VideoDemoS.hpp"

// ----------------------------------------------------------------------------
// Magic macros
// ----------------------------------------------------------------------------
RTTIDecls(TVideoDemoServerBase,TOrbServerBase)


// ----------------------------------------------------------------------------
// Public, static data
// ----------------------------------------------------------------------------
const TString TVideoDemoServerBase::strInterfaceId(L"E1CCC9CBCFA1FDAF-29A8F7CB04763265");
const TString TVideoDemoServerBase::strBinding(L"/VideoDemo/IntfImpl");


// ----------------------------------------------------------------------------
// TVideoDemoServerBase: Destructor
// ----------------------------------------------------------------------------
TVideoDemoServerBase::~TVideoDemoServerBase()
{
}

// ----------------------------------------------------------------------------
// TVideoDemoServerBase: Protected Constructors
// ----------------------------------------------------------------------------
TVideoDemoServerBase::TVideoDemoServerBase() :
    TOrbServerBase(strInterfaceId, L"TVideoDemoClientProxy" )
{
}

TVideoDemoServerBase::TVideoDemoServerBase(const TOrbObjId& ooidThis) :
    TOrbServerBase(ooidThis)
{
}

// ----------------------------------------------------------------------------
// TVideoDemoServerBase: Public, non-virtual methods
// ----------------------------------------------------------------------------
tCIDLib::TVoid TVideoDemoServerBase::Dispatch(const TString& strMethodName, TOrbCmd& orbcToDispatch)
{
    if (strMethodName == L"bQueryByName")
    {
        TString strToFind;
        orbcToDispatch.strmIn() >> strToFind;
        TDemoRecord recFound;
        tCIDLib::TBoolean retVal = bQueryByName
        (
            strToFind
          , recFound
        );
        orbcToDispatch.strmOut().Reset();
        orbcToDispatch.strmOut() << retVal;
        orbcToDispatch.strmOut() << recFound;
    }
     else if (strMethodName == L"bQueryAllStatus")
    {
        tVideoDemoSh::EStatus eToFind;
        orbcToDispatch.strmIn() >> eToFind;
        TVector<TDemoRecord> colFound;
        tCIDLib::TBoolean retVal = bQueryAllStatus
        (
            eToFind
          , colFound
        );
        orbcToDispatch.strmOut().Reset();
        orbcToDispatch.strmOut() << retVal;
        orbcToDispatch.strmOut() << colFound;
    }
     else
    {
         TParent::Dispatch(strMethodName, orbcToDispatch);
    }
}

