---
title: Nonlinear elasto-plastic Von-Mises material analysis via MFront $-$Isotropic linear hardening plasticity$-$ 
subtitle: Isotropic linear hardening plasticity
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
    \usepackage[style=numeric, bibencoding=utf8]{biblatex}
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
    \addbibresource{biblio.bib}   
abstract: This document details a tutorial that allows one to use PSD-MFront interface for non linear elasto-plastic problem. MFront is used for  general handling the material behaviour, i.e. it it handles the non-linearity updates and material parameters. It is advised to follow this tutorial after tutorial 1 and tutorial 9 of linear-elasticity, which introduce MFront for linear-elasticty (I believe, it is best to walk before we run). \newline Note that, non linear  elasto-plastic merely provides means of getting started with Mfornt, the real potential lies in using different and more complex non linear materials and laws which Mfront provides. So this tutorial should be considered as baptism to the world of non linear PSD-MFront coupling which we believe has a lot of potential to solve some non trivial problems.
---

\newcommand{\psd}[1]{{\small\sffamily{\color{blue!60}#1}}}

This tutorial is concerned with a non-linear problem of the incremental analysis of an elasto-plastic Von-Mises material. A two-dimensional test (in $x-y$) will be considered. The problem of interest is a quarter of a cylinder (with external radius $R_e$ and internal radius $R_i$) \cref{bar-sd}. Boundary conditions correspond to symmetry conditions on the bottom horizontal $y=0$ and left vertical borders $x=0$ (resp. numbered 1 and 3 as mesh labels). Loading consists of a uniform pressure (traction boundary) on the internal boundary (numbered 4 as mesh label). Load (pressure) $q$ will be progressively increased from 0 to $q_{\text{lim}}=\frac{2}{\sqrt3}\sigma_0\text{log}(\frac{R_e}{R_i})$ which is the analytical collapse load for a perfectly-plastic material (no hardening): 

\begin{figure}[h!]
\centering
\includegraphics[width=0.3\textwidth]{./Images/nl-arc.png}
\caption{Domain of the non-linear problem. \label{bar-sd}}
\end{figure}


The material is represented by an isotropic elasto-plastic von Mises yield condition of uniaxial strength $\sigma_0$ and with isotropic hardening of modulus $H$. The yield condition is thus given by:

$$f(\sigma)=\sqrt{\frac{3}{2}s:s}-\sigma_0-Hp\le0$$

where $p$ is the cumulated equivalent plastic strain and $s$ denoting the deviatoric elastic stress $s = \text{dev} \sigma_{\text{elas}}$. The hardening modulus can also be related to a tangent elastic modulus $E_t=\frac{EH}{E+H}$.

To compute the structures response an iterative predictor-corrector return mapping algorithm embedded in a Newton-Raphson global loop for restoring equilibrium is used. Due to the simple expression of the von Mises criterion, the return mapping procedure is completely analytical (with linear isotropic hardening). We point out that the two-dimensional nature of the problem will be impose keeping track of the out-of-plane $\varepsilon^p_{zz}$ plastic strain and dealing with representations of stress/strain states including the $zz$ component.


The displacement field evolution during the cylinder expansion will look like this the one presented in \cref{bar-sd}:

\begin{figure}[h!]
\centering
\includegraphics[width=0.3\textwidth]{./Images/nl-ep-t0.png}\includegraphics[width=0.3\textwidth]{./Images/nl-ep-t4.png}\includegraphics[width=0.3\textwidth]{./Images/nl-ep-t8.png}\\
\includegraphics[width=0.3\textwidth]{./Images/nl-ep-t12.png}\includegraphics[width=0.3\textwidth]{./Images/nl-ep-t16.png}\includegraphics[width=0.3\textwidth]{./Images/nl-ep-t19.png}
\caption{Warped displacement field evolution - from top left $t_0,t_4,t_8,t_{12},t_{16},t_{19}$. \label{bar-sd}}
\end{figure}


The return mapping procedure consists in finding a new stress $\sigma_{n+1}$ and internal variable $p_{n+1}$ state verifying the current plasticity condition from a previous stress $\sigma_n$ and internal variable $p_{n}$ state and an increment of total deformation $\Delta \varepsilon$. All this is handled by MFront, where MFront requests PSD for the previous $n$ time-step strains $\varepsilon_n$. In order to use a Newton-Raphson procedure to resolve global equilibrium, we also need to derive the algorithmic consistent tangent matrix which is also given by MFront. 

Within MFront an elastic trial stress $\sigma_{\text{elas}} = \sigma_{n} + \mathbf{M}\Delta \varepsilon$ is first computed. Then the  plasticity criterion is then evaluated with the previous plastic strain $f_{\text{elas}}=\sigma_{\text{elas}}^{\text{eq}} - \sigma_0 - Hp_n$, where $\sigma_{\text{elas}}^{\text{eq}}=\sqrt{\frac{3}{2}s:s}$. Consequently, if $f_{\text{elas}} \le 0$ no plasticity occurs during this time increment and $\Delta \varepsilon^p = \Delta p =0$. Otherwise if $f_{\text{elas}} > 0$, plasticity  occurs and the increment of plastic strain is given by 
$$\Delta p = \frac{f_{\text{elas}}}{3\mu + H}$$


The final stress state is corrected by the plastic strain as follows 

$$\sigma_{n+1} = \sigma_{\text{elas}} - \beta s \quad \text{with} \quad \beta=\frac{3\mu}{\sigma_{\text{elas}}^{\text{eq}}}\Delta p$$



\begin{figure}[h!]
\centering
\includegraphics[width=0.45\textwidth]{./Images/t5.png}\includegraphics[width=0.45\textwidth]{./Images/t19.png}
\caption{Validation of the displacement field obtained by PSD and another reference code. The displacement magnitude is plotted on the central line which bisects the geometry into two. On the left time steps - $t_0,t_4,t_8,t_{12},t_{16}$ are plotted and on the right $t_{19}$. Reference results used for comparison  were obtained by installing and running the FEniCS Solid Mechanics library [Garth N. Wells (2021)]. \label{comp1}}
\end{figure}


\begin{figure}[h!]
\centering
\includegraphics[width=0.45\textwidth]{./Images/final.png}
\caption{Validation of the displacement  movement of inner border movement obtained by PSD and another reference code.  Reference results used for comparison  were obtained by installing and running the FENICS solid mechanics codes \url{https://bitbucket.org/fenics-apps/fenics-solid-mechanics}. \label{comp2}}
\end{figure}





\begin{figure}[h!]
\centering
\fbox{\includegraphics[width=0.45\textwidth]{./Images/test_psd_t0.png}}\hspace{1mm}\fbox{\includegraphics[width=0.456\textwidth]{./Images/test_fenics_t0.png}}\vspace{1mm}
\fbox{\includegraphics[width=0.45\textwidth]{./Images/test_psd_t10.png}}\hspace{1mm}\fbox{\includegraphics[width=0.456\textwidth]{./Images/test_fenics_t10.png}}\vspace{1mm}
\fbox{\includegraphics[width=0.45\textwidth]{./Images/test_psd_t19.png}}\hspace{1mm}\fbox{\includegraphics[width=0.456\textwidth]{./Images/test_fenics_t19.png}}\vspace{1mm}
\caption{Validation results comparison of PSD (left column) and reference code (right column) at different timesteps ($t_0, t_{10}, t_{19}$). Reference results used for comparison  were obtained by installing and running the FEniCS Solid Mechanics library [Garth N. Wells (2021)]. \label{comp2}}
\end{figure}

# Bibliography

