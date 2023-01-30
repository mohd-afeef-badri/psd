#!/usr/bin/env python

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

### Create Sketch
Sketch_1 = model.addSketch(Part_1_doc, model.defaultPlane("XOY"))

### Create SketchPoint
SketchPoint_1 = Sketch_1.addPoint(0, 0)

### Create SketchProjection
SketchProjection_1 = Sketch_1.addProjection(model.selection("VERTEX", "PartSet/Origin"), False)
SketchPoint_2 = SketchProjection_1.createdFeature()
Sketch_1.setCoincident(SketchPoint_1.coordinates(), SketchPoint_2.result())

### Create SketchPoint
SketchPoint_3 = Sketch_1.addPoint(1, 0)

### Create SketchProjection
SketchProjection_2 = Sketch_1.addProjection(model.selection("EDGE", "PartSet/OX"), False)
SketchLine_1 = SketchProjection_2.createdFeature()
Sketch_1.setCoincident(SketchPoint_3.coordinates(), SketchLine_1.result())

### Create SketchPoint
SketchPoint_4 = Sketch_1.addPoint(1.3, 0)
Sketch_1.setCoincident(SketchPoint_4.coordinates(), SketchLine_1.result())

### Create SketchPoint
SketchPoint_5 = Sketch_1.addPoint(0, 1)

### Create SketchProjection
SketchProjection_3 = Sketch_1.addProjection(model.selection("EDGE", "PartSet/OY"), False)
SketchLine_2 = SketchProjection_3.createdFeature()
Sketch_1.setCoincident(SketchPoint_5.coordinates(), SketchLine_2.result())

### Create SketchPoint
SketchPoint_6 = Sketch_1.addPoint(0, 1.3)
Sketch_1.setCoincident(SketchPoint_6.coordinates(), SketchLine_2.result())
Sketch_1.setVerticalDistance(SketchPoint_6.coordinates(), SketchPoint_1.coordinates(), 1.3)
Sketch_1.setHorizontalDistance(SketchPoint_1.coordinates(), SketchPoint_4.coordinates(), 1.3)
Sketch_1.setHorizontalDistance(SketchPoint_3.coordinates(), SketchPoint_4.coordinates(), 0.3)
Sketch_1.setVerticalDistance(SketchPoint_6.coordinates(), SketchPoint_5.coordinates(), 0.3)

### Create SketchArc
SketchArc_1 = Sketch_1.addArc(0, 0, 1, 0, 2.917196034004092e-15, 1, False)
Sketch_1.setCoincident(SketchPoint_1.coordinates(), SketchArc_1.center())
Sketch_1.setCoincident(SketchPoint_3.coordinates(), SketchArc_1.startPoint())
Sketch_1.setCoincident(SketchLine_2.result(), SketchArc_1.endPoint())

### Create SketchArc
SketchArc_2 = Sketch_1.addArc(0, 0, 1.3, 0, -2.911465560568432e-14, 1.300000000023283, False)
Sketch_1.setCoincident(SketchPoint_1.coordinates(), SketchArc_2.center())
Sketch_1.setCoincident(SketchPoint_4.coordinates(), SketchArc_2.startPoint())
Sketch_1.setCoincident(SketchLine_2.result(), SketchArc_2.endPoint())

### Create SketchLine
SketchLine_3 = Sketch_1.addLine(1, 0, 1.3, 0)
Sketch_1.setCoincident(SketchPoint_3.coordinates(), SketchLine_3.startPoint())
Sketch_1.setCoincident(SketchPoint_4.coordinates(), SketchLine_3.endPoint())

### Create SketchLine
SketchLine_4 = Sketch_1.addLine(0, 1, 0, 1.3)
Sketch_1.setCoincident(SketchPoint_5.coordinates(), SketchLine_4.startPoint())
Sketch_1.setCoincident(SketchPoint_6.coordinates(), SketchLine_4.endPoint())
model.do()

### Create Face
Face_1 = model.addFace(Part_1_doc, [model.selection("FACE", "Sketch_1/Face-SketchLine_3f-SketchArc_2_2f-SketchLine_4r-SketchArc_1_2r")])

### Create Group
Group_1 = model.addGroup(Part_1_doc, "Edges", [model.selection("EDGE", "Face_1_1/Modified_Edge&Sketch_1/SketchLine_3")])
Group_1.setName("bot")
Group_1.result().setName("bot")

### Create Group
Group_2 = model.addGroup(Part_1_doc, "Edges", [model.selection("EDGE", "Face_1_1/Modified_Edge&Sketch_1/SketchLine_4")])
Group_2.setName("top")
Group_2.result().setName("top")

