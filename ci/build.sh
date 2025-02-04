#! /bin/sh
#
# Generic build (driven by environment variables)
#

# Sanity check
test -n "$BUILDDIR" || { echo "! \$BUILDDIR not set" ; exit 1 ; }
mkdir -p "$BUILDDIR"
test -f "$SRCDIR/CMakeLists.txt" || { echo "! Missing $SRCDIR/CMakeLists.txt" ; exit 1 ; }

BUILD_MESSAGE="No commit info"
test -n "$GIT_HASH" && BUILD_MESSAGE=$( git log -1 --abbrev-commit --pretty=oneline --no-decorate "$GIT_HASH" )

echo "::" ; echo ":: $BUILD_MESSAGE" ; echo "::"

cmake -S "$SRCDIR" -B "$BUILDDIR" $CMAKE_ARGS || exit 1
make -C "$BUILDDIR" -j2 VERBOSE=1 || exit 1
make -C "$BUILDDIR" install VERBOSE=1 || exit 1

echo "::" ; echo ":: $BUILD_MESSAGE" ; echo "::"
