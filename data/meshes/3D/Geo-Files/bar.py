#!/usr/bin/env python

###
### This file is generated automatically by SALOME v9.9.0 with dump python functionality
###

import sys
import salome

salome.salome_init()

###
### SHAPER component
###

from salome.shaper import model

model.begin()
partSet = model.moduleDocument()

### Create Part
Part_1 = model.addPart(partSet)
Part_1_doc = Part_1.document()

### Create Box
Box_1 = model.addBox(Part_1_doc, 5, 1, 1)

### Create Group
Group_1 = model.addGroup(Part_1_doc, "Faces", [model.selection("FACE", "Box_1_1/Back")])
Group_1.setName("left")
Group_1.result().setName("left")

### Create Group
Group_2 = model.addGroup(Part_1_doc, "Faces", [model.selection("FACE", "Box_1_1/Front")])
Group_2.setName("right")
Group_2.result().setName("right")

### Create Group
Group_3 = model.addGroup(Part_1_doc, "Faces", [model.selection("FACE", "Box_1_1/Top")])
Group_3.setName("top")
Group_3.result().setName("top")

### Create Group
Group_4 = model.addGroup(Part_1_doc, "Faces", [model.selection("FACE", "Box_1_1/Bottom")])
Group_4.setName("bot")
Group_4.result().setName("bot")

### Create Group
Group_5 = model.addGroup(Part_1_doc, "Faces", [model.selection("FACE", "Box_1_1/Left"), model.selection("FACE", "Box_1_1/Right")])
Group_5.setName("other")
Group_5.result().setName("other")

### Create Group
Group_6 = model.addGroup(Part_1_doc, "Solids", [model.selection("SOLID", "Box_1_1")])
Group_6.setName("vol")
Group_6.result().setName("vol")

model.end()

###
### SHAPERSTUDY component
###

model.publishToShaperStudy()
import SHAPERSTUDY
Box_1_1, left, right, top, bot, other, vol, = SHAPERSTUDY.shape(model.featureStringId(Box_1))
###
### SMESH component
###

import  SMESH, SALOMEDS
from salome.smesh import smeshBuilder

h= 0.03

smesh = smeshBuilder.New()
#smesh.SetEnablePublish( False ) # Set to False to avoid publish in study if not needed or in some particular situations:
                                 # multiples meshes built in parallel, complex and numerous mesh edition (performance)

Mesh_1 = smesh.Mesh(Box_1_1,'Mesh_1')
'''
NETGEN_1D_2D_3D = Mesh_1.Tetrahedron(algo=smeshBuilder.NETGEN_1D2D3D)
NETGEN_3D_Parameters_1 = NETGEN_1D_2D_3D.Parameters()
NETGEN_3D_Parameters_1.SetMaxSize( h )
NETGEN_3D_Parameters_1.SetMinSize( h )
NETGEN_3D_Parameters_1.SetSecondOrder( 0 )
NETGEN_3D_Parameters_1.SetOptimize( 1 )
NETGEN_3D_Parameters_1.SetFineness( 2 )
NETGEN_3D_Parameters_1.SetChordalError( -1 )
NETGEN_3D_Parameters_1.SetChordalErrorEnabled( 0 )
NETGEN_3D_Parameters_1.SetUseSurfaceCurvature( 1 )
NETGEN_3D_Parameters_1.SetFuseEdges( 1 )
NETGEN_3D_Parameters_1.SetQuadAllowed( 0 )
NETGEN_3D_Parameters_1.SetCheckChartBoundary( 3 )
left_1 = Mesh_1.GroupOnGeom(left,'left',SMESH.FACE)
right_1 = Mesh_1.GroupOnGeom(right,'right',SMESH.FACE)
top_1 = Mesh_1.GroupOnGeom(top,'top',SMESH.FACE)
bot_1 = Mesh_1.GroupOnGeom(bot,'bot',SMESH.FACE)
other_1 = Mesh_1.GroupOnGeom(other,'other',SMESH.FACE)
vol_1 = Mesh_1.GroupOnGeom(vol,'vol',SMESH.VOLUME)
isDone = Mesh_1.Compute()
[ left_1, right_1, top_1, bot_1, other_1, vol_1 ] = Mesh_1.GetGroups()
smesh.SetName(Mesh_1, 'Mesh_1')
try:
  Mesh_1.ExportMED( r'./bar_NetGen.med', 0, 41, 1, Mesh_1, 1, [], '',-1, 1 )
  pass
except:
  print('ExportPartToMED() failed. Invalid file name?')
 '''
