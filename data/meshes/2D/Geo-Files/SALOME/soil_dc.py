#!/usr/bin/env python

import sys
import salome

salome.salome_init()
###
### SHAPER component
###

from SketchAPI import *

from salome.shaper import model

model.begin()
partSet = model.moduleDocument()

### Create Part
Part_1 = model.addPart(partSet)
Part_1_doc = Part_1.document()

### Create Sketch
Sketch_1 = model.addSketch(Part_1_doc, model.defaultPlane("XOY"))

### Create SketchLine
SketchLine_1 = Sketch_1.addLine(50, 0, 0, 0)

### Create SketchProjection
SketchProjection_1 = Sketch_1.addProjection(model.selection("VERTEX", "PartSet/Origin"), False)
SketchPoint_1 = SketchProjection_1.createdFeature()
Sketch_1.setCoincident(SketchLine_1.endPoint(), SketchPoint_1.result())

### Create SketchLine
SketchLine_2 = Sketch_1.addLine(0, 0, 0, 50)

### Create SketchLine
SketchLine_3 = Sketch_1.addLine(0, 50, 50, 50)

### Create SketchLine
SketchLine_4 = Sketch_1.addLine(50, 50, 50, 0)
Sketch_1.setCoincident(SketchLine_4.endPoint(), SketchLine_1.startPoint())
Sketch_1.setCoincident(SketchLine_1.endPoint(), SketchLine_2.startPoint())
Sketch_1.setCoincident(SketchLine_2.endPoint(), SketchLine_3.startPoint())
Sketch_1.setCoincident(SketchLine_3.endPoint(), SketchLine_4.startPoint())
Sketch_1.setHorizontal(SketchLine_1.result())
Sketch_1.setVertical(SketchLine_2.result())
Sketch_1.setHorizontal(SketchLine_3.result())
Sketch_1.setVertical(SketchLine_4.result())
Sketch_1.setLength(SketchLine_1.result(), 50)
Sketch_1.setLength(SketchLine_2.result(), 50)

### Create SketchPoint
SketchPoint_2 = Sketch_1.addPoint(5, 5)
Sketch_1.setVerticalDistance(SketchPoint_2.coordinates(), SketchAPI_Point(SketchPoint_1).coordinates(), 5)
Sketch_1.setHorizontalDistance(SketchPoint_2.coordinates(), SketchAPI_Point(SketchPoint_1).coordinates(), 5)

### Create SketchPoint
SketchPoint_3 = Sketch_1.addPoint(5, 5.1)
Sketch_1.setVerticalDistance(SketchPoint_3.coordinates(), SketchPoint_2.coordinates(), 0.1)
Sketch_1.setHorizontalDistance(SketchPoint_3.coordinates(), SketchAPI_Point(SketchPoint_1).coordinates(), 5)

### Create SketchPoint
SketchPoint_4 = Sketch_1.addPoint(4.95, 5.05)

### Create SketchPoint
SketchPoint_5 = Sketch_1.addPoint(5.05, 5.05)

### Create SketchPoint
SketchPoint_6 = Sketch_1.addPoint(5, 5.05)
Sketch_1.setHorizontalDistance(SketchPoint_4.coordinates(), SketchPoint_6.coordinates(), 0.05)
Sketch_1.setHorizontalDistance(SketchPoint_6.coordinates(), SketchPoint_5.coordinates(), 0.05)
Sketch_1.setVerticalDistance(SketchPoint_6.coordinates(), SketchPoint_3.coordinates(), 0.05)
Sketch_1.setVerticalDistance(SketchPoint_4.coordinates(), SketchPoint_2.coordinates(), 0.05)
Sketch_1.setVerticalDistance(SketchPoint_5.coordinates(), SketchPoint_2.coordinates(), 0.05)
Sketch_1.setHorizontalDistance(SketchPoint_6.coordinates(), SketchAPI_Point(SketchPoint_1).coordinates(), 5)

### Create SketchLine
SketchLine_5 = Sketch_1.addLine(5, 5, 5.05, 5.05)
Sketch_1.setCoincident(SketchPoint_2.coordinates(), SketchLine_5.startPoint())
Sketch_1.setCoincident(SketchPoint_5.coordinates(), SketchLine_5.endPoint())

### Create SketchLine
SketchLine_6 = Sketch_1.addLine(5.05, 5.05, 5, 5.1)
Sketch_1.setCoincident(SketchPoint_5.coordinates(), SketchLine_6.startPoint())
Sketch_1.setCoincident(SketchPoint_3.coordinates(), SketchLine_6.endPoint())

### Create SketchLine
SketchLine_7 = Sketch_1.addLine(5, 5.1, 4.95, 5.05)
Sketch_1.setCoincident(SketchPoint_3.coordinates(), SketchLine_7.startPoint())
Sketch_1.setCoincident(SketchPoint_4.coordinates(), SketchLine_7.endPoint())

