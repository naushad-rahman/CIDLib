//
// FILE NAME: CIDLib_BasicTreeCol.hpp
//
// AUTHOR: Dean Roddey
//
// CREATED: 02/11/2001
//
// COPYRIGHT: $_CIDLib_CopyRight_$
//
//  This file is part of a demonstration program of the CIDLib C++
//  Frameworks. Its contents are distributed 'as is', to provide guidance on
//  the use of the CIDLib system. However, these demos are not intended to
//  represent a full fledged applications. Any direct use of demo code in
//  user applications is at the user's discretion, and no warranties are
//  implied as to its correctness or applicability.
//
// DESCRIPTION:
//
//  This is the header for the templatized, by value, tree collection. It
//  contains two types of node, terminal and non-terminal. A terminal node
//  contains a value, while non-terminal nodes contain other child nodes (of
//  either type.)
//
//  This is not any sort of balanced tree. It is designed for simple tree
//  needs, where there is some other criteria driving the organization of the
//  tree, such as a natural hierarchical format.
//
//  We create a basic tree node, and derive from it a class each for terminal
//  and non-terminal nodes.
//
//  Each node, terminal or non-terminal, must have a name. This name is used
//  to maintain the child nodes in sorted order and to provide an addressing
//  mechanism.
//
//  To keep at least some of the code out of the template, since its already
//  large enough that instantiating it is piggy, we provide a namespace for
//  some helper methods that can be out of line.
//
// CAVEATS/GOTCHAS:
//
//  1)  Instantiation classes, TElem in this case, must support assignment
//      and copy construction, since this is a by value collection.
//
//  2)  The standard basic collection node class isn't of any use to us, so
//      we don't derive from it. This is no problem, since its not required
//      anyway, its just a convenience.
//
//  3)  Iteration is pre-order, depth first. So, we return a non-terminal
//      when we first hit it. Then the next call will iterate that node's
//      children, then come back up and do its siblings.
//
//  4)  All private methods assume that the public method that called it
//      will have already locked the collection if that is required.
//
// LOG:
//
//  $_CIDLib_Log_$
//
#pragma once


#pragma CIDLIB_PACK(CIDLIBPACK)

// Forward ref some local stuff
template <class TElem> class TTreeNodeNT;


// ---------------------------------------------------------------------------
//   CLASS: TBaseTreeNode
//  PREFIX: node
// ---------------------------------------------------------------------------
class CIDLIBEXP TBaseTreeNode : public TObject
{
    public :
        // -------------------------------------------------------------------
        //  Destructor
        // -------------------------------------------------------------------
        TBaseTreeNode(const TBaseTreeNode&) = delete;

        ~TBaseTreeNode();


        // -------------------------------------------------------------------
        //  Public operators
        // -------------------------------------------------------------------
        TBaseTreeNode& operator=(const TBaseTreeNode&) = delete;


        // -------------------------------------------------------------------
        //  Public, non-virtual methods
        // -------------------------------------------------------------------
        tCIDLib::TBoolean bHasDescription() const
        {
            return (m_pstrDescription != nullptr);
        }

        tCIDLib::ETreeNodes eType() const
        {
            return  m_eType;
        }

        const TString& strName() const
        {
            return m_strName;
        }

        const TString& strName(const TString& strToSet)
        {
            m_strName = strToSet;
            return m_strName;
        }

        const TString& strDescription() const;

        const TString& strDescription
        (
            const   TString&                strNew
        );


    protected :
        // -------------------------------------------------------------------
        //  Hidden constructors
        // -------------------------------------------------------------------
        TBaseTreeNode
        (
            const   tCIDLib::ETreeNodes     eType
            , const TString&                strName
            , const TString&                strDescription
        );


    private :
        // -------------------------------------------------------------------
        //  Private data members
        //
        //  m_eType
        //      The type of node. Its either a terminal or non-terminal. If
        //      its a terminal, it cannot have children. If its a non-terminal,
        //      it can only have children and no value.
        //
        //  m_pstrDescription
        //      Each node can have an optional descriptive name. This allows
        //      browsing the tree without having to get into the actual data.
        //      Since it might not be used in some cases, it is faulted in
        //      upon first use.
        //
        //  m_strName
        //      This is the name of this node. It is used to address this
        //      node within its peers, so it must be unique within its list
        //      of peers.
        // -------------------------------------------------------------------
        tCIDLib::ETreeNodes m_eType;
        mutable TString*    m_pstrDescription;
        TString             m_strName;


        // -------------------------------------------------------------------
        //  Magic Macros
        // -------------------------------------------------------------------
        RTTIDefs(TBaseTreeNode,TObject)
};


// ---------------------------------------------------------------------------
//  This namespace contains some helper methods for the collection. Don't
//  call them directly.
// ---------------------------------------------------------------------------
namespace TBasicTreeHelpers
{
    CIDLIBEXP tCIDLib::TVoid BadNode
    (
        const   tCIDLib::TCh* const     pszFile
        , const tCIDLib::TCard4         c4Line
    );

    CIDLIBEXP tCIDLib::TVoid BadPath
    (
        const   tCIDLib::TCh* const     pszFile
        , const tCIDLib::TCard4         c4Line
    );

    CIDLIBEXP tCIDLib::TVoid CheckNodeType
    (
        const   TBaseTreeNode* const    pnodeToCheck
        , const tCIDLib::ETreeNodes     eType
        , const tCIDLib::TCh* const     pszFile
        , const tCIDLib::TCard4         c4Line
    );

    CIDLIBEXP tCIDLib::TVoid CheckName
    (
        const   TString&                strToCheck
        , const tCIDLib::TCh* const     pszFile
        , const tCIDLib::TCard4         c4Line
    );

    CIDLIBEXP tCIDLib::TVoid CheckPath
    (
        const   TString&                strToCheck
        , const tCIDLib::TCh* const     pszFile
        , const tCIDLib::TCard4         c4Line
    );

    CIDLIBEXP tCIDLib::TVoid CheckPathAndName
    (
        const   TString&                strPathToCheck
        , const TString&                strNameToCheck
        , const tCIDLib::TCh* const     pszFile
        , const tCIDLib::TCard4         c4Line
    );

    CIDLIBEXP tCIDLib::TVoid DepthUnderflow
    (
        const   tCIDLib::TCh* const     pszFile
        , const tCIDLib::TCard4         c4Line
    );

    CIDLIBEXP tCIDLib::TVoid MustBeNonTerminal
    (
        const   tCIDLib::TCh* const     pszFile
        , const tCIDLib::TCard4         c4Line
        , const TString&                strName
    );

    CIDLIBEXP tCIDLib::TVoid NamedNodeNotFound
    (
        const   tCIDLib::TCh* const     pszFile
        , const tCIDLib::TCard4         c4Line
        , const TString&                strName
    );

    CIDLIBEXP tCIDLib::TVoid NotMemberNode
    (
        const   tCIDLib::TCh* const     pszFile
        , const tCIDLib::TCard4         c4Line
    );

    CIDLIBEXP tCIDLib::TVoid NotSupported
    (
        const   tCIDLib::TCh* const     pszFile
        , const tCIDLib::TCard4         c4Line
        , const tCIDLib::TCh* const     pszMethod
    );

    CIDLIBEXP tCIDLib::TVoid ThrowDup
    (
        const   tCIDLib::TCh* const     pszFile
        , const tCIDLib::TCard4         c4Line
        , const TString&                strName
    );
}


// ---------------------------------------------------------------------------
//   CLASS: TBasicTreeNode
//  PREFIX: node
// ---------------------------------------------------------------------------
template <class TElem> class TBasicTreeNode : public TBaseTreeNode
{
    public :
        // -------------------------------------------------------------------
        //  Destructor
        // -------------------------------------------------------------------
        TBasicTreeNode(const TBasicTreeNode<TElem>&) = delete;

        ~TBasicTreeNode()
        {
        }


        // -------------------------------------------------------------------
        //  Public operators
        // -------------------------------------------------------------------
        TBasicTreeNode<TElem>& operator=(const TBasicTreeNode<TElem>&) = delete;


        // -------------------------------------------------------------------
        //  Public, virtual methods
        // -------------------------------------------------------------------
        virtual tCIDLib::TBoolean bContainsNode
        (
            const   TBasicTreeNode<TElem>* const    pnodeToCheck
        )   const = 0;

        virtual tCIDLib::TVoid BuildFullName(TString& strToFill) = 0;

        virtual tCIDLib::TVoid ContainedNodes
        (
                    tCIDLib::TCard4&        c4TNodes
            ,       tCIDLib::TCard4&        c4NTNodes
        )   const = 0;


        // -------------------------------------------------------------------
        //  Public, non-virtual methods
        // -------------------------------------------------------------------
        const TElem& objData() const
        {
            return m_objData;
        }

        TElem& objData()
        {
            return m_objData;
        }

        TElem& objData(const TElem& objToSet)
        {
            m_objData = objToSet;
            return m_objData;
        }

        const TBasicTreeNode<TElem>* pnodeNext() const
        {
            return m_pnodeNext;
        }

        TBasicTreeNode<TElem>* pnodeNext()
        {
            return m_pnodeNext;
        }

        TBasicTreeNode<TElem>* pnodeNext(TBasicTreeNode<TElem>* const pnodeToSet)
        {
            m_pnodeNext = pnodeToSet;
            return m_pnodeNext;
        }

        const TTreeNodeNT<TElem>* pnodeParent() const
        {
            return m_pnodeParent;
        }

        TTreeNodeNT<TElem>* pnodeParent()
        {
            return m_pnodeParent;
        }


    protected :
        // -------------------------------------------------------------------
        //  Hidden constructors
        // -------------------------------------------------------------------
        TBasicTreeNode( const   tCIDLib::ETreeNodes         eType
                        , const TString&                    strName
                        , const TString&                    strDescription
                        ,       TTreeNodeNT<TElem>* const   pnodeParent
                        ,       TBasicTreeNode<TElem>*      pnodeNext = nullptr) :

            TBaseTreeNode(eType, strName, strDescription)
            , m_pnodeNext(pnodeNext)
            , m_pnodeParent(pnodeParent)
        {
        }

        TBasicTreeNode( const   TElem&                      objToCopy
                        , const tCIDLib::ETreeNodes         eType
                        , const TString&                    strName
                        , const TString&                    strDescription
                        ,       TTreeNodeNT<TElem>* const   pnodeParent
                        ,       TBasicTreeNode<TElem>*      pnodeNext = nullptr) :

            TBaseTreeNode(eType, strName, strDescription)
            , m_objData(objToCopy)
            , m_pnodeNext(pnodeNext)
            , m_pnodeParent(pnodeParent)
        {
        }



    private :
        // -------------------------------------------------------------------
        //  Private data members
        //
        //  m_objData
        //      This is the user data for this node.
        //
        //  m_pnodeNext
        //      Each parent node keeps its children in a linked list, to aid
        //      faster insertion and removal. So this is the link for the
        //      next member in the list.
        //
        //  m_pnodeParent
        //      In order to support backtracking up the tree, we store the
        //      parent node of each node.
        // -------------------------------------------------------------------
        TElem                       m_objData;
        TBasicTreeNode<TElem>*      m_pnodeNext;
        TTreeNodeNT<TElem>* const   m_pnodeParent;


        // -------------------------------------------------------------------
        //  Magic Macros
        // -------------------------------------------------------------------
        TemplateRTTIDefs(TBasicTreeNode<TElem>,TBaseTreeNode)
};


