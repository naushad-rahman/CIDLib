//
// FILE NAME: CIDXML_ChildContentModel.hpp
//
// AUTHOR: Dean Roddey
//
// CREATED: 09/23/1999
//
// COPYRIGHT: $_CIDLib_CopyRight_$
//
//  $_CIDLib_CopyRight2_$
//
// DESCRIPTION:
//
//  This is the header file for the CIDXML_ChildContentModel.Cpp file, which
//  implements the TXMLChildCM class. This class is derived from the base
//  content model class, TXMLContentModel, and provides an implementation
//  for elements with the "Children" style content model.
//
//  This class implements a classic NFA to DFA transformation on the original
//  content spec node tree. It creates a deterministic automata that can very
//  quickly and efficiently validate regular expression type content models.
//
// CAVEATS/GOTCHAS:
//
// LOG:
//
//  $_CIDLib_Log_$
//
#pragma once


#pragma CIDLIB_PACK(CIDLIBPACK)

class TXMLCMSpecNode;
class TXMLCMLeaf;
class TXMLCMNode;


// ---------------------------------------------------------------------------
//  CLASS: TXMLChildCM
// PREFIX: xcm
// ---------------------------------------------------------------------------
class CIDXMLEXP TXMLChildCM : public TXMLContentModel
{
    public  :
        // -------------------------------------------------------------------
        //  Constructors and Destructor
        // -------------------------------------------------------------------
        TXMLChildCM
        (
                    TXMLCMSpecNode* const   pxcsnToAdopt
        );

        ~TXMLChildCM();


        // -------------------------------------------------------------------
        //  Public, inherited methods
        // -------------------------------------------------------------------
        tCIDXML::EValidRes eValidate
        (
            const   tCIDLib::TCard4* const  pc4ChildIds
            , const tCIDLib::TCard4         c4ChildCount
            ,       tCIDLib::TCard4&        c4FailedAt
        )   const;

        tCIDLib::TVoid FormatTo
        (
                    TTextOutStream&         strmDest
            , const TXMLValidator&          xvalPools
        )   const;


    protected :
        // -------------------------------------------------------------------
        //  Hidden constructors
        // -------------------------------------------------------------------
        TXMLChildCM();


    private :
        // -------------------------------------------------------------------
        //  Unimplemented constructors and operators
        // -------------------------------------------------------------------
        TXMLChildCM(const TXMLChildCM&);
        tCIDLib::TVoid operator=(const TXMLChildCM&);


        // -------------------------------------------------------------------
        //  Private, non-virtual methods
        // -------------------------------------------------------------------
        tCIDLib::TVoid BuildDFA();

        tCIDLib::TVoid BuildFollowLists
        (
                    TXMLCMNode* const       pxcmnCur
        );

        tCIDLib::TCard4 c4InitLeaves
        (
                    TXMLCMNode* const       pxcmnCur
            , const tCIDLib::TCard4         c4CurIndex
        );

        tCIDLib::TCard4* pc4NewTransTableEntry() const;

        TXMLCMNode* pxcmnRewriteTree
        (
            const   TXMLCMSpecNode* const   pxcsnCur
        );


        // -------------------------------------------------------------------
        //  Private data members
        //
        //  m_bCanBeEmpty
        //      In order to vastly speed up the simple case where we are asked
        //      to validate an empty list of child elements, we store this
        //      flag. Basically, if the root node of the original content is
        //      nullable, then it can be empty.
        //
        //  m_c4ElemListSize
        //      This holds the number of element ids in the m_pc4ElemList
        //      array.
        //
        //  m_c4EOCPosition
        //      This is the leaf position of the special end of content leaf
        //      node. This value is referenced quite a bit while building
        //      the DFA.
        //
        //  m_c4LeafCount
        //      This is the count of leaf nodes in the content mode. This is
        //      set during the rewrite of the original spec node tree. As it
        //      is counted up, those values are used to set the NFA position
        //      of each new leaf node added to the rewritten tree.
        //
        //  m_c4TransTableSize
        //      This is the number of entries in the transition table. It is
        //      calculated during the NFA to DFA transformation.
        //
        //  m_pbFinalFlags
        //      Tracks whether each new state set created is a final one or
        //      not. Its final if its states contain the EOC leaf.
        //
        //  m_pbtsFollowLists
        //      This is a list of bit sets which are filled with the caluclated
        //      follow lists for each non-epsilong leaf node.
        //
        //  m_pc4ElemList
        //      We have to have a list of unique possible element ids. This is
        //      used to convert an element id of this content model into a zero
        //      based index.
        //
        //  m_ppc4TransTable
        //      This is the actual transition table that all this fuss is
        //      about. Its an array of arrays of TCard4 values. Each row
        //      will represent a list of ways out of that particular state.
        //      Each column represents the next state  (if any) for any given
        //      input leaf.
        //
        //  m_pxcmnLeaves
        //      After we've built the rewritten tree, we store a sequential
        //      list of nodes for later use. We'll allocate this after we
        //      figure out how many leaves there are.
        //
        //  m_pxcmnRoot
        //      Before we can do the NFA to DFA algorithm, we have to rewrite
        //      the content spec nodes into a different form of tree. This
        //      is the root of that tree. This is faulted in when/if the
        //      eValidate() method is every called and can be dropped after
        //      the DFA is built.
        //
        //  m_pxcsnRoot
        //      This is the root of the content specification tree that
        //      represents the content model. Its adopted in the ctor.
        // -------------------------------------------------------------------
        tCIDLib::TBoolean   m_bCanBeEmpty;
        tCIDLib::TCard4     m_c4ElemListSize;
        tCIDLib::TCard4     m_c4EOCPosition;
        tCIDLib::TCard4     m_c4LeafCount;
        tCIDLib::TCard4     m_c4TransTableSize;
        tCIDLib::TBoolean*  m_pbFinalFlags;
        TBitset*            m_pbtsFollowLists;
        tCIDLib::TCard4*    m_pc4ElemList;
        tCIDLib::TCard4**   m_ppc4TransTable;
        TXMLCMLeaf**        m_pxcmnLeaves;
        TXMLCMNode*         m_pxcmnRoot;
        TXMLCMSpecNode*     m_pxcsnRoot;


        // -------------------------------------------------------------------
        //  Magic macros
        // -------------------------------------------------------------------
        RTTIDefs(TXMLChildCM,TXMLContentModel)
};

#pragma CIDLIB_POPPACK

