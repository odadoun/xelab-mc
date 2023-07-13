// =============================================================================
//  Title: XelabConstruction.hh
//  Author: Erwann Masson
//  Creation: Spring 2023
// =============================================================================

#ifndef XELABCONSTRUCTION_HH
#define XELABCONSTRUCTION_HH

// Materials
#include <G4NistManager.hh>

// Units
#include <G4SystemOfUnits.hh>

// Visualisation
#include <G4Colour.hh>
#include <G4VisAttributes.hh>

// Placement
#include <G4PVPlacement.hh>
#include <G4ThreeVector.hh>
#include <G4RotationMatrix.hh>
#include <G4Transform3D.hh>

// Solids
#include <G4Box.hh>
#include <G4Torus.hh>
#include <G4Tubs.hh>
#include <G4SubtractionSolid.hh>
#include <G4UnionSolid.hh>
#include <G4MultiUnion.hh>
#include <G4VSolid.hh>
#include <G4DisplacedSolid.hh>

// Construction headers
#include <G4LogicalVolume.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VUserDetectorConstruction.hh>

// Messenger
#include <G4GenericMessenger.hh>

// Xelab header
#include "XelabDetector.hh"

// Additional classes
using std::map;
using std::vector;

class XelabDetectorConstruction : public G4VUserDetectorConstruction
{
public:
  XelabDetectorConstruction();
  ~XelabDetectorConstruction();

  virtual G4VPhysicalVolume *Construct();

private:
  void DefineMaterials();

  void DefineGeometryParameters();

  void ConstructWorld();

  void ConstructCryostat();

  static map<G4String, G4double> geometryParameters;

  G4ThreeVector nullTranslation = G4ThreeVector(0.0, 0.0, 0.0);
  G4RotationMatrix nullRotation = G4RotationMatrix();

  G4GenericMessenger *fMessenger;

  // Elements
  G4Element *N, *O, *Cr, *Ni, *Mo, *Mn, *C, *Si, *Ti, *Fe, *Xe;
  G4Material *Vacuum, *Air, *SS316Ti, *Rubber, *Copper, *LXe, *GXe;

  // Solid volumes
  G4Box *world_solid;

  G4Tubs *LXeMainPart_solid;
  G4Tubs *LXePipeSubPart_solid;
  G4Tubs *LXeColumnSubPart_solid;
  G4SubtractionSolid *LXe_sub1_solid;
  G4SubtractionSolid *LXe_solid;

  G4Tubs *innCryoTranslation_solid;
  G4Tubs *innCryoEnvelope_solid;
  G4Tubs *innCryoBotEndCap_solid;
  G4Tubs *innCryoTopSealLowerPart_solid;
  G4Tubs *innCryoTopSealUpperPart_solid;
  G4UnionSolid *innCryoTopSeal_solid;
  G4Tubs *innCryoTopEndCap_solid;
  G4Tubs *innCryoPipe_solid;

  G4Tubs *outCryoTranslation_solid;
  G4Tubs *outCryoEnvelope_solid;
  G4Tubs *outCryoBotEndCap_solid;
  G4Tubs *outCryoTopSealMainPart_solid;
  G4Tubs *outCryoTopSealUpperSubPart_solid;
  G4SubtractionSolid *outCryoTopSeal_sub1_solid;
  G4Tubs *outCryoTopSealInnerLowerSubPart_solid;
  G4SubtractionSolid *outCryoTopSeal_sub2_solid;
  G4Tubs *outCryoTopSealOuterLowerSubPart_solid;
  G4SubtractionSolid *outCryoTopSeal_solid;
  G4Tubs *outCryoTopEndCapMainPart_solid;
  G4Tubs *outCryoTopEndCapUpperSubPart_solid;
  G4SubtractionSolid *outCryoTopEndCap_sub1_solid;
  G4Tubs *outCryoTopEndCapInnerLowerSubPart_solid;
  G4SubtractionSolid *outCryoTopEndCap_sub2_solid;
  G4Tubs *outCryoTopEndCapOuterLowerSubPart_solid;
  G4SubtractionSolid *outCryoTopEndCap_solid;
  G4Tubs *outCryoTopJointOuterPart_solid;
  G4Torus *outCryoTopJointOuterSubPart_solid;
  G4SubtractionSolid *outCryoTopJoint_sub_solid;
  G4Tubs *outCryoTopJointMainPart_solid;
  G4UnionSolid *outCryoTopJoint_solid;
  G4Tubs *outCryoColumnSealLowerPart_solid;
  G4Tubs *outCryoColumnSealUpperPart_solid;
  G4UnionSolid *outCryoColumnSeal_solid;
  G4Tubs *outCryoColumnEndCap_solid;
  G4Tubs *outCryoColumn_solid;

