---
title: Linear Elasticity Tutorials
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
abstract: This document details some tutorials of 'linear elasticity' module of PSD. These tutorials are not verbose, but does instead give a kick start to users/developers for using PSD's 'linear elasticity' module.
---

\newcommand{\sh}[1]{\small\sffamily{\color{blue!60}#1}}

\begin{figure}[h!]
\centering
\includegraphics[width=0.5\textwidth]{./Images/le-2d-bar.png}
\caption{The 2D clamped bar problem. \label{2dbar-le}}
\end{figure}

\subsection{Parallel 2D linear-elasticity}

The problem of interest is a single Dirichlet condition (clamped end 2D bar) and body force source term (see, figure~\ref{2dbar-le}). Additionally postrocessing is demanded for displacement $u$. 

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -problem linear_elasticity -dimension 2 -bodyforceconditions 1 \
-dirichletconditions 1 -postprocess u
\end{lstlisting}

We solve the problem using four MPI processes, with the given mesh file \sh{bar.msh}. 

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve -np 4 Main.edp -mesh ./../Meshes/2D/bar.msh -v 0
\end{lstlisting}

\begin{figure}[h!]
\centering
\includegraphics[width=0.4\textwidth]{./Images/le-2d-bar-partioned.png}\\
\includegraphics[width=0.4\textwidth]{./Images/le-2d-bar-results.png}
\caption{The 2D clamped bar problem: partitioned mesh and displacement field visualization in ParaView. \label{bar-le}}
\end{figure}

Using ParaView for postprocessing the results that are provided in the \sh{VTUs...} folder, results such as those shown in figure~\ref{bar-le} can be extracted.

\subsection{Parallel 3D linear-elasticity}

The problem of interest is a single Dirichlet condition (clamped end 3D bar) and body force source term. Additionally postrocessing is demanded for displacement $u$. 

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -problem linear_elasticity -dimension 3 -bodyforceconditions 1 \
-dirichletconditions 1 -postprocess u
\end{lstlisting}

We solve the problem using four MPI processes, with the given mesh file \sh{bar.msh}. 

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve -np 4 Main.edp -mesh ./../Meshes/3D/bar.msh -v 0
\end{lstlisting}

\begin{figure}[h!]
\centering
\includegraphics[width=0.4\textwidth]{./Images/le-3d-bar-clamped-ends.png}\\
\includegraphics[width=0.4\textwidth]{./Images/le-3d-bar-clamped-pulled-partioned.png}
\caption{The 3D clamped bar problem: partitioned mesh and displacement field visualization in ParaView. \label{3dbar-le}}
\end{figure}

Using ParaView for postprocessing the results that are provided in the \sh{VTUs...} folder, results such as those shown in figure~\ref{3dbar-le} can be extracted.

\subsection{Sequential problems}

To the same problems above Add \sh{-sequential} flag to \sh{PSD\_PreProcess} for sequential solver, but remember to use \sh{PSD\_Solve\_Seq} instead of \sh{PSD\_Solve}. So the work flow for the 2D problem would be:

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -problem linear_elasticity -dimension 2 -bodyforceconditions 1 \
-dirichletconditions 1 -postprocess u -sequential
\end{lstlisting}

We solve the problem using the given mesh file \sh{bar.msh}. 

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve_Seq Main.edp -mesh ./../Meshes/2D/bar.msh -v 0
\end{lstlisting}

Similarly try out the 3D problem as well.

\subsection{Comparing CPU time}

PSD provides mean to time log your solver via \sh{-timelog} flag. What this will do when you run your solver, on the terminal you will have information printed on what is the amount of time taken by each step of your solver. Warning, this will make your solver slower, as this action involves 'MPI\_Barrier' routines for correctly timing operation. 

An example work flow of 2D solver with timelogging:

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -problem linear_elasticity -dimension 2 -bodyforceconditions 1 \
-dirichletconditions 1 -postprocess u -timelog
\end{lstlisting}

We solve the problem using four MPI processes, with the given mesh file \sh{bar.msh}. 

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve -np 4 Main.edp -mesh ./../Meshes/2D/bar.msh -v 0
\end{lstlisting}


\begin{figure}[h!]
\centering
\includegraphics[width=0.4\textwidth]{./Images/le-time-par.png}
\caption{Time logging output produced for parallel run on 4 processes.\label{time-par-le}}
\end{figure}

The figure~\ref{time-par-le} shows the time logging output produced for parallel run on 4 processes using \sh{-timelog} flag. Take note of timings produced for different operations of the solver. 


\subsection{Exercise  1}

There is a solver run level flag for mesh refinement \footnote{Mesh refinement is performed after partitioning.}. This flag is called \sh{-split [int]} which splits the triangles (resp. tetrahedrons) of your mesh into  four smaller  triangles (resp. tetrahedrons). As such \sh{-split 2} will produce a mesh with 4 times the elements of the input mesh. Similarly, \sh{-split n} where $n$ is a positive integer produces $2^n$ times more elements than the input mesh. You are encouraged to use this \sh{-split} flag to produce refined meshes and check, mesh convergence of a problem, computational time, etc. Use of parallel computing is recommended. You could try it out with \sh{PSD\_Solve} or \sh{PSD\_Solve\_Seq}, for example:

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve -np 4 Main.edp -mesh ./../Meshes/2D/bar.msh -v 0 -split 2
\end{lstlisting}

for splitting each triangle of the mesh  \sh{bar.msh} into 4. 


\subsection{Exercise  2}

There is a preprocess level flag \sh{-debug}, which as the name suggests should be used for debug proposes by developers. However, this flag will activate OpenGL live visualization of the problems displacement field. You are encouraged to try it out 

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -problem linear_elasticity -dimension 2 -bodyforceconditions 1 \
-dirichletconditions 1 -postprocess u -timelog -debug
\end{lstlisting}

Then to run the problem we need traditional \sh{-wg} flag

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve -np 4 Main.edp -mesh ./../Meshes/2D/bar.msh -v 0 -wg
\end{lstlisting}

\subsection{Exercise  3}

There is a preprocess level flag \sh{-withmaterialtensor}, which introduces the full material tensor into the finite element variational formulation. You are encouraged to use this flag and see how the solver performs.

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -problem linear_elasticity -dimension 2 -bodyforceconditions 1 \
-dirichletconditions 1 -postprocess u -timelog -withmaterialtensor
\end{lstlisting}

Then to run the problem we need additional \sh{-wg} flag

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve -np 4 Main.edp -mesh ./../Meshes/2D/bar.msh -v 0
\end{lstlisting}

To understand what the flag does, try to find out the difference between the files created by \sh{PSD\_PreProcess} when used with and without  \sh{-withmaterialtensor} flag. Especially, compare  \sh{ControlParameters.edp} and \sh{VariationalFormulations.edp} files produced by \sh{PSD\_PreProcess} step. 

