---
title: Poisson Tutorial 1 PSD simulation of nontrivial manufactured tests
geometry: margin=2cm
author: Mohd Afeef Badri
header-includes: |
    \usepackage{tikz,pgfplots}
    \usepackage{listings}
    \usepackage{textcomp}
    \usepackage{fancyhdr}
    \usepackage{graphbox}
    \usepackage{cleveref}
    \usepackage{subcaption}
    \pagestyle{fancy}
    \lstdefinestyle{BashInputStyle}{
	language=bash,
	basicstyle=\small\sffamily,
	numbers=left,
	numberstyle=\tiny,
	numbersep=3pt,
	frame=tb,
	columns=fullflexible,
	backgroundcolor=\color{yellow!20},
	linewidth=1.\linewidth,
	xleftmargin=0.05\linewidth,
	literate =
	{"}{{\uprightquote}}1
	{'}{{\textquotesingle}}1
	{-}{{-}}1
	{~}{{\centeredtilde}}1
	,
    }
abstract: This document details a single tutorials of 'linear elasticity' module of PSD in a more verbos manner.
---

\newcommand{\psd}[1]{{\small\sffamily{\color{blue!60}#1}}}
PSD_Solve -np 4 Main.edp -mesh ./../Meshes/3D/cube.msh -v 0
Poisson problem is a boundary value problem in FEM which is often used to demonstrate the solvers correctness or used to develop many fundamental tools that are later used for other complex problems. Poisson's problem itself can be used to approximate certain physcial phenomena such as, heat trasfer, electrostatics, basic aerodynamics, etc.

The Poisson equation is a PDE which is defined by the following boundary-value problem,

$$\Delta u (x) = -f(x) \quad \forall x \in \Omega, $$

$$u (x) = u_{\text{D}}(x) \quad \forall x \in \partial\Omega, $$

here,  $u(x)$ is the unknown variable, $f(x)$ is  a known function also known as source term, $\Delta$ is the Laplace operator, $\Omega$ is  the spatial domain in space $x$ and is bounded by boundary $\partial \Omega$. The Poisson problem here, includes known value $u_{\text{D}}$ on its border $\partial \Omega$.

The starting point for FEM approximation for a   PDE is its *variational form*. The variational formulation for Poission's problem reads, find $u \in \mathcal{V}$:


$$\int_\Omega \nabla u \cdot \nabla v~\mathrm{d} x = \int_\Omega fv~\mathrm{d} x \quad \quad \forall v \in \hat{\mathcal{V}}.$$

For this formulation, the trial function $u$ and test function $v$ are defined in functional spaces

$$\mathcal{V}=\{v\in H^1(\Omega)|v=u_{\text{D}} \quad \text{on} \quad \partial\Omega \},$$

$$\hat{\mathcal{V}}=\{v\in H^1(\Omega)|v=0 \quad \text{on} \quad \partial\Omega \}.$$

Here, $H^1(\Omega)$ is the  Sobolev space containing functions $v$ such that these are square integrable with continuous derivatives over $\Omega$. Note that, the Sobolev space allows functions with discontinuous derivatives. This weaker continuity requirement in our weak formulation (caused by the integration by parts) is of great importance when it comes to constructing the finite element function space. In particular, it allows the use of piecewise polynomial function spaces. This means that the function spaces are constructed by stitching together polynomial functions on simple domains such as intervals, triangles, quadrilaterals, tetrahedra and hexahedra. In principal these simpler domains are  obtaining by converting our domain $\Omega$ to its meshed form $\Omega^h$, such that $h$ defines the size of the mesh.

The variational problem is a *continuous problem*: it defines the solution  in the infinite-dimensional function space . The finite element method for the Poisson equation finds an approximate  solution $u^h$ of the variational problem by replacing the  infinite-dimensional function spaces $\mathcal{V}$  and  by *discrete* (finite dimensional) trial  and test spaces  $\mathcal{V}^h$ and $\hat{\mathcal{V}}^h$ . The discrete variational problem reads: Find  find $u^h \in \mathcal{V}^h$ such that


$$\int_\Omega^h \nabla u^h \cdot \nabla v^h~\mathrm{d} x = \int_\Omega^h fv^h~\mathrm{d} x \quad \quad \forall v^h \in \hat{\mathcal{V}^h}.$$

\subsection{2D example}
To showcase the usage of poisson, we solve for the following manufactured solution on a 2D square unit mesh:
$$u = \tanh(-100(y - 0.5 -0.25\sin(2\pi x))) + \tanh(100(y - x))$$
It will define the dirichlet condition on all borders which leaves our source term:
$$f = 100 \pi^2 \sin(2 \pi x) \left(\tanh^2\left(-100\left(y - 0.5 - 0.25 \sin(2 \pi x)\right)\right) - 1 \right) - 5000 \pi^2 \cos^2(2 \pi x)$$
$$\left(1 - \tanh^2\left(-100\left(y - 0.5 - 0.25 \sin(2 \pi x)\right)\right) \right) \tanh\left(-100\left(y - 0.6 - 0.25 \sin(2 \pi x)\right)\right)$$
$$+ 20000 \left(\tanh^2\left(-100\left(y - 0.5 - 0.25 \sin(2 \pi x)\right)\right) - 1 \right) \tanh\left(-100\left(y - 0.5 - 0.25 \sin(2 \pi x)\right)\right)$$
$$+ 20000 \left(\tanh^2\left(100\left(y - x\right)\right) - 1 \right) \tanh\left(100\left(y - x\right)\right)$$
$$- 20000 \left(1 - \tanh^2\left(100\left(y - x\right)\right) \right) \tanh\left(100\left(y - x\right)\right)$$

To get the PSD simulation, we start by PSD pre-processing to specify the tools and methods to use and the desired type of output.
For instance, the following command communicates to \psd{PSD\_PreProcess} that the problem is a poisson problem in two dimensions and that we want to post-proccess the solution u.  

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -dimension 2 -problem poisson -postprocess u -sequential
\end{lstlisting}

This will produce a set of \psd{.edp} files with Main.edp to be run by \psd{PSD\_Solve\_Seq} for sequential solving. Further editing can be done on the produced files to adjust to a problem, mainly on \psd{ControlParameters} where all the problem specific parameters are written. For this example, the default provided ones are suitable. This example will be done on the mesh \psd{./../Meshes/2D/square.msh}. Other arguments can be passed to the PSD solver such as the verbosity which is set to 0 in the following command:

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve_Seq Main.edp -mesh ./../Meshes/2D/square.msh -v 0
\end{lstlisting}

To vizualise the solution, we launch \psd{paraview} and open the file \psd{solution0.vtu}. The result that we see is not the expected solution as the mesh is too coarse to capture the variations in the function. Instead of using a finer uniform mesh, we perform mesh adaption. In order to do that, we add the flag \psd{-adaptmesh} and specify some more parameters. 
Parameters such as the number of iterations, the minimum and maximum element sizes can be edited in \psd{ControlParameters.edp}. We first launch with freefem for metric calculation and adaption. 

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -dimension 2 -problem poisson -adaptmesh -adaptmesh-metric-backend freefem \
-adaptmesh-metric freefem -postprocess u -sequential
PSD_Solve_Seq Main.edp -mesh ./../Meshes/2D/square.msh -v 0
\end{lstlisting}

In order to visualize the solution, we open the group of solution files and view the results of adaption iterations one by one. We start getting a satisfactory approximated solution by the NUMBER OF ITERATION iteration.

We can also run with different backends. Each have their respective parameters documented on \psd{ControlParameters.edp}. These are the valid configurations:
\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -dimension 2 -problem poisson -adaptmesh -adaptmesh-metric-backend freefem \
-adaptmesh-metric freefem -postprocess u -sequential
PSD_PreProcess -dimension 2 -problem poisson -adaptmesh -adaptmesh-metric-backend freefem \
-adaptmesh-metric mmg -postprocess u -sequential
PSD_PreProcess -dimension 2 -problem poisson -adaptmesh -adaptmesh-metric-backend mshmet \
-adaptmesh-metric mmg -postprocess u -sequential
\end{lstlisting}

We can also reach a good approximation of the solution by enabling anisotropy through the \psd{-adaptmesh\_type} flag.
\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -dimension 2 -problem poisson -adaptmesh -adaptmesh-metric-backend mshmet \
-adaptmesh-metric mmg -adaptmesh_type anisotropic -postprocess u -sequential
\end{lstlisting}

\subsection{3D example}
We solve the same problem but on a 3D cube keeping the solution constant across the z axis. Adaption in 3D is done using mshmet for metric calculation and mmg for mesh adaption. In \psd{ControlParameters.edp}, set the number of adaption iterations to 5 (\psd{adaptIter}). 

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -dimension 3 -problem poisson -adaptmesh -adaptmesh_metric_backend mshmet \
-adaptmesh_backend mmg -postprocess u -sequential
PSD_Solve_Seq Main.edp -mesh ./../Meshes/3D/cube.msh -v 0
\end{lstlisting}

Notice how the solving takes a lot of time in this example; it is generally the case when we move to 3D as we have an additional axis and more elements on the initial mesh. This is why we prefer to parallelize the process. We omit the -sequential flag to enable mpi and change the adaption backend to parmmg. We specify the number of procs to \psd{PSD\_Solve} using the flag \psd{-np}. Parallel solving can also be done in 2D but is generally not necessary while parallel adaption (\psd{parmmg}) is only available in 3D.

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -dimension 3 -problem poisson -adaptmesh -adaptmesh_metric_backend mshmet \
-adaptmesh_backend parmmg -postprocess u
PSD_Solve -np 4 Main.edp -mesh ./../Meshes/3D/cube.msh -v 0
\end{lstlisting}

For larger meshes, it can be beneficial to group processes (only for the adaption step) on a bigger partition of the mesh. It is not the case in this example.
The number of groups can either be fixed across iterations and unrelated to the mesh (it can be changed in \psd{ControlParameters.edp}), or adaptive to the number of elements across iterations; these are the respective commands of the two methods.

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -dimension 3 -problem poisson -adaptmesh -adaptmesh_metric_backend mshmet \
-adaptmesh_backend parmmg --adaptmesh_parmmg_method partition_regrouping -postprocess u
PSD_Solve -np 4 Main.edp -mesh ./../Meshes/3D/cube.msh -v 0
\end{lstlisting}

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -dimension 3 -problem poisson -adaptmesh -adaptmesh_metric_backend mshmet \
-adaptmesh_backend parmmg --adaptmesh_parmmg_method partition_automatic_regrouping -postprocess u
PSD_Solve -np 4 Main.edp -mesh ./../Meshes/3D/cube.msh -v 0
\end{lstlisting}
