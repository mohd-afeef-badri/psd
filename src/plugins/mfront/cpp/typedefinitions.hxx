//

#define MFRONT_SHARED_LIBRARY_LOCATION "/usr/lib/libBehaviour.so"


/*
    2D strain  Tensor Logic
    
            d.s1.gradients[0] = mfrontStrainTensor->operator[](indexEx)  ;  //E11
            d.s1.gradients[1] = mfrontStrainTensor->operator[](indexEx+3);  //E22
            d.s1.gradients[2] = 0.                                       ;  //E33
            d.s1.gradients[3] = mfrontStrainTensor->operator[](indexEx+6);  //E22
*/

#define MacroSetGradient2D(x)  \
	d.s1.gradients[0] = mfrontStrainTensor->operator[](x)  ;  \
	d.s1.gradients[1] = mfrontStrainTensor->operator[](x+3);  \
	d.s1.gradients[2] = 0.                                 ;  \
	d.s1.gradients[3] = mfrontStrainTensor->operator[](x+6);


/*

    2D stress  Tensor Logic
    
            mfrontStressTensor->operator[](indexEx)    = d.s1.thermodynamic_forces[0]; // sig_xx
            mfrontStressTensor->operator[](indexEx+1)  = d.s1.thermodynamic_forces[0]; // sig_xx
            mfrontStressTensor->operator[](indexEx+2)  = d.s1.thermodynamic_forces[0]; // sig_xx

            mfrontStressTensor->operator[](indexEx+3)  = d.s1.thermodynamic_forces[1]; // sig_yy
            mfrontStressTensor->operator[](indexEx+4)  = d.s1.thermodynamic_forces[1]; // sig_yy
            mfrontStressTensor->operator[](indexEx+5)  = d.s1.thermodynamic_forces[1]; // sig_yy

            mfrontStressTensor->operator[](indexEx+6)  = d.s1.thermodynamic_forces[3]; // sig_xy
            mfrontStressTensor->operator[](indexEx+7)  = d.s1.thermodynamic_forces[3]; // sig_xy
            mfrontStressTensor->operator[](indexEx+8)  = d.s1.thermodynamic_forces[3]; // sig_xy
*/
            
            
#define MacroGetSress2D(x) \
	mfrontStressTensor->operator[](x)    = d.s1.thermodynamic_forces[0];  \
	mfrontStressTensor->operator[](x+1)  = d.s1.thermodynamic_forces[0];  \
	mfrontStressTensor->operator[](x+2)  = d.s1.thermodynamic_forces[0];  \
                                                                              \
	mfrontStressTensor->operator[](x+3)  = d.s1.thermodynamic_forces[1];  \
	mfrontStressTensor->operator[](x+4)  = d.s1.thermodynamic_forces[1];  \
	mfrontStressTensor->operator[](x+5)  = d.s1.thermodynamic_forces[1];  \
                                                                              \
	mfrontStressTensor->operator[](x+6)  = d.s1.thermodynamic_forces[3];  \
	mfrontStressTensor->operator[](x+7)  = d.s1.thermodynamic_forces[3];  \
	mfrontStressTensor->operator[](x+8)  = d.s1.thermodynamic_forces[3];



/*  
    2D material Tensor Logic

            mfrontMaterialTensor->operator[](indexMtTensor)    = d.K[0];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +1) = d.K[0];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +2) = d.K[0];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)

            mfrontMaterialTensor->operator[](indexMtTensor+3) = d.K[1];  //  Mt_12 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor+4) = d.K[1];  //  Mt_12 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor+5) = d.K[1];  //  Mt_12 Quadrature point 1 (3 Quad points per tria)

            mfrontMaterialTensor->operator[](indexMtTensor+6) = d.K[3];  //  Mt_13 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor+7) = d.K[3];  //  Mt_13 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor+8) = d.K[3];  //  Mt_13 Quadrature point 1 (3 Quad points per tria)

            mfrontMaterialTensor->operator[](indexMtTensor+9)  = d.K[5];  //  Mt_22 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor+10) = d.K[5];  //  Mt_22 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor+11) = d.K[5];  //  Mt_22 Quadrature point 1 (3 Quad points per tria)

            mfrontMaterialTensor->operator[](indexMtTensor+12) = d.K[7];  //  Mt_23 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor+13) = d.K[7];  //  Mt_23 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor+14) = d.K[7];  //  Mt_23 Quadrature point 1 (3 Quad points per tria)

            mfrontMaterialTensor->operator[](indexMtTensor+15) = d.K[15];  //  Mt_33 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor+16) = d.K[15];  //  Mt_33 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor+17) = d.K[15];  //  Mt_33 Quadrature point 1 (3 Quad points per tria)
*/
            
            
                                    
