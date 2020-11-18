LIST_COMPILE= gofastplugins.edp \
gofastplugins_GFPeigenAlone.edp \
gofastplugins_GFPeigen.edp \
iovtk.edp \
MatrixPlotter.edp \
top-ii-vol.edp \
top-ii-vol_partitioningAndMeshingAndReconstruction.edp \
top-ii-vol_partitioningAndMeshing.edp \
top-ii-vol_partitioning.edp


all-local: 
	@echo ""
	
check-local: gofastplugins.edp
	@echo ""
	@echo "*============================================================*"
	@echo " Checking gofastplugins plugin                                "
	@echo "*============================================================*"
	@echo ""
	./../../src/psd-solve/PSD_Solve gofastplugins.edp > PSD-check.log
	./../../src/psd-solve/PSD_Solve gofastplugins_GFPeigenAlone.edp  >> PSD-check.log
	./../../src/psd-solve/PSD_Solve gofastplugins_GFPeigen.edp >> PSD-check.log
	@echo ""
	@echo "*============================================================*"
	@echo " Checking iovtk  plugin                                       "
	@echo "*============================================================*"
	@echo ""	 
	./../../src/psd-solve/PSD_Solve iovtk.edp >> PSD-check.log
	@echo ""
	@echo "*============================================================*"
	@echo " Checking MatrixPlotter  plugin                               "
	@echo "*============================================================*"
	@echo ""		 
	./../../src/psd-solve/PSD_Solve MatrixPlotter.edp >> PSD-check.log
	@echo ""
	@echo "*============================================================*"
	@echo " Checking top-ii-vol  plugin                                  "
	@echo "*============================================================*"
	@echo ""	
	./../../src/psd-solve/PSD_Solve top-ii-vol.edp >> PSD-check.log
	./../../src/psd-solve/PSD_Solve -np 2 top-ii-vol.edp  >> PSD-check.log	
	./../../src/psd-solve/PSD_Solve -np 2 top-ii-vol_partitioningAndMeshingAndReconstructionX.edp  >> PSD-check.log
	./../../src/psd-solve/PSD_Solve -np 2 top-ii-vol_partitioningAndMeshingAndReconstructionY.edp  >> PSD-check.log
	./../../src/psd-solve/PSD_Solve -np 2 top-ii-vol_partitioningAndMeshingAndReconstructionZ.edp  >> PSD-check.log
	./../../src/psd-solve/PSD_Solve -np 2 top-ii-vol_partitioningAndMeshing.edp >> PSD-check.log
	./../../src/psd-solve/PSD_Solve -np 2 top-ii-vol_partitioning.edp	>> PSD-check.log
	@echo ""
	@echo "*============================================================*"
	@echo " Checking soil-laws  plugin                                  "
	@echo "*============================================================*"
	@echo ""		 
	./../../src/psd-solve/PSD_Solve soil-laws.edp >> PSD-check.log
	./../../src/psd-solve/PSD_Solve soil-laws_hujeux.edp  >> PSD-check.log		 	
	./../../src/psd-solve/PSD_Solve -np 2 soil-laws.edp >> PSD-check.log
	./../../src/psd-solve/PSD_Solve -np 2 soil-laws_hujeux.edp >> PSD-check.log
	
hujeux: soil-laws_hujeux.edp 	soil-laws.edp
	@echo ""
	@echo "*============================================================*"
	@echo " Checking Hujeux soil-law plugin                              "
	@echo "*============================================================*"
	@echo ""
	./../../src/psd-solve/PSD_Solve -np 2 soil-laws_hujeux.edp -v 0
	
clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""	
	rm  -f *~ *.mesh *.pvd *.vtu *.info *.pdf *.xyz *.dat *.gnu *.output
	rm  -f *~ *.log	
	

maintainer-clean-local: clean-local
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning automake generated files"
	@echo "*============================================================*"
	@echo ""	
	rm  -rf Makefile Makefile.in
