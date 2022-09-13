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

### Create SketchLine
SketchLine_1 = Sketch_1.addLine(0, 0, 0, -15)

### Create SketchProjection
SketchProjection_1 = Sketch_1.addProjection(model.selection("VERTEX", "PartSet/Origin"), False)
SketchPoint_1 = SketchProjection_1.createdFeature()
Sketch_1.setCoincident(SketchLine_1.startPoint(), SketchPoint_1.result())
Sketch_1.setVertical(SketchLine_1.result())

### Create SketchLine
SketchLine_2 = Sketch_1.addLine(0, -15, 50, -15)
Sketch_1.setCoincident(SketchLine_1.endPoint(), SketchLine_2.startPoint())
Sketch_1.setHorizontal(SketchLine_2.result())

### Create SketchLine
SketchLine_3 = Sketch_1.addLine(50, -15, 50, 0)
Sketch_1.setCoincident(SketchLine_2.endPoint(), SketchLine_3.startPoint())

### Create SketchProjection
SketchProjection_2 = Sketch_1.addProjection(model.selection("EDGE", "PartSet/OX"), False)
SketchLine_4 = SketchProjection_2.createdFeature()
Sketch_1.setCoincident(SketchLine_3.endPoint(), SketchLine_4.result())
Sketch_1.setVertical(SketchLine_3.result())

### Create SketchLine
SketchLine_5 = Sketch_1.addLine(50, 0, 35, 0)
Sketch_1.setCoincident(SketchLine_3.endPoint(), SketchLine_5.startPoint())
Sketch_1.setCoincident(SketchLine_5.endPoint(), SketchLine_4.result())

### Create SketchLine
SketchLine_6 = Sketch_1.addLine(35, 0, 35, 5)
Sketch_1.setCoincident(SketchLine_5.endPoint(), SketchLine_6.startPoint())

### Create SketchLine
SketchLine_7 = Sketch_1.addLine(35, 5, 33, 5)
Sketch_1.setCoincident(SketchLine_6.endPoint(), SketchLine_7.startPoint())
Sketch_1.setHorizontal(SketchLine_7.result())

### Create SketchLine
SketchLine_8 = Sketch_1.addLine(33, 5, 33, 0)
Sketch_1.setCoincident(SketchLine_7.endPoint(), SketchLine_8.startPoint())
Sketch_1.setCoincident(SketchLine_8.endPoint(), SketchLine_4.result())

### Create SketchLine
SketchLine_9 = Sketch_1.addLine(33, 0, 27, 0)
Sketch_1.setCoincident(SketchLine_8.endPoint(), SketchLine_9.startPoint())
Sketch_1.setCoincident(SketchLine_9.endPoint(), SketchLine_4.result())

### Create SketchLine
SketchLine_10 = Sketch_1.addLine(27, 0, 27, 7.5)
Sketch_1.setCoincident(SketchLine_9.endPoint(), SketchLine_10.startPoint())
Sketch_1.setVertical(SketchLine_10.result())

### Create SketchLine
SketchLine_11 = Sketch_1.addLine(27, 7.5, 26, 9)
Sketch_1.setCoincident(SketchLine_10.endPoint(), SketchLine_11.startPoint())

### Create SketchLine
SketchLine_12 = Sketch_1.addLine(26, 9, 25, 7.5)
Sketch_1.setCoincident(SketchLine_11.endPoint(), SketchLine_12.startPoint())

### Create SketchLine
SketchLine_13 = Sketch_1.addLine(25, 7.5, 25, 0)
Sketch_1.setCoincident(SketchLine_12.endPoint(), SketchLine_13.startPoint())
Sketch_1.setCoincident(SketchLine_13.endPoint(), SketchLine_4.result())

### Create SketchLine
SketchLine_14 = Sketch_1.addLine(25, 0, 17, 0)
Sketch_1.setCoincident(SketchLine_13.endPoint(), SketchLine_14.startPoint())
Sketch_1.setCoincident(SketchLine_14.endPoint(), SketchLine_4.result())

### Create SketchLine
SketchLine_15 = Sketch_1.addLine(17, 0, 17, 4)
Sketch_1.setCoincident(SketchLine_14.endPoint(), SketchLine_15.startPoint())

### Create SketchLine
SketchLine_16 = Sketch_1.addLine(17, 4, 14, 4)
Sketch_1.setCoincident(SketchLine_15.endPoint(), SketchLine_16.startPoint())
Sketch_1.setHorizontal(SketchLine_16.result())

