AC_INIT([PSD],[2.6],[mohd-afeef.badri@cea.fr])
AM_INIT_AUTOMAKE([-Wall -Werror foreign parallel-tests])

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

dnl ---------------------------------------------------------------
dnl arguments for compiling with med support : hdf5, medfile, medcoupling
dnl ---------------------------------------------------------------
AC_ARG_WITH([hdf5],
	[  --with-hdf5=               hdf5 root path : (e.g. --with-hdf5=/home/salome/INSTALL/hdf5)],
        [hdf5="$withval"], [hdf5="no"])

AC_ARG_WITH([medfile],
	[  --with-medfile=            medfile root path : (e.g. --with-medfile=/home/salome/INSTALL/medfile)],
        [medfile="$withval"], [medfile="no"])

AC_ARG_WITH([medcoupling],
	[  --with-medcoupling=        medcoupling root path : (e.g. --with-salome=/home/salome/INSTALL/MEDCOUPLING)],
        [medcoupling="$withval"], [medcoupling="no"])


AU_ALIAS([ACX_GMSH], [AX_GMSH])
AC_DEFUN([AX_GMSH], [
AC_PREREQ([2.71])
AC_ARG_VAR(GMSH,[Gmsh mesher])
AC_CHECK_PROG(GMSH,[gmsh],[gmsh],[no])
dnl AC_CHECK_PROGS(GMSH, gmsh, $GMSH)
dnl AC_SUBST(GMSH)
])dnl ACX_GMSH

AU_ALIAS([ACX_FF], [AX_FF])
AC_DEFUN([AX_FF], [
AC_PREREQ([2.71])
AC_ARG_VAR(FF,[FreeFEM compiler command])
AC_CHECK_PROG(FF,[FreeFem++],[FreeFem++],[no])
])dnl ACX_FF

AU_ALIAS([ACX_FFCXX], [AX_FFCXX])
AC_DEFUN([AX_FFCXX], [
AC_PREREQ([2.71])
AC_ARG_VAR(FFCXX,[FreeFEM compiler command])
AC_CHECK_PROG(FFCXX,[ff-c++],[ff-c++],[no])
dnl AC_CHECK_PROGS(FFCXX, ff-c++, $FFCXX)
dnl AC_SUBST(FFCXX)
])dnl ACX_FFCXX

AU_ALIAS([ACX_FFCXXDEP], [AX_FFCXXDEP])
AC_DEFUN([AX_FFCXXDEP], [
AC_PREREQ([2.71])
AC_ARG_VAR(FFCXXDEP,[ff-c++ compiler dependencies])
AC_CHECK_PROG(FFCXXDEP,[ff-get-dep],[ff-get-dep],[no])
])dnl ACX_FFCXXDEP

AU_ALIAS([ACX_FFMPI], [AX_FFMPI])
AC_DEFUN([AX_FFMPI], [
AC_PREREQ([2.71])
AC_ARG_VAR(FFMPI,[FreeFEM compiler command])
AC_CHECK_PROG(FFMPI,[ff-mpirun],[ff-mpirun],[no])
dnl AC_CHECK_PROGS(FFMPI, ff-mpirun, $FFMPI)
dnl AC_SUBST(FFMPI)
])dnl ACX_FFMPI

AC_ARG_VAR(MPIRUN,[MPIRUN command])
AC_CHECK_PROGS(MPIRUN, mpirun mpiexec srun ccc_mprun, $MPIRUN)


AC_ARG_WITH([dependencies],
	[  --with-dependencies=         Dependencies installation : (e.g. --with-dependencies=yes)],
        [dependencies="$withval"], [dependencies="no"])

AC_ARG_WITH([zipped_dependencies],
	[  --with-zipped_dependencies=  Folder contaning tar.gz for dependencies : (e.g. --with-zipped_dependencies=yes)
	],
        [zipped_dependencies="$withval"], [zipped_dependencies="no"])

AC_ARG_WITH(FreeFEM,
	[  --with-FreeFEM=         FreeFEM  installation path : (e.g. --with-FreeFEM=/opt/FreeFem/bin)],
	   FF="${withval}/FreeFem++"
	   FFCXX="${withval}/ff-c++"
	   FFCXXDEP="${withval}/ff-get-dep"
	   FFMPI="${withval}/ff-mpirun")

AC_ARG_WITH(Gmsh,
	[  --with-Gmsh=            Gmsh installation path : (e.g. --with-Gmsh=/opt/Gmsh/bin)],
	   GMSH="${withval}/gmsh")

AC_ARG_WITH([salome],
	[  --with-salome=          salome installation path : (e.g. --with-salome=/opt/install/local)
	],
        [salome="$withval"], [salome="no"])