// ---------------------------------------------------------------------------
//   CLASS: TTreeNodeT
//  PREFIX: node
// ---------------------------------------------------------------------------
template <class TElem> class TTreeNodeT : public TBasicTreeNode<TElem>
{
    public :
        // -------------------------------------------------------------------
        //  Constructors and Destructor
        // -------------------------------------------------------------------
        TTreeNodeT(const TTreeNodeT<TElem>&) = delete;

        TTreeNodeT( const   TElem&                      objToCopy
                    , const TString&                    strName
                    , const TString&                    strDescription
                    ,       TTreeNodeNT<TElem>* const   pnodeParent) :

            TBasicTreeNode<TElem>
            (
                objToCopy
                , tCIDLib::ETreeNodes::Terminal
                , strName
                , strDescription
                , pnodeParent
            )
        {
        }

        ~TTreeNodeT()
        {
        }


        // -------------------------------------------------------------------
        //  Public operators
        // -------------------------------------------------------------------
        TTreeNodeT<TElem>& operator=(const TTreeNodeT<TElem>&) = delete;


        // -------------------------------------------------------------------
        //  Public, inherited methods
        // -------------------------------------------------------------------
        tCIDLib::TBoolean
        bContainsNode(const TBasicTreeNode<TElem>* const) const override
        {
            // We never contain anything
            return kCIDLib::False;
        }

        tCIDLib::TVoid BuildFullName(TString& strToFill) override
        {
            // Call our parent node first. As a non-terminal, we have to have one
            this->pnodeParent()->BuildFullName(strToFill);

            // And now add our name
            strToFill.Append(kCIDLib::chTreeSepChar);
            strToFill.Append(this->strName());
        }

        tCIDLib::TVoid
        ContainedNodes(tCIDLib::TCard4& c4TNodes, tCIDLib::TCard4&) const override
        {
            // Just count ourself
            c4TNodes++;
        }


    private :
        // -------------------------------------------------------------------
        //  Magic Macros
        // -------------------------------------------------------------------
        TemplateRTTIDefs(TreeNodeT<TElem>,TBasicTreeNode<TElem>)
};


// ---------------------------------------------------------------------------
//   CLASS: TTreeNodeNT
//  PREFIX: node
// ---------------------------------------------------------------------------
template <class TElem> class TTreeNodeNT : public TBasicTreeNode<TElem>
{
    public :
        // -------------------------------------------------------------------
        //  Constructors and Destructor
        // -------------------------------------------------------------------
        TTreeNodeNT(const TTreeNodeNT<TElem>&) = delete;

        TTreeNodeNT(const   TString&                    strName
                    , const TString&                    strDescription
                    ,       TTreeNodeNT<TElem>* const   pnodeParent) :

            TBasicTreeNode<TElem>
            (
                tCIDLib::ETreeNodes::NonTerminal
                , strName
                , strDescription
                , pnodeParent
            )
            , m_c4SerialNum(1)
            , m_pnodeRoot(nullptr)
        {
        }

        TTreeNodeNT(const   TElem&                      objToCopy
                    , const TString&                    strName
                    , const TString&                    strDescription
                    ,       TTreeNodeNT<TElem>* const   pnodeParent) :

            TBasicTreeNode<TElem>
            (
                objToCopy
                , tCIDLib::ETreeNodes::NonTerminal
                , strName
                , strDescription
                , pnodeParent
            )
            , m_c4SerialNum(1)
            , m_pnodeRoot(nullptr)
        {
        }

        ~TTreeNodeNT()
        {
            RemoveAll();
        }


        // -------------------------------------------------------------------
        //  Public operators
        // -------------------------------------------------------------------
        TTreeNodeNT<TElem>& operator=(const TTreeNodeNT<TElem>&) = delete;


        // -------------------------------------------------------------------
        //  Public, inherited methods
        // -------------------------------------------------------------------
        tCIDLib::TBoolean
        bContainsNode(const TBasicTreeNode<TElem>* const pnodeToCheck) const override
        {
            // Just iterate our children
            TBasicTreeNode<TElem>* pnodeCur = m_pnodeRoot;
            while (pnodeCur)
            {
                if (pnodeCur->bContainsNode(pnodeToCheck))
                    return kCIDLib::True;
                pnodeCur = pnodeCur->pnodeNext();
            }
            return kCIDLib::False;
        }

        tCIDLib::TVoid BuildFullName(TString& strToFill) override
        {
            //
            //  If we have a parent node, then call it first. Else, we are the
            //  root so we do nothing and the call chain will now collapse
            //  back up and the name will be built.
            //
            if (this->pnodeParent())
            {
                this->pnodeParent()->BuildFullName(strToFill);

                // And now add our name
                strToFill.Append(kCIDLib::chTreeSepChar);
                strToFill.Append(this->strName());
            }
        }

        tCIDLib::TVoid ContainedNodes(  tCIDLib::TCard4&    c4TNodes
                                        , tCIDLib::TCard4&  c4NTNodes) const override
        {
            // Just iterate our children
            TBasicTreeNode<TElem>* pnodeCur = m_pnodeRoot;
            while (pnodeCur)
            {
                //
                //  If the child is an NT, then count it, since it won't
                //  count itself, since they only count what's contained
                //  within them.
                //
                if (pnodeCur->eType() == tCIDLib::ETreeNodes::NonTerminal)
                    c4NTNodes++;

                pnodeCur->ContainedNodes(c4TNodes, c4NTNodes);
                pnodeCur = pnodeCur->pnodeNext();
            }
        }


        // -------------------------------------------------------------------
        //  Public, non-virtual methods
        // -------------------------------------------------------------------
        tCIDLib::TCard4 c4SerialNum() const
        {
            return m_c4SerialNum;
        }

        TTreeNodeNT<TElem>*
        pnodeAddNonTerminal(const   TString&            strName
                            , const TString&            strDescription
                            , const tCIDLib::TBoolean   bCaseSensitive
                            , const tCIDLib::TBoolean   bSorted)
        {
            // Create the new node we'll put in
            TTreeNodeNT<TElem>* pnodeNewNT = new TTreeNodeNT<TElem>
            (
                strName, strDescription, this
            );
            TJanitor<TTreeNodeNT<TElem> > janNew(pnodeNewNT);
            InsertNode(pnodeNewNT, bCaseSensitive, bSorted);
            janNew.Orphan();

            // Bump our serial number and return the new node
            m_c4SerialNum++;
            return pnodeNewNT;
        }

        TTreeNodeNT<TElem>*
        pnodeAddNonTerminal(const   TElem&              objToCopy
                            , const TString&            strName
                            , const TString&            strDescription
                            , const tCIDLib::TBoolean   bCaseSensitive
                            , const tCIDLib::TBoolean   bSorted)
        {
            // Create the new node we'll put in
            TTreeNodeNT<TElem>* pnodeNewNT = new TTreeNodeNT<TElem>
            (
                objToCopy, strName, strDescription, this
            );
            TJanitor<TTreeNodeNT<TElem> > janNew(pnodeNewNT);
            InsertNode(pnodeNewNT, bCaseSensitive, bSorted);
            janNew.Orphan();

            // Bump our serial number and return the new node
            m_c4SerialNum++;
            return pnodeNewNT;
        }

        TBasicTreeNode<TElem>* pnodeFind(const  TString&            strCur
                                        , const tCIDLib::TBoolean   bCaseSensitive)
        {
            // Search for a child with the passed name
            TBasicTreeNode<TElem>* pnodeCur = m_pnodeRoot;
            while (pnodeCur)
            {
                if (bCaseSensitive)
                {
                    if (strCur == pnodeCur->strName())
                        return pnodeCur;
                }
                 else
                {
                    if (strCur.bCompareI(pnodeCur->strName()))
                        return pnodeCur;
                }
                pnodeCur = pnodeCur->pnodeNext();
            }
            return nullptr;
        }

        TBasicTreeNode<TElem>* pnodeFirstChild() const
        {
            return m_pnodeRoot;
        }

        TElem& objAddTerminal(  const   TElem&              objToAdd
                                , const TString&            strName
                                , const TString&            strDescription
                                , const tCIDLib::TBoolean   bCaseSensitive
                                , const tCIDLib::TBoolean   bSorted)
        {
            // Create the new node we'll put in
            TTreeNodeT<TElem>* pnodeNewT = new TTreeNodeT<TElem>
            (
                objToAdd
                , strName
                , strDescription
                , this
            );
            TJanitor<TTreeNodeT<TElem> > janNew(pnodeNewT);
            InsertNode(pnodeNewT, bCaseSensitive, bSorted);
            janNew.Orphan();

            // Bump our serial number
            m_c4SerialNum++;

            //
            //  As a convenience, we return a ref to the newly added object.
            //  This keeps the user from having to turn right around and find
            //  this newly added object again after adding it.
            //
            return pnodeNewT->objData();
        }

        tCIDLib::TVoid RemoveAll()
        {
            //
            //  Run through the child list and delete each one. They will
            //  in turn delete their children and so on.
            //
            TBasicTreeNode<TElem>*  pnodeN   = nullptr;
            TBasicTreeNode<TElem>*  pnodeCur = m_pnodeRoot;
            while (pnodeCur)
            {
                // Remember the next node, then toast the current one
                pnodeN = pnodeCur->pnodeNext();
                delete pnodeCur;

                // And move forward to the saved next node
                pnodeCur = pnodeN;
            }

            // And clear out our members to indicate we are empty
            m_pnodeRoot  = 0;

            // Bump our serial number
            m_c4SerialNum++;
        }

        tCIDLib::TVoid RemoveChild(TBasicTreeNode<TElem>* const pnodeToRemove)
        {
            // Find this node in our child list
            TBasicTreeNode<TElem>*  pnodePrev = nullptr;
            TBasicTreeNode<TElem>*  pnodeCur  = m_pnodeRoot;
            while (pnodeCur)
            {
                if (pnodeCur == pnodeToRemove)
                {
                    // Ok, we have to patch around this guy
                    if (pnodePrev)
                        pnodePrev->pnodeNext(pnodeCur->pnodeNext());
                    else
                        m_pnodeRoot = pnodeCur->pnodeNext();

                    // And now delete the flushed node and break out
                    delete pnodeToRemove;

                    // Bump our serial number
                    m_c4SerialNum++;
                    return;
                }

                // Not it, so move forward
                pnodePrev   = pnodeCur;
                pnodeCur    = pnodeCur->pnodeNext();
            }

            // We didn't find it
            TBasicTreeHelpers::NotMemberNode(CID_FILE, CID_LINE);
        }


    private :
        // -------------------------------------------------------------------
        //  Private, non-virtual methods
        // -------------------------------------------------------------------

        //
        //  Finds the insert point for a new node (could be T or NT), and checks
        //  for dups.
        //
        tCIDLib::TVoid
        InsertNode(         TBasicTreeNode<TElem>* const    pnodeAdd
                    , const tCIDLib::TBoolean               bCaseSensitive
                    , const tCIDLib::TBoolean               bSorted)
        {
            TBasicTreeNode<TElem>* pnodeCur  = m_pnodeRoot;
            TBasicTreeNode<TElem>* pnodePrev = nullptr;
            tCIDLib::TBoolean      bDup      = kCIDLib::False;

            const TString& strNewName = pnodeAdd->strName();
            if (pnodeCur)
            {
                //
                //  There are existing nodes, so we need to find the insert
                //  point. If not sorting, then just go to the end. Else,
                //  we find the sorted insert point. If not case sensitive,
                //  then we have to do case insensitive compares for both
                //  dups and insert comparisons.
                //
                tCIDLib::ESortComps eComp;
                if (bCaseSensitive)
                {
                    while (pnodeCur)
                    {
                        // If a dup, then set flag and break out
                        eComp = pnodeCur->strName().eCompare(strNewName);
                        if (eComp == tCIDLib::ESortComps::Equal)
                        {
                            bDup = kCIDLib::True;
                            break;
                        }
                        if (bSorted && (eComp == tCIDLib::ESortComps::FirstGreater))
                            break;
                        pnodePrev = pnodeCur;
                        pnodeCur = pnodeCur->pnodeNext();
                    }
                }
                 else
                {
                    TString strTmp1(strNewName);
                    strTmp1.ToUpper();
                    TString strTmp2;
                    while (pnodeCur)
                    {
                        strTmp2 = pnodeCur->strName();
                        strTmp2.ToUpper();
                        eComp = strTmp1.eCompare(strTmp2);
                        if (eComp == tCIDLib::ESortComps::Equal)
                        {
                            bDup = kCIDLib::True;
                            break;
                        }
                        if (bSorted && (eComp == tCIDLib::ESortComps::FirstGreater))
                            break;
                        pnodePrev = pnodeCur;
                        pnodeCur = pnodeCur->pnodeNext();
                    }
                }
            }

            // If a dup, we can't take it
            if (bDup)
                TBasicTreeHelpers::ThrowDup(CID_FILE, CID_LINE, pnodeAdd->strName());

            if (pnodePrev)
            {
                // Its going in after some other node
                pnodeAdd->pnodeNext(pnodePrev->pnodeNext());
                pnodePrev->pnodeNext(pnodeAdd);
            }
             else
            {
                // Its becoming the new root
                pnodeAdd->pnodeNext(m_pnodeRoot);
                m_pnodeRoot = pnodeAdd;
            }
        }


        // -------------------------------------------------------------------
        //  Private data members
        //
        //  m_c4SerialNum
        //      This is initialized to 1 and is bumped any time our child list is
        //      modified. Not the actual contents of terminals, but removeall or
        //      additions of nodes.
        //
        //  m_pnodeRoot
        //      A pointer to the root node of the children in this list. The
        //      children are maintained as a simple singly linked list, to
        //      optimize insertion in sorted order.
        // -------------------------------------------------------------------
        tCIDLib::TCard4         m_c4SerialNum;
        TBasicTreeNode<TElem>*  m_pnodeRoot;


        // -------------------------------------------------------------------
        //  Magic Macros
        // -------------------------------------------------------------------
        TemplateRTTIDefs(TreeNodeT<TElem>,TBasicTreeNode<TElem>)
};