### Create SketchLine
SketchLine_17 = Sketch_1.addLine(14, 4, 14, -8.881784197001252e-16)
Sketch_1.setCoincident(SketchLine_16.endPoint(), SketchLine_17.startPoint())

### Create SketchLine
SketchLine_18 = Sketch_1.addLine(14, -8.881784197001252e-16, 12.5, 0)
Sketch_1.setCoincident(SketchLine_17.endPoint(), SketchLine_18.startPoint())
Sketch_1.setCoincident(SketchLine_18.endPoint(), SketchLine_4.result())

### Create SketchLine
SketchLine_19 = Sketch_1.addLine(12.5, 0, 12.5, 3)
Sketch_1.setCoincident(SketchLine_18.endPoint(), SketchLine_19.startPoint())

### Create SketchLine
SketchLine_20 = Sketch_1.addLine(12.5, 3, 10, 3)
Sketch_1.setCoincident(SketchLine_19.endPoint(), SketchLine_20.startPoint())
Sketch_1.setHorizontal(SketchLine_20.result())

### Create SketchLine
SketchLine_21 = Sketch_1.addLine(10, 3, 10, 3.05311331771918e-16)
Sketch_1.setCoincident(SketchLine_20.endPoint(), SketchLine_21.startPoint())

### Create SketchLine
SketchLine_22 = Sketch_1.addLine(10, 3.05311331771918e-16, 9, -6.938893903907228e-16)
Sketch_1.setCoincident(SketchLine_21.endPoint(), SketchLine_22.startPoint())

### Create SketchLine
SketchLine_23 = Sketch_1.addLine(9, -6.938893903907228e-16, 9, 6.999999999999999)
Sketch_1.setCoincident(SketchLine_22.endPoint(), SketchLine_23.startPoint())
Sketch_1.setVertical(SketchLine_23.result())

### Create SketchLine
SketchLine_24 = Sketch_1.addLine(9, 6.999999999999999, 7, 8)
Sketch_1.setCoincident(SketchLine_23.endPoint(), SketchLine_24.startPoint())

### Create SketchLine
SketchLine_25 = Sketch_1.addLine(7, 8, 5, 7)
Sketch_1.setCoincident(SketchLine_24.endPoint(), SketchLine_25.startPoint())

### Create SketchLine
SketchLine_26 = Sketch_1.addLine(5, 7, 5, 0)
Sketch_1.setCoincident(SketchLine_25.endPoint(), SketchLine_26.startPoint())
Sketch_1.setCoincident(SketchLine_26.endPoint(), SketchLine_4.result())
Sketch_1.setVertical(SketchLine_26.result())