#define MacroGetStifness2D(x) \
            mfrontMaterialTensor->operator[](x)    = d.K[0];  \
            mfrontMaterialTensor->operator[](x +1) = d.K[0];  \
            mfrontMaterialTensor->operator[](x +2) = d.K[0];  \
                                                              \
            mfrontMaterialTensor->operator[](x+3) = d.K[1];   \
            mfrontMaterialTensor->operator[](x+4) = d.K[1];   \
            mfrontMaterialTensor->operator[](x+5) = d.K[1];   \
                                                              \
            mfrontMaterialTensor->operator[](x+6) = d.K[3];   \
            mfrontMaterialTensor->operator[](x+7) = d.K[3];   \
            mfrontMaterialTensor->operator[](x+8) = d.K[3];   \
                                                              \
            mfrontMaterialTensor->operator[](x+9)  = d.K[5];  \
            mfrontMaterialTensor->operator[](x+10) = d.K[5];  \
            mfrontMaterialTensor->operator[](x+11) = d.K[5];  \
                                                              \
            mfrontMaterialTensor->operator[](x+12) = d.K[7];  \
            mfrontMaterialTensor->operator[](x+13) = d.K[7];  \
            mfrontMaterialTensor->operator[](x+14) = d.K[7];  \
                                                              \
            mfrontMaterialTensor->operator[](x+15) = d.K[15]; \
            mfrontMaterialTensor->operator[](x+16) = d.K[15]; \
            mfrontMaterialTensor->operator[](x+17) = d.K[15];
 
