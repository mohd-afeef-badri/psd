# Validation test for Iwan law #

Iwan law is used for modeling the non-linear behavior in soil dynamics. PSD provides this law by its MFront interface. In this file the results and other key information concerning the validation numerical experiments conducted for PSD-MFront Iwan law is presented. 

### Facts ###

- $\epsilon_{i,j}^{MFront} = (1/\sqrt{2}) \epsilon_{i,j}, \quad i\ne j$
- $\sigma_{i,j}^{MFront} = (1/\sqrt{2}) \sigma_{i,j}, \quad i\ne j$
- $\epsilon_{i,j}^{MFront}  = (1/\sqrt{2})\gamma_{i,j}^{CAST\epsilon M} , \quad i\ne j$

### Notes ###

- decimal problem does not seem to be effected if values of $C[N_s]$ and $Y[N_s]$ are input in MFront file or via PSD interface. 

## To Do

- Mtest file from Reine -> Afeef
- Correct the decimal problem
- Reine veirify MFront error 
- Complete the file with maths behind