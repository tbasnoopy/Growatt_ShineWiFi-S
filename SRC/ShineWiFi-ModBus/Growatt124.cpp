#include "Arduino.h"

#include "Growatt124.h"

// NOTE: my inverter (SPH4-10KTL3 BH-UP) only manages to read 64 registers in
// one read!
void init_growatt124(sProtocolDefinition_t &Protocol) {
  // definition of input registers
  Protocol.InputRegisterCount = 53;
  // address, value, size, name, multiplier, unit, frontend, plot
  // FEAGMENT 1: BEGIN
  Protocol.InputRegisters[P124_I_STATUS] = sGrowattModbusReg_t{
      0,    0,    SIZE_16BIT, "InverterStatus",      1, 1,
      NONE, true, false,      ByteOrder_t::FirstHigh};  // #1
  Protocol.InputRegisters[P124_INPUT_POWER] = sGrowattModbusReg_t{
      1,   0,       SIZE_32BIT, "InputPower", 0.1,
      0.1, POWER_W, true,       true,         ByteOrder_t::FirstHigh};  // #2

  Protocol.InputRegisters[P124_PV1_VOLTAGE] = sGrowattModbusReg_t{
      3,   0,       SIZE_16BIT, "PV1Voltage", 0.1,
      0.1, VOLTAGE, false,      false,        ByteOrder_t::FirstHigh};  // #3
  Protocol.InputRegisters[P124_PV1_CURRENT] = sGrowattModbusReg_t{
      4,       0,     SIZE_16BIT, "PV1InputCurrent",     0.1, 0.1,
      CURRENT, false, false,      ByteOrder_t::FirstHigh};  // #4
  Protocol.InputRegisters[P124_PV1_POWER] = sGrowattModbusReg_t{
      5,   0,       SIZE_32BIT, "PV1InputPower", 0.1,
      0.1, POWER_W, false,      false,           ByteOrder_t::FirstHigh};  // #5
  Protocol.InputRegisters[P124_PV2_VOLTAGE] = sGrowattModbusReg_t{
      7,   0,       SIZE_16BIT, "PV2Voltage", 0.1,
      0.1, VOLTAGE, false,      false,        ByteOrder_t::FirstHigh};  // #6
  Protocol.InputRegisters[P124_PV2_CURRENT] = sGrowattModbusReg_t{
      8,       0,     SIZE_16BIT, "PV2InputCurrent",     0.1, 0.1,
      CURRENT, false, false,      ByteOrder_t::FirstHigh};  // #7
  Protocol.InputRegisters[P124_PV2_POWER] = sGrowattModbusReg_t{
      9,   0,       SIZE_32BIT, "PV2InputPower", 0.1,
      0.1, POWER_W, false,      false,           ByteOrder_t::FirstHigh};  // #8

  Protocol.InputRegisters[P124_PAC] = sGrowattModbusReg_t{
      35,  0,       SIZE_32BIT, "OutputPower", 0.1,
      0.1, POWER_W, true,       true,          ByteOrder_t::FirstHigh};  // #9
  Protocol.InputRegisters[P124_FAC] = sGrowattModbusReg_t{
      37,        0,     SIZE_16BIT, "GridFrequency",       0.01, 0.01,
      FREQUENCY, false, false,      ByteOrder_t::FirstHigh};  // #10

  Protocol.InputRegisters[P124_VAC1] = sGrowattModbusReg_t{
      38,      0,     SIZE_16BIT, "L1ThreePhaseGridVoltage", 0.1, 0.1,
      VOLTAGE, false, false,      ByteOrder_t::FirstHigh};  // #11
  Protocol.InputRegisters[P124_IAC1] = sGrowattModbusReg_t{
      39,      0,     SIZE_16BIT, "L1ThreePhaseGridOutputCurrent", 0.1, 0.1,
      CURRENT, false, false,      ByteOrder_t::FirstHigh};  // #12
  Protocol.InputRegisters[P124_PAC1] = sGrowattModbusReg_t{
      40, 0,     SIZE_32BIT, "L1ThreePhaseGridOutputPower", 0.1, 0.1,
      VA, false, false,      ByteOrder_t::FirstHigh};  // #13
  Protocol.InputRegisters[P124_VAC2] = sGrowattModbusReg_t{
      42,      0,     SIZE_16BIT, "L2ThreePhaseGridVoltage", 0.1, 0.1,
      VOLTAGE, false, false,      ByteOrder_t::FirstHigh};  // #14
  Protocol.InputRegisters[P124_IAC2] = sGrowattModbusReg_t{
      43,      0,     SIZE_16BIT, "L2ThreePhaseGridOutputCurrent", 0.1, 0.1,
      CURRENT, false, false,      ByteOrder_t::FirstHigh};  // #15
  Protocol.InputRegisters[P124_PAC2] = sGrowattModbusReg_t{
      44, 0,     SIZE_32BIT, "L2ThreePhaseGridOutputPower", 0.1, 0.1,
      VA, false, false,      ByteOrder_t::FirstHigh};  // #16
  Protocol.InputRegisters[P124_VAC3] = sGrowattModbusReg_t{
      46,      0,     SIZE_16BIT, "L3ThreePhaseGridVoltage", 0.1, 0.1,
      VOLTAGE, false, false,      ByteOrder_t::FirstHigh};  // #17
  Protocol.InputRegisters[P124_IAC3] = sGrowattModbusReg_t{
      47,      0,     SIZE_16BIT, "L3ThreePhaseGridOutputCurrent", 0.1, 0.1,
      CURRENT, false, false,      ByteOrder_t::FirstHigh};  // #18
  Protocol.InputRegisters[P124_PAC3] = sGrowattModbusReg_t{
      48, 0,     SIZE_32BIT, "L3ThreePhaseGridOutputPower", 0.1, 0.1,
      VA, false, false,      ByteOrder_t::FirstHigh};  // #19
  // FEAGMENT 1: END

  // FEAGMENT 2: BEGIN
  Protocol.InputRegisters[P124_EAC_TODAY] = sGrowattModbusReg_t{
      53,        0,    SIZE_32BIT, "TodayGenerateEnergy", 0.1, 0.1,
      POWER_KWH, true, false,      ByteOrder_t::FirstHigh};  // #20
  Protocol.InputRegisters[P124_EAC_TOTAL] = sGrowattModbusReg_t{
      55,        0,    SIZE_32BIT, "TotalGenerateEnergy", 0.1, 0.1,
      POWER_KWH, true, false,      ByteOrder_t::FirstHigh};  // #21
  Protocol.InputRegisters[P124_TIME_TOTAL] = sGrowattModbusReg_t{
      57,      0,     SIZE_32BIT, "TWorkTimeTotal",      0.5, 1,
      SECONDS, false, false,      ByteOrder_t::FirstHigh};  // #22

  Protocol.InputRegisters[P124_EPV1_TODAY] = sGrowattModbusReg_t{
      59,        0,     SIZE_32BIT, "PV1EnergyToday",      0.1, 0.1,
      POWER_KWH, false, false,      ByteOrder_t::FirstHigh};  // #23
  Protocol.InputRegisters[P124_EPV1_TOTAL] = sGrowattModbusReg_t{
      61,        0,     SIZE_32BIT, "PV1EnergyTotal",      0.1, 0.1,
      POWER_KWH, false, false,      ByteOrder_t::FirstHigh};  // #24
  Protocol.InputRegisters[P124_EPV2_TODAY] = sGrowattModbusReg_t{
      63,        0,     SIZE_32BIT, "PV2EnergyToday",      0.1, 0.1,
      POWER_KWH, false, false,      ByteOrder_t::FirstHigh};  // #25
  Protocol.InputRegisters[P124_EPV2_TOTAL] = sGrowattModbusReg_t{
      65,        0,     SIZE_32BIT, "PV2EnergyTotal",      0.1, 0.1,
      POWER_KWH, false, false,      ByteOrder_t::FirstHigh};  // #26
  Protocol.InputRegisters[P124_EPV_TOTAL] = sGrowattModbusReg_t{
      91,        0,     SIZE_32BIT, "PVEnergyTotal",       0.1, 0.1,
      POWER_KWH, false, false,      ByteOrder_t::FirstHigh};  // #27

  Protocol.InputRegisters[P124_TEMP1] = sGrowattModbusReg_t{
      93,          0,    SIZE_16BIT, "InverterTemperature", 0.1, 0.1,
      TEMPERATURE, true, true,       ByteOrder_t::FirstHigh};  // #28
  Protocol.InputRegisters[P124_TEMP2] = sGrowattModbusReg_t{
      94,          0,     SIZE_16BIT, "TemperatureInsideIPM", 0.1, 0.1,
      TEMPERATURE, false, false,      ByteOrder_t::FirstHigh};  // #29
  Protocol.InputRegisters[P124_TEMP3] = sGrowattModbusReg_t{
      95,          0,     SIZE_16BIT, "BoostTemperature",    0.1, 0.1,
      TEMPERATURE, false, false,      ByteOrder_t::FirstHigh};  // #30
  // FEAGMENT 2: END

  // FEAGMENT 3: BEGIN
  Protocol.InputRegisters[P124_PDISCHARGE] = sGrowattModbusReg_t{
      1009,    0,    SIZE_32BIT, "DischargePower",      0.1, 0.1,
      POWER_W, true, true,       ByteOrder_t::FirstHigh};  // #31
  Protocol.InputRegisters[P124_PCHARGE] = sGrowattModbusReg_t{
      1011, 0,       SIZE_32BIT, "ChargePower", 0.1,
      0.1,  POWER_W, true,       true,          ByteOrder_t::FirstHigh};  // #32
  Protocol.InputRegisters[P124_VBAT] = sGrowattModbusReg_t{
      1013,    0,     SIZE_16BIT, "BatteryVoltage",      0.1, 0.1,
      VOLTAGE, false, false,      ByteOrder_t::FirstHigh};  // #33
  Protocol.InputRegisters[P124_SOC] = sGrowattModbusReg_t{
      1014, 0,          SIZE_16BIT, "SOC", 1,
      1,    PRECENTAGE, true,       true,  ByteOrder_t::FirstHigh};  // #34
  Protocol.InputRegisters[P124_PAC_TO_USER] = sGrowattModbusReg_t{
      1015,    0,     SIZE_32BIT, "ACPowerToUser",       0.1, 0.1,
      POWER_W, false, false,      ByteOrder_t::FirstHigh};  // #35
  Protocol.InputRegisters[P124_PAC_TO_USER_TOTAL] = sGrowattModbusReg_t{
      1021,    0,     SIZE_32BIT, "ACPowerToUserTotal",  0.1, 0.1,
      POWER_W, false, false,      ByteOrder_t::FirstHigh};  // #36
  Protocol.InputRegisters[P124_PAC_TO_GRID] = sGrowattModbusReg_t{
      1023,    0,     SIZE_32BIT, "ACPowerToGrid",       0.1, 0.1,
      POWER_W, false, false,      ByteOrder_t::FirstHigh};  // #37
  Protocol.InputRegisters[P124_PAC_TO_GRID_TOTAL] = sGrowattModbusReg_t{
      1029,    0,     SIZE_32BIT, "ACPowerToGridTotal",  0.1, 0.1,
      POWER_W, false, false,      ByteOrder_t::FirstHigh};  // #38
  Protocol.InputRegisters[P124_PLOCAL_LOAD] = sGrowattModbusReg_t{
      1031,    0,     SIZE_32BIT, "INVPowerToLocalLoad", 0.1, 0.1,
      POWER_W, false, false,      ByteOrder_t::FirstHigh};  // #39
  Protocol.InputRegisters[P124_PLOCAL_LOAD_TOTAL] = sGrowattModbusReg_t{
      1037,    0,    SIZE_32BIT, "INVPowerToLocalLoadTotal", 0.1, 0.1,
      POWER_W, true, false,      ByteOrder_t::FirstHigh};  // #40
  Protocol.InputRegisters[P124_BATTERY_TEMPERATURE] = sGrowattModbusReg_t{
      1040,        0,    SIZE_16BIT, "BatteryTemperature",  0.1, 0.1,
      TEMPERATURE, true, true,       ByteOrder_t::FirstHigh};  // #41
  Protocol.InputRegisters[P124_BATTERY_STATE] = sGrowattModbusReg_t{
      1041, 0,    SIZE_16BIT, "BatteryState", 1,
      1,    NONE, true,       false,          ByteOrder_t::FirstHigh};  // #42

  Protocol.InputRegisters[P124_ETOUSER_TODAY] = sGrowattModbusReg_t{
      1044,      0,    SIZE_32BIT, "EnergyToUserToday",   0.1, 0.1,
      POWER_KWH, true, false,      ByteOrder_t::FirstHigh};  // #43
  Protocol.InputRegisters[P124_ETOUSER_TOTAL] = sGrowattModbusReg_t{
      1046,      0,    SIZE_32BIT, "EnergyToUserTotal",   0.1, 0.1,
      POWER_KWH, true, false,      ByteOrder_t::FirstHigh};  // #44
  Protocol.InputRegisters[P124_ETOGRID_TODAY] = sGrowattModbusReg_t{
      1048,      0,    SIZE_32BIT, "EnergyToGridToday",   0.1, 0.1,
      POWER_KWH, true, false,      ByteOrder_t::FirstHigh};  // #45
  Protocol.InputRegisters[P124_ETOGRID_TOTAL] = sGrowattModbusReg_t{
      1050,      0,    SIZE_32BIT, "EnergyToGridTotal",   0.1, 0.1,
      POWER_KWH, true, false,      ByteOrder_t::FirstHigh};  // #46
  Protocol.InputRegisters[P124_EDISCHARGE_TODAY] = sGrowattModbusReg_t{
      1052,      0,    SIZE_32BIT, "DischargeEnergyToday", 0.1, 0.1,
      POWER_KWH, true, false,      ByteOrder_t::FirstHigh};  // #47
  Protocol.InputRegisters[P124_EDISCHARGE_TOTAL] = sGrowattModbusReg_t{
      1054,      0,    SIZE_32BIT, "DischargeEnergyTotal", 0.1, 0.1,
      POWER_KWH, true, false,      ByteOrder_t::FirstHigh};  // #48
  Protocol.InputRegisters[P124_ECHARGE_TODAY] = sGrowattModbusReg_t{
      1056,      0,    SIZE_32BIT, "ChargeEnergyToday",   0.1, 0.1,
      POWER_KWH, true, false,      ByteOrder_t::FirstHigh};  // #49
  Protocol.InputRegisters[P124_ECHARGE_TOTAL] = sGrowattModbusReg_t{
      1058,      0,    SIZE_32BIT, "ChargeEnergyTotal",   0.1, 0.1,
      POWER_KWH, true, false,      ByteOrder_t::FirstHigh};  // #50
  Protocol.InputRegisters[P124_ETOLOCALLOAD_TODAY] = sGrowattModbusReg_t{
      1060,      0,    SIZE_32BIT, "LocalLoadEnergyToday", 0.1, 0.1,
      POWER_KWH, true, false,      ByteOrder_t::FirstHigh};  // #51
  Protocol.InputRegisters[P124_ETOLOCALLOAD_TOTAL] = sGrowattModbusReg_t{
      1062,      0,    SIZE_32BIT, "LocalLoadEnergyTotal", 0.1, 0.1,
      POWER_KWH, true, false,      ByteOrder_t::FirstHigh};  // #52
  // FEAGMENT 3: END

  // FEAGMENT 4: BEGIN
   Protocol.InputRegisters[P124_SOC_NEW] = sGrowattModbusReg_t{
      3171, 0, SIZE_16BIT, "SOC", 1, PRECENTAGE, true, true};
  // FEAGMENT 4: END

  Protocol.InputFragmentCount = 4;
  Protocol.InputReadFragments[0] = sGrowattReadFragment_t{0, 50};
  Protocol.InputReadFragments[1] = sGrowattReadFragment_t{53, 43};
  Protocol.InputReadFragments[2] = sGrowattReadFragment_t{1009, 55};
  Protocol.InputReadFragments[3] = sGrowattReadFragment_t{3171, 1};

  Protocol.HoldingRegisterCount = 0;
  Protocol.HoldingFragmentCount = 0;
}