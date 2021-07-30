AC_INIT([PSD], [2.2], [mohd-afeef.badri@cea.fr])
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
AC_ARG_VAR(GMSH,[Gmsh mesher])
AC_CHECK_PROG(GMSH,[gmsh],[gmsh],[no])
dnl AC_CHECK_PROGS(GMSH, gmsh, $GMSH)
dnl AC_SUBST(GMSH)
])dnl ACX_GMSH

AU_ALIAS([ACX_FF], [AX_FF])
AC_DEFUN([AX_FF], [
AC_PREREQ(2.50)
AC_ARG_VAR(FF,[FreeFEM compiler command])
AC_CHECK_PROG(FF,[FreeFem++],[FreeFem++],[no])
])dnl ACX_FF

AU_ALIAS([ACX_FFCXX], [AX_FFCXX])
AC_DEFUN([AX_FFCXX], [
AC_PREREQ(2.50)
AC_ARG_VAR(FFCXX,[FreeFEM compiler command])
AC_CHECK_PROG(FFCXX,[ff-c++],[ff-c++],[no])
dnl AC_CHECK_PROGS(FFCXX, ff-c++, $FFCXX)
dnl AC_SUBST(FFCXX)
])dnl ACX_FFCXX

AU_ALIAS([ACX_FFMPI], [AX_FFMPI])
AC_DEFUN([AX_FFMPI], [
AC_PREREQ(2.50)
AC_ARG_VAR(FFMPI,[FreeFEM compiler command])
AC_CHECK_PROG(FFMPI,[ff-mpirun],[ff-mpirun],[no])
dnl AC_CHECK_PROGS(FFMPI, ff-mpirun, $FFMPI)
dnl AC_SUBST(FFMPI)
])dnl ACX_FFMPI

AC_ARG_WITH([mgis],
	[  --with-mgis=            Mgis installation path : (e.g. --with-mgis=/opt/mgis)],
        [mgis="$withval"], [mgis="no"])



AC_ARG_WITH([mfront],
	[  --with-mfront=            mfront installation path : (e.g. --with-mfront=/opt/mgis/bin/mfront)],
        [mfront="$withval"], [mfront="no"])




AC_ARG_WITH(FreeFEM,
	[  --with-FreeFEM=         FreeFEM  installation path : (e.g. --with-FreeFEM=/opt/FreeFem/bin)],
	   FF="${withval}/FreeFem++"
	   FFCXX="${withval}/ff-c++"
	   FFMPI="${withval}/ff-mpirun")
	   
AC_ARG_WITH(Gmsh,
	[  --with-Gmsh=            Gmsh installation path : (e.g. --with-Gmsh=/opt/Gmsh/bin)],
	   GMSH="${withval}/gmsh")	   

SECTION_TITLE([    checking for a C++  compilers       ])
AC_PROG_CXX
AC_LANG(C++)

SECTION_TITLE([      checking for a Gmsh mesher        ])
AX_GMSH
test "$GMSH" == "no" && AC_MSG_ERROR([
  Required  program  'gmsh'  not   found.
  If 'gmsh' is not  present  in  /usr/bin 
  or in /usr/local/bin consider using the
   '--with-Gmsh=your/Gmsh/path/bin'  flag  
   with ./configure command. 
                                   ])


SECTION_TITLE([      checking for a FF++ compilers     ])
AX_FF
test "$FF" == "no" && AC_MSG_ERROR([
  Required  program  'FreeFem++'  not  found.
  If 'FreeFem++' is not  present in  /usr/bin 
  or in  /usr/local/bin  consider  using  the
  '--with-FreeFEM=your/FreeFEM/path/bin' flag  
  with ./configure command. 
                                   ])

AX_FFCXX
test "$FFCXX" == "no" && AC_MSG_ERROR([
  Required  program   'ff-++'   not    found.
  If  'ff-++'  is  not  present  in  /usr/bin 
  or  in  /usr/local/bin consider  using  the
  '--with-FreeFEM=your/FreeFEM/path/bin' flag  
  with ./configure command. 
                                   ])

AX_FFMPI
test "$FFMPI" == "no" && AC_MSG_ERROR([
  Required  program  'ff-mpirun'  not  found.
  If 'ff-mpirun' is not present  in  /usr/bin 
  or in  /usr/local/bin  consider  using  the
  '--with-FreeFEM=your/FreeFEM/path/bin' flag  
  with ./configure command. 
                                  ])

SECTION_TITLE([      checking for a MFront support     ])

AC_SUBST([mgis])
AM_CONDITIONAL([HAVEMGIS], [test $mgis != no])                                  
test "$mgis" == "no" && AC_MSG_WARN([ 
 You did not provide --with-mgis flag so
 MGIS SUPPORT = OFF 

 Mfront will not be configured with PSD:
 
 To have Mfront support in PSD, please correctly
 provide both  --with-mgis   and  --with-mfront 
 flags 
 ])
 
AC_SUBST([mfront])
AM_CONDITIONAL([HAVEMFRONT], [test $mfront != no]) 
test "$mfront" == "no" && AC_MSG_WARN([
 You did not provide --with-front flag so
 MFRONT SUPPORT = OFF 

 Mfront will not be configured with PSD:
 
 To have Mfront support in PSD, please correctly
 provide both  --with-mgis   and  --with-mfront 
 flags 
  
 ])


test "$mfront" != "no" -a "$mgis" != "no" &&  AC_MSG_RESULT([ Mfront will be configured with PSD])

SECTION_TITLE([    generating the required makefiles   ])

#AC_PREFIX_DEFAULT($HOME)
#AC_PREFIX_DEFAULT()
AC_CONFIG_FILES([
 Makefile
 data/Makefile
 data/meshes/2D/Geo-Files/Makefile
 data/meshes/3D/Geo-Files/Makefile 
 src/Makefile
 src/plugins/Makefile
 src/ff-files/Makefile 
 src/plugins/go-fast-plugins/Makefile
 src/plugins/go-fast-plugins/cpp/Makefile
 src/plugins/go-fast-plugins/test/Makefile  
 src/plugins/mfront/Makefile
 src/plugins/mfront/cpp/Makefile
 src/plugins/mfront/law/Makefile
 src/plugins/mfront/law/elasticity/Makefile
 src/plugins/mfront/test/Makefile  
 src/plugins/paraview-output/Makefile 
 src/plugins/paraview-output/cpp/Makefile
 src/plugins/paraview-output/test/Makefile 
 src/plugins/petsc/Makefile
 src/plugins/petsc/cpp/Makefile
 src/plugins/soil-laws/Makefile 
 src/plugins/soil-laws/cpp/Makefile 
 src/plugins/soil-laws/hujeux-law-lib/Makefile
 src/plugins/soil-laws/test/Makefile  
 src/plugins/sparsity-visualizer/Makefile 
 src/plugins/sparsity-visualizer/cpp/Makefile
 src/plugins/sparsity-visualizer/test/Makefile 
 src/plugins/top-ii-vol/Makefile
 src/plugins/top-ii-vol/cpp/Makefile
 src/plugins/top-ii-vol/test/Makefile       
 src/psd-preprocessor/Makefile
 src/psd-solve/Makefile   
 test/load/Makefile 
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
