AC_INIT([PSD], [2.4], [mohd-afeef.badri@cea.fr])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

AC_CONFIG_HEADERS([config.h])
dnl AC_PREFIX_PROGRAM (gcc)


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

AC_ARG_WITH([dependencies],
	[  --with-dependencies=            Dependencies installation : (e.g. --with-dependencies=yes)],
        [dependencies="$withval"], [dependencies="no"])

AC_ARG_WITH([mgis],
	[  --with-mgis=            Mgis installation path : (e.g. --with-mgis=/opt/install/local)],
        [mgis="$withval"], [mgis="no"])



AC_ARG_WITH([mfront],
	[  --with-mfront=            mfront installation path : (e.g. --with-mfront=/opt/install/local)],
        [mfront="$withval"], [mfront="no"])




AC_ARG_WITH(FreeFEM,
	[  --with-FreeFEM=         FreeFEM  installation path : (e.g. --with-FreeFEM=/opt/FreeFem/bin)],
	   FF="${withval}/FreeFem++"
	   FFCXX="${withval}/ff-c++"
	   FFMPI="${withval}/ff-mpirun")

AC_ARG_WITH(Gmsh,
	[  --with-Gmsh=            Gmsh installation path : (e.g. --with-Gmsh=/opt/Gmsh/bin)],
	   GMSH="${withval}/gmsh")

AC_SUBST([dependencies])
AM_CONDITIONAL([BUILDDEPENDENCIES], [test $dependencies != no])
test "$dependencies" == "no" && AC_MSG_WARN([

 PSD can automatically build for you its dependencies
 FreeFEM, PETSc, MFront, MGIS, METIS, ParMETIS, etc.
 In order to do so

 --with-dependencies=yes

 A power user is adviced to build these on their own.
 ])