### Create Group
Group_3 = model.addGroup(Part_1_doc, "Edges", [model.selection("EDGE", "Face_1_1/Modified_Edge&Sketch_1/SketchArc_1_2")])
Group_3.setName("inner")
Group_3.result().setName("inner")

### Create Group
Group_4 = model.addGroup(Part_1_doc, "Edges", [model.selection("EDGE", "Face_1_1/Modified_Edge&Sketch_1/SketchArc_2_2")])
Group_4.setName("outer")
Group_4.result().setName("outer")

### Create Group
Group_5 = model.addGroup(Part_1_doc, "Faces", [model.selection("FACE", "Face_1_1")])
Group_5.setName("sur")
Group_5.result().setName("sur")

model.end()

###
### SHAPERSTUDY component
###

model.publishToShaperStudy()
import SHAPERSTUDY
Face_1_1, bot, top, inner, outer, sur, = SHAPERSTUDY.shape(model.featureStringId(Face_1))
###
### SMESH component
###

import  SMESH, SALOMEDS
from salome.smesh import smeshBuilder

smesh = smeshBuilder.New()
#smesh.SetEnablePublish( False ) # Set to False to avoid publish in study if not needed or in some particular situations:
                                 # multiples meshes built in parallel, complex and numerous mesh edition (performance)

Mesh_1 = smesh.Mesh(Face_1_1,'Mesh_1')
NETGEN_1D_2D = Mesh_1.Triangle(algo=smeshBuilder.NETGEN_1D2D)
NETGEN_2D_Parameters_1 = NETGEN_1D_2D.Parameters()
NETGEN_2D_Parameters_1.SetMaxSize( 0.01 )
NETGEN_2D_Parameters_1.SetMinSize( 0.01 )
NETGEN_2D_Parameters_1.SetSecondOrder( 0 )
NETGEN_2D_Parameters_1.SetOptimize( 1 )
NETGEN_2D_Parameters_1.SetFineness( 2 )
NETGEN_2D_Parameters_1.SetChordalError( -1 )
NETGEN_2D_Parameters_1.SetChordalErrorEnabled( 0 )
NETGEN_2D_Parameters_1.SetUseSurfaceCurvature( 1 )
NETGEN_2D_Parameters_1.SetFuseEdges( 1 )
NETGEN_2D_Parameters_1.SetWorstElemMeasure( 0 )
NETGEN_2D_Parameters_1.SetUseDelauney( 122 )
NETGEN_2D_Parameters_1.SetQuadAllowed( 0 )
NETGEN_2D_Parameters_1.SetCheckChartBoundary( 128 )
bot_1 = Mesh_1.GroupOnGeom(bot,'bot',SMESH.EDGE)
top_1 = Mesh_1.GroupOnGeom(top,'top',SMESH.EDGE)
inner_1 = Mesh_1.GroupOnGeom(inner,'inner',SMESH.EDGE)
outer_1 = Mesh_1.GroupOnGeom(outer,'outer',SMESH.EDGE)
sur_1 = Mesh_1.GroupOnGeom(sur,'sur',SMESH.FACE)
isDone = Mesh_1.Compute()
[ bot_1, top_1, inner_1, outer_1, sur_1 ] = Mesh_1.GetGroups()
NETGEN_2D_Parameters_1.SetMaxSize( 0.02 )
NETGEN_2D_Parameters_1.SetMinSize( 0.02 )
NETGEN_2D_Parameters_1.SetCheckChartBoundary( 128 )
isDone = Mesh_1.Compute()
[ bot_1, top_1, inner_1, outer_1, sur_1 ] = Mesh_1.GetGroups()
smesh.SetName(Mesh_1, 'Mesh_1')
try:
  Mesh_1.ExportMED( r'./quater_cylinder.med', 0, 41, 1, Mesh_1, 1, [], '',-1, 1 )
  pass
except:
  print('ExportPartToMED() failed. Invalid file name?')


## Set names of Mesh objects
smesh.SetName(NETGEN_1D_2D.GetAlgorithm(), 'NETGEN 1D-2D')
smesh.SetName(sur_1, 'sur')
smesh.SetName(Mesh_1.GetMesh(), 'Mesh_1')
smesh.SetName(bot_1, 'bot')
smesh.SetName(top_1, 'top')
smesh.SetName(inner_1, 'inner')
smesh.SetName(outer_1, 'outer')
smesh.SetName(NETGEN_2D_Parameters_1, 'NETGEN 2D Parameters_1')


if salome.sg.hasDesktop():
  salome.sg.updateObjBrowser()
