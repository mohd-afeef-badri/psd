/**************************************************************************************
*                                                                                     *
*           This file is a part of PSD project                                        *
*                                                                                     *
*       -------------------------------------------------------------------           *
*                                                                                     *
*       Copyright 2019-2025 CEA/DES                                                   *
*                                                                                     *
*       Licensed under the Apache License, Version 2.0  (the "License");              *
*       you may not use this file except in compliance with the License.              *
*       You may obtain a copy of the License at                                       *
*                                                                                     *
*           http://www.apache.org/licenses/LICENSE-2.0                                *
*                                                                                     *
*       Unless required by applicable law or agreed to in writing, software           *
*       distributed under the License is distributed on an  "AS IS"  BASIS,           *
*       WITHOUT  WARRANTIES  OR  CONDITIONS  OF  ANY  KIND,  either express           *
*       or implied. See  the License  for  the  specific language governing           *
*       permissions and limitations under the License.                                *
*                                                                                     *
*       -------------------------------------------------------------------           *
*                                                                                     *
*                                                                                     *
* Comment: This support file is  responsible for generating iwan-validation.edp       *
*                                                                                     *
**************************************************************************************/

cout << " building PSD-validation-iwan.edp";


ofstream  write("PSD-validation-iwan.edp");

codeSnippet R""""(
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
	FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d,
	FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d,
	FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d,
	FEQF23d, FEQF23d, FEQF23d, FEQF23d
]);

Ih[Isv0, Isv1, Isv2, Isv3, Isv4, Isv5, Isv6, Isv7, Isv8, Isv9, Isv10, Isv11, Isv12, Isv13, Isv14, Isv15, Isv16, Isv17, Isv18, Isv19, Isv20,
Isv21, Isv22, Isv23, Isv24, Isv25, Isv26, Isv27, Isv28, Isv29, Isv30, Isv31, Isv32, Isv33, Isv34, Isv35, Isv36, Isv37, Isv38, Isv39, Isv40,
Isv41, Isv42, Isv43, Isv44, Isv45, Isv46, Isv47, Isv48, Isv49, Isv50, Isv51, Isv52, Isv53, Isv54, Isv55, Isv56, Isv57, Isv58, Isv59, Isv60,
Isv61, Isv62, Isv63, Isv64, Isv65, Isv66, Isv67, Isv68, Isv69, Isv70, Isv71, Isv72, Isv73, Isv74, Isv75, Isv76, Isv77, Isv78, Isv79, Isv80,
Isv81, Isv82, Isv83, Isv84, Isv85, Isv86, Isv87, Isv88, Isv89, Isv90, Isv91, Isv92, Isv93, Isv94, Isv95, Isv96, Isv97, Isv98, Isv99, Isv100,
Isv101, Isv102, Isv103, Isv104, Isv105, Isv106, Isv107, Isv108, Isv109, Isv110, Isv111, Isv112, Isv113, Isv114, Isv115, Isv116, Isv117, Isv118, Isv119, Isv120,
Isv121, Isv122, Isv123, Isv124, Isv125, Isv126, Isv127, Isv128, Isv129, Isv130, Isv131, Isv132, Isv133, Isv134, Isv135, Isv136, Isv137, Isv138, Isv139, Isv140,
Isv141, Isv142, Isv143, Isv144, Isv145, Isv146, Isv147, Isv148, Isv149, Isv150, Isv151, Isv152, Isv153, Isv154, Isv155, Isv156, Isv157, Isv158, Isv159, Isv160,
Isv161, Isv162, Isv163, Isv164, Isv165, Isv166, Isv167, Isv168, Isv169, Isv170, Isv171, Isv172, Isv173, Isv174, Isv175, Isv176, Isv177, Isv178, Isv179, Isv180,
Isv181, Isv182, Isv183, Isv184, Isv185, Isv186, Isv187, Isv188, Isv189, Isv190, Isv191, Isv192, Isv193, Isv194, Isv195, Isv196, Isv197, Isv198, Isv199, Isv200,
Isv201, Isv202, Isv203, Isv204, Isv205, Isv206, Isv207, Isv208, Isv209, Isv210, Isv211, Isv212, Isv213, Isv214, Isv215, Isv216, Isv217, Isv218, Isv219, Isv220,
Isv221, Isv222, Isv223, Isv224, Isv225, Isv226, Isv227, Isv228, Isv229, Isv230, Isv231, Isv232, Isv233, Isv234, Isv235, Isv236, Isv237, Isv238, Isv239, Isv240,
Isv241, Isv242, Isv243];

Isv0[] = 0;

string MaterialProperty = "YoungModulus PoissonRatio NumberofSpring";

string backSCoeffCiNames1 = " BackSCoeffCi[0] BackSCoeffCi[1] BackSCoeffCi[2] BackSCoeffCi[3] BackSCoeffCi[4] BackSCoeffCi[5] BackSCoeffCi[6] BackSCoeffCi[7] BackSCoeffCi[8] BackSCoeffCi[9]";
string backSCoeffCiNames2 = " BackSCoeffCi[10] BackSCoeffCi[11] BackSCoeffCi[12] BackSCoeffCi[13] BackSCoeffCi[14] BackSCoeffCi[15] BackSCoeffCi[16] BackSCoeffCi[17] BackSCoeffCi[18] BackSCoeffCi[19]";
string backSCoeffCiNames3 = " BackSCoeffCi[20] BackSCoeffCi[21] BackSCoeffCi[22] BackSCoeffCi[23] BackSCoeffCi[24] BackSCoeffCi[25] BackSCoeffCi[26] BackSCoeffCi[27] BackSCoeffCi[28] BackSCoeffCi[29]";
string backSCoeffCiNames4 = " BackSCoeffCi[30] BackSCoeffCi[31] BackSCoeffCi[32] BackSCoeffCi[33]";


string VMSYiNames1 = " VMSYi[0] VMSYi[1] VMSYi[2] VMSYi[3] VMSYi[4] VMSYi[5] VMSYi[6] VMSYi[7] VMSYi[8] VMSYi[9]";
string VMSYiNames2 = " VMSYi[10] VMSYi[11] VMSYi[12] VMSYi[13] VMSYi[14] VMSYi[15] VMSYi[16] VMSYi[17] VMSYi[18] VMSYi[19]";
string VMSYiNames3 = " VMSYi[20] VMSYi[21] VMSYi[22] VMSYi[23] VMSYi[24] VMSYi[25] VMSYi[26] VMSYi[27] VMSYi[28] VMSYi[29]";
string VMSYiNames4 = " VMSYi[30] VMSYi[31] VMSYi[32] VMSYi[33]";

string PropertyNames = MaterialProperty + backSCoeffCiNames1 + backSCoeffCiNames2 + backSCoeffCiNames3 + backSCoeffCiNames4 + VMSYiNames1 + VMSYiNames2 + VMSYiNames3 + VMSYiNames4;



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
real dummy;

ifstream inEpsilon("./data/input.data");
ofstream outStress("out-psd.data");

if (mpirank == 0)
	outStress << "#Time" << "  " << "G_xy" << "  " << "Sig_xy_psd" << endl;

for (int i = 0; i < steps; i++)
{
        //-----------------------------------------------------------------------------------------------------
        //           Time  |    G_xy   | Sig_xy_mtest | G_xy*50  | Sig_xy_mtest*50 | Sig_xy_PSD | Sig_xy_PSD*50
        //-----------------------------------------------------------------------------------------------------
	inEpsilon >> timeT >> GammaExy >> SigxyRef(i) >> dummy  >>     dummy      >>   dummy   >>   dummy    ;
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
	{
          outStress << timeT << "  " << GammaExy *  sqrt(2.) << "  " << Sig11[][12] / sqrt(2.)  << endl;
          cout << timeT << "  " << GammaExy *  sqrt(2.) << "  "
               << Sig11[][12] / sqrt(2.)  <<   "  "  << SigxyRef(i)  <<  endl;
        }
}

)"""";

if(pipegnu)
{
write<<
   "system(\"echo \\\"plot 'out-psd.data' u 1:3 w l lw 4 t 'PSD', './data/test.res' u 1:(\\\\$11/sqrt(2)) w l lw 2 t 'MTEST'\\\" | gnuplot -p\");"
<< endl;
}

cout << " ............................ Done  \n";
