---
title: Linear Elasticity Tutorial 2
geometry: margin=2cm
author: Mohd Afeef Badri
header-includes: |
    \usepackage{tikz,pgfplots}
    \usepackage{listings}
    \usepackage{textcomp}
    \usepackage{fancyhdr}
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


To showcase the usage of Linear elasticity, we shall discuss here an example of a 2D bar, which bends under its own load. The bar $5\times1$ m$^2$ in area is made up of material with $\rho=8\times 10^3$, $E=200\times 10^9$, and $\nu=0.3$. Contrary to tutorial 1, now both ends of the bar are clamped.

\subsection{Step 1: Preprocessing}

First step in a PSD simulation is PSD preprocessing , at this step you tell PSD what kind of physics, boundary conditions, approximations, mesh, etc are you expecting to solve.

In the terminal \psd{cd} to the folder \psd{/home/PSD-tutorials/linear-elasticity}. Launch \psd{PSD\_PreProcess} from the terminal, to do so run the following command.

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -problem linear_elasticity -dimension 2 -bodyforceconditions 1 \
-dirichletconditions 2 -postprocess u
\end{lstlisting}

After the \psd{PSD\_PreProcess} runs successfully you should see many \psd{.edp} files in your current folder.

\textbf{What do the arguments mean ?}

\begin{itemize}
\item \psd{-problem linear\_elasticity} means that we are solving linear elasticity problem;
\item \psd{-dimension 2} means it is a 2D simulation;
\item \psd{-bodyforceconditions 1} with applied body force acting on the domain;
\item \psd{-dirichletconditions 2} says we have two Dirichlet border;
\item \psd{-postprocess u} means we would like to have ParaView post processing files.

\end{itemize}

Since basic nature of both the problems (the one from tutorial 1 and 2) is same the almost the same command for preprocessing used in previous tutorial 1 is used here. The only difference,is that an additional Dirichlet condition needs to be supplied, notified to PSD by \psd{ -dirichletconditions 2}. To provide Dirichlet conditions of the left clamped end ($u_x=u_y=0$) in \psd{ControlParameters.edp} set \psd{Dbc0On 2}, \psd{Dbc0Ux 0.}, and \psd{Dbc0Uy 0.}. Similarly, for the right end set variables \psd{Dbc1On 4}, \psd{Dbc1Ux 0.}, and \psd{Dbc1Uy 0}. Each one of these is a clamped border respectively labeled as 2 (\psd{Dbc0On 2}) and 4 (\psd{Dbc1On 4}) in the mesh \psd{../Meshes/2D/bar.msh}.

Just like the previous tutorial the input properties $E,\nu$ should be mentioned in \psd{ControlParameters.edp}, use \psd{E = 200.e9}, and \psd{nu = 0.3;}. The volumetric body force condition is mentioned in the same file via variable \psd{Fbc0Fy -78480.0}, i.e ($\rho*g=8.e3*(-9.81)=-78480.0$). One can also provide the mesh to be used in \psd{ControlParameters.edp} , via \psd{ThName = "../Meshes/2D/bar.msh"} (\textit{note that mesh can also be provided in the next step}) .In addition variable \psd{Fbc0On 1} has to be provided in order to indicate the volume (region) for which the body force is acting, here \psd{1} is the integer volume tag of the mesh.

\subsection{Step 2: Solving}

As PSD is a parallel solver, let us use 3 parallel processes to solve this 2D bar case. To do so enter the following command:

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve -np 3 Main.edp -mesh ./../Meshes/2D/bar.msh -v 0
\end{lstlisting}

Here \psd{-np 3} denote the argument used to enter the number of parallel processes (MPI processes) used while solving. \psd{-mesh ./../Meshes/2D/bar.msh} is used to provide the mesh file to the solver. \psd{-v 0} denotes the verbosity level on screen.\psd{PSD\_Solve} is a wrapper around \psd{FreeFem++} or \psd{FreeFem++-mpi}. Note that if your problem is large use more cores. PSD has been tested upto 13,000 parallel processes and problem sizes with billions of unknowns, surely you will now need that many for the 2D bar problem.



\subsection{Step 3: Postprocessing}

PSD allows postprocessing of results in ParaView. After the step 2 mentioned above finishes. Launch ParaView and have a look at the \psd{.pvd} file in the \psd{VTUs\_DATE\_TIME} folder. Using ParaView for postprocessing the results that are provided in the \psd{VTUs...} folder, results such as those shown in figure~\ref{bar-le-full-n} can be extracted.


