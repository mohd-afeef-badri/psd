---
title: Elastodynamics Tutorials
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
abstract: This document details some tutorials of elastodynamics module of PSD. These tutorials are not verbose, but does instead give a kick start to users/developers for using PSD's elastodynamics module. 
---

\newcommand{\sh}[1]{\small\sffamily{\color{blue!60}#1}}

\subsection{Parallel 2D}

The problem of interest is a single Dirichlet condition (clamped end bar) and traction loading. For this example we use Newmark-$\beta$ time discretization. Additionally postrocessing is demanded for displacement, acceleration, and velocity ($u,a,v$). 

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -dimension 2 -problem elastodynamics -dirichletconditions 1 -tractionconditions 1 \
-timediscretization newmark_beta -postprocess uav
\end{lstlisting}

Once the step above has been performed, we solve the problem using two MPI processes, with the given mesh file \sh{bar-dynamic.msh}. 

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve -np 2 Main.edp -mesh ./../Meshes/2D/bar-dynamic.msh -v 0
\end{lstlisting}

\begin{figure}[h!]
\includegraphics[width=0.19\textwidth]{./Images/ed-u0.png}
\includegraphics[width=0.19\textwidth]{./Images/ed-u2.png}
\includegraphics[width=0.19\textwidth]{./Images/ed-u3.png}
\includegraphics[width=0.19\textwidth]{./Images/ed-u4.png}
\includegraphics[width=0.19\textwidth]{./Images/ed-u5.png}
\caption{Finite element displacement field on warped mesh shown at different time steps. \label{bar-ed}}
\end{figure}

Using ParaView for postprocessing the results that are provided in the \sh{VTUs...} folder, results such as those shown in figure~\ref{bar-ed} can be extracted. 

\subsection{Parallel 3D}

The problem of interest is a single Dirichlet condition (clamped end bar) and traction loading. For this example we use Newmark-$\beta$ time discretization. Additionally postrocessing is demanded for displacement, acceleration, and velocity ($u,a,v$). 

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -dimension 3 -problem elastodynamics -dirichletconditions 1 -tractionconditions 1 \
-timediscretization newmark_beta
\end{lstlisting}

Once the step above has been performed, we solve the problem using four MPI processes, with the given mesh file \sh{bar-dynamic.msh}. 

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve -np 4 Main.edp -mesh ./../Meshes/3D/bar-dynamic.msh -v 0
\end{lstlisting}


\subsection{Sequential problems}

To the same problems above Add \sh{-sequential} flag to \sh{PSD\_PreProcess} for sequential solver, but remember to use \sh{PSD\_Solve\_Seq} instead of \sh{PSD\_Solve}. So the work flow for the 2D problem would be:

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -dimension 2 -problem elastodynamics -dirichletconditions 1 -tractionconditions 1 \
-timediscretization newmark_beta -postprocess uav -sequential
\end{lstlisting}

Once the step above has been performed, we solve the problem using the given mesh file \sh{bar-dynamic.msh}. 

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve_Seq -np 2 Main.edp -mesh ./../Meshes/2D/bar-dynamic.msh -v 0
\end{lstlisting}

Similarly try out the 3D problem as well.

\subsection{Different time discretization}

PSD offers different time discretization techniques for solving time dependent problems. For this example instead of using Newmark-$\beta$ time  discretization let us switch to more advanced Generalized-$\alpha$ one. This can be done by \sh{-timediscretization generalized\_alpha}, so for example for a 2D problem we use:

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -dimension 2 -problem elastodynamics -dirichletconditions 1 -tractionconditions 1 \
-timediscretization generalized_alpha -postprocess uav
\end{lstlisting}

Once the step above has been performed, we solve the problem using three MPI processes, with the given mesh file \sh{bar-dynamic.msh}. 

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve -np 3 Main.edp -mesh ./../Meshes/2D/bar-dynamic.msh -v 0
\end{lstlisting}

Similarly try out the 3D problem as well.

\subsection{Comparing CPU time}

PSD provides mean to time log your solver via \sh{-timelog} flag. What this will do when you run your solver, on the terminal you will have information printed on what is the amount of time taken by each step of your solver. Warning, this will make your solver slower, as this action involves MPIbarrier routines for correctly timing operation. 

An example work flow of 2D solver with timelogging:

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -dimension 2 -problem elastodynamics -dirichletconditions 1 -tractionconditions 1 \
-timediscretization newmark_beta -postprocess uav -timelog
\end{lstlisting}

Once the step above has been performed, we solve the problem using two MPI processes, with the given mesh file \sh{bar-dynamic.msh}. 

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve -np 2 Main.edp -mesh ./../Meshes/2D/bar-dynamic.msh -v 0
\end{lstlisting}


\begin{figure}[h!]
\centering
\includegraphics[width=0.4\textwidth]{./Images/ed-time-par.png}
\caption{Time logging output produced for parallel run on 2 processes.\label{time-par-ed}}
\end{figure}

The figure~\ref{time-par-ed} shows the time logging output produced for parallel run on 2 processes using \sh{-timelog} flag. Similar output is produced for sequential solver of the same problem shown in figure~\ref{time-seq-ed}. Take note of the speed up, which should be two folds - parallel solver solves the full problem in half the time (1.5 sec) than that of sequential solver (3.3 sec). This is due to the fact we used 2 MPI processes.

Also take note of timings produced for different operations of the solver. Note that in figures~\ref{time-par-ed}, \ref{time-seq-ed}, we only see the final time step of the solved problem. 

\begin{figure}[h!]
\centering
\includegraphics[width=0.4\textwidth]{./Images/ed-time-seq.png}
\caption{Time logging output produced for parallel run on 2 processes.\label{time-seq-ed}}
\end{figure}

\subsection{Exercise 1}

You are encouraged to try out timelogging and find out if the code (parallel/sequential) is any faster when we use Newmark-$\beta$ or Generalized-$\alpha$. Read the documentation for other types of time discretizations that can be performed with PSD, try each one out with \sh{-timelog} and compare. 

\subsection{Exercise  2}

There is a solver run level flag for mesh refinement \footnote{Mesh refinement is performed after partitioning.}. This flag is called \sh{-split [int]} which splits the triangles (resp. tetrahedrons) of your mesh into  four smaller  triangles (resp. tetrahedrons). As such \sh{-split 2} will produce a mesh with 4 times the elements of the input mesh. Similarly, \sh{-split n} where $n$ is a positive integer produces $2^n$ times more elements than the input mesh. You are encouraged to use this \sh{-split} flag to produce refined meshes and check, mesh convergence of a problem, computational time, etc. Use of parallel computing is recommended. You could try it out with \sh{PSD\_Solve} or \sh{PSD\_Solve\_Seq}, for example:

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve -np 2 Main.edp -mesh ./../Meshes/2D/bar-dynamic.msh -v 0 -split 2
\end{lstlisting}

for splitting each triangle of the mesh  \sh{bar-dynamic.msh} into 4. 


\subsection{Exercise  3}

There is a preprocess level flag \sh{-debug}, which as the name suggests should be used for debug proposes by developers. However, this flag will activate OpebGL live plotting of the problem, with displaced mesh. You are encouraged to try it out 

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -dimension 2 -problem elastodynamics -dirichletconditions 1 -tractionconditions 1 \
-timediscretization newmark_beta -postprocess uav -timelog -debug
\end{lstlisting}

Then to run the problem we need aditional \sh{-wg} flag

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve -np 2 Main.edp -mesh ./../Meshes/2D/bar-dynamic.msh -v 0 -wg
\end{lstlisting}

\subsection{Exercise  4}

PSD comes with additional set of plugins/functions that are highly optimized for performing certain operations during solving. These operations are handled by GoFast Plugins (GFP) kernel of PSD (optimize C++ classes/templates/structures), by default this functionality is turned off and not used. You are encouraged to try out using GFP functions in a solver by using \sh{-useGFP} flag flag to \sh{PSD\_PreProcess} For example, the PSD solver workflow for the first 2D example in this tutorial would be:

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -dimension 2 -problem elastodynamics -dirichletconditions 1 -tractionconditions 1 \
-timediscretization newmark_beta -postprocess uav -useGFP
\end{lstlisting}

Once the step above has been performed, we solve the problem using, with the given mesh file \sh{bar-dynamic}. 

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve -np 2 Main.edp -mesh ./../Meshes/2D/bar-dynamic.msh -v 0 -wg
\end{lstlisting}

Try it out for other problems of this tutorial. \sh{-useGFP} should lead to a faster solver, it might be a good idea to always use this option. To go one step further, use \sh{-timelog} flag and determine if you have some speed up.