### Create SketchLine
SketchLine_8 = Sketch_1.addLine(4.95, 5.05, 5, 5)
Sketch_1.setCoincident(SketchPoint_4.coordinates(), SketchLine_8.startPoint())
Sketch_1.setCoincident(SketchPoint_2.coordinates(), SketchLine_8.endPoint())

### Create SketchLine
SketchLine_9 = Sketch_1.addLine(5, 5.05, 5.05, 5.05)
Sketch_1.setCoincident(SketchPoint_6.coordinates(), SketchLine_9.startPoint())
Sketch_1.setCoincident(SketchPoint_5.coordinates(), SketchLine_9.endPoint())

### Create SketchLine
SketchLine_10 = Sketch_1.addLine(5, 5.1, 5, 5.05)
Sketch_1.setCoincident(SketchPoint_3.coordinates(), SketchLine_10.startPoint())
Sketch_1.setCoincident(SketchPoint_6.coordinates(), SketchLine_10.endPoint())

### Create SketchLine
SketchLine_11 = Sketch_1.addLine(4.95, 5.05, 5, 5.05)
Sketch_1.setCoincident(SketchPoint_4.coordinates(), SketchLine_11.startPoint())
Sketch_1.setCoincident(SketchPoint_6.coordinates(), SketchLine_11.endPoint())

### Create SketchLine
SketchLine_12 = Sketch_1.addLine(5, 5.05, 5, 5)
Sketch_1.setCoincident(SketchPoint_6.coordinates(), SketchLine_12.startPoint())
Sketch_1.setCoincident(SketchPoint_2.coordinates(), SketchLine_12.endPoint())
model.do()

### Create Vertex
Vertex_1_objects = [model.selection("VERTEX", "Sketch_1/SketchLine_6_StartVertex"),
                    model.selection("VERTEX", "Sketch_1/SketchLine_8_EndVertex"),
                    model.selection("VERTEX", "Sketch_1/SketchLine_7_EndVertex"),
                    model.selection("VERTEX", "Sketch_1/SketchPoint_3"),
                    model.selection("VERTEX", "Sketch_1/SketchLine_11_EndVertex")]
Vertex_1 = model.addVertex(Part_1_doc, Vertex_1_objects, False)

### Create Face
Face_1_objects = [model.selection("FACE", "Sketch_1/Face-SketchLine_4r-SketchLine_3r-SketchLine_2r-SketchLine_1r-SketchLine_8r-SketchLine_7r-SketchLine_6r-SketchLine_5r"),
                  model.selection("FACE", "Sketch_1/Face-SketchLine_5f-SketchLine_9r-SketchLine_12f"),
                  model.selection("FACE", "Sketch_1/Face-SketchLine_6f-SketchLine_10f-SketchLine_9f"),
                  model.selection("FACE", "Sketch_1/Face-SketchLine_7f-SketchLine_11f-SketchLine_10r"),
                  model.selection("FACE", "Sketch_1/Face-SketchLine_8f-SketchLine_12r-SketchLine_11r")]
Face_1 = model.addFace(Part_1_doc, Face_1_objects)

### Create Fuse
Fuse_1_objects_1 = [model.selection("FACE", "Face_1_1"),
                    model.selection("FACE", "Face_1_2"),
                    model.selection("FACE", "Face_1_3"),
                    model.selection("FACE", "Face_1_4"),
                    model.selection("FACE", "Face_1_5")]
Fuse_1 = model.addFuse(Part_1_doc, Fuse_1_objects_1, keepSubResults = True)

### Create Group
Group_1 = model.addGroup(Part_1_doc, "Faces", [model.selection("COMPOUND", "Fuse_1_1")])
Group_1.setName("volume")
Group_1.result().setName("volume")

### Create Group
Group_2 = model.addGroup(Part_1_doc, "Edges", [model.selection("EDGE", "Face_1_1/Modified_Edge&Sketch_1/SketchLine_2")])
Group_2.setName("surface-left")
Group_2.result().setName("surface-left")

### Create Group
Group_3 = model.addGroup(Part_1_doc, "Edges", [model.selection("EDGE", "Face_1_1/Modified_Edge&Sketch_1/SketchLine_3")])
Group_3.setName("surface-top")
Group_3.result().setName("surface-top")

### Create Group
Group_4 = model.addGroup(Part_1_doc, "Edges", [model.selection("EDGE", "Face_1_1/Modified_Edge&Sketch_1/SketchLine_4")])
Group_4.setName("surface-right")
Group_4.result().setName("surface-right")

### Create Group
Group_5 = model.addGroup(Part_1_doc, "Edges", [model.selection("EDGE", "Face_1_1/Modified_Edge&Sketch_1/SketchLine_1")])
Group_5.setName("surface-bot")
Group_5.result().setName("surface-bot")

model.end()

###
### SHAPERSTUDY component
###

