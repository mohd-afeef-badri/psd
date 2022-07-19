

# Dependencies 

With PSD we do not intend to recreate the wheel, as such we rely on multiple dependencies. PSD has some essential prerequisites without which PSD will not function. The table below enlists the dependencies, and also provides a link from where the tarball (`.tar.gz`) file can be obtained for these. 



### Version of packaes 

```bash
MFRONT_VERSION=3.4.0

MGIS_VERSION=1.2

PETSC_VERSION=3.16.1

FREEFEM_VERSION=4.10

GMSH_VERSION=4.8.4

MUMPS_VERSION=5.4.1

METIS_VERSION=5.1.0

PARMETIS_VERSION=4.0.3

SLEPC_VERSION=3.16.1

SCALAPACK_VERSION=2.1.0

HPDDM_VERSION=832303ecdffd25c34206e5392fb3cf85960490a2
```



### Where to find the tarballs 



| Package name                                                 | Used for                                  | Version | Link (Linux)                                                 |
| ------------------------------------------------------------ | ----------------------------------------- | ------- | ------------------------------------------------------------ |
| [Gmsh](http://gmsh.info/)                                    | meshing                                   | 4.8.4   | https://gmsh.info/bin/Linux/gmsh-4.8.4-Linux64.tgz           |
| [FreeFEM](https://freefem.org/)                              | finite element kernel                     | 4.10    | https://github.com/FreeFem/FreeFem-sources/archive/refs/tags/v4.10.tar.gz |
| [hpddm](https://github.com/hpddm/hpddm)                      | parallel linear algebra                   | **      | https://github.com/hpddm/hpddm/archive/832303e.tar.gz        |
| [METIS](https://github.com/KarypisLab/METIS)                 | mesh partitioning                         | 5.1.0   | https://bitbucket.org/petsc/pkg-metis/get/v5.1.0-p10.tar.gz  |
| [MFRONT](https://github.com/thelfer/tfel)                    | non-linear law kernel                     | 3.4.0   | https://github.com/thelfer/tfel/archive/refs/tags/TFEL-3.4.0.tar.gz |
| [MGIS](https://github.com/thelfer/MFrontGenericInterfaceSupport) | non-linear law kernel                     | 1.2     | https://github.com/thelfer/MFrontGenericInterfaceSupport/archive/refs/tags/MFrontGenericInterfaceSupport-1.2.tar.gz |
| [MUMPS](http://mumps.enseeiht.fr/)                           | direct linear algebra solver              | 5.4.1   | https://bitbucket.org/petsc/pkg-mumps/get/v5.4.1-p1.tar.gz   |
| [PARMETIS](https://github.com/KarypisLab/ParMETIS)           | parallel mesh partitioning                | 4.0.3   | https://bitbucket.org/petsc/pkg-parmetis/get/v4.0.3-p6.tar.gz |
| [PETSc](https://petsc.org)                                   | preconditioning and linear system solving | 3.16.1  | https://gitlab.com/petsc/petsc/-/archive/v3.16.1/petsc-v3.16.1.tar.gz |
| [SCALAPACK](http://www.netlib.org/scalapack/)                | linear algebra routines                   | 2.1.0   | https://bitbucket.org/petsc/pkg-scalapack/get/v2.1.0-p2.tar.gz |
| [SLEPc](https://slepc.upv.es/)                               | parallel eigenvalue solver                | 3.16.1  | https://gitlab.com/slepc/slepc/-/archive/v3.16.1/slepc-v3.16.1.tar.gz |
|                                                              |                                           |         |                                                              |

** For `hpddm` a specific git hash `832303ecdffd25c34206e5392fb3cf85960490a2` is used.

### How to get packages 

```bash
GMSH_DOWNLOAD    = wget -c https://gmsh.info/bin/Linux/gmsh-$(GMSH_VERSION)-Linux64.tgz \
                       -O gmsh-$(GMSH_VERSION).tar.gz
                       
                       
MFRONT_DOWNLOAD  = wget -c https://github.com/thelfer/tfel/archive/refs/tags/TFEL-$(MFRONT_VERSION).tar.gz \
                       -O mfront-$(MFRONT_VERSION).tar.gz
                       
                       
MGIS_DOWNLOAD    = wget -c https://github.com/thelfer/MFrontGenericInterfaceSupport/archive/refs/tags/MFrontGenericInterfaceSupport-$(MGIS_VERSION).tar.gz \
                       -O mgis-$(MGIS_VERSION).tar.gz
                       
                       
PETSC_DOWNLOAD   = wget -c https://gitlab.com/petsc/petsc/-/archive/v$(PETSC_VERSION)/petsc-v$(PETSC_VERSION).tar.gz \
                       -O petsc-$(PETSC_VERSION).tar.gz
                       
                       
FREEFEM_DOWNLOAD = wget -c https://github.com/FreeFem/FreeFem-sources/archive/refs/tags/v$(FREEFEM_VERSION).tar.gz \
                       -O freefem-$(FREEFEM_VERSION).tar.gz
                       
                       
MUMPS_DOWNLOAD   =  wget -c https://bitbucket.org/petsc/pkg-mumps/get/v$(MUMPS_VERSION)-p1.tar.gz \
                       -O mumps-$(MUMPS_VERSION).tar.gz 
                       
                       
METIS_DOWNLOAD   =  wget -c https://bitbucket.org/petsc/pkg-metis/get/v$(METIS_VERSION)-p10.tar.gz \
                       -O metis-$(METIS_VERSION).tar.gz
                       
                       
SLEPC_DOWNLOAD   =  wget -c https://gitlab.com/slepc/slepc/-/archive/v$(SLEPC_VERSION)/slepc-v$(SLEPC_VERSION).tar.gz \
                       -O slepc-$(SLEPC_VERSION).tar.gz
                       
                       
HPDDM_DOWNLOAD   =  wget -c https://github.com/hpddm/hpddm/archive/$(HPDDM_VERSION).tar.gz \
                       -O hpddm-$(HPDDM_VERSION).tar.gz
                       
                       
PARMETIS_DOWNLOAD   =  wget -c https://bitbucket.org/petsc/pkg-parmetis/get/v$(PARMETIS_VERSION)-p6.tar.gz \
                       -O parmetis-$(PARMETIS_VERSION).tar.gz
                       
                       
SCALAPACK_DOWNLOAD  =  wget -c https://bitbucket.org/petsc/pkg-scalapack/get/v$(SCALAPACK_VERSION)-p2.tar.gz \
                       -O scalapack-$(SCALAPACK_VERSION).tar.gz
```

