#include "XelabConstruction.hh"

XelabDetectorConstruction::XelabDetectorConstruction()
{
  fMessenger = new G4GenericMessenger(this, "/detector/", "Detector Construction");
};

XelabDetectorConstruction::~XelabDetectorConstruction()
{
  delete fMessenger;
};

// Definitions from XENON class Xenon1tMaterials
void XelabDetectorConstruction::DefineMaterials()
{
  const test abcd = 58. ;
  for(int i = 0; i < 5; i ++){
  G4cout << i << G4endl;}

  G4NistManager *pNistManager = G4NistManager::Instance();

  const G4int nEntries = 32;
  G4double PhotonEnergy[nEntries] = {
      2.034 * eV, 2.068 * eV, 2.103 * eV, 2.139 * eV, 2.177 * eV, 2.216 * eV,
      2.256 * eV, 2.298 * eV, 2.341 * eV, 2.386 * eV, 2.433 * eV, 2.481 * eV,
      2.532 * eV, 2.585 * eV, 2.640 * eV, 2.697 * eV, 2.757 * eV, 2.820 * eV,
      2.885 * eV, 2.954 * eV, 3.026 * eV, 3.102 * eV, 3.181 * eV, 3.265 * eV,
      3.353 * eV, 3.446 * eV, 3.545 * eV, 3.649 * eV, 3.760 * eV, 3.877 * eV,
      4.002 * eV, 4.136 * eV};

  // ---------------------------------------------------------------------------
  // Common elements

  N = new G4Element("Nitrogen", "N", 7., 14.007 * g / mole);
  O = new G4Element("Oxygen", "O", 8., 15.999 * g / mole);
  Cr = new G4Element("Chromium", "Cr", 24., 51.996 * g / mole);
  Ni = new G4Element("Nickel", "Ni", 28., 58.693 * g / mole);
  Mo = pNistManager->FindOrBuildElement("Mo");
  Mn = new G4Element("Manganese", "Mn", 25., 54.938 * g / mole);
  C = new G4Element("Carbon", "C", 6., 12.011 * g / mole);
  Si = new G4Element("Silicon", "Si", 14., 28.086 * g / mole);
  Ti = pNistManager->FindOrBuildElement("Ti");
  Fe = new G4Element("Iron", "Fe", 26., 55.85 * g / mole);

  // ---------------------------------------------------------------------------
  // Vacuum definition

  Vacuum = new G4Material("Vacuum", 1.e-20 * g / cm3, 2, kStateGas);
  Vacuum->AddElement(N, 0.755);
  Vacuum->AddElement(O, 0.245);

  // Optical properties of vacuum
  G4double VacuumRefractiveIndex[nEntries] = {
      1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
      1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
      1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00};
  G4MaterialPropertiesTable *VacuumMPT = new G4MaterialPropertiesTable();
  VacuumMPT->AddProperty("RINDEX", PhotonEnergy, VacuumRefractiveIndex, nEntries);
  Vacuum->SetMaterialPropertiesTable(VacuumMPT);

  // ---------------------------------------------------------------------------
  // Air definition

  pNistManager->FindOrBuildMaterial("G4_AIR");
  Air = G4Material::GetMaterial("G4_AIR");

  // Optical properties of air
  G4double AirRefractiveIndex[nEntries] = {
      1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
      1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
      1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00};
  G4MaterialPropertiesTable *AirMPT = new G4MaterialPropertiesTable();
  AirMPT->AddProperty("RINDEX", PhotonEnergy, AirRefractiveIndex, nEntries);
  Air->SetMaterialPropertiesTable(AirMPT);

  // ---------------------------------------------------------------------------
  // SS316Ti steel definition

  SS316Ti = new G4Material("SS316Ti", 8.00 * g / cm3, 8, kStateSolid); // Should be SS304LSteel?
  SS316Ti->AddElement(Cr, 0.18);
  SS316Ti->AddElement(Ni, 0.14);
  SS316Ti->AddElement(Mo, 0.03);
  SS316Ti->AddElement(Mn, 0.02);
  SS316Ti->AddElement(C, 0.008);
  SS316Ti->AddElement(Si, 0.0075);
  SS316Ti->AddElement(Ti, 0.0070);
  SS316Ti->AddElement(Fe, 0.6075);

  // ---------------------------------------------------------------------------
  // Rubber definition (PLACEHOLDER for the outer cryostat top joint material)

  pNistManager->FindOrBuildMaterial("G4_RUBBER_NATURAL");
  Rubber = G4Material::GetMaterial("G4_RUBBER_NATURAL");

  // ---------------------------------------------------------------------------
  // Copper definition (PLACEHOLDER for the copper envelope around inner cryostat)

  pNistManager->FindOrBuildMaterial("G4_Cu");
  Copper = G4Material::GetMaterial("G4_Cu");

};

map<G4String, G4double> XelabDetectorConstruction::geometryParameters;

