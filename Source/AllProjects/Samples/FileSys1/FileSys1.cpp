//
// FILE NAME: FileSys1.cpp
//
// AUTHOR: Dean Roddey
//
// CREATED: 05/24/1997
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
//  This is the main module for the first of the file system oriented demo
//  programs. This one just provides a very simple directory listing program.
//  This demonstrates directory iteration, recursive directory searching,
//  and some formatting of objects and text stream stuff.
//
//  It outputs pretty much the same as the built in NT "DIR" command.
//
// CAVEATS/GOTCHAS:
//
//  1)  This program is so simple that it does not create a facility object
//      for itself, or have a main facility header.
//
//  2)  We create a TFindBuf object on each level of the recursive search.
//      In a 'real' program we'd probably be a little more paranoid about
//      stack overflow and just allocate one on each level, using a janitor
//      object to clean it up.
//
//  3)  This program does not attempt to be language independent.
//
// LOG:
//
//  $_CIDLib_Log_$
//


// ---------------------------------------------------------------------------
//  Includes. This program is so simple that we don't even have a header of
//  our own. So just include CIDLib, which is all we need.
// ---------------------------------------------------------------------------
#include    "CIDLib.hpp"


// ---------------------------------------------------------------------------
//  Forward references
// ---------------------------------------------------------------------------
tCIDLib::EExitCodes eMainThreadFunc
(
        TThread&            thrThis
        , tCIDLib::TVoid*   pData
);


// ---------------------------------------------------------------------------
//  Do the magic main module code
// ---------------------------------------------------------------------------
CIDLib_MainModule(TThread(L"FileSys1MainThread", eMainThreadFunc))



// ---------------------------------------------------------------------------
//  Local functions
// ---------------------------------------------------------------------------

//
//  This method is called if the user wants to do a recursive directory
//  operation. We just recurse our way down the chain.
//
static tCIDLib::TVoid
RecursiveSearch(const   TPathStr&           pathFullPath
                , const TPathStr&           pathWildCard
                ,       tCIDLib::TCard8&    c8TotalBytes
                ,       tCIDLib::TCard4&    c4TotalFiles)
{
    //
    //  First we want to iterate this whole directory and display anything
    //  that matches the wildcard.
    //
    tCIDLib::TCard4 c4CurFiles = 0;
    tCIDLib::TCard8 c8CurBytes = 0;
    TDirIter        diterLevel;
    TFindBuf        fndbSearch;

    if (diterLevel.bFindFirst(pathFullPath, pathWildCard, fndbSearch, tCIDLib::EDirSearchFlags::All))
    {
        TSysInfo::strmOut() << kCIDLib::DNewLn
                            << L"  Directory of " << pathFullPath
                            << kCIDLib::NewLn << kCIDLib::EndLn;

        //
        //  Just iterate the rest of files, displaying each one. Keep
        //  up with how many files and how many bytes total.
        //
        do
        {
            //
            //  Just do the default format of a find buffer by just
            //  dumping it to the console.
            //
            TSysInfo::strmOut() << fndbSearch << kCIDLib::NewLn;

            c4TotalFiles++;
            c8TotalBytes += fndbSearch.c8Size();

            c4CurFiles++;
            c8CurBytes += fndbSearch.c8Size();

        }   while (diterLevel.bFindNext(fndbSearch));
    }

    if (c4CurFiles)
    {
        TSysInfo::strmOut() << L"   " << c4CurFiles << L" File(s), "
                            << c8CurBytes << L" bytes" << kCIDLib::EndLn;
    }

    //
    //  Now start a new search, for directories only. For each one, we
    //  want to recurse and handle it the same way. We tell it we only
    //  want to find normal directories.
    //
    //  We pass our own search spec, which won't limit the search in any
    //  way. pszAllFilesSpec is a predefined spec that has this effect, so
    //  its safer to do than something hard coded.
    //
    if (diterLevel.bFindFirst
    (
        pathFullPath
        , kCIDLib::pszAllFilesSpec
        , fndbSearch
        , tCIDLib::EDirSearchFlags::NormalDirs))
    {
        //
        //  Ok, for all of the rest of the finds, we want to recurse upon
        //  ourselves.
        //
        do
        {
            // Now handle this level if its a normal directory
            if (fndbSearch.bIsNormalDir())
            {
                RecursiveSearch
                (
                    fndbSearch.pathFileName()
                    , pathWildCard
                    , c8TotalBytes
                    , c4TotalFiles
                );
            }
            c4TotalFiles++;
        }   while (diterLevel.bFindNext(fndbSearch));
    }
}