### Create SketchLine
SketchLine_27 = Sketch_1.addLine(5, 0, 0, 0)
Sketch_1.setCoincident(SketchLine_26.endPoint(), SketchLine_27.startPoint())
Sketch_1.setCoincident(SketchLine_1.startPoint(), SketchLine_27.endPoint())
Sketch_1.setLength(SketchLine_2.result(), 50)
Sketch_1.setLength(SketchLine_1.result(), 15)
Sketch_1.setLength(SketchLine_5.result(), 15)
Sketch_1.setLength(SketchLine_27.result(), 5)
Sketch_1.setVerticalDistance(SketchLine_26.startPoint(), SketchLine_27.startPoint(), 7)
Sketch_1.setVerticalDistance(SketchLine_23.endPoint(), SketchLine_22.endPoint(), 7)
Sketch_1.setVerticalDistance(SketchLine_22.endPoint(), SketchLine_1.endPoint(), 15)
Sketch_1.setVerticalDistance(SketchLine_25.startPoint(), SketchLine_27.startPoint(), 8)
Sketch_1.setHorizontalDistance(SketchLine_25.startPoint(), SketchLine_1.endPoint(), 7)
Sketch_1.setHorizontalDistance(SketchLine_23.endPoint(), SketchLine_1.startPoint(), 9)
Sketch_1.setVerticalDistance(SketchLine_22.startPoint(), SketchLine_1.endPoint(), 15)
Sketch_1.setVerticalDistance(SketchLine_18.startPoint(), SketchLine_1.endPoint(), 15)
Sketch_1.setHorizontalDistance(SketchLine_7.startPoint(), SketchLine_5.startPoint(), 15)
Sketch_1.setHorizontalDistance(SketchLine_8.startPoint(), SketchLine_7.startPoint(), 2)
Sketch_1.setHorizontalDistance(SketchLine_9.startPoint(), SketchLine_6.startPoint(), 2)
Sketch_1.setVerticalDistance(SketchLine_6.endPoint(), SketchLine_6.startPoint(), 5)
Sketch_1.setHorizontalDistance(SketchLine_9.startPoint(), SketchLine_9.endPoint(), 6)
Sketch_1.setHorizontalDistance(SketchLine_10.endPoint(), SketchLine_11.endPoint(), 1)
Sketch_1.setHorizontalDistance(SketchLine_11.endPoint(), SketchLine_13.startPoint(), 1)
Sketch_1.setHorizontalDistance(SketchLine_9.endPoint(), SketchLine_14.startPoint(), 2)
Sketch_1.setHorizontalDistance(SketchLine_14.startPoint(), SketchLine_14.endPoint(), 8)
Sketch_1.setHorizontalDistance(SketchLine_15.endPoint(), SketchLine_14.startPoint(), 8)
Sketch_1.setHorizontalDistance(SketchLine_15.endPoint(), SketchLine_17.startPoint(), 3)
Sketch_1.setHorizontalDistance(SketchLine_17.startPoint(), SketchLine_19.startPoint(), 1.5)
Sketch_1.setHorizontalDistance(SketchLine_20.startPoint(), SketchLine_17.startPoint(), 1.5)
Sketch_1.setHorizontalDistance(SketchLine_20.startPoint(), SketchLine_21.startPoint(), 2.5)
Sketch_1.setHorizontalDistance(SketchLine_22.startPoint(), SketchLine_18.endPoint(), 2.5)
Sketch_1.setVerticalDistance(SketchLine_10.endPoint(), SketchLine_9.endPoint(), 7.5)
Sketch_1.setVerticalDistance(SketchLine_13.startPoint(), SketchLine_14.startPoint(), 7.5)
Sketch_1.setVerticalDistance(SketchLine_15.endPoint(), SketchLine_15.startPoint(), 4)
Sketch_1.setVerticalDistance(SketchLine_20.startPoint(), SketchLine_18.endPoint(), 3)
Sketch_1.setVerticalDistance(SketchLine_12.startPoint(), SketchLine_10.endPoint(), 1.5)
Sketch_1.setHorizontalDistance(SketchLine_18.startPoint(), SketchLine_15.startPoint(), 3)

### Create SketchLine
SketchLine_28 = Sketch_1.addLine(5, 0, 9, -6.938893903907228e-16)
SketchLine_28.setAuxiliary(True)
Sketch_1.setCoincident(SketchLine_26.endPoint(), SketchLine_28.startPoint())
Sketch_1.setCoincident(SketchLine_22.endPoint(), SketchLine_28.endPoint())

### Create SketchLine
SketchLine_29 = Sketch_1.addLine(10, 3.05311331771918e-16, 12.5, 0)
SketchLine_29.setAuxiliary(True)
Sketch_1.setCoincident(SketchLine_21.endPoint(), SketchLine_29.startPoint())
Sketch_1.setCoincident(SketchLine_18.endPoint(), SketchLine_29.endPoint())

### Create SketchLine
SketchLine_30 = Sketch_1.addLine(14, -8.881784197001252e-16, 17, 0)
SketchLine_30.setAuxiliary(True)
Sketch_1.setCoincident(SketchLine_17.endPoint(), SketchLine_30.startPoint())
Sketch_1.setCoincident(SketchLine_14.endPoint(), SketchLine_30.endPoint())

### Create SketchLine
SketchLine_31 = Sketch_1.addLine(25, 0, 27, 0)
SketchLine_31.setAuxiliary(True)
Sketch_1.setCoincident(SketchLine_13.endPoint(), SketchLine_31.startPoint())
Sketch_1.setCoincident(SketchLine_9.endPoint(), SketchLine_31.endPoint())

### Create SketchLine
SketchLine_32 = Sketch_1.addLine(33, 0, 35, 0)
SketchLine_32.setAuxiliary(True)
Sketch_1.setCoincident(SketchLine_8.endPoint(), SketchLine_32.startPoint())
Sketch_1.setCoincident(SketchLine_5.endPoint(), SketchLine_32.endPoint())
model.do()

