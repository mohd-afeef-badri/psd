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
	$(FF) gofastplugins.edp
	$(FF) gofastplugins_GFPeigenAlone.edp 
	$(FF) gofastplugins_GFPeigen.edp 
	$(FF) iovtk.edp 
	$(FF) MatrixPlotter.edp 
	$(FF) top-ii-vol.edp 
	$(FFMPI) -np 2 top-ii-vol.edp 	
	$(FFMPI) -np 2 top-ii-vol_partitioningAndMeshingAndReconstruction.edp 
	$(FFMPI) -np 2 top-ii-vol_partitioningAndMeshing.edp 
	$(FFMPI) -np 2 top-ii-vol_partitioning.edp
	
clean-local:
	@echo ""
	@echo "*============================================================*"
	@echo " Cleaning files in :"; pwd
	@echo "*============================================================*"
	@echo ""	
	rm  -f *~ *.mesh *.pvd *.vtu *.info *.pdf *.xyz *.dat *.gnu