AC_SUBST([dependencies])
AM_CONDITIONAL([BUILDDEPENDENCIES], [test $dependencies != no])
test "$dependencies" == "no" && AC_MSG_WARN([

 PSD can automatically build for you its dependencies
 FreeFEM, PETSc, MFront, MGIS, METIS,  ParMETIS, etc.
 A power user is adviced to build these on their own.
 In order to do so

 --with-dependencies=yes

 The wget command will be used to download these,  if
 you wish to provided already downloaded  files,  use
   --with-zipped_dependencies  option.
 ])


AC_SUBST([zipped_dependencies])
AM_CONDITIONAL([BUILDZIPPEDDEPENDENCIES], [test $zipped_dependencies != no])
test "$zipped_dependencies" == "no" && AC_MSG_WARN([

 PSD can automatically build for you its dependencies
 FreeFEM, PETSc, MFront,  MGIS, METIS, ParMETIS, etc.
 from *.tar.gz files. In order to do so, provide the
 tar.gz files for dependencies in /ext folder of PSD

 --with-zipped_dependencies=yes
 ])

AU_ALIAS([ACX_MPI], [AX_MPI])
AC_DEFUN([AX_MPI], [
AC_PREREQ([2.71])

AC_LANG_CASE(
[C], [
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

dnl We have to use AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[]], [[]])],[],[]) and not AC_CHECK_HEADER because the
dnl latter uses $CPP, not $CC (which may be mpicc).
AC_LANG_CASE([C], [if test x != x"$MPILIBS"; then
	AC_MSG_CHECKING([for mpi.h])
	AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <mpi.h>]], [[]])],[AC_MSG_RESULT(yes)],[MPILIBS=""
		AC_MSG_RESULT(no)])
fi],
[C++], [if test x != x"$MPILIBS"; then
	AC_MSG_CHECKING([for mpi.h])
	AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <mpi.h>]], [[]])],[AC_MSG_RESULT(yes)],[MPILIBS=""
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
	[  --with-MPICC=           path of the MPI C compiler to be used
	                  (e.g. --with-MPICC=your/MPIC++/Install/path/bin/mpicc)],
	   MPICC="${withval}")

AC_ARG_WITH(MPIFC,
	[  --with-MPIFC=           path of the MPI Fortran compiler to be used
	                  (e.g. --with-MPIFC=your/MPIFC/Install/path/bin/mpicf90)],
	   MPIFC="${withval}")

AC_ARG_WITH(MPIF77,
	[  --with-MPIF77=          path of the MPI C++ compiler to be used
	                  (e.g. --with-MPIF77=your/MPIF77/Install/path/bin/mpif77)],
	   MPIF77="${withval}")

AC_ARG_WITH(MPIRUN,
	[  --with-MPIRUN=          path of the MPIRUN to be used
	                  (e.g. --with-MPIRUN=your/Install/path/bin/mpirun)],
	   MPIRUN="${withval}")


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

dnl ---------------------------------------------------------------
dnl Did the user provide Gmsh mesher
dnl ---------------------------------------------------------------

SECTION_TITLE([      checking for a Gmsh mesher        ])

AX_GMSH

if test "$dependencies" != "no"  && test "$os_type" != "mac"; then
dnl Use internally built dependencies from ext/
  GMSH="${prefix}/bin/gmsh"
fi

dnl Summary logging
AC_MSG_RESULT([])
AC_MSG_RESULT([Using internal dependencies... $dependencies])
AC_MSG_RESULT([checking for Gmsh...           $GMSH])
AC_MSG_RESULT([Gmsh support...                $HAVE_MFRONT_SUPPORT])
AC_MSG_RESULT([])

dnl If GMSH is not found, then error out
test "$GMSH" == "no"  && AC_MSG_ERROR([
  Required  program  'gmsh'  not   found.
  If 'gmsh' is not  present  in  /usr/bin
  or in /usr/local/bin consider using the
   '--with-Gmsh=your/Gmsh/path/bin'  flag
   with ./configure command.
                                   ])
dnl ---------------------------------------------------------------


dnl ---------------------------------------------------------------
dnl Did the user provide FreeFEM compilers
dnl ---------------------------------------------------------------

SECTION_TITLE([      checking for a FreeFEM compilers     ])

HAVE_FF_SUPPORT=no

AX_FF
AX_FFCXX
AX_FFCXXDEP
AX_FFMPI

