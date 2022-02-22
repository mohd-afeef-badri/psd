split=4
N=1
np=4
ksppar=
file=blabla
ffpar=

run:
	sed "s#SPLITNUMBER#$(split)#g" mbatch-temp-IRENE.sh > launchscript.mbatch && \
	sed -i "s#NODES#$(N)#g" launchscript.mbatch && \
	sed -i "s#KSPPAR#$(ksppar)#g" launchscript.mbatch && \
	sed -i "s#FFPAR#$(ffpar)#g" launchscript.mbatch && \
	sed -i "s#MPIPROC#$(np)#g" launchscript.mbatch && \
	sed -i "s#OUTFILE#$(file)_np-$(np)_N-$(N)#g" launchscript.mbatch && \
	ccc_msub launchscript.mbatch  && \
	echo "done"