void XelabDetectorConstruction::DefineGeometryParameters()
{
  // ---------------------------------------------------------------------------
  // Subtracion tolerance

  geometryParameters["booleanTolerance"] = 0.1 * mm;

  // ---------------------------------------------------------------------------
  // World

  geometryParameters["world_halfX"] = 2. * m;
  geometryParameters["world_halfY"] = 2. * m;
  geometryParameters["world_halfZ"] = 2. * m;

  // ---------------------------------------------------------------------------
  // Inner cryostat

  // Envelope
  geometryParameters["innCryoEnvelope_innerRadius"] = 125. * mm;
  geometryParameters["innCryoEnvelope_outerRadius"] = 128. * mm;
  geometryParameters["innCryoEnvelope_halfLength"] = 135.7 * mm;

  geometryParameters["innCryoEnvelope_x"] = 0. * mm;
  geometryParameters["innCryoEnvelope_y"] = 0. * mm;
  geometryParameters["innCryoEnvelope_z"] = 0. * mm;

  // Bottom end cap
  geometryParameters["innCryoBotEndCap_innerRadius"] = 0. * mm;
  geometryParameters["innCryoBotEndCap_outerRadius"] = 128. * mm;
  geometryParameters["innCryoBotEndCap_halfWidth"] = 2. * mm;

  geometryParameters["innCryoBotEndCap_x"] = 0. * mm;
  geometryParameters["innCryoBotEndCap_y"] = 0. * mm;
  geometryParameters["innCryoBotEndCap_z"] = - (
    geometryParameters["innCryoEnvelope_halfLength"] +
    geometryParameters["innCryoBotEndCap_halfWidth"]
  );

  // Top seal
  geometryParameters["innCryoTopSealLowerPart_innerRadius"] = 128.25 * mm; // CHECK IF .25 GAP OR NOT
  geometryParameters["innCryoTopSealLowerPart_outerRadius"] = 153. * mm;
  geometryParameters["innCryoTopSealLowerPart_halfWidth"] = 5.2 * mm;

  geometryParameters["innCryoTopSealUpperPart_innerRadius"] = 126.5 * mm;
  geometryParameters["innCryoTopSealUpperPart_outerRadius"] = 153. * mm;
  geometryParameters["innCryoTopSealUpperPart_halfWidth"] = 7.3 * mm;

  geometryParameters["innCryoTopSealUpperLowerUnion_x"] = 0. * mm;
  geometryParameters["innCryoTopSealUpperLowerUnion_y"] = 0. * mm;
  geometryParameters["innCryoTopSealUpperLowerUnion_z"] = (
    geometryParameters["innCryoTopSealLowerPart_halfWidth"] +
    geometryParameters["innCryoTopSealUpperPart_halfWidth"]
  );

  geometryParameters["innCryoTopSeal_x"] = 0. * mm;
  geometryParameters["innCryoTopSeal_y"] = 0. * mm;
  geometryParameters["innCryoTopSeal_z"] = (
    geometryParameters["innCryoEnvelope_halfLength"] -
    geometryParameters["innCryoTopSealLowerPart_halfWidth"]
  );

  // Top end cap
  geometryParameters["innCryoTopEndCap_innerRadius"] = 78.5 * mm;
  geometryParameters["innCryoTopEndCap_outerRadius"] = 153. * mm;
  geometryParameters["innCryoTopEndCap_halfWidth"] = 12.5 * mm;

  geometryParameters["innCryoTopEndCap_x"] = 0. * mm;
  geometryParameters["innCryoTopEndCap_y"] = 0. * mm;
  geometryParameters["innCryoTopEndCap_z"] = (
    geometryParameters["innCryoEnvelope_halfLength"] +
    2 * geometryParameters["innCryoTopSealUpperPart_halfWidth"] +
    geometryParameters["innCryoTopEndCap_halfWidth"]
  );

  // Pipe
  geometryParameters["innCryoPipe_innerRadius"] = 2.46 * mm;
  geometryParameters["innCryoPipe_outerRadius"] = 3.17 * mm;
  geometryParameters["innCryoPipe_halfLength"] = 95. * mm;

  geometryParameters["innCryoPipe_rho"] = 95. * mm;
  geometryParameters["innCryoPipe_phi"] = 37.5 * deg;
  geometryParameters["innCryoPipe_z"] = (
    geometryParameters["innCryoEnvelope_halfLength"] -
    geometryParameters["innCryoPipe_halfLength"] +
    2 * geometryParameters["innCryoTopSealUpperPart_halfWidth"]
  );

  // ---------------------------------------------------------------------------
  // Outer cryostat

  // Envelope
  geometryParameters["outCryoEnvelope_innerRadius"] = 250. * mm;
  geometryParameters["outCryoEnvelope_outerRadius"] = 254. * mm;
  geometryParameters["outCryoEnvelope_halfLength"] = 340. * mm;

  geometryParameters["outCryoEnvelope_x"] = 0. * mm;
  geometryParameters["outCryoEnvelope_y"] = 0. * mm;
  geometryParameters["outCryoEnvelope_z"] = 0. * mm;

  // Bottom end cap
  geometryParameters["outCryoBotEndCap_innerRadius"] = 0. * mm;
  geometryParameters["outCryoBotEndCap_outerRadius"] = 252.5 * mm;
  geometryParameters["outCryoBotEndCap_halfWidth"] = 3. * mm;

  geometryParameters["outCryoBotEndCap_x"] = 0. * mm;
  geometryParameters["outCryoBotEndCap_y"] = 0. * mm;
  geometryParameters["outCryoBotEndCap_z"] = - (
    geometryParameters["outCryoEnvelope_halfLength"] +
    geometryParameters["outCryoBotEndCap_halfWidth"]
  );

  // Top seal
  geometryParameters["outCryoTopSealMainPart_innerRadius"] = 251. * mm;
  geometryParameters["outCryoTopSealMainPart_outerRadius"] = 275. * mm;
  geometryParameters["outCryoTopSealMainPart_halfWidth"] = 8.5 * mm;

  geometryParameters["outCryoTopSealUpperSubPart_innerRadius"] = 0. * mm;
  geometryParameters["outCryoTopSealUpperSubPart_outerRadius"] = 256.75 * mm;
  geometryParameters["outCryoTopSealUpperSubPart_halfWidth"] = (
    2.75 * mm +
    geometryParameters["booleanTolerance"]
  );

  geometryParameters["outCryoTopSealInnerLowerSubPart_innerRadius"] = 0. * mm;
  geometryParameters["outCryoTopSealInnerLowerSubPart_outerRadius"] = 254. * mm;
  geometryParameters["outCryoTopSealInnerLowerSubPart_halfWidth"] = (
    3.75 * mm +
    geometryParameters["booleanTolerance"]
  );

  geometryParameters["outCryoTopSealOuterLowerSubPart_innerRadius"] = 266.5 * mm;
  geometryParameters["outCryoTopSealOuterLowerSubPart_outerRadius"] = 272.5 * mm;
  geometryParameters["outCryoTopSealOuterLowerSubPart_halfWidth"] = (
    1.5 * mm +
    geometryParameters["booleanTolerance"]
  );

  geometryParameters["outCryoTopSealMainUpperSub_x"] = 0. * mm;
  geometryParameters["outCryoTopSealMainUpperSub_y"] = 0. * mm;
  geometryParameters["outCryoTopSealMainUpperSub_z"] = (
    geometryParameters["outCryoTopSealMainPart_halfWidth"] -
    geometryParameters["outCryoTopSealUpperSubPart_halfWidth"] +
    geometryParameters["booleanTolerance"]
  );

  geometryParameters["outCryoTopSealMainInnerLowerSub_x"] = 0. * mm;
  geometryParameters["outCryoTopSealMainInnerLowerSub_y"] = 0. * mm;
  geometryParameters["outCryoTopSealMainInnerLowerSub_z"] = - (
    geometryParameters["outCryoTopSealMainPart_halfWidth"] -
    geometryParameters["outCryoTopSealInnerLowerSubPart_halfWidth"] +
    geometryParameters["booleanTolerance"]
  );

  geometryParameters["outCryoTopSealMainOuterLowerSub_x"] = 0. * mm;
  geometryParameters["outCryoTopSealMainOuterLowerSub_y"] = 0. * mm;
  geometryParameters["outCryoTopSealMainOuterLowerSub_z"] = - (
    geometryParameters["outCryoTopSealMainPart_halfWidth"] -
    geometryParameters["outCryoTopSealOuterLowerSubPart_halfWidth"] +
    geometryParameters["booleanTolerance"]
  );

  geometryParameters["outCryoTopSeal_x"] = 0. * mm;
  geometryParameters["outCryoTopSeal_y"] = 0. * mm;
  geometryParameters["outCryoTopSeal_z"] = (
    geometryParameters["outCryoEnvelope_halfLength"] +
    geometryParameters["outCryoTopSealMainPart_halfWidth"] -
    7. * mm
  );

  // Top end cap
  geometryParameters["outCryoTopEndCapMainPart_innerRadius"] = 78.5 * mm;
  geometryParameters["outCryoTopEndCapMainPart_outerRadius"] = 275. * mm;
  geometryParameters["outCryoTopEndCapMainPart_halfWidth"] = 8.5 * mm;

  geometryParameters["outCryoTopEndCapUpperSubPart_innerRadius"] = 266.5 * mm;
  geometryParameters["outCryoTopEndCapUpperSubPart_outerRadius"] = 272.5 * mm;
  geometryParameters["outCryoTopEndCapUpperSubPart_halfWidth"] = (
    1.5 * mm +
    geometryParameters["booleanTolerance"]
  );

  geometryParameters["outCryoTopEndCapInnerLowerSubPart_innerRadius"] = 81.5 * mm;
  geometryParameters["outCryoTopEndCapInnerLowerSubPart_outerRadius"] = 84.5 * mm;
  geometryParameters["outCryoTopEndCapInnerLowerSubPart_halfWidth"] = (
    1.5 * mm +
    geometryParameters["booleanTolerance"]
  );

  geometryParameters["outCryoTopEndCapOuterLowerSubPart_innerRadius"] = 248. * mm;
  geometryParameters["outCryoTopEndCapOuterLowerSubPart_outerRadius"] = 251. * mm;
  geometryParameters["outCryoTopEndCapOuterLowerSubPart_halfWidth"] = (
    3. * mm +
    geometryParameters["booleanTolerance"]
  );

  geometryParameters["outCryoTopEndCapMainUpperSub_x"] = 0. * mm;
  geometryParameters["outCryoTopEndCapMainUpperSub_y"] = 0. * mm;
  geometryParameters["outCryoTopEndCapMainUpperSub_z"] = (
    geometryParameters["outCryoTopEndCapMainPart_halfWidth"] -
    geometryParameters["outCryoTopEndCapUpperSubPart_halfWidth"] +
    geometryParameters["booleanTolerance"]
  );

  geometryParameters["outCryoTopEndCapMainInnerLowerSub_x"] = 0. * mm;
  geometryParameters["outCryoTopEndCapMainInnerLowerSub_y"] = 0. * mm;
  geometryParameters["outCryoTopEndCapMainInnerLowerSub_z"] = - (
    geometryParameters["outCryoTopEndCapMainPart_halfWidth"] -
    geometryParameters["outCryoTopEndCapInnerLowerSubPart_halfWidth"] +
    geometryParameters["booleanTolerance"]
  );

  geometryParameters["outCryoTopEndCapMainOuterLowerSub_x"] = 0. * mm;
  geometryParameters["outCryoTopEndCapMainOuterLowerSub_y"] = 0. * mm;
  geometryParameters["outCryoTopEndCapMainOuterLowerSub_z"] = - (
    geometryParameters["outCryoTopEndCapMainPart_halfWidth"] -
    geometryParameters["outCryoTopEndCapOuterLowerSubPart_halfWidth"] +
    geometryParameters["booleanTolerance"]
  );

  geometryParameters["outCryoTopEndCap_x"] = 0. * mm;
  geometryParameters["outCryoTopEndCap_y"] = 0. * mm;
  geometryParameters["outCryoTopEndCap_z"] = (
    geometryParameters["outCryoTopSeal_z"] +
    geometryParameters["outCryoTopSealMainPart_halfWidth"] +
    geometryParameters["outCryoTopEndCapMainPart_halfWidth"]
  );

  // Top joint
  geometryParameters["outCryoTopJointMainPart_innerRadius"] = 248. * mm;
  geometryParameters["outCryoTopJointMainPart_outerRadius"] = 250.5 * mm;
  geometryParameters["outCryoTopJointMainPart_halfWidth"] = 7. * mm;

  geometryParameters["outCryoTopJointOuterPart_innerRadius"] = (
    250.5 * mm -
    geometryParameters["booleanTolerance"] // For boolean union
  );
  geometryParameters["outCryoTopJointOuterPart_outerRadius"] = 253.4 * mm; // Tuned to deal with overlaps (253.45 * mm in CAD)
  geometryParameters["outCryoTopJointOuterPart_halfWidth"] = 2.75 * mm; // Tuned to deal with overlaps (2.8 * mm in CAD)

  geometryParameters["outCryoTopJointOuterSubPart_innerRadius"] = 0. * mm;
  geometryParameters["outCryoTopJointOuterSubPart_outerRadius"] = 2.75 * mm; // Tuned to deal with overlaps (2.8 * mm in CAD)
  geometryParameters["outCryoTopJointOuterSubPart_sweptRadius"] = 253.4 * mm; // Tuned to deal with overlaps (253.45 * mm in CAD)

  geometryParameters["outCryoTopJointMainOuterUnion_x"] = 0. * mm;
  geometryParameters["outCryoTopJointMainOuterUnion_y"] = 0. * mm;
  geometryParameters["outCryoTopJointMainOuterUnion_z"] = 0. * mm;

  geometryParameters["outCryoTopJointOutersSub_x"] = 0. * mm;
  geometryParameters["outCryoTopJointOutersSub_y"] = 0. * mm;
  geometryParameters["outCryoTopJointOutersSub_z"] = 0. * mm;

  geometryParameters["outCryoTopJoint_x"] = 0. * mm;
  geometryParameters["outCryoTopJoint_y"] = 0. * mm;
  geometryParameters["outCryoTopJoint_z"] = (
    geometryParameters["outCryoTopSeal_z"] +
    geometryParameters["outCryoTopSealMainPart_halfWidth"] -
    2.75 * mm // Tuned to deal with overlaps (2.7 * mm in CAD)
  );

  // Column seal
  geometryParameters["outCryoColumnSealLowerPart_innerRadius"] = 78.7 * mm;
  geometryParameters["outCryoColumnSealLowerPart_outerRadius"] = 99.5 * mm;
  geometryParameters["outCryoColumnSealLowerPart_halfWidth"] = 6.2 * mm;

  geometryParameters["outCryoColumnSealUpperPart_innerRadius"] = 76. * mm;
  geometryParameters["outCryoColumnSealUpperPart_outerRadius"] = 99.5 * mm;
  geometryParameters["outCryoColumnSealUpperPart_halfWidth"] = 4.9 * mm;

  geometryParameters["outCryoColumnSealUpperLowerUnion_x"] = 0. * mm;
  geometryParameters["outCryoColumnSealUpperLowerUnion_y"] = 0. * mm;
  geometryParameters["outCryoColumnSealUpperLowerUnion_z"] = (
    geometryParameters["outCryoColumnSealLowerPart_halfWidth"] +
    geometryParameters["outCryoColumnSealUpperPart_halfWidth"]
  );

  geometryParameters["outCryoColumnSeal_x"] = 0. * mm;
  geometryParameters["outCryoColumnSeal_y"] = 0. * mm;
  geometryParameters["outCryoColumnSeal_z"] = (
    geometryParameters["outCryoTopEndCap_z"] +
    geometryParameters["outCryoTopEndCapMainPart_halfWidth"] +
    geometryParameters["outCryoColumnSealLowerPart_halfWidth"]
  );

  // Top end cap
  geometryParameters["outCryoColumnEndCap_innerRadius"] = 0. * mm;
  geometryParameters["outCryoColumnEndCap_outerRadius"] = 99.5 * mm;
  geometryParameters["outCryoColumnEndCap_halfWidth"] = 11.1 * mm;

  geometryParameters["outCryoColumnEndCap_x"] = 0. * mm;
  geometryParameters["outCryoColumnEndCap_y"] = 0. * mm;
  geometryParameters["outCryoColumnEndCap_z"] = (
    geometryParameters["outCryoColumnSeal_z"] +
    geometryParameters["outCryoColumnSealLowerPart_halfWidth"] +
    2 * geometryParameters["outCryoColumnSealUpperPart_halfWidth"] +
    geometryParameters["outCryoColumnEndCap_halfWidth"]
  );

  // Column
  geometryParameters["outCryoColumn_innerRadius"] = 76.5 * mm;
  geometryParameters["outCryoColumn_outerRadius"] = 78.5 * mm;
  geometryParameters["outCryoColumn_halfLength"] = 224.7 * mm;

  geometryParameters["outCryoColumn_x"] = 0. * mm;
  geometryParameters["outCryoColumn_y"] = 0. * mm;
  geometryParameters["outCryoColumn_z"] = (
    geometryParameters["outCryoColumnSeal_z"] +
    geometryParameters["outCryoColumnSealLowerPart_halfWidth"] -
    geometryParameters["outCryoColumn_halfLength"]
  );

  // ---------------------------------------------------------------------------
  // Copper envelope around inner cryostat

  // Half tube (base solid)
  // Aligned to the inner cryostat envelope to make multi-union easier
  // (true position set after union)
  geometryParameters["copperEnvelopeHalfTube_innerRadius"] = 128. * mm;
  geometryParameters["copperEnvelopeHalfTube_outerRadius"] = 129. * mm;
  geometryParameters["copperEnvelopeHalfTube_halfLength"] = 125. * mm;
  geometryParameters["copperEnvelopeHalfTube_startPhi"] = 3.664257656132 * deg;
  geometryParameters["copperEnvelopeHalfTube_dPhi"] = 172.671484687736 * deg;

  geometryParameters["copperEnvelopeHalfTube_x"] = 0. * mm;
  geometryParameters["copperEnvelopeHalfTube_y"] = 0. * mm;
  geometryParameters["copperEnvelopeHalfTube_z"] = 0. * mm;

  // Junction (base solid)
  geometryParameters["copperEnvelopeJunction_innerRadius"] = 4. * mm;
  geometryParameters["copperEnvelopeJunction_outerRadius"] = 5. * mm;
  geometryParameters["copperEnvelopeJunction_halfLength"] = 125. * mm;
  geometryParameters["copperEnvelopeJunction_startPhi"] = 270. * deg;
  geometryParameters["copperEnvelopeJunction_dPhi"] = 86.335742343959 * deg;

  geometryParameters["copperEnvelopeJunction_rho"] = 133 * mm;
  geometryParameters["copperEnvelopeJunction_phi"] = 176.335742343876 * deg;
  geometryParameters["copperEnvelopeJunction_x"] = (
    geometryParameters["copperEnvelopeJunction_rho"] *
    std::cos(geometryParameters["copperEnvelopeJunction_phi"])
  );
  geometryParameters["copperEnvelopeJunction_y"] = (
    geometryParameters["copperEnvelopeJunction_rho"] *
    std::sin(geometryParameters["copperEnvelopeJunction_phi"])
  );
  geometryParameters["copperEnvelopeJunction_z"] = geometryParameters["copperEnvelopeHalfTube_z"];

  // Long frame (base solid)
  geometryParameters["copperEnvelopeLongFrame_halfX"] = (
    27.6120169755 * mm +
    geometryParameters["booleanTolerance"]
  );
  geometryParameters["copperEnvelopeLongFrame_halfY"] = 0.5 * mm;
  geometryParameters["copperEnvelopeLongFrame_halfZ"] = 125. * mm;

  geometryParameters["copperEnvelopeLongFrame_x"] = (
    geometryParameters["copperEnvelopeJunction_x"] -
    geometryParameters["copperEnvelopeLongFrame_halfX"] +
    geometryParameters["booleanTolerance"]
  );
  geometryParameters["copperEnvelopeLongFrame_y"] = (
    geometryParameters["copperEnvelopeJunction_y"] -
    geometryParameters["copperEnvelopeJunction_innerRadius"] -
    geometryParameters["copperEnvelopeLongFrame_halfY"]
  );
  geometryParameters["copperEnvelopeLongFrame_z"] = geometryParameters["copperEnvelopeHalfTube_z"];

  // Short frame (base solid)
  geometryParameters["copperEnvelopeShortFrame_halfX"] = (
    10.1120169755 * mm +
    geometryParameters["booleanTolerance"]
  );
  geometryParameters["copperEnvelopeShortFrame_halfY"] = 0.5 * mm;
  geometryParameters["copperEnvelopeShortFrame_halfZ"] = 125. * mm;

  geometryParameters["copperEnvelopeShortFrame_x"] = - (
    geometryParameters["copperEnvelopeJunction_x"] -
    geometryParameters["copperEnvelopeShortFrame_halfX"] +
    geometryParameters["booleanTolerance"]
  );
  geometryParameters["copperEnvelopeShortFrame_y"] = (
    geometryParameters["copperEnvelopeJunction_y"] -
    geometryParameters["copperEnvelopeJunction_innerRadius"] -
    geometryParameters["copperEnvelopeShortFrame_halfY"]
  );
  geometryParameters["copperEnvelopeShortFrame_z"] = geometryParameters["copperEnvelopeHalfTube_z"];

  // Tongue tube
  geometryParameters["copperEnvelopeTongueTube_innerRadius"] = 3.05 * mm;
  geometryParameters["copperEnvelopeTongueTube_outerRadius"] = 4.05 * mm;
  geometryParameters["copperEnvelopeTongueTube_halfLength"] = 12. * mm;
  geometryParameters["copperEnvelopeTongueTube_startPhi"] = 47.423583589956 * deg;
  geometryParameters["copperEnvelopeTongueTube_dPhi"] = (
    315. * deg -
    geometryParameters["copperEnvelopeTongueTube_startPhi"]
  );

  geometryParameters["copperEnvelopeTongueTube_x"] = - 166 * mm;
  geometryParameters["copperEnvelopeTongueTube_y"] = 0. * mm;
  geometryParameters["copperEnvelopeTongueTube_z"] = (
    geometryParameters["copperEnvelopeHalfTube_z"] -
    geometryParameters["copperEnvelopeHalfTube_halfLength"] +
    geometryParameters["copperEnvelopeTongueTube_halfLength"]
  );

  // Tongue straight part
  geometryParameters["copperEnvelopeTongueStraightPart_halfX"] = 49.8730542807 * mm;
  geometryParameters["copperEnvelopeTongueStraightPart_halfY"] = 0.5 * mm;
  geometryParameters["copperEnvelopeTongueStraightPart_halfZ"] = 12. * mm;

  geometryParameters["copperEnvelopeTongueStraightPart_x"] = - 133.358245507564 * mm;
  geometryParameters["copperEnvelopeTongueStraightPart_y"] = 41.631116949941 * mm;
  geometryParameters["copperEnvelopeTongueStraightPart_z"] = (
    geometryParameters["copperEnvelopeHalfTube_z"] -
    geometryParameters["copperEnvelopeHalfTube_halfLength"] +
    geometryParameters["copperEnvelopeTongueStraightPart_halfZ"]
  );
  geometryParameters["copperEnvelopeTongueStraightPart_rotZ"] = 51.747632500513 * deg;

  // Tongue curved part
  geometryParameters["copperEnvelopeTongueCurvedPart_innerRadius"] = 130. * mm;
  geometryParameters["copperEnvelopeTongueCurvedPart_outerRadius"] = 131. * mm;
  geometryParameters["copperEnvelopeTongueCurvedPart_halfLength"] = 12. * mm;
  geometryParameters["copperEnvelopeTongueCurvedPart_startPhi"] = 90. * deg;
  geometryParameters["copperEnvelopeTongueCurvedPart_dPhi"] = 51.747632500598 * deg;

  geometryParameters["copperEnvelopeTongueCurvedPart_rho"] = 0. * mm;
  geometryParameters["copperEnvelopeTongueCurvedPart_phi"] = (
    geometryParameters["copperEnvelopeTongueCurvedPart_startPhi"] +
    geometryParameters["copperEnvelopeTongueCurvedPart_dPhi"] / 2
  );
  geometryParameters["copperEnvelopeTongueCurvedPart_z"] = (
    geometryParameters["copperEnvelopeHalfTube_z"] -
    geometryParameters["copperEnvelopeHalfTube_halfLength"] +
    geometryParameters["copperEnvelopeTongueCurvedPart_halfLength"]
  );

  // Half-envelope position
  geometryParameters["copperEnvelopeHalf_x"] = 0. * mm;
  geometryParameters["copperEnvelopeHalf_y"] = 0. * mm;
  geometryParameters["copperEnvelopeHalf_z"] = 0. * mm;

  // Full-envelope position
  geometryParameters["copperEnvelope_x"] = 0. * mm;
  geometryParameters["copperEnvelope_y"] = 0. * mm;
  geometryParameters["copperEnvelope_z"] = - (
    geometryParameters["innCryoEnvelope_halfLength"] -
    geometryParameters["copperEnvelopeHalfTube_halfLength"] +
    2 * geometryParameters["innCryoBotEndCap_halfWidth"]
  );

  // ---------------------------------------------------------------------------
  // Translation volumes

  // Inner cryostat
  geometryParameters["innCryoTranslation_innerRadius"] = 0. * mm;
  geometryParameters["innCryoTranslation_outerRadius"] = 190. * mm;
  geometryParameters["innCryoTranslation_halfLength"] = 176. * mm;

  geometryParameters["innCryoTranslation_x"] = 0. * mm;
  geometryParameters["innCryoTranslation_y"] = 0. * mm;
  geometryParameters["innCryoTranslation_z"] = - (
    geometryParameters["outCryoEnvelope_halfLength"] -
    geometryParameters["innCryoEnvelope_halfLength"] -
    54. * mm
  );

  // Outer cryostat
  geometryParameters["outCryoTranslation_innerRadius"] = 0. * mm;
  geometryParameters["outCryoTranslation_outerRadius"] = 278. * mm;
  geometryParameters["outCryoTranslation_halfLength"] = 412. * mm;

  geometryParameters["outCryoTranslation_x"] = 0. * mm;
  geometryParameters["outCryoTranslation_y"] = 0. * mm;
  geometryParameters["outCryoTranslation_z"] = 0. * mm;

  G4cout << "******************************************************" << G4endl;
  G4cout << "******** Printing geometry parameters (in mm) ********" << G4endl;
  for (auto it = geometryParameters.begin(); it != geometryParameters.end(); it ++)
  {
    G4cout << it->first << " = " << it->second << G4endl;
  }
  G4cout << "******************************************************" << G4endl;
}

