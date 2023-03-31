#include "Arduino.h"

#include "GrowattET340.h"

// information from:
// https://gavazzi.se/produkter/et340dinav23xs1x/
// https://gavazzi.se/app/uploads/2020/11/em330_em340_et330_et340_cp.pdf

// Supported inverters:
// - Victron ET340
// - Victron EM24

void addFragment(sProtocolDefinition_t &Protocol, uint8_t &fragmentID,
                 const ePET340InputRegisters_t &start,
                 const ePET340InputRegisters_t &end) {
  Protocol.InputReadFragments[fragmentID++] = sGrowattReadFragment_t{
      Protocol.InputRegisters[start].address,
      static_cast<uint8_t>(Protocol.InputRegisters[end].address +
                           Protocol.InputRegisters[end].size -
                           Protocol.InputRegisters[start].address)};
}

void init_growattET340(sProtocolDefinition_t &Protocol) {
  // definition of input registers
  Protocol.InputRegisterCount = ePET340InputRegisters_t::LASTInput;
  uint8_t fragmentID = 0;

  // FRAGMENT 1: BEGIN
  Protocol.InputRegisters[ET340_VL1_N] = sGrowattModbusReg_t{
      0x0000,   0,       SIZE_32BIT, "V L1-N", 1.0 / 10,
      1.0 / 10, VOLTAGE, true,       false,    ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_VL2_N] = sGrowattModbusReg_t{
      0x0002,   0,       SIZE_32BIT, "V L2-N", 1.0 / 10,
      1.0 / 10, VOLTAGE, true,       false,    ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_VL3_N] = sGrowattModbusReg_t{
      0x0004,   0,       SIZE_32BIT, "V L3-N", 1.0 / 10,
      1.0 / 10, VOLTAGE, true,       false,    ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_VL1_L2] = sGrowattModbusReg_t{
      0x0006,   0,       SIZE_32BIT, "V L1-L2", 1.0 / 10,
      1.0 / 10, VOLTAGE, false,      false,     ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_VL2_L3] = sGrowattModbusReg_t{
      0x0008,   0,       SIZE_32BIT, "V L2-L3", 1.0 / 10,
      1.0 / 10, VOLTAGE, false,      false,     ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_VL3_L1] = sGrowattModbusReg_t{
      0x000A,   0,       SIZE_32BIT, "V L3-L1", 1.0 / 10,
      1.0 / 10, VOLTAGE, false,      false,     ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_AL1] = sGrowattModbusReg_t{
      0x000C,     0,       SIZE_32BIT, "A L1", 1.0 / 1000,
      1.0 / 1000, CURRENT, true,       false,  ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_AL2] = sGrowattModbusReg_t{
      0x000E,     0,       SIZE_32BIT, "A L2", 1.0 / 1000,
      1.0 / 1000, CURRENT, true,       false,  ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_AL3] = sGrowattModbusReg_t{
      0x0010,     0,       SIZE_32BIT, "A L3", 1.0 / 1000,
      1.0 / 1000, CURRENT, true,       false,  ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_WL1] = sGrowattModbusReg_t{
      0x0012,   0,       SIZE_32BIT, "W L1", 1.0 / 10,
      1.0 / 10, POWER_W, true,       true,   ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_WL2] = sGrowattModbusReg_t{
      0x0014,   0,       SIZE_32BIT, "W L2", 1.0 / 10,
      1.0 / 10, POWER_W, true,       true,   ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_WL3] = sGrowattModbusReg_t{
      0x0016,   0,       SIZE_32BIT, "W L3", 1.0 / 10,
      1.0 / 10, POWER_W, true,       true,   ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_VAL1] = sGrowattModbusReg_t{
      0x0018,   0,  SIZE_32BIT, "VA L1", 1.0 / 10,
      1.0 / 10, VA, false,      false,   ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_VAL2] = sGrowattModbusReg_t{
      0x001A,   0,  SIZE_32BIT, "VA L2", 1.0 / 10,
      1.0 / 10, VA, false,      false,   ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_VAL3] = sGrowattModbusReg_t{
      0x001C,   0,  SIZE_32BIT, "VA L3", 1.0 / 10,
      1.0 / 10, VA, false,      false,   ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_varL1] = sGrowattModbusReg_t{
      0x001E,   0,    SIZE_32BIT, "var L1", 1.0 / 10,
      1.0 / 10, NONE, false,      false,    ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_varL2] = sGrowattModbusReg_t{
      0x0020,   0,    SIZE_32BIT, "var L2", 1.0 / 10,
      1.0 / 10, NONE, false,      false,    ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_varL3] = sGrowattModbusReg_t{
      0x0022,   0,    SIZE_32BIT, "var L3", 1.0 / 10,
      1.0 / 10, NONE, false,      false,    ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_L_Nsys] = sGrowattModbusReg_t{
      0x0024,   0,       SIZE_32BIT, "L-N sys", 1.0 / 10,
      1.0 / 10, VOLTAGE, false,      false,     ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_L_Lsys] = sGrowattModbusReg_t{
      0x0026,   0,       SIZE_32BIT, "L-L sys", 1.0 / 10,
      1.0 / 10, VOLTAGE, false,      false,     ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_Wsys] = sGrowattModbusReg_t{
      0x0028,   0,       SIZE_32BIT, "W sys", 1.0 / 10,
      1.0 / 10, POWER_W, true,       true,    ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_VAsys] = sGrowattModbusReg_t{
      0x002A,   0,  SIZE_32BIT, "VA sys", 1.0 / 10,
      1.0 / 10, VA, false,      false,    ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_varsys] = sGrowattModbusReg_t{
      0x002C,   0,    SIZE_32BIT, "var sys", 1.0 / 10,
      1.0 / 10, NONE, false,      false,     ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_PFL1] = sGrowattModbusReg_t{
      0x002E, 0,     SIZE_16BIT,           "PF L1", 1.0 / 1000, 1.0 / 1000, PF,
      false,  false, ByteOrder_t::LastHigh};  // Negative values correspond to
                                              // exported active power, positive
                                              // values correspond to imported
                                              // active power. Value weight:
                                              // PF*1000
  Protocol.InputRegisters[ET340_PFL2] = sGrowattModbusReg_t{
      0x002F,     0,  SIZE_16BIT, "PF L2", 1.0 / 1000,
      1.0 / 1000, PF, false,      false,   ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_PFL3] = sGrowattModbusReg_t{
      0x0030,     0,  SIZE_16BIT, "PF L3", 1.0 / 1000,
      1.0 / 1000, PF, false,      false,   ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_PFsys] = sGrowattModbusReg_t{
      0x0031,     0,  SIZE_16BIT, "PF sys", 1.0 / 1000,
      1.0 / 1000, PF, false,      false,    ByteOrder_t::LastHigh};
  addFragment(Protocol, fragmentID, ET340_VL1_N, ET340_PFsys);

  // FRAGMENT 2: BEGIN
  Protocol.InputRegisters[ET340_Phasesequence] =
      sGrowattModbusReg_t{0x0032,
                          0,
                          SIZE_16BIT,
                          "Phase sequence",
                          1.0 / 1,
                          1.0 / 1,
                          NONE,
                          false,
                          false,
                          ByteOrder_t::LastHigh};  // The value “1” corresponds
                                                   // to L1-L3-L2 sequence, the
                                                   // value 0 corresponds to
                                                   // L1-L2-L3 sequence. The
                                                   // phase sequence value is
                                                   // meaningful only in a
                                                   // 3-phase system
  Protocol.InputRegisters[ET340_Hz] = sGrowattModbusReg_t{
      0x0033,   0,  SIZE_16BIT, "Hz",  1.0 / 10,
      1.0 / 10, Hz, false,      false, ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_kWh_PLUS_TOT] = sGrowattModbusReg_t{
      0x0034,    0,     SIZE_32BIT, "kWh (PLUS) TOT",     1.0 / 10, 1.0 / 10,
      POWER_KWH, false, false,      ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_Kvarh_PLUS_TOT] = sGrowattModbusReg_t{
      0x0036,      0,     SIZE_32BIT, "Kvarh (PLUS) TOT",   1.0 / 10, 1.0 / 10,
      POWER_KVARH, false, false,      ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_kWdmd] = sGrowattModbusReg_t{
      0x0038,   0,        SIZE_32BIT, "kW dmd", 1.0 / 10,
      1.0 / 10, POWER_KW, false,      false,    ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_kWdmdpeak] = sGrowattModbusReg_t{
      0x003A,   0,        SIZE_32BIT, "kW dmd peak", 1.0 / 10,
      1.0 / 10, POWER_KW, false,      false,         ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_kWh_PLUS_PARTIAL] = sGrowattModbusReg_t{
      0x003C,    0,     SIZE_32BIT, "kWh (PLUS) PARTIAL", 1.0 / 10, 1.0 / 10,
      POWER_KWH, false, false,      ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_kvarh_PLUS_PARTIAL] =
      sGrowattModbusReg_t{0x003E,      0,
                          SIZE_32BIT,  "kvarh (PLUS) PARTIAL",
                          1.0 / 10,    1.0 / 10,
                          POWER_KVARH, false,
                          false,       ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_kWhL1] = sGrowattModbusReg_t{
      0x0040,   0,         SIZE_32BIT, "kWh L1", 1.0 / 10,
      1.0 / 10, POWER_KWH, false,      false,    ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_kWhL2] = sGrowattModbusReg_t{
      0x0042,   0,         SIZE_32BIT, "kWh L2", 1.0 / 10,
      1.0 / 10, POWER_KWH, false,      false,    ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_kWhL3] = sGrowattModbusReg_t{
      0x0044,   0,         SIZE_32BIT, "kWh L3", 1.0 / 10,
      1.0 / 10, POWER_KWH, false,      false,    ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_kWht1] = sGrowattModbusReg_t{
      0x0046,   0,         SIZE_32BIT, "kWh t1", 1.0 / 10,
      1.0 / 10, POWER_KWH, false,      false,    ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_kWht2] = sGrowattModbusReg_t{
      0x0048,   0,         SIZE_32BIT, "kWh t2", 1.0 / 10,
      1.0 / 10, POWER_KWH, false,      false,    ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_kWh_MINUS_TOT] = sGrowattModbusReg_t{
      0x004E,    0,     SIZE_32BIT, "kWh (MINUS) TOT",    1.0 / 10, 1.0 / 10,
      POWER_KWH, false, false,      ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_kVarh_MINUS_TOT] = sGrowattModbusReg_t{
      0x0050,      0,     SIZE_32BIT, "kVarh (MINUS) TOT",  1.0 / 10, 1.0 / 10,
      POWER_KVARH, false, false,      ByteOrder_t::LastHigh};
  addFragment(Protocol, fragmentID, ET340_Phasesequence, ET340_kVarh_MINUS_TOT);

  // FRAGMENT 3: BEGIN
  Protocol.InputRegisters[ET340_Runhourmeter] = sGrowattModbusReg_t{
      0x005A, 0,     SIZE_32BIT, "Run hour meter",     1.0 / 100, 1.0 / 100,
      NONE,   false, false,      ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_kWh_MINUS_L1] = sGrowattModbusReg_t{
      0x0060,    0,     SIZE_32BIT, "kWh (MINUS) L1",     1.0 / 10, 1.0 / 10,
      POWER_KWH, false, false,      ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_kWh_MINUS_L2] = sGrowattModbusReg_t{
      0x0062,    0,     SIZE_32BIT, "kWh (MINUS) L2",     1.0 / 10, 1.0 / 10,
      POWER_KWH, false, false,      ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_kWh_MINUS_L3] = sGrowattModbusReg_t{
      0x0064,    0,     SIZE_32BIT, "kWh (MINUS) L3",     1.0 / 10, 1.0 / 10,
      POWER_KWH, false, false,      ByteOrder_t::LastHigh};
  addFragment(Protocol, fragmentID, ET340_Runhourmeter, ET340_kWh_MINUS_L3);

  // FRAGMENT 4: BEGIN
  // Protocol.InputRegisters[ET340_An] = sGrowattModbusReg_t{0x0098, 0,
  // SIZE_32BIT, "An", 1.0/1000,1.0/1000, CURRENT, false, false,
  // ByteOrder_t::LastHigh};

  // FRAGMENT 5: BEGIN
  Protocol.InputRegisters[ET340_HourmeterkWh_MINUS] =
      sGrowattModbusReg_t{0x00F6,     0,
                          SIZE_32BIT, "Hour meter kWh (MINUS)",
                          1.0 / 1000, 1.0 / 1000,
                          POWER_KWH,  false,
                          false,      ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_A_n] = sGrowattModbusReg_t{
      0x00F8,     0,       SIZE_32BIT, "A n", 1.0 / 1000,
      1.0 / 1000, CURRENT, false,      false, ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_THDVL_Nsys] =
      sGrowattModbusReg_t{
          0x00FA,
          0,
          SIZE_32BIT,
          "THD V L-N sys",
          1.0 / 100,
          1.0 / 100,
          VOLTAGE,
          false,
          false,
          ByteOrder_t::LastHigh};  // PERCENT only ET series if THD calculation
                                   // is enabled in 1106h. Average of V1-N,
                                   // V2-N, V3-N
  Protocol.InputRegisters[ET340_Hourmeter] = sGrowattModbusReg_t{
      0x00FE, 0,     SIZE_32BIT, "Hour meter",         1.0 / 100, 1.0 / 100,
      NONE,   false, false,      ByteOrder_t::LastHigh};  // only ET series
  Protocol.InputRegisters[ET340_VL_Nsys] = sGrowattModbusReg_t{
      0x0102,   0,       SIZE_32BIT, "V L-N sys", 1.0 / 10,
      1.0 / 10, VOLTAGE, false,      false,       ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_VL_Lsys] = sGrowattModbusReg_t{
      0x0104,   0,       SIZE_32BIT, "V L-L sys", 1.0 / 10,
      1.0 / 10, VOLTAGE, false,      false,       ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_kWsys] = sGrowattModbusReg_t{
      0x0106,   0,        SIZE_32BIT, "kW sys", 1.0 / 10,
      1.0 / 10, POWER_KW, false,      false,    ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_kVAsys] = sGrowattModbusReg_t{
      0x0108,   0,         SIZE_32BIT, "kVA sys", 1.0 / 10,
      1.0 / 10, POWER_KVA, false,      false,     ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_kvarsys] = sGrowattModbusReg_t{
      0x010A,   0,          SIZE_32BIT, "kvar sys", 1.0 / 10,
      1.0 / 10, POWER_KVAR, false,      false,      ByteOrder_t::LastHigh};
  // Protocol.InputRegisters[ET340_PFsys] = sGrowattModbusReg_t{0x010C, 0,
  // SIZE_32BIT, "PF sys", 1.0/1/1.0/1/1000, PF, false, false,
  // ByteOrder_t::LastHigh}; Protocol.InputRegisters[ET340_Phasesequence] =
  // sGrowattModbusReg_t{0x010E, 0, SIZE_32BIT, "Phase sequence", 1.0/1/1.0/1/1,
  // NONE, false, false, ByteOrder_t::LastHigh}; // The value –1 corresponds to
  // L1-L3-L2 sequence, the value 0 corresponds to L1-L2-L3 sequence. The phase
  // sequence value is meaningful only in a 3-phase system
  // Protocol.InputRegisters[ET340_Hz] = sGrowattModbusReg_t{0x0110, 0,
  // SIZE_32BIT, "Hz", 1.0/1/1.0/1/10, Hz, false, false, ByteOrder_t::LastHigh};
  // // Total energies and dmd power Protocol.InputRegisters[ET340_kWh_PLUS_TOT]
  // = sGrowattModbusReg_t{0x0112, 0, SIZE_32BIT, "kWh (PLUS)
  // TOT", 1.0/1/1.0/1/10, POWER_KWH, false, false, ByteOrder_t::LastHigh};
  // Protocol.InputRegisters[ET340_Kvarh_PLUS_TOT] = sGrowattModbusReg_t{0x0114,
  // 0, SIZE_32BIT, "Kvarh (PLUS) TOT", 1.0/10,1.0/10, ByteOrder_t::LastHigh};
  // Protocol.InputRegisters[ET340_kWh_MINUS_TOT] = sGrowattModbusReg_t{0x0116,
  // 0, SIZE_32BIT, "kWh (MINUS) TOT", 1.0/1/1.0/1/10, POWER_KWH, false, false,
  // ByteOrder_t::LastHigh}; Protocol.InputRegisters[ET340_kvarh_MINUS_TOT] =
  // sGrowattModbusReg_t{0x0118, 0, SIZE_32BIT, "kvarh (MINUS)
  // TOT", 1.0/10,1.0/10, POWER_KVARH, false, false, ByteOrder_t::LastHigh};
  // Protocol.InputRegisters[ET340_kWdmd] = sGrowattModbusReg_t{0x011A, 0,
  // SIZE_32BIT, "kW dmd", 1.0/1/1.0/1/10, POWER_KW, false, false,
  // ByteOrder_t::LastHigh}; Protocol.InputRegisters[ET340_kWdmdpeak] =
  // sGrowattModbusReg_t{0x011C, 0, SIZE_32BIT, "kW dmd peak", 1.0/1/1.0/1/10,
  // POWER_KW, false, false, ByteOrder_t::LastHigh};
  addFragment(Protocol, fragmentID, ET340_HourmeterkWh_MINUS, ET340_kvarsys);

  // FRAGMENT 6: BEGIN
  // Protocol.InputRegisters[ET340_VL1_L2] = sGrowattModbusReg_t{0x011E, 0,
  // SIZE_32BIT, "V L1-L2", 1.0/1/1.0/1/10, VOLTAGE, false, false,
  // ByteOrder_t::LastHigh}; Protocol.InputRegisters[ET340_VL1_N] =
  // sGrowattModbusReg_t{0x0120, 0, SIZE_32BIT, "V L1-N", 1.0/1/1.0/1/10,
  // VOLTAGE, false, false, ByteOrder_t::LastHigh};
  // Protocol.InputRegisters[ET340_AL1] = sGrowattModbusReg_t{0x0122, 0,
  // SIZE_32BIT, "A L1", 1.0/1/1.0/1/1000, CURRENT, false, false,
  // ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_kWL1] = sGrowattModbusReg_t{
      0x0124,   0,        SIZE_32BIT, "kW L1", 1.0 / 10,
      1.0 / 10, POWER_KW, false,      false,   ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_kVAL1] = sGrowattModbusReg_t{
      0x0126,   0,         SIZE_32BIT, "kVA L1", 1.0 / 10,
      1.0 / 10, POWER_KVA, false,      false,    ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_kvarL1] = sGrowattModbusReg_t{
      0x0128,   0,          SIZE_32BIT, "kvar L1", 1.0 / 10,
      1.0 / 10, POWER_KVAR, false,      false,     ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_PFL1_STAR] = sGrowattModbusReg_t{
      0x012A,     0,  SIZE_32BIT, "PF L1 (STAR)", 1.0 / 1000,
      1.0 / 1000, PF, false,      false,          ByteOrder_t::LastHigh};
  // Phase 2 variables
  // Protocol.InputRegisters[ET340_VL2_L3] = sGrowattModbusReg_t{0x012C, 0,
  // SIZE_32BIT, "V L2-L3", 1.0/1/1.0/1/10, VOLTAGE, false, false,
  // ByteOrder_t::LastHigh}; Protocol.InputRegisters[ET340_VL2_N] =
  // sGrowattModbusReg_t{0x012E, 0, SIZE_32BIT, "V L2-N", 1.0/1/1.0/1/10,
  // VOLTAGE, false, false, ByteOrder_t::LastHigh};
  // Protocol.InputRegisters[ET340_AL2] = sGrowattModbusReg_t{0x0130, 0,
  // SIZE_32BIT, "A L2", 1.0/1/1.0/1/1000, CURRENT, false, false,
  // ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_kWL2] = sGrowattModbusReg_t{
      0x0132,   0,        SIZE_32BIT, "kW L2", 1.0 / 10,
      1.0 / 10, POWER_KW, false,      false,   ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_kVAL2] = sGrowattModbusReg_t{
      0x0134,   0,         SIZE_32BIT, "kVA L2", 1.0 / 10,
      1.0 / 10, POWER_KVA, false,      false,    ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_kvarL2] = sGrowattModbusReg_t{
      0x0136,   0,          SIZE_32BIT, "kvar L2", 1.0 / 10,
      1.0 / 10, POWER_KVAR, false,      false,     ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_PFL2_STAR] = sGrowattModbusReg_t{
      0x0138,     0,  SIZE_32BIT, "PF L2 (STAR)", 1.0 / 1000,
      1.0 / 1000, PF, false,      false,          ByteOrder_t::LastHigh};
  // Phase 3 variables
  // Protocol.InputRegisters[ET340_VL3_L1] = sGrowattModbusReg_t{0x013A, 0,
  // SIZE_32BIT, "V L3-L1", 1.0/1/1.0/1/10, VOLTAGE, false, false,
  // ByteOrder_t::LastHigh}; Protocol.InputRegisters[ET340_VL3_N] =
  // sGrowattModbusReg_t{0x013C, 0, SIZE_32BIT, "V L3-N", 1.0/1/1.0/1/10,
  // VOLTAGE, false, false, ByteOrder_t::LastHigh};
  // Protocol.InputRegisters[ET340_AL3] = sGrowattModbusReg_t{0x013E, 0,
  // SIZE_32BIT, "A L3", 1.0/1/1.0/1/1000, CURRENT, false, false,
  // ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_kWL3] = sGrowattModbusReg_t{
      0x0140,   0,        SIZE_32BIT, "kW L3", 1.0 / 10,
      1.0 / 10, POWER_KW, false,      false,   ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_kVAL3] = sGrowattModbusReg_t{
      0x0142,   0,         SIZE_32BIT, "kVA L3", 1.0 / 10,
      1.0 / 10, POWER_KVA, false,      false,    ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_kvarL3] = sGrowattModbusReg_t{
      0x0144,   0,          SIZE_32BIT, "kvar L3", 1.0 / 10,
      1.0 / 10, POWER_KVAR, false,      false,     ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_PFL3_STAR] = sGrowattModbusReg_t{
      0x0146,     0,  SIZE_32BIT, "PF L3 (STAR)", 1.0 / 1000,
      1.0 / 1000, PF, false,      false,          ByteOrder_t::LastHigh};
  // Other energies
  // Protocol.InputRegisters[ET340_kWh_PLUS_PARTIAL] =
  // sGrowattModbusReg_t{0x0148, 0, SIZE_32BIT, "kWh (PLUS)
  // PARTIAL", 1.0/1/1.0/1/10, POWER_KWH, false, false, ByteOrder_t::LastHigh};
  // Protocol.InputRegisters[ET340_kvarh_PLUS_PARTIAL] =
  // sGrowattModbusReg_t{0x014A, 0, SIZE_32BIT, "Kvarh (PLUS)
  // PARTIAL", 1.0/10,1.0/10, POWER_KVARH, false, false, ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_kWh_PLUS_L1] = sGrowattModbusReg_t{
      0x014C,   0,         SIZE_32BIT, "kWh (PLUS) L1", 1.0 / 10,
      1.0 / 10, POWER_KWH, false,      false,           ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_kWh_PLUS_L2] = sGrowattModbusReg_t{
      0x014E,   0,         SIZE_32BIT, "kWh (PLUS) L2", 1.0 / 10,
      1.0 / 10, POWER_KWH, false,      false,           ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_kWh_PLUS_L3] = sGrowattModbusReg_t{
      0x0150,   0,         SIZE_32BIT, "kWh (PLUS) L3", 1.0 / 10,
      1.0 / 10, POWER_KWH, false,      false,           ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_kWh_PLUS_t1] = sGrowattModbusReg_t{
      0x0152,   0,         SIZE_32BIT, "kWh (PLUS) t1", 1.0 / 10,
      1.0 / 10, POWER_KWH, false,      false,           ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_kWh_PLUS_t2] = sGrowattModbusReg_t{
      0x0154,   0,         SIZE_32BIT, "kWh (PLUS) t2", 1.0 / 10,
      1.0 / 10, POWER_KWH, false,      false,           ByteOrder_t::LastHigh};
  addFragment(Protocol, fragmentID, ET340_kWL1, ET340_kWh_PLUS_t2);

  Protocol.InputRegisters[ET340_MeassurementMode] = sGrowattModbusReg_t{
      0x1103, 0,    SIZE_16BIT, "Measurement mode selection", 1.0 / 1, 1.0 / 1,
      NONE,   true, false,      ByteOrder_t::LastHigh};
  Protocol.InputRegisters[ET340_WrongConnectionMode] =
      sGrowattModbusReg_t{0x1104,     0,
                          SIZE_16BIT, "Wrong connection management enabling",
                          1.0 / 1,    1.0 / 1,
                          NONE,       true,
                          false,      ByteOrder_t::LastHigh};
  addFragment(Protocol, fragmentID, ET340_MeassurementMode,
              ET340_WrongConnectionMode);

  Protocol.InputFragmentCount = fragmentID;

  // definition of holding registers
  Protocol.HoldingRegisterCount = ePET340HoldingRegisters_t::LASTHolding;
  Protocol.HoldingFragmentCount = 0;
}