model.publishToShaperStudy()
import SHAPERSTUDY
Vertex_1_1, = SHAPERSTUDY.shape(model.featureStringId(Vertex_1))
Vertex_1_2, = SHAPERSTUDY.shape(model.featureStringId(Vertex_1, 1))
Vertex_1_3, = SHAPERSTUDY.shape(model.featureStringId(Vertex_1, 2))
Vertex_1_4, = SHAPERSTUDY.shape(model.featureStringId(Vertex_1, 3))
Vertex_1_5, = SHAPERSTUDY.shape(model.featureStringId(Vertex_1, 4))
Fuse_1_1, volume, surface-left, surface-top, surface-right, surface-bot, = SHAPERSTUDY.shape(model.featureStringId(Fuse_1))
###
### GEOM component
###

import GEOM
from salome.geom import geomBuilder
import math
import SALOMEDS


geompy = geomBuilder.New()

O = geompy.MakeVertex(0, 0, 0)
OX = geompy.MakeVectorDXDYDZ(1, 0, 0)
OY = geompy.MakeVectorDXDYDZ(0, 1, 0)
OZ = geompy.MakeVectorDXDYDZ(0, 0, 1)
geompy.addToStudy( O, 'O' )
geompy.addToStudy( OX, 'OX' )
geompy.addToStudy( OY, 'OY' )
geompy.addToStudy( OZ, 'OZ' )

###
### SMESH component
###

import  SMESH, SALOMEDS
from salome.smesh import smeshBuilder

smesh = smeshBuilder.New()
#smesh.SetEnablePublish( False ) # Set to False to avoid publish in study if not needed or in some particular situations:
                                 # multiples meshes built in parallel, complex and numerous mesh edition (performance)

NETGEN_2D_Parameters_1 = smesh.CreateHypothesis('NETGEN_Parameters_2D', 'NETGENEngine')
NETGEN_2D_Parameters_1.SetMaxSize( 1 )
NETGEN_2D_Parameters_1.SetMinSize( 1 )
NETGEN_2D_Parameters_1.SetSecondOrder( 0 )
NETGEN_2D_Parameters_1.SetOptimize( 1 )
NETGEN_2D_Parameters_1.SetFineness( 2 )
NETGEN_2D_Parameters_1.SetChordalError( -1 )
NETGEN_2D_Parameters_1.SetChordalErrorEnabled( 0 )
NETGEN_2D_Parameters_1.SetUseSurfaceCurvature( 1 )
NETGEN_2D_Parameters_1.SetFuseEdges( 1 )
NETGEN_2D_Parameters_1.SetWorstElemMeasure( 0 )
NETGEN_2D_Parameters_1.SetUseDelauney( 108 )
NETGEN_2D_Parameters_1.SetQuadAllowed( 0 )
NETGEN_2D_Parameters_1.SetLocalSizeOnShape(Vertex_1_1, 0.1)
NETGEN_2D_Parameters_1.SetLocalSizeOnShape(Vertex_1_2, 0.1)
NETGEN_2D_Parameters_1.SetLocalSizeOnShape(Vertex_1_3, 0.1)
NETGEN_2D_Parameters_1.SetLocalSizeOnShape(Vertex_1_4, 0.1)
NETGEN_2D_Parameters_1.SetLocalSizeOnShape(Vertex_1_5, 0.1)
NETGEN_2D_Parameters_1.SetCheckChartBoundary( 128 )
NETGEN_1D_2D = smesh.CreateHypothesis('NETGEN_2D', 'NETGENEngine')
Mesh_1 = smesh.Mesh(Fuse_1_1,'Mesh_1')
status = Mesh_1.AddHypothesis(NETGEN_2D_Parameters_1)
status = Mesh_1.AddHypothesis(NETGEN_1D_2D)
volume_1 = Mesh_1.GroupOnGeom(volume,'volume',SMESH.FACE)
surface_left = Mesh_1.GroupOnGeom(surface-left,'surface-left',SMESH.EDGE)
surface_top = Mesh_1.GroupOnGeom(surface-top,'surface-top',SMESH.EDGE)
surface_right = Mesh_1.GroupOnGeom(surface-right,'surface-right',SMESH.EDGE)
surface_bot = Mesh_1.GroupOnGeom(surface-bot,'surface-bot',SMESH.EDGE)
isDone = Mesh_1.Compute()
[ volume_1, surface_left, surface_top, surface_right, surface_bot ] = Mesh_1.GetGroups()
smesh.SetName(Mesh_1, 'Mesh_1')
try:
  Mesh_1.ExportMED( r'./soil_dc.med', 0, 41, 1, Mesh_1, 1, [], '',-1, 1 )
  pass
except:
  print('ExportPartToMED() failed. Invalid file name?')


## Set names of Mesh objects
smesh.SetName(volume_1, 'volume')
smesh.SetName(NETGEN_1D_2D, 'NETGEN 1D-2D')
smesh.SetName(Mesh_1.GetMesh(), 'Mesh_1')
smesh.SetName(surface_bot, 'surface-bot')
smesh.SetName(surface_right, 'surface-right')
smesh.SetName(surface_top, 'surface-top')
smesh.SetName(surface_left, 'surface-left')
smesh.SetName(NETGEN_2D_Parameters_1, 'NETGEN 2D Parameters_1')


if salome.sg.hasDesktop():
  salome.sg.updateObjBrowser()
