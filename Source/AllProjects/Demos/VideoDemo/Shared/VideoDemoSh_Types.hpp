// ----------------------------------------------------------------------------
//  FILE: VideoDemoSh_Types.hpp
//  DATE: Tue, Jan 29 23:33:30 2019 -0500
//
//  This file was generated by the Charmed Quark CIDIDL compiler. Do not make
//  changes by hand, because they will be lost if the file is regenerated.
// ----------------------------------------------------------------------------

#pragma CIDLIB_PACK(CIDLIBPACK)

// ----------------------------------------------------------------------------
// Types namespace
// ----------------------------------------------------------------------------
namespace tVideoDemoSh
{
    
    // ------------------------------------------------------------------------
    //  The status marital status of a patient
    //                  
    // ------------------------------------------------------------------------
    enum class EStatus
    {
        Divorced
        , Married
        , Single
        , Widowed
        , Count
        , Min = Divorced
        , Max = Widowed
    };
    VIDEODEMOSHEXP EStatus eXlatEStatus(const TString& strToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::False);
    VIDEODEMOSHEXP const TString& strXlatEStatus(const EStatus eToXlat, const tCIDLib::TBoolean bThrowIfNot = kCIDLib::True);
    VIDEODEMOSHEXP tCIDLib::TBoolean bIsValidEnum(const EStatus eVal);

}

#pragma CIDLIB_POPPACK

VIDEODEMOSHEXP TBinOutStream& operator<<(TBinOutStream& strmTar, const tVideoDemoSh::EStatus eToStream);
VIDEODEMOSHEXP TBinInStream& operator>>(TBinInStream& strmSrc, tVideoDemoSh::EStatus& eToFill);
VIDEODEMOSHEXP tCIDLib::TVoid TBinInStream_ReadArray(TBinInStream& strmSrc, tVideoDemoSh::EStatus* const aeList, const tCIDLib::TCard4 c4Count);
VIDEODEMOSHEXP tCIDLib::TVoid TBinOutStream_WriteArray(TBinOutStream& strmTar, const tVideoDemoSh::EStatus* const aeList, const tCIDLib::TCard4 c4Count);
VIDEODEMOSHEXP TTextOutStream& operator<<(TTextOutStream& strmTar, const tVideoDemoSh::EStatus eToStream);
