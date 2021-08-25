---
title: Soildynamics Tutorials for PSD
author: Mohd Afeef Badri
geometry: margin=2cm
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
abstract: This document details some tutorials of soildynamics module of PSD. These tutorials are not verbose, but does instead give a kick start to users/developers for using PSD's soildynamics module. 
---
\newcommand{\psd}[1]{{\small\sffamily{\color{blue!60}#1}}}

\subsection{Exercise  1}

You are encouraged to try out sequential PSD solver, to do so used add \psd{-sequential} flag to \psd{PSD\_PreProcess} step and run the solver with \psd{PSD\_Solve\_Seq} instead of \psd{PSD\_Solve}. For example, the PSD sequential solver workflow for the first 2D example in this tutorial would be:

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -dimension 2 -problem soildynamics -dirichletconditions 1 -timediscretization newmark_beta \
-postprocess uav -sequential
\end{lstlisting}

Once the step above has been performed, we solve the problem using \psd{PSD\_Solve\_Seq}, with the given mesh file \psd{soil.msh}. 

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve_Seq  Main.edp -mesh ./../Meshes/2D/soil.msh -v 0
\end{lstlisting}

Try it out for other problems of this tutorial. 

\subsection{Exercise 2}

For soildynamic problems with double couple source, the double couple source can be introduced into the solver either by displacement-based operator -- providing displacements at the double couple points that will be converted to moments -- or by force-based operators -- providing forces at the double couple points that  will be converted to moments. In the tutorials above we already tried displacement-based way of introducing double couple source by using \psd{-doublecouple displacement\_based}. You are encouraged to try out the force-based double couple source by using \psd{-doublecouple force\_based}.

\subsection{Exercise 3}

You are encouraged to try out timelogging and find out if the code (parallel/sequential) is any faster when we use Newmark-$\beta$ or Generalized-$\alpha$. Read the documentation for other types of time discretizations that can be performed with PSD, try each one out with \psd{-timelog} and compare.

\subsection{Exercise  4}

PSD comes with additional set of plugins/functions that are highly optimized for performing certain operations during solving. These operations are handled by GoFast Plugins (GFP) kernel of PSD (optimize C++ classes/templates/structures), by default this functionality is turned off and not used. You are encouraged to try out using GFP functions in a solver by using \psd{-useGFP} flag flag to \psd{PSD\_PreProcess} For example, the PSD solver workflow for the first 2D example in this tutorial would be:

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -dimension 2 -problem soildynamics -dirichletconditions 1 -timediscretization newmark\_beta \
-postprocess uav -useGFP
\end{lstlisting}

Once the step above has been performed, we solve the problem using, with the given mesh file \psd{soil.msh}. 

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve -np 4 Main.edp -mesh ./../Meshes/2D/soil.msh -v 0
\end{lstlisting}

Try it out for other problems of this tutorial. \psd{-useGFP} should lead to a faster solver, it might be a good idea to always use this option. To go one step further, use \psd{-timelog} flag and determine if you have some speed up. 