if test "$dependencies" != "no"; then
dnl Use internally built dependencies from ext/
  FF="${prefix}/bin/FreeFem++"
  FFCXX="${prefix}/bin/ff-c++"
  FFCXXDEP="${prefix}/bin/ff-get-dep"
  FFMPI="${prefix}/bin/ff-mpirun"
  HAVE_FF_SUPPORT=yes
fi

if test "$FF" != "no" && test "$FFCXX" != "no" && test "$FFCXXDEP" != "no" && test "$FFMPI" != "no"; then
  HAVE_FF_SUPPORT=yes
fi

dnl Summary logging
AC_MSG_RESULT([])
AC_MSG_RESULT([Using internal dependencies... $dependencies])
AC_MSG_RESULT([checking for FreeFem++...      $FF])
AC_MSG_RESULT([checking for ff-c++...         $FFCXX])
AC_MSG_RESULT([checking for ff-get-dep...     $FFCXXDEP])
AC_MSG_RESULT([checking for ff-mpirun...      $FFMPI])
AC_MSG_RESULT([FreeFEM support...             $HAVE_FF_SUPPORT])
AC_MSG_RESULT([])


if test "$HAVE_FF_SUPPORT" = no; then
  AC_MSG_ERROR([
 Required  program  'FreeFem++'  not  found.
 You must provide either:

  --with-dependencies
    OR
  --with-FreeFEM=your/FreeFEM/path/bin

 FREEFEM SUPPORT = OFF
])
fi
dnl ---------------------------------------------------------------

dnl ---------------------------------------------------------------
dnl Did the user provide mfront/mgis
dnl ---------------------------------------------------------------

SECTION_TITLE([      checking for a MFront/MGIS support     ])

HAVE_MGIS_SUPPORT=no
HAVE_MFRONT_SUPPORT=no
MFRONT_PREFIX=""
MGIS_PREFIX=""
MGIS_LIBS=""
MGIS_LDFLAGS=""
MGIS_CPPFLAGS=""

AC_ARG_WITH([mfront],
  AS_HELP_STRING([--with-mfront=PREFIX],
                 [prefix where mfront is installed]),
  [MFRONT_PREFIX="$withval"],
  [MFRONT_PREFIX=""]
)

if test "$dependencies" != "no"; then
  if test "x$MFRONT_PREFIX" = "x"; then
    MFRONT_PREFIX="${prefix}"
    PATH="$prefix/bin:$PATH"
    mgis="${prefix}"
    AC_PATH_PROG([MFRONT], [mfront])
  fi
fi

# If user gave --with-mfront, prepend its bin to PATH for detection
if test "x$MFRONT_PREFIX" != "x"; then
  PATH="$MFRONT_PREFIX/bin:$PATH"
fi

# Look for the mfront executable
AC_PATH_PROG([MFRONT], [mfront])
AC_SUBST([MFRONT])
AC_MSG_NOTICE([Using mfront: $MFRONT])

