/**************************************************************************************
*                                                                                     *
* Author : Mohd Afeef BADRI, Reine Fares                                              *
* Email  : mohd-afeef.badri@cea.fr                                                    *
* Date   : 02/03/2022                                                                 *
* Type   : Support file                                                               *
*                                                                                     *
* Comment: This support file is  responsible for generating iwan-validation.edp       *
*                                                                                     *
**************************************************************************************/

cout << " building PSD-validation-iwan.edp";


ofstream  write("PSD-validation-iwan.edp");

codeSnippet R""""(

/*****************************************************************************

         This file is a part of PSD (Parallel Structural Dynamics)

     -------------------------------------------------------------------

     Author(s): Mohd Afeef Badri, Reine Fares
     Email    : mohd-afeef.badri@cea.fr
     Date     : 02-March-2022
     Comment  : This test checks the MFront-PSD coupling for Iwan law.
                This code expects the following INPUTS from user:
                  i) 'in.data' this file contains 2  columns  the time 
                     and input Exy value (loading).
                 ii) 'steps' this is an integer value giving the total
                     number of time steps in your file 'in.data'
                The output of this code is 'out.data' file, an  ASCII 
                file that contains 3 columns, time, Sigma_xy, Exy.

     -------------------------------------------------------------------

     PSD a parallel  finite  element framework  provides tools to  solve
     multiple  solid-dynamic  problems; PSD is distributed  in  the hope
     that it will be useful, but WITHOUT ANY WARRANTY; or  without  even
     the implied warranty of  FITNESS  FOR  A  PARTICULAR  PURPOSE.

*******************************************************************************/
load "mfront"
load "Element_QF"
load "msh3"

mesh3 Th = cube(1, 1, 1);

// Quadrature space with 3 elements for stress and strain tensor
fespace Sh(Th, [FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d]);
Sh[Eps11, Eps22, Eps33, Eps12, Eps13, Eps23];
Sh[EpsOld11, EpsOld22, EpsOld33, EpsOld12, EpsOld13, EpsOld23];
Sh[Sig11, Sig22, Sig33, Sig12, Sig13, Sig23];

fespace Ih(Th, [FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d,
	FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d,
	FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d,
	FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d,
	FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d,
	FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d,
	FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d,
	FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d,
	FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d,
	FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d,
	FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d,
	FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d
]);

Ih[Isv0, Isv1, Isv2, Isv3, Isv4, Isv5, Isv6, Isv7, Isv8, Isv9, Isv10, Isv11, Isv12, Isv13, Isv14, Isv15, Isv16, Isv17, Isv18, Isv19, Isv20, Isv21, Isv22, Isv23, Isv24, Isv25, Isv26, Isv27, Isv28, Isv29, Isv30, Isv31, Isv32, Isv33, Isv34, Isv35, Isv36, Isv37, Isv38, Isv39, Isv40, Isv41, Isv42, Isv43, Isv44, Isv45, Isv46, Isv47, Isv48, Isv49, Isv50, Isv51, Isv52, Isv53, Isv54, Isv55, Isv56, Isv57, Isv58, Isv59, Isv60, Isv61, Isv62, Isv63, Isv64, Isv65, Isv66, Isv67, Isv68, Isv69, Isv70, Isv71, Isv72, Isv73, Isv74, Isv75, Isv76, Isv77, Isv78, Isv79, Isv80, Isv81, Isv82, Isv83, Isv84, Isv85, Isv86, Isv87, Isv88, Isv89, Isv90, Isv91, Isv92, Isv93, Isv94, Isv95, Isv96, Isv97, Isv98, Isv99, Isv100, Isv101, Isv102, Isv103, Isv104, Isv105, Isv106, Isv107, Isv108, Isv109, Isv110, Isv111, Isv112, Isv113, Isv114, Isv115, Isv116, Isv117];

Isv0[] = 0;

string MaterialProperty = "YoungModulus PoissonRatio NumberofSpring";

string BackSCoeffCiNames1 = " BackSCoeff_Ci[0] BackSCoeff_Ci[1] BackSCoeff_Ci[2] BackSCoeff_Ci[3] BackSCoeff_Ci[4] BackSCoeff_Ci[5] BackSCoeff_Ci[6] BackSCoeff_Ci[7] BackSCoeff_Ci[8] BackSCoeff_Ci[9]";
string BackSCoeffCiNames2 = " BackSCoeff_Ci[10] BackSCoeff_Ci[11] BackSCoeff_Ci[12] BackSCoeff_Ci[13] BackSCoeff_Ci[14] BackSCoeff_Ci[15] BackSCoeff_Ci[16] BackSCoeff_Ci[17] BackSCoeff_Ci[18] BackSCoeff_Ci[19]";
string BackSCoeffCiNames3 = " BackSCoeff_Ci[20] BackSCoeff_Ci[21] BackSCoeff_Ci[22] BackSCoeff_Ci[23] BackSCoeff_Ci[24] BackSCoeff_Ci[25] BackSCoeff_Ci[26] BackSCoeff_Ci[27] BackSCoeff_Ci[28] BackSCoeff_Ci[29]";
string BackSCoeffCiNames4 = " BackSCoeff_Ci[30] BackSCoeff_Ci[31] BackSCoeff_Ci[32] BackSCoeff_Ci[33]";


string VMSYiNames1 = " VMS_Yi[0] VMS_Yi[1] VMS_Yi[2] VMS_Yi[3] VMS_Yi[4] VMS_Yi[5] VMS_Yi[6] VMS_Yi[7] VMS_Yi[8] VMS_Yi[9]";
string VMSYiNames2 = " VMS_Yi[10] VMS_Yi[11] VMS_Yi[12] VMS_Yi[13] VMS_Yi[14] VMS_Yi[15] VMS_Yi[16] VMS_Yi[17] VMS_Yi[18] VMS_Yi[19]";
string VMSYiNames3 = " VMS_Yi[20] VMS_Yi[21] VMS_Yi[22] VMS_Yi[23] VMS_Yi[24] VMS_Yi[25] VMS_Yi[26] VMS_Yi[27] VMS_Yi[28] VMS_Yi[29]";
string VMSYiNames4 = " VMS_Yi[30] VMS_Yi[31] VMS_Yi[32] VMS_Yi[33]";  

string PropertyNames = MaterialProperty + BackSCoeffCiNames1 + BackSCoeffCiNames2 + BackSCoeffCiNames3 + BackSCoeffCiNames4 + VMSYiNames1 + VMSYiNames2 + VMSYiNames3 + VMSYiNames4;


 
real[int] PropertyValues =[

	614930000.0, 0.371, 34,
	1.45281258E+10, 5.82178617E+10, 4.54355646E+10, 3.70904898E+10, 2.77751572E+10, 2.15706482E+10, 
	1.53920096E+10, 1.23928163E+10, 1.00167542E+10, 7.88712681E+09, 6.17841185E+09, 5.25405456E+09, 
	4.27446331E+09, 4.01462717E+09, 4.28497533E+09, 3.47094829E+09, 2.39276478E+09, 1.81963534E+09, 
	1.42613657E+09, 1.08674829E+09, 8.65896849E+08, 7.59030876E+08, 5.12631105E+08, 3.82296058E+08, 
	2.91042980E+08, 1.35494636E+08, 9.52184677E+07, 1.03105902E+08, 7.05953646E+07, 4.13915375E+07, 
	2.51757271E+07, 1.47582922E+07, 8.87052676E+06, 5.95328485E+06,
	
	3.40005509E+05, 4.20308513E+05, 5.24405583E+05, 6.53604724E+05, 8.05746026E+05, 1.02172957E+06, 
 	1.26789373E+06, 1.64705367E+06, 2.01271770E+06, 2.52032780E+06, 3.05546227E+06, 3.75162146E+06, 
 	4.38436606E+06, 5.22502629E+06, 5.80307354E+06, 6.42397205E+06, 7.14120247E+06, 8.13198230E+06, 
	9.07056705E+06, 1.01794843E+07, 1.12643332E+07, 1.23695744E+07, 1.32516915E+07, 1.46063819E+07, 
	1.55155396E+07, 1.67173705E+07, 1.84181142E+07, 1.92532768E+07, 1.98852369E+07, 2.06809022E+07, 
	2.14289929E+07, 2.21412448E+07, 2.27687421E+07, 2.32772260E+07

];



int steps = 2001;
real timeT, GammaExy;
real[int] SigxyRef(steps);
real SigxyMtest;

ifstream inEpsilon("in.data");
ofstream outStress("out.data");
  
if (mpirank == 0)
	outStress << "#Time" << "  " << "G_xy" << "  " << "Sig_xy"  <<  "  " << "Sig_xy_mtest" <<endl;

for (int i = 0; i < steps; i++)
{

	inEpsilon >> timeT >> GammaExy >> SigxyRef(i) >> SigxyMtest ;
	GammaExy = 1. / sqrt(2.) *GammaExy;
        [Eps11, Eps22, Eps33, Eps12, Eps13, Eps23] =[0, 0, 0, GammaExy, 0, 0];

        PsdMfrontHandler( "Iwan"                                               ,
                           mfrontBehaviourHypothesis = "TRIDIMENSIONAL"        ,
                           mfrontPropertyNames       = PropertyNames         ,
                           mfrontPropertyValues      = PropertyValues        ,
                           mfrontStrainTensor        = Eps12[]                 ,
                           mfrontStressTensor        = Sig22[]                 ,
                           mfrontStateVariable       = Isv1[],
                           mfrontPreviousStrainTensor = EpsOld12[]                 
                         );
	EpsOld12[] = Eps12 [];
	              
	int prec = outStress.precision(16);                       
	if(mpirank==0)                         
    outStress << timeT << "  " << GammaExy *  sqrt(2.) << "  " << Sig11[][12] / sqrt(2.) << "  " << SigxyMtest << endl;
}

)"""";

if(pipegnu)
{
write<< 
   "system(\"echo \\\"plot 'out.data' u 1:3 w l lw 4 t 'PSD', '' u 1:4 w l lw 2 t 'MTEST'\\\" | gnuplot -p\");"
<< endl;
}

cout << " ............................ Done  \n";  
