---
title: Elastodynamics Tutorials - Advanced Exercises
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

\newcommand{\psd}[1]{{\small\sffamily{\color{blue!60}#1}}}


\subsection{Exercise 1}

You are encouraged to try out timelogging and find out if the code (parallel/sequential) is any faster when we use Newmark-$\beta$ or Generalized-$\alpha$. Read the documentation for other types of time discretizations that can be performed with PSD, try each one out with \psd{-timelog} and compare. 

\subsection{Exercise  2}

There is a solver run level flag for mesh refinement \footnote{Mesh refinement is performed after partitioning.}. This flag is called \psd{-split [int]} which splits the triangles (resp. tetrahedrons) of your mesh into  four smaller  triangles (resp. tetrahedrons). As such \psd{-split 2} will produce a mesh with 4 times the elements of the input mesh. Similarly, \psd{-split n} where $n$ is a positive integer produces $2^n$ times more elements than the input mesh. You are encouraged to use this \psd{-split} flag to produce refined meshes and check, mesh convergence of a problem, computational time, etc. Use of parallel computing is recommended. You could try it out with \psd{PSD\_Solve} or \psd{PSD\_Solve\_Seq}, for example:

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve -np 2 Main.edp -mesh ./../Meshes/2D/bar-dynamic.msh -v 0 -split 2
\end{lstlisting}

for splitting each triangle of the mesh  \psd{bar-dynamic.msh} into 4. 


\subsection{Exercise  3}

There is a preprocess level flag \psd{-debug}, which as the name suggests should be used for debug proposes by developers. However, this flag will activate OpebGL live plotting of the problem, with displaced mesh. You are encouraged to try it out 

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -dimension 2 -problem elastodynamics -dirichletconditions 1 -tractionconditions 1 \
-timediscretization newmark_beta -postprocess uav -timelog -debug
\end{lstlisting}

Then to run the problem we need aditional \psd{-wg} flag

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve -np 2 Main.edp -mesh ./../Meshes/2D/bar-dynamic.msh -v 0 -wg
\end{lstlisting}

\subsection{Exercise  4}

PSD comes with additional set of plugins/functions that are highly optimized for performing certain operations during solving. These operations are handled by GoFast Plugins (GFP) kernel of PSD (optimize C++ classes/templates/structures), by default this functionality is turned off and not used. You are encouraged to try out using GFP functions in a solver by using \psd{-useGFP} flag flag to \psd{PSD\_PreProcess} For example, the PSD solver workflow for the first 2D example in this tutorial would be:

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -dimension 2 -problem elastodynamics -dirichletconditions 1 -tractionconditions 1 \
-timediscretization newmark_beta -postprocess uav -useGFP
\end{lstlisting}

Once the step above has been performed, we solve the problem using, with the given mesh file \psd{bar-dynamic}. 

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve -np 2 Main.edp -mesh ./../Meshes/2D/bar-dynamic.msh -v 0 -wg
\end{lstlisting}

Try it out for other problems of this tutorial. \psd{-useGFP} should lead to a faster solver, it might be a good idea to always use this option. To go one step further, use \psd{-timelog} flag and determine if you have some speed up.

