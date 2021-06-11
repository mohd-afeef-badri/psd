---
title: Fracture mechanics Tutorials
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
abstract: This document details some tutorials of 'fracture mechanics' module of PSD. These tutorials are not verbose, but does instead give a kick start to users/developers for using PSD's 'fracture mechanics' module. 
---

\newcommand{\sh}[1]{\small\sffamily{\color{blue!60}#1}}



\subsection{Parallel 2D}

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field \
-dirichletconditions 2
\end{lstlisting}

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve -np 4 Main.edp -mesh ./../Meshes/2D/tensile-crack.msh -v 0
\end{lstlisting}




\subsection{Parallel 3D}

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field \
-dirichletconditions 2
\end{lstlisting}

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve -np 3 Main.edp -mesh ./../Meshes/3D/tensile-crack.msh -v 0
\end{lstlisting}




\subsection{Parallel 2D and calculate reactionforce}

\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field \
-dirichletconditions 2 -getreactionforce -reactionforce stress_based
\end{lstlisting}

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve -np 4 Main.edp -mesh ./../Meshes/2D/tensile-crack.msh -v 0
\end{lstlisting}



\subsection{Parallel 3D and calculate reactionforce}


\begin{lstlisting}[style=BashInputStyle]
PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field \
-dirichletconditions 2 -getreactionforce -reactionforce stress_based
\end{lstlisting}

\begin{lstlisting}[style=BashInputStyle]
PSD_Solve -np 3 Main.edp -mesh ./../Meshes/3D/tensile-crack.msh -v 0
\end{lstlisting}

\subsection{Exercise 1}

Optionally try changing \sh{-reactionforce stress\_based} to \sh{-reactionforce variational\_based} for changing the method to extract reaction force, note that stress based method is way faster.

\subsection{Exercise 2}

Optionally try using  \sh{-useGFP} flag with \sh{PSD\_PreProcess} optimized solver

\subsection{Exercise 3}

Add \sh{-sequential} flag to \sh{PSD\_PreProcess} for sequential solver, but remember to use \sh{PSD\_Solve\_Seq} instead of \sh{PSD\_Solve}

\subsection{Advanced Exercise 1}
try the \sh{-vectorial} flag for vectorial finite element method

\subsection{Advanced Exercise 2}
try the \sh{-energydecomp} flag for using split of tensile energy

\subsection{Advanced Exercise 3}
try using \sh{-constrainHPF} flag for using the constrain condition in hybrid phase field model
