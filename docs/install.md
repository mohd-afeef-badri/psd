**PSD Platform Support and Installation Guide**

**PSD** is a cross-platform finite element method (FEM) solver primarily designed for Unix/Linux environments. It has been successfully deployed on the following systems:

* **CentOS**: 7 / 8
* **Ubuntu**: 16.04 / 18.04 / 20.04 / 22.04 / 24.04
* **Debian**: 11
* **Raspberry Pi OS**
* **Fedora**: 30 / 32 / 34 / 36 / 38
* **macOS**:
  * Intel: Puma 10.1.5
  * ARM (M2): Ventura 13

---

**Prerequisites**

Before installing PSD, ensure the following dependencies are installed and compatible on your system.

| Package                                                   | Required Version                                                                   | Essential | Install Assist |
| --------------------------------------------------------- | ---------------------------------------------------------------------------------- | --------- | -------------- |
| [automake](https://www.gnu.org/software/automake/)           | 2.8 or higher                                                                      | ✅        | ❌             |
| [C/C++ compiler](http://www.cplusplus.com/)                  | GCC 7 or higher                                                                    | ✅        | ❌             |
| [MPI](https://www.mpich.org/)                                | 2.0 or higher ([MPICH](https://www.mpich.org/) or [Open MPI](https://www.open-mpi.org/)) | ✅        | ❌             |
| [git](https://git-scm.com/)                                  | –                                                                                 | ✅        | ❌             |
| [FreeFEM](https://freefem.org/)                              | 4.15                                                                               | ✅        | ✅             |
| [PETSc](https://www.mcs.anl.gov/petsc/)                      | 3.22.2                                                                             | ✅        | ✅             |
| [Gmsh](http://gmsh.info/)                                    | 4.11.1                                                                             | ✅        | ✅             |
| [SALOME](https://www.salome-platform.org/)                   | 9.0 or higher                                                                      | ❌        | ❌             |
| [gnuplot](http://www.gnuplot.info/)                          | 4.0 or higher                                                                      | ❌        | ❌             |
| [MFront](http://tfel.sourceforge.net/)                       | 5.0.0                                                                              | ❌        | ✅             |
| [MGIS](https://thelfer.github.io/mgis/web/bindings-cxx.html) | 3.0                                                                                | ❌        | ✅             |

> ⚠️ **Note:**
> Some dependencies can be automatically installed with PSD. These are marked in the “Install Assist” column above. Others must be installed manually before proceeding.

> ⚙️ **Important:**
> `FreeFEM` and `PETSc` must be compiled with support for **METIS**, **ParMETIS**, and **HPDDM**. These are considered additional critical dependencies when compiling from source.

---

## Installation Procedure 1

**PSD installs all the dependencies**  *Recommended* ✅

* Ensure the following are pre-installed:
  `automake`, a C/C++ compiler, `git`, `MPI`, `lapack`, and others. For ubuntu following is suggested :
  <pre><code>
  sudo apt-get install libgsl-dev libhdf5-dev \
        liblapack-dev libopenmpi-dev freeglut3-dev \
        cpp g++ gcc gfortran bison flex gdb git \
        m4 make patch pkg-config wget python3 unzip \
        autoconf automake autotools-dev cmake libtirpc-dev
  </code></pre>
* System must have **active Internet access** to fetch and build dependencies.

- Obtain the latest version of PSD by cloning the git repository:

<pre><code>
git clone https://github.com/mohd-afeef-badri/psd.git PSD-Sources
</code></pre>

- Use automake within the  cloned PSD folder (`PSD-Sources`)

<pre><code>
autoreconf -i
</code></pre>

- Configure  PSD within the  cloned folder, we will install PSD in `$HOME/PSDinstall`

<pre><code>
./configure --prefix=$HOME/PSDinstall --with-dependencies=yes
</code></pre>

> 💡 **Note**:   `--with-dependencies=yes` uses `wget` and internet, so make sure you are connected. To bypass the internet limitation, for instance on clusters or supercomputers, users can provide the tarball files `*.tar.gz` files of the dependencies within the `/ext` folder and use the flag `--with-zipped_dependencies`.

- Build PSD directives and install PSD

<pre><code>
make
make install
</code></pre>

- Perform a check to see if everything works

<pre><code>
make check
</code></pre>

- Install PSD tutorials

<pre><code>
make tutorials
</code></pre>

Now you should have the PSD solver installed on your machine.

> 💡 **Note**: that, the solver will be installed at `$HOME/PSDInstall`.  The PSD tutorials are installed in `$HOME/PSD-tutorials`.

- Update environment variables permanently:

<pre><code>
echo 'export PATH=$HOME/PSDinstall/bin:$PATH' >> ~/.bashrc
echo 'export LD_LIBRARY_PATH=$HOME/PSDinstall/lib:$LD_LIBRARY_PATH' >> ~/.bashrc
</code></pre>

> 💡 **Note**: for temporary approach, run `source $PREFIXPSD/mfront-env.sh` before using PSD.

**MED support:**

Follow this to build PSD with `med` support, use

- provide SALOME's hdf5 `--with-hdf5=$SALOMEPREFIX/hdf5`
- provide SALOME's medfile `--with-medfile=$SALOMEPREFIX/medfile`
- provide SALOME's MedCoupling `--with-medcoupling=$SALOMEPREFIX/MEDCOUPLING`
  All these flags can be set by downloading SALOME and providing the SALOME's install path directory in `SALOMEPREFIX`.

## Installation Procedure 2

**I install my own dependencies for PSD**

- Obtain the latest version of PSD by cloning the git repository:

<pre><code>
git clone https://github.com/mohd-afeef-badri/psd.git PSD-Sources
</code></pre>

- Set up PSD:

<pre><code>
autoreconf -i
</code></pre>

- Configure  PSD within the  cloned folder

<pre><code>
./configure
</code></pre>

> 💡 **Note**:   `./configure` will install PSD in `/usr/local/bin`  and you would need `sudo` rights (superuser) to perform installation, for non `sudo` users or for local install consider changing directory of installation. To change this directory use `--prefix=Your/Own/Path` with `./configure`.

> 💡 **Note**: if FreeFEM, MGIS, MFront, and Gmsh are installed in directories other than the default `PATH`, specify their locations during `./configure` using flags like `--with-FreeFEM=`, `--with-Gmsh=`, etc., use `./configure -h` to know more about these flags or see the "Configuration flags" section.

- Build PSD directives:

<pre><code>
make
</code></pre>

- Install PSD:

<pre><code>
sudo make install
</code></pre>

> 💡 **Note**:  You should not use `sudo` if you have used `--prefix` during the `./configure` phase.

- Install PSD tutorials

<pre><code>
make tutorials
</code></pre>

Now you should have the PSD solver installed on your machine. Note that, the solver will be installed at `usr/bin` or ` usr/local/bin` directories if you used `sudo make install` or else it will be in your ` --prefix` location.  The PSD tutorials are installed in `$HOME/PSD-tutorials`.

## Installation procedure on MacOS

**MacOS with Apple Silicon**

- Install dependencies via Homebrew. In this example we are using `gcc-15` and `g++-15`
  <pre><code>
  brew install m4 git bison hdf5 wget autoconf automake gcc gmsh scotch scalapack openblas
  export HOMEBREW_CC=gcc-15
  export HOMEBREW_CXX=g++-15
  brew install open-mpi  --build-from-source
  </code></pre>

> 💡 **Note**:  You should not check that your `mpicc` uses `GNU 15`. Check via `mpicc --version`
> 💡 **Note**:  System must have **active Internet access** to fetch and build dependencies.

- Obtain the latest version of PSD by cloning the git repository:

<pre><code>
git clone https://github.com/mohd-afeef-badri/psd.git PSD-Sources
</code></pre>

- Use automake within the  cloned PSD folder (`PSD-Sources`)

<pre><code>
autoreconf -i
</code></pre>

- Configure  PSD within the  cloned folder, we will install PSD in `$HOME/PSDinstall`

<pre><code>
./configure --prefix=$HOME/PSDinstall --with-dependencies=yes
</code></pre>

> 💡 **Note**:   `--with-dependencies=yes` uses `wget` and internet, so make sure you are connected. To bypass the internet limitation, for instance on clusters or supercomputers, users can provide the tarball files `*.tar.gz` files of the dependencies within the `/ext` folder and use the flag `--with-zipped_dependencies`.
> 💡 **Note**:   since `Gmsh` is among the dependencies for MacOS assure that configure finds the `gmsh` that was installed via `Homebrew` if not use `--with-Gmsh=` to provide the correct path.

- Build PSD directives and install PSD

<pre><code>
make
make install
</code></pre>

> 💡 **Note**: `sudo make install` is called for installing `FreeFEM` if one uses `--with-dependencies=yes`, so keep an eye as you might need to enter your password.

- Perform a check to see if everything works

<pre><code>
make check
</code></pre>

- Install PSD tutorials

<pre><code>
make tutorials
</code></pre>

Now you should have the PSD solver installed on your machine.

## Docker Image for PSD

To simplify installation and ensure a consistent runtime environment across platforms, a Docker image for PSD is available. This image can be used on Linux and macOS systems with Docker installed.

**Pulling the Docker Image**

Download the latest PSD Docker image from Docker Hub:

<pre><code>
docker pull mohdafeef/psd:latest
</code></pre>

**Running the PSD Docker Container**

<pre><code>
docker run -it mohdafeef/psd:latest
</code></pre>

PSD is pre-installed and available in `/opt/psd/bin` and is avaliable in `PATH`.

- PSD tutorials can be generated inside the container by running:

<pre><code>
make tutorials
</code></pre>

The tutorials will be installed in `/root/PSD-tutorials`

#### Configuration flags

These are a set of commandline flags/options that control your PSD configuration via the automake ligo.

| **Flag**                 | **Description**                                                                                                                                                                                                                                                                                                                                                                                                          | **Examples**                                                                                                                             |
| ------------------------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ | ---------------------------------------------------------------------------------------------------------------------------------------------- |
| `--prefix`                   | Enter the directory where you wish to install PSD.<br />Note that  you  will  need to  have read and write <br />permission for this directory.<br /><br />*This flag is an optional flag*                                                                                                                                                                                                                                   | `--prefix=/usr` <br /> `--prefix=/usr/local` <br /> `--prefix=/home/install`                                                             |
| `--with-FreeFEM`             | Enter the directory where FreeFem binary has been installed.<br />Tip, in your terminal  `which FreeFem++`  can  help you <br />find this directory.<br /><br />*This flag is an optional flag*                                                                                                                                                                                                                            | `--with-FreeFEM=/usr/bin` <br />`--with-FreeFEM=/home/install/bin` <br />`--with-FreeFEM=/usr/local/bin`                                 |
| `--with-Gmsh`                | Enter the directory  where  Gmsh  binary has been installed.<br />Tip, in your terminal `which gmsh`  can help you find this<br />directory.<br /><br />*This flag is an optional flag*                                                                                                                                                                                                                                    | `--with-Gmsh=/usr/bin` <br />`--with-Gmsh=/home/install/bin` <br />`--with-Gmsh=/usr/local/bin`                                          |
| `--with-mgis`                | Enter the directory  where  Mgis  has been installed.<br /><br />*This flag is an optional flag*                                                                                                                                                                                                                                                                                                                             | `--with-mgis=/usr` <br />`--with-mgis=/home/install` <br />`--with-mgis=/usr/local`                                                      |
| `--with-salome`              | Enter the directory  where  SALOME  has been installed.<br /><br />*This flag is an optional flag*                                                                                                                                                                                                                                                                                                                           | `--with-salome=/home/SALOME-UB22.04` <br />`--with-salome=/home/install/SALOME-UB22.04` <br />`--with-salome=/usr/local/SALOME-UB22.04`  |
| `--with-hdf5`                | Enter the directory  where  hdf5  has been installed.<br /><br />*This flag is an optional flag*                                                                                                                                                                                                                                                                                                                             | `--with-hdf5=/home/SALOME-UB22.04/INSTALL/hdf5` <br />`--with-hdf5=/home/install/SALOME/BINARIES-UB22.04/hdf5`                             |
| `--with-medfile`             | Enter the directory  where  medfile  has been installed.<br /><br />*This flag is an optional flag*                                                                                                                                                                                                                                                                                                                          | `--with-medfile=/home/SALOME-UB22.04/INSTALL/medfile` <br />`--with-medfile=/home/install/SALOME/BINARIES-UB22.04/medfile`                 |
| `--with-medcoupling`         | Enter the directory  where  MEDCOUPLING  has been installed.<br /><br />*This flag is an optional flag*                                                                                                                                                                                                                                                                                                                      | `--with-medcoupling=/home/SALOME-UB22.04/INSTALL/MEDCOUPLING` <br />`--with-medcoupling=/home/install/SALOME/BINARIES-UB22.04/MEDCOUPLING` |
| `--with-mfront`              | Enter the directory  where  Mfront binary  has been installed.<br /><br />*This flag is an optional flag*                                                                                                                                                                                                                                                                                                                    | `--with-mfront=/usr/bin` <br />`--with-mfront=/home/install/bin` <br />`--with-mfront=/usr/local/bin`                                    |
| `--with-dependencies`        | Enter yes or no as an option to this flag, default is no. If yes<br />is entered to this command, PSD will build and compile its<br />dependencies for you. If yes PSD will compile PETSc, FreeFEM,<br />Mgis, MFront, Metis, ParMetis, Scalapack, mumps, hpddm,<br />slepc, suitsspars, tetgen.<br /><br />*This flag is an optional flag*                                                                                  | `--with-dependencies=yes` <br />`--with-dependencies=no`                                                                                   |
| `--with-zipped_dependencies` | Enter yes or no as an option to this flag, default is no. If yes<br />is entered to this command, PSD will look for `.tar.gz` files for <br />dependencies in `ext` folder and compile them<br />for you. If yes PSD will expect `.tar.gz` for PETSc, FreeFEM,<br />Mgis, MFront, Metis, ParMetis, Scalapack, mumps, hpddm,<br />slepc, suitsspars, tetgen from ext folder.<br /><br />*This flag is an optional flag* | `--with-zipped_dependencies=yes` <br />`--with-zipped_dependencies=no`                                                                     |

#### make options for PSD

Once `./configure` runs successfully your Makefiles will be generated thanks to automake. Different options are available with `make` command some are native to Make (still listed here, sorry to my Linux co-geeks)


| **Command**    | **Description**                                                                                                                                                                                                                                                                                                              | **Example**                            |
| -------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | -------------------------------------------- |
| `make`             | Command responsible to compile PSD for you. This is necessary.                                                                                                                                                                                                                                                                     | `make`                                     |
| `-j4`              | Activates parallel make, i.e., faster compilation on 4 cores.<br /><br />*This flag is an optional flag*                                                                                                                                                                                                                         | `make -j4`                                 |
| `install`          | Command that installs PSD for you, this command should follow the `make` command.                                                                                                                                                                                                                                                | `make install` <br /> `make install -j4` |
| `check`            | Command that should follow `make install` helps to check the PSD installation.<br /><br />*This command is an optional but recommended*                                                                                                                                                                                        | `make check`                               |
| `clean`            | Command that cleans PSD's compilation directory.<br /><br />*This command is an optional*                                                                                                                                                                                                                                        | `make clean`                               |
| `maintainer-clean` | Command that cleans PSD's compilation directory throughly.<br /><br />*This command is an optional*                                                                                                                                                                                                                              | `make maintainer-clean`                    |
| `tutorials`        | Command that builds PSD tutorials in `$HOME` directory. This should <br />follow/be-used only after  `make install`.<br /><br />*This command is an optional*                                                                                                                                                                | `make tutorials`                           |
| `install-devl`     | Command that installs developers version of PSD for you, this command should follow<br />the `make` command.<br /><br />*This command is an optional*                                                                                                                                                                          | `make install-devel`                       |
| `documentation`    | Command that builds documentation, in html, and pdf formats. This command should follow<br />the `make` command. Note that this needs pandoc installed in your system. And also pandoc support for specific html templates, [Link](https://github.com/ryangrose/easy-pandoc-templates). <br /><br />*This command is an optional* | `make documentation`                       |

*To report bugs, issues, feature-requests contact:*

- **mohd-afeef.badri@cea.fr**
