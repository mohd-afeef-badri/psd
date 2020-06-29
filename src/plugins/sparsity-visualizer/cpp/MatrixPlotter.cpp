#include <iostream>
#include <fstream>
#include <math.h>
#include <cstdio>

using namespace std;

#include "ff++.hpp"


template<class K>
class MatViz_Op : public E_F0mps {
    public:
        Expression matrix;
        static const int n_name_param = 0;
        static basicAC_F0::name_and_type name_param[];
        Expression nargs[n_name_param];
        MatViz_Op(const basicAC_F0&  args, Expression param1) : matrix(param1) {
            args.SetNameParam(n_name_param, name_param, nargs);
        }
        AnyType operator()(Stack stack) const;
};

template<class K>
basicAC_F0::name_and_type MatViz_Op<K>::name_param[] = { };

template<class K>
class MatViz : public OneOperator {
    public:
        MatViz() : OneOperator(atype<long>(), atype<Matrice_Creuse<K>*>()) {}

        E_F0* code(const basicAC_F0& args) const {
            return new MatViz_Op<K>(args, t[0]->CastTo(args[0]));
        }
};


template<class K>
AnyType MatViz_Op<K>::operator()(Stack stack)  const {
    Matrice_Creuse<K>* ptMat = GetAny<Matrice_Creuse<K>*>((*matrix)(stack));

    {ofstream wrt("mat.dat");
    wrt << *ptMat << endl;}

    #include "../lib/gnuCommands.hpp"

   system ("gnuplot style.gnu -p");
   
   //system ("pdflatex out.tex");
   //system ("rm mat.dat");
   //system ("rm style.gnu");
    return 0L;
}

static void Init_MatViz() {
    Global.Add("MatViz", "(", new MatViz<double>);
}

LOADFUNC(Init_MatViz)