dnl ---------------------------------------------------------------
dnl MGIS argument and path preparation (don't test library yet)
dnl ---------------------------------------------------------------
AC_ARG_WITH([mgis],
  AS_HELP_STRING([--with-mgis@<:@=PATH@:>@],
                 [Enable MFront Generic Interface support (auto-detects from Spack LIBRARY_PATH if available)]),
  [with_mgis="$withval"],
  [with_mgis="auto"])

dnl 1. Handle Internal Dependencies Override
if test "$dependencies" != "no"; then
    AC_MSG_NOTICE([Using internal PSD dependencies for MGIS])
    MGIS_PREFIX="${prefix}"
    MFRONT="${prefix}/bin/mfront"
    HAVE_MGIS_SUPPORT=yes
    HAVE_MFRONT_SUPPORT=yes

dnl 2. Automatic Detection (via Spack/Environment)
else
    # Locate mfront executable
    AC_PATH_PROG([MFRONT], [mfront])
	if test "x$MFRONT_PREFIX" = "x"; then
		HAVE_MFRONT_SUPPORT=yes
	fi
    
    # Locate the MGIS library folder by scanning LD_LIBRARY_PATH
    AC_MSG_CHECKING([for MGIS library directory])
    found_lib_dir=""
    save_IFS=$IFS; IFS=':'
    for dir in $LD_LIBRARY_PATH; do
        if test -f "$dir/libMFrontGenericInterface.$SO_SUFFIX"; then
            found_lib_dir=$dir
            break
        fi
    done
    IFS=$save_IFS

    if test -n "$found_lib_dir"; then
        AC_MSG_RESULT([$found_lib_dir])
        # Derive prefix by going up one level from the lib directory
        MGIS_PREFIX=`AS_DIRNAME(["$found_lib_dir"])`
        HAVE_MGIS_SUPPORT=yes
    else
        AC_MSG_RESULT([not found])
        # Fallback to user-provided --with-mgis path if available
        if test "$mgis" != "no" && test -d "$mgis"; then
            MGIS_PREFIX="$mgis"
            HAVE_MGIS_SUPPORT=yes
        fi
    fi
fi

dnl 3. Set Flags if MGIS is found
if test "$HAVE_MGIS_SUPPORT" = "yes"; then
    MGIS_LIBS="-lMFrontGenericInterface"
    MGIS_LDFLAGS="-L$MGIS_PREFIX/lib"
    MGIS_CPPFLAGS="-I$MGIS_PREFIX/include"
    
    # Verification check
    save_LDFLAGS="$LDFLAGS"
    LDFLAGS="$MGIS_LDFLAGS $LDFLAGS"
    AC_CHECK_LIB([MFrontGenericInterface], [main], [], [
        AC_MSG_WARN([Linking test failed. Ensure all MGIS dependencies are in LD_LIBRARY_PATH.])
    ])
    LDFLAGS="$save_LDFLAGS"
fi

dnl Export variables to Makefiles
AC_SUBST([MFRONT_PREFIX])
AC_SUBST([MGIS_PREFIX])
AC_SUBST([MGIS_LIBS])
AC_SUBST([MGIS_LDFLAGS])
AC_SUBST([MGIS_CPPFLAGS])
AC_SUBST([MFRONT])

AM_CONDITIONAL([HAVEMFRONTPREFIX], [test "x$MFRONT_PREFIX" != "x"])
AM_CONDITIONAL([HAVEMFRONT], [test "$HAVE_MFRONT_SUPPORT" = yes])
AM_CONDITIONAL([HAVEMGIS], [test "$HAVE_MGIS_SUPPORT" = yes])

dnl Summary report
AC_MSG_RESULT([])
AC_MSG_RESULT([MGIS Prefix:       $MGIS_PREFIX])
AC_MSG_RESULT([MGIS Support:      $HAVE_MGIS_SUPPORT])
AC_MSG_RESULT([MFront Prefix:     $MFRONT_PREFIX])
AC_MSG_RESULT([MFront support:    $HAVE_MFRONT_SUPPORT])

dnl ---------------------------------------------------------------

dnl ---------------------------------------------------------------
dnl Did the user provide salome
dnl ---------------------------------------------------------------
SECTION_TITLE([      checking for a salome support     ])

AC_SUBST([salome])
AM_CONDITIONAL([HAVESALOME], [test $salome != no])
test "$salome" == "no" && AC_MSG_WARN([
 PSD will not be configured with salome,
 you did not provide --with-salome flag so

 SALOME SUPPORT = OFF

 To have salome support in PSD, please correctly
 provide both  --with-salome flag.
 ])
dnl ---------------------------------------------------------------

dnl ---------------------------------------------------------------
dnl Did the user provide hdf5/medfile/medcoupling
dnl ---------------------------------------------------------------

SECTION_TITLE([      checking for a med support     ])

HAVE_MED_SUPPORT=no

if test "$dependencies" != "no" && test "$os_type" != "mac" ; then
dnl Use internally built dependencies from ext/
  hdf5="${prefix}/MEDCOUPLING-9.14.0/BINARIES-CO7/hdf5"
  medfile="${prefix}/MEDCOUPLING-9.14.0/BINARIES-CO7/medfile"
  medcoupling="${prefix}/MEDCOUPLING-9.14.0/INSTALL/MEDCOUPLING"
fi

if test "$hdf5" != "no" && test "$medfile" != "no" && test "$medcoupling" != "no"; then
  AC_SUBST(CXXFLAGS_MED, "-I${hdf5}/include -I${medfile}/include -I${medcoupling}/include ${CXXFLAGS}")
  AC_SUBST(LDFLAGS_MED,  "-L${hdf5}/lib -L${medfile}/lib -L${medcoupling}/lib ${LDFLAGS}")
  AC_SUBST(LIBS_MED,     "-lhdf5 -lmedC -lmedloader -lmedcoupling -linterpkernel -lmedcouplingremapper ${LIBS}")
  HAVE_MED_SUPPORT=yes
fi

AC_SUBST([hdf5])
AC_SUBST([medfile])
AC_SUBST([medcoupling])

AM_CONDITIONAL([HAVEMED], [test "$HAVE_MED_SUPPORT" = yes])

dnl Summary logging
AC_MSG_RESULT([])
AC_MSG_RESULT([Using internal dependencies... $dependencies])
AC_MSG_RESULT([checking for hdf5...          $hdf5])
AC_MSG_RESULT([checking for medfile...       $medfile])
AC_MSG_RESULT([checking for medcoupling...   $medcoupling])
AC_MSG_RESULT([MED support...                $HAVE_MED_SUPPORT])
AC_MSG_RESULT([])

if test "$HAVE_MED_SUPPORT" = no; then
  AC_MSG_WARN([
 top-ii-vol will not be configured with MED support.
 You must provide either:

  --with-dependencies
    OR
  --with-hdf5
  --with-medfile
  --with-medcoupling

 MED SUPPORT = OFF
])
fi
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
 src/plugins/medio/Makefile
 src/plugins/medio/cpp/Makefile
 src/plugins/medio/test/Makefile
 src/plugins/mfront/Makefile
 src/plugins/mfront/cpp/Makefile
 src/plugins/mfront/law/Makefile
 src/plugins/mfront/law/test/Makefile
 src/plugins/mfront/test/Makefile
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
 test/poisson/Makefile
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
AC_MSG_RESULT([ MPIRUN             : '$MPIRUN'])
AC_MSG_RESULT([ MPIC++ compiler    : '$MPICXX'])
AC_MSG_RESULT([ MPIC   compiler    : '$MPICC'])
AC_MSG_RESULT([ MPIF77 compiler    : '$MPIF77'])
AC_MSG_RESULT([ MPIFC  compiler    : '$MPIFC'])
AC_MSG_RESULT([])
AC_MSG_RESULT([ FreeFEM compiler   : '$FF'])
AC_MSG_RESULT([ ff-c++  compiler   : '$FFCXX'])
AC_MSG_RESULT([ ff-mpi  compiler   : '$FFMPI'])
dnl if test "$HAVE_MED_SUPPORT" = yes; then
dnl  AC_MSG_RESULT([])
dnl  AC_MSG_RESULT([ CXXFLAGS_MED       : '$CXXFLAGS_MED'])
dnl  AC_MSG_RESULT([ LDFLAGS_MED        : '$LDFLAGS_MED'])
dnl  AC_MSG_RESULT([ LIBS_MED           : '$LIBS_MED'])
dnl fi
test "$LDFLAGS" != "" && AC_MSG_RESULT([ Building with '$LDFLAGS' for linker flags.])
test "$LIBS"    != "" && AC_MSG_RESULT([ Building with '$LIBS' libraries.])
AC_MSG_RESULT([])
test "$dependencies"          != "no"     &&  AC_MSG_RESULT([ Dependencies  compile        : ENABLED])
test "$zipped_dependencies"   != "no"     &&  AC_MSG_RESULT([ Dependencies  from *.tar.gz  : ENABLED])
AC_MSG_RESULT([])
test "$mfront"      != "no" -a "$mgis" != "no" 				&&  AC_MSG_RESULT([ Mfront      : YES])
test "$mfront"      == "no" -o "$mgis" == "no" 				&&  AC_MSG_RESULT([ Mfront      : NO])
test "$GMSH"        == "no"                    				&&  AC_MSG_RESULT([ Gmsh        : NO])
test "$GMSH"        != "no"                    				&&  AC_MSG_RESULT([ Gmsh        : YES])
test "$hdf5"        != "no" 						&&  AC_MSG_RESULT([ Hdf5        : YES])
test "$hdf5"        == "no" 						&&  AC_MSG_RESULT([ Hdf5        : NO])
test "$medfile"     != "no" 						&&  AC_MSG_RESULT([ medfile     : YES])
test "$medfile"     == "no" 						&&  AC_MSG_RESULT([ medfile     : NO])
test "$medcoupling" != "no" 						&&  AC_MSG_RESULT([ medcoupling : YES])
test "$medcoupling" == "no" 						&&  AC_MSG_RESULT([ medcoupling : NO])
test $hdf5 	    != no -a $medfile != no -a $medcoupling != no 	&&  AC_MSG_RESULT([ med support : YES])
test $hdf5          == no -o $medfile == no -o $medcoupling == no 	&&  AC_MSG_RESULT([ med support : NO])
test "$salome" 	    != "no"                    				&&  AC_MSG_RESULT([ salome      : YES])
test "$salome"      == "no"                    				&&  AC_MSG_RESULT([ salome      : NO])
test "$FF"          != "no"                    				&&  AC_MSG_RESULT([ PSD Seq     : YES])
test "$FFMPI"       == "no"                     			&&  AC_MSG_RESULT([ PSD Par     : NO])
test "$FFMPI"       != "no"                     			&&  AC_MSG_RESULT([ PSD Par     : YES])
AC_MSG_RESULT([])