//
//  Shows the parameter usage for the program.
//
static tCIDLib::TVoid ShowUsage()
{
    TSysInfo::strmOut()
                << L"Usage: FileSys1 wildcard [/s]" << kCIDLib::DNewLn
                << L"  wildcard  The file search specification, e.g. *.*"
                << kCIDLib::NewLn
                << L"  /s        Indicates a recursive directory search."
                << kCIDLib::NewLn
                << L"              Otherwise just the current directory is listed"
                << kCIDLib::NewLn << kCIDLib::EndLn;
}


//
//  This is the the thread function for the main thread.
//
tCIDLib::EExitCodes eMainThreadFunc(TThread& thrThis, tCIDLib::TVoid*)
{
    // We have to let our calling thread go first
    thrThis.Sync();

    //
    //  Since this is a demo and testing program, we'd like to catch
    //  all exceptions cleanly and report them. So put the whole thing
    //  in a try.
    //
    try
    {
        // Check out the command line parms for valid count
        tCIDLib::TCard4 c4Args = TSysInfo::c4CmdLineParmCount();
        if ((c4Args < 1) || (c4Args > 2))
        {
            ShowUsage();
            return tCIDLib::EExitCodes::BadParameters;
        }

        //
        //  If there is a single user parm and its /?, then show the program
        //  usage and exit. If its not, then it must be the wildcard. If there
        //  is none, then set wildcard to default.
        //
        TPathStr pathSearchSpec;
        if (c4Args == 1)
        {
            pathSearchSpec = TSysInfo::strCmdLineParmAt(0);
            if (pathSearchSpec == L"/?")
            {
                ShowUsage();
                return tCIDLib::EExitCodes::Normal;
            }
        }
         else
        {
            // Set it to the default 'all files' spec
            pathSearchSpec = kCIDLib::pszAllFilesSpec;
        }

        //
        //  If we have another parm, then get it. If it is /s, then set
        //  the bRecursive flag. Else show usage and exit.
        //
        tCIDLib::TBoolean bRecursive = kCIDLib::False;
        if (c4Args == 2)
        {
            if (TSysInfo::strCmdLineParmAt(1) != L"/s")
            {
                ShowUsage();
                return tCIDLib::EExitCodes::BadParameters;
            }
            bRecursive = kCIDLib::True;
        }

        //
        //  Get the fully qualified path to the search spec we got. This
        //  will let us get the volume from it.
        //
        TPathStr pathFullPath;
        TFileSys::QueryFullPath(pathSearchSpec, pathFullPath);

        //
        //  Ask for the volume that contains the path of this file.
        //
        TVolumeInfo voliTarget;
        TPathStr    pathVolume;
        pathFullPath.bQueryVolume(pathVolume);
        try
        {
            voliTarget.SetFromPath(pathVolume);
        }

        catch(TError& errToCatch)
        {
            // If this hasn't been logged already, then log it
            if (!errToCatch.bLogged())
            {
                errToCatch.AddStackLevel(CID_FILE, CID_LINE);
                TModule::LogEventObj(errToCatch);
            }

            TSysInfo::strmOut() << errToCatch.strErrText();
            if (!errToCatch.strAuxText().bIsEmpty())
                TSysInfo::strmOut() << L"\nReason: " << errToCatch.strAuxText();
            TSysInfo::strmOut() << kCIDLib::NewLn << kCIDLib::EndLn;
            return tCIDLib::EExitCodes::ResourceAccess;
        }

        // Now output the preamble stuff
        TSysInfo::strmOut()
                    << L"  Volume in drive " << voliTarget.strVolume()
                    << L" is " << voliTarget.strVolumeLabel() << kCIDLib::NewLn
                    << L"  Volume Serial Number is "
                    << voliTarget.strVolumeSerialNum() << kCIDLib::NewLn << kCIDLib::EndLn;

        //
        //  Now we need to split out the wildcard part of it from the path
        //  part. If there is no wildcard part, i.e. its just something
        //  like C:\Bubba, then we need to turn it into something like
        //  C:\Bubba\*.*. If its something like C:\Bub?a, then they want
        //  to just search in C:\ for things that match Bub?a.
        //
        //  The thing that tells us this is whether the path has any wild
        //  card characters in it.
        //
        TPathStr pathWildCard;
        if (pathSearchSpec.bHasWildCards())
        {
            //
            //  Get the name.ext from the path and that becomes the wild
            //  card part, the rest is the path.
            //
            pathFullPath.bQueryNameExt(pathWildCard);
            pathFullPath.bRemoveNameExt();
        }
         else
        {
            //
            //  The path remains the path and the wild card gets set to the
            //  platform's default 'find all' spec.
            //
            pathWildCard = kCIDLib::pszAllFilesSpec;
        }

        //
        //  Ok, lets do the directory listing. If this is a recursive search
        //  we kick off a local recursive function. If its not, we just do
        //  it right here since its so trivial.
        //
        tCIDLib::TCard8 c8TotalBytes = 0;
        tCIDLib::TCard4 c4TotalFiles = 0;
        try
        {
            if (bRecursive)
            {
                RecursiveSearch
                (
                    pathFullPath
                    , pathWildCard
                    , c8TotalBytes
                    , c4TotalFiles
                );
            }
             else
            {
                TSysInfo::strmOut() << L"  Directory of " << pathFullPath
                                    << kCIDLib::NewLn << kCIDLib::EndLn;

                // Use the default search flags, which is to find everything
                TDirIter diterSearch;
                TFindBuf fndbSearch;
                if (diterSearch.bFindFirst(pathFullPath, pathWildCard, fndbSearch))
                {
                    //
                    //  Just iterate the rest of files, displaying each one. Keep
                    //  up with how many files and how many bytes total.
                    //
                    do
                    {
                        //
                        //  Just do the default format of a find buffer by just
                        //  dumping it to the console.
                        //
                        TSysInfo::strmOut() << fndbSearch << kCIDLib::EndLn;

                        c4TotalFiles++;
                        c8TotalBytes += fndbSearch.c8Size();

                    }   while (diterSearch.bFindNext(fndbSearch));
                }
            }
        }

        catch(TError& errToCatch)
        {
            // If this hasn't been logged already, then log it
            if (!errToCatch.bLogged())
            {
                errToCatch.AddStackLevel(CID_FILE, CID_LINE);
                TModule::LogEventObj(errToCatch);
            }

            TSysInfo::strmOut() << errToCatch.strErrText();
            if (!errToCatch.strAuxText().bIsEmpty())
                TSysInfo::strmOut() << L"\nReason: " << errToCatch.strAuxText();
            TSysInfo::strmOut() << kCIDLib::NewLn << kCIDLib::EndLn;
            return tCIDLib::EExitCodes::RuntimeError;
        }

        if (!c4TotalFiles)
        {
            TSysInfo::strmOut() << L"There were no files found at: "
                                << pathFullPath << kCIDLib::NewLn << kCIDLib::EndLn;
            return tCIDLib::EExitCodes::NotFound;
        }

        // Query the space info
        tCIDLib::TCard8 c8VolFreeBytes;
        tCIDLib::TCard8 c8UserAvailBytes;
        TFileSys::QueryVolumeInfo
        (
            voliTarget.strVolume()
            , c8TotalBytes
            , c8VolFreeBytes
            , c8UserAvailBytes
        );

        // Output the totals
        TSysInfo::strmOut()
                    << kCIDLib::NewLn
                    << L"   Total Files: " << c4TotalFiles << kCIDLib::NewLn
                    << L"   Total Bytes: " << TLocCardinal64(c8TotalBytes) << kCIDLib::NewLn
                    << L"   Avail Bytes: "
                    << TLocCardinal64(c8UserAvailBytes) << kCIDLib::NewLn
                    << L"    Free Bytes: "
                    << TLocCardinal64(c8VolFreeBytes)
                    << kCIDLib::NewLn << kCIDLib::EndLn;
    }


    //
    //  Catch any unhandled CIDLib runtime errors
    //
    catch(TError& errToCatch)
    {
        // If this hasn't been logged already, then log it
        if (!errToCatch.bLogged())
        {
            errToCatch.AddStackLevel(CID_FILE, CID_LINE);
            TModule::LogEventObj(errToCatch);
        }

        TSysInfo::strmOut()
                    <<  L"A CIDLib runtime error occured during processing. "
                    <<  L"\nError: " << errToCatch.strErrText()
                    << kCIDLib::NewLn << kCIDLib::EndLn;
        return tCIDLib::EExitCodes::FatalError;
    }

    //
    //  Kernel errors should never propogate out of CIDLib, but I test
    //  for them in my test programs so I can catch them if they do
    //  and fix them.
    //
    catch(const TKrnlError& kerrToCatch)
    {
        TSysInfo::strmOut()
                    << L"A kernel error occured during processing.\n  Error="
                    << kerrToCatch.errcId() << kCIDLib::NewLn << kCIDLib::EndLn;
        return tCIDLib::EExitCodes::FatalError;
    }

    // Catch a general exception
    catch(...)
    {
        TSysInfo::strmOut()
                    << L"A general exception occured during processing\n"
                    << kCIDLib::EndLn;
        return tCIDLib::EExitCodes::SystemException;
    }

    return tCIDLib::EExitCodes::Normal;
}