AU_ALIAS([ACX_MPI], [AX_MPI])
AC_DEFUN([AX_MPI], [
AC_PREREQ(2.50)

AC_LANG_CASE([C], [
	AC_REQUIRE([AC_PROG_CC])
	AC_ARG_VAR(MPICC,[MPI C compiler command])
	AC_CHECK_PROGS(MPICC, mpicc hcc mpxlc_r mpxlc mpcc cmpicc, $CC)
	ax_mpi_save_CC="$CC"
	CC="$MPICC"
	AC_SUBST(MPICC)
],
[C++], [
	AC_REQUIRE([AC_PROG_CXX])
	AC_ARG_VAR(MPICXX,[MPI C++ compiler command])
	AC_CHECK_PROGS(MPICXX, mpic++ mpicxx mpiCC hcp mpxlC_r mpxlC mpCC cmpic++, $CXX)
	ax_mpi_save_CXX="$CXX"
	CXX="$MPICXX"
	AC_SUBST(MPICXX)
],
[Fortran 77], [
	AC_REQUIRE([AC_PROG_F77])
	AC_ARG_VAR(MPIF77,[MPI Fortran 77 compiler command])
	AC_CHECK_PROGS(MPIF77, mpif77 hf77 mpxlf_r mpxlf mpf77 cmpifc, $F77)
	ax_mpi_save_F77="$F77"
	F77="$MPIF77"
	AC_SUBST(MPIF77)
],
[Fortran], [
	AC_REQUIRE([AC_PROG_FC])
	AC_ARG_VAR(MPIFC,[MPI Fortran compiler command])
	AC_CHECK_PROGS(MPIFC, mpif90 mpxlf95_r mpxlf90_r mpxlf95 mpxlf90 mpf90 cmpif90c, $FC)
	ax_mpi_save_FC="$FC"
	FC="$MPIFC"
	AC_SUBST(MPIFC)
])



if test x = x"$MPILIBS"; then
	AC_LANG_CASE([C], [AC_CHECK_FUNC(MPI_Init, [MPILIBS=" "])],
		[C++], [AC_CHECK_FUNC(MPI_Init, [MPILIBS=" "])],
		[Fortran 77], [AC_MSG_CHECKING([for MPI_Init])
			AC_LINK_IFELSE([AC_LANG_PROGRAM([],[      call MPI_Init])],[MPILIBS=" "
				AC_MSG_RESULT(yes)], [AC_MSG_RESULT(no)])],
		[Fortran], [AC_MSG_CHECKING([for MPI_Init])
			AC_LINK_IFELSE([AC_LANG_PROGRAM([],[      call MPI_Init])],[MPILIBS=" "
				AC_MSG_RESULT(yes)], [AC_MSG_RESULT(no)])])
fi
AC_LANG_CASE([Fortran 77], [
	if test x = x"$MPILIBS"; then
		AC_CHECK_LIB(fmpi, MPI_Init, [MPILIBS="-lfmpi"])
	fi
	if test x = x"$MPILIBS"; then
		AC_CHECK_LIB(fmpich, MPI_Init, [MPILIBS="-lfmpich"])
	fi
],
[Fortran], [
	if test x = x"$MPILIBS"; then
		AC_CHECK_LIB(fmpi, MPI_Init, [MPILIBS="-lfmpi"])
	fi
	if test x = x"$MPILIBS"; then
		AC_CHECK_LIB(mpichf90, MPI_Init, [MPILIBS="-lmpichf90"])
	fi
])
if test x = x"$MPILIBS"; then
	AC_CHECK_LIB(mpi, MPI_Init, [MPILIBS="-lmpi"])
fi
if test x = x"$MPILIBS"; then
	AC_CHECK_LIB(mpich, MPI_Init, [MPILIBS="-lmpich"])
fi

dnl We have to use AC_TRY_COMPILE and not AC_CHECK_HEADER because the
dnl latter uses $CPP, not $CC (which may be mpicc).
AC_LANG_CASE([C], [if test x != x"$MPILIBS"; then
	AC_MSG_CHECKING([for mpi.h])
	AC_TRY_COMPILE([#include <mpi.h>],[],[AC_MSG_RESULT(yes)], [MPILIBS=""
		AC_MSG_RESULT(no)])
fi],
[C++], [if test x != x"$MPILIBS"; then
	AC_MSG_CHECKING([for mpi.h])
	AC_TRY_COMPILE([#include <mpi.h>],[],[AC_MSG_RESULT(yes)], [MPILIBS=""
		AC_MSG_RESULT(no)])
fi],
[Fortran 77], [if test x != x"$MPILIBS"; then
	AC_MSG_CHECKING([for mpif.h])
	AC_COMPILE_IFELSE([AC_LANG_PROGRAM([],[      include 'mpif.h'])],[AC_MSG_RESULT(yes)], [MPILIBS=""
		AC_MSG_RESULT(no)])
fi],
[Fortran], [if test x != x"$MPILIBS"; then
	AC_MSG_CHECKING([for mpif.h])
	AC_COMPILE_IFELSE([AC_LANG_PROGRAM([],[      include 'mpif.h'])],[AC_MSG_RESULT(yes)], [MPILIBS=""
		AC_MSG_RESULT(no)])
fi])

AC_LANG_CASE([C], [CC="$ax_mpi_save_CC"],
	[C++], [CXX="$ax_mpi_save_CXX"],
	[Fortran 77], [F77="$ax_mpi_save_F77"],
	[Fortran], [FC="$ax_mpi_save_FC"])

AC_SUBST(MPILIBS)

# Finally, execute ACTION-IF-FOUND/ACTION-IF-NOT-FOUND:
if test x = x"$MPILIBS"; then
        $2
        :
else
        ifelse([$1],,[AC_DEFINE(HAVE_MPI,1,[Define if you have the MPI library.])],[$1])
        :
fi
])

SECTION_TITLE([ checking for a C++/MPIC++ compilers ])
AC_PROG_CXX
AC_LANG(C++)
AX_MPI

SECTION_TITLE([ checking for a C/MPIC compilers ])
AC_PROG_CC
AC_LANG(C)
AX_MPI

SECTION_TITLE([ checking for a Fortran/MPIFC compilers ])
AC_PROG_FC
AC_LANG(Fortran)
AX_MPI

SECTION_TITLE([ checking for a Fortran-77/MPIF77 compilers ])
AC_PROG_F77
AC_LANG(Fortran 77)
AX_MPI

AC_ARG_WITH(MPICXX,
	[  --with-MPICXX=          path of the MPI C++ compiler to be used
	                  (e.g. --with-MPICXX=your/MPIC++/Install/path/bin/mpic++)],
	   MPICXX="${withval}")

AC_ARG_WITH(MPICC,
	[  --with-MPICC=          path of the MPI C compiler to be used
	                  (e.g. --with-MPICC=your/MPIC++/Install/path/bin/mpicc)],
	   MPICC="${withval}")

AC_ARG_WITH(MPIFC,
	[  --with-MPIFC=          path of the MPI Fortran compiler to be used
	                  (e.g. --with-MPIFC=your/MPIFC/Install/path/bin/mpicf90)],
	   MPIFC="${withval}")

AC_ARG_WITH(MPIF77,
	[  --with-MPIF77=          path of the MPI C++ compiler to be used
	                  (e.g. --with-MPIF77=your/MPIF77/Install/path/bin/mpif77)],
	   MPIF77="${withval}")