// ---------------------------------------------------------------------------
//   CLASS: TBasicTreeCol
//  PREFIX: col
// ---------------------------------------------------------------------------
template <class TElem> class TBasicTreeCol : public TCollection<TElem>
{
    public :
        // -------------------------------------------------------------------
        //  Nested aliases for the node types used by this collection
        // -------------------------------------------------------------------
        using TMyType = TBasicTreeCol<TElem>;
        using TNode = TBasicTreeNode<TElem>;
        using TNodeT = TTreeNodeT<TElem>;
        using TNodeNT = TTreeNodeNT<TElem>;


        // -------------------------------------------------------------------
        //  Our nested cursor classes
        // -------------------------------------------------------------------
        template <class TElem> class TConstCursor : public TColCursor<TElem>
        {
            public  :
                // -----------------------------------------------------------
                //  Constructors and Destructor
                // -----------------------------------------------------------
                TConstCursor() :

                    m_c4Depth(0)
                    , m_pcolCursoring(nullptr)
                    , m_pnodeCur(nullptr)
                {
                }

                explicit  TConstCursor(const TMyType* const pcolToCursor) :

                    TParent(pcolToCursor)
                    , m_c4Depth(0)
                    , m_pcolCursoring(pcolToCursor)
                    , m_pnodeCur(m_pcolCursoring->m_pnodeRoot->pnodeFirstChild())
                {
                }

                // We have to lock first, so we can't use member init!
                TConstCursor(const TConstCursor& cursSrc)
                {
                    operator=(cursSrc);
                }

                ~TConstCursor()
                {
                }


                // -----------------------------------------------------------
                //  Public operators
                // -----------------------------------------------------------
                TConstCursor& operator=(const TConstCursor& cursSrc)
                {
                    if (this != &cursSrc)
                    {
                        TMtxLocker lockCol
                        (
                            cursSrc.m_pcolCursoring
                            ? cursSrc.m_pcolCursoring->pmtxLock() : nullptr
                        );

                        TParent::operator=(cursSrc);
                        m_c4Depth       = cursSrc.m_c4Depth;
                        m_pcolCursoring = cursSrc.m_pcolCursoring;
                        m_pnodeCur      = cursSrc.m_pnodeCur;
                    }
                    return *this;
                }

                tCIDLib::TBoolean operator==(const TConstCursor& cursSrc) const
                {
                    if (!TParent::operator==(cursSrc))
                        return kCIDLib::False;
                    return
                    (
                        (m_c4Depth == cursSrc.m_c4Depth)
                        && (m_pnodeCur == cursSrc.m_pnodeCur)
                    );
                }

                tCIDLib::TBoolean operator!=(const TConstCursor& cursSrc) const
                {
                    return !TConstCursor::operator==(cursSrc);
                }

                TConstCursor& operator++()
                {
                    this->bNext();
                    return *this;
                }

                TConstCursor operator++(int)
                {
                    TConstCursor cursTmp(*this);
                    this->bNext();
                    return cursTmp;
                }


                // -----------------------------------------------------------
                //  Public, inherited methods
                // -----------------------------------------------------------
                tCIDLib::TBoolean bIsValid() const override
                {
                    if (!TParent::bIsValid())
                        return kCIDLib::False;
                    return (m_pnodeCur != nullptr);
                }

                tCIDLib::TBoolean bNext() override
                {
                    this->CheckInitialized(CID_FILE, CID_LINE);

                    TMtxLocker lockCol(m_pcolCursoring->pmtxLock());
                    this->CheckSerialNum(m_pcolCursoring->c4SerialNum(), CID_FILE, CID_LINE);
                    if (!m_pnodeCur)
                        return kCIDLib::False;
                    m_pnodeCur = m_pcolCursoring->pnodeFindNext(m_pnodeCur, m_c4Depth);
                    return (m_pnodeCur != nullptr);
                }

                tCIDLib::TBoolean bReset() override
                {
                    this->CheckInitialized(CID_FILE, CID_LINE);

                    TMtxLocker lockCol(m_pcolCursoring->pmtxLock());
                    m_pnodeCur  = m_pcolCursoring->m_pnodeRoot->pnodeFirstChild();
                    m_c4Depth   = 0;
                    this->c4SerialNum(m_pcolCursoring->c4SerialNum());
                    return (m_pnodeCur != nullptr);
                }

                const TElem& objRCur() const override
                {
                    this->CheckInitialized(CID_FILE, CID_LINE);

                    TMtxLocker lockCol(m_pcolCursoring->pmtxLock());
                    this->CheckSerialNum(m_pcolCursoring->c4SerialNum(), CID_FILE, CID_LINE);
                    this->CheckValid(m_pnodeCur, CID_FILE, CID_LINE);
                    return static_cast<TNode*>(m_pnodeCur)->objData();
                }

                // -----------------------------------------------------------
                //  Public, non-virtual methods
                // -----------------------------------------------------------
                tCIDLib::ETreeNodes eCurType() const
                {
                    this->CheckInitialized(CID_FILE, CID_LINE);

                    // Lock, check the serial number and node validity
                    TMtxLocker lockCol(m_pcolCursoring->pmtxLock());
                    this->CheckSerialNum(m_pcolCursoring->c4SerialNum(), CID_FILE, CID_LINE);
                    this->CheckValid(m_pnodeCur, CID_FILE, CID_LINE);
                    return m_pnodeCur->eType();
                }

                tCIDLib::TCard4 c4Depth() const
                {
                    return m_c4Depth;
                }

                const TNode* pnodeCur() const
                {
                    this->CheckInitialized(CID_FILE, CID_LINE);

                    TMtxLocker lockCol(m_pcolCursoring->pmtxLock());
                    this->CheckSerialNum(m_pcolCursoring->c4SerialNum(), CID_FILE, CID_LINE);
                    return m_pnodeCur;
                }

                TNode* pnodeCur()
                {
                    this->CheckInitialized(CID_FILE, CID_LINE);

                    TMtxLocker lockCol(m_pcolCursoring->pmtxLock());
                    this->CheckSerialNum(m_pcolCursoring->c4SerialNum(), CID_FILE, CID_LINE);
                    return m_pnodeCur;
                }

                const TString& strCurDescription() const
                {
                    this->CheckInitialized(CID_FILE, CID_LINE);

                    TMtxLocker lockCol(m_pcolCursoring->pmtxLock());
                    this->CheckSerialNum(m_pcolCursoring->c4SerialNum(), CID_FILE, CID_LINE);
                    this->CheckValid(m_pnodeCur, CID_FILE, CID_LINE);
                    return m_pnodeCur->strDescription();
                }

                const TString& strCurName() const
                {
                    this->CheckInitialized(CID_FILE, CID_LINE);

                    TMtxLocker lockCol(m_pcolCursoring->pmtxLock());
                    this->CheckSerialNum(m_pcolCursoring->c4SerialNum(), CID_FILE, CID_LINE);
                    this->CheckValid(m_pnodeCur, CID_FILE, CID_LINE);
                    return m_pnodeCur->strName();
                }


            protected :
                // -----------------------------------------------------------
                //  Declare our friends
                // -----------------------------------------------------------
                friend class TMyType;


            private :
                // -----------------------------------------------------------
                //  Private data members
                //
                //  m_c4Depth
                //      We use this to keep up with the current depth during
                //      cursoring. Its not for our use, just a convenience for the
                //      client code.
                //
                //  m_pcolCursoring
                //      The basic tree collection we are cursoring.
                //
                //  m_pnodeCur
                //      This is the current node that we are on in our iteration.
                //      It is null if we are at the end.
                // -----------------------------------------------------------
                tCIDLib::TCard4     m_c4Depth;
                const TMyType*      m_pcolCursoring;
                TNode*              m_pnodeCur;


                // -----------------------------------------------------------
                //  Do any needed magic macros
                // -----------------------------------------------------------
                TemplateRTTIDefs
                (
                    TBasicTreeCol::TConstCursor<TElem>
                    , TColCursor<TElem>
                )
        };

        template <class TElem> class TNonConstCursor : public TConstCursor<TElem>
        {
            public  :
                // -----------------------------------------------------------
                //  Constructors and Destructor
                // -----------------------------------------------------------
                TNonConstCursor() :

                    m_pcolNCCursoring(nullptr)
                {
                }

                explicit  TNonConstCursor(TMyType* const pcolToCursor) :

                    TParent(pcolToCursor)
                    , m_pcolNCCursoring(pcolToCursor)
                {
                }

                // We have to lock first, so we can't use member init!
                TNonConstCursor(const TNonConstCursor& cursSrc)
                {
                    operator=(cursSrc);
                }

                ~TNonConstCursor()
                {
                }


                // -----------------------------------------------------------
                //  Public operators
                // -----------------------------------------------------------
                TNonConstCursor& operator=(const TNonConstCursor& cursSrc)
                {
                    if (this != &cursSrc)
                    {
                        TMtxLocker lockCol
                        (
                            cursSrc.m_pcolNCCursoring
                            ? cursSrc.m_pcolNCCursoring->pmtxLock() : nullptr
                        );
                        TParent::operator=(cursSrc);
                        m_pcolNCCursoring = cursSrc.m_pcolNCCursoring;
                    }
                    return *this;
                }

                TElem& operator*() const
                {
                    TMtxLocker lockCol(m_pcolNCCursoring->pmtxLock());
                    this->CheckSerialNum(m_pcolNCCursoring->c4SerialNum(), CID_FILE, CID_LINE);
                    this->CheckValid(this->bIsValid(), CID_FILE, CID_LINE);
                    return const_cast<TElem&>
                    (
                        static_cast<const TNode*>(this->pnodeCur())->objData()
                    );
                }

                TElem* operator->() const
                {
                    TMtxLocker lockCol(m_pcolNCCursoring->pmtxLock());
                    this->CheckSerialNum(m_pcolNCCursoring->c4SerialNum(), CID_FILE, CID_LINE);
                    this->CheckValid(this->bIsValid(), CID_FILE, CID_LINE);
                    return &const_cast<TElem&>
                    (
                        static_cast<const TNode*>(this->pnodeCur())->objData()
                    );
                }

                TNonConstCursor& operator++()
                {
                    this->bNext();
                    return *this;
                }

                TNonConstCursor operator++(int)
                {
                    TNonConstCursor cursTmp(*this);
                    this->bNext();
                    return cursTmp;
                }


                // -----------------------------------------------------------
                //  Public, non-virtual methods
                // -----------------------------------------------------------
                TElem& objWCur() const
                {
                    this->CheckInitialized(CID_FILE, CID_LINE);

                    // Lock, check the serial number and node validity
                    TMtxLocker lockCol(m_pcolNCCursoring->pmtxLock());
                    this->CheckSerialNum(m_pcolNCCursoring->c4SerialNum(), CID_FILE, CID_LINE);
                    this->CheckValid(this->bIsValid(), CID_FILE, CID_LINE);
                    return const_cast<TElem&>
                    (
                        static_cast<const TNode*>(this->pnodeCur())->objData()
                    );
                }


            private :
                // -----------------------------------------------------------
                //  Private data members
                //
                //  m_pcolNCCursoring
                //      Our non-const pointer to the cursor we are working on
                // -----------------------------------------------------------
                TMyType*    m_pcolNCCursoring;


                // -----------------------------------------------------------
                //  Do any needed magic macros
                // -----------------------------------------------------------
                TemplateRTTIDefs
                (
                    TBasicTreeCol::TNonConstCursor<TElem>
                    , TBasicTreeCol::TConstCursor<TElem>
                )
        };


        template <class TElem> class TConstScopeCursor : public TColCursor<TElem>
        {
            public  :
                // -----------------------------------------------------------
                //  Constructors and Destructor
                // -----------------------------------------------------------
                TConstScopeCursor() :

                    m_c4Depth(0)
                    , m_pcolCursoring(nullptr)
                    , m_pnodeCur(nullptr)
                    , m_pnodeParent(nullptr)
                {
                }

                TConstScopeCursor(  const   TMyType* const  pcolToCursor
                                    , const TString&        strStartNode) :

                    TParent(pcolToCursor)
                    , m_c4Depth(0)
                    , m_pcolCursoring(pcolToCursor)
                    , m_pnodeCur(nullptr)
                    , m_pnodeParent(nullptr)
                {
                    //
                    //  Find our start node. This will also initialize our depth
                    //  value to the depth that the starting node was found at.
                    //
                    m_pnodeCur = pcolToCursor->pnodeFindNode
                    (
                        strStartNode, m_c4Depth, kCIDLib::True
                    );

                    // It has to be a non-terminal. If so, then cast and store it
                    TBasicTreeHelpers::CheckNodeType
                    (
                        m_pnodeCur, tCIDLib::ETreeNodes::NonTerminal, CID_FILE, CID_LINE
                    );
                    m_pnodeParent = static_cast<TNodeNT*>(m_pnodeCur);

                    // And now get the real current node, which is the first child
                    m_pnodeCur = m_pnodeParent->pnodeFirstChild();
                }

                // We have to lock first, so we can't use member init!
                TConstScopeCursor(const TConstScopeCursor& cursSrc)
                {
                    TConstScopeCursor::operator=(cursSrc);
                }

                ~TConstScopeCursor()
                {
                }


                // -----------------------------------------------------------
                //  Public operators
                // -----------------------------------------------------------
                TConstScopeCursor& operator=(const TConstScopeCursor& cursSrc)
                {
                    if (this != &cursSrc)
                    {
                        TMtxLocker lockCol
                        (
                            cursSrc.m_pcolCursoring
                            ? cursSrc.m_pcolCursoring->pmtxLock() : nullptr
                        );

                        TParent::operator=(cursSrc);
                        m_c4Depth       = cursSrc.m_c4Depth;
                        m_pcolCursoring = cursSrc.m_pcolCursoring;
                        m_pnodeCur      = cursSrc.m_pnodeCur;
                        m_pnodeParent   = cursSrc.m_pnodeParent;
                    }
                    return *this;
                }

                tCIDLib::TBoolean operator==(const TConstScopeCursor& cursSrc) const
                {
                    if (!TParent::operator==(cursSrc))
                        return kCIDLib::False;
                    return
                    (
                        (m_c4Depth == cursSrc.m_c4Depth)
                        && (m_pnodeParent == cursSrc.m_pnodeParent)
                        && (m_pnodeCur == cursSrc.m_pnodeCur)
                    );
                }

                tCIDLib::TBoolean operator!=(const TConstScopeCursor& cursSrc) const
                {
                    return !TConstScopeCursor::operator==(cursSrc);
                }


                // -----------------------------------------------------------
                //  Public, inherited methods
                // -----------------------------------------------------------
                tCIDLib::TBoolean bIsValid() const override
                {
                    if (!TParent::bIsValid())
                        return kCIDLib::False;
                    return (m_pnodeCur != nullptr);
                }

                tCIDLib::TBoolean bNext() override
                {
                    this->CheckInitialized(CID_FILE, CID_LINE);

                    TMtxLocker lockCol(m_pcolCursoring->pmtxLock());
                    m_pnodeCur = m_pnodeCur->pnodeNext();
                    return (m_pnodeCur != nullptr);
                }

                tCIDLib::TBoolean bReset() override
                {
                    this->CheckInitialized(CID_FILE, CID_LINE);

                    TMtxLocker lockCol(m_pcolCursoring->pmtxLock());
                    m_pnodeCur  = m_pnodeParent->pnodeFirstChild();

                    // Get our serial num back in sync with the collection
                    this->c4SerialNum(m_pcolCursoring->c4SerialNum());
                    return (m_pnodeCur != nullptr);
                }

                const TElem& objRCur() const override
                {
                    this->CheckInitialized(CID_FILE, CID_LINE);

                    // Lock, check the serial number, and node validity
                    TMtxLocker lockCol(m_pcolCursoring->pmtxLock());
                    this->CheckSerialNum(m_pcolCursoring->c4SerialNum(), CID_FILE, CID_LINE);
                    this->CheckValid(m_pnodeCur, CID_FILE, CID_LINE);

                    return static_cast<TNode*>(m_pnodeCur)->objData();
                }

                // -----------------------------------------------------------
                //  Public, non-virtual methods
                // -----------------------------------------------------------
                tCIDLib::TCard4 c4Depth() const
                {
                    return m_c4Depth;
                }

                tCIDLib::ETreeNodes eCurType() const
                {
                    this->CheckInitialized(CID_FILE, CID_LINE);

                    // Lock, check the serial number and node validity
                    TMtxLocker lockCol(m_pcolCursoring->pmtxLock());
                    this->CheckSerialNum(m_pcolCursoring->c4SerialNum(), CID_FILE, CID_LINE);
                    this->CheckValid(m_pnodeCur, CID_FILE, CID_LINE);
                    return m_pnodeCur->eType();
                }

                const TNode* pnodeCur() const
                {
                    this->CheckInitialized(CID_FILE, CID_LINE);

                    TMtxLocker lockCol(m_pcolCursoring->pmtxLock());
                    this->CheckSerialNum(m_pcolCursoring->c4SerialNum(), CID_FILE, CID_LINE);
                    return m_pnodeCur;
                }

                TNode* pnodeCur()
                {
                    this->CheckInitialized(CID_FILE, CID_LINE);

                    TMtxLocker lockCol(m_pcolCursoring->pmtxLock());
                    this->CheckSerialNum(m_pcolCursoring->c4SerialNum(), CID_FILE, CID_LINE);
                    return m_pnodeCur;
                }

                const TString& strCurDescription() const
                {
                    this->CheckInitialized(CID_FILE, CID_LINE);

                    TMtxLocker lockCol(m_pcolCursoring->pmtxLock());
                    this->CheckSerialNum(m_pcolCursoring->c4SerialNum(), CID_FILE, CID_LINE);
                    this->CheckValid(m_pnodeCur, CID_FILE, CID_LINE);
                    return m_pnodeCur->strDescription();
                }

                const TString& strCurName() const
                {
                    this->CheckInitialized(CID_FILE, CID_LINE);

                    TMtxLocker lockCol(m_pcolCursoring->pmtxLock());
                    this->CheckSerialNum(m_pcolCursoring->c4SerialNum(), CID_FILE, CID_LINE);
                    this->CheckValid(m_pnodeCur, CID_FILE, CID_LINE);
                    return m_pnodeCur->strName();
                }


            private :
                // -----------------------------------------------------------
                //  Private data members
                //
                //  m_c4Depth
                //      Our current depth in the tree. We set this during reset
                //      and keep it around for client's convenience.
                //
                //  m_pcolCursoring
                //      The collection that we are cursoring. We need it in order
                //      re-sync and to watch for invalidation.
                //
                //  m_pnodeParent
                //      The parent node that we are cursoring. We have to have
                //      it in case they reset us.
                //
                //  m_pnodeCur
                //      Our current node of the parent. Its zero if we've hit
                //      the end, or the parent had no children.
                // -----------------------------------------------------------
                tCIDLib::TCard4     m_c4Depth;
                const TMyType*      m_pcolCursoring;
                TNodeNT*            m_pnodeParent;
                TNode*              m_pnodeCur;


                // -----------------------------------------------------------
                //  Do any needed magic macros
                // -----------------------------------------------------------
                TemplateRTTIDefs(TConstScopeCursor<TElem>,TColCursor<TElem>)
        };


        template <class TElem> class TNonConstScopeCursor : public TConstScopeCursor<TElem>
        {
            public  :
                // -----------------------------------------------------------
                //  Constructors and Destructor
                // -----------------------------------------------------------
                TNonConstScopeCursor() :

                    m_pcolNCCursoring(nullptr)
                {
                }

                TNonConstScopeCursor(       TBasicTreeCol<TElem>* const pcolToCursor
                                    , const TString&                    strStartNode) :

                    TParent(pcolToCursor, strStartNode)
                    , m_pcolNCCursoring(pcolToCursor)
                {
                }

                // We have to lock first, so we can't use member init!
                TNonConstScopeCursor(const TNonConstScopeCursor<TElem>& cursSrc)
                {
                    TNonConstScopeCursor::operator=(cursSrc);
                }

                ~TNonConstScopeCursor()
                {
                }


                // -----------------------------------------------------------
                //  Public operators
                // -----------------------------------------------------------
                TNonConstScopeCursor& operator=(const TNonConstScopeCursor& cursSrc)
                {
                    if (this != &cursSrc)
                    {
                        TMtxLocker lockCol
                        (
                            cursSrc.m_pcolNCCursoring
                            ? cursSrc.m_pcolNCCursoring->pmtxLock() : nullptr
                        );

                        TParent::operator=(cursSrc);
                        m_pcolNCCursoring = cursSrc.m_pcolNCCursoring;
                    }
                    return *this;
                }


                // -----------------------------------------------------------
                //  Public, non-virtual methods
                // -----------------------------------------------------------
                TElem& objWCur()
                {
                    this->CheckInitialized(CID_FILE, CID_LINE);

                    // Lock, check the serial number, and node validity
                    TMtxLocker lockCol(m_pcolNCCursoring->pmtxLock());
                    this->CheckSerialNum(m_pcolNCCursoring->c4SerialNum(), CID_FILE, CID_LINE);
                    this->CheckValid(this->pnodeCur(), CID_FILE, CID_LINE);

                    return static_cast<TNode*>(this->pnodeCur())->objData();

                }


            private :
                // -----------------------------------------------------------
                //  Private data members
                //
                //  m_pcolNCCursoring
                //      Our non-const pointer to the cursor we are working on
                // -----------------------------------------------------------
                TMyType*   m_pcolNCCursoring;


                // -----------------------------------------------------------
                //  Do any needed magic macros
                // -----------------------------------------------------------
                TemplateRTTIDefs
                (
                    TMyTpye::TNonConstScopeCursor<TElem>
                    , TMyType::TConstScopeCursor<TElem>
                )
        };


        // -------------------------------------------------------------------
        //  Aliases for our cursors
        // -------------------------------------------------------------------
        using TCursor           = TConstCursor<TElem>;
        using TNCCursor         = TNonConstCursor<TElem>;
        using TScopeCursor      = TConstScopeCursor<TElem>;
        using TNCScopeCursor    = TNonConstScopeCursor<TElem>;


        // -------------------------------------------------------------------
        //  Constructors and Destructor
        // -------------------------------------------------------------------
        TBasicTreeCol(  const   tCIDLib::EMTStates  eMTSafe = tCIDLib::EMTStates::Unsafe
                        , const tCIDLib::TBoolean   bCasePaths = kCIDLib::True
                        , const tCIDLib::TBoolean   bSorted = kCIDLib::True) :

            TCollection<TElem>(eMTSafe)
            , m_bCasePath(bCasePaths)
            , m_bSorted(bSorted)
            , m_c4NTCount(0)
            , m_c4TCount(0)
            , m_pnodeRoot(new TNodeNT(L"Root", L"$Root$", nullptr))
        {
        }

        TBasicTreeCol(const TBasicTreeCol<TElem>& colToCopy) :

            TCollection<TElem>(colToCopy)
            , m_bCasePath(colToCopy.m_bCasePath)
            , m_bSorted(colToCopy.m_bSorted)
            , m_c4TCount(colToCopy.m_c4TCount)
            , m_c4NTCount(colToCopy.m_c4NTCount)
            , m_pnodeRoot(new TNodeNT(L"Root", L"$Root$", nullptr))
        {
            // Do a recursive replication of the tree
            ReplicateNodes(colToCopy.m_pnodeRoot, m_pnodeRoot);
        }

        TBasicTreeCol(TBasicTreeCol<TElem>&&) = delete;

        ~TBasicTreeCol()
        {
            // Remove all the stuff under the root
            try
            {
                RemoveAll();
            }

            catch(...)
            {
            }

            // And delete the root itself
            delete m_pnodeRoot;
        }


        // -------------------------------------------------------------------
        //  Public operators
        // -------------------------------------------------------------------
        TBasicTreeCol<TElem>& operator=(const TBasicTreeCol<TElem>& colToAssign)
        {
            if (this != &colToAssign)
            {
                TMtxLocker lockThis(this->pmtxLock());
                TMtxLocker lockSource(colToAssign.pmtxLock());
                TParent::operator=(colToAssign);

                // Flush our current root node
                m_pnodeRoot->RemoveAll();

                m_bCasePath  = colToAssign.m_bCasePath;
                m_bSorted    = colToAssign.m_bSorted;
                m_c4NTCount  = colToAssign.m_c4NTCount;
                m_c4TCount   = colToAssign.m_c4TCount;

                // Do this AFTER setting sorted/case flags
                ReplicateNodes(colToAssign.m_pnodeRoot, m_pnodeRoot);
            }
            return *this;
        }

        TBasicTreeCol<TElem>& operator=(TBasicTreeCol<TElem>&&) = delete;


        // -------------------------------------------------------------------
        //  Public, inherited methods
        // -------------------------------------------------------------------
        tCIDLib::TBoolean bIsEmpty() const override
        {
            TMtxLocker lockThis(this->pmtxLock());
            return ((m_c4TCount + m_c4NTCount) == 0);
        }

        tCIDLib::TCard4 c4ElemCount() const override
        {
            TMtxLocker lockThis(this->pmtxLock());

            // Return cum of terminal and non-terminal nodes
            return m_c4TCount + m_c4NTCount;
        }

        tCIDLib::TVoid RemoveAll() override
        {
            TMtxLocker lockThis(this->pmtxLock());
            if (m_c4TCount + m_c4NTCount == 0)
                return;

            // Flush the root node, which will flush everyone else
            m_pnodeRoot->RemoveAll();
            m_c4TCount  = 0;
            m_c4NTCount = 0;

            // Bump serial number to invalidate cursors
            this->c4IncSerialNum();
        }

        TElem& objAdd(const TElem&) override
        {
            //
            //  This type of collection really doesn't fit too well into the
            //  generic collection scheme, so this operation isn't really
            //  supportable. We don't know where to put it or what its name
            //  should be.
            //
            TBasicTreeHelpers::NotSupported(CID_FILE, CID_LINE, L"objAdd");

            // Make the compiler happy. It will never get called
            static TElem* pobjTmp = nullptr;
            return *pobjTmp;
        }

        TCursor* pcursNew() const override
        {
            TMtxLocker lockThis(this->pmtxLock());
            return new TCursor(this);
        }


        // -------------------------------------------------------------------
        //  Public, non-virtual methods
        // -------------------------------------------------------------------
        tCIDLib::TBoolean bNodeExists(const TString& strToCheck) const
        {
            // Validate the passed path
            TBasicTreeHelpers::CheckPath(strToCheck, CID_FILE, CID_LINE);

            // Looks ok, so lets lock and try to find it
            TMtxLocker lockThis(this->pmtxLock());
            tCIDLib::TCard4 c4Dummy;
            return (pnodeFindNode(strToCheck, c4Dummy) != nullptr);
        }

        tCIDLib::TBoolean bNodeExists(  const   TString&             strToCheck
                                        ,       tCIDLib::ETreeNodes& eToFill) const
        {
            // Validate the passed path
            TBasicTreeHelpers::CheckPath(strToCheck, CID_FILE, CID_LINE);

            // Looks ok, so lets lock and try to find it
            TMtxLocker lockThis(this->pmtxLock());
            tCIDLib::TCard4 c4Dummy;
            TNode* pnodeTmp = pnodeFindNode(strToCheck, c4Dummy);
            if (pnodeTmp)
                eToFill = pnodeTmp->eType();
            return (pnodeTmp != nullptr);
        }

        tCIDLib::TCard4 c4NonTerminalCount() const
        {
            TMtxLocker lockThis(this->pmtxLock());
            return m_c4NTCount;
        }

        tCIDLib::TCard4 c4ScopeSerialNum(const TString& strScopePath) const
        {
            // Validate the passed path
            TBasicTreeHelpers::CheckPath(strScopePath, CID_FILE, CID_LINE);

            // Looks ok, so lets lock the collection and start working
            TMtxLocker lockThis(this->pmtxLock());

            // Find the node and make sure it's a scope, casting it to the right type
            tCIDLib::TCard4 c4Dummy;
            TNode* pnodeToFind = pnodeFindNode(strScopePath, c4Dummy, kCIDLib::True);
            TBasicTreeHelpers::CheckNodeType
            (
                pnodeToFind, tCIDLib::ETreeNodes::NonTerminal, CID_FILE, CID_LINE
            );
            TNodeNT* pnodeTarget = static_cast<TNodeNT*>(pnodeToFind);

            return pnodeTarget->c4SerialNum();
        }

        tCIDLib::TCard4 c4TerminalCount() const
        {
            TMtxLocker lockThis(this->pmtxLock());
            return m_c4TCount;
        }

        TNodeNT* pnodeCreateNTPath( const   TString&    strScopePath
                                    , const TString&    strDescription)
        {
            // Validate the passed path
            TBasicTreeHelpers::CheckPath(strScopePath, CID_FILE, CID_LINE);

            // Looks ok, so lets lock the collection and start working
            TMtxLocker lockThis(this->pmtxLock());

            // Use a string tokenizer to break out the path chunks
            TStringTokenizer stokPath(&strScopePath, kCIDLib::pszTreeSepChar);

            // Start at the root node
            TNodeNT*    pnodeCurParent = m_pnodeRoot;
            TString     strComp;

            //
            //  While we find more parent nodes, and have more tokens, check
            //  that we are on an existing path. Note that we peek here, so
            //  that when we break out at the first on-existing node, we will
            //  not already have gone by it.
            //
            while (pnodeCurParent && stokPath.bPeekNextToken(strComp))
            {
                // Find this under the current node
                TNode* pnodeChild = pnodeCurParent->pnodeFind(strComp, m_bCasePath);

                // If not found, then we need to start creating here so break
                if (!pnodeChild)
                    break;

                // Make sure its a non-terminal
                TBasicTreeHelpers::CheckNodeType
                (
                    pnodeChild, tCIDLib::ETreeNodes::NonTerminal, CID_FILE, CID_LINE
                );

                // Make the current child the new parent
                pnodeCurParent = static_cast<TNodeNT*>(pnodeChild);

                // Ok, eat this token
                stokPath.bEatNextToken();
            }

            //
            //  For any more tokens we have left, we have to create those
            //  components. Note that we can only give a description to the
            //  final one, because we only get a description for that one.
            //  Mostly this API is intended to just create another NT at
            //  the end of an existing path, but we are tolerant here and
            //  will create the ones in between.
            //
            const tCIDLib::TBoolean bSet = stokPath.bMoreTokens();
            while (stokPath.bGetNextToken(strComp))
            {
                pnodeCurParent = pnodeCurParent->pnodeAddNonTerminal
                (
                    strComp
                    , TString::Nul_TString()
                    , m_bCasePath
                    , m_bSorted
                );

                // Bump our non-terminal element count
                m_c4NTCount++;
            }

            // On the last one we created, set the description
            if (bSet)
                pnodeCurParent->strDescription(strDescription);

            // And return the final target node
            return pnodeCurParent;
        }

        TNodeNT* pnodeCreateNTPath(const TCollection<TKeyValuePair>& colPairs)
        {
            // Lock the collection and start working
            TMtxLocker lockThis(this->pmtxLock());

            // Get a cursor for this collection. If empty, then do nothing
            TColCursor<TKeyValuePair>* pcursPairs = colPairs.pcursNew();
            TJanitor<TColCursor<TKeyValuePair> > janCurs(pcursPairs);
            if (!pcursPairs->bReset())
                return nullptr;

            // Start at the root node
            TNodeNT* pnodeCurParent = m_pnodeRoot;
            do
            {
                // Get the current key/value pair
                const TKeyValuePair& kvalCur = pcursPairs->objRCur();

                // Find this under the current node
                TNode* pnodeChild = pnodeCurParent->pnodeFind(kvalCur.strKey(), m_bCasePath);

                // If not found, then we need to start creating here so break
                if (!pnodeChild)
                    break;

                // Make sure its a non-terminal
                TBasicTreeHelpers::CheckNodeType
                (
                    pnodeChild, tCIDLib::ETreeNodes::NonTerminal, CID_FILE, CID_LINE
                );

                // Make current child the new parent
                pnodeCurParent = static_cast<TNodeNT*>(pnodeChild);

            }   while(pnodeCurParent && pcursPairs->bNext());

            //
            //  For any more key/value paris we have left, we have to create
            //  those components.
            //
            if (pcursPairs->bIsValid())
            {
                do
                {
                    const TKeyValuePair& kvalCur = pcursPairs->objRCur();
                    pnodeCurParent = pnodeCurParent->pnodeAddNonTerminal
                    (
                        kvalCur.strKey()
                        , kvalCur.strValue()
                        , m_bCasePath
                        , m_bSorted
                    );

                    // Bump our non-terminal element count
                    m_c4NTCount++;

                }   while (pcursPairs->bNext());
            }

            // Return the final target node
            return pnodeCurParent;
        }

        tCIDLib::ETreeNodes eTypeAt(const TString& strPath) const
        {
            // Validate the path
            TBasicTreeHelpers::CheckPath(strPath, CID_FILE, CID_LINE);

            // Looks ok, so lock the collection
            TMtxLocker lockThis(this->pmtxLock());
            tCIDLib::TCard4 c4Dummy;
            return pnodeFindNode(strPath, c4Dummy, kCIDLib::True)->eType();
        }

        tCIDLib::TVoid FormatTree(TTextOutStream& strmTarget)
        {
            TMtxLocker lockThis(this->pmtxLock());

            // Just call the private recursive helper
            FormatLevel(strmTarget, m_pnodeRoot, 0);

            // And now make sure its flushed
            strmTarget.Flush();
        }

        TElem&
        objAddTerminal( const   TString&    strPath
                        , const TString&    strToAdd
                        , const TElem&      objToAdd
                        , const TString&    strDescription = TString::Nul_TString())
        {
            // Validate the passed strings
            TBasicTreeHelpers::CheckPathAndName(strPath, strToAdd, CID_FILE, CID_LINE);

            // Looks ok, so lets lock and try the add
            TMtxLocker lockThis(this->pmtxLock());

            // Find the node that we are to add under and check the type
            tCIDLib::TCard4 c4Dummy;
            TNode* pnodeToFind = pnodeFindNode(strPath, c4Dummy, kCIDLib::True);
            TBasicTreeHelpers::CheckNodeType
            (
                pnodeToFind, tCIDLib::ETreeNodes::NonTerminal, CID_FILE, CID_LINE
            );
            TNodeNT* pnodeTarget = static_cast<TNodeNT*>(pnodeToFind);

            // Bump our terminal element count
            m_c4TCount++;

            // And now add it to the target node
            return pnodeTarget->objAddTerminal
            (
                objToAdd, strToAdd, strDescription, m_bCasePath, m_bSorted
            );
        }

        TElem&
        objAddTerminal(         TNCCursor&  cursAt
                        , const TString&    strToAdd
                        , const TElem&      objToAdd
                        , const TString&    strDescription = TString::Nul_TString())
        {
            // Validate the name
            TBasicTreeHelpers::CheckName(strToAdd, CID_FILE, CID_LINE);

            // Looks ok, so lets lock the collection and try to add
            TMtxLocker lockThis(this->pmtxLock());

            // Find the node that we are to add under and check the type
            TNode* pnodeAt = cursAt.pnodeCur();
            TBasicTreeHelpers::CheckNodeType
            (
                pnodeAt, tCIDLib::ETreeNodes::NonTerminal, CID_FILE, CID_LINE
            );
            TNodeNT* pnodeTarget = static_cast<TNodeNT*>(pnodeAt);

            // Bump our terminal element count
            m_c4TCount++;

            // And now add it to the target node
            return pnodeTarget->objAddTerminal
            (
                objToAdd, strToAdd, strDescription, m_bCasePath, m_bSorted
            );
        }

        TElem& objAt(const TString& strPath)
        {
            // Validate the path
            TBasicTreeHelpers::CheckPath(strPath, CID_FILE, CID_LINE);

            // Looks ok, so lock the collection
            TMtxLocker lockThis(this->pmtxLock());

            tCIDLib::TCard4 c4Dummy;
            TNode* pnodeAt = pnodeFindNode(strPath, c4Dummy, kCIDLib::True);
            return static_cast<TNode*>(pnodeAt)->objData();
        }

        const TElem& objAt(const TString& strPath) const
        {
            // Validate the path
            TBasicTreeHelpers::CheckPath(strPath, CID_FILE, CID_LINE);

            // Looks ok, so lock the collection
            TMtxLocker lockThis(this->pmtxLock());

            tCIDLib::TCard4 c4Dummy;
            const TNode* pnodeAt = pnodeFindNode(strPath, c4Dummy, kCIDLib::True);
            return static_cast<const TNode*>(pnodeAt)->objData();
        }

        const TElem& objAt( const   TString&    strPath
                            ,       TString&    strNameToFill
                            ,       TString&    strDescToFill)
        {
            // Looks ok, so lock the collection
            TMtxLocker lockThis(this->pmtxLock());

            tCIDLib::TCard4 c4Dummy;
            TNode* pnodeToFind = pnodeFindNode(strPath, c4Dummy, kCIDLib::True);

            // Has to be a terminal in this case
            TBasicTreeHelpers::CheckNodeType
            (
                pnodeToFind, tCIDLib::ETreeNodes::Terminal, CID_FILE, CID_LINE
            );

            // Give back the name/descr info
            strNameToFill = pnodeToFind->strName();
            strDescToFill = pnodeToFind->strDescription();

            // And the data
            return static_cast<const TNodeT*>(pnodeToFind)->objData();
        }

        TElem* pobjAt(const TString& strPath)
        {
            // Validate the path
            TBasicTreeHelpers::CheckPath(strPath, CID_FILE, CID_LINE);

            // Looks ok, so lock the collection
            TMtxLocker lockThis(this->pmtxLock());

            tCIDLib::TCard4 c4Dummy;
            TNode* pnodeAt = pnodeFindNode(strPath, c4Dummy, kCIDLib::False);
            if (!pnodeAt)
                return nullptr;

            return &(static_cast<TNode*>(pnodeAt)->objData());
        }

        const TElem* pobjAt(const TString& strPath) const
        {
            // Validate the path
            TBasicTreeHelpers::CheckPath(strPath, CID_FILE, CID_LINE);

            // Looks ok, so lock the collection
            TMtxLocker lockThis(this->pmtxLock());

            tCIDLib::TCard4 c4Dummy;
            const TNode* pnodeAt = pnodeFindNode(strPath, c4Dummy, kCIDLib::False);
            if (!pnodeAt)
                return nullptr;

            return &(static_cast<const TNode*>(pnodeAt)->objData());
        }

        TNode* pnodeAt(const TString& strPath)
        {
            // Validate the path
            TBasicTreeHelpers::CheckPath(strPath, CID_FILE, CID_LINE);

            // Looks ok, so lock the collection
            TMtxLocker lockThis(this->pmtxLock());

            tCIDLib::TCard4 c4Dummy;
            return pnodeFindNode(strPath, c4Dummy, kCIDLib::False);
        }

        const TNode* pnodeAt(const TString& strPath) const
        {
            // Validate the path
            TBasicTreeHelpers::CheckPath(strPath, CID_FILE, CID_LINE);

            // Looks ok, so lock the collection
            TMtxLocker lockThis(this->pmtxLock());

            tCIDLib::TCard4 c4Dummy;
            return pnodeFindNode(strPath, c4Dummy, kCIDLib::False);
        }

        tCIDLib::TVoid QueryNameAndDesc(const   TString&    strPath
                                        ,       TString&    strNameToFill
                                        ,       TString&    strDescToFill)
        {
            // Validate the path
            TBasicTreeHelpers::CheckPath(strPath, CID_FILE, CID_LINE);

            // Looks ok, so lock the collection
            TMtxLocker lockThis(this->pmtxLock());

            tCIDLib::TCard4 c4Dummy;
            TNode* pnodeToFind = pnodeFindNode(strPath, c4Dummy, kCIDLib::True);
            strNameToFill = pnodeToFind->strName();
            strDescToFill = pnodeToFind->strDescription();
        }

        TNodeNT*
        pnodeAddNonTerminal(const   TString& strPath
                            , const TString& strToAdd
                            , const TString& strDescription = TString::Nul_TString())
        {
            // Validate the passed strings
            TBasicTreeHelpers::CheckPathAndName(strPath, strToAdd, CID_FILE, CID_LINE);

            // Looks ok, so lets lock and try the add
            TMtxLocker lockThis(this->pmtxLock());

            // Find the node that we are to add under
            tCIDLib::TCard4 c4Dummy;
            TNode* pnodeToFind = pnodeFindNode(strPath, c4Dummy, kCIDLib::True);

            // It must be a non-terminal
            TBasicTreeHelpers::CheckNodeType
            (
                pnodeToFind, tCIDLib::ETreeNodes::NonTerminal, CID_FILE, CID_LINE
            );
            TNodeNT* pnodeTarget = static_cast<TNodeNT*>(pnodeToFind);

            // Bump our non-terminal element count
            m_c4NTCount++;

            // And now add it to the target node
            return pnodeTarget->pnodeAddNonTerminal
            (
                strToAdd, strDescription, m_bCasePath, m_bSorted
            );
        }

        TNodeNT*
        pnodeAddNonTerminal(        TNCCursor&  cursAt
                            , const TString&    strToAdd
                            , const TString&    strDescription = TString::Nul_TString())
        {
            // Validate the name
            TBasicTreeHelpers::CheckName(strToAdd, CID_FILE, CID_LINE);

            // Looks ok, so lets lock the collection and try to add
            TMtxLocker lockThis(this->pmtxLock());

            // Find the node that we are to add under and check the type
            TNode* pnodeAt = cursAt.pnodeCur();
            TBasicTreeHelpers::CheckNodeType
            (
                pnodeAt, tCIDLib::ETreeNodes::NonTerminal, CID_FILE, CID_LINE
            );
            TNodeNT* pnodeTarget = static_cast<TNodeNT*>(pnodeAt);

            // Bump our terminal element count
            m_c4NTCount++;

            // And now add it to the target node
            return pnodeTarget->pnodeAddNonTerminal
            (
                strToAdd, strDescription, m_bCasePath, m_bSorted
            );
        }


        TNodeNT* pnodeRoot()
        {
            // Looks ok, so lock the collection
            TMtxLocker lockThis(this->pmtxLock());
            return m_pnodeRoot;
        }

        const TNodeNT* pnodeRoot() const
        {
            // Looks ok, so lock the collection
            TMtxLocker lockThis(this->pmtxLock());
            return m_pnodeRoot;
        }

        tCIDLib::TVoid
        RefreshTerminal(const   TString&    strPath
                        , const TElem&      objToCopy
                        , const TString&    strDescription = TString::Nul_TString())
        {
            // Looks ok, so lock the collection
            TMtxLocker lockThis(this->pmtxLock());

            tCIDLib::TCard4 c4Dummy;
            TNode* pnodeToFind = pnodeFindNode(strPath, c4Dummy, kCIDLib::True);
            TBasicTreeHelpers::CheckNodeType
            (
                pnodeToFind, tCIDLib::ETreeNodes::Terminal, CID_FILE, CID_LINE
            );
            TNodeT* pnodeTarget = static_cast<TNodeT*>(pnodeToFind);

            // Update the value, and the description if its not null
            pnodeTarget->objData(objToCopy);
            if (!TString::bIsNullObject(strDescription))
                pnodeTarget->strDescription(strDescription);
        }

        tCIDLib::TVoid RemoveNode(const TString& strToRemove)
        {
            TMtxLocker lockThis(this->pmtxLock());

            // Find the node indicated
            tCIDLib::TCard4 c4Dummy;
            TNode* pnodeTarget = pnodeFindNode(strToRemove, c4Dummy, kCIDLib::True);

            //
            //  And call the private method that removes nodes. Indicate that
            //  we want to remove the node itself, not just flush its contents.
            //
            RemoveChild(pnodeTarget, kCIDLib::True);
        }

        const TString& strDescriptionAt(const TString& strPath) const
        {
            // Validate the path
            TBasicTreeHelpers::CheckPath(strPath, CID_FILE, CID_LINE);

            // Looks ok, so lock the collection
            TMtxLocker lockThis(this->pmtxLock());
            tCIDLib::TCard4 c4Dummy;
            return pnodeFindNode(strPath, c4Dummy, kCIDLib::True)->strDescription();
        }

        const TString& strNameAt(const TString& strPath)
        {
            // Validate the path
            TBasicTreeHelpers::CheckPath(strPath, CID_FILE, CID_LINE);

            // Looks ok, so lock the collection
            TMtxLocker lockThis(this->pmtxLock());
            tCIDLib::TCard4 c4Dummy;
            return pnodeFindNode(strPath, c4Dummy, kCIDLib::True)->strName();
        }

        tCIDLib::TVoid SetDescription(  const   TString&    strPath
                                        , const TString&    strDescription)
        {
            // Looks ok, so lock the collection
            TMtxLocker lockThis(this->pmtxLock());

            tCIDLib::TCard4 c4Dummy;
            TNode* pnodeToFind = pnodeFindNode(strPath, c4Dummy, kCIDLib::True);
            pnodeToFind->strDescription(strDescription);
        }


    protected :
        // -------------------------------------------------------------------
        //  Declare our friends
        // -------------------------------------------------------------------
        friend class TConstCursor<TElem>;
        friend class TNonConstCursor<TElem>;
        friend class TConstScopeCursor<TElem>;
        friend class TNonConstScopeCursor<TElem>;


    private :
        // -------------------------------------------------------------------
        //  Private, non-virtual methods
        // -------------------------------------------------------------------
        tCIDLib::TVoid
        RemoveChild(        TNode* const        pnodeToRemove
                    , const tCIDLib::TBoolean   bDelParent)
        {
            // If its null or the magic root node, then its illegal
            if (!pnodeToRemove || (pnodeToRemove == m_pnodeRoot))
                TBasicTreeHelpers::BadNode(CID_FILE, CID_LINE);

            //
            //  Before we do this, find out how many terminal nodes exist
            //  under this node. We need to subtract this from our count.
            //
            tCIDLib::TCard4 c4RemovedT = 0;
            tCIDLib::TCard4 c4RemovedNT = 0;
            pnodeToRemove->ContainedNodes(c4RemovedT, c4RemovedNT);

            //
            //  Get the parent node of the current node, and ask it to flush
            //  this node.
            //
            if (bDelParent)
            {
                //
                //  If we are deleting the node itself, and its a non-terminal,
                //  then add one more for it.
                //
                if (pnodeToRemove->eType() == tCIDLib::ETreeNodes::NonTerminal)
                    c4RemovedNT++;

                pnodeToRemove->pnodeParent()->RemoveChild(pnodeToRemove);
            }
             else
            {
                // It must be a non-terminal then
                TBasicTreeHelpers::CheckNodeType
                (
                    pnodeToRemove, tCIDLib::ETreeNodes::NonTerminal, CID_FILE, CID_LINE
                );
                static_cast<TNodeNT*>(pnodeToRemove)->RemoveAll();
            }

            // Now sub the removed counts from the total counts
            m_c4TCount  -= c4RemovedT;
            m_c4NTCount -= c4RemovedNT;

            // Bump serial number to invalidate cursors
            this->c4IncSerialNum();
        }

        tCIDLib::TVoid FormatLevel(         TTextOutStream&     strmTarget
                                    , const TNodeNT* const      pnodeCur
                                    , const tCIDLib::TCard4     c4Level)
        {
            // First space us over
            strmTarget << TTextOutStream::Spaces(c4Level * 4);

            // Now output our tag
            strmTarget << L"<" << pnodeCur->strName() << L">\n";

            // Now output the child nodes, recursing where needed
            TNode* pnodeChild = pnodeCur->pnodeFirstChild();
            while (pnodeChild)
            {
                if (pnodeChild->eType() == tCIDLib::ETreeNodes::NonTerminal)
                {
                    FormatLevel
                    (
                        strmTarget, static_cast<const TNodeNT*>(pnodeChild), c4Level + 1
                    );
                }
                 else
                {
                    // Output our tag for this terminal, after spacing over
                    strmTarget  << TTextOutStream::Spaces((c4Level + 1) * 4)
                                << L"<" << pnodeChild->strName() << L"/>\n";

                }
                pnodeChild = pnodeChild->pnodeNext();
            }

            // And output the closing tag
            strmTarget  << TTextOutStream::Spaces(c4Level * 4)
                        << L"</" << pnodeCur->strName() << L">\n";
        }

        TNode* pnodeFindNext(TNode* const       pnodeStart
                            , tCIDLib::TCard4&  c4Depth) const
        {
            //
            //  If the current node is a non-terminal, then the first thing
            //  we do is iterate down into its children. So, if it has any
            //  children, its first child becomes the next node.
            //
            TNodeNT* pnodeCurParent;
            if (pnodeStart->eType() == tCIDLib::ETreeNodes::NonTerminal)
            {
                pnodeCurParent = static_cast<TNodeNT*>(pnodeStart);
                if (pnodeCurParent->pnodeFirstChild())
                {
                    c4Depth++;
                    return pnodeCurParent->pnodeFirstChild();
                }
                // No children, we move on to look for siblings
            }

            // If this node has a next sibling, then that's our guy
            if (pnodeStart->pnodeNext())
                return pnodeStart->pnodeNext();

            //
            //  Not either of the easy ones, so we have to move up a level,
            //  if we aren't already at the top. This might collapse all the
            //  way back to the root, no matter how deep we are now.
            //
            //  Because we do pre-order, any parent we go up to has already
            //  been handled, so we are only interested in moving forward
            //  through its siblings.
            //
            pnodeCurParent = pnodeStart->pnodeParent();
            TNode* pnodeCur = nullptr;
            tCIDLib::TBoolean bDone = kCIDLib::False;
            while (!bDone)
            {
                // The current parent becomes the current node
                pnodeCur = pnodeCurParent;

                // And we move up to the parent's parent as the current parent
                pnodeCurParent = pnodeCurParent->pnodeParent();

                //
                //  If there is no parent, then we were on the root, so
                //  we are done and have no more nodes to interate.
                //
                if (!pnodeCurParent)
                {
                    pnodeCur = nullptr;
                    break;
                }

                // Bump down the passed depth. Sanity check it first
                if (!c4Depth)
                    TBasicTreeHelpers::DepthUnderflow(CID_FILE, CID_LINE);
                c4Depth--;

                // See if the current node has a next sibling
                if (pnodeCur->pnodeNext())
                {
                    pnodeCur = pnodeCur->pnodeNext();
                    break;
                }
            }
            return pnodeCur;
        }

        TNode*
        pnodeFindNode(  const   TString&            strToFind
                        ,       tCIDLib::TCard4&    c4Depth
                        , const tCIDLib::TBoolean   bThrowIfNotFound = kCIDLib::False) const
        {
            // Validate the path
            TBasicTreeHelpers::CheckPath(strToFind, CID_FILE, CID_LINE);

            // Initialize the depth return to zero. This represents the root
            c4Depth = 0;

            // Optimize for root
            if (strToFind == L"/")
                return m_pnodeRoot;

            // If its empty, then we know we won't find it
            if (!m_c4TCount && !m_c4NTCount)
            {
                if (bThrowIfNotFound)
                    TBasicTreeHelpers::NamedNodeNotFound(CID_FILE, CID_LINE, strToFind);
                return 0;
            }

            //
            //  We just search the tree, finding each component of the passed
            //  path at each level.
            //
            TString strSepChars(kCIDLib::pszTreeSepChar);
            TStringTokenizer stokName(&strToFind, strSepChars);

            TNodeNT*    pnodeCurParent = m_pnodeRoot;
            TNode*      pnodeTmp = nullptr;
            TString     strCur;
            while (stokName.bGetNextToken(strCur))
            {
                //
                //  If it's empty, that's bad unless it's because of a final
                //  trailing separator.
                //
                if (strCur.bIsEmpty())
                {
                    if (!stokName.bMoreTokens())
                        break;
                    TBasicTreeHelpers::BadPath(CID_FILE, CID_LINE);
                }

                //
                //  Find this child node under the current parent. If not
                //  found, then we are done.
                //
                pnodeTmp = pnodeCurParent->pnodeFind(strCur, m_bCasePath);
                if (!pnodeTmp)
                {
                    if (bThrowIfNotFound)
                        TBasicTreeHelpers::NamedNodeNotFound(CID_FILE, CID_LINE, strToFind);
                    return nullptr;
                }

                // If its a terminal node, we must be at the end
                if (pnodeTmp->eType() == tCIDLib::ETreeNodes::Terminal)
                {
                    if (stokName.bMoreTokens())
                        TBasicTreeHelpers::MustBeNonTerminal(CID_FILE, CID_LINE, strToFind);
                }
                 else
                {
                    pnodeCurParent = static_cast<TNodeNT*>(pnodeTmp);

                    // Increment the depth that we've searched
                    c4Depth++;
                }
            }
            return pnodeTmp;
        }

        tCIDLib::TVoid
        ReplicateNodes( const   TNodeNT* const  pnodeSrcParent
                        ,       TNodeNT* const  pnodeTargetParent)
        {
            //
            //  Go through the children of the source parent node and replicate
            //  each one. If its a non-terminal node, then recurse as we see
            //  them.
            //
            const TNode* pnodeSrc = pnodeSrcParent->pnodeFirstChild();
            while (pnodeSrc)
            {
                if (pnodeSrc->eType() == tCIDLib::ETreeNodes::Terminal)
                {
                    const TNodeT* pnodeNewSrc
                        = static_cast<const TNodeT*>(pnodeSrc);

                    // Add a new non-terminal, with the same data and name
                    if (pnodeNewSrc->bHasDescription())
                    {
                        pnodeTargetParent->objAddTerminal
                        (
                            pnodeNewSrc->objData()
                            , pnodeNewSrc->strName()
                            , pnodeNewSrc->strDescription()
                            , m_bCasePath
                            , m_bSorted
                        );
                    }
                     else
                    {
                        pnodeTargetParent->objAddTerminal
                        (
                            pnodeNewSrc->objData()
                            , pnodeNewSrc->strName()
                            , TString::Nul_TString()
                            , m_bCasePath
                            , m_bSorted
                        );
                    }
                }
                 else
                {
                    //
                    //  Add a new non-terminal with the same name as the
                    //  source, and then recurse on it.
                    //
                    TNodeNT* pnodeNewNT;
                    if (pnodeSrc->bHasDescription())
                    {
                        pnodeNewNT = pnodeTargetParent->pnodeAddNonTerminal
                        (
                            pnodeSrc->strName()
                            , pnodeSrc->strDescription()
                            , m_bCasePath
                            , m_bSorted
                        );
                    }
                     else
                    {
                        pnodeNewNT = pnodeTargetParent->pnodeAddNonTerminal
                        (
                            pnodeSrc->strName()
                            , TString::Nul_TString()
                            , m_bCasePath
                            , m_bSorted
                        );
                    }
                    ReplicateNodes
                    (
                        static_cast<const TNodeNT*>(pnodeSrc)
                        , pnodeNewNT
                    );
                }

                // And move forward at this level
                pnodeSrc = pnodeSrc->pnodeNext();
            }
        }


        // -------------------------------------------------------------------
        //  Private data members
        //
        //  m_bCasePath
        //      Controls whether paths are treated as case sensitive when
        //      using them to look up nodes. Defaults to true.
        //
        //  m_bSorted
        //      Controls whether nodes are stored sorted. Defaults to true
        //      unless forced off.
        //
        //  m_c4NTCount
        //  m_c4TCount
        //      These are the counts of terminal and non-terminal nodes we
        //      have. The number of nodes we report via the generic element
        //      count API we inherit from TCollection is the sum of these.
        //      But via our interface, we provide access to both values since
        //      some programs care about the difference.
        //
        //  m_pnodeRoot
        //      The root node. This is a magic node, with the name set to
        //      "Root", that is added upon construction. All child nodes are
        //      added under this one.
        // -------------------------------------------------------------------
        tCIDLib::TBoolean   m_bCasePath;
        tCIDLib::TBoolean   m_bSorted;
        tCIDLib::TCard4     m_c4NTCount;
        tCIDLib::TCard4     m_c4TCount;
        TNodeNT*            m_pnodeRoot;


        // -------------------------------------------------------------------
        //  Magic Macros
        // -------------------------------------------------------------------
        DefPolyDup(TMyType)
        TemplateRTTIDefs(TMyType,TCollection<TElem>)
};


#pragma CIDLIB_POPPACK