void XelabDetectorConstruction::ConstructWorld()
{
  world_solid = new G4Box(
    "world_solid",
    geometryParameters["world_halfX"],
    geometryParameters["world_halfY"],
    geometryParameters["world_halfZ"]
  );

  world_logical = new G4LogicalVolume(world_solid, Air, "world_logical");
  world_logical->SetVisAttributes(G4VisAttributes::Invisible);

  world_physical = new G4PVPlacement(
    0, G4ThreeVector(0., 0., 0.),
    world_logical,
    "world_physical",
    0, false, 0, true
  );
}

void XelabDetectorConstruction::ConstructCryostat()
{
  // ---------------------------------------------------------------------------
  // Visualisation attributes

  // SS316Ti colour
  G4Colour SS316TiColour(0.7, 0.82, 0.98, 0.35);
  G4VisAttributes *SS316TiVisAtt = new G4VisAttributes(SS316TiColour);
  SS316TiVisAtt->SetVisibility(true);

  // Inner cryostat colour
  G4Colour innCryoColour(0.1, 0.5, 0.7, 1.0); //0.8);
  G4VisAttributes *innCryoVisAtt = new G4VisAttributes(innCryoColour);
  innCryoVisAtt->SetVisibility(true);

  // Outer cryostat colour
  G4Colour outCryoColour(0.7, 0.82, 0.98, 0.35);
  G4VisAttributes *outCryoVisAtt = new G4VisAttributes(outCryoColour);
  outCryoVisAtt->SetVisibility(true);

  // Column colour (tweaked outer cryostat colour)
  G4Colour columnColour(0.7, 0.82, 0.98, 0.2);
  G4VisAttributes *columnVisAtt = new G4VisAttributes(columnColour);
  columnVisAtt->SetVisibility(true);

  // Rubber colour
  G4Colour RubberColour(1.0, 0.8, 0.0, 0.8);
  G4VisAttributes *RubberVisAtt = new G4VisAttributes(RubberColour);
  RubberVisAtt->SetVisibility(true);

  // Copper colour
  G4Colour CopperColour(0.95, 0.53, 0.04, 1.0); //0.25);
  G4VisAttributes *CopperVisAtt = new G4VisAttributes(CopperColour);
  CopperVisAtt->SetVisibility(true);

  // ---------------------------------------------------------------------------
  // Inner cryostat

  // Hollow translation tube
  innCryoTranslation_solid = new G4Tubs(
    "innCryoTranslation_solid",
    geometryParameters["innCryoTranslation_innerRadius"],
    geometryParameters["innCryoTranslation_outerRadius"],
    geometryParameters["innCryoTranslation_halfLength"],
    0. * deg, 360. * deg
  );

  innCryoTranslation_logical = new G4LogicalVolume(
    innCryoTranslation_solid, Air, // To be updated when vacuum set between cryostats
    "innCryoTranslation_logical"
  );
  innCryoTranslation_logical->SetVisAttributes(G4VisAttributes::Invisible);

  G4ThreeVector innCryoTranslation_pos(
    geometryParameters["innCryoTranslation_x"],
    geometryParameters["innCryoTranslation_y"],
    geometryParameters["innCryoTranslation_z"]
  );

  innCryoTranslation_physical = new G4PVPlacement(
    0, innCryoTranslation_pos,
    innCryoTranslation_logical,
    "innCryoTranslation_physical",
    world_logical, false, 0, true
  );

  // Envelope
  innCryoEnvelope_solid = new G4Tubs(
    "innCryoEnvelope_solid",
    geometryParameters["innCryoEnvelope_innerRadius"],
    geometryParameters["innCryoEnvelope_outerRadius"],
    geometryParameters["innCryoEnvelope_halfLength"],
    0. * deg, 360. * deg
  );

  innCryoEnvelope_logical = new G4LogicalVolume(
    innCryoEnvelope_solid, SS316Ti,
    "innCryoEnvelope_logical"
  );
  innCryoEnvelope_logical->SetVisAttributes(innCryoVisAtt);

  G4ThreeVector innCryoEnvelope_pos(
    geometryParameters["innCryoEnvelope_x"],
    geometryParameters["innCryoEnvelope_y"],
    geometryParameters["innCryoEnvelope_z"]
  );

  innCryoEnvelope_physical = new G4PVPlacement(
    0, innCryoEnvelope_pos,
    innCryoEnvelope_logical,
    "innCryoEnvelope_physical",
    innCryoTranslation_logical, false, 0, true
  );

  // Bottom end cap
  innCryoBotEndCap_solid = new G4Tubs(
    "innCryoBotEndCap_solid",
    geometryParameters["innCryoBotEndCap_innerRadius"],
    geometryParameters["innCryoBotEndCap_outerRadius"],
    geometryParameters["innCryoBotEndCap_halfWidth"],
    0. * deg, 360. * deg
  );

  innCryoBotEndCap_logical = new G4LogicalVolume(
    innCryoBotEndCap_solid, SS316Ti,
    "innCryoBotEndCap_logical"
  );
  innCryoBotEndCap_logical->SetVisAttributes(innCryoVisAtt);

  G4ThreeVector innCryoBotEndCap_pos(
    geometryParameters["innCryoBotEndCap_x"],
    geometryParameters["innCryoBotEndCap_y"],
    geometryParameters["innCryoBotEndCap_z"]
  );

  innCryoBotEndCap_physical = new G4PVPlacement(
    0, innCryoBotEndCap_pos,
    innCryoBotEndCap_logical,
    "innCryoBotEndCap_physical",
    innCryoTranslation_logical, false, 0, true
  );

  // Top seal
  innCryoTopSealLowerPart_solid = new G4Tubs(
    "innCryoTopSealLowerPart_solid",
    geometryParameters["innCryoTopSealLowerPart_innerRadius"],
    geometryParameters["innCryoTopSealLowerPart_outerRadius"],
    geometryParameters["innCryoTopSealLowerPart_halfWidth"],
    0. * deg, 360. * deg
  );

  innCryoTopSealUpperPart_solid = new G4Tubs(
    "innCryoTopSealUpperPart_solid",
    geometryParameters["innCryoTopSealUpperPart_innerRadius"],
    geometryParameters["innCryoTopSealUpperPart_outerRadius"],
    geometryParameters["innCryoTopSealUpperPart_halfWidth"],
    0. * deg, 360. * deg
  );

  G4ThreeVector innCryoTopSealUpperLowerUnion_pos(
    geometryParameters["innCryoTopSealUpperLowerUnion_x"],
    geometryParameters["innCryoTopSealUpperLowerUnion_y"],
    geometryParameters["innCryoTopSealUpperLowerUnion_z"]
  );

  innCryoTopSeal_solid = new G4UnionSolid(
    "innCryoTopSeal_solid",
    innCryoTopSealLowerPart_solid,
    innCryoTopSealUpperPart_solid,
    0, innCryoTopSealUpperLowerUnion_pos
  );

  innCryoTopSeal_logical = new G4LogicalVolume(
    innCryoTopSeal_solid, SS316Ti,
    "innCryoTopSeal_logical"
  );
  innCryoTopSeal_logical->SetVisAttributes(innCryoVisAtt);

  G4ThreeVector innCryoTopSeal_pos(
    geometryParameters["innCryoTopSeal_x"],
    geometryParameters["innCryoTopSeal_y"],
    geometryParameters["innCryoTopSeal_z"]
  );

  innCryoTopSeal_physical = new G4PVPlacement(
    0, innCryoTopSeal_pos,
    innCryoTopSeal_logical,
    "innCryoTopSeal_physical",
    innCryoTranslation_logical, false, 0, true
  );

  // Top end cap
  innCryoTopEndCap_solid = new G4Tubs(
    "innCryoTopEndCap_solid",
    geometryParameters["innCryoTopEndCap_innerRadius"],
    geometryParameters["innCryoTopEndCap_outerRadius"],
    geometryParameters["innCryoTopEndCap_halfWidth"],
    0. * deg, 360. * deg
  );

  innCryoTopEndCap_logical = new G4LogicalVolume(
    innCryoTopEndCap_solid, SS316Ti,
    "innCryoTopEndCap_logical"
  );
  innCryoTopEndCap_logical->SetVisAttributes(innCryoVisAtt);

  G4ThreeVector innCryoTopEndCap_pos(
    geometryParameters["innCryoTopEndCap_x"],
    geometryParameters["innCryoTopEndCap_y"],
    geometryParameters["innCryoTopEndCap_z"]
  );

  innCryoTopEndCap_physical = new G4PVPlacement(
    0, innCryoTopEndCap_pos,
    innCryoTopEndCap_logical,
    "innCryoTopEndCap_physical",
    innCryoTranslation_logical, false, 0, true
  );

  // Pipe
  innCryoPipe_solid = new G4Tubs(
    "innCryoPipe_solid",
    geometryParameters["innCryoPipe_innerRadius"],
    geometryParameters["innCryoPipe_outerRadius"],
    geometryParameters["innCryoPipe_halfLength"],
    0. * deg, 360. * deg
  );

  innCryoPipe_logical = new G4LogicalVolume(
    innCryoPipe_solid, SS316Ti,
    "innCryoPipe_logical"
  );
  innCryoPipe_logical->SetVisAttributes(innCryoVisAtt);

  G4ThreeVector innCryoPipe_pos;
  innCryoPipe_pos.setRhoPhiZ(
    geometryParameters["innCryoPipe_rho"],
    geometryParameters["innCryoPipe_phi"],
    geometryParameters["innCryoPipe_z"]
  );

  innCryoPipe_physical = new G4PVPlacement(
    0, innCryoPipe_pos,
    innCryoPipe_logical,
    "innCryoPipe_physical",
    innCryoTranslation_logical, false, 0, true
  );

  // ---------------------------------------------------------------------------
  // Outer cryostat

  // Hollow translation tube
  outCryoTranslation_solid = new G4Tubs(
    "outCryoTranslation_solid",
    geometryParameters["outCryoTranslation_innerRadius"],
    geometryParameters["outCryoTranslation_outerRadius"],
    geometryParameters["outCryoTranslation_halfLength"],
    0. * deg, 360. * deg
  );

  outCryoTranslation_logical = new G4LogicalVolume(
    outCryoTranslation_solid, Air,
    "outCryoTranslation_logical"
  );
  outCryoTranslation_logical->SetVisAttributes(G4VisAttributes::Invisible);

  G4ThreeVector outCryoTranslation_pos(
    geometryParameters["outCryoTranslation_x"],
    geometryParameters["outCryoTranslation_y"],
    geometryParameters["outCryoTranslation_z"]
  );

  outCryoTranslation_physical = new G4PVPlacement(
    0, outCryoTranslation_pos,
    outCryoTranslation_logical,
    "outCryoTranslation_physical",
    world_logical, false, 0, true
  );

  // Envelope
  outCryoEnvelope_solid = new G4Tubs(
    "outCryoEnvelope_solid",
    geometryParameters["outCryoEnvelope_innerRadius"],
    geometryParameters["outCryoEnvelope_outerRadius"],
    geometryParameters["outCryoEnvelope_halfLength"],
    0. * deg, 360. * deg
  );

  outCryoEnvelope_logical = new G4LogicalVolume(
    outCryoEnvelope_solid, SS316Ti,
    "outCryoEnvelope_logical"
  );
  outCryoEnvelope_logical->SetVisAttributes(outCryoVisAtt);

  G4ThreeVector outCryoEnvelope_pos(
    geometryParameters["outCryoEnvelope_x"],
    geometryParameters["outCryoEnvelope_y"],
    geometryParameters["outCryoEnvelope_z"]
  );

  outCryoEnvelope_physical = new G4PVPlacement(
    0, outCryoEnvelope_pos,
    outCryoEnvelope_logical,
    "outCryoEnvelope_physical",
    outCryoTranslation_logical, false, 0, true
  );

  // Bottom end cap
  outCryoBotEndCap_solid = new G4Tubs(
    "outCryoBotEndCap_solid",
    geometryParameters["outCryoBotEndCap_innerRadius"],
    geometryParameters["outCryoBotEndCap_outerRadius"],
    geometryParameters["outCryoBotEndCap_halfWidth"],
    0. * deg, 360. * deg
  );

  outCryoBotEndCap_logical = new G4LogicalVolume(
    outCryoBotEndCap_solid, SS316Ti,
    "outCryoBotEndCap_logical"
  );
  outCryoBotEndCap_logical->SetVisAttributes(outCryoVisAtt);

  G4ThreeVector outCryoBotEndCap_pos(
    geometryParameters["outCryoBotEndCap_x"],
    geometryParameters["outCryoBotEndCap_y"],
    geometryParameters["outCryoBotEndCap_z"]
  );

  outCryoBotEndCap_physical = new G4PVPlacement(
    0, outCryoBotEndCap_pos,
    outCryoBotEndCap_logical,
    "outCryoBotEndCap_physical",
    outCryoTranslation_logical, false, 0, true
  );

  // Top seal
  outCryoTopSealMainPart_solid = new G4Tubs(
    "outCryoTopSealMainPart_solid",
    geometryParameters["outCryoTopSealMainPart_innerRadius"],
    geometryParameters["outCryoTopSealMainPart_outerRadius"],
    geometryParameters["outCryoTopSealMainPart_halfWidth"],
    0. * deg, 360. * deg
  );

  outCryoTopSealUpperSubPart_solid = new G4Tubs(
    "outCryoTopSealUpperSubPart_solid",
    geometryParameters["outCryoTopSealUpperSubPart_innerRadius"],
    geometryParameters["outCryoTopSealUpperSubPart_outerRadius"],
    geometryParameters["outCryoTopSealUpperSubPart_halfWidth"],
    0. * deg, 360. * deg
  );

  G4ThreeVector outCryoTopSealMainUpperSub_pos(
    geometryParameters["outCryoTopSealMainUpperSub_x"],
    geometryParameters["outCryoTopSealMainUpperSub_y"],
    geometryParameters["outCryoTopSealMainUpperSub_z"]
  );

  outCryoTopSeal_sub1_solid = new G4SubtractionSolid(
    "outCryoTopSeal_sub1_solid",
    outCryoTopSealMainPart_solid,
    outCryoTopSealUpperSubPart_solid,
    0, outCryoTopSealMainUpperSub_pos
  );

  outCryoTopSealInnerLowerSubPart_solid = new G4Tubs(
    "outCryoTopSealInnerLowerSubPart_solid",
    geometryParameters["outCryoTopSealInnerLowerSubPart_innerRadius"],
    geometryParameters["outCryoTopSealInnerLowerSubPart_outerRadius"],
    geometryParameters["outCryoTopSealInnerLowerSubPart_halfWidth"],
    0. * deg, 360. * deg
  );

  G4ThreeVector outCryoTopSealMainInnerLowerSub_pos(
    geometryParameters["outCryoTopSealMainInnerLowerSub_x"],
    geometryParameters["outCryoTopSealMainInnerLowerSub_y"],
    geometryParameters["outCryoTopSealMainInnerLowerSub_z"]
  );

  outCryoTopSeal_sub2_solid = new G4SubtractionSolid(
    "outCryoTopSeal_sub2_solid",
    outCryoTopSeal_sub1_solid,
    outCryoTopSealInnerLowerSubPart_solid,
    0, outCryoTopSealMainInnerLowerSub_pos
  );

  outCryoTopSealOuterLowerSubPart_solid = new G4Tubs(
    "outCryoTopSealOuterLowerSubPart_solid",
    geometryParameters["outCryoTopSealOuterLowerSubPart_innerRadius"],
    geometryParameters["outCryoTopSealOuterLowerSubPart_outerRadius"],
    geometryParameters["outCryoTopSealOuterLowerSubPart_halfWidth"],
    0. * deg, 360. * deg
  );

  G4ThreeVector outCryoTopSealMainOuterLowerSub_pos(
    geometryParameters["outCryoTopSealMainOuterLowerSub_x"],
    geometryParameters["outCryoTopSealMainOuterLowerSub_y"],
    geometryParameters["outCryoTopSealMainOuterLowerSub_z"]
  );

  outCryoTopSeal_solid = new G4SubtractionSolid(
    "outCryoTopSeal_solid",
    outCryoTopSeal_sub2_solid,
    outCryoTopSealOuterLowerSubPart_solid,
    0, outCryoTopSealMainOuterLowerSub_pos
  );

  outCryoTopSeal_logical = new G4LogicalVolume(
    outCryoTopSeal_solid, SS316Ti,
    "outCryoTopSeal_logical"
  );
  outCryoTopSeal_logical->SetVisAttributes(outCryoVisAtt);

  G4ThreeVector outCryoTopSeal_pos(
    geometryParameters["outCryoTopSeal_x"],
    geometryParameters["outCryoTopSeal_y"],
    geometryParameters["outCryoTopSeal_z"]
  );

  outCryoTopSeal_physical = new G4PVPlacement(
    0, outCryoTopSeal_pos,
    outCryoTopSeal_logical,
    "outCryoTopSeal_physical",
    outCryoTranslation_logical, false, 0, true
  );

  // Top end cap
  outCryoTopEndCapMainPart_solid = new G4Tubs(
    "outCryoTopEndCapMainPart_solid",
    geometryParameters["outCryoTopEndCapMainPart_innerRadius"],
    geometryParameters["outCryoTopEndCapMainPart_outerRadius"],
    geometryParameters["outCryoTopEndCapMainPart_halfWidth"],
    0. * deg, 360. * deg
  );

  outCryoTopEndCapUpperSubPart_solid = new G4Tubs(
    "outCryoTopEndCapUpperSubPart_solid",
    geometryParameters["outCryoTopEndCapUpperSubPart_innerRadius"],
    geometryParameters["outCryoTopEndCapUpperSubPart_outerRadius"],
    geometryParameters["outCryoTopEndCapUpperSubPart_halfWidth"],
    0. * deg, 360. * deg
  );

  G4ThreeVector outCryoTopEndCapMainUpperSub_pos(
    geometryParameters["outCryoTopEndCapMainUpperSub_x"],
    geometryParameters["outCryoTopEndCapMainUpperSub_y"],
    geometryParameters["outCryoTopEndCapMainUpperSub_z"]
  );

  outCryoTopEndCap_sub1_solid = new G4SubtractionSolid(
    "outCryoTopEndCap_sub1_solid",
    outCryoTopEndCapMainPart_solid,
    outCryoTopEndCapUpperSubPart_solid,
    0, outCryoTopEndCapMainUpperSub_pos
  );

  outCryoTopEndCapInnerLowerSubPart_solid = new G4Tubs(
    "outCryoTopEndCapInnerLowerSubPart_solid",
    geometryParameters["outCryoTopEndCapInnerLowerSubPart_innerRadius"],
    geometryParameters["outCryoTopEndCapInnerLowerSubPart_outerRadius"],
    geometryParameters["outCryoTopEndCapInnerLowerSubPart_halfWidth"],
    0. * deg, 360. * deg
  );

  G4ThreeVector outCryoTopEndCapMainInnerLowerSub_pos(
    geometryParameters["outCryoTopEndCapMainInnerLowerSub_x"],
    geometryParameters["outCryoTopEndCapMainInnerLowerSub_y"],
    geometryParameters["outCryoTopEndCapMainInnerLowerSub_z"]
  );

  outCryoTopEndCap_sub2_solid = new G4SubtractionSolid(
    "outCryoTopEndCap_sub2_solid",
    outCryoTopEndCap_sub1_solid,
    outCryoTopEndCapInnerLowerSubPart_solid,
    0, outCryoTopEndCapMainInnerLowerSub_pos
  );

  outCryoTopEndCapOuterLowerSubPart_solid = new G4Tubs(
    "outCryoTopEndCapOuterLowerSubPart_solid",
    geometryParameters["outCryoTopEndCapOuterLowerSubPart_innerRadius"],
    geometryParameters["outCryoTopEndCapOuterLowerSubPart_outerRadius"],
    geometryParameters["outCryoTopEndCapOuterLowerSubPart_halfWidth"],
    0. * deg, 360. * deg
  );

  G4ThreeVector outCryoTopEndCapMainOuterLowerSub_pos(
    geometryParameters["outCryoTopEndCapMainOuterLowerSub_x"],
    geometryParameters["outCryoTopEndCapMainOuterLowerSub_y"],
    geometryParameters["outCryoTopEndCapMainOuterLowerSub_z"]
  );

  outCryoTopEndCap_solid = new G4SubtractionSolid(
    "outCryoTopEndCap_solid",
    outCryoTopEndCap_sub2_solid,
    outCryoTopEndCapOuterLowerSubPart_solid,
    0, outCryoTopEndCapMainOuterLowerSub_pos
  );

  outCryoTopEndCap_logical = new G4LogicalVolume(
    outCryoTopEndCap_solid, SS316Ti,
    "outCryoTopEndCap_logical"
  );
  outCryoTopEndCap_logical->SetVisAttributes(outCryoVisAtt);

  G4ThreeVector outCryoTopEndCap_pos(
    geometryParameters["outCryoTopEndCap_x"],
    geometryParameters["outCryoTopEndCap_y"],
    geometryParameters["outCryoTopEndCap_z"]
  );

  outCryoTopEndCap_physical = new G4PVPlacement(
    0, outCryoTopEndCap_pos,
    outCryoTopEndCap_logical,
    "outCryoTopEndCap_physical",
    outCryoTranslation_logical, false, 0, true
  );

  // Top joint
  outCryoTopJointOuterPart_solid = new G4Tubs(
    "outCryoTopJointOuterPart_solid",
    geometryParameters["outCryoTopJointOuterPart_innerRadius"],
    geometryParameters["outCryoTopJointOuterPart_outerRadius"],
    geometryParameters["outCryoTopJointOuterPart_halfWidth"],
    0. * deg, 360. * deg
  );

  outCryoTopJointOuterSubPart_solid = new G4Torus(
    "outCryoTopJointOuterSubPart_solid",
    geometryParameters["outCryoTopJointOuterSubPart_innerRadius"],
    geometryParameters["outCryoTopJointOuterSubPart_outerRadius"],
    geometryParameters["outCryoTopJointOuterSubPart_sweptRadius"],
    0. * deg, 360. * deg
  );

  G4ThreeVector outCryoTopJointOutersSub_pos(
    geometryParameters["outCryoTopJointOutersSub_x"],
    geometryParameters["outCryoTopJointOutersSub_y"],
    geometryParameters["outCryoTopJointOutersSub_z"]
  );

  outCryoTopJoint_sub_solid = new G4SubtractionSolid(
    "outCryoTopJoint_sub_solid",
    outCryoTopJointOuterPart_solid,
    outCryoTopJointOuterSubPart_solid,
    0, outCryoTopJointOutersSub_pos
  );

  outCryoTopJointMainPart_solid = new G4Tubs(
    "outCryoTopJointMainPart_solid",
    geometryParameters["outCryoTopJointMainPart_innerRadius"],
    geometryParameters["outCryoTopJointMainPart_outerRadius"],
    geometryParameters["outCryoTopJointMainPart_halfWidth"],
    0. * deg, 360. * deg
  );

  G4ThreeVector outCryoTopJointMainOuterUnion_pos(
    geometryParameters["outCryoTopJointMainOuterUnion_x"],
    geometryParameters["outCryoTopJointMainOuterUnion_y"],
    geometryParameters["outCryoTopJointMainOuterUnion_z"]
  );

  outCryoTopJoint_solid = new G4UnionSolid(
    "outCryoTopJoint_solid",
    outCryoTopJointMainPart_solid,
    outCryoTopJoint_sub_solid,
    0, outCryoTopJointMainOuterUnion_pos
  );

  outCryoTopJoint_logical = new G4LogicalVolume(
    outCryoTopJoint_solid, Rubber,
    "outCryoTopJoint_logical"
  );
  outCryoTopJoint_logical->SetVisAttributes(RubberVisAtt);

  G4ThreeVector outCryoTopJoint_pos(
    geometryParameters["outCryoTopJoint_x"],
    geometryParameters["outCryoTopJoint_y"],
    geometryParameters["outCryoTopJoint_z"]
  );

  outCryoTopJoint_physical = new G4PVPlacement(
    0, outCryoTopJoint_pos,
    outCryoTopJoint_logical,
    "outCryoTopJoint_physical",
    outCryoTranslation_logical, false, 0, true
  );

  // Column seal
  outCryoColumnSealLowerPart_solid = new G4Tubs(
    "outCryoColumnSealLowerPart_solid",
    geometryParameters["outCryoColumnSealLowerPart_innerRadius"],
    geometryParameters["outCryoColumnSealLowerPart_outerRadius"],
    geometryParameters["outCryoColumnSealLowerPart_halfWidth"],
    0. * deg, 360. * deg
  );

  outCryoColumnSealUpperPart_solid = new G4Tubs(
    "outCryoColumnSealUpperPart_solid",
    geometryParameters["outCryoColumnSealUpperPart_innerRadius"],
    geometryParameters["outCryoColumnSealUpperPart_outerRadius"],
    geometryParameters["outCryoColumnSealUpperPart_halfWidth"],
    0. * deg, 360. * deg
  );

  G4ThreeVector outCryoColumnSealUpperLowerUnion_pos(
    geometryParameters["outCryoColumnSealUpperLowerUnion_x"],
    geometryParameters["outCryoColumnSealUpperLowerUnion_y"],
    geometryParameters["outCryoColumnSealUpperLowerUnion_z"]
  );

  outCryoColumnSeal_solid = new G4UnionSolid(
    "outCryoColumnSeal_solid",
    outCryoColumnSealLowerPart_solid,
    outCryoColumnSealUpperPart_solid,
    0, outCryoColumnSealUpperLowerUnion_pos
  );

  outCryoColumnSeal_logical = new G4LogicalVolume(
    outCryoColumnSeal_solid, SS316Ti,
    "outCryoColumnSeal_logical"
  );
  outCryoColumnSeal_logical->SetVisAttributes(outCryoVisAtt);

  G4ThreeVector outCryoColumnSeal_pos(
    geometryParameters["outCryoColumnSeal_x"],
    geometryParameters["outCryoColumnSeal_y"],
    geometryParameters["outCryoColumnSeal_z"]
  );

  outCryoColumnSeal_physical = new G4PVPlacement(
    0, outCryoColumnSeal_pos,
    outCryoColumnSeal_logical,
    "outCryoColumnSeal_physical",
    outCryoTranslation_logical, false, 0, true
  );

  // Column end cap
  outCryoColumnEndCap_solid = new G4Tubs(
    "outCryoColumnEndCap_solid",
    geometryParameters["outCryoColumnEndCap_innerRadius"],
    geometryParameters["outCryoColumnEndCap_outerRadius"],
    geometryParameters["outCryoColumnEndCap_halfWidth"],
    0. * deg, 360. * deg
  );

  outCryoColumnEndCap_logical = new G4LogicalVolume(
    outCryoColumnEndCap_solid, SS316Ti,
    "outCryoColumnEndCap_logical"
  );
  outCryoColumnEndCap_logical->SetVisAttributes(outCryoVisAtt);

  G4ThreeVector outCryoColumnEndCap_pos(
    geometryParameters["outCryoColumnEndCap_x"],
    geometryParameters["outCryoColumnEndCap_y"],
    geometryParameters["outCryoColumnEndCap_z"]
  );

  outCryoColumnEndCap_physical = new G4PVPlacement(
    0, outCryoColumnEndCap_pos,
    outCryoColumnEndCap_logical,
    "outCryoColumnEndCap_physical",
    outCryoTranslation_logical, false, 0, true
  );

  // Column
  outCryoColumn_solid = new G4Tubs(
    "outCryoColumn_solid",
    geometryParameters["outCryoColumn_innerRadius"],
    geometryParameters["outCryoColumn_outerRadius"],
    geometryParameters["outCryoColumn_halfLength"],
    0. * deg, 360. * deg
  );

  outCryoColumn_logical = new G4LogicalVolume(
    outCryoColumn_solid, SS316Ti,
    "outCryoColumn_logical"
  );
  outCryoColumn_logical->SetVisAttributes(columnVisAtt);

  G4ThreeVector outCryoColumn_pos(
    geometryParameters["outCryoColumn_x"],
    geometryParameters["outCryoColumn_y"],
    geometryParameters["outCryoColumn_z"]
  );

  outCryoColumn_physical = new G4PVPlacement(
    0, outCryoColumn_pos,
    outCryoColumn_logical,
    "outCryoColumn_physical",
    outCryoTranslation_logical, false, 0, true
  );

  // ---------------------------------------------------------------------------
  // Copper envelope around inner cryostat

  // First half multi-union initialisation
  copperEnvelopeFirstHalf_solid = new G4MultiUnion("copperEnvelopeFirstHalf_solid");

  // Half tube base
  copperEnvelopeHalfTube_solid = new G4Tubs(
    "copperEnvelopeHalfTube_solid",
    geometryParameters["copperEnvelopeHalfTube_innerRadius"],
    geometryParameters["copperEnvelopeHalfTube_outerRadius"],
    geometryParameters["copperEnvelopeHalfTube_halfLength"],
    geometryParameters["copperEnvelopeHalfTube_startPhi"],
    geometryParameters["copperEnvelopeHalfTube_dPhi"]
  );

  G4ThreeVector copperEnvelopeHalfTube_pos(
    geometryParameters["copperEnvelopeHalfTube_x"],
    geometryParameters["copperEnvelopeHalfTube_y"],
    geometryParameters["copperEnvelopeHalfTube_z"]
  );

  G4Transform3D copperEnvelopeHalfTube_placement = G4Transform3D(
    nullRotation,
    copperEnvelopeHalfTube_pos
  );

  copperEnvelopeFirstHalf_solid->AddNode(
    *copperEnvelopeHalfTube_solid,
    copperEnvelopeHalfTube_placement
  );

  // Junction base
  copperEnvelopeJunction_solid = new G4Tubs(
    "copperEnvelopeJunction_solid",
    geometryParameters["copperEnvelopeJunction_innerRadius"],
    geometryParameters["copperEnvelopeJunction_outerRadius"],
    geometryParameters["copperEnvelopeJunction_halfLength"],
    geometryParameters["copperEnvelopeJunction_startPhi"],
    geometryParameters["copperEnvelopeJunction_dPhi"]
  );

  G4ThreeVector copperEnvelopeJunction_pos;
  copperEnvelopeJunction_pos.setRhoPhiZ(
    geometryParameters["copperEnvelopeJunction_rho"],
    geometryParameters["copperEnvelopeJunction_phi"],
    geometryParameters["copperEnvelopeJunction_z"]
  );

  G4Transform3D copperEnvelopeJunction_placement = G4Transform3D(
    nullRotation,
    copperEnvelopeJunction_pos
  );

  copperEnvelopeFirstHalf_solid->AddNode(
    *copperEnvelopeJunction_solid,
    copperEnvelopeJunction_placement
  );

  // Long frame
  copperEnvelopeLongFrame_solid = new G4Box(
    "copperEnvelopeLongFrame_solid",
    geometryParameters["copperEnvelopeLongFrame_halfX"],
    geometryParameters["copperEnvelopeLongFrame_halfY"],
    geometryParameters["copperEnvelopeLongFrame_halfZ"]
  );

  G4ThreeVector copperEnvelopeLongFrame_pos(
    geometryParameters["copperEnvelopeLongFrame_x"],
    geometryParameters["copperEnvelopeLongFrame_y"],
    geometryParameters["copperEnvelopeLongFrame_z"]
  );

  G4Transform3D copperEnvelopeLongFrame_placement = G4Transform3D(
    nullRotation,
    copperEnvelopeLongFrame_pos
  );

  copperEnvelopeFirstHalf_solid->AddNode(
    *copperEnvelopeLongFrame_solid,
    copperEnvelopeLongFrame_placement
  );

  // Y-rotated junction
  G4RotationMatrix *copperEnvelopeJunctionRotY_rot = new G4RotationMatrix();
  copperEnvelopeJunctionRotY_rot->rotateY(180. * deg);
  G4Transform3D copperEnvelopeJunctionRotY_transformation(
    *copperEnvelopeJunctionRotY_rot,
    nullTranslation
  );

  copperEnvelopeJunctionRotY_solid = new G4DisplacedSolid(
    "copperEnvelopeJunctionRotY_solid",
    copperEnvelopeJunction_solid,
    copperEnvelopeJunctionRotY_transformation
  );

  G4ThreeVector copperEnvelopeJunctionRotY_pos;
  copperEnvelopeJunctionRotY_pos.setRhoPhiZ(
    geometryParameters["copperEnvelopeJunction_rho"],
    180 * deg - geometryParameters["copperEnvelopeJunction_phi"],
    geometryParameters["copperEnvelopeJunction_z"]
  );

  G4Transform3D copperEnvelopeJunctionRotY_placement = G4Transform3D(
    nullRotation,
    copperEnvelopeJunctionRotY_pos
  );

  copperEnvelopeFirstHalf_solid->AddNode(
    *copperEnvelopeJunctionRotY_solid,
    copperEnvelopeJunctionRotY_placement
  );

  // Short frame
  copperEnvelopeShortFrame_solid = new G4Box(
    "copperEnvelopeShortFrame_solid",
    geometryParameters["copperEnvelopeShortFrame_halfX"],
    geometryParameters["copperEnvelopeShortFrame_halfY"],
    geometryParameters["copperEnvelopeShortFrame_halfZ"]
  );

  G4ThreeVector copperEnvelopeShortFrame_pos(
    geometryParameters["copperEnvelopeShortFrame_x"],
    geometryParameters["copperEnvelopeShortFrame_y"],
    geometryParameters["copperEnvelopeShortFrame_z"]
  );

  G4Transform3D copperEnvelopeShortFrame_placement = G4Transform3D(
    nullRotation,
    copperEnvelopeShortFrame_pos
  );

  copperEnvelopeFirstHalf_solid->AddNode(
    *copperEnvelopeShortFrame_solid,
    copperEnvelopeShortFrame_placement
  );

  // First half multi-union completion
  copperEnvelopeFirstHalf_solid->Voxelize();

  // Second half (X-rotated first half-envelope)
  G4RotationMatrix *copperEnvelopeSecondHalf_rot = new G4RotationMatrix();
  copperEnvelopeSecondHalf_rot->rotateX(180. * deg);
  G4Transform3D copperEnvelopeSecondHalf_transformation(
    *copperEnvelopeSecondHalf_rot,
    nullTranslation
  );

  copperEnvelopeSecondHalf_solid = new G4DisplacedSolid(
    "copperEnvelopeSecondHalf_solid",
    copperEnvelopeFirstHalf_solid,
    copperEnvelopeSecondHalf_transformation
  );

  // Tongue tube
  copperEnvelopeTongueTube_solid = new G4Tubs(
    "copperEnvelopeTongueTube_solid",
    geometryParameters["copperEnvelopeTongueTube_innerRadius"],
    geometryParameters["copperEnvelopeTongueTube_outerRadius"],
    geometryParameters["copperEnvelopeTongueTube_halfLength"],
    geometryParameters["copperEnvelopeTongueTube_startPhi"],
    geometryParameters["copperEnvelopeTongueTube_dPhi"]
  );

  // Tongue straight part
  copperEnvelopeTongueStraightPart_solid = new G4Box(
    "copperEnvelopeTongueStraightPart_solid",
    geometryParameters["copperEnvelopeTongueStraightPart_halfX"],
    geometryParameters["copperEnvelopeTongueStraightPart_halfY"],
    geometryParameters["copperEnvelopeTongueStraightPart_halfZ"]
  );

  // Tongue curved part
  copperEnvelopeTongueCurvedPart_solid = new G4Tubs(
    "copperEnvelopeTongueCurvedPart_solid",
    geometryParameters["copperEnvelopeTongueCurvedPart_innerRadius"],
    geometryParameters["copperEnvelopeTongueCurvedPart_outerRadius"],
    geometryParameters["copperEnvelopeTongueCurvedPart_halfLength"],
    geometryParameters["copperEnvelopeTongueCurvedPart_startPhi"],
    geometryParameters["copperEnvelopeTongueCurvedPart_dPhi"]
  );

  // Final multi-union
  copperEnvelope_solid = new G4MultiUnion("copperEnvelope_solid");

  G4ThreeVector copperEnvelopeHalf_pos(
    geometryParameters["copperEnvelopeHalf_x"],
    geometryParameters["copperEnvelopeHalf_y"],
    geometryParameters["copperEnvelopeHalf_z"]
  );
  G4Transform3D copperEnvelopeHalf_placement = G4Transform3D(
    nullRotation, copperEnvelopeHalf_pos
  );
  copperEnvelope_solid->AddNode(
    *copperEnvelopeFirstHalf_solid,
    copperEnvelopeHalf_placement
  );
  copperEnvelope_solid->AddNode(
    *copperEnvelopeSecondHalf_solid,
    copperEnvelopeHalf_placement
  );

  G4ThreeVector copperEnvelopeTongueTube_pos(
    geometryParameters["copperEnvelopeTongueTube_x"],
    geometryParameters["copperEnvelopeTongueTube_y"],
    geometryParameters["copperEnvelopeTongueTube_z"]
  );
  G4Transform3D copperEnvelopeTongueTube_placement = G4Transform3D(
    nullRotation, copperEnvelopeTongueTube_pos
  );
  copperEnvelope_solid->AddNode(
    *copperEnvelopeTongueTube_solid,
    copperEnvelopeTongueTube_placement
  );

  G4RotationMatrix *copperEnvelopeTongueStraightPart_rot = new G4RotationMatrix();
  copperEnvelopeTongueStraightPart_rot->rotateZ(
    geometryParameters["copperEnvelopeTongueStraightPart_rotZ"]
  );
  G4ThreeVector copperEnvelopeTongueStraightPart_pos(
    geometryParameters["copperEnvelopeTongueStraightPart_x"],
    geometryParameters["copperEnvelopeTongueStraightPart_y"],
    geometryParameters["copperEnvelopeTongueStraightPart_z"]
  );
  G4Transform3D copperEnvelopeTongueStraightPart_placement = G4Transform3D(
    *copperEnvelopeTongueStraightPart_rot, copperEnvelopeTongueStraightPart_pos
  );
  copperEnvelope_solid->AddNode(
    *copperEnvelopeTongueStraightPart_solid,
    copperEnvelopeTongueStraightPart_placement
  );

  G4ThreeVector copperEnvelopeTongueCurvedPart_pos;
  copperEnvelopeTongueCurvedPart_pos.setRhoPhiZ(
    geometryParameters["copperEnvelopeTongueCurvedPart_rho"],
    geometryParameters["copperEnvelopeTongueCurvedPart_phi"],
    geometryParameters["copperEnvelopeTongueCurvedPart_z"]
  );
  G4Transform3D copperEnvelopeTongueCurvedPart_placement = G4Transform3D(
    nullRotation, copperEnvelopeTongueCurvedPart_pos
  );
  copperEnvelope_solid->AddNode(
    *copperEnvelopeTongueCurvedPart_solid,
    copperEnvelopeTongueCurvedPart_placement
  );

  copperEnvelope_solid->Voxelize();

  copperEnvelope_logical = new G4LogicalVolume(
    copperEnvelope_solid, Copper,
    "copperEnvelope_logical"
  );
  copperEnvelope_logical->SetVisAttributes(CopperVisAtt);

  G4ThreeVector copperEnvelope_pos(
    geometryParameters["copperEnvelope_x"],
    geometryParameters["copperEnvelope_y"],
    geometryParameters["copperEnvelope_z"]
  );

  copperEnvelope_physical = new G4PVPlacement(
    0, copperEnvelope_pos,
    copperEnvelope_logical,
    "copperEnvelope_physical",
    innCryoTranslation_logical, false, 0, true
  );












  // // Get the position of two volumes
  // G4ThreeVector pos1 = outCryoBotEndCap_physical->GetTranslation();
  // G4ThreeVector hollow = innCryoTranslation_physical->GetTranslation();
  // G4ThreeVector pos2 = innCryoBotEndCap_physical->GetTranslation() + hollow;
  //
  // // Calculate the distance along the z-axis
  // G4double dz = pos2.z() - pos1.z();
  //
  // // Print the positions
  // G4cout << outCryoBotEndCap_physical->GetName() << " position: " << pos1 << " mm" << G4endl;
  // G4cout << innCryoBotEndCap_physical->GetName() << " position: " << pos2 << " mm" << G4endl;
  //
  // // Print the distance
  // G4cout << "Distance along z-axis between " << outCryoBotEndCap_physical->GetName()
  //        << " and " << innCryoBotEndCap_physical->GetName() << ": " << dz << " mm" << G4endl;



  G4cout << "XelabDetectorConstruction::ConstructCryostat - "
            "Finished building cryostat geometry"
         << G4endl;

}

G4VPhysicalVolume *XelabDetectorConstruction::Construct()
{
  DefineGeometryParameters();

  DefineMaterials();

  ConstructWorld();

  ConstructCryostat();

  return world_physical;
};
