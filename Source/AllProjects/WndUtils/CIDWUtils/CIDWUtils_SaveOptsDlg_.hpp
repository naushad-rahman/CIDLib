//
// FILE NAME: CIDWUtils_SaveOptsDlg_.hpp
//
// AUTHOR: Dean Roddey
//
// CREATED: 08/20/2015
//
// COPYRIGHT: $_CIDLib_CopyRight_$
//
//  $_CIDLib_CopyRight2_$
//
// DESCRIPTION:
//
//  This is the header for the CIDWUtils_SaveOptsDlg.cpp file, which provides a
//  general dialog for getting save/discard/cancel options from the user.
//
// CAVEATS/GOTCHAS:
//
// LOG:
//
//  $_CIDLib_Log_$
//
#pragma once


#pragma CIDLIB_PACK(CIDLIBPACK)

// ---------------------------------------------------------------------------
//   CLASS: TSaveOptsDlg
//  PREFIX: dlg
// ---------------------------------------------------------------------------
class TSaveOptsDlg : public TDlgBox
{
    public :
        // -------------------------------------------------------------------
        //  Constructors and Destructor
        // -------------------------------------------------------------------
        TSaveOptsDlg();

        TSaveOptsDlg(const TSaveOptsDlg&) = delete;

        ~TSaveOptsDlg();


        // -------------------------------------------------------------------
        //  Public operators
        // -------------------------------------------------------------------
        TSaveOptsDlg& operator=(const TSaveOptsDlg&) = delete;


        // -------------------------------------------------------------------
        //  Public, non-virtual methods
        // -------------------------------------------------------------------
        tCIDWUtils::ESaveOpts eRun
        (
            const   TWindow&                wndOwner
            ,       tCIDLib::TBoolean&      bDoAll
            , const TString&                strSource
            , const tCIDLib::TBoolean       bMultiMode
        );


    protected :
        // -------------------------------------------------------------------
        //  Protected inherited methods
        // -------------------------------------------------------------------
        tCIDLib::TBoolean bCreated() override;


    private :
        // -------------------------------------------------------------------
        //  Private, non-virtual methods
        // -------------------------------------------------------------------
        tCIDCtrls::EEvResponses eClickHandler
        (
                    TButtClickInfo&         wnotEvent
        );


        // -------------------------------------------------------------------
        //  Private data members
        //
        //  m_bDoAll
        //      To save the 'do all' check box state until we can get it back to the caller.
        //
        //  m_bMultiMode
        //      If in multi-mode, we enable the 'ignore all' check box and return whatever
        //      the user indicates. Else, we hide it and 'do all' is always false.
        //
        //  m_strSource
        //      To save the incoming source until we can get it displayed
        // -------------------------------------------------------------------
        tCIDLib::TBoolean   m_bDoAll;
        tCIDLib::TBoolean   m_bMultiMode;
        TPushButton*        m_pwndCancel;
        TPushButton*        m_pwndDiscard;
        TCheckBox*          m_pwndDoAll;
        TPushButton*        m_pwndSave;
        TStaticText*        m_pwndSource;
        TString             m_strSource;


        // -------------------------------------------------------------------
        //  Magic Macros
        // -------------------------------------------------------------------
        RTTIDefs(TSaveOptsDlg,TDlgBox)
};

#pragma CIDLIB_POPPACK