### Create Face
Face_1_objects = [model.selection("EDGE", "Sketch_1/SketchLine_26"),
                  model.selection("EDGE", "Sketch_1/SketchLine_25"),
                  model.selection("EDGE", "Sketch_1/SketchLine_24"),
                  model.selection("EDGE", "Sketch_1/SketchLine_23"),
                  model.selection("EDGE", "Sketch_1/SketchLine_28"),
                  model.selection("EDGE", "Sketch_1/SketchLine_21"),
                  model.selection("EDGE", "Sketch_1/SketchLine_20"),
                  model.selection("EDGE", "Sketch_1/SketchLine_19"),
                  model.selection("EDGE", "Sketch_1/SketchLine_29"),
                  model.selection("EDGE", "Sketch_1/SketchLine_17"),
                  model.selection("EDGE", "Sketch_1/SketchLine_16"),
                  model.selection("EDGE", "Sketch_1/SketchLine_15"),
                  model.selection("EDGE", "Sketch_1/SketchLine_30"),
                  model.selection("EDGE", "Sketch_1/SketchLine_13"),
                  model.selection("EDGE", "Sketch_1/SketchLine_12"),
                  model.selection("EDGE", "Sketch_1/SketchLine_11"),
                  model.selection("EDGE", "Sketch_1/SketchLine_10"),
                  model.selection("EDGE", "Sketch_1/SketchLine_31"),
                  model.selection("EDGE", "Sketch_1/SketchLine_8"),
                  model.selection("EDGE", "Sketch_1/SketchLine_7"),
                  model.selection("EDGE", "Sketch_1/SketchLine_6"),
                  model.selection("EDGE", "Sketch_1/SketchLine_32")]
Face_1 = model.addFace(Part_1_doc, Face_1_objects)

### Create Face
Face_2_objects = [model.selection("EDGE", "Sketch_1/SketchLine_2"),
                  model.selection("EDGE", "Sketch_1/SketchLine_1"),
                  model.selection("EDGE", "Sketch_1/SketchLine_27"),
                  model.selection("EDGE", "Sketch_1/SketchLine_28"),
                  model.selection("EDGE", "Sketch_1/SketchLine_22"),
                  model.selection("EDGE", "Face_1_2/Modified_Edge&Sketch_1/SketchLine_29"),
                  model.selection("EDGE", "Sketch_1/SketchLine_18"),
                  model.selection("EDGE", "Face_1_3/Modified_Edge&Sketch_1/SketchLine_30"),
                  model.selection("EDGE", "Sketch_1/SketchLine_14"),
                  model.selection("EDGE", "Sketch_1/SketchLine_31"),
                  model.selection("EDGE", "Sketch_1/SketchLine_9"),
                  model.selection("EDGE", "Sketch_1/SketchLine_32"),
                  model.selection("EDGE", "Sketch_1/SketchLine_5"),
                  model.selection("EDGE", "Sketch_1/SketchLine_3")]
Face_2 = model.addFace(Part_1_doc, Face_2_objects)

### Create Face
Face_3_objects = [model.selection("EDGE", "Sketch_1/SketchLine_21"),
                  model.selection("EDGE", "Sketch_1/SketchLine_20"),
                  model.selection("EDGE", "Sketch_1/SketchLine_19"),
                  model.selection("EDGE", "Sketch_1/SketchLine_29")]
Face_3 = model.addFace(Part_1_doc, Face_3_objects)

### Create Face
Face_4_objects = [model.selection("EDGE", "Sketch_1/SketchLine_17"),
                  model.selection("EDGE", "Sketch_1/SketchLine_16"),
                  model.selection("EDGE", "Sketch_1/SketchLine_15"),
                  model.selection("EDGE", "Sketch_1/SketchLine_30")]
Face_4 = model.addFace(Part_1_doc, Face_4_objects)

### Create Fuse
Fuse_1_objects_1 = [model.selection("FACE", "Face_1_1"),
                    model.selection("FACE", "Face_1_4"),
                    model.selection("FACE", "Face_1_5"),
                    model.selection("FACE", "Face_3_1"),
                    model.selection("FACE", "Face_4_1")]
Fuse_1 = model.addFuse(Part_1_doc, Fuse_1_objects_1, keepSubResults = True)

### Create Fuse
Fuse_2 = model.addFuse(Part_1_doc, [model.selection("FACE", "Face_2_1"), model.selection("COMPOUND", "Fuse_1_1")], keepSubResults = True)

### Create Group
Group_1 = model.addGroup(Part_1_doc, "Faces", [model.selection("FACE", "Fuse_2_1_1")])
Group_1.setName("soil-volume")
Group_1.result().setName("soil-volume")

