#include "Arduino.h"

#include "GrowattEM24.h"

// information from:
// https://gavazzi.se/produkter/em24dinav93xispfa/
// https://gavazzi.se/app/uploads/2020/11/em24_is_cp.pdf

// Supported inverters:
// - Victron EM24

uint8_t getSizeFromEnum(const RegisterSize_t& s) {
  switch (s) {
    case RegisterSize_t::SIZE_16BIT:
    case RegisterSize_t::SIZE_16BIT_S:
      return 1;
    case RegisterSize_t::SIZE_32BIT:
    case RegisterSize_t::SIZE_32BIT_S:
      return 2;
  }
  return 0;
}

void addFragment(sProtocolDefinition_t& Protocol,
                 const eEM24InputRegisters_t& start,
                 const eEM24InputRegisters_t& end) {
  Protocol.InputReadFragments[Protocol.InputFragmentCount++] =
      sGrowattReadFragment_t{
          Protocol.InputRegisters[start].address,
          static_cast<uint8_t>(
              Protocol.InputRegisters[end].address +
              getSizeFromEnum(Protocol.InputRegisters[end].size) -
              Protocol.InputRegisters[start].address)};
}

void init_growattEM24(sProtocolDefinition_t& Protocol) {
  // definition of input registers

  // max 11 words per request

  // 2.3 Instantaneous variables and meters
  Protocol.InputRegisters[EM24_V_L1_N] = sGrowattModbusReg_t{
      0x0000,   0,       SIZE_32BIT, "V L1-N", 1.0 / 10,
      1.0 / 10, VOLTAGE, true,       false,    ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_V_L2_N] = sGrowattModbusReg_t{
      0x0002,   0,       SIZE_32BIT, "V L2-N", 1.0 / 10,
      1.0 / 10, VOLTAGE, true,       false,    ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_V_L3_N] = sGrowattModbusReg_t{
      0x0004,   0,       SIZE_32BIT, "V L3-N", 1.0 / 10,
      1.0 / 10, VOLTAGE, true,       false,    ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_V_L1_L2] = sGrowattModbusReg_t{
      0x0006,   0,       SIZE_32BIT, "V L1-L2", 1.0 / 10,
      1.0 / 10, VOLTAGE, false,      false,     ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_V_L2_L3] = sGrowattModbusReg_t{
      0x0008,   0,       SIZE_32BIT, "V L2-L3", 1.0 / 10,
      1.0 / 10, VOLTAGE, false,      false,     ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_V_L3_L1] = sGrowattModbusReg_t{
      0x000A,   0,       SIZE_32BIT, "V L3-L1", 1.0 / 10,
      1.0 / 10, VOLTAGE, false,      false,     ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_A_L1] = sGrowattModbusReg_t{
      0x000C,     0,       SIZE_32BIT, "A L1", 1.0 / 1000,
      1.0 / 1000, CURRENT, true,       false,  ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_A_L2] = sGrowattModbusReg_t{
      0x000E,     0,       SIZE_32BIT, "A L2", 1.0 / 1000,
      1.0 / 1000, CURRENT, true,       false,  ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_A_L3] = sGrowattModbusReg_t{
      0x0010,     0,       SIZE_32BIT, "A L3", 1.0 / 1000,
      1.0 / 1000, CURRENT, true,       false,  ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_W_L1] = sGrowattModbusReg_t{
      0x0012,   0,       SIZE_32BIT, "W L1", 1.0 / 10,
      1.0 / 10, POWER_W, true,      true,  ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_W_L2] = sGrowattModbusReg_t{
      0x0014,   0,       SIZE_32BIT, "W L2", 1.0 / 10,
      1.0 / 10, POWER_W, true,      true,  ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_W_L3] = sGrowattModbusReg_t{
      0x0016,   0,       SIZE_32BIT, "W L3", 1.0 / 10,
      1.0 / 10, POWER_W, true,      true,  ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_VA_L1] = sGrowattModbusReg_t{
      0x0018,   0,  SIZE_32BIT, "VA L1", 1.0 / 10,
      1.0 / 10, VA, false,      false,   ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_VA_L2] = sGrowattModbusReg_t{
      0x001A,   0,  SIZE_32BIT, "VA L2", 1.0 / 10,
      1.0 / 10, VA, false,      false,   ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_VA_L3] = sGrowattModbusReg_t{
      0x001C,   0,  SIZE_32BIT, "VA L3", 1.0 / 10,
      1.0 / 10, VA, false,      false,   ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_VAR_L1] = sGrowattModbusReg_t{
      0x001E,   0,   SIZE_32BIT, "VAR L1", 1.0 / 10,
      1.0 / 10, VAR, false,      false,    ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_VAR_L2] = sGrowattModbusReg_t{
      0x0020,   0,   SIZE_32BIT, "VAR L2", 1.0 / 10,
      1.0 / 10, VAR, false,      false,    ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_VAR_L3] = sGrowattModbusReg_t{
      0x0022,   0,   SIZE_32BIT, "VAR L3", 1.0 / 10,
      1.0 / 10, VAR, false,      false,    ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_V_L_N_Epsilon] = sGrowattModbusReg_t{
      0x0024,   0,       SIZE_32BIT, "V L-N Epsilon", 1.0 / 10,
      1.0 / 10, VOLTAGE, false,      false,           ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_V_L_L_Epsilon] = sGrowattModbusReg_t{
      0x0026,   0,       SIZE_32BIT, "V L-L Epsilon", 1.0 / 10,
      1.0 / 10, VOLTAGE, false,      false,           ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_W_Epsilon] = sGrowattModbusReg_t{
      0x0028,   0,       SIZE_32BIT, "W Epsilon", 1.0 / 10,
      1.0 / 10, POWER_W, false,      false,       ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_VA_Epsilon] = sGrowattModbusReg_t{
      0x002A,   0,  SIZE_32BIT, "VA Epsilon", 1.0 / 10,
      1.0 / 10, VA, false,      false,        ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_VAR_Epsilon] = sGrowattModbusReg_t{
      0x002C,   0,   SIZE_32BIT, "VAR Epsilon", 1.0 / 10,
      1.0 / 10, VAR, false,      false,         ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_DMD_W_Epsilon] = sGrowattModbusReg_t{
      0x002E,   0,       SIZE_32BIT, "DMD W Epsilon", 1.0 / 10,
      1.0 / 10, POWER_W, false,      false,           ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_DMD_VA_Epsilon] = sGrowattModbusReg_t{
      0x0030, 0,     SIZE_32BIT, "DMD VA Epsilon",     1.0 / 10, 1.0 / 10,
      VA,     false, false,      ByteOrder_t::LastHigh};
  // Negative values correspond to lead(C), positive value correspond to
  // lag(L)
  Protocol.InputRegisters[EM24_PF_L1] = sGrowattModbusReg_t{
      0x0032,     0,  SIZE_16BIT, "PF L1", 1.0 / 1000,
      1.0 / 1000, PF, false,      false,   ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_PF_L2] = sGrowattModbusReg_t{
      0x0033,     0,  SIZE_16BIT, "PF L2", 1.0 / 1000,
      1.0 / 1000, PF, false,      false,   ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_PF_L3] = sGrowattModbusReg_t{
      0x0034,     0,  SIZE_16BIT, "PF L3", 1.0 / 1000,
      1.0 / 1000, PF, false,      false,   ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_PF_Epsilon] = sGrowattModbusReg_t{
      0x0035,     0,  SIZE_16BIT, "PF Epsilon", 1.0 / 1000,
      1.0 / 1000, PF, false,      false,        ByteOrder_t::LastHigh};

  Protocol.InputRegisters[EM24_Phase_sequence] =
      sGrowattModbusReg_t{0x0036,
                          0,
                          SIZE_16BIT,
                          "Phase sequence",
                          1.,
                          1.,
                          PF,
                          false,
                          false,
                          ByteOrder_t::LastHigh};  // Value –1 correspond to
                                                   // L1-L3-L2 sequence, value
                                                   // 0 correspond to L1-L2-L3
                                                   // sequence (this value is
                                                   // meaningful only in case
                                                   // of 3-phase systems)
  Protocol.InputRegisters[EM24_Hz] = sGrowattModbusReg_t{
      0x0037,   0,  SIZE_16BIT, "Hz",  1.0 / 10,
      1.0 / 10, Hz, false,      false, ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_DMD_W_Epsilon_max] = sGrowattModbusReg_t{
      0x0038,  0,     SIZE_32BIT, "DMD W Epsilon max ", 1.0 / 10, 1.0 / 10,
      POWER_W, false, false,      ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_DMD_VA_Epsilon_max] = sGrowattModbusReg_t{
      0x003A, 0,     SIZE_32BIT, "DMD VA Epsilon max", 1.0 / 10, 1.0 / 10,
      VA,     false, false,      ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_DMD_A_max] = sGrowattModbusReg_t{
      0x003C,     0,       SIZE_32BIT, "DMD A max", 1.0 / 1000,
      1.0 / 1000, CURRENT, false,      false,       ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_kWh_PLUS_TOT] = sGrowattModbusReg_t{
      0x003E,   0,         SIZE_32BIT, "kWh(+) TOT", 1.0 / 10,
      1.0 / 10, POWER_KWH, false,      false,        ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_kvarh_PLUS_TOT] = sGrowattModbusReg_t{
      0x0040,   0,           SIZE_32BIT, "kvarh(+) TOT", 1.0 / 10,
      1.0 / 10, POWER_KVARH, false,      false,          ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_KWh_PLUS_PAR] = sGrowattModbusReg_t{
      0x0042,   0,         SIZE_32BIT, "KWh(+) PAR", 1.0 / 10,
      1.0 / 10, POWER_KWH, false,      false,        ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_kvarh_PLUS_PAR] = sGrowattModbusReg_t{
      0x0044,   0,           SIZE_32BIT, "kvarh(+) PAR", 1.0 / 10,
      1.0 / 10, POWER_KVARH, false,      false,          ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_kWh_PLUS_L1] = sGrowattModbusReg_t{
      0x0046,   0,         SIZE_32BIT, "kWh(+) L1", 1.0 / 10,
      1.0 / 10, POWER_KWH, false,      false,       ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_kWh_PLUS_L2] = sGrowattModbusReg_t{
      0x0048,   0,         SIZE_32BIT, "kWh(+) L2", 1.0 / 10,
      1.0 / 10, POWER_KWH, false,      false,       ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_kWh_PLUS_L3] = sGrowattModbusReg_t{
      0x004A,   0,         SIZE_32BIT, "kWh(+) L3", 1.0 / 10,
      1.0 / 10, POWER_KWH, false,      false,       ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_kWh_PLUS_T1] = sGrowattModbusReg_t{
      0x004C,   0,         SIZE_32BIT, "kWh(+) T1", 1.0 / 10,
      1.0 / 10, POWER_KWH, false,      false,       ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_kWh_PLUS_T2] = sGrowattModbusReg_t{
      0x004E,   0,         SIZE_32BIT, "kWh(+) T2", 1.0 / 10,
      1.0 / 10, POWER_KWH, false,      false,       ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_kWh_PLUS_T3] = sGrowattModbusReg_t{
      0x0050,   0,         SIZE_32BIT, "kWh(+) T3", 1.0 / 10,
      1.0 / 10, POWER_KWH, false,      false,       ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_kWh_PLUS_T4] = sGrowattModbusReg_t{
      0x0052,   0,         SIZE_32BIT, "kWh(+) T4", 1.0 / 10,
      1.0 / 10, POWER_KWH, false,      false,       ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_kvarh_PLUS_T1] = sGrowattModbusReg_t{
      0x0054,   0,           SIZE_32BIT, "kvarh(+) T1", 1.0 / 10,
      1.0 / 10, POWER_KVARH, false,      false,         ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_kvarh_PLUS_T2] = sGrowattModbusReg_t{
      0x0056,   0,           SIZE_32BIT, "kvarh(+) T2", 1.0 / 10,
      1.0 / 10, POWER_KVARH, false,      false,         ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_kvarh_PLUS_T3] = sGrowattModbusReg_t{
      0x0058,   0,           SIZE_32BIT, "kvarh(+) T3", 1.0 / 10,
      1.0 / 10, POWER_KVARH, false,      false,         ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_kvarh_PLUS_T4] = sGrowattModbusReg_t{
      0x005A,   0,           SIZE_32BIT, "kvarh(+) T4", 1.0 / 10,
      1.0 / 10, POWER_KVARH, false,      false,         ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_kWh_MINUS_TOT] = sGrowattModbusReg_t{
      0x005C,   0,         SIZE_32BIT, "kWh(-) TOT", 1.0 / 10,
      1.0 / 10, POWER_KWH, false,      false,        ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_kvarh_MINUS_TOT] = sGrowattModbusReg_t{
      0x005E,   0,           SIZE_32BIT, "kvarh(-) TOT", 1.0 / 10,
      1.0 / 10, POWER_KVARH, false,      false,          ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_Hour] = sGrowattModbusReg_t{
      0x0060,    0,       SIZE_32BIT, "HOURS", 1.0 / 100,
      1.0 / 100, VOLTAGE, false,      false,   ByteOrder_t::LastHigh};
  // Value weight: Eng.Unit*10 or *100 or *1000 (see digital input
  // configuration menu)
  Protocol.InputRegisters[EM24_Counter_1] = sGrowattModbusReg_t{
      0x0062, 0,    SIZE_32BIT, "Counter 1", 1.,
      1.,     NONE, false,      false,       ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_Counter_2] = sGrowattModbusReg_t{
      0x0064, 0,    SIZE_32BIT, "Counter 2", 1.,
      1.,     NONE, false,      false,       ByteOrder_t::LastHigh};
  Protocol.InputRegisters[EM24_Counter_3] = sGrowattModbusReg_t{
      0x0066, 0,    SIZE_32BIT, "Counter 3", 1.,
      1.,     NONE, false,      false,       ByteOrder_t::LastHigh};

  // 2.4 Digital input status
  // bit=0 input close
  // bit=1 input open
  // bit0=input status Ch1
  // bit1=input status Ch2
  // bit2=input status Ch3
  Protocol.InputRegisters[EM24_Digital_Input_Status] = sGrowattModbusReg_t{
      0x0300, 0,     SIZE_16BIT, "Digital input status", 1., 1.,
      NONE,   false, false,      ByteOrder_t::LastHigh};

  // 2.5 Current tariff
  // Value=0: tariff 1
  // Value=1: tariff 2
  // Value=2: tariff 3
  // Value=3: tariff 4
  Protocol.InputRegisters[EM24_Current_Tariff] = sGrowattModbusReg_t{
      0x0301, 0,     SIZE_16BIT, "Digital input status", 1., 1.,
      NONE,   false, false,      ByteOrder_t::LastHigh};

  // general informations
  Protocol.InputRegisterCount = eEM24InputRegisters_t::LASTInput;

  addFragment(Protocol, eEM24InputRegisters_t::EM24_V_L1_N,eEM24InputRegisters_t::EM24_V_L2_L3);
  addFragment(Protocol, eEM24InputRegisters_t::EM24_V_L3_L1,eEM24InputRegisters_t::EM24_W_L1);
  addFragment(Protocol, eEM24InputRegisters_t::EM24_W_L2,eEM24InputRegisters_t::EM24_VA_L3);
  addFragment(Protocol, eEM24InputRegisters_t::EM24_VAR_L1,eEM24InputRegisters_t::EM24_V_L_L_Epsilon);
  addFragment(Protocol, eEM24InputRegisters_t::EM24_W_Epsilon,eEM24InputRegisters_t::EM24_PF_L1);
  addFragment(Protocol, eEM24InputRegisters_t::EM24_PF_L2,eEM24InputRegisters_t::EM24_DMD_A_max);
  addFragment(Protocol, eEM24InputRegisters_t::EM24_kWh_PLUS_TOT,eEM24InputRegisters_t::EM24_kWh_PLUS_L1);
  addFragment(Protocol, eEM24InputRegisters_t::EM24_kWh_PLUS_L2,eEM24InputRegisters_t::EM24_kWh_PLUS_T3);
  addFragment(Protocol, eEM24InputRegisters_t::EM24_kWh_PLUS_T4,eEM24InputRegisters_t::EM24_kvarh_PLUS_T4);
  addFragment(Protocol, eEM24InputRegisters_t::EM24_kWh_MINUS_TOT,eEM24InputRegisters_t::EM24_Counter_2);
  addFragment(Protocol, eEM24InputRegisters_t::EM24_Counter_3,eEM24InputRegisters_t::EM24_Counter_3);

//   addFragment(Protocol, eEM24InputRegisters_t::EM24_Digital_Input_Status,eEM24InputRegisters_t::EM24_Digital_Input_Status);
  addFragment(Protocol, eEM24InputRegisters_t::EM24_Current_Tariff,eEM24InputRegisters_t::EM24_Current_Tariff);

  // definition of holding registers
  Protocol.HoldingRegisterCount = eEM24HoldingRegisters_t::LASTHolding;
  Protocol.HoldingFragmentCount = 0;
}