test "$MPICXX" == "$CXX" && AC_MSG_ERROR([

  Required  MPI C++ compilers were not  found. If you are
  sure that MPI C++ compiler is  present on you operating
  system you might use the ./configure flag:

    '--with-MPICXX=your/MPIC++/Install/path/bin/mpic++'

  to provide the location of MPI C++ compiler.
                                   ])

test "$MPICC" == "$CC" && AC_MSG_ERROR([

  Required  MPI C compilers were not  found. If you are
  sure that MPI C compiler is  present on you operating
  system you might use the ./configure flag:

    '--with-MPICC=your/MPIC/Install/path/bin/mpicc'

  to provide the location of MPI C compiler.
                                   ])

test "$MPIFC" == "$FC" && AC_MSG_ERROR([

  Required  MPI Fortran compilers were not  found. If you are
  sure that MPI Fortran compiler is  present on you operating
  system you might use the ./configure flag:

    '--with-MPIFC=your/MPIFC/Install/path/bin/mpif90'

  to provide the location of MPI Fortran compiler.
                                   ])

test "$MPIF77" == "$F77" && AC_MSG_ERROR([

  Required  MPI Fortran 77 compilers were not  found. If you are
  sure that MPI Fortran 77 compiler is  present on you operating
  system you might use the ./configure flag:

    '--with-MPIFC=your/MPIFC/Install/path/bin/mpif77'

  to provide the location of MPI Fortran 77 compiler.
                                   ])




SECTION_TITLE([      checking for a Gmsh mesher        ])
AX_GMSH
test "$dependencies" == "no" -a "$GMSH" == "no"  && AC_MSG_ERROR([
  Required  program  'gmsh'  not   found.
  If 'gmsh' is not  present  in  /usr/bin
  or in /usr/local/bin consider using the
   '--with-Gmsh=your/Gmsh/path/bin'  flag
   with ./configure command.
                                   ])


SECTION_TITLE([      checking for a FF++ compilers     ])
AX_FF
test "$dependencies" == "no" -a  "$FF" == "no" && AC_MSG_ERROR([
  Required  program  'FreeFem++'  not  found.
  If 'FreeFem++' is not  present in  /usr/bin
  or in  /usr/local/bin  consider  using  the
  '--with-FreeFEM=your/FreeFEM/path/bin' flag
  with ./configure command.
                                   ])

AX_FFCXX
test "$dependencies" == "no" -a  "$FFCXX" == "no" && AC_MSG_ERROR([
  Required  program   'ff-++'   not    found.
  If  'ff-++'  is  not  present  in  /usr/bin
  or  in  /usr/local/bin consider  using  the
  '--with-FreeFEM=your/FreeFEM/path/bin' flag
  with ./configure command.
                                   ])

AX_FFMPI
test "$dependencies" == "no" -a  "$FFMPI" == "no" && AC_MSG_ERROR([
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
 Mfront will not be configured with PSD,
 you did not provide --with-mgis flag so

 MGIS SUPPORT = OFF

 To have Mfront support in PSD, please correctly
 provide both  --with-mgis   and  --with-mfront
 flags.
 ])

AC_SUBST([mfront])
AM_CONDITIONAL([HAVEMFRONT], [test $mfront != no])
test "$mfront" == "no" && AC_MSG_WARN([
 Mfront will not be configured with PSD,
 You did not provide --with-front flag so

 MFRONT SUPPORT = OFF

 To have Mfront support in PSD, please correctly
 provide both  --with-mgis   and  --with-mfront
 flags.
 ])




dnl ---------------------------------------------------------------
dnl Associate appropriate suffix for diffrent os
dnl ---------------------------------------------------------------
SECTION_TITLE([      checking for operating system type    ])

os_uname=`uname`
case $os_uname in
     CYGWIN*|MINGW*|MSYS_NT*)
	os_type="windows";;
     Darwin)
	os_type="mac";;
     Linux)
	os_type="linux";;
     *)
	os_type="unknown";;
esac

AC_MSG_RESULT([])
test "$os_type" == "windows" && AC_MSG_RESULT([ OS identified: Windows])
test "$os_type" == "mac"     && AC_MSG_RESULT([ OS identified: MacOs])
test "$os_type" == "linux"   && AC_MSG_RESULT([ OS identified: Linux])

test "$os_type" == "unknown" && AC_MSG_ERROR([
  For the moment PSD is only built on Linux or MacOS
  please contact  mohd-afeef.badri@cea.fr  for  help
  regarding to building PSD on your OS.
                                   ])

