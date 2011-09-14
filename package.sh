#!/bin/sh

BASE="$(dirname $0)"
VERSION="2.0"
WINDOWS=false
case "$(uname)" in
  MINGW*) WINDOWS=true ;;
esac

# Clear and create the dist folder.
if [ -d "$BASE/dist" ] ; then
  rm -rf "$BASE/dist"
fi
mkdir "$BASE/dist"

# Common procedure to stage the source code.
mkdir "$BASE/dist/bday-$VERSION"
cp -r "$BASE/etc" "$BASE/help" "$BASE/images" "$BASE/src" "$BASE/.cproject" "$BASE/.project" "$BASE/BUILD" "$BASE/COPYING" "$BASE/README" "$BASE/LICENSE" "$BASE/package.sh" "$BASE/dist/bday-$VERSION"

mkdir "$BASE/dist/bday-$VERSION/linux"
cp "$BASE/linux/Makefile" "$BASE/dist/bday-$VERSION/linux"

mkdir "$BASE/dist/bday-$VERSION/msys"
cp "$BASE/msys/Makefile" "$BASE/msys/bday.rc" "$BASE/msys/setup.nsi" "$BASE/dist/bday-$VERSION/msys"

find "$BASE/dist/bday-$VERSION" -iname .svn | sed -e 's/^/"/' -e 's/$/"/' | xargs rm -rf

# Operating system specific stuff here.
if $WINDOWS ; then
  # Figure out if we have a zip program
  ZIP="$(which zip)"
  if [ "a$ZIP" = "a" ] ; then
    if [ -x /cygdrive/c/cygwin/bin/zip ] ; then
      ZIP=/cygdrive/c/cygwin/bin/zip
    elif [ -x /c/cygwin/bin/zip ] ; then
      ZIP=/c/cygwin/bin/zip
    fi
  fi

  # Create src zip
  if [ "a$ZIP" != "a" ] ; then
    echo "Building bday-src-$VERSION.zip"
    cd "$BASE/dist"
    $ZIP -r -m -q "bday-src-$VERSION.zip" bday-$VERSION
    cd -
  else
    echo
    echo "NOTICE: No zip program available.  Make a zip of the $BASE/dist/bday-$VERSION folder to package the source code."
    echo
  fi

  # Copy installer to dist folder.
  if [ -f "$BASE/msys/bday-win32-$VERSION.exe" ] ; then
    cp "$BASE/msys/bday-win32-$VERSION.exe" "$BASE/dist"
  else
    echo "NOTE: You can build the self-install package by running NSIS on $BASE/msys/setup.nsi"
  fi

  # Create bin zip
  if [ ! -f "$BASE/msys/bday.exe" ] ; then
    echo
    echo 'ERROR: Need to do "cd msys; make" first to create the binary.' 1>&2
    echo 'See BUILD for more information.' 1>&2
    exit 1
  fi

  mkdir "$BASE/dist/bday"
  cp -r "$BASE/msys/bday.exe" "$BASE/help" "$BASE/etc/win32/COPYING.txt" "$BASE/etc/win32/LICENSE.txt" "$BASE/etc/win32/README.txt" "$BASE/etc/win32/INSTALL.txt" "$BASE/dist/bday"

  find "$BASE/dist/bday" -iname .svn | sed -e 's/^/"/' -e 's/$/"/' | xargs rm -rf 2> /dev/null

  if [ "a$ZIP" != "a" ] ; then
    echo "Building bday-win32-$VERSION.tar.gz"
    cd "$BASE/dist"
    $ZIP -r -m -q "bday-win32-$VERSION.zip" bday
    cd -
  else
    echo
    echo "NOTICE: No zip program available.  Make a zip of the $BASE/dist/bday folder to package the distributable executable."
    echo
  fi
else
  # Create src tar.gz/bz2
  echo "Building bday-src-$VERSION.tar.gz"
  tar -cf - -C "$BASE/dist" bday-$VERSION | gzip -9 > "$BASE/dist/bday-src-$VERSION.tar.gz"

  echo "Building bday-src-$VERSION.tar.bz2"
  tar -cf - -C "$BASE/dist" bday-$VERSION | bzip2 > "$BASE/dist/bday-src-$VERSION.tar.bz2"

  rm -r "$BASE/dist/bday-$VERSION"

  # Create bin tar.gz/bz2
  if [ ! -f "$BASE/linux/bday" ] ; then
    echo 'ERROR Need to do "cd linux; make" first to create the binary.' 1>&2
    echo 'See BUILD for more information.' 1>&2
    exit 1
  fi

  mkdir "$BASE/dist/bday"
  cp -r "$BASE/linux/bday" "$BASE/help" "$BASE/COPYING" "$BASE/README" "$BASE/LICENSE" "$BASE/etc/linux/INSTALL" "$BASE/etc/linux/bday.desktop" "$BASE/etc/linux/bday.png" "$BASE/dist/bday"

  find "$BASE/dist/bday" -iname .svn | sed -e 's/^/"/' -e 's/$/"/' | xargs rm -rf 2> /dev/null

  echo "Building bday-linux-$(uname -i)-$VERSION.tar.gz"
  tar -cf - -C "$BASE/dist" bday | gzip -9 > "$BASE/dist/bday-linux-$(uname -i)-$VERSION.tar.gz"

  echo "Building bday-linux-$(uname -i)-$VERSION.tar.bz2"
  tar -cf - -C "$BASE/dist" bday | bzip2 > "$BASE/dist/bday-linux-$(uname -i)-$VERSION.tar.bz2"

  rm -r "$BASE/dist/bday"
fi
