// ----------------------------------------------------------------------------
//  FILE: TestOrb2_ClientProxy.cpp
//  DATE: Tue, Feb 26 15:38:53 2019 -0500
//    ID: 04B5C1BC4E24325C-2549453D6539A000
//
//  This file was generated by the Charmed Quark CIDIDL compiler. Do not make
//  changes by hand, because they will be lost if the file is regenerated.
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "TestOrb2.hpp"

// ----------------------------------------------------------------------------
// Magic macros
// ----------------------------------------------------------------------------
AdvRTTIDecls(TTestOrb2IntfClientProxy,TOrbClientBase)


// ----------------------------------------------------------------------------
// TTestOrb2IntfClientProxy: Public, static data
// ----------------------------------------------------------------------------
const TString TTestOrb2IntfClientProxy::strInterfaceId(L"04B5C1BC4E24325C-2549453D6539A000");

// ----------------------------------------------------------------------------
// TTestOrb2IntfClientProxy: Constructors and Destructor
// ----------------------------------------------------------------------------
TTestOrb2IntfClientProxy::TTestOrb2IntfClientProxy()
{
}

TTestOrb2IntfClientProxy::
TTestOrb2IntfClientProxy(const TOrbObjId& ooidSrc, const TString& strNSBinding)
{
    #if CID_DEBUG_ON
    if (!ooidSrc.oidKey().bIsInterfaceId(strInterfaceId))
    {
        facCIDOrb().ThrowErr
        (
            CID_FILE
            , CID_LINE
            , kOrbErrs::errcClient_BadIntfId
            , tCIDLib::ESeverities::Failed
            , tCIDLib::EErrClasses::BadParms
            , ooidSrc.oidKey().mhashInterface()
            , strInterfaceId
        );
    }
    #endif
    SetObjId(ooidSrc, strNSBinding, kCIDLib::False);
}

TTestOrb2IntfClientProxy::~TTestOrb2IntfClientProxy()
{
}

// ----------------------------------------------------------------------------
// TTestOrb2IntfClientProxy: Public, non-virtual methods
// ----------------------------------------------------------------------------
tCIDLib::TVoid TTestOrb2IntfClientProxy::Ping()
{
    TCmdQItem* pcqiToUse = pcqiGetCmdItem(ooidThis().oidKey());
    TOrbCmd& ocmdToUse = pcqiToUse->ocmdData();
    try
    {
        ocmdToUse.strmOut() << TString(L"Ping");
        Dispatch(30000, pcqiToUse);
        ocmdToUse.strmIn().Reset();
        GiveBackCmdItem(pcqiToUse);
    }
    catch(TError& errToCatch)
    {
        GiveBackCmdItem(pcqiToUse);
        errToCatch.AddStackLevel(CID_FILE, CID_LINE);
        throw;
    }
}