AM_CONDITIONAL([WINDOWS], [test "$os_type" == "windows"])
AM_CONDITIONAL([MAC],     [test "$os_type" == "mac"])
AM_CONDITIONAL([LINUX],   [test "$os_type" == "linux"])

test "$os_type" == "windows" && AC_SUBST(SO_SUFFIX,"dll"  )
test "$os_type" == "mac"     && AC_SUBST(SO_SUFFIX,"dylib")
test "$os_type" == "linux"   && AC_SUBST(SO_SUFFIX,"so"   )

AC_MSG_RESULT([ Shared object sufix   : '$SO_SUFFIX'])
dnl ---------------------------------------------------------------

SECTION_TITLE([    generating the required makefiles   ])

#AC_PREFIX_DEFAULT($HOME)
#AC_PREFIX_DEFAULT()
AC_CONFIG_FILES([
 Makefile
 data/Makefile
 data/meshes/2D/Geo-Files/Makefile
 data/meshes/3D/Geo-Files/Makefile
 ext/Makefile
 src/Makefile
 src/plugins/Makefile
 src/ff-files/Makefile
 src/plugins/go-fast-plugins/Makefile
 src/plugins/go-fast-plugins/cpp/Makefile
 src/plugins/go-fast-plugins/test/Makefile
 src/plugins/mfront/Makefile
 src/plugins/mfront/cpp/Makefile
 src/plugins/mfront/law/Makefile
 src/plugins/mfront/law/test/Makefile
 src/plugins/mfront/test/Makefile
 src/plugins/paraview-output/Makefile
 src/plugins/paraview-output/cpp/Makefile
 src/plugins/paraview-output/test/Makefile
 src/plugins/pdmt/Makefile
 src/plugins/pdmt/cpp/Makefile
 src/plugins/pdmt/test/Makefile
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
 test/Makefile
 test/elastodynamics/Makefile
 test/elasto-plastic/Makefile
 test/fracture-mechanics/Makefile
 test/linear-elasticity/Makefile
 test/soildynamics/Makefile
])
AC_OUTPUT

SECTION_TITLE([               status               ])

dnl Print results
AC_MSG_RESULT([])
AC_MSG_RESULT([ PSD version $VERSION configured successfully.])
AC_MSG_RESULT([])
AC_MSG_RESULT([ PSD install  path  : '$prefix'])
AC_MSG_RESULT([ PSD tutoirlas path : '$HOME/PSD-tutorials'])
AC_MSG_RESULT([])
AC_MSG_RESULT([ C++ compiler       : '$CXX'])
AC_MSG_RESULT([ C compiler         : '$CC'])
AC_MSG_RESULT([ FC compiler        : '$FC'])
AC_MSG_RESULT([ F77 compiler       : '$F77'])
AC_MSG_RESULT([])
AC_MSG_RESULT([ C/C++ compiler flags   : '$CXXFLAGS'])
AC_MSG_RESULT([ F77/FC compiler flags  : '$FCFLAGS'])
AC_MSG_RESULT([])
AC_MSG_RESULT([ MPIC++ compiler    : '$MPICXX'])
AC_MSG_RESULT([ MPIC   compiler    : '$MPICC'])
AC_MSG_RESULT([ MPIF77 compiler    : '$MPIF77'])
AC_MSG_RESULT([ MPIFC  compiler    : '$MPIFC'])
AC_MSG_RESULT([])
AC_MSG_RESULT([ FreeFEM compiler   : '$FF'])
test "$LDFLAGS" != "" && AC_MSG_RESULT([ Building with '$LDFLAGS' for linker flags.])
test "$LIBS"    != "" && AC_MSG_RESULT([ Building with '$LIBS' libraries.])
AC_MSG_RESULT([])
test "$dependencies"   != "no"            &&  AC_MSG_RESULT([ Dependencies  compile   : ENABLED])
AC_MSG_RESULT([])
test "$mfront" != "no" -a "$mgis" != "no" &&  AC_MSG_RESULT([ Mfront   : YES])
test "$mfront" == "no" -o "$mgis" == "no" &&  AC_MSG_RESULT([ Mfront   : NO])
test "$GMSH"   == "no"                    &&  AC_MSG_RESULT([ Gmsh     : NO])
test "$GMSH"   != "no"                    &&  AC_MSG_RESULT([ Gmsh     : YES])
test "$FF"     != "no"                    &&  AC_MSG_RESULT([ PSD Seq  : YES])
test "$FFMPI" == "no"                     &&  AC_MSG_RESULT([ PSD Par  : NO])
test "$FFMPI" != "no"                     &&  AC_MSG_RESULT([ PSD Par  : YES])
AC_MSG_RESULT([])