/*  
    3D material Tensor Logic
    
            indexMtTensor  = i*84;  // 21 - components of sym. material tensor and 4 quadrature points per element 4*6= 84    
           
            //------------ row 1 - 6 components -------------------//

            mfrontMaterialTensor->operator[](indexMtTensor +0 ) = d.K[0];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +1 ) = d.K[0];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +2 ) = d.K[0];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +3 ) = d.K[0];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)

            mfrontMaterialTensor->operator[](indexMtTensor +4 ) = d.K[1];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +5 ) = d.K[1];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +6 ) = d.K[1];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +7 ) = d.K[1];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)

            mfrontMaterialTensor->operator[](indexMtTensor +8 ) = d.K[2];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +9) = d.K[2];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +10) = d.K[2];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +11) = d.K[2];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)

            mfrontMaterialTensor->operator[](indexMtTensor +12) = d.K[3];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +13) = d.K[3];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +14) = d.K[3];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +15) = d.K[3];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)

            mfrontMaterialTensor->operator[](indexMtTensor +16) = d.K[4];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +17) = d.K[4];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +18) = d.K[4];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +19) = d.K[4];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)

            mfrontMaterialTensor->operator[](indexMtTensor +20) = d.K[5];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +21) = d.K[5];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +22) = d.K[5];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +23) = d.K[5];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)


            //------------ row 2 - 5 components -------------------//


            mfrontMaterialTensor->operator[](indexMtTensor +24) = d.K[7];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +25) = d.K[7];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +26) = d.K[7];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +27) = d.K[7];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)

            mfrontMaterialTensor->operator[](indexMtTensor +28) = d.K[8];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +29) = d.K[8];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +30) = d.K[8];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +31) = d.K[8];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)

            mfrontMaterialTensor->operator[](indexMtTensor +32) = d.K[9];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +33) = d.K[9];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +34) = d.K[9];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +35) = d.K[9];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)

            mfrontMaterialTensor->operator[](indexMtTensor +36) = d.K[10];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +37) = d.K[10];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +38) = d.K[10];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +39) = d.K[10];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)

            mfrontMaterialTensor->operator[](indexMtTensor +40) = d.K[11];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +41) = d.K[11];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +42) = d.K[11];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +43) = d.K[11];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)

            //------------ row 3 - 4 components -------------------//


            mfrontMaterialTensor->operator[](indexMtTensor +44) = d.K[14];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +45) = d.K[14];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +46) = d.K[14];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +47) = d.K[14];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)

            mfrontMaterialTensor->operator[](indexMtTensor +48) = d.K[15];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +49) = d.K[15];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +50) = d.K[15];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +51) = d.K[15];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)

            mfrontMaterialTensor->operator[](indexMtTensor +52) = d.K[16];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +53) = d.K[16];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +54) = d.K[16];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +55) = d.K[16];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)

            mfrontMaterialTensor->operator[](indexMtTensor +56) = d.K[17];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +57) = d.K[17];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +58) = d.K[17];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +59) = d.K[17];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)

            //------------ row 4 - 3 components -------------------//

            mfrontMaterialTensor->operator[](indexMtTensor +60) = d.K[21];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +61) = d.K[21];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +62) = d.K[21];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +63) = d.K[21];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)

            mfrontMaterialTensor->operator[](indexMtTensor +64) = d.K[22];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +65) = d.K[22];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +66) = d.K[22];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +67) = d.K[22];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)

            mfrontMaterialTensor->operator[](indexMtTensor +68) = d.K[23];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +69) = d.K[23];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +70) = d.K[23];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +71) = d.K[23];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)


            //------------ row 5 - 2 components -------------------//

            mfrontMaterialTensor->operator[](indexMtTensor +72) = d.K[28];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +73) = d.K[28];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +74) = d.K[28];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +75) = d.K[28];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)

            mfrontMaterialTensor->operator[](indexMtTensor +76) = d.K[29];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +77) = d.K[29];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +78) = d.K[29];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +79) = d.K[29];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)

            //------------ row 6 - 1 component -------------------//

            mfrontMaterialTensor->operator[](indexMtTensor +80) = d.K[35];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +81) = d.K[35];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +82) = d.K[35];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +83) = d.K[35];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
*/

