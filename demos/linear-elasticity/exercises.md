---
title: Linear Elasticity additional exercises
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
    \lstdefinestyle{CppStyle}{
	language=bash,
	basicstyle=\small\sffamily,
	numbers=left,
	numberstyle=\tiny,
	numbersep=3pt,
	morekeywords={real, macro, for, int, mpirank, abs, string, FEQF2, fespace, PsdMfrontHandler},
	morecomment=[l]{//},
	morecomment=[s]{/*}{*/},
	keywordstyle=\color{magenta}\ttfamily,
	commentstyle=\color{blue}\ttfamily,
	stringstyle=\color{red}\ttfamily,
	frame=tb,
	columns=fullflexible,
	backgroundcolor=\color{black!10},
	linewidth=1.\linewidth,
	xleftmargin=0.05\linewidth,
	literate =
	{'}{{\textquotesingle}}1
	{-}{{-}}1
	{~}{{\centeredtilde}}1
	,
    }
abstract: This document details a additional exercises of linear elasticity. These exercises are recomeneded to be followed only after other tutorials of linear elasticity  have been followed.
---

\newcommand{\psd}[1]{{\small\sffamily{\color{blue!60}#1}}}

\subsection{Advance exercise  1}

There is a solver run level flag for mesh refinement \footnote{Mesh refinement is performed after partitioning.}. This flag is called \psd{-split [int]} which splits the triangles (resp. tetrahedrons) of your mesh into  four smaller  triangles (resp. tetrahedrons). As such \psd{-split 2} will produce a mesh with 4 times the elements of the input mesh. Similarly, \psd{-split n} where $n$ is a positive integer produces $2^n$ times more elements than the input mesh. You are encouraged to use this \psd{-split} flag to produce refined meshes and check, mesh convergence of a problem, computational time, etc. Use of parallel computing is recommended. You could try it out with \psd{PSD\_Solve} or \psd{PSD\_Solve\_Seq}, for example:

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve -np 4 Main.edp -mesh ./../Meshes/2D/bar.msh -v 0 -split 2
\end{lstlisting}

for splitting each triangle of the mesh \psd{bar.msh} into 4.

\subsection{Advance exercise  2}

There is a preprocess level flag \psd{-debug}, which as the name suggests should be used for debug proposes by developers. However, this flag will activate OpenGL live visualization of the problems displacement field. You are encouraged to try it out

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -problem linear_elasticity -dimension 2 -bodyforceconditions 1 \
-dirichletconditions 1 -postprocess u -timelog -debug
\end{lstlisting}

Then to run the problem we need additional \psd{-wg} flag

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve -np 4 Main.edp -mesh ./../Meshes/2D/bar.msh -v 0 -wg
\end{lstlisting}

\subsection{Advance Exercise  3}

One interesting way of solving a linear Elasticity problem is to solve it via a pseudo nonlinear model. There is a preprocess level flag \psd{-model pseudo\_nonlinear}, which introduces pseudo nonlinearity  into the finite element variational formulation of linear elasticity. You are encouraged to use this flag and see how the solver performs. Indeed, now you should see some nonlinear iterations (1 or 2)  are taken for convergence.

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -problem linear_elasticity -dimension 2 -bodyforceconditions 1 \
-dirichletconditions 1 -postprocess u -timelog -model pseudo_nonlinear
\end{lstlisting}

Then to run the problem

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve -np 4 Main.edp -mesh ./../Meshes/2D/bar.msh -v 0
\end{lstlisting}

To understand what the flag does, try to find out the difference between the files created by \psd{PSD\_PreProcess} when used with and without  \psd{-model pseudo\_nonlinear} flag. Especially, compare  \psd{LinearFormBuilderAndSolver.edp} and \psd{VariationalFormulations.edp} files produced by \psd{PSD\_PreProcess} step. You will see Newton--Raphsons iterations are performed for solving the linear problem. However, the nonlinear iterations loop converges very rapidly (in 1 iteration) due to linear nature of the problem. **Note:** This flag is exclusive for parallel solver.


\subsection{Advance exercise 4}

There is a preprocess level flag \psd{-withmaterialtensor}, which introduces the full material tensor into the finite element variational formulation. You are encouraged to use this flag and see how the solver performs.

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -problem linear_elasticity -dimension 2 -bodyforceconditions 1 \
-dirichletconditions 1 -postprocess u -timelog -withmaterialtensor
\end{lstlisting}

Then to run the problem

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve -np 4 Main.edp -mesh ./../Meshes/2D/bar.msh -v 0
\end{lstlisting}

To understand what the flag does, try to find out the difference between the files created by \psd{PSD\_PreProcess} when used with and without  \psd{-withmaterialtensor} flag. Especially, compare  \psd{FemParameters.edp}, \psd{MeshAndFeSpace} and \psd{VariationalFormulations.edp} files produced by \psd{PSD\_PreProcess} step.
