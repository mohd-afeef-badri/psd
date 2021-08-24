---
title: Linear Elasticity Tutorial 2 PSD simulation of bar problem using a sequential solver (non parallel)
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
abstract: This tutorial details how to use 'linear elasticity' module of PSD, however we will not use a parallel solver but a sequential one. Naturally, this tutorial leads to a slow solver than the previous tutorial 1. So this tutorial is not for speed lovers, but rather for detailing the full capacity of PSD. Also sequential solvers are easier to develop and understand hence this tutorial.
---

\newcommand{\psd}[1]{{\small\sffamily{\color{blue!60}#1}}}

Same problem  of Linear elasticity as in tutorial 1 --  2D bar which bends under its own load --, is discuss here. The bar $5\times1$ m$^2$ in area is made up of material with $\rho=8\times 10^3$, $E=200\times 10^9$, and $\nu=0.3$. To avoid text repetition, readers are encouraged to go ahead with this tutorial only after tutorial 1.

As  the problem remains same as tutorial 1, simply add \psd{-sequential} flag to \psd{PSD\_PreProcess} flags from tutorial 1 for sequential solver. The flag \psd{-sequential} signifies the use of sequential PSD solver. So the work flow for the 2D problem would be:

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -problem linear_elasticity -dimension 2 -bodyforceconditions 1 \
-dirichletconditions 1 -postprocess u -sequential
\end{lstlisting}

Similar to tutorial 1, We solve the problem using the given mesh file \psd{bar.msh}. However now we need to use \psd{PSD\_Solve\_Seq} instead of \psd{PSD\_Solve}, as such:

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve_Seq Main.edp -mesh ./../Meshes/2D/bar.msh -v 0
\end{lstlisting}

Users are encouraged to try out the 3D problem with sequential solver.

\subsection{Comparing CPU time}

Naturally, since we are not using parallel PSD for solving, we lose the advantage of solving fast. To testify this claim checking solver timings can be helpful. PSD provides mean to time log your solver via \psd{-timelog} flag. What this will do when you run your solver, on the terminal you will have information printed on what is the amount of time taken by each step of your solver. Warning, this will make your solver slower, as this action involves 'MPI\_Barrier' routines for correctly timing operation.

An example work flow of 2D solver (parallel) with timelogging:

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -problem linear_elasticity -dimension 2 -bodyforceconditions 1 \
-dirichletconditions 1 -postprocess u -timelog
\end{lstlisting}

We solve the problem using four MPI processes, with the given mesh file \psd{bar.msh}.

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve -np 4 Main.edp -mesh ./../Meshes/2D/bar.msh -v 0
\end{lstlisting}


\begin{figure}[h!]
\centering
\includegraphics[width=0.4\textwidth]{./Images/le-time-par.png}
\caption{Time logging output produced for parallel run on 4 processes.\label{time-par-le}}
\end{figure}

The figure~\ref{time-par-le} shows the time logging output produced for parallel run on 4 processes using \psd{-timelog} flag. Take note of timings produced for different operations of the solver.

Now let us repeat the procedure but this time use sequential solver:

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -problem linear_elasticity -dimension 2 -bodyforceconditions 1 \
-dirichletconditions 1 -postprocess u -timelog -sequential
\end{lstlisting}

We solve the problem now in sequential, with the given mesh file \psd{bar.msh}.

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve_Seq Main.edp -mesh ./../Meshes/2D/bar.msh -v 0
\end{lstlisting}


You should now see timings that are higher in comparison to the parallel solver. Approximately, for large meshes using 4 MPI processes should lead to 4 times fast solver. 