\begin{figure}[h!]
\centering
\includegraphics[width=0.4\textwidth]{./Images/le-2d-bar-partitioned3.png}\\
\includegraphics[width=0.4\textwidth]{./Images/le-2d-bar-clamped-ends.png}
\caption{The 2D clamped bar problem: partitioned mesh and displacement field visualization in ParaView. \label{bar-le-full-n}}
\end{figure}


You are all done with your 2D linear-elasticity simulation.



\subsection{What else should you try to become an advanced user}

Try running the 3D problem. Keep in mind to rerun the \psd{PSD\_PreProcess} with \psd{-dimension 3} flag and using the appropriate mesh via \psd{-mesh} flag with \psd{PSD\_Solve}. It goes without saying you will need to adjust the Dirichlet border labels in \psd{ControlParameters.edp}.

Since gravity is the main force involved in the problem, try redoing the test with different gravitational constant. Imagine, you wish to know how the test would compare if performed on Moon and Jupiter. The only thing that will change now is the gravitational pull, for Moon $g=1.32$ and for Jupiter $g=24.79$. To perform the moon test simply change \psd{Fbc0Fy -10560.0} in \psd{ControlParameters.edp} and redo step 2 and step 3. Similarly, for the Jupiter test \psd{Fbc0Fy -198320.0} in \psd{ControlParameters.edp} and redo step 2 and step 3.

Optionally try using \psd{-withmaterialtensor} flag with \psd{PSD\_PreProcess} , and run the simulation. You are encouraged to have a look at \psd{ControlParameters.edp} and \psd{VariationalFormulations.edp} file produced with \psd{-withmaterialtensor} flag and without this flag.

Add \psd{-sequential} flag to \psd{PSD\_PreProcess} for sequential solver, but remember to use \psd{PSD\_Solve\_Seq} instead of \psd{PSD\_Solve} and no \psd{-np} flag.

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -problem linear_elasticity -dimension 2 -sequential \
-bodyforceconditions 1 -dirichletconditions 2 -postprocess u
\end{lstlisting}

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve_Seq Main.edp -mesh ./../Meshes/2D/bar.msh -v 0
\end{lstlisting}

\subsection{Advance exercise  1}

There is a solver run level flag for mesh refinement \footnote{Mesh refinement is performed after partitioning.}. This flag is called \psd{-split [int]} which splits the triangles (resp. tetrahedrons) of your mesh into  four smaller  triangles (resp. tetrahedrons). As such \psd{-split 2} will produce a mesh with 4 times the elements of the input mesh. Similarly, \psd{-split n} where $n$ is a positive integer produces $2^n$ times more elements than the input mesh. You are encouraged to use this \psd{-split} flag to produce refined meshes and check, mesh convergence of a problem, computational time, etc. Use of parallel computing is recommended. You could try it out with \psd{PSD\_Solve} or \psd{PSD\_Solve\_Seq}, for example:

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve -np 4 Main.edp -mesh ./../Meshes/3D/bar.msh -v 0 -split 2
\end{lstlisting}

for splitting each triangle of the mesh  \psd{bar.msh} into 4.

\subsection{Advance exercise  2}

There is a preprocess level flag \psd{-debug}, which as the name suggests should be used for debug proposes by developers. However, this flag will activate OpenGL live visualization of the problems displacement field. You are encouraged to try it out

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -problem linear_elasticity -dimension 3 -bodyforceconditions 1 \
-dirichletconditions 2 -postprocess u -timelog -debug
\end{lstlisting}

Then to run the problem we need aditional \psd{-wg} flag

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve -np 4 Main.edp -mesh ./../Meshes/3D/bar.msh -v 0 -wg
\end{lstlisting}

\subsection{Advance exercise 3}

There is a preprocess level flag \psd{-withmaterialtensor}, which introduces the full material tensor into the finite element variational formulation. You are encouraged to use this flag and see how the sollver performs.

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -problem linear_elasticity -dimension 3 -bodyforceconditions 1 \
-dirichletconditions 2 -postprocess u -timelog -withmaterialtensor
\end{lstlisting}

Then to run the problem we need aditional \psd{-wg} flag

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve -np 4 Main.edp -mesh ./../Meshes/3D/bar.msh -v 0
\end{lstlisting}

To understand what the flag does, try to find out the difference between the files created by \psd{PSD\_PreProcess} when used with and without  \psd{-withmaterialtensor} flag. Especially, compare  \psd{FemParameters.edp}, \psd{MeshAndFeSpace} and \psd{VariationalFormulations.edp} files produced by \psd{PSD\_PreProcess} step.

\subsection{Advance exercise  4}

You are encouraged to use more complex meshes for this same problem, but do not forget to update the \psd{ControlParameters.edp} file, with your desired boundary conditions.
