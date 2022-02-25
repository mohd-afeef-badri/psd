/**************************************************************************************
*                                                                                     *
* Author : Mohd Afeef BADRI                                                           *
* Email  : mohd-afeef.badri@cea.fr                                                    *
* Date   : 25/02/2020                                                                 *
* Type   : Support file                                                               *
*                                                                                     *
* Comment: This support  file is responsible for generating startProcedure and        *
*          endProcedure macros that are evaluated at compile-time in.                *
*                                                                                     *
**************************************************************************************/


codeSnippet R""""(

//=============================================================================
//            ------ Start and End procedure macros  -------
// -------------------------------------------------------------------
//    Note these macros will print on screen a message at the start
//    and end of a procedure, and also print the time taken by that
//    procedure in seconds. However, -timelog flag needs to be used
//    for this macro, or else this macro will serve as a dummy macro.
// -------------------------------------------------------------------
//=============================================================================

)"""";


if(timelog){

if(!Sequential)
{
codeSnippet R""""(

//==============================================================================
// ------- startProcedure (string , real) -------
//==============================================================================

  macro startProcedure(str1,t0){
    mpiBarrier(mpiCommWorld);
    t0 = mpiWtime();
    if(mpirank==0)
    cout << "-->"+str1+" began....\n";
  }//

//==============================================================================
// ------- endProcedure (string , real) -------
//==============================================================================

  macro endProcedure(str1,t0){
    mpiBarrier(mpiCommWorld);
    if(mpirank==0)
    cout.scientific << "finished in [ "
                    << mpiWtime()-t0
                    << " ] seconds\n\n";
  }//

)"""";
}

if(Sequential)
{
codeSnippet R""""(

//==============================================================================
// ------- startProcedure (string , real) -------
//==============================================================================

  macro startProcedure(str1,t0){
    t0 = clock();
    cout << "-->"+str1+" began....\n";
  }//

//==============================================================================
// ------- endProcedure (string , real) -------
//==============================================================================

  macro endProcedure(str1,t0){
    cout.scientific << "finished in [ "
                    << clock()-t0
                    << " ] seconds\n\n";
  }//

)"""";
}

}

if(!timelog){

codeSnippet R""""(

//==============================================================================
// ------- startProcedure (string , real) is a DUMMY macro -------
//==============================================================================

  macro startProcedure(str1,t0){}//

//==============================================================================
// ------- endProcedure (string , real) is a DUMMY macro  -------
//==============================================================================

  macro endProcedure(str1,t0){}//

)"""";

}
