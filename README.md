# libSQLiteDatabaseHelper

Welcome to the official repository of the "libSQLiteDatabaseHelper" project.
Here you will find the source code, documentation, and examples for the project.

This library was originally only to be used in one of my other (non-public)
projects, but then I changed my mind, and decided I wanted to share it with the
public.

## Compiling (Linux and macOS)
**Note**: If on macOS, please make sure you have the [Xcode Command Line Tools](https://developer.apple.com/library/ios/technotes/tn2339/_index.html)
installed.

Before you can compile anything, you need to make sure that you have a copy of
the library's source-tree.

Using the power of Git, obtaining a copy of the source-tree is easy. If you
don't already know how to do this, perhaps you should read
[this](https://help.github.com/articles/fetching-a-remote/).

Once you have a copy of the source-tree, all you need to do is edit 2 macros
found within the Makefile, to specify where you want the library's files to be
copied to once compilation has finished.

The macros that you need to modify, are called "`COPY_LIBRARY_ARCHIVES_TO`"
and "`COPY_LIBRARY_HEADERS_TO`".

Once you've done that, just run `make`. Everything should compile. Once
everything finishes compiling, the library files will be copied to the
directories that you specified.

If you encounter any problems during compilation, please [open a new issue](https://github.com/Gigabyte-Giant/SQLiteDatabaseHelper/issues/new).