#define MacroGetStifness3D(x) \
            mfrontMaterialTensor->operator[](x    ) = d.K[0]; \
            mfrontMaterialTensor->operator[](x +1 ) = d.K[0]; \
            mfrontMaterialTensor->operator[](x +2 ) = d.K[0]; \
            mfrontMaterialTensor->operator[](x +3 ) = d.K[0]; \
            mfrontMaterialTensor->operator[](x +4 ) = d.K[1]; \
            mfrontMaterialTensor->operator[](x +5 ) = d.K[1]; \
            mfrontMaterialTensor->operator[](x +6 ) = d.K[1]; \
            mfrontMaterialTensor->operator[](x +7 ) = d.K[1]; \
            mfrontMaterialTensor->operator[](x +8 ) = d.K[2]; \
            mfrontMaterialTensor->operator[](x +9 ) = d.K[2]; \
            mfrontMaterialTensor->operator[](x +10) = d.K[2]; \
            mfrontMaterialTensor->operator[](x +11) = d.K[2]; \
            mfrontMaterialTensor->operator[](x +12) = d.K[3]; \
            mfrontMaterialTensor->operator[](x +13) = d.K[3]; \
            mfrontMaterialTensor->operator[](x +14) = d.K[3]; \
            mfrontMaterialTensor->operator[](x +15) = d.K[3]; \
            mfrontMaterialTensor->operator[](x +16) = d.K[4]; \
            mfrontMaterialTensor->operator[](x +17) = d.K[4]; \
            mfrontMaterialTensor->operator[](x +18) = d.K[4]; \
            mfrontMaterialTensor->operator[](x +19) = d.K[4]; \
            mfrontMaterialTensor->operator[](x +20) = d.K[5]; \
            mfrontMaterialTensor->operator[](x +21) = d.K[5]; \
            mfrontMaterialTensor->operator[](x +22) = d.K[5]; \
            mfrontMaterialTensor->operator[](x +23) = d.K[5]; \
            mfrontMaterialTensor->operator[](x +24) = d.K[7]; \
            mfrontMaterialTensor->operator[](x +25) = d.K[7]; \
            mfrontMaterialTensor->operator[](x +26) = d.K[7]; \
            mfrontMaterialTensor->operator[](x +27) = d.K[7]; \
            mfrontMaterialTensor->operator[](x +28) = d.K[8]; \
            mfrontMaterialTensor->operator[](x +29) = d.K[8]; \
            mfrontMaterialTensor->operator[](x +30) = d.K[8]; \
            mfrontMaterialTensor->operator[](x +31) = d.K[8]; \
            mfrontMaterialTensor->operator[](x +32) = d.K[9]; \
            mfrontMaterialTensor->operator[](x +33) = d.K[9]; \
            mfrontMaterialTensor->operator[](x +34) = d.K[9]; \
            mfrontMaterialTensor->operator[](x +35) = d.K[9]; \
            mfrontMaterialTensor->operator[](x +36) = d.K[10]; \
            mfrontMaterialTensor->operator[](x +37) = d.K[10]; \
            mfrontMaterialTensor->operator[](x +38) = d.K[10]; \
            mfrontMaterialTensor->operator[](x +39) = d.K[10]; \
            mfrontMaterialTensor->operator[](x +40) = d.K[11]; \
            mfrontMaterialTensor->operator[](x +41) = d.K[11]; \
            mfrontMaterialTensor->operator[](x +42) = d.K[11]; \
            mfrontMaterialTensor->operator[](x +43) = d.K[11]; \
            mfrontMaterialTensor->operator[](x +44) = d.K[14]; \
            mfrontMaterialTensor->operator[](x +45) = d.K[14]; \
            mfrontMaterialTensor->operator[](x +46) = d.K[14]; \
            mfrontMaterialTensor->operator[](x +47) = d.K[14]; \
            mfrontMaterialTensor->operator[](x +48) = d.K[15]; \
            mfrontMaterialTensor->operator[](x +49) = d.K[15]; \
            mfrontMaterialTensor->operator[](x +50) = d.K[15]; \
            mfrontMaterialTensor->operator[](x +51) = d.K[15]; \
            mfrontMaterialTensor->operator[](x +52) = d.K[16]; \
            mfrontMaterialTensor->operator[](x +53) = d.K[16]; \
            mfrontMaterialTensor->operator[](x +54) = d.K[16]; \
            mfrontMaterialTensor->operator[](x +55) = d.K[16]; \
            mfrontMaterialTensor->operator[](x +56) = d.K[17]; \
            mfrontMaterialTensor->operator[](x +57) = d.K[17]; \
            mfrontMaterialTensor->operator[](x +58) = d.K[17]; \
            mfrontMaterialTensor->operator[](x +59) = d.K[17]; \
            mfrontMaterialTensor->operator[](x +60) = d.K[21]; \
            mfrontMaterialTensor->operator[](x +61) = d.K[21]; \
            mfrontMaterialTensor->operator[](x +62) = d.K[21]; \
            mfrontMaterialTensor->operator[](x +63) = d.K[21]; \
            mfrontMaterialTensor->operator[](x +64) = d.K[22]; \
            mfrontMaterialTensor->operator[](x +65) = d.K[22]; \
            mfrontMaterialTensor->operator[](x +66) = d.K[22]; \
            mfrontMaterialTensor->operator[](x +67) = d.K[22]; \
            mfrontMaterialTensor->operator[](x +68) = d.K[23]; \
            mfrontMaterialTensor->operator[](x +69) = d.K[23]; \
            mfrontMaterialTensor->operator[](x +70) = d.K[23]; \
            mfrontMaterialTensor->operator[](x +71) = d.K[23]; \
            mfrontMaterialTensor->operator[](x +72) = d.K[28]; \
            mfrontMaterialTensor->operator[](x +73) = d.K[28]; \
            mfrontMaterialTensor->operator[](x +74) = d.K[28]; \
            mfrontMaterialTensor->operator[](x +75) = d.K[28]; \
            mfrontMaterialTensor->operator[](x +76) = d.K[29]; \
            mfrontMaterialTensor->operator[](x +77) = d.K[29]; \
            mfrontMaterialTensor->operator[](x +78) = d.K[29]; \
            mfrontMaterialTensor->operator[](x +79) = d.K[29]; \
            mfrontMaterialTensor->operator[](x +80) = d.K[35]; \
            mfrontMaterialTensor->operator[](x +81) = d.K[35]; \
            mfrontMaterialTensor->operator[](x +82) = d.K[35]; \
            mfrontMaterialTensor->operator[](x +83) = d.K[35];
            
