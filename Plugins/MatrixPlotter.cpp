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

   {ofstream script ("style.gnu");
   //script<<" set terminal tikz standalone" <<endl;
   script<<" set terminal pdfcairo enhanced color lw 3 size 3,2 font 'Arial-Bold'" <<endl;  
   script<<" set output 'matrix.pdf'" <<endl;  
   script<<" a=system(\"cat -n mat.dat | awk '{if ($1 == 3) print $2}'\")" << endl; 
   script<<" b=system(\"cat -n mat.dat | awk '{if ($1 == 3) print $5}'\")" << endl; 
   script<<" set tics nomirror out scale 0.75" <<endl;
   script<<" set size ratio -1 \n set xtics rotate" <<endl;
   script<<" set palette defined (0 0 0 0, 1 0 0 1, 3 0 1 0, 4 1 0 0, 6 1 1 1)" <<endl;
   script<<" f(x) = x>0 ? x : 1./10 " <<endl;
   script<<" set style fill transparent solid 0.8 noborder" <<endl;
   script<<" set yrange [a+1:-1]" <<endl;
   script<<" set xrange [-1:a+1]" <<endl;
   script<<" set title ' '"<<endl;
   script<<" plot '<sort -g -k3 mat.dat' u 1:2:(0.6):(f($3)) w circles lc palette t ''" <<endl;
   }

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