### Create Group
Group_2_objects = [model.selection("FACE", "Fuse_2_1_2"),
                   model.selection("FACE", "Fuse_2_1_3"),
                   model.selection("FACE", "Fuse_2_1_4"),
                   model.selection("FACE", "Fuse_2_1_5"),
                   model.selection("FACE", "Fuse_2_1_6")]
Group_2 = model.addGroup(Part_1_doc, "Faces", Group_2_objects)
Group_2.setName("city-volume")
Group_2.result().setName("city-volume")

### Create Group
Group_3 = model.addGroup(Part_1_doc, "Edges", [model.selection("EDGE", "Face_2_1/Modified_Edge&Sketch_1/SketchLine_2")])
Group_3.setName("paraxial-bot")
Group_3.result().setName("paraxial-bot")

### Create Group
Group_4 = model.addGroup(Part_1_doc, "Edges", [model.selection("EDGE", "Face_2_1/Modified_Edge&Sketch_1/SketchLine_1")])
Group_4.setName("paraxial-left")
Group_4.result().setName("paraxial-left")

### Create Group
Group_5 = model.addGroup(Part_1_doc, "Edges", [model.selection("EDGE", "Face_2_1/Modified_Edge&Sketch_1/SketchLine_3")])
Group_5.setName("paraxial-right")
Group_5.result().setName("paraxial-right")

### Create Group
Group_6_objects = [model.selection("EDGE", "Fuse_2_1_1/Modified_Edge&Sketch_1/SketchLine_27"),
                   model.selection("EDGE", "Fuse_2_1_1/Modified_Edge&Sketch_1/SketchLine_22"),
                   model.selection("EDGE", "Fuse_2_1_1/Modified_Edge&Sketch_1/SketchLine_18"),
                   model.selection("EDGE", "Fuse_2_1_1/Modified_Edge&Sketch_1/SketchLine_14"),
                   model.selection("EDGE", "Fuse_2_1_1/Modified_Edge&Sketch_1/SketchLine_9"),
                   model.selection("EDGE", "Fuse_2_1_1/Modified_Edge&Sketch_1/SketchLine_5")]
Group_6 = model.addGroup(Part_1_doc, "Edges", Group_6_objects)
Group_6.setName("soil-surface")
Group_6.result().setName("soil-surface")

### Create Group
Group_7_objects = [model.selection("EDGE", "Fuse_2_1_3/Modified_Edge&Sketch_1/SketchLine_26"),
                   model.selection("EDGE", "Face_1_1/Modified_Edge&Sketch_1/SketchLine_25"),
                   model.selection("EDGE", "Face_1_1/Modified_Edge&Sketch_1/SketchLine_24"),
                   model.selection("EDGE", "Fuse_2_1_3/Modified_Edge&Sketch_1/SketchLine_23"),
                   model.selection("EDGE", "Fuse_2_1_6/Modified_Edge&Sketch_1/SketchLine_21"),
                   model.selection("EDGE", "Face_3_1/Modified_Edge&Sketch_1/SketchLine_20"),
                   model.selection("EDGE", "Fuse_2_1_6/Modified_Edge&Sketch_1/SketchLine_19"),
                   model.selection("EDGE", "Fuse_2_1_2/Modified_Edge&Sketch_1/SketchLine_17"),
                   model.selection("EDGE", "Face_4_1/Modified_Edge&Sketch_1/SketchLine_16"),
                   model.selection("EDGE", "Fuse_2_1_2/Modified_Edge&Sketch_1/SketchLine_15"),
                   model.selection("EDGE", "Fuse_2_1_4/Modified_Edge&Sketch_1/SketchLine_13"),
                   model.selection("EDGE", "Face_1_4/Modified_Edge&Sketch_1/SketchLine_12"),
                   model.selection("EDGE", "Face_1_4/Modified_Edge&Sketch_1/SketchLine_11"),
                   model.selection("EDGE", "Fuse_2_1_4/Modified_Edge&Sketch_1/SketchLine_10"),
                   model.selection("EDGE", "Fuse_2_1_5/Modified_Edge&Sketch_1/SketchLine_8"),
                   model.selection("EDGE", "Face_1_5/Modified_Edge&Sketch_1/SketchLine_7"),
                   model.selection("EDGE", "Fuse_2_1_5/Modified_Edge&Sketch_1/SketchLine_6")]
Group_7 = model.addGroup(Part_1_doc, "Edges", Group_7_objects)
Group_7.setName("building-surface")
Group_7.result().setName("building-surface")

model.end()

###
### SHAPERSTUDY component
###

