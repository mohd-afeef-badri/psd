AC_INIT([PSD], [2.0], [mohd-afeef.badri@cea.fr])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

AC_CONFIG_HEADERS([config.h])
AC_PREFIX_PROGRAM (program)


dnl Small macro to print out a nice, pretty section title.
define(SECTION_TITLE,
[
	echo >& AS_MESSAGE_FD
	echo '   $1   ' | sed -e's/./-/g' >&AS_MESSAGE_FD
	echo '   $1' >& AS_MESSAGE_FD
	echo '   $1   ' | sed -e's/./-/g' >&AS_MESSAGE_FD
])

AU_ALIAS([ACX_GMSH], [AX_GMSH])
AC_DEFUN([AX_GMSH], [
AC_PREREQ(2.50)
AC_REQUIRE([AC_PROG_CXX])
AC_ARG_VAR(GMSH,[Gmsh mesher])
AC_CHECK_PROGS(GMSH, gmsh, $GMSH)
AC_SUBST(GMSH)
])dnl ACX_GMSH

AU_ALIAS([ACX_FF], [AX_FF])
AC_DEFUN([AX_FF], [
AC_PREREQ(2.50)
AC_REQUIRE([AC_PROG_CXX])
AC_ARG_VAR(FF,[FreeFEM compiler command])
AC_CHECK_PROGS(FF, FreeFem++, $FF)
AC_SUBST(FF)
])dnl ACX_FF

AU_ALIAS([ACX_FFCXX], [AX_FFCXX])
AC_DEFUN([AX_FFCXX], [
AC_PREREQ(2.50)
AC_REQUIRE([AC_PROG_CXX])
AC_ARG_VAR(FFCXX,[FreeFEM compiler command])
AC_CHECK_PROGS(FFCXX, ff-c++, $FFCXX)
AC_SUBST(FFCXX)
])dnl ACX_FFCXX

AU_ALIAS([ACX_FFMPI], [AX_FFMPI])
AC_DEFUN([AX_FFMPI], [
AC_PREREQ(2.50)
AC_REQUIRE([AC_PROG_CXX])
AC_ARG_VAR(FFMPI,[FreeFEM compiler command])
AC_CHECK_PROGS(FFMPI, ff-mpirun, $FFMPI)
AC_SUBST(FFMPI)
])dnl ACX_FFMPI

AC_ARG_WITH(FreeFEM,
	[  --with-FreeFEM=         FreeFEM installation path : (e.g. --with-FreeFEM=/opt/FreeFem/bin)],
	   FF="${withval}/FreeFem++"
	   FFCXX="${withval}/ff-c++"
	   FFMPI="${withval}/ff-mpirun")
	   
AC_ARG_WITH(Gmsh,
	[  --with-Gmsh=            Gmsh installation path : (e.g. --with-Gmsh=/opt/Gmsh/bin)],
	   FF="${withval}/Gmsh")	   

SECTION_TITLE([    checking for a C++  compilers       ])
AC_PROG_CXX
AC_LANG(C++)

SECTION_TITLE([      checking for a Gmsh mesher        ])
AX_GMSH


SECTION_TITLE([      checking for a FF++ compilers     ])
AX_FF
AX_FFCXX
AX_FFMPI


SECTION_TITLE([    generating the required makefiles   ])

AC_PREFIX_DEFAULT($HOME)
AC_CONFIG_FILES([
 Makefile
 src/Makefile 
 src/plugins/Makefile
 src/psd-preprocessor/Makefile
 data/Makefile
 data/meshes/2D/Geo-Files/Makefile
 data/meshes/3D/Geo-Files/Makefile 
])
AC_OUTPUT

SECTION_TITLE([                   status               ])

dnl Print results
AC_MSG_RESULT([])
AC_MSG_RESULT([ PSD version $VERSION configured successfully.])
AC_MSG_RESULT([])
AC_MSG_RESULT([ Using '$prefix' for installation.])
AC_MSG_RESULT([ Using '$CXX' for C++ compiler.])
AC_MSG_RESULT([ Building with '$CXXFLAGS' for C++ compiler flags.])
AC_MSG_RESULT([ Building with '$LDFLAGS' for linker flags.])
AC_MSG_RESULT([ Building with '$LIBS' libraries.])
AC_MSG_RESULT([])