/*
    3D strain  Tensor Logic

            indexEx  = i*24         ;
                
            d.s1.gradients[0] = mfrontStrainTensor->operator[](indexEx)  ;  //E11
            d.s1.gradients[1] = mfrontStrainTensor->operator[](indexEx+4);  //E22
            d.s1.gradients[2] = mfrontStrainTensor->operator[](indexEx+8);  //E33
            d.s1.gradients[3] = mfrontStrainTensor->operator[](indexEx+12); //E12
            d.s1.gradients[4] = mfrontStrainTensor->operator[](indexEx+16); //E13
            d.s1.gradients[5] = mfrontStrainTensor->operator[](indexEx+20); //E23
*/

#define MacroSetGradient3D(x)  \
            d.s1.gradients[0] = mfrontStrainTensor->operator[](indexEx)  ;  \
            d.s1.gradients[1] = mfrontStrainTensor->operator[](indexEx+4);  \
            d.s1.gradients[2] = mfrontStrainTensor->operator[](indexEx+8);  \
            d.s1.gradients[3] = mfrontStrainTensor->operator[](indexEx+12); \
            d.s1.gradients[4] = mfrontStrainTensor->operator[](indexEx+16); \
            d.s1.gradients[5] = mfrontStrainTensor->operator[](indexEx+20);
            
/*
    3D stress  Tensor Logic

            indexEx  = i*24         ;
            
            mfrontStressTensor->operator[](indexEx)    = d.s1.thermodynamic_forces[0]; // sig_xx
            mfrontStressTensor->operator[](indexEx+1)  = d.s1.thermodynamic_forces[0]; // sig_xx
            mfrontStressTensor->operator[](indexEx+2)  = d.s1.thermodynamic_forces[0]; // sig_xx
            mfrontStressTensor->operator[](indexEx+3)  = d.s1.thermodynamic_forces[0]; // sig_xx

            mfrontStressTensor->operator[](indexEx+4)  = d.s1.thermodynamic_forces[1]; // sig_yy
            mfrontStressTensor->operator[](indexEx+5)  = d.s1.thermodynamic_forces[1]; // sig_yy
            mfrontStressTensor->operator[](indexEx+6)  = d.s1.thermodynamic_forces[1]; // sig_yy
            mfrontStressTensor->operator[](indexEx+7)  = d.s1.thermodynamic_forces[1]; // sig_yy

            mfrontStressTensor->operator[](indexEx+8)  = d.s1.thermodynamic_forces[2];  // sig_zz
            mfrontStressTensor->operator[](indexEx+9)  = d.s1.thermodynamic_forces[2];  // sig_zz
            mfrontStressTensor->operator[](indexEx+10)  = d.s1.thermodynamic_forces[2]; // sig_zz
            mfrontStressTensor->operator[](indexEx+11)  = d.s1.thermodynamic_forces[2]; // sig_zz

            mfrontStressTensor->operator[](indexEx+12)  = d.s1.thermodynamic_forces[3]; // sig_xy
            mfrontStressTensor->operator[](indexEx+13)  = d.s1.thermodynamic_forces[3]; // sig_xy
            mfrontStressTensor->operator[](indexEx+14)  = d.s1.thermodynamic_forces[3]; // sig_xy
            mfrontStressTensor->operator[](indexEx+15)  = d.s1.thermodynamic_forces[3]; // sig_xy

            mfrontStressTensor->operator[](indexEx+16)  = d.s1.thermodynamic_forces[4]; // sig_xz
            mfrontStressTensor->operator[](indexEx+17)  = d.s1.thermodynamic_forces[4]; // sig_xz
            mfrontStressTensor->operator[](indexEx+18)  = d.s1.thermodynamic_forces[4]; // sig_xz
            mfrontStressTensor->operator[](indexEx+19)  = d.s1.thermodynamic_forces[4]; // sig_xz

            mfrontStressTensor->operator[](indexEx+20)  = d.s1.thermodynamic_forces[5]; // sig_yz
            mfrontStressTensor->operator[](indexEx+21)  = d.s1.thermodynamic_forces[5]; // sig_yz
            mfrontStressTensor->operator[](indexEx+22)  = d.s1.thermodynamic_forces[5]; // sig_yz
            mfrontStressTensor->operator[](indexEx+23)  = d.s1.thermodynamic_forces[5]; // sig_yz
*/

