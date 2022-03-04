#!/usr/bin/env python

###
### This file is generated automatically by SALOME v9.8.0 with dump python functionality
###

import sys
import salome

salome.salome_init()
import salome_notebook
notebook = salome_notebook.NoteBook()
sys.path.insert(0, r'/home/mb258512/Work/repo/psd_sources/data/meshes/3D/Geo-Files')

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
Box_1 = model.addBox(Part_1_doc, 10, 10, 100)

### Create Solid
Solid_1 = model.addSolid(Part_1_doc, [model.selection("SHELL", "[Box_1_1/Back][Box_1_1/Front][Box_1_1/Left][Box_1_1/Right][Box_1_1/Bottom][Box_1_1/Top]")])

### Create Group
Group_1 = model.addGroup(Part_1_doc, "Faces", [model.selection("FACE", "Box_1_1/Top")])
Group_1.setName("top")
Group_1.result().setName("top")

### Create Group
Group_2_objects = [model.selection("FACE", "Box_1_1/Left"),
                   model.selection("FACE", "Box_1_1/Front"),
                   model.selection("FACE", "Box_1_1/Right"),
                   model.selection("FACE", "Box_1_1/Back")]
Group_2 = model.addGroup(Part_1_doc, "Faces", Group_2_objects)
Group_2.setName("other")
Group_2.result().setName("other")

### Create Group
Group_3 = model.addGroup(Part_1_doc, "Faces", [model.selection("FACE", "Box_1_1/Bottom")])
Group_3.setName("bot")
Group_3.result().setName("bot")

### Create Group
Group_4 = model.addGroup(Part_1_doc, "Solids", [model.selection("SOLID", "Solid_1_1")])
Group_4.setName("vol")
Group_4.result().setName("vol")

model.end()

###
### SHAPERSTUDY component
###

model.publishToShaperStudy()
import SHAPERSTUDY
Solid_1_1, top, other, bot, vol, = SHAPERSTUDY.shape(model.featureStringId(Solid_1))
###
### SMESH component
###

import  SMESH, SALOMEDS
from salome.smesh import smeshBuilder

smesh = smeshBuilder.New()
#smesh.SetEnablePublish( False ) # Set to False to avoid publish in study if not needed or in some particular situations:
                                 # multiples meshes built in parallel, complex and numerous mesh edition (performance)

Mesh_1 = smesh.Mesh(Solid_1_1)
NETGEN_1D_2D_3D = Mesh_1.Tetrahedron(algo=smeshBuilder.NETGEN_1D2D3D)
NETGEN_3D_Simple_Parameters_1 = NETGEN_1D_2D_3D.Parameters(smeshBuilder.SIMPLE)
NETGEN_3D_Simple_Parameters_1.SetNumberOfSegments( 15 )
NETGEN_3D_Simple_Parameters_1.LengthFromEdges()
NETGEN_3D_Simple_Parameters_1.LengthFromFaces()
top_1 = Mesh_1.GroupOnGeom(top,'top',SMESH.FACE)
other_1 = Mesh_1.GroupOnGeom(other,'other',SMESH.FACE)
bot_1 = Mesh_1.GroupOnGeom(bot,'bot',SMESH.FACE)
vol_1 = Mesh_1.GroupOnGeom(vol,'vol',SMESH.VOLUME)
isDone = Mesh_1.Compute()
[ top_1, other_1, bot_1, vol_1 ] = Mesh_1.GetGroups()
status = Mesh_1.RemoveHypothesis(NETGEN_3D_Simple_Parameters_1)
NETGEN_3D_Parameters_1 = NETGEN_1D_2D_3D.Parameters()
NETGEN_3D_Parameters_1.SetMaxSize( 5 )
NETGEN_3D_Parameters_1.SetMinSize( 5 )
NETGEN_3D_Parameters_1.SetSecondOrder( 0 )
NETGEN_3D_Parameters_1.SetOptimize( 1 )
NETGEN_3D_Parameters_1.SetFineness( 2 )
NETGEN_3D_Parameters_1.SetChordalError( -1 )
NETGEN_3D_Parameters_1.SetChordalErrorEnabled( 0 )
NETGEN_3D_Parameters_1.SetUseSurfaceCurvature( 1 )
NETGEN_3D_Parameters_1.SetFuseEdges( 1 )
NETGEN_3D_Parameters_1.SetQuadAllowed( 0 )
NETGEN_3D_Parameters_1.SetCheckChartBoundary( 192 )
isDone = Mesh_1.Compute()
[ top_1, other_1, bot_1, vol_1 ] = Mesh_1.GetGroups()
smesh.SetName(Mesh_1, 'Mesh_1')
try:
  Mesh_1.ExportMED( r'/home/mb258512/Work/repo/psd_sources/data/meshes/3D/Geo-Files/Mesh_bar.med', 0, 41, 1, Mesh_1, 1, [], '',-1, 1 )
  pass
except:
  print('ExportPartToMED() failed. Invalid file name?')


## Set names of Mesh objects
smesh.SetName(NETGEN_1D_2D_3D.GetAlgorithm(), 'NETGEN 1D-2D-3D')
smesh.SetName(top_1, 'top')
smesh.SetName(vol_1, 'vol')
smesh.SetName(bot_1, 'bot')
smesh.SetName(other_1, 'other')
smesh.SetName(Mesh_1.GetMesh(), 'Mesh_1')
smesh.SetName(NETGEN_3D_Parameters_1, 'NETGEN 3D Parameters_1')
smesh.SetName(NETGEN_3D_Simple_Parameters_1, 'NETGEN 3D Simple Parameters_1')


if salome.sg.hasDesktop():
  salome.sg.updateObjBrowser()
