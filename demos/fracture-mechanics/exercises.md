---
title: Fracture mechanics Tutorials - additional exercises
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
abstract: This document details a additional exercises of fracture mechanics. These exercises are recomeneded to be followed only after other tutorials of fracture mechanics  have been followed.
---

\newcommand{\psd}[1]{{\small\sffamily{\color{blue!60}#1}}}

\subsection{Exercise 1}

When calculating the reaction force produced on a surface, optionally try changing \psd{-reactionforce stress\_based} to \psd{-reactionforce variational\_based} for changing the method to extract reaction force, note that stress based method is way faster.

\subsection{Exercise 2}

Optionally try using  \psd{-useGFP} flag with \psd{PSD\_PreProcess} optimized solver. GFP acrynom for GoFast Plugins is a suite of C++ based fuctions built for PSD that are speed optimal.

\subsection{Exercise 3}

Add \psd{-sequential} flag to \psd{PSD\_PreProcess} for sequential solver, but remember to use \psd{PSD\_Solve\_Seq} instead of \psd{PSD\_Solve}

\subsection{Advanced Exercise 1}
try the \psd{-vectorial} flag for vectorial finite element method

\subsection{Advanced Exercise 2}
try the \psd{-energydecomp} flag for using split of tensile energy

\subsection{Advanced Exercise 3}
try using \psd{-constrainHPF} flag for using the constrain condition in hybrid phase field model