  G4Tubs *copperEnvelopeHalfTube_solid;
  G4Tubs *copperEnvelopeJunction_solid;
  G4Box *copperEnvelopeLongFrame_solid;
  G4VSolid *copperEnvelopeJunctionRotY_solid;
  G4Box *copperEnvelopeShortFrame_solid;
  G4MultiUnion *copperEnvelopeFirstHalf_solid;
  G4VSolid *copperEnvelopeSecondHalf_solid;
  G4Tubs *copperEnvelopeTongueTube_solid;
  G4Box *copperEnvelopeTongueStraightPart_solid;
  G4Tubs *copperEnvelopeTongueCurvedPart_solid;
  G4MultiUnion *copperEnvelope_solid;

  // Logical volumes
  G4LogicalVolume *world_logical;

  G4LogicalVolume *LXe_logical;

  G4LogicalVolume *innCryoTranslation_logical;
  G4LogicalVolume *innCryoEnvelope_logical;
  G4LogicalVolume *innCryoBotEndCap_logical;
  G4LogicalVolume *innCryoTopSeal_logical;
  G4LogicalVolume *innCryoTopEndCap_logical;
  G4LogicalVolume *innCryoPipe_logical;

  G4LogicalVolume *outCryoTranslation_logical;
  G4LogicalVolume *outCryoEnvelope_logical;
  G4LogicalVolume *outCryoBotEndCap_logical;
  G4LogicalVolume *outCryoTopSeal_logical;
  G4LogicalVolume *outCryoTopEndCap_logical;
  G4LogicalVolume *outCryoTopJoint_logical;
  G4LogicalVolume *outCryoColumnSeal_logical;
  G4LogicalVolume *outCryoColumnEndCap_logical;
  G4LogicalVolume *outCryoColumn_logical;

  G4LogicalVolume *copperEnvelope_logical;

  // Physical volumes
  G4VPhysicalVolume *world_physical;

  G4VPhysicalVolume *LXe_physical;

  G4VPhysicalVolume *innCryoTranslation_physical;
  G4VPhysicalVolume *innCryoEnvelope_physical;
  G4VPhysicalVolume *innCryoBotEndCap_physical;
  G4VPhysicalVolume *innCryoTopSeal_physical;
  G4VPhysicalVolume *innCryoTopEndCap_physical;
  G4VPhysicalVolume *innCryoPipe_physical;

  G4VPhysicalVolume *outCryoTranslation_physical;
  G4VPhysicalVolume *outCryoEnvelope_physical;
  G4VPhysicalVolume *outCryoBotEndCap_physical;
  G4VPhysicalVolume *outCryoTopSeal_physical;
  G4VPhysicalVolume *outCryoTopEndCap_physical;
  G4VPhysicalVolume *outCryoTopJoint_physical;
  G4VPhysicalVolume *outCryoColumnSeal_physical;
  G4VPhysicalVolume *outCryoColumnEndCap_physical;
  G4VPhysicalVolume *outCryoColumn_physical;

  G4VPhysicalVolume *copperEnvelope_physical;
};

#endif