Mesh_2 = smesh.Mesh(Box_1_1,'Mesh_2')
MG_Tetra = Mesh_2.Tetrahedron(algo=smeshBuilder.MG_Tetra)
MG_Tetra_Parameters_1 = MG_Tetra.Parameters()
MG_Tetra_Parameters_1.SetOptimizationLevel( 2 )
MG_Tetra_Parameters_1.SetMinSize( h )
MG_Tetra_Parameters_1.SetMaxSize( h )
MG_Tetra_Parameters_1.SetToMeshHoles( 0 )
MG_Tetra_Parameters_1.SetToMakeGroupsOfDomains( 0 )
MG_Tetra_Parameters_1.SetMaximumMemory( -1 )
MG_Tetra_Parameters_1.SetInitialMemory( -1 )
MG_Tetra_Parameters_1.SetKeepFiles( 0 )
MG_Tetra_Parameters_1.SetWorkingDirectory( '/tmp/' )
MG_Tetra_Parameters_1.SetVerboseLevel( 10 )
MG_Tetra_Parameters_1.SetStandardOutputLog( 0 )
MG_Tetra_Parameters_1.SetRemoveLogOnSuccess( 0 )
left_2 = Mesh_2.GroupOnGeom(left,'left',SMESH.FACE)
right_2 = Mesh_2.GroupOnGeom(right,'right',SMESH.FACE)
top_2 = Mesh_2.GroupOnGeom(top,'top',SMESH.FACE)
bot_2 = Mesh_2.GroupOnGeom(bot,'bot',SMESH.FACE)
other_2 = Mesh_2.GroupOnGeom(other,'other',SMESH.FACE)
vol_2 = Mesh_2.GroupOnGeom(vol,'vol',SMESH.VOLUME)
isDone = Mesh_2.Compute()
[ left_2, right_2, top_2, bot_2, other_2, vol_2 ] = Mesh_2.GetGroups()
MG_CADSurf = Mesh_2.Triangle(algo=smeshBuilder.MG_CADSurf)
MG_CADSurf_Parameters_1 = MG_CADSurf.Parameters()
MG_CADSurf_Parameters_1.SetPhySize( h)
MG_CADSurf_Parameters_1.SetMinSize( h )
MG_CADSurf_Parameters_1.SetMaxSize( h )
MG_CADSurf_Parameters_1.SetChordalError( 0.259808 )
isDone = Mesh_2.Compute()
[ left_2, right_2, top_2, bot_2, other_2, vol_2 ] = Mesh_2.GetGroups()
smesh.SetName(Mesh_2, 'Mesh_2')
try:
  Mesh_2.ExportMED( r'./bar_MG.med', 0, 41, 1, Mesh_2, 1, [], '',-1, 1 )
  pass
except:
  print('ExportPartToMED() failed. Invalid file name?')


## Set names of Mesh objects
smesh.SetName(bot_2, 'bot')
smesh.SetName(other_2, 'other')
smesh.SetName(right_2, 'right')
smesh.SetName(top_2, 'top')
smesh.SetName(left_2, 'left')
smesh.SetName(NETGEN_1D_2D_3D.GetAlgorithm(), 'NETGEN 1D-2D-3D')
smesh.SetName(MG_Tetra.GetAlgorithm(), 'MG-Tetra')
smesh.SetName(MG_CADSurf.GetAlgorithm(), 'MG-CADSurf')
smesh.SetName(left_1, 'left')
smesh.SetName(vol_1, 'vol')
smesh.SetName(top_1, 'top')
smesh.SetName(right_1, 'right')
smesh.SetName(other_1, 'other')
smesh.SetName(bot_1, 'bot')
smesh.SetName(Mesh_1.GetMesh(), 'Mesh_1')
smesh.SetName(Mesh_2.GetMesh(), 'Mesh_2')
smesh.SetName(MG_CADSurf_Parameters_1, 'MG-CADSurf Parameters_1')
smesh.SetName(MG_Tetra_Parameters_1, 'MG-Tetra Parameters_1')
smesh.SetName(NETGEN_3D_Parameters_1, 'NETGEN 3D Parameters_1')
smesh.SetName(vol_2, 'vol')


if salome.sg.hasDesktop():
  salome.sg.updateObjBrowser()
