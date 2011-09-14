CONTENTS
--------

Building Under the Linux Operating System
Building Under the Windows Operating System
Generating the GUI


BUILDING UNDER THE LINUX OPERATING SYSTEM
-----------------------------------------

You must have a C++ compiler and the wxWidgets libraries and development files
installed before you can compile BDay.  wxWidgets version 2.8.9 or greater
should work fine.

Depending on your Linux distribution, these packages can be installed in
different ways.  If you were using smart for package management, for example,
you could simply type:

	smart install wxWidgets wxWidgets-devel

Unpack the source for BDay into a directory, then change directories to the
"linux" sub-directory.  From there, simply run "make" to compile.

If you want to repackage the sources or executables, you can change directory
to the base directory for the source install and run the package.sh script.

	./package.sh

This will create the directory "dist" with the various distribute packages (not
including the RPMs).

The GUI is written using wxFormBuilder.  See "Generating the GUI" below.


BUILDING UNDER THE WINDOWS OPERATING SYSTEM
-------------------------------------------

MinGW/MSYS Build Environment
----------------------------

BDay is built using MinGW, the Minimalist GNU for Windows C++ compiler, with
the aid of MSYS, the Minimal SYStem which provides a Bourne Shell command line
environment for MingGW.

http://www.mingw.org/

The easiest way to install MinGW is to go to the download page, then download
and run the Automated MinGW Installer.

wxWidgets Library
-----------------

BDay also uses the wxWidgets library to supply the graphical user interface.

http://wxwidgets.org/

BDay currently uses 2.8.9 or higher.  Go to the download page and select the
mxMSW installer for Windows.  Run this and install in the default directory.

Once installed, you need to compile the wxWidgets libraries.

Open an MSYS command line window, and change directory to where wxWidgets was
installed.  Then follow these steps:

  1. Make a sub-directory called "msw".

	mkdir msw

  2. Change directory to msw.

	cd msw

  3. Run configure as shown below:

	../configure --enable-unicode --enable-monolithic --disable-shared --disable-threads --enable-no_exceptions --disable-exceptions --enable-no_rtti --with-msw

  4. Run make

	make

  5. Run make install.

	make install

NSIS (Optional)
---------------

The Nullsoft Scriptable Install System is used to build the self-installing
package for BDay under Windows.

If you want to build this, you can download and install it from
http://nsis.sourceforge.net/

Building BDay
-------------

Once the above prerequisites have been met, building BDay should simply be a
matter of unpacking the sources into a directory, opening an MSYS command line
window, changing directory to the msys directory  and running "make" to
compile.

Within the msys directory there is also a setup.nsi file, which can be compiled
with NSIS to create the self-installing executable.

Finally, if you want to repackage the sources or executables, you can change
directory to the base directory for the source install and run the package.sh
script.

	./package.sh

This will create the directory "dist" with the various distribute packages.


GENERATING THE GUI
------------------

The file src/gui.fpb is an XML file that outlines the windows and dialogues
used by BDay.  The wxFormBuilder tool is used to convert this to C++ code to be
derived and compiled.

wxFormBuilder is available from http://wxformbuilder.org/

I have included the generated files, GeneratedGui.h and GeneratedGui.cpp in the
source repository for convenience (and to save anybody who is just downloading
and compiling the source from needing an extra step) however you should not
modify these generated files.  If you want to modify the GUI base classes, use
wxFormBuilder to do the modifications and generate new C++ code for your
changes.