#define MacroGetSress3D(x) \
            mfrontStressTensor->operator[](indexEx)    = d.s1.thermodynamic_forces[0]; \
            mfrontStressTensor->operator[](indexEx+1)  = d.s1.thermodynamic_forces[0]; \
            mfrontStressTensor->operator[](indexEx+2)  = d.s1.thermodynamic_forces[0]; \
            mfrontStressTensor->operator[](indexEx+3)  = d.s1.thermodynamic_forces[0]; \
                                                                                       \
            mfrontStressTensor->operator[](indexEx+4)  = d.s1.thermodynamic_forces[1]; \
            mfrontStressTensor->operator[](indexEx+5)  = d.s1.thermodynamic_forces[1]; \
            mfrontStressTensor->operator[](indexEx+6)  = d.s1.thermodynamic_forces[1]; \
            mfrontStressTensor->operator[](indexEx+7)  = d.s1.thermodynamic_forces[1]; \
                                                                                       \
            mfrontStressTensor->operator[](indexEx+8)  = d.s1.thermodynamic_forces[2]; \
            mfrontStressTensor->operator[](indexEx+9)  = d.s1.thermodynamic_forces[2]; \
            mfrontStressTensor->operator[](indexEx+10)  = d.s1.thermodynamic_forces[2];\
            mfrontStressTensor->operator[](indexEx+11)  = d.s1.thermodynamic_forces[2];\
                                                                                       \
            mfrontStressTensor->operator[](indexEx+12)  = d.s1.thermodynamic_forces[3];\
            mfrontStressTensor->operator[](indexEx+13)  = d.s1.thermodynamic_forces[3];\
            mfrontStressTensor->operator[](indexEx+14)  = d.s1.thermodynamic_forces[3];\
            mfrontStressTensor->operator[](indexEx+15)  = d.s1.thermodynamic_forces[3];\
                                                                                       \
            mfrontStressTensor->operator[](indexEx+16)  = d.s1.thermodynamic_forces[4];\
            mfrontStressTensor->operator[](indexEx+17)  = d.s1.thermodynamic_forces[4];\
            mfrontStressTensor->operator[](indexEx+18)  = d.s1.thermodynamic_forces[4];\
            mfrontStressTensor->operator[](indexEx+19)  = d.s1.thermodynamic_forces[4];\
                                                                                       \
            mfrontStressTensor->operator[](indexEx+20)  = d.s1.thermodynamic_forces[5];\
            mfrontStressTensor->operator[](indexEx+21)  = d.s1.thermodynamic_forces[5];\
            mfrontStressTensor->operator[](indexEx+22)  = d.s1.thermodynamic_forces[5];\
            mfrontStressTensor->operator[](indexEx+23)  = d.s1.thermodynamic_forces[5];
                                                      