model.publishToShaperStudy()
import SHAPERSTUDY
# This shape does not exist among the SHAPER results; if it is referenced by SMESH, this may cause an error
# Face_2_1, = SHAPERSTUDY.shape("dead01_8:190")
# This shape does not exist among the SHAPER results; if it is referenced by SMESH, this may cause an error
# Fuse_1_1, = SHAPERSTUDY.shape("dead02_8:193")
Fuse_2_1, soil-volume, city-volume, paraxial-bot, paraxial-left, paraxial-right, soil-surface, building-surface, = SHAPERSTUDY.shape(model.featureStringId(Fuse_2))
###
### SMESH component
###

import  SMESH, SALOMEDS
from salome.smesh import smeshBuilder

smesh = smeshBuilder.New()
#smesh.SetEnablePublish( False ) # Set to False to avoid publish in study if not needed or in some particular situations:
                                 # multiples meshes built in parallel, complex and numerous mesh edition (performance)

Mesh_1 = smesh.Mesh(Fuse_2_1,'Mesh_1')
NETGEN_1D_2D = Mesh_1.Triangle(algo=smeshBuilder.NETGEN_1D2D)
NETGEN_2D_Parameters_1 = NETGEN_1D_2D.Parameters()
NETGEN_2D_Parameters_1.SetSecondOrder( 0 )
NETGEN_2D_Parameters_1.SetOptimize( 1 )
NETGEN_2D_Parameters_1.SetFineness( 2 )
NETGEN_2D_Parameters_1.SetChordalError( -1 )
NETGEN_2D_Parameters_1.SetChordalErrorEnabled( 0 )
NETGEN_2D_Parameters_1.SetUseSurfaceCurvature( 1 )
NETGEN_2D_Parameters_1.SetFuseEdges( 1 )
NETGEN_2D_Parameters_1.SetWorstElemMeasure( 0 )
NETGEN_2D_Parameters_1.SetUseDelauney( 141 )
NETGEN_2D_Parameters_1.SetCheckChartBoundary( 0 )
NETGEN_2D_Parameters_1.SetQuadAllowed( 0 )
soil_volume = Mesh_1.GroupOnGeom(soil-volume,'soil-volume',SMESH.FACE)
city_volume = Mesh_1.GroupOnGeom(city-volume,'city-volume',SMESH.FACE)
paraxial_bot = Mesh_1.GroupOnGeom(paraxial-bot,'paraxial-bot',SMESH.EDGE)
paraxial_left = Mesh_1.GroupOnGeom(paraxial-left,'paraxial-left',SMESH.EDGE)
paraxial_right = Mesh_1.GroupOnGeom(paraxial-right,'paraxial-right',SMESH.EDGE)
soil_surface = Mesh_1.GroupOnGeom(soil-surface,'soil-surface',SMESH.EDGE)
building_surface = Mesh_1.GroupOnGeom(building-surface,'building-surface',SMESH.EDGE)
NETGEN_2D_Parameters_1.SetMaxSize( 0.3 )
NETGEN_2D_Parameters_1.SetMinSize( 0.3 )
NETGEN_2D_Parameters_1.SetCheckChartBoundary( 144 )
isDone = Mesh_1.Compute()
[ soil_volume, city_volume, paraxial_bot, paraxial_left, paraxial_right, soil_surface, building_surface ] = Mesh_1.GetGroups()
smesh.SetName(Mesh_1, 'Mesh_1')
try:
  Mesh_1.ExportMED( r'./city.med', 0, 41, 1, Mesh_1, 1, [], '',-1, 1 )
  pass
except:
  print('ExportPartToMED() failed. Invalid file name?')


## Set names of Mesh objects
smesh.SetName(NETGEN_1D_2D.GetAlgorithm(), 'NETGEN 1D-2D')
smesh.SetName(soil_volume, 'soil-volume')
smesh.SetName(city_volume, 'city-volume')
smesh.SetName(Mesh_1.GetMesh(), 'Mesh_1')
smesh.SetName(paraxial_bot, 'paraxial-bot')
smesh.SetName(paraxial_left, 'paraxial-left')
smesh.SetName(paraxial_right, 'paraxial-right')
smesh.SetName(soil_surface, 'soil-surface')
smesh.SetName(building_surface, 'building-surface')
smesh.SetName(NETGEN_2D_Parameters_1, 'NETGEN 2D Parameters_1')


if salome.sg.hasDesktop():
  salome.sg.updateObjBrowser()
