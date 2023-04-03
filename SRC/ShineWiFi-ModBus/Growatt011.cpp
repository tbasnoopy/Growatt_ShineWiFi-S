#include "Arduino.h"

#include "Growatt011.h"
#include "protocollhelper.h"

// information from:
// https://watts247.com/manuals/gw/GrowattModBusProtocol.pdf

// V0.11
// 2017‐8‐09

// Supported inverters:
// ?? can not test this ??
// ?? Growatt OffGrid SPF5000 ??

void init_growatt011(sProtocolDefinition_t& Protocol) {
  // definition of input registers

  const uint8_t maxFragmentSize = 10;  // todo: how much really

  // clang-format off
addInputRegister(Protocol, 0, SIZE_16BIT, eGRO_011InputRegisters_t::SYSTEM_STATUS, "System Status", 1.0, VOLTAGE, true, false); // System run state
addInputRegister(Protocol, 1, SIZE_16BIT, eGRO_011InputRegisters_t::VPV1, "Vpv1", 0.1, VOLTAGE);                                // PV1 voltage 0.1V
addInputRegister(Protocol, 2, SIZE_16BIT, eGRO_011InputRegisters_t::VPV2, "Vpv2", 0.1, VOLTAGE);                                // PV2 voltage 0.1V
addInputRegister(Protocol, 3, SIZE_32BIT, eGRO_011InputRegisters_t::PPV1, "Ppv1", 0.1, POWER_W, true, true);                    // H PV1 charge power (high) 0.1W
addInputRegister(Protocol, 5, SIZE_32BIT, eGRO_011InputRegisters_t::PPV2, "Ppv2", 0.1, POWER_W, true, true);                    // H PV2 charge power (high) 0.1W
addInputRegister(Protocol, 7, SIZE_16BIT, eGRO_011InputRegisters_t::BUCK1CURR, "Buck1Curr", 0.1, CURRENT);                      // Buck1 current 0.1A
addInputRegister(Protocol, 8, SIZE_16BIT, eGRO_011InputRegisters_t::BUCK2CURR, "Buck2Curr", 0.1, CURRENT);                      // Buck2 current 0.1A
addInputRegister(Protocol, 9, SIZE_32BIT, eGRO_011InputRegisters_t::OP_WATT, "OP_Watt", 0.1, POWER_W);                          // Output active power (high) 0.1W
addInputRegister(Protocol, 12, SIZE_32BIT, eGRO_011InputRegisters_t::OP_VA, "OP_VA", 0.1, VA);                                  // Output apparent power (low) 0.1VA
addInputRegister(Protocol, 13, SIZE_32BIT, eGRO_011InputRegisters_t::ACCHR_WATT, "ACChr_Watt", 0.1, POWER_W);                   // AC charge watt (high) 0.1W
addInputRegister(Protocol, 15, SIZE_32BIT, eGRO_011InputRegisters_t::ACCHR_VA, "ACChr_VA", 0.1, VA);                            // AC charge apparent power (high) 0.1VA
addInputRegister(Protocol, 17, SIZE_16BIT, eGRO_011InputRegisters_t::BAT_VOLT, "Bat Volt", 0.01, VOLTAGE);                      //  Battery volt (M3) 0.01V
addInputRegister(Protocol, 18, SIZE_16BIT, eGRO_011InputRegisters_t::BATTERYSOC, "BatterySOC", 1.0, PRECENTAGE);                //  Battery SOC
addInputRegister(Protocol, 19, SIZE_16BIT, eGRO_011InputRegisters_t::BUS_VOLT, "Bus Volt", 0.1, VOLTAGE);                       //  Bus Voltage 0.1V
addInputRegister(Protocol, 20, SIZE_16BIT, eGRO_011InputRegisters_t::GRID_VOLT, "Grid Volt", 0.1, VOLTAGE);                     //  AC input Volt 0.1V
addInputRegister(Protocol, 21, SIZE_16BIT, eGRO_011InputRegisters_t::LINE_FREQ, "Line Freq", 0.01, FREQUENCY);                  //  AC input frequency 0.01Hz
addInputRegister(Protocol, 22, SIZE_16BIT, eGRO_011InputRegisters_t::OUTPUTVOLT, "OutputVolt", 0.1, VOLTAGE);                   //  AC output Volt 0.1V
addInputRegister(Protocol, 23, SIZE_16BIT, eGRO_011InputRegisters_t::OUTPUTFREQ, "OutputFreq", 0.01, FREQUENCY);                //  AC output frequency 0.01Hz
addInputRegister(Protocol, 24, SIZE_16BIT, eGRO_011InputRegisters_t::OUPUT_DCV, "Ouput DCV", 0.1, VOLTAGE);                     //  Ouput DC Volt 0.1V 0: Standby; 1; （No Use） 2: Discharge; 3: Fault; 4: Flash; 5: PV charge; 6: AC charge; 7: Combine charge; 8: Combine charge and Bypass; 9: PV charge and Bypass; 10: AC charge and Bypass; 11: Bypass; 12: PV charge and Discharge; 0~100 1%
addInputRegister(Protocol, 25, SIZE_16BIT, eGRO_011InputRegisters_t::INVTEMP, "InvTemp", 0.1, TEMPERATURE);                     //  Inv Temperature 0.1C
addInputRegister(Protocol, 26, SIZE_16BIT, eGRO_011InputRegisters_t::DCDC_TEMP, "DcDc Temp", 0.1, TEMPERATURE);                 //  DC‐DC Temperature 0.1C
addInputRegister(Protocol, 27, SIZE_16BIT, eGRO_011InputRegisters_t::LOADPERCENT, "LoadPercent", 1.0, PRECENTAGE);              //  Load Percent
addInputRegister(Protocol, 28, SIZE_16BIT, eGRO_011InputRegisters_t::BAT_S_VOLT, "Bat_s_Volt", 0.01, VOLTAGE);                  //  Battery‐port volt (DSP) 0.01V
addInputRegister(Protocol, 29, SIZE_16BIT, eGRO_011InputRegisters_t::BAT_VOLT_DSP, "Bat_Volt_DSP", 0.01, VOLTAGE);              //  Battery‐bus volt (DSP) 0.01V
addInputRegister(Protocol, 30, SIZE_32BIT, eGRO_011InputRegisters_t::TIME_TOTAL, "Time total", .5, SECONDS);                    //  Work time total (high) 0.5S
addInputRegister(Protocol, 32, SIZE_16BIT, eGRO_011InputRegisters_t::BUCK1_NTC, "Buck1_NTC", 0.1, TEMPERATURE);                 //  Buck1 Temperature 0.1C
addInputRegister(Protocol, 33, SIZE_16BIT, eGRO_011InputRegisters_t::BUCK2_NTC, "Buck2_NTC", 0.1, TEMPERATURE);                 //  Buck2 Temperature 0.1C
addInputRegister(Protocol, 34, SIZE_16BIT, eGRO_011InputRegisters_t::OP_CURR, "OP_Curr", 0.1, CURRENT);                         //  Output Current 0.1A
addInputRegister(Protocol, 35, SIZE_16BIT, eGRO_011InputRegisters_t::INV_CURR, "Inv_Curr", 0.1, CURRENT);                       //  Inv Current 0.1A
addInputRegister(Protocol, 36, SIZE_32BIT, eGRO_011InputRegisters_t::AC_INWATT, "AC_InWatt", 0.1, POWER_W);                     //  AC input watt (high) 0.1W
addInputRegister(Protocol, 38, SIZE_32BIT, eGRO_011InputRegisters_t::AC_INVA, "AC_InVA", 0.1, VA);                              //  AC input apparent power (high) 0.1VA
addInputRegister(Protocol, 40, SIZE_16BIT, eGRO_011InputRegisters_t::FAULT_BIT, "Fault bit", 1., NONE);                         //  fault bit &*1
addInputRegister(Protocol, 41, SIZE_16BIT, eGRO_011InputRegisters_t::WARNING_BIT, "Warning bit", 1., NONE);                     //  Warning bit &*1
addInputRegister(Protocol, 42, SIZE_16BIT, eGRO_011InputRegisters_t::FAULT_VALUE, "fault value", 1., NONE);                     //  fault value
addInputRegister(Protocol, 43, SIZE_16BIT, eGRO_011InputRegisters_t::WARNING_VALUE, "warning value", 1., NONE);                 //  warning value
addInputRegister(Protocol, 44, SIZE_16BIT, eGRO_011InputRegisters_t::DTC, "DTC", 1., NONE);                                     //  Device Type Code &*6
addInputRegister(Protocol, 45, SIZE_16BIT, eGRO_011InputRegisters_t::CHECK_STEP, "Check Step", 1., NONE);                       //  Product check step 1:PV1 charge power check; 2:PV2 charge power check; 3:AC charge Power check
addInputRegister(Protocol, 46, SIZE_16BIT, eGRO_011InputRegisters_t::PRODUCTION_LINE_MODE, "Production Line Mode", 1., NONE);   //  Production Line Mode 0: Not at Production Line Mode; 1: Production Line Mode; 2: Production Line Clear Fault Mode;
addInputRegister(Protocol, 47, SIZE_16BIT, eGRO_011InputRegisters_t::CONSTANTPOWEROKFLAG, "ConstantPowerOKFlag", 1., NONE);     //  Constant Power OK Flag 0: Not OK; 1: OK;
addInputRegister(Protocol, 48, SIZE_32BIT, eGRO_011InputRegisters_t::EPV1_TODAY, "Epv1_today", .1, POWER_KWH);                  //  PV Energy today 0.1kW/h
addInputRegister(Protocol, 50, SIZE_32BIT, eGRO_011InputRegisters_t::EPV1_TOTAL, "Epv1_total", .1, POWER_KWH);                  //  PV Energy total 0.1kW/h
addInputRegister(Protocol, 52, SIZE_32BIT, eGRO_011InputRegisters_t::EPV2_TODAY, "Epv2_today", .1, POWER_KWH);                  //  PV Energy today
addInputRegister(Protocol, 54, SIZE_32BIT, eGRO_011InputRegisters_t::EPV2_TOTAL, "Epv2_total", .1, POWER_KWH);                  //  PV Energy total
addInputRegister(Protocol, 56, SIZE_32BIT, eGRO_011InputRegisters_t::EAC_CHRTODAY, "Eac_chrToday", .1, POWER_KWH);              //  AC charge Energy today
addInputRegister(Protocol, 58, SIZE_32BIT, eGRO_011InputRegisters_t::EAC_CHRTOTAL, "Eac_chrTotal", .1, POWER_KWH);              //  AC charge Energy total
addInputRegister(Protocol, 60, SIZE_32BIT, eGRO_011InputRegisters_t::EBAT_DISCHRTODAY, "Ebat_dischrToday", .1, POWER_KWH);      //  Bat discharge Energy today
addInputRegister(Protocol, 62, SIZE_32BIT, eGRO_011InputRegisters_t::EBAT_DISCHRTOTAL, "Ebat_dischrTotal", .1, POWER_KWH);      //  Bat discharge Energy total
addInputRegister(Protocol, 64, SIZE_32BIT, eGRO_011InputRegisters_t::EAC_DISCHRTODAY, "Eac_dischrToday", .1, POWER_KWH);        //  AC discharge Energy today
addInputRegister(Protocol, 66, SIZE_32BIT, eGRO_011InputRegisters_t::EAC_DISCHRTOTAL, "Eac_dischrTotal", .1, POWER_KWH);        //  AC discharge Energy total
addInputRegister(Protocol, 68, SIZE_16BIT, eGRO_011InputRegisters_t::ACCHRCURR_AC, "ACChrCurr AC", .1, CURRENT);                //  Charge Battery Current 0.1A
addInputRegister(Protocol, 69, SIZE_32BIT, eGRO_011InputRegisters_t::AC_DISCHRWATT, "AC_DisChrWatt", .1, POWER_W);              //  AC discharge watt (high) 0.1W
addInputRegister(Protocol, 71, SIZE_32BIT, eGRO_011InputRegisters_t::AC_DISCHRVA, "AC_DisChrVA", .1, VA);                       //  AC discharge apparent power (high) 0.1VA
addInputRegister(Protocol, 73, SIZE_32BIT, eGRO_011InputRegisters_t::BAT_DISCHRWATT, "Bat_DisChrWatt", .1, POWER_W);            //  Bat discharge watt (high) 0.1W
addInputRegister(Protocol, 75, SIZE_32BIT, eGRO_011InputRegisters_t::BAT_DISCHRVA, "Bat_DisChrVA", .1, VA);                     //  Bat discharge apparent power (high) 0.1VA
addInputRegister(Protocol, 77, SIZE_32BIT, eGRO_011InputRegisters_t::BAT_WATT, "Bat_Watt", .1, POWER_W);                        //  Bat watt (high)
// addInputRegister(Protocol, 79, SIZE_16BIT, eGRO_011InputRegisters_t::RESERVED, "Reserved", .1, NONE);                                  //  Not Used
addInputRegister(Protocol, 80, SIZE_16BIT, eGRO_011InputRegisters_t::BATOVERCHARGE, "BatOverCharge", 1., NONE);                        //  Battery Over Charge Flag 0.1kW h 0.1kW h 0.1kW h 0.1kW h 0.1kW h 0.1kW h 0.1kW h (signed int 32) Positive:Battery Discharge Power; Negative: Battery Charge Power; 0:Battery not 0.1W 0.1W over charge; 1:Battery over charge;
addInputRegister(Protocol, 81, SIZE_16BIT, eGRO_011InputRegisters_t::MPPTFANSPEED, "MpptFanSpeed", 1., PRECENTAGE);                    //  Fan speed of MPPT Charger 0~100 1%
addInputRegister(Protocol, 82, SIZE_16BIT, eGRO_011InputRegisters_t::INVFANSPEED, "InvFanSpeed", 1., PRECENTAGE);                      //  Fan speed of Inverter 0~100 1%
addInputRegister(Protocol, 90, SIZE_16BIT, eGRO_011InputRegisters_t::BMS_STATUS, "BMS_Status", 1., NONE);                              //  Status from BMS
addInputRegister(Protocol, 91, SIZE_16BIT, eGRO_011InputRegisters_t::BMS_ERROR, "BMS_Error", 1., NONE);                                //  Error infomation from BMS
addInputRegister(Protocol, 92, SIZE_16BIT, eGRO_011InputRegisters_t::BMS_WARNINFO, "BMS_ WarnInfo", 1., NONE);                         //  Warning info from BMS Detail information, refer to document: Growatt xxSxxP ESS Protocol;
addInputRegister(Protocol, 93, SIZE_16BIT, eGRO_011InputRegisters_t::BMS_SOC, "BMS_SOC", 1., NONE);                                    //  SOC from BMS
addInputRegister(Protocol, 94, SIZE_16BIT, eGRO_011InputRegisters_t::BMS_BATTERYVOLT, "BMS_ BatteryVolt", 1., NONE);                   //  Battery voltage from BMS
addInputRegister(Protocol, 95, SIZE_16BIT, eGRO_011InputRegisters_t::BMS_BATTERYCURR, "BMS_ BatteryCurr", 1., NONE);                   //  Battery current from BMS BMS_ BatteryTemp Battery BMS BMS_ MaxCurr Max. charge/discharge current from BMS
addInputRegister(Protocol, 98, SIZE_16BIT, eGRO_011InputRegisters_t::BMS_CONSTANTVOLT, "BMS_ ConstantVolt", 1., NONE);                 //  CV voltage from BMS
addInputRegister(Protocol, 99, SIZE_16BIT, eGRO_011InputRegisters_t::BMS_BMSINFO, "BMS_ BMSInfo", 1., NONE);                           //  BMS Information from BMS
addInputRegister(Protocol, 100, SIZE_16BIT, eGRO_011InputRegisters_t::BMS_PACKINFO, "BMS_ PackInfo", 1., NONE);                        //  Pack Information from BMS
addInputRegister(Protocol, 101, SIZE_16BIT, eGRO_011InputRegisters_t::BMS_USINGCAP, "BMS_ UsingCap", 1., NONE);                        //  Using Cap from BMS
addInputRegister(Protocol, 102, SIZE_16BIT, eGRO_011InputRegisters_t::BMS_CELL1_VOLT, "BMS_ Cell1_Volt", 1., NONE);                    //  Cell1_Voltage from BMS
addInputRegister(Protocol, 103, SIZE_16BIT, eGRO_011InputRegisters_t::BMS_CELL2_VOLT, "BMS_ Cell2_Volt", 1., NONE);                    //  Cell2_Voltage from BMS
addInputRegister(Protocol, 104, SIZE_16BIT, eGRO_011InputRegisters_t::BMS_CELL3_VOLT, "BMS_ Cell3_Volt", 1., NONE);                    //  Cell3_Voltage from BMS
addInputRegister(Protocol, 105, SIZE_16BIT, eGRO_011InputRegisters_t::BMS_CELL4_VOLT, "BMS_ Cell4_Volt", 1., NONE);                    //  Cell4_Voltage from BMS
addInputRegister(Protocol, 106, SIZE_16BIT, eGRO_011InputRegisters_t::BMS_CELL5_VOLT, "BMS_ Cell5_Volt", 1., NONE);                    //  Cell5_Voltage from BMS
addInputRegister(Protocol, 107, SIZE_16BIT, eGRO_011InputRegisters_t::BMS_CELL6_VOLT, "BMS_ Cell6_Volt", 1., NONE);                    //  Cell6_Voltage from BMS
addInputRegister(Protocol, 108, SIZE_16BIT, eGRO_011InputRegisters_t::BMS_CELL7_VOLT, "BMS_ Cell7_Volt", 1., NONE);                    //  Cell7_Voltage from BMS
addInputRegister(Protocol, 109, SIZE_16BIT, eGRO_011InputRegisters_t::BMS_CELL8_VOLT, "BMS_ Cell8_Volt", 1., NONE);                    //  Cell8_Voltage from BMS
addInputRegister(Protocol, 110, SIZE_16BIT, eGRO_011InputRegisters_t::BMS_CELL9_VOLT, "BMS_ Cell9_Volt", 1., NONE);                    //  Cell9_Voltage from BMS
addInputRegister(Protocol, 111, SIZE_16BIT, eGRO_011InputRegisters_t::BMS_CELL10_VOLT, "BMS_ Cell10_Volt", 1., NONE);                  //  Cell10_Voltage from BMS
addInputRegister(Protocol, 112, SIZE_16BIT, eGRO_011InputRegisters_t::BMS_CELL11_VOLT, "BMS_ Cell11_Volt", 1., NONE);                  //  Cell11_Voltage from BMS
addInputRegister(Protocol, 113, SIZE_16BIT, eGRO_011InputRegisters_t::BMS_CELL12_VOLT, "BMS_ Cell12_Volt", 1., NONE);                  //  Cell12_Voltage from BMS
addInputRegister(Protocol, 114, SIZE_16BIT, eGRO_011InputRegisters_t::BMS_CELL13_VOLT, "BMS_ Cell13_Volt", 1., NONE);                  //  Cell13_Voltage from BMS
addInputRegister(Protocol, 115, SIZE_16BIT, eGRO_011InputRegisters_t::BMS_CELL14_VOLT, "BMS_ Cell14_Volt", 1., NONE);                  //  Cell14_Voltage from BMS
addInputRegister(Protocol, 116, SIZE_16BIT, eGRO_011InputRegisters_t::BMS_CELL15_VOLT, "BMS_ Cell15_Volt", 1., NONE);                  //  Cell15_Voltage from BMS
addInputRegister(Protocol, 117, SIZE_16BIT, eGRO_011InputRegisters_t::BMS_CELL16_VOLT, "BMS_ Cell16_Volt", 1., NONE);                  //  Cell16_Voltage from BMS
addInputRegister(Protocol, 118, SIZE_16BIT, eGRO_011InputRegisters_t::BMS2_STATUS, "BMS2_Status", 1., NONE);                           //  Status from BMS2
addInputRegister(Protocol, 119, SIZE_16BIT, eGRO_011InputRegisters_t::BMS2_ERROR, "BMS2_Error", 1., NONE);                             //  Error infomation from BMS
addInputRegister(Protocol, 120, SIZE_16BIT, eGRO_011InputRegisters_t::BMS2_WARNINFO, "BMS2_ WarnInfo", 1., NONE);                      //  Warning info from BMS2
addInputRegister(Protocol, 121, SIZE_16BIT, eGRO_011InputRegisters_t::BMS2_SOC, "BMS2_SOC", 1., NONE);                                 //  SOC from BMS2
addInputRegister(Protocol, 122, SIZE_16BIT, eGRO_011InputRegisters_t::BMS2_BATTERYVOLT, "BMS2_ BatteryVolt", 1., NONE);                //  Battery voltage from BMS2
addInputRegister(Protocol, 123, SIZE_16BIT, eGRO_011InputRegisters_t::BMS2_BATTERYCURR, "BMS2_ BatteryCurr", 1., NONE);                //  Battery current from BMS2 BMS2_ BatteryTemp Battery BMS2 BMS2_ MaxCurr Max. charge/discharge current from BMS2
addInputRegister(Protocol, 126, SIZE_16BIT, eGRO_011InputRegisters_t::BMS2_CONSTANTVOLT, "BMS2_ ConstantVolt", 1., NONE);              //  CV voltage from BMS2
addInputRegister(Protocol, 127, SIZE_16BIT, eGRO_011InputRegisters_t::BMS2_BMSINFO, "BMS2_ BMSInfo", 1., NONE);                        //  BMS Information from BMS2
addInputRegister(Protocol, 128, SIZE_16BIT, eGRO_011InputRegisters_t::BMS2_PACKINFO, "BMS2_ PackInfo", 1., NONE);                      //  Pack Information from BMS2
addInputRegister(Protocol, 129, SIZE_16BIT, eGRO_011InputRegisters_t::BMS2_USINGCAP, "BMS2_ UsingCap", 1., NONE);                      //  Using Cap from BMS2
addInputRegister(Protocol, 130, SIZE_16BIT, eGRO_011InputRegisters_t::BMS2_CELL1_VOLT, "BMS2_ Cell1_Volt", 1., NONE);                  //  Cell1_Voltage from BMS2
addInputRegister(Protocol, 131, SIZE_16BIT, eGRO_011InputRegisters_t::BMS2_CELL2_VOLT, "BMS2_ Cell2_Volt", 1., NONE);                  //  Cell2_Voltage from BMS2
addInputRegister(Protocol, 132, SIZE_16BIT, eGRO_011InputRegisters_t::BMS2_CELL3_VOLT, "BMS2_ Cell3_Volt", 1., NONE);                  //  Cell3_Voltage from BMS2
addInputRegister(Protocol, 133, SIZE_16BIT, eGRO_011InputRegisters_t::BMS2_CELL4_VOLT, "BMS2_ Cell4_Volt", 1., NONE);                  //  Cell4_Voltage from BMS2
addInputRegister(Protocol, 134, SIZE_16BIT, eGRO_011InputRegisters_t::BMS2_CELL5_VOLT, "BMS2_ Cell5_Volt", 1., NONE);                  //  Cell5_Voltage from BMS2
addInputRegister(Protocol, 135, SIZE_16BIT, eGRO_011InputRegisters_t::BMS2_CELL6_VOLT, "BMS2_ Cell6_Volt", 1., NONE);                  //  Cell6_Voltage from BMS2
addInputRegister(Protocol, 136, SIZE_16BIT, eGRO_011InputRegisters_t::BMS2_CELL7_VOLT, "BMS2_ Cell7_Volt", 1., NONE);                  //  Cell7_Voltage from BMS2
addInputRegister(Protocol, 137, SIZE_16BIT, eGRO_011InputRegisters_t::BMS2_CELL8_VOLT, "BMS2_ Cell8_Volt", 1., NONE);                  //  Cell8_Voltage from BMS2
addInputRegister(Protocol, 138, SIZE_16BIT, eGRO_011InputRegisters_t::BMS2_CELL9_VOLT, "BMS2_ Cell9_Volt", 1., NONE);                  //  Cell9_Voltage from BMS2
addInputRegister(Protocol, 139, SIZE_16BIT, eGRO_011InputRegisters_t::BMS2_CELL10_VOLT, "BMS2_ Cell10_Volt", 1., NONE);                //  Cell10_Voltage from BMS2
addInputRegister(Protocol, 140, SIZE_16BIT, eGRO_011InputRegisters_t::BMS2_CELL11_VOLT, "BMS2_ Cell11_Volt", 1., NONE);                //  Cell11_Voltage from BMS2
addInputRegister(Protocol, 141, SIZE_16BIT, eGRO_011InputRegisters_t::BMS2_CELL12_VOLT, "BMS2_ Cell12_Volt", 1., NONE);                //  Cell12_Voltage from BMS2
addInputRegister(Protocol, 142, SIZE_16BIT, eGRO_011InputRegisters_t::BMS2_CELL13_VOLT, "BMS2_ Cell13_Volt", 1., NONE);                //  Cell13_Voltage from BMS2
addInputRegister(Protocol, 143, SIZE_16BIT, eGRO_011InputRegisters_t::BMS2_CELL14_VOLT, "BMS2_ Cell14_Volt", 1., NONE);                //  Cell14_Voltage from BMS2
addInputRegister(Protocol, 144, SIZE_16BIT, eGRO_011InputRegisters_t::BMS2_CELL15_VOLT, "BMS2_ Cell15_Volt", 1., NONE);                //  Cell15_Voltage from BMS2
addInputRegister(Protocol, 145, SIZE_16BIT, eGRO_011InputRegisters_t::BMS2_CELL16_VOLT, "BMS2_ Cell16_Volt", 1., NONE);                //  Cell16_Voltage from BMS2
addInputRegister(Protocol, 180, SIZE_16BIT, eGRO_011InputRegisters_t::SOLAR1_STATUS_SOLAR, "Solar1_Status Solar", 1., NONE);           //  Charger1 Status
addInputRegister(Protocol, 181, SIZE_16BIT, eGRO_011InputRegisters_t::SOLAR1_FAULTCODE, "Solar1_FaultCode", 1., NONE);                 //  Solar Charger1 FaultCode
addInputRegister(Protocol, 182, SIZE_16BIT, eGRO_011InputRegisters_t::SOLAR1_WARNINGCODE, "Solar1_WarningCode", 1., NONE);             //  Solar Charger1 WarningCode
addInputRegister(Protocol, 125, SIZE_16BIT, eGRO_011InputRegisters_t::TEMPERATURE, "temperature", 1., TEMPERATURE);                    //  temperature from Detail information, refer to document: Growatt xxSxxP ESS Protocol; from
addInputRegister(Protocol, 183, SIZE_16BIT, eGRO_011InputRegisters_t::SOLAR1_BATVOLT, "Solar1_BatVolt", .1, VOLTAGE);                  //  Solar Charger1 battery voltage 0.01V
addInputRegister(Protocol, 184, SIZE_16BIT, eGRO_011InputRegisters_t::SOLAR1_PV1VOLT, "Solar1_PV1Volt", .1, VOLTAGE);                  //  Solar Charger1 PV1 voltage 0.1V
addInputRegister(Protocol, 185, SIZE_16BIT, eGRO_011InputRegisters_t::SOLAR1_PV2VOLT, "Solar1_PV2Volt", .1, VOLTAGE);                  //  Solar Charger1 PV2 voltage 0.1V
addInputRegister(Protocol, 186, SIZE_16BIT, eGRO_011InputRegisters_t::SOLAR1_BUCK1CURR, "Solar1_Buck1Curr", .1, VOLTAGE);              //  Solar Charger1 Buck1 current 0.1A
addInputRegister(Protocol, 187, SIZE_16BIT, eGRO_011InputRegisters_t::SOLAR1_BUCK2CURR, "Solar1_Buck2Curr", .1, VOLTAGE);              //  Solar Charger1 Buck2 current 0.1A
addInputRegister(Protocol, 188, SIZE_32BIT, eGRO_011InputRegisters_t::SOLAR1_PV1CHRPOWER, "Solar1_PV1ChrPower", .1, POWER_W);          //  Solar Charger1 PV1 charge Power High 16 bit 0.1W
addInputRegister(Protocol, 190, SIZE_32BIT, eGRO_011InputRegisters_t::SOLAR1_PV2CHRPOWER, "Solar1_PV2ChrPower", .1, POWER_W);          //  Solar Charger1 PV2 charge Power High 16 bit 0.1W
addInputRegister(Protocol, 192, SIZE_16BIT, eGRO_011InputRegisters_t::SOLAR1_HS1TEMP, "Solar1_HS1Temp", .1, TEMPERATURE);              //  Solar Charger1 Temperature Buck1 0.1C
addInputRegister(Protocol, 193, SIZE_16BIT, eGRO_011InputRegisters_t::SOLAR1_HS2TEMP, "Solar1_HS2Temp", .1, TEMPERATURE);              //  Solar Charger1 Temperature Buck2 0.1C
addInputRegister(Protocol, 194, SIZE_32BIT, eGRO_011InputRegisters_t::SOLAR1_EPV1_TODAY, "Solar1_Epv1_today", .1, POWER_KWH);          //   Solar Charger1 PV1 Energy today 0.1k Wh
addInputRegister(Protocol, 196, SIZE_32BIT, eGRO_011InputRegisters_t::SOLAR1_EPV1_TOTAL, "Solar1_Epv1_total", .1, POWER_KWH);          //  Solar Charger1 PV1 Energy total High 16 bit 0.1k Wh
addInputRegister(Protocol, 198, SIZE_32BIT, eGRO_011InputRegisters_t::SOLAR1_EPV2_TOTAL, "Solar1_Epv2_total", .1, POWER_KWH);          //  Solar Charger1 PV2 Energy total High 16 bit 0.1k Wh
addInputRegister(Protocol, 200, SIZE_16BIT, eGRO_011InputRegisters_t::SOLAR2_STATUS, "Solar2_Status", 1, NONE);                        //  Solar Charger2 Status
addInputRegister(Protocol, 201, SIZE_16BIT, eGRO_011InputRegisters_t::SOLAR2_FAULTCODE, "Solar2_FaultCode", 1, NONE);                  //  Solar Charger2 FaultCode
addInputRegister(Protocol, 202, SIZE_16BIT, eGRO_011InputRegisters_t::SOLAR2_WARNINGCODE, "Solar2_WarningCode", 1, NONE);              //  Solar Charger2 WarningCode
addInputRegister(Protocol, 203, SIZE_16BIT, eGRO_011InputRegisters_t::SOLAR2_BATVOLT, "Solar2_BatVolt", .01, VOLTAGE);                 //  Solar Charger2 battery voltage 0.01V
addInputRegister(Protocol, 204, SIZE_16BIT, eGRO_011InputRegisters_t::SOLAR2_PV1VOLT, "Solar2_PV1Volt", .1, VOLTAGE);                  //  Solar Charger2 PV1 voltage 0.1V
addInputRegister(Protocol, 205, SIZE_16BIT, eGRO_011InputRegisters_t::SOLAR2_PV2VOLT, "Solar2_PV2Volt", .1, VOLTAGE);                  //  Solar Charger2 PV2 voltage 0.1V
addInputRegister(Protocol, 206, SIZE_16BIT, eGRO_011InputRegisters_t::SOLAR2_BUCK1CURR, "Solar2_Buck1Curr", .1, CURRENT);              //  Solar Charger2 Buck1 current 0.1A
addInputRegister(Protocol, 207, SIZE_16BIT, eGRO_011InputRegisters_t::SOLAR2_BUCK2CURR, "Solar2_Buck2Curr", .1, CURRENT);              //  Solar Charger2 Buck2 current 0.1A
addInputRegister(Protocol, 208, SIZE_32BIT, eGRO_011InputRegisters_t::SOLAR2_PV1CHRPOWER, "Solar2_PV1ChrPower", .1, POWER_W);          //  Solar Charger2 PV1 charge Power High 16 bit 0.1W
addInputRegister(Protocol, 210, SIZE_32BIT, eGRO_011InputRegisters_t::SOLAR2_PV2CHRPOWER, "Solar2_PV2ChrPower", .1, POWER_W);          //  Solar Charger2 PV2 charge Power High 16 bit 0.1W
addInputRegister(Protocol, 212, SIZE_16BIT, eGRO_011InputRegisters_t::SOLAR2_HS1TEMP, "Solar2_HS1Temp", .1, TEMPERATURE);              //  Solar Charger2 Temperature Buck1 0.1C
addInputRegister(Protocol, 213, SIZE_16BIT, eGRO_011InputRegisters_t::SOLAR2_HS2TEMP, "Solar2_HS2Temp", .1, TEMPERATURE);              //  Solar Charger2 Temperature Buck2 0.1C
addInputRegister(Protocol, 214, SIZE_16BIT, eGRO_011InputRegisters_t::SOLAR2_EPV1_TODAY, "Solar2_Epv1_today", .1, POWER_KWH);          //  Solar Charger2 PV1 Energy today 0.1k Wh
addInputRegister(Protocol, 215, SIZE_16BIT, eGRO_011InputRegisters_t::SOLAR2_EPV2_TODAY, "Solar2_Epv2_today", .1, POWER_KWH);          //  Solar Charger2 PV2 Energy today 0.1k Wh
addInputRegister(Protocol, 216, SIZE_32BIT, eGRO_011InputRegisters_t::SOLAR2_EPV1_TOTAL, "Solar2_Epv1_total", .1, POWER_KWH);          //  Solar Charger2 PV1 Energy total High 16 bit 0.1k Wh
addInputRegister(Protocol, 218, SIZE_32BIT, eGRO_011InputRegisters_t::SOLAR2_EPV2_TOTAL, "Solar2_Epv2_total", .1, POWER_KWH);          //  Solar Charger2 PV2 Energy total High 16 bit 0.1k Wh
addInputRegister(Protocol, 220, SIZE_16BIT, eGRO_011InputRegisters_t::SOLAR_CONNECTOKFLAG, "Solar_ConnectOKFlag", 1., NONE);           //  Slave Solar Connect OK Flag 1：Solar Charger1； 2：Solar Charger2； 3：Solar Charger1 2；
addInputRegister(Protocol, 221, SIZE_16BIT, eGRO_011InputRegisters_t::SOLAR_BATVOLTCONSISTFLAG, "Solar_BatVoltConsistFlag", 1., NONE); //  Check Slave Solar Battery Voltage Consist OK Flag 1：Check Solar Charger1  OK；2：Check Solar Charger2 OK； 3：Check Solar Charger1 2 OK；
addInputRegister(Protocol, 222, SIZE_16BIT, eGRO_011InputRegisters_t::SOLAR_TYPESWSTATE, "Solar_TypeSwState", 1., NONE);               //  Solar Charger Type Swtich State 0:Master SolarCharger; 1:Slaver SolarCharger;
addInputRegister(Protocol, 223, SIZE_16BIT, eGRO_011InputRegisters_t::SOLAR_MODESWSTATE, "Solar_ModeSwState", 1., NONE);               //  Solar Charger Mode Swtich State 0: Parallel Mode; 1:Single Mode;
addInputRegister(Protocol, 224, SIZE_16BIT, eGRO_011InputRegisters_t::SOLAR_ADDRSWSTATE, "Solar_AddrSwState", 1., NONE);               //  Solar Charger Addr Swtich State 2~3;
addInputRegister(Protocol, 360, SIZE_16BIT, eGRO_011InputRegisters_t::BMS_GAUGERM, "BMS_ GaugeRM", 1., NONE);                          //  Gauge RM from BMS
addInputRegister(Protocol, 361, SIZE_16BIT, eGRO_011InputRegisters_t::BMS_GAUGEFCC, "BMS_GaugeFCC", 1., NONE);                         //  Gauge FCC from BMS
addInputRegister(Protocol, 362, SIZE_16BIT, eGRO_011InputRegisters_t::BMS_FW, "BMS_ FW", 1., NONE);                                    //  BMS_ FW
addInputRegister(Protocol, 363, SIZE_16BIT, eGRO_011InputRegisters_t::BMS_DELTAVOLT, "BMS_ DeltaVolt", 1., NONE);                      //  Delta V from BMS Detail information, refer to document: Growatt xxSxxP ESS Protocol;
addInputRegister(Protocol, 364, SIZE_16BIT, eGRO_011InputRegisters_t::BMS_CYCLECNT, "BMS_ CycleCnt", 1., NONE);                        //  Cycle Count from BMS
addInputRegister(Protocol, 365, SIZE_16BIT, eGRO_011InputRegisters_t::BMS_SOH, "BMS_ SOH", 1., NONE);                                  //  SOH from BMS
addInputRegister(Protocol, 366, SIZE_16BIT, eGRO_011InputRegisters_t::BMS_GAUGEICCURR, "BMS_ GaugeICCurr", 1., NONE);                  //  Gauge IC current from BMS
addInputRegister(Protocol, 367, SIZE_16BIT, eGRO_011InputRegisters_t::BMS_MCUVERSION, "BMS_ MCUVersion", 1., NONE);                    //  MCU Software version from BMS
addInputRegister(Protocol, 368, SIZE_16BIT, eGRO_011InputRegisters_t::BMS_GAUGEVERSION, "BMS_ GaugeVersion", 1., NONE);                //  Gauge Version from BMS
addInputRegister(Protocol, 369, SIZE_16BIT, eGRO_011InputRegisters_t::BMS_WGAUGEFRVERSION_L, "BMS_ wGaugeFRVersion_L", 1., NONE);      //  Gauge FR Version L16 from BMS // reversed order?
addInputRegister(Protocol, 370, SIZE_16BIT, eGRO_011InputRegisters_t::BMS_WGAUGEFRVERSION_H, "BMS_ wGaugeFRVersion_H", 1., NONE);      //  Gauge FR Version H16 from BMS // reversed order?
addInputRegister(Protocol, 371, SIZE_16BIT, eGRO_011InputRegisters_t::BMS2_GAUGERM, "BMS2_ GaugeRM", 1., NONE);                        //  Gauge RM from BMS2
addInputRegister(Protocol, 372, SIZE_16BIT, eGRO_011InputRegisters_t::BMS2_GAUGEFCC, "BMS2_GaugeFCC", 1., NONE);                       //  Gauge FCC from BMS2
addInputRegister(Protocol, 373, SIZE_16BIT, eGRO_011InputRegisters_t::BMS2_FW, "BMS2_ FW", 1., NONE);                                  //  BMS2_ FW
addInputRegister(Protocol, 374, SIZE_16BIT, eGRO_011InputRegisters_t::BMS2_DELTAVOLT, "BMS2_ DeltaVolt", 1., NONE);                    //  Delta V from BMS2
addInputRegister(Protocol, 375, SIZE_16BIT, eGRO_011InputRegisters_t::BMS2_CYCLECNT, "BMS2_ CycleCnt", 1., NONE);                      //  Cycle Count from BMS2
addInputRegister(Protocol, 376, SIZE_16BIT, eGRO_011InputRegisters_t::BMS2_SOH, "BMS2_ SOH", 1., NONE);                                //  SOH from BMS2
addInputRegister(Protocol, 377, SIZE_16BIT, eGRO_011InputRegisters_t::BMS2_GAUGEICCURR, "BMS2_ GaugeICCurr", 1., NONE);                //  Gauge IC current from BMS2
addInputRegister(Protocol, 378, SIZE_16BIT, eGRO_011InputRegisters_t::BMS2_MCUVERSION, "BMS2_ MCUVersion", 1., NONE);                  //  MCU Software version from BMS2
addInputRegister(Protocol, 379, SIZE_16BIT, eGRO_011InputRegisters_t::BMS2_GAUGEVERSION, "BMS2_ GaugeVersion", 1., NONE);              //  Gauge Version from BMS2
addInputRegister(Protocol, 380, SIZE_16BIT, eGRO_011InputRegisters_t::BMS2_WGAUGEFRVERSION_L, "BMS2_ wGaugeFRVersion_L", 1., NONE);    //  Gauge FR Version L16 from BMS2 // reversed order?
addInputRegister(Protocol, 381, SIZE_16BIT, eGRO_011InputRegisters_t::BMS2_WGAUGEFRVERSION_H, "BMS2_ wGaugeFRVersion_H", 1., NONE);    //  Gauge FR Version H16 from BMS2 Detail information, refer to document: Growatt xxSxxP ESS Protocol; // reversed order?
              // clang-format on

  // clang-format off
addHoldingRegister(Protocol, 0, SIZE_16BIT, eGRO_011HoldingRegisters_t::ON_Off, "On/Off", 1., NONE);                          // The Standby On/Off state and the AC output DisEN/EN state; The low byte is the Standby on/off(1/0),
                                                                                                                              // the high byte is the AC output disable/enable (1/0). Cust ome r Writ e Value 0x0000: Standby Output enable; 0x0001: Standby Output enable; 0x0100: Standby Output disable; 0x0101: Standby Output disable; Unit Initial value 0 off, on, off, on,
addHoldingRegister(Protocol, 1, SIZE_16BIT, eGRO_011HoldingRegisters_t::OUTPUTCONFIG, "OutputConfig", 1., NONE);              // AC output set W 0: BAT First; 1: PV First; 2: UTI First; 0
addHoldingRegister(Protocol, 2, SIZE_16BIT, eGRO_011HoldingRegisters_t::CHARGECONFIG, "ChargeConfig", 1., NONE);              // Charge source set W 0: PV first; 1: PV&UTI; 2: PV Only; 0
addHoldingRegister(Protocol, 3, SIZE_16BIT, eGRO_011HoldingRegisters_t::UTIOUTSTART, "UtiOutStart", 1., NONE);                // Uti Output Start Time W 0‐23 H(hour) 0
addHoldingRegister(Protocol, 4, SIZE_16BIT, eGRO_011HoldingRegisters_t::UTIOUTEND, "UtiOutEnd", 1., NONE);                    // Uti Output End Time W 0‐23 H(hour) 0
addHoldingRegister(Protocol, 5, SIZE_16BIT, eGRO_011HoldingRegisters_t::UTICHARGESTART, "UtiChargeStart", 1., NONE);          // Uti Charge Start Time W 0‐23 H(hour) 0
addHoldingRegister(Protocol, 6, SIZE_16BIT, eGRO_011HoldingRegisters_t::UTICHARGEEND, "UtiChargeEnd", 1., NONE);              // Uti Charge End Time W 0‐23 H(hour) 0
addHoldingRegister(Protocol, 7, SIZE_16BIT, eGRO_011HoldingRegisters_t::PVMODEL, "PVModel", 1., NONE);                        // PV Input Mode W 0:Independent; 1: Parallel; 0
addHoldingRegister(Protocol, 8, SIZE_16BIT, eGRO_011HoldingRegisters_t::ACINMODEL, "ACInModel", 1., NONE);                    // AC Input Mode W 0: APL,90‐280VAC; 1: UPS,170‐280VAC; 0
addHoldingRegister(Protocol, 9, SIZE_16BIT, eGRO_011HoldingRegisters_t::FWVERSIONH, "Fw version H", 1., NONE);                // Firmware version (high)
addHoldingRegister(Protocol, 10, SIZE_16BIT, eGRO_011HoldingRegisters_t::FWVERSIONM, "Fw version M", 1., NONE);               // Firmware version (middle)
addHoldingRegister(Protocol, 11, SIZE_16BIT, eGRO_011HoldingRegisters_t::FWVERSIONL, "Fw version L", 1., NONE);               // Firmware version (low)
addHoldingRegister(Protocol, 12, SIZE_16BIT, eGRO_011HoldingRegisters_t::FWVERSION2H, "Fw version2 H", 1., NONE);             // Control Firmware version (high)
addHoldingRegister(Protocol, 13, SIZE_16BIT, eGRO_011HoldingRegisters_t::FWVERSION2M, "Fw version2 M", 1., NONE);             // Control Firmware version (middle)
addHoldingRegister(Protocol, 14, SIZE_16BIT, eGRO_011HoldingRegisters_t::FWVERSION2L, "Fw version2 L", 1., NONE);             // Control Firmware version (low)
addHoldingRegister(Protocol, 15, SIZE_16BIT, eGRO_011HoldingRegisters_t::LCDLANGUAGE, "LCD language", 1., NONE);              // LCD language W 0‐1 1 English
addHoldingRegister(Protocol, 18, SIZE_16BIT, eGRO_011HoldingRegisters_t::OUTPUTVOLTTYPE, "OutputVoltType", 1., NONE);         // Output Volt Type W 0: 208VAC; 1: 230VAC 2: 240VAC 1
addHoldingRegister(Protocol, 19, SIZE_16BIT, eGRO_011HoldingRegisters_t::OUTPUTFREQTYPE, "OutputFreqType", 1., NONE);         // Output Freq Type W 0: 50Hz; 1: 60Hz 0
addHoldingRegister(Protocol, 20, SIZE_16BIT, eGRO_011HoldingRegisters_t::OVERLOADRESTART, "OverLoadRestart", 1., NONE);       // Over Load Restart W 0:Yes; 1:No; 2: Swith to UTI; 0 Yes(over Load 1mins to restart, after over Load three times to stop output)
addHoldingRegister(Protocol, 21, SIZE_16BIT, eGRO_011HoldingRegisters_t::OVERTEMPRESTART, "OverTempRestart", 1., NONE);       // Over Temperature Restart W 0:Yes; 1:No; 0 Yes(over Temperature to after restart ， over Temperature three times to stop output)
addHoldingRegister(Protocol, 22, SIZE_16BIT, eGRO_011HoldingRegisters_t::BUZZEREN, "BuzzerEN", 1., NONE);                     // Buzzer on/off enable W
addHoldingRegister(Protocol, 23, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIALNO5, "Serial NO .5", 1., NONE);                // Serial number 5 W
addHoldingRegister(Protocol, 24, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIALNO4, "Serial No .4", 1., NONE);                // Serial number 4 W
addHoldingRegister(Protocol, 25, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIALNO3, "Serial No .3", 1., NONE);                // Serial number 3 W
addHoldingRegister(Protocol, 26, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIALNO2, "Serial No .2", 1., NONE);                // Serial number 2 W
addHoldingRegister(Protocol, 27, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIALNO1, "Serial No .1", 1., NONE);                // Serial number 1 W
addHoldingRegister(Protocol, 28, SIZE_32BIT, eGRO_011HoldingRegisters_t::MOUDLE, "Moudle", 1., NONE);                         // Inverter Moudle (high) W M‐power rate: 3: 3KW; 5:5KW; S‐Aging; 0: Normal Mode; 1: Aging Mode;
addHoldingRegister(Protocol, 30, SIZE_16BIT, eGRO_011HoldingRegisters_t::COMADDRESS, "Com Address", 1., NONE);                // Address Communicate addre ss W 1~254 1
addHoldingRegister(Protocol, 31, SIZE_16BIT, eGRO_011HoldingRegisters_t::FLASHSTART, "FlashStart", 1., NONE);                 // Update firmware W 0x0001: own 0X0100: control broad
addHoldingRegister(Protocol, 32, SIZE_16BIT, eGRO_011HoldingRegisters_t::RESETUSERINFO, "ResetUser Info", 1., NONE);          // Reset User Information W 0x0001
addHoldingRegister(Protocol, 33, SIZE_16BIT, eGRO_011HoldingRegisters_t::RESETTOFACTORY, "Resetto factory", 1., NONE);        // Reset to factory W 0x0001
addHoldingRegister(Protocol, 34, SIZE_16BIT, eGRO_011HoldingRegisters_t::MAXCHARGECURR, "MaxChargeCurr", 1., NONE);           // Max Charge Current W 10~130 1A 70
addHoldingRegister(Protocol, 35, SIZE_16BIT, eGRO_011HoldingRegisters_t::BULKCHARGEVOLT, "BulkChargeVolt", 1., NONE);         // Bulk Charge Volt W 500~580 0.1V 564
addHoldingRegister(Protocol, 36, SIZE_16BIT, eGRO_011HoldingRegisters_t::FLOATCHARGEVOLT, "FloatChargeVolt", 1., NONE);       // Float Charge Volt W 500~560 0.1V 540
addHoldingRegister(Protocol, 37, SIZE_16BIT, eGRO_011HoldingRegisters_t::BATLOWTOUTIVOLT, "BatLowToUtiVolt", 1., NONE);       // Bat Low Volt Switch To Uti W 444~514 0.1V 464
addHoldingRegister(Protocol, 38, SIZE_16BIT, eGRO_011HoldingRegisters_t::FLOATCHARGECURR, "FloatChargeCurr", 1., NONE);       // Float Charge Current W 0~80 0.1A
addHoldingRegister(Protocol, 39, SIZE_16BIT, eGRO_011HoldingRegisters_t::BATTERY, "Battery", 1., NONE);                       // Type Battery Type W 0: Lead_Acid; 1: Lithium; 2: CustomLead_Acid; 1 Can be set at standy state Only
addHoldingRegister(Protocol, 40, SIZE_16BIT, eGRO_011HoldingRegisters_t::AGING, "Aging", 1., NONE);                           // Mode Aging Mode W 0: Normal Mode; 1: Aging Mode; 0 Can be set at standy state Only
addHoldingRegister(Protocol, 43, SIZE_16BIT, eGRO_011HoldingRegisters_t::DTC, "DTC", 1., NONE);                               // Device Type Code
addHoldingRegister(Protocol, 45, SIZE_16BIT, eGRO_011HoldingRegisters_t::SYSYEAR, "Sys Year", 1., NONE);                      // System time‐year W Year offset is 2000
addHoldingRegister(Protocol, 46, SIZE_16BIT, eGRO_011HoldingRegisters_t::SYSMONTH, "Sys Month", 1., NONE);                    // System time‐ Month W
addHoldingRegister(Protocol, 47, SIZE_16BIT, eGRO_011HoldingRegisters_t::SYSDAY, "Sys Day", 1., NONE);                        // System time‐ Day W
addHoldingRegister(Protocol, 48, SIZE_16BIT, eGRO_011HoldingRegisters_t::SYSHOUR, "Sys Hour", 1., NONE);                      // System time‐ Hour W
addHoldingRegister(Protocol, 49, SIZE_16BIT, eGRO_011HoldingRegisters_t::SYSMIN, "Sys Min", 1., NONE);                        // System time‐ Min W
addHoldingRegister(Protocol, 50, SIZE_16BIT, eGRO_011HoldingRegisters_t::SYSSEC, "Sys Sec", 1., NONE);                        // System time‐ Second W
addHoldingRegister(Protocol, 59, SIZE_16BIT, eGRO_011HoldingRegisters_t::MANUFACTURERINFO8, "Manufacturer Info 8", 1., NONE); // Manufacturer information (high)
addHoldingRegister(Protocol, 60, SIZE_16BIT, eGRO_011HoldingRegisters_t::MANUFACTURERINFO7, "Manufacturer Info 7", 1., NONE); // Manufacturer information (middle)
addHoldingRegister(Protocol, 61, SIZE_16BIT, eGRO_011HoldingRegisters_t::MANUFACTURERINFO6, "Manufacturer Info 6", 1., NONE); // Manufacturer information (low)
addHoldingRegister(Protocol, 62, SIZE_16BIT, eGRO_011HoldingRegisters_t::MANUFACTURERINFO5, "Manufacturer Info 5", 1., NONE); // Manufacturer information (high)
addHoldingRegister(Protocol, 63, SIZE_16BIT, eGRO_011HoldingRegisters_t::MANUFACTURERINFO4, "Manufacturer Info 4", 1., NONE); // Manufacturer information (middle)
addHoldingRegister(Protocol, 64, SIZE_16BIT, eGRO_011HoldingRegisters_t::MANUFACTURERINFO3, "Manufacturer Info 3", 1., NONE); // Manufacturer information (low)
addHoldingRegister(Protocol, 65, SIZE_16BIT, eGRO_011HoldingRegisters_t::MANUFACTURERINFO2, "Manufacturer Info 2", 1., NONE); // Manufacturer information (low)
addHoldingRegister(Protocol, 66, SIZE_16BIT, eGRO_011HoldingRegisters_t::MANUFACTURERINFO1, "Manufacturer Info 1", 1., NONE); // Manufacturer information (high) ASCII
addHoldingRegister(Protocol, 67, SIZE_16BIT, eGRO_011HoldingRegisters_t::FWBUILDNO4, "FW Build No .4", 1., NONE);             // Control FW Build No. 2 ASCII
addHoldingRegister(Protocol, 68, SIZE_16BIT, eGRO_011HoldingRegisters_t::FWBUILDNO3, "FW Build No .3", 1., NONE);             // Control FW Build No. 1
addHoldingRegister(Protocol, 69, SIZE_16BIT, eGRO_011HoldingRegisters_t::FWBUILDNO2, "FW Build No .2", 1., NONE);             // COM FW Build No. 2
addHoldingRegister(Protocol, 70, SIZE_16BIT, eGRO_011HoldingRegisters_t::FWBUILDNO1, "FW Build No .1", 1., NONE);             // COM FW Build No. 1
addHoldingRegister(Protocol, 72, SIZE_16BIT, eGRO_011HoldingRegisters_t::SYSWEEKLY, "Sys Weekly", 1., NONE);                  // Sys Weekly
addHoldingRegister(Protocol, 73, SIZE_16BIT, eGRO_011HoldingRegisters_t::MODBUSVERSION, "ModbusVersion", 1., NONE);           // Modbus Version
addHoldingRegister(Protocol, 76, SIZE_32BIT, eGRO_011HoldingRegisters_t::RATEWATT, "Rate Watt", 1., POWER_W);                 // Watt Rate active power(high) 0.1W
addHoldingRegister(Protocol, 78, SIZE_32BIT, eGRO_011HoldingRegisters_t::RATEVA, "Rate VA", 1., VA);                          // Rata apparent power (high) 0.1VA
addHoldingRegister(Protocol, 80, SIZE_16BIT, eGRO_011HoldingRegisters_t::FACTORY, "Factory", 1., NONE);                       // The ODM Info code BLVersion2 Boot loader version2 ASCII 71 W 0‐6 Eg：207 is V2.07 Int(16bit s)
addHoldingRegister(Protocol, 162, SIZE_16BIT, eGRO_011HoldingRegisters_t::BLVERSION2, "BLVersion2", 1., NONE);                // bootloader version
                             // clang-format on

  makeSegments(eGRO_011InputRegisters_t::LASTInput, maxFragmentSize,
               Protocol.InputRegisters, Protocol.InputReadFragments,Protocol.InputFragmentCount);
    Protocol.InputRegisterCount = static_cast<uint16_t>(eGRO_011InputRegisters_t::LASTInput);
  makeSegments(eGRO_011HoldingRegisters_t::LASTHolding, maxFragmentSize,
               Protocol.HoldingRegisters, Protocol.HoldingReadFragments,Protocol.HoldingFragmentCount);
    Protocol.HoldingRegisterCount = static_cast<uint16_t>(eGRO_011HoldingRegisters_t::LASTHolding);
}
