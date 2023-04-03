#include "Arduino.h"

#include "Growatt113.h"

// information from:
// https://www.amosplanet.org/wp-content/uploads/2022/12/%E9%80%9A%E4%BF%A1%E5%8D%8F%E8%AE%AEMAX_Growatt-Inverter-Modbus-RTU-Protocol_II-V1_13_20190116-English.pdf

// Supported inverters:
// ????

void init_growatt113(sProtocolDefinition_t& Protocol) {

addHoldingRegister(Protocol, 00, SIZE_16BIT, eGRO_011HoldingRegisters_t::ONOFF, "OnOff   ", 1., NONE);                           // Remote On/Off . On（1）； Off（0） W 0or1  1 When PV restart , recover 1.
addHoldingRegister(Protocol, 01, SIZE_16BIT, eGRO_011HoldingRegisters_t::SAFTYFUNCEN, "SaftyFuncEn  ", 1., NONE);                // Bit0: SPI enable Bit1: AutoTestStart Bit2: LVFRT enable Bit3: FreqDeratingEnable Bit4: Softstart enable Bit5: DRMS enable Bit6:PowerVoltFunc En Bit7~15:reserved W 0 : disable 1: enable   SPI: system protection interface Bit0~3:for CEI0-21 Bit4~6:for SAA
addHoldingRegister(Protocol, 02, SIZE_16BIT, eGRO_011HoldingRegisters_t::PF, "PF  ", 1., NONE);                                  // CMD memory state Set Holding register3,4,5,99 CMD will be memory or not(1/0) ,  if  not ,  these settings   are the initial value. W 0or1  0 Means  these  settings    will  be acting  or not when next power on
addHoldingRegister(Protocol, 03, SIZE_16BIT, eGRO_011HoldingRegisters_t::ACTIVE_P, "Active P  ", 1., NONE);                      // Rate Inverter Max output active power percent   W 0-100 or   255 % 255 255: power is not be limited
addHoldingRegister(Protocol, 04, SIZE_16BIT, eGRO_011HoldingRegisters_t::REACTIVE_P, "Reactive P ", 1., NONE);                   // Rate Inverter max output reactive power percent W 0-100 or 255 % 255 255: power is not be limited
addHoldingRegister(Protocol, 05, SIZE_16BIT, eGRO_011HoldingRegisters_t::POWER_FACTOR, "Power factor  ", 1., NONE);              // Inverter  output  power factor’s 10000 times W 0-20000 , 0-10000 is underexcited , other is overexcited  0
addHoldingRegister(Protocol, 06, SIZE_32BIT, eGRO_011HoldingRegisters_t::PMAX_NORMAL, "Pmax  Normal  ", 1., NONE);               //   power (high)   0.1VA
addHoldingRegister(Protocol, 08, SIZE_16BIT, eGRO_011HoldingRegisters_t::VNORMAL, "Vnormal ", 1., NONE);                         // Normal work PV voltage   0.1V
addHoldingRegister(Protocol, 09, SIZE_16BIT, eGRO_011HoldingRegisters_t::FW_VERSION_H, "Fw version H ", 1., NONE);               //  Firmware version (high)   ASCII
addHoldingRegister(Protocol, 10, SIZE_16BIT, eGRO_011HoldingRegisters_t::FW_VERSION_M, "Fw version M ", 1., NONE);               // Firmware version (middle)
addHoldingRegister(Protocol, 11, SIZE_16BIT, eGRO_011HoldingRegisters_t::FW_VERSION_L, "Fw version L ", 1., NONE);               // Firmware version (low)
addHoldingRegister(Protocol, 12, SIZE_16BIT, eGRO_011HoldingRegisters_t::FW_VERSION2_H, "Fw version2 H ", 1., NONE);             // Control Firmware version (high)   ASCII
addHoldingRegister(Protocol, 13, SIZE_16BIT, eGRO_011HoldingRegisters_t::FW_VERSION2_M, "Fw version2 M ", 1., NONE);             // Control Firmware version (middle)   ASCII
addHoldingRegister(Protocol, 14, SIZE_16BIT, eGRO_011HoldingRegisters_t::FW_VERSION2_L, "Fw version2 L ", 1., NONE);             // Control Firmware version (low)   digital
addHoldingRegister(Protocol, 15, SIZE_16BIT, eGRO_011HoldingRegisters_t::LCD_LANGUAGE, "LCD language ", 1., NONE);               // LCD language W 0-5   0: Italian; 1: English; 2: German; 3: Spanish; 4: French; 5: Chinese;
addHoldingRegister(Protocol, 16, SIZE_16BIT, eGRO_011HoldingRegisters_t::COUNTRYSELECTED, "CountrySelected ", 1., NONE);         // Country Selected or not W 0: need to select; 1: have selected
addHoldingRegister(Protocol, 17, SIZE_16BIT, eGRO_011HoldingRegisters_t::VPV_START, "Vpv start", 1., NONE);                      //  Input start voltage   W  0.1V
addHoldingRegister(Protocol, 18, SIZE_16BIT, eGRO_011HoldingRegisters_t::TIME_START, "Time start ", 1., NONE);                   // Start time W  1s
addHoldingRegister(Protocol, 19, SIZE_16BIT, eGRO_011HoldingRegisters_t::RESTARTDELAY_TIME, "RestartDelay Time ", 1., NONE);     // Restart Delay Time after fault back; W  1s
addHoldingRegister(Protocol, 20, SIZE_16BIT, eGRO_011HoldingRegisters_t::WPOWERSTART, "wPowerStart", 1., NONE);                  //  Slope Power start slope W 1-1000 0.1%
addHoldingRegister(Protocol, 21, SIZE_16BIT, eGRO_011HoldingRegisters_t::WPOWERREST, "wPowerRest ", 1., NONE);                   // artSlopeEE Power restart slope W 1-1000 0.1%
addHoldingRegister(Protocol, 22, SIZE_16BIT, eGRO_011HoldingRegisters_t::WSELECTBAUD, "wSelectBaud ", 1., NONE);                 // rate Select communicationbaudrate 0: 9600bps 1:38400bps W 0-1  0
addHoldingRegister(Protocol, 23, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIAL_NO_5, "Serial NO. 5 ", 1., NONE);                // Serial number 5   ASCII
addHoldingRegister(Protocol, 24, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIAL_NO_4, "Serial No. 4", 1., NONE);                 //  Serial number 4
addHoldingRegister(Protocol, 25, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIAL_NO_3, "Serial No. 3 ", 1., NONE);                // Serial number 3
addHoldingRegister(Protocol, 26, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIAL_NO_2, "Serial No. 2 ", 1., NONE);                // Serial number 2
addHoldingRegister(Protocol, 27, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIAL_NO_1, "Serial No. 1 ", 1., NONE);                // Serial number 1
addHoldingRegister(Protocol, 28, SIZE_32BIT, eGRO_011HoldingRegisters_t::MODULE, "Module ", 1., NONE);                           // Inverter Module (high)  &*5
addHoldingRegister(Protocol, 30, SIZE_16BIT, eGRO_011HoldingRegisters_t::COM_ADDRESS, "Com Address ", 1., NONE);                 // Communicate   address W 1-254  1
addHoldingRegister(Protocol, 31, SIZE_16BIT, eGRO_011HoldingRegisters_t::FLASHSTART, "FlashStart ", 1., NONE);                   // Update firmware W 1
addHoldingRegister(Protocol, 32, SIZE_16BIT, eGRO_011HoldingRegisters_t::RESET_USER_INFO, "Reset User Info", 1., NONE);          //  Reset User Information W 0x0001
addHoldingRegister(Protocol, 33, SIZE_16BIT, eGRO_011HoldingRegisters_t::RESET_TO_FACTORY, "Reset to factory ", 1., NONE);       // Reset to factory W 0x0001
addHoldingRegister(Protocol, 34, SIZE_16BIT, eGRO_011HoldingRegisters_t::MANUFACTURER_INFO_8, "Manufacturer Info 8", 1., NONE);  //  Manufacturer information (high)   ASCII
addHoldingRegister(Protocol, 35, SIZE_16BIT, eGRO_011HoldingRegisters_t::MANUFACTURER_INFO_7, "Manufacturer Info 7 ", 1., NONE); // Manufacturer information (middle)
addHoldingRegister(Protocol, 36, SIZE_16BIT, eGRO_011HoldingRegisters_t::MANUFACTURER_INFO_6, "Manufacturer Info 6", 1., NONE);  //  Manufacturer information (low)
addHoldingRegister(Protocol, 37, SIZE_16BIT, eGRO_011HoldingRegisters_t::MANUFACTURER_INFO_5, "Manufacturer Info 5", 1., NONE);  //  Manufacturer information (high)
addHoldingRegister(Protocol, 38, SIZE_16BIT, eGRO_011HoldingRegisters_t::MANUFACTURER_INFO_4, "Manufacturer Info 4", 1., NONE);  //  Manufacturer information (middle)
addHoldingRegister(Protocol, 39, SIZE_16BIT, eGRO_011HoldingRegisters_t::MANUFACTURER_INFO_3, "Manufacturer Info 3", 1., NONE);  //  Manufacturer information (low)
addHoldingRegister(Protocol, 40, SIZE_16BIT, eGRO_011HoldingRegisters_t::MANUFACTURER_INFO_2, "Manufacturer Info 2", 1., NONE);  //  Manufacturer information (low)
addHoldingRegister(Protocol, 41, SIZE_16BIT, eGRO_011HoldingRegisters_t::MANUFACTURER_INFO_1, "Manufacturer Info 1 ", 1., NONE); // Manufacturer information (high)
addHoldingRegister(Protocol, 42, SIZE_16BIT, eGRO_011HoldingRegisters_t::BPARALLELANTIBACKFLOWHOSTNORESPONSEFLAG, "bParallelAntiBackflowHostNoResponseFlag", 1., NONE); //  Parallel Anti-Backflow Host NoResponse Flag W 0 ： Response OK 1 ：NoResponse   Parallel Anti-Backflow Host NoResponse Flag 43 DTC Device Type Code  &*6
addHoldingRegister(Protocol, 44, SIZE_16BIT, eGRO_011HoldingRegisters_t::TP, "TP ", 1., NONE);                                                                          // Input tracker num and output phase num  Eg:0x0203 is two    MPPT and 3ph output
addHoldingRegister(Protocol, 45, SIZE_16BIT, eGRO_011HoldingRegisters_t::SYS_YEAR, "Sys Year ", 1., NONE);                                                              // System time-year W Year offset is 0   Local time 46 Sys Month System time- Month W
addHoldingRegister(Protocol, 47, SIZE_16BIT, eGRO_011HoldingRegisters_t::SYS_DAY, "Sys Day ", 1., NONE);                                                                // System time- Day W
addHoldingRegister(Protocol, 48, SIZE_16BIT, eGRO_011HoldingRegisters_t::SYS_HOUR, "Sys Hour", 1., NONE);                                                               //  System time- Hour W
addHoldingRegister(Protocol, 49, SIZE_16BIT, eGRO_011HoldingRegisters_t::SYS_MIN, "Sys Min", 1., NONE);                                                                 //  System time- Min W
addHoldingRegister(Protocol, 50, SIZE_16BIT, eGRO_011HoldingRegisters_t::SYS_SEC, "Sys Sec", 1., NONE);                                                                 //  System time- Second W
addHoldingRegister(Protocol, 51, SIZE_16BIT, eGRO_011HoldingRegisters_t::SYS_WEEKLY, "Sys Weekly ", 1., NONE);                                                          // System Weekly W 0-6
addHoldingRegister(Protocol, 52, SIZE_16BIT, eGRO_011HoldingRegisters_t::VAC_LOW_GRID, "Vac low Grid ", 1., NONE);                                                      // voltage low limit protect   W  0.1V
addHoldingRegister(Protocol, 53, SIZE_16BIT, eGRO_011HoldingRegisters_t::VAC_HIGH_GRID, "Vac high Grid", 1., NONE);                                                     //  voltage high limit protect   W  0.1V
addHoldingRegister(Protocol, 54, SIZE_16BIT, eGRO_011HoldingRegisters_t::FAC_LOW_GRID, "Fac low   Grid ", 1., NONE);                                                    // frequency low limit protect   W  0.01 Hz
addHoldingRegister(Protocol, 55, SIZE_16BIT, eGRO_011HoldingRegisters_t::FAC_HIGH_GRID, "Fac high Grid ", 1., NONE);                                                    // high frequencylimit protect   W  0.01 Hz
addHoldingRegister(Protocol, 56, SIZE_16BIT, eGRO_011HoldingRegisters_t::VAC_LOW_2_GRID, "Vac low 2 Grid", 1., NONE);                                                   //  voltage low limit protect 2 W  0.1V
addHoldingRegister(Protocol, 57, SIZE_16BIT, eGRO_011HoldingRegisters_t::VAC_HIGH_2_GRID, "Vac high 2 Grid", 1., NONE);                                                 //  voltage high limit protect 2 W  0.1V
addHoldingRegister(Protocol, 58, SIZE_16BIT, eGRO_011HoldingRegisters_t::FAC_LOW_2_GRID, "Fac low 2 Grid", 1., NONE);                                                   //  frequency low limit protect 2 W  0.01 Hz
addHoldingRegister(Protocol, 59, SIZE_16BIT, eGRO_011HoldingRegisters_t::FAC_HIGH_2_GRID, "Fac high 2 Grid", 1., NONE);                                                 //  high frequency limit protect 2 W  0.01 Hz
addHoldingRegister(Protocol, 60, SIZE_16BIT, eGRO_011HoldingRegisters_t::VAC_LOW_3_GRID, "Vac low 3 Grid", 1., NONE);                                                   //  voltage low limit protect 3 W   0.1V
addHoldingRegister(Protocol, 61, SIZE_16BIT, eGRO_011HoldingRegisters_t::VAC_HIGH_3_GRID, "Vac high 3 Grid", 1., NONE);                                                 //   voltage  high  limit protect 3 W   0.1V
addHoldingRegister(Protocol, 62, SIZE_16BIT, eGRO_011HoldingRegisters_t::FAC_LOW_3_GRID, "Fac low 3 Grid", 1., NONE);                                                   //  frequency low limit protect 3 W   0.01Hz
addHoldingRegister(Protocol, 63, SIZE_16BIT, eGRO_011HoldingRegisters_t::FAC_HIGH_3_GRID, "Fac high 3 Grid", 1., NONE);                                                 //  frequency high limit protect 3 W   0.01Hz
addHoldingRegister(Protocol, 64, SIZE_16BIT, eGRO_011HoldingRegisters_t::VAC_LOW_C_GRID, "Vac low C Grid", 1., NONE);                                                   //  low voltage limit connect to Grid W  0.1V
addHoldingRegister(Protocol, 65, SIZE_16BIT, eGRO_011HoldingRegisters_t::VAC_HIGH_C_GRID, "Vac high C Grid", 1., NONE);                                                 //  high voltage limit connect to Grid W  0.1V
addHoldingRegister(Protocol, 66, SIZE_16BIT, eGRO_011HoldingRegisters_t::FAC_LOW_C_GRID, "Fac low C Grid", 1., NONE);                                                   //  low frequency limit connect to Grid W  0.01 Hz
addHoldingRegister(Protocol, 67, SIZE_16BIT, eGRO_011HoldingRegisters_t::FAC_HIGH_C_GRID, "Fac high C Grid", 1., NONE);                                                 //  high frequency limit connect to Grid W  0.01 Hz
addHoldingRegister(Protocol, 68, SIZE_16BIT, eGRO_011HoldingRegisters_t::VAC_LOW1_TIME_GRID, "Vac low1 time Grid", 1., NONE);                                           //  voltage low limit protect time    1 W  Cycle
addHoldingRegister(Protocol, 69, SIZE_16BIT, eGRO_011HoldingRegisters_t::VAC_HIGH1_TIME_GRID, "Vac high1 time Grid", 1., NONE);                                         //   voltage  high  limit protect time    1 W  Cycle
addHoldingRegister(Protocol, 70, SIZE_16BIT, eGRO_011HoldingRegisters_t::VAC_LOW2_TIME_GRID, "Vac low2 time Grid", 1., NONE);                                           //  voltage low limit protect time    2 W  Cycle
addHoldingRegister(Protocol, 71, SIZE_16BIT, eGRO_011HoldingRegisters_t::VAC_HIGH2_GRID_VOLTAGE, "Vac high2 Grid  voltage", 1., NONE);                                  //   high  limit W  Cycle
addHoldingRegister(Protocol, 72, SIZE_16BIT, eGRO_011HoldingRegisters_t::FAC_LOW1_TIME_GRID, "Fac low1 time Grid", 1., NONE);                                           //  frequency low limit protect time    1 W  Cycle
addHoldingRegister(Protocol, 73, SIZE_16BIT, eGRO_011HoldingRegisters_t::FAC_HIGH1_TIME_GRID, "Fac high1 time Grid", 1., NONE);                                         //  frequency high limit protect time    1 W  Cycle
addHoldingRegister(Protocol, 74, SIZE_16BIT, eGRO_011HoldingRegisters_t::FAC_LOW2_TIME_GRID, "Fac low2 time Grid", 1., NONE);                                           //  frequency low limit protect time    2 W  Cycle
addHoldingRegister(Protocol, 75, SIZE_16BIT, eGRO_011HoldingRegisters_t::FAC_HIGH2_TIME_GRID, "Fac high2 time Grid", 1., NONE);                                         //  frequency high limit protect time    2 W  Cycle
addHoldingRegister(Protocol, 76, SIZE_16BIT, eGRO_011HoldingRegisters_t::VAC_LOW3_TIME_GRID, "Vac low3 time Grid", 1., NONE);                                           //  voltage low limit protect time    3 W   Cycle
addHoldingRegister(Protocol, 77, SIZE_16BIT, eGRO_011HoldingRegisters_t::VAC_HIGH3_TIME_GRID, "Vac high3 time Grid", 1., NONE);                                         //   voltage  high  limit protect time    3 W   Cycle
addHoldingRegister(Protocol, 78, SIZE_16BIT, eGRO_011HoldingRegisters_t::FAC_LOW3_TIME_GRID, "Fac low3 time Grid", 1., NONE);                                           //  frequency low limit protect time    3 W   Cycle
addHoldingRegister(Protocol, 79, SIZE_16BIT, eGRO_011HoldingRegisters_t::FAC_HIGH3_TIME_GRID, "Fac high3 time Grid", 1., NONE);                                         //  frequency high limit protect time    3 W   Cycle
addHoldingRegister(Protocol, 80, SIZE_16BIT, eGRO_011HoldingRegisters_t::U10MIN, "U10min ", 1., NONE);                                                                  // Volt protection for 10 min W  0.1V 1.1Vn
addHoldingRegister(Protocol, 81, SIZE_16BIT, eGRO_011HoldingRegisters_t::PV_VOLTAGE_HIGH, "PV Voltage High ", 1., NONE);                                                //   Fault   PV Voltage High   Fault    W   0.1V
addHoldingRegister(Protocol, 82, SIZE_16BIT, eGRO_011HoldingRegisters_t::FW_BUILD_NO_5, "FW Build No. 5", 1., NONE);                                                    //  FW Build version   ASCII
addHoldingRegister(Protocol, 83, SIZE_16BIT, eGRO_011HoldingRegisters_t::FW_BUILD_NO_4, "FW Build No. 4", 1., NONE);                                                    //  FW Build version   ASCII
addHoldingRegister(Protocol, 84, SIZE_16BIT, eGRO_011HoldingRegisters_t::FW_BUILD_NO_3, "FW Build No. 3", 1., NONE);                                                    //  DSP1 FW Build No.   ASCII
addHoldingRegister(Protocol, 85, SIZE_16BIT, eGRO_011HoldingRegisters_t::FW_BUILD_NO_2, "FW Build No. 2", 1., NONE);                                                    //  DSP2 FW Build No.   ASCII
addHoldingRegister(Protocol, 86, SIZE_16BIT, eGRO_011HoldingRegisters_t::FW_BUILD_NO_1, "FW Build No. 1", 1., NONE);                                                    //  M3 FW Build No.   ASCII
addHoldingRegister(Protocol, 87, SIZE_16BIT, eGRO_011HoldingRegisters_t::FW_BUILD_NO_0, "FW Build No. 0", 1., NONE);                                                    //  CPLD FW Build No.   ASCII
addHoldingRegister(Protocol, 88, SIZE_16BIT, eGRO_011HoldingRegisters_t::MODBUSVERSION, "ModbusVersion ", 1., NONE);                                                    // Modbus Version  Eg：207 is V2.07 Int(16bits)
addHoldingRegister(Protocol, 89, SIZE_16BIT, eGRO_011HoldingRegisters_t::PFMODEL, "PFModel ", 1., NONE);                                                                // Set PF function Model 0: PF=1 1: PF by set 2: default PF line 3: User PF line   4: UnderExcited (Inda) Reactive Power W     5: OverExcited(Capa) Reactive Power 6：Q(v)model
addHoldingRegister(Protocol, 90, SIZE_16BIT, eGRO_011HoldingRegisters_t::GPRS_IP, "GPRS IP", 1., NONE);                                                                 //  Flag read:1;Set GPRS IP Successed Write:2;Read GPRS IP Successed W about GPRS IP SET
addHoldingRegister(Protocol, 91, SIZE_16BIT, eGRO_011HoldingRegisters_t::FREQDERATESTART, "FreqDerateStart", 1., NONE);                                                 //  Frequency derating start point   W  0.01HZ
addHoldingRegister(Protocol, 92, SIZE_16BIT, eGRO_011HoldingRegisters_t::FLRATE_FREQUENCY, "FLrate Frequency ", 1., NONE);                                              // – load limit rate W 0-100 10times
addHoldingRegister(Protocol, 93, SIZE_16BIT, eGRO_011HoldingRegisters_t::V1S_CEI021_V1S_Q_V, "V1S CEI021 V1S Q(v) ", 1., NONE);                                         // W V1S<V2S 0.1V
addHoldingRegister(Protocol, 94, SIZE_16BIT, eGRO_011HoldingRegisters_t::V2S_CEI021_V2S_Q_V, "V2S CEI021 V2S Q(v) ", 1., NONE);                                         // W  0.1V
addHoldingRegister(Protocol, 95, SIZE_16BIT, eGRO_011HoldingRegisters_t::V1L_CEI021_V1L_Q_V, "V1L CEI021 V1L Q(v) ", 1., NONE);                                         // W V1L<V1S 0.1V
addHoldingRegister(Protocol, 96, SIZE_16BIT, eGRO_011HoldingRegisters_t::V2L_CEI021_V2L_Q_V, "V2L CEI021 V2L Q(v) ", 1., NONE);                                         // W V2L<V1L 0.1V
addHoldingRegister(Protocol, 97, SIZE_16BIT, eGRO_011HoldingRegisters_t::QLOCKINPOWER_Q_V, "Qlockinpower Q(v) ", 1., NONE);                                             // lock in active power of CEI021 W 0-100 Percent
addHoldingRegister(Protocol, 98, SIZE_16BIT, eGRO_011HoldingRegisters_t::QLOCKOUTPOWER_Q_V, "QlockOutpower Q(v) ", 1., NONE);                                           // lock Out active power of CEI021 W 0-100 Percent
addHoldingRegister(Protocol, 99, SIZE_16BIT, eGRO_011HoldingRegisters_t::LIGRIDV, "LIGridV", 1., NONE);                                                                 //  Lock in gird volt of CEI021 PF line W nVn 0.1V
addHoldingRegister(Protocol, 100, SIZE_16BIT, eGRO_011HoldingRegisters_t::LOGRIDV, "LOGridV ", 1., NONE);                                                               // Lock out gird volt of CEI021 PF line W nVn 0.1V
addHoldingRegister(Protocol, 101, SIZE_16BIT, eGRO_011HoldingRegisters_t::PFADJ1, "PFAdj1", 1., NONE);                                                                  //  PF adjust value 1  4096 is 1
addHoldingRegister(Protocol, 102, SIZE_16BIT, eGRO_011HoldingRegisters_t::PFADJ2, "PFAdj2", 1., NONE);                                                                  //  PF adjust value 2  4096 is 1
addHoldingRegister(Protocol, 103, SIZE_16BIT, eGRO_011HoldingRegisters_t::PFADJ3, "PFAdj3", 1., NONE);                                                                  //  PF adjust value 3  4096 is 1
addHoldingRegister(Protocol, 104, SIZE_16BIT, eGRO_011HoldingRegisters_t::PFADJ4, "PFAdj4", 1., NONE);                                                                  //  PF adjust value 4  4096 is 1
addHoldingRegister(Protocol, 105, SIZE_16BIT, eGRO_011HoldingRegisters_t::PFADJ5, "PFAdj5 ", 1., NONE);                                                                 // PF adjust value 5  4096 is 1
addHoldingRegister(Protocol, 106, SIZE_16BIT, eGRO_011HoldingRegisters_t::PFADJ6, "PFAdj6", 1., NONE);                                                                  //  PF adjust value 6  4096 is 1
addHoldingRegister(Protocol, 107, SIZE_16BIT, eGRO_011HoldingRegisters_t::QVRPDELAYTIMEEE, "QVRPDelayTimeEE", 1., NONE);                                                //  QV Reactive Power delaytime W 0-30 1S 3S
addHoldingRegister(Protocol, 108, SIZE_16BIT, eGRO_011HoldingRegisters_t::OVERFDERATDELAYTIMEEE, "OverFDeratDelayTimeEE", 1., NONE);                                    //  Overfrequency  deratingdelaytime W 0-20 50ms 0
addHoldingRegister(Protocol, 109, SIZE_16BIT, eGRO_011HoldingRegisters_t::QPERCENTMAX, "QpercentMax", 1., NONE);                                                        //  Qmax for Q(V) curve W 0-1000 0.1%
addHoldingRegister(Protocol, 110, SIZE_16BIT, eGRO_011HoldingRegisters_t::PFLINEP1_LP, "PFLineP1_LP", 1., NONE);                                                        //   PF limit line point 1 load percent W 0-255 percent  255 means no this point 111 PFLineP1_PF  PF limit line point 1 power factor W 0-20000
addHoldingRegister(Protocol, 112, SIZE_16BIT, eGRO_011HoldingRegisters_t::PFLINEP2_LP, "PFLineP2_LP ", 1., NONE);                                                       //  PF limit line point 2 load percent W 0-255 percent  255 means no this point 113 PFLineP2_PF  PF limit line point 2power factor W 0-20000
addHoldingRegister(Protocol, 114, SIZE_16BIT, eGRO_011HoldingRegisters_t::PFLINEP3_LP, "PFLineP3_LP ", 1., NONE);                                                       //  PF limit line point 3 load percent W 0-255 percent  255 means no this point 115 PFLineP3_PF  PF limit line point 3 power factor W 0-20000
addHoldingRegister(Protocol, 116, SIZE_16BIT, eGRO_011HoldingRegisters_t::PFLINEP4_LP, "PFLineP4_LP ", 1., NONE);                                                       //  PF limit line point 4 load percent W 0-255 percent  255 means no this point 117 PFLineP4_PF  PF limit line point 4 power factor W 0-20000
addHoldingRegister(
    Protocol, 118, SIZE_16BIT, eGRO_011HoldingRegisters_t::MODULE_4, "Module 4 ", 1.,
    NONE); // Inverter Module (4)  &*11   SxxBxx 119 Module 3 Inverter Module (3)  &*11   DxxTxx 120 Module 2 Inverter Module (2)  &*11   PxxUxx 121 Module 1 Inverter Module (1)  &*11   Mxxxx    Power 122 uwLocalAntiBackflowEnable Local Anti Backflow Enable R/W 1/0 0：disable Not zero：enable   Local Anti-backflow enable， 0: Disable exportLimit; 1: Enable meter1 exportLimit;(default) 2: Enable
           // meter2   exportLimit; 3: Enable CT exportLimit; 123 wLocalAntiBackflowMeterPowerLimitEE wLocalAntiBackflowMeterPowerLimitEE R/W -1000~+1000 0.1%  Local Anti-backflow power limit percentage 124 TrakerModel  2 Traker Model   W 0,1,2 0:Independent 1:DC Source 2:Parallel   Second group 125 INV Type-1 Inverter type-1 R  ASCII  Reserved 126 INV Type-2 Inverter type-2 R  ASCII
addHoldingRegister(Protocol, 127, SIZE_16BIT, eGRO_011HoldingRegisters_t::INV_TYPE_3, "INV Type-3", 1., NONE);             //  Inverter type-3 R  ASCII
addHoldingRegister(Protocol, 128, SIZE_16BIT, eGRO_011HoldingRegisters_t::INV_TYPE_4, "INV Type-4 ", 1., NONE);            // Inverter type-4 R  ASCII
addHoldingRegister(Protocol, 129, SIZE_16BIT, eGRO_011HoldingRegisters_t::INV_TYPE_5, "INV Type-5 ", 1., NONE);            // Inverter type-5 R  ASCII
addHoldingRegister(Protocol, 130, SIZE_16BIT, eGRO_011HoldingRegisters_t::INV_TYPE_6, "INV Type-6", 1., NONE);             //  Inverter type-06 R  ASCII
addHoldingRegister(Protocol, 131, SIZE_16BIT, eGRO_011HoldingRegisters_t::INV_TYPE_7, "INV Type-7", 1., NONE);             //  Inverter type-7 R  ASCII
addHoldingRegister(Protocol, 132, SIZE_16BIT, eGRO_011HoldingRegisters_t::INV_TYPE_8, "INV Type-8 ", 1., NONE);            // Inverter type-8 R  ASCII
addHoldingRegister(Protocol, 133, SIZE_16BIT, eGRO_011HoldingRegisters_t::BLVERSION1, "BLVersion1", 1., NONE);               //  Boot loader version1 R    Reserved
addHoldingRegister(Protocol, 134, SIZE_16BIT, eGRO_011HoldingRegisters_t::BLVERSION2, "BLVersion2", 1., NONE);               //  Boot loader version2 R    Reserved
addHoldingRegister(Protocol, 135, SIZE_16BIT, eGRO_011HoldingRegisters_t::BLVERSION3, "BLVersion3", 1., NONE);               //  Boot loader version3 R    Reserved
addHoldingRegister(Protocol, 136, SIZE_16BIT, eGRO_011HoldingRegisters_t::BLVERSION4, "BLVersion4", 1., NONE);               //  Boot loader version4 R    Reserved
addHoldingRegister(Protocol, 201, SIZE_16BIT, eGRO_011HoldingRegisters_t::PID, "PID ", 1., NONE);                            //  Working Model PID Working Model W 0:Automatic 1:Continual 2: Overnight
addHoldingRegister(Protocol, 202, SIZE_16BIT, eGRO_011HoldingRegisters_t::PID_ON_Off, "PID On/Off", 1., NONE);             //  Ctrl PID On/Off Control W 0:On 1:Off
addHoldingRegister(Protocol, 203, SIZE_16BIT, eGRO_011HoldingRegisters_t::PID_VOLT, "PID Volt", 1., NONE);                   //  Option PID Output Voltage Option   W 300~1000 V   ......       Reserved
addHoldingRegister(Protocol, 209, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIAL_NO_NEW_15, "Serial NO New. 15 ", 1., NONE); // 15   ASCII
addHoldingRegister(Protocol, 210, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIAL_NO_NEW_14, "Serial NO. New 14 ", 1., NONE); // 14   ASCII
addHoldingRegister(Protocol, 211, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIAL_NO_NEW_13, "Serial NO. New 13 ", 1., NONE); // 13   ASCII
addHoldingRegister(Protocol, 212, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIAL_NO_NEW_12, "Serial NO. New 12 ", 1., NONE); // 12   ASCII
addHoldingRegister(Protocol, 213, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIAL_NO_NEW_11, "Serial NO. New 11 ", 1., NONE); // 11   ASCII
addHoldingRegister(Protocol, 214, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIAL_NO_NEW_10, "Serial NO. New 10 ", 1., NONE); // 10   ASCII
addHoldingRegister(Protocol, 215, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIAL_NO_NEW_9, "Serial NO. New 9", 1., NONE);    //  9   ASCII
addHoldingRegister(Protocol, 216, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIAL_NO_NEW_8, "Serial NO. New 8", 1., NONE);    //  8   ASCII
addHoldingRegister(Protocol, 217, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIAL_NO_NEW_7, "Serial NO. New 7", 1., NONE);    //  7   ASCII
addHoldingRegister(Protocol, 218, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIAL_NO_NEW_6, "Serial NO. New 6", 1., NONE);    //  6   ASCII
addHoldingRegister(Protocol, 219, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIAL_NO_NEW_5, "Serial NO. New 5", 1., NONE);    //  5   ASCII
addHoldingRegister(Protocol, 220, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIAL_NO_NEW_4, "Serial NO. New 4", 1., NONE);    //  4   ASCII
addHoldingRegister(Protocol, 221, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIAL_NO_NEW_3, "Serial NO. New 3", 1., NONE);    //  3   ASCII
addHoldingRegister(Protocol, 222, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIAL_NO_NEW_2, "Serial NO New. 2", 1., NONE);    //  2   ASCII
addHoldingRegister(Protocol, 223, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIAL_NO_NEW_1, "Serial NO New. 1", 1., NONE);    //  1   ASCII
// 230~249 for growatt debug setting
addHoldingRegister(Protocol, 230, SIZE_16BIT, eGRO_011HoldingRegisters_t::ISLANDDISABLE, "IslandDisable", 1., NONE);                                           //  Island Disable or not. 1:disable    0:Enable W 0,1  0
addHoldingRegister(Protocol, 231, SIZE_16BIT, eGRO_011HoldingRegisters_t::FANCHECK, "FanCheck", 1., NONE);                                                     //  Start Fan Check W 1
addHoldingRegister(Protocol, 232, SIZE_16BIT, eGRO_011HoldingRegisters_t::ENABLENLINE, "EnableNLine", 1., NONE);                                               //   Enable N Line of grid W 1  0
addHoldingRegister(Protocol, 233, SIZE_16BIT, eGRO_011HoldingRegisters_t::WCHECKHARDWARE, "wCheckHardware", 1., NONE);                                         //   wCheckHardware Bit0: GFCIBreak; Bit1:SPSDamage Bit8:EepromReadWarning Bit9:EEWriteWarning ......
addHoldingRegister(Protocol, 234, SIZE_16BIT, eGRO_011HoldingRegisters_t::WCHECKHARDWARE2, "wCheckHardware2", 1., NONE);                                       //       reserved
addHoldingRegister(Protocol, 235, SIZE_16BIT, eGRO_011HoldingRegisters_t::UBNTOGNDDETECT, "ubNToGNDDetect", 1., NONE);                                         //  Dis/enable N to GND detect function W 1:enable 0:disable  1
addHoldingRegister(Protocol, 236, SIZE_16BIT, eGRO_011HoldingRegisters_t::NONSTDVACENABLE, "NonStdVacEnable", 1., NONE);                                       //  Enable/Disable  Nonstandard Grid voltage range  W 0-1;  0 0:Disable; 1:Enable;
addHoldingRegister(Protocol, 237, SIZE_16BIT, eGRO_011HoldingRegisters_t::UWENABLESPECSET, "uwEnableSpecSet ", 1., NONE);                                      // Disablse/enable appointed spec setting   W 1:enable 0:disable Binary 0x0000 Bit 0: Hungary
addHoldingRegister(Protocol, 238, SIZE_16BIT, eGRO_011HoldingRegisters_t::FAST_MPPT, "Fast MPPT", 1., NONE);                                                   //  enable About Fast mppt  0,1,2  0 Reserved
addHoldingRegister(Protocol, 240, SIZE_16BIT, eGRO_011HoldingRegisters_t::CHECK_STEP, "Check Step", 1., NONE);                                                 //   W
addHoldingRegister(Protocol, 241, SIZE_16BIT, eGRO_011HoldingRegisters_t::INV_Lng, "INV-Lng ", 1., NONE);                                                    // Inverter Longitude W    Longitude
addHoldingRegister(Protocol, 242, SIZE_16BIT, eGRO_011HoldingRegisters_t::INV_Lat, "INV-Lat", 1., NONE);                                                     //  Inverter Latitude W    Latitude ......       Reserved
addHoldingRegister(Protocol, 250, SIZE_16BIT, eGRO_011HoldingRegisters_t::CURVE_ANALYSIS, "Curve analysis", 1., NONE);                                         //  Enable  a  curve  analysis of a road W 0~1 0
addHoldingRegister(Protocol, 251, SIZE_16BIT, eGRO_011HoldingRegisters_t::FAULTRECORDERWAVE1, "FaultrecorderWave1 ", 1., NONE);                                // Preset Record Waveform Number W 1001~1999 1001
addHoldingRegister(Protocol, 252, SIZE_16BIT, eGRO_011HoldingRegisters_t::FAULTRECORDERWAVE2, "FaultrecorderWave2", 1., NONE);                                 //  Preset Record Waveform Number W 1001~1999 1002
addHoldingRegister(Protocol, 253, SIZE_16BIT, eGRO_011HoldingRegisters_t::FAULTRECORDERWAVE3, "FaultrecorderWave3 ", 1., NONE);                                //  Preset Record W 1001~199 1003
addHoldingRegister(Protocol, 254, SIZE_16BIT, eGRO_011HoldingRegisters_t::FAULTRECORDERWAVE4, "FaultrecorderWave4 ", 1., NONE);                                // Preset Record Waveform Number W 1001~1999 1004
addHoldingRegister(Protocol, 255, SIZE_16BIT, eGRO_011HoldingRegisters_t::FAULTRECORDERWAVE5, "FaultrecorderWave5 ", 1., NONE);                                // Preset Record Waveform Number W 1~999 1
addHoldingRegister(Protocol, 256, SIZE_16BIT, eGRO_011HoldingRegisters_t::FAULTRECORDERWAVE6, "FaultrecorderWave6 ", 1., NONE);                                // Preset Record Waveform Number W 1~999 2
addHoldingRegister(Protocol, 257, SIZE_16BIT, eGRO_011HoldingRegisters_t::FAULTRECORDERWAVE7, "FaultrecorderWave7 ", 1., NONE);                                // Preset Record Waveform Number W 1~999 3
addHoldingRegister(Protocol, 258, SIZE_16BIT, eGRO_011HoldingRegisters_t::FAULTRECORDERWAVE8, "FaultrecorderWave8 ", 1., NONE);                                // Preset Record Waveform Number W 1~999 4
addHoldingRegister(Protocol, 259, SIZE_16BIT, eGRO_011HoldingRegisters_t::FAULTRECORDERENABLE, "FaultRecorderEnable ", 1., NONE);                              // FaultRecorderEnable W 1~100 0
addHoldingRegister(Protocol, 260, SIZE_16BIT, eGRO_011HoldingRegisters_t::RECORDERWAVE1, "recorderWave1 ", 1., NONE);                                          // Preset Record Waveform Number W 1~1999 1
addHoldingRegister(Protocol, 261, SIZE_16BIT, eGRO_011HoldingRegisters_t::RECORDERWAVE2, "recorderWave2 ", 1., NONE);                                          // Preset Record Waveform Number W 1~1999 2
addHoldingRegister(Protocol, 262, SIZE_16BIT, eGRO_011HoldingRegisters_t::RECORDERWAVE3, "recorderWave3", 1., NONE);                                           //  Preset Record Waveform Number W 1~1999 3
addHoldingRegister(Protocol, 263, SIZE_16BIT, eGRO_011HoldingRegisters_t::RECORDERWAVE4, "recorderWave4 ", 1., NONE);                                          // Preset Record Waveform Number W 1~1999 4
addHoldingRegister(Protocol, 264, SIZE_16BIT, eGRO_011HoldingRegisters_t::WAVERECORDERENABLE, "WaveRecorderEnable ", 1., NONE);                                // Real-time waveform recording  W 0~1 0
addHoldingRegister(Protocol, 265, SIZE_16BIT, eGRO_011HoldingRegisters_t::HARMONIC_CHECK, "Harmonic Check ", 1., NONE);                                        // Enable Harmonic Check Enable W 0~1 0
addHoldingRegister(Protocol, 266, SIZE_16BIT, eGRO_011HoldingRegisters_t::IMPEDANCE_ENABLE, "Impedance Enable", 1., NONE);                                     //  Impedance Enable W 0~1 0
addHoldingRegister(Protocol, 299, SIZE_16BIT, eGRO_011HoldingRegisters_t::BACTIVEOVERLOADENABLE, "bActiveOverloadEnable", 1., NONE);                           //  ActiveOverloadEnable
addHoldingRegister(Protocol, 300, SIZE_16BIT, eGRO_011HoldingRegisters_t::BSVGAPFMODE, "bSvgApfMode", 1., NONE);                                               //  SvgApfMode  Low 4bit：0:SVG/APF , 1:APF/SVG ,   2:SVG , 3:APF   High 4bit: 0:one day mode , 1:Night node ,
addHoldingRegister(Protocol, 301, SIZE_16BIT, eGRO_011HoldingRegisters_t::BBDEWLVRTKFACTOR, "bBdewLvrtKFactor ", 1., NONE);                                    // BDEW LVRT KFactor  0-7
addHoldingRegister(Protocol, 302, SIZE_16BIT, eGRO_011HoldingRegisters_t::BBDEWZEROCURRENTMODEEN, "bBdewZeroCurrentModeEn ", 1., NONE);                        // BDEW ZeroCurrentMode Enable  0-1
addHoldingRegister(Protocol, 303, SIZE_16BIT, eGRO_011HoldingRegisters_t::BSVGAPFEQUALRATIO, "bSVGAPFEqualRatio", 1., NONE);                                   //  SVG/APFEqualRatio  0-32
addHoldingRegister(Protocol, 304, SIZE_16BIT, eGRO_011HoldingRegisters_t::UWANTIBACKFLOWFAILPOWERLIMITEE, "uwAntiBackflowFailPowerLimitEE", 1., NONE);         //  Anti-Backflow Failed PowerRate R/W 0-1000 0.1%  Anti-Backflow failure default setting power percentage
addHoldingRegister(Protocol, 305, SIZE_16BIT, eGRO_011HoldingRegisters_t::QLOADSPEED, "Qloadspeed ", 1., NONE);                                                // Q load speed R/W 0-100 1%  Reactive power adjustment speed  setting  item ,  n%Pn/s ,  0 means  that  the  loading  speed is not enabled , that is , directly loaded to the setting value
addHoldingRegister(Protocol, 306, SIZE_16BIT, eGRO_011HoldingRegisters_t::BPARALLELANTIBACKFLOWENABLE, "bParallelAntiBackflowEnable ", 1., NONE);              // Parallel Anti-Backflow enable R/W 0-1   Parallel  Anti-Backflow  enable 1:Enable 0:Disable
addHoldingRegister(Protocol, 307, SIZE_16BIT, eGRO_011HoldingRegisters_t::UWANTIBACKF, "uwAntiBackf", 1., NONE);                                               //  Anti-Backflow R/W 1-5000 1s  Anti-backflow failure response lowFailureResponseTime FailureResponseTime time
addHoldingRegister(Protocol, 308, SIZE_16BIT, eGRO_011HoldingRegisters_t::UWPARALLELANTIBACKFLOWPOWERLIMITEE, "uwParallelAntiBackflowPowerLimitEE", 1., NONE); //  Parallel Anti Backflow Power Limit R/W 0-1000 0.1%  Parallel  Anti  Backflow  Power Limit
addHoldingRegister(Protocol, 309, SIZE_16BIT, eGRO_011HoldingRegisters_t::BISOCHECKCMD, "bISOCheckCmd ", 1., NONE);                                            // ISO Check Cmd R/W 0-1 1  ISO Check Cmd
addHoldingRegister(Protocol, 310, SIZE_16BIT, eGRO_011HoldingRegisters_t::BGRPRSSTATUS, "bGRPRSStatus ", 1., NONE);                                            // GPRS status 1 ：Module does not work 2：No SIM 3：No network 4：TCP is connecting to the server 5 ： TCP connection succeeded R/W 0-255 1  GPRS status Pending part
addHoldingRegister(Protocol, 360, SIZE_16BIT, eGRO_011HoldingRegisters_t::T232T485ENABLE, "t232T485Enable", 1., NONE);                                         //  232T485Enable W 0: Disable; 1: Enable
addHoldingRegister(Protocol, 361, SIZE_32BIT, eGRO_011HoldingRegisters_t::DECREASE_POWER, "Decrease Power", 1., NONE);                                         //  Decrease output watt   W 0.1w
addHoldingRegister(Protocol, 363, SIZE_32BIT, eGRO_011HoldingRegisters_t::INCREASE_POWER, "Increase Power", 1., NONE);                                         //  Increase output watt   W  0.1w
addHoldingRegister(Protocol, 365, SIZE_16BIT, eGRO_011HoldingRegisters_t::FACTORY, "Factory", 1., NONE);                                                       //  The ODM Info code
addHoldingRegister(Protocol, 366, SIZE_16BIT, eGRO_011HoldingRegisters_t::VAC_START_BY_PF, "Vac start by pf", 1., NONE);                                       //  Vac start adjust by pf W  0.1V
addHoldingRegister(Protocol, 367, SIZE_16BIT, eGRO_011HoldingRegisters_t::PF_OF_VAC, "PF of vac", 1., NONE);                                                   //  limit Max pf of adjust Vac W   10000
addHoldingRegister(Protocol, 368, SIZE_16BIT, eGRO_011HoldingRegisters_t::LCMDTEST, "LCMDTest", 1., NONE);                                                     //  Local command test   W 1 to test
addHoldingRegister(Protocol, 369, SIZE_16BIT, eGRO_011HoldingRegisters_t::REACTIVERATE, "ReactiveRate", 1., NONE);                                             //   Reactive Rate in LVFRT W 0-100  2
addHoldingRegister(Protocol, 370, SIZE_16BIT, eGRO_011HoldingRegisters_t::LVFRT_LV1_LVFRT, "LVFRT_LV1 LVFRT", 1., NONE);                                       //  low fault value 1 W  0.1V
addHoldingRegister(Protocol, 371, SIZE_16BIT, eGRO_011HoldingRegisters_t::LVFRT_LT1_LVFRT, "LVFRT_LT1 LVFRT", 1., NONE);                                       //  low fault time 1 W  1ms
addHoldingRegister(Protocol, 372, SIZE_16BIT, eGRO_011HoldingRegisters_t::LVFRT_LV2_LVFRT, "LVFRT_LV2 LVFRT", 1., NONE);                                       //  low fault value 2 W  0.1V
addHoldingRegister(Protocol, 373, SIZE_16BIT, eGRO_011HoldingRegisters_t::LVFRT_LT2_LVFRT, "LVFRT_LT2 LVFRT", 1., NONE);                                       //  low fault time 2 W  1ms
addHoldingRegister(Protocol, 374, SIZE_16BIT, eGRO_011HoldingRegisters_t::LVFRT_LV3_LVFRT, "LVFRT_LV3 LVFRT", 1., NONE);                                       //  low fault value 3 W  0.1V
addHoldingRegister(Protocol, 375, SIZE_16BIT, eGRO_011HoldingRegisters_t::LVFRT_LT3_LVFRT, "LVFRT_LT3 LVFRT", 1., NONE);                                       //  low fault time 3 W  1ms
addHoldingRegister(Protocol, 376, SIZE_16BIT, eGRO_011HoldingRegisters_t::LVFRT_LV4_LVFRT, "LVFRT_LV4 LVFRT", 1., NONE);                                       //  low fault value 4 W  0.1V
addHoldingRegister(Protocol, 377, SIZE_16BIT, eGRO_011HoldingRegisters_t::LVFRT_LT4_LVFRT, "LVFRT_LT4 LVFRT", 1., NONE);                                       //  low fault time 4 W  1ms
addHoldingRegister(Protocol, 378, SIZE_16BIT, eGRO_011HoldingRegisters_t::LVFRT_HV1_LVFRT, "LVFRT_HV1 LVFRT", 1., NONE);                                       //  high fault value 1 W  0.1V
addHoldingRegister(Protocol, 379, SIZE_16BIT, eGRO_011HoldingRegisters_t::LVFRT_HT1_LVFRT, "LVFRT_HT1 LVFRT", 1., NONE);                                       //  high fault time 1 W  1ms
addHoldingRegister(Protocol, 380, SIZE_16BIT, eGRO_011HoldingRegisters_t::WLOADDERATESTARTVOLT, "wLoadDerateStartVolt", 1., NONE);                             //  Load derate start ac voltage  1.05Vn~1.2Vn 0.1V
addHoldingRegister(Protocol, 381, SIZE_16BIT, eGRO_011HoldingRegisters_t::SPECPASSWORDTYPE, "SpecPasswordType", 1_, _NONE);
                                                                                                                                                      //__Unlock_or_set_Specpassword_W_0:unlock  ,auto lock in 5 minute; 1:change pw (should unlock first)， 2：lock , &*7  2
addHoldingRegister(Protocol, 382, SIZE_16BIT, eGRO_011HoldingRegisters_t::SPECPASSWORD3, "SpecPassword3", 1., NONE);                               //  SpecPassword3 W For the spec setting change ASCII XX
addHoldingRegister(Protocol, 383, SIZE_16BIT, eGRO_011HoldingRegisters_t::SPECPASSWORD2, "SpecPassword2", 1., NONE);                                   //  SpecPassword2 W .. ASCII XX
addHoldingRegister(Protocol, 384, SIZE_16BIT, eGRO_011HoldingRegisters_t::SPECPASSWORD1, "SpecPassword1", 1., NONE);                                   //  SpecPassword1 W .. ASCII XX
addHoldingRegister(Protocol, 385, SIZE_16BIT, eGRO_011HoldingRegisters_t::DCISHIFT, "DCIshift ", 1., NONE);                                            // DCI offset  Center is 30000   Reserved
addHoldingRegister(Protocol, 386, SIZE_16BIT, eGRO_011HoldingRegisters_t::DCIADJ, "DCIAdj ", 1., NONE);                                                // DCI adjust  Center is 2000   Reserved
addHoldingRegister(Protocol, 387, SIZE_16BIT, eGRO_011HoldingRegisters_t::INIEEPROM, "IniEEPROM", 1., NONE);                                           //  IniEEPROM W 0xFF   Reserved
addHoldingRegister(Protocol, 388, SIZE_16BIT, eGRO_011HoldingRegisters_t::BALANCE_1, "Balance 1", 1., NONE);                                           //  Phaseflag|ErrorCode W    Reserved
addHoldingRegister(Protocol, 389, SIZE_16BIT, eGRO_011HoldingRegisters_t::BALANCE_2, "Balance 2", 1., NONE);                                           //  Power H W    Reserved
addHoldingRegister(Protocol, 390, SIZE_16BIT, eGRO_011HoldingRegisters_t::BALANCE_3, "Balance 3", 1., NONE);                                           //  Power L W    Reserved
addHoldingRegister(Protocol, 391, SIZE_16BIT, eGRO_011HoldingRegisters_t::BHIGHACVDERATESLOPE, "bHighACVDerateSlope ", 1., NONE);                      // High ac voltage load derating slope W 20 0-100
addHoldingRegister(Protocol, 392, SIZE_16BIT, eGRO_011HoldingRegisters_t::BLANECEMODEL, "BlaneceModel ", 1., NONE);                                    // BlaneceModel W 1-3
addHoldingRegister(Protocol, 393, SIZE_16BIT, eGRO_011HoldingRegisters_t::BALENCEPHASE, "BalencePhase ", 1., NONE);                                    // BalencePhase W 1-3
addHoldingRegister(Protocol, 394, SIZE_16BIT, eGRO_011HoldingRegisters_t::DCISHIFT2, "DCIshift2 ", 1., NONE);                                          // DCI offset 2 W Center is 30000   Reserved
addHoldingRegister(Protocol, 395, SIZE_16BIT, eGRO_011HoldingRegisters_t::DCISHIFT3, "DCIshift3 ", 1., NONE);                                          // DCI offset 3 W Center is 30000   Reserved
addHoldingRegister(Protocol, 396, SIZE_16BIT, eGRO_011HoldingRegisters_t::ENERGYLIMITENABLE, "EnergyLimitEnable ", 1., NONE);                          // Output Energy  Limit Enable R 1 is enable   Reserved
addHoldingRegister(Protocol, 397, SIZE_16BIT, eGRO_011HoldingRegisters_t::ENERGYREMAIN, "EnergyRemain ", 1., NONE);                                    // H Output Energy  Limit value High W 0.1kWh   Reserved
addHoldingRegister(Protocol, 398, SIZE_16BIT, eGRO_011HoldingRegisters_t::ENERGYREMAIN, "EnergyRemain ", 1., NONE);                                    // L Output Energy  Limit value low W 0.1kWh   Reserved
addHoldingRegister(Protocol, 399, SIZE_16BIT, eGRO_011HoldingRegisters_t::TRAKERMODEL, "TrakerModel ", 1., NONE);                                      //  2 Traker Model   PV model check W 0,1,2   SPH
addHoldingRegister(Protocol, 400, SIZE_16BIT, eGRO_011HoldingRegisters_t::PMCHECK, "PMcheck ", 1., NONE);                                              // Growatt Resaved W    Reserved
addHoldingRegister(Protocol, 401, SIZE_16BIT, eGRO_011HoldingRegisters_t::INVWORKMODE, "INVWorkMode ", 1., NONE);                                      // INV work mode set W 0:default 1:CV Mode 2:CC Mode 3:CP Mode  0
addHoldingRegister(Protocol, 402, SIZE_16BIT, eGRO_011HoldingRegisters_t::PV1VOLTSET, "PV1VoltSet ", 1., NONE);                                        // pv1 voltage set when CV Mode was chosed W StartPVVolt-HighPVVolt
addHoldingRegister(Protocol, 403, SIZE_16BIT, eGRO_011HoldingRegisters_t::PV2VOLTSET, "PV2VoltSet ", 1., NONE);                                        // Pv2 voltage set when CV Mode was chosed W StartPVVolt-HighPVVolt
addHoldingRegister(Protocol, 404, SIZE_16BIT, eGRO_011HoldingRegisters_t::BT1CURRREFSET, "BT1CurrRefSet ", 1., NONE);                                  // BT1 current set when CC Mode was chosed W 0-MaxBTCurrent
addHoldingRegister(Protocol, 405, SIZE_16BIT, eGRO_011HoldingRegisters_t::BT2CURRREFSET, "BT2CurrRefSet ", 1., NONE);                                  // BT2current set when CC Mode was chosed W 0-MaxBTCurrent
addHoldingRegister(Protocol, 406, SIZE_16BIT, eGRO_011HoldingRegisters_t::WATTACVRECOVERDELAYTIME, "WattACVRecoverDelayTime ", 1., NONE);              // Delay time for power recovering when ac voltage getting normal W 3-90S
addHoldingRegister(Protocol, 407, SIZE_16BIT, eGRO_011HoldingRegisters_t::TXDATAINTERVAL, "TxDataInterval ", 1., NONE);                                // TxDataInterval W  1~600 0.1 mins 50 5mins
addHoldingRegister(Protocol, 408, SIZE_16BIT, eGRO_011HoldingRegisters_t::CHKCODE_NO_1, "ChkCode NO.1 ", 1., NONE);                                    // Datalogger Check Code 1 R  ASCII
addHoldingRegister(Protocol, 409, SIZE_16BIT, eGRO_011HoldingRegisters_t::CHKCODE_NO_2, "ChkCode NO.2 ", 1., NONE);                                    // Datalogger Check Code 2 R  ASCII
addHoldingRegister(Protocol, 500, SIZE_16BIT, eGRO_011HoldingRegisters_t::CHKCODE_NO_3, "ChkCode NO.3 ", 1., NONE);                                    // Datalogger Check Code 3 R  ASCII
addHoldingRegister(Protocol, 501, SIZE_16BIT, eGRO_011HoldingRegisters_t::BISLDSHIFTDELTAEE, "bISLDShiftDeltaEE ", 1., NONE);                          // Growatt Resaved W    Reserved
addHoldingRegister(Protocol, 502, SIZE_16BIT, eGRO_011HoldingRegisters_t::BLOWPOINTER, "bLowPointer ", 1., NONE);                                      //  Growatt Resaved W    Reserved
addHoldingRegister(Protocol, 505, SIZE_16BIT, eGRO_011HoldingRegisters_t::GPRSIP_ADDR_GPRSIP_ADDR_NO_1, "GPRSIP Addr  GPRSIP Addr No.1 ", 1., NONE);   // W 0~65536 ASCII
addHoldingRegister(Protocol, 506, SIZE_16BIT, eGRO_011HoldingRegisters_t::GPRSIP_ADDR_GPRSIP_ADDR_NO_2, "GPRSIP Addr  GPRSIP Addr No.2 ", 1., NONE);   // W 0~65536 ASCII
addHoldingRegister(Protocol, 507, SIZE_16BIT, eGRO_011HoldingRegisters_t::GPRSIP_ADDR_GPRSIP_ADDR_NO_3, "GPRSIP Addr  GPRSIP Addr No.3 ", 1., NONE);   // W 0~65536 ASCII
addHoldingRegister(Protocol, 508, SIZE_16BIT, eGRO_011HoldingRegisters_t::GPRSIP_ADDR_GPRSIP_ADDR_NO_4, "GPRSIP Addr  GPRSIP Addr No.4 ", 1., NONE);   // W 0~65536 ASCII
addHoldingRegister(Protocol, 509, SIZE_16BIT, eGRO_011HoldingRegisters_t::GPRSIP_ADDR_GPRSIP_ADDR_NO_5, "GPRSIP Addr  GPRSIP Addr No.5 ", 1., NONE);   // W 0~65536 ASCII
addHoldingRegister(Protocol, 510, SIZE_16BIT, eGRO_011HoldingRegisters_t::GPRSIP_ADDR_GPRSIP_ADDR_NO_6, "GPRSIP Addr  GPRSIP Addr No.6 ", 1., NONE);   // W 0~65536 ASCII
addHoldingRegister(Protocol, 511, SIZE_16BIT, eGRO_011HoldingRegisters_t::GPRSIP_ADDR_GPRSIP_ADDR_NO_7, "GPRSIP Addr  GPRSIP Addr No.7 ", 1., NONE);   // W 0~65536 ASCII
addHoldingRegister(Protocol, 512, SIZE_16BIT, eGRO_011HoldingRegisters_t::GPRSIP_ADDR_GPRSIP_ADDR_NO_8, "GPRSIP Addr  GPRSIP Addr No.8 ", 1., NONE);   // W 0~65536 ASCII
addHoldingRegister(Protocol, 513, SIZE_16BIT, eGRO_011HoldingRegisters_t::GPRSIP_ADDR_GPRSIP_ADDR_NO_9, "GPRSIP Addr  GPRSIP Addr No.9 ", 1., NONE);   // W 0~65536 ASCII
addHoldingRegister(Protocol, 514, SIZE_16BIT, eGRO_011HoldingRegisters_t::GPRSIP_ADDR_GPRSIP_ADDR_NO_10, "GPRSIP Addr  GPRSIP Addr No.10 ", 1., NONE); // W 0~65536 ASCII
addHoldingRegister(Protocol, 515, SIZE_16BIT, eGRO_011HoldingRegisters_t::GPRSIP_ADDR_GPRSIP_ADDR_NO_11, "GPRSIP Addr  GPRSIP Addr No.11 ", 1., NONE); // W 0~65536 ASCII
addHoldingRegister(Protocol, 516, SIZE_16BIT, eGRO_011HoldingRegisters_t::GPRSIP_ADDR_GPRSIP_ADDR_NO_12, "GPRSIP Addr  GPRSIP Addr No.12 ", 1., NONE); // W 0~65536 ASCII
addHoldingRegister(Protocol, 517, SIZE_16BIT, eGRO_011HoldingRegisters_t::GPRSIP_ADDR_GPRSIP_ADDR_NO_13, "GPRSIP Addr  GPRSIP Addr No.13 ", 1., NONE); // W 0~65536 ASCII
addHoldingRegister(Protocol, 518, SIZE_16BIT, eGRO_011HoldingRegisters_t::GPRSIP_ADDR_GPRSIP_ADDR_NO_14, "GPRSIP Addr  GPRSIP Addr No.14 ", 1., NONE); // W 0~65536 ASCII
addHoldingRegister(Protocol, 519, SIZE_16BIT, eGRO_011HoldingRegisters_t::GPRSIP_ADDR_GPRSIP_ADDR_NO_15, "GPRSIP Addr  GPRSIP Addr No.15 ", 1., NONE); // W 0~65536 ASCII
addHoldingRegister(Protocol, 520, SIZE_16BIT, eGRO_011HoldingRegisters_t::GPRSIP_ADDR_GPRSIP_ADDR_NO_16, "GPRSIP Addr  GPRSIP Addr No.16 ", 1., NONE); // W 0~65536 ASCII
addHoldingRegister(Protocol, 521, SIZE_16BIT, eGRO_011HoldingRegisters_t::GPRSIP_ADDR_GPRSIP_ADDR_NO_17, "GPRSIP Addr  GPRSIP Addr No.17 ", 1., NONE); // W 0~65536 ASCII
addHoldingRegister(Protocol, 522, SIZE_16BIT, eGRO_011HoldingRegisters_t::GPRSIP_ADDR_GPRSIP_ADDR_NO_18, "GPRSIP Addr  GPRSIP Addr No.18 ", 1., NONE); // W 0~65536 ASCII
addHoldingRegister(Protocol, 523, SIZE_16BIT, eGRO_011HoldingRegisters_t::GPRSIP_ADDR_GPRSIP_ADDR_NO_19, "GPRSIP Addr  GPRSIP Addr No.19 ", 1., NONE); // W 0~65536 ASCII
addHoldingRegister(Protocol, 524, SIZE_16BIT, eGRO_011HoldingRegisters_t::GPRSIP_ADDR_GPRSIP_ADDR_NO_20, "GPRSIP Addr  GPRSIP Addr No.20 ", 1., NONE); // W 0~65536 ASCII
addHoldingRegister(Protocol, 525, SIZE_16BIT, eGRO_011HoldingRegisters_t::GPRSIP_ADDR_GPRSIP_ADDR_NO_21, "GPRSIP Addr  GPRSIP Addr No.21 ", 1., NONE); // W 0~65536 ASCII
addHoldingRegister(Protocol, 526, SIZE_16BIT, eGRO_011HoldingRegisters_t::GPRSIP_ADDR_GPRSIP_ADDR_NO_22, "GPRSIP Addr  GPRSIP Addr No.22 ", 1., NONE); // W 0~65536 ASCII
addHoldingRegister(Protocol, 527, SIZE_16BIT, eGRO_011HoldingRegisters_t::GPRSIP_ADDR_GPRSIP_ADDR_NO_23, "GPRSIP Addr  GPRSIP Addr No.23 ", 1., NONE); // W 0~65536 ASCII
addHoldingRegister(Protocol, 528, SIZE_16BIT, eGRO_011HoldingRegisters_t::GPRSIP_ADDR_GPRSIP_ADDR_NO_24, "GPRSIP Addr  GPRSIP Addr No.24 ", 1., NONE); // W 0~65536 ASCII
addHoldingRegister(Protocol, 529, SIZE_16BIT, eGRO_011HoldingRegisters_t::GPRSIP_ADDR_GPRSIP_ADDR_NO_25, "GPRSIP Addr  GPRSIP Addr No.25 ", 1., NONE); // W 0~65536 ASCII
addHoldingRegister(Protocol, 1000, SIZE_16BIT, eGRO_011HoldingRegisters_t::FLOAT, "Float ", 1., NONE);                                                 // charge current limit When charge current battery need is lower than this value, enter into float charge W  0.1A  600 CC current
addHoldingRegister(Protocol, 1001, SIZE_16BIT, eGRO_011HoldingRegisters_t::PF, "PF ", 1., NONE);                                                       // CMD memory state Set  the  following  19-22 CMD will be memory ornot(1/0),  if  not,  these settings      are the initial value. W 0or1,  0 Means  these  settings    will  be acting  or not when next power on(02 repeat)
addHoldingRegister(Protocol, 1002, SIZE_16BIT, eGRO_011HoldingRegisters_t::VBATSTARTFORDISCHARGE, "VbatStartForDischarge ", 1., NONE);                 // LV Vbat  R/W  0.1V  Lead-acid battery LV voltage
addHoldingRegister(Protocol, 1003, SIZE_16BIT, eGRO_011HoldingRegisters_t::VBATLOWWARNCLR, "VbatlowWarnClr ", 1., NONE);                               // LoadPercent(only lead-Acid): W  0.1V  Clear battery low voltage error voltage point 45.5V <20% 48.0V 20%~50% 49.0V >50
addHoldingRegister(Protocol, 1004, SIZE_16BIT, eGRO_011HoldingRegisters_t::VBATSTOPFORDISCHARGE, "Vbatstopfordischarge ", 1., NONE);                   // Should stop discharge when lower than this voltage(only lead-Acid): 46.0V <20% 44.8V 20%~50% 44.2V >50% W  0.01V
addHoldingRegister(Protocol, 1005, SIZE_16BIT, eGRO_011HoldingRegisters_t::VBAT_STOP, "Vbat stop", 1., NONE);                                          // for charge Should stop charge when higher than this voltage W  0.01V 5800
addHoldingRegister(Protocol, 1006, SIZE_16BIT, eGRO_011HoldingRegisters_t::VBAT_START, "Vbat start", 1., NONE);                                        // for discharge Should not discharge when lower than this voltage W  0.01V 4800
addHoldingRegister(Protocol, 1007, SIZE_16BIT, eGRO_011HoldingRegisters_t::VBAT_CONSTANT, "Vbat constant", 1., NONE);                                  // charge can charge when lower than this voltage W  0.01V 5800 CV voltage（acid）
addHoldingRegister(Protocol, 1008, SIZE_16BIT, eGRO_011HoldingRegisters_t::EESYSINFO, "EESysInfo ", 1., NONE); //.SysSetEn Bit0：Resved;                           Bit1：Resved;                               Bit2：Resved;                             Bit3：Resved;  Bit4：Resved; Bit5：bDischargeEn； Bit6：ForceDischrEn； Bit7：ChargeEn； Bit8：bForceChrEn； Bit9：bBackUpEn； Bit10：bInvLimitLoadE；
                                                                                                               //Bit11：bSpLimitLoadEn； Bit12：bACChargeEn； Bit13：bPVLoadLimitEn; Bit14,15:UnUsed; W    System Enable
addHoldingRegister(Protocol, 1009, SIZE_16BIT, eGRO_011HoldingRegisters_t::BATTEMP, "Battemp ", 1., NONE);                                         // lower limit d Battery temperature lower limit for discharge W 0-200:0-20°C 1000-1400.1°C 1170  0：-40-0°C
addHoldingRegister(Protocol, 1010, SIZE_16BIT, eGRO_011HoldingRegisters_t::BAT_TEMP_UPPER, "Bat temp upper", 1., NONE);                            //  limit d Battery temperature upper limit for discharge W 200-1000 0.1°C 420
addHoldingRegister(Protocol, 1011, SIZE_16BIT, eGRO_011HoldingRegisters_t::BAT_TEMP_LOWER, "Bat temp lower", 1., NONE);                            // limit c Battery temperature lower limit for charge W 0-200:0-20°C 1000-1400：-40-0°C 0.1°C 30 Lower temperature limit
addHoldingRegister(Protocol, 1012, SIZE_16BIT, eGRO_011HoldingRegisters_t::BAT_TEMP_UPPER, "Bat temp upper", 1., NONE);                            //  limit c Battery temperature upper limit for charge W 200-1000 0.1°C 370 Upper temperature limit
addHoldingRegister(Protocol, 1013, SIZE_16BIT, eGRO_011HoldingRegisters_t::UWUNDERFREDISCHARGEDELYTIME, "uwUnderFreDischargeDelyTime ", 1., NONE); // Under Fre Delay Time   s 0-20 50ms  Under Fre Delay Time
addHoldingRegister(Protocol, 1014, SIZE_16BIT, eGRO_011HoldingRegisters_t::BATMDLSERIALNUM, "BatMdlSerialNum ", 1., NONE);                         // Battery serial number W 00:00   SPH4-11K used
addHoldingRegister(Protocol, 1015, SIZE_16BIT, eGRO_011HoldingRegisters_t::BATMDLPARALLNUM, "BatMdlParallNum ", 1., NONE);                         // Battery parallel section W 00:00   SPH4-11K used
addHoldingRegister(Protocol, 1037, SIZE_16BIT, eGRO_011HoldingRegisters_t::BCTMODE, " bCTMode ", 1., NONE);                                        // Use the CTMode to   Choose RFCT \ Cable CT\METER  W 2:METER 1:cWirelessCT 0:cWiredCT  0
addHoldingRegister(Protocol, 1038, SIZE_16BIT, eGRO_011HoldingRegisters_t::CTADJUST, "CTAdjust ", 1., NONE);                                       // CTAdjust enable   W 0:disable   1:enable  0
addHoldingRegister(Protocol, 1044, SIZE_16BIT, eGRO_011HoldingRegisters_t::PRIORITY, "Priority ", 1., NONE);                                       // ForceChrEn/ForceDischrEn Load  first/bat  first  /grid first R 0.Load(default)/1.Battery/2.Grid   bForceChrEn/disbForceDischrEn/dis
addHoldingRegister(Protocol, 1047, SIZE_16BIT, eGRO_011HoldingRegisters_t::AGINGTESTSTEP, "AgingTestStep ", 1., NONE);                             // Cmd Command for aging test  0: default 1: charge 2: discharge   Cmd for aging test
addHoldingRegister(Protocol, 1048, SIZE_16BIT, eGRO_011HoldingRegisters_t::BATTERYTYPE, "BatteryType ", 1., NONE);                                 // Battery type choose of buck-boost input  0:Lithium 1:Lead-acid 2:other  0 Battery type
addHoldingRegister(Protocol, 1060, SIZE_16BIT, eGRO_011HoldingRegisters_t::BUCKUPSFUNEN, "BuckUpsFunEn ", 1., NONE);                               // Ups function enable or disable  0:disable   1:enable
addHoldingRegister(Protocol, 1061, SIZE_16BIT, eGRO_011HoldingRegisters_t::BUCKUPSVOLTSET, "BuckUPSVoltSet ", 1., NONE);                           // UPS output voltage  0:230 1:208 2:240  230V  1062.  UPSFreqSet UPS output frequency  0:50Hz 1:60Hz  50Hz  ... / / / / / / reverse Priority set
addHoldingRegister(Protocol, 1070, SIZE_16BIT, eGRO_011HoldingRegisters_t::GRIDFIRSTDISCHARGEPOWERRATE, "GridFirstDischargePowerRate ", 1., NONE); // Discharge Power Rate when Grid First   W 0-100 1% Discharge Power Rate when Grid First
addHoldingRegister(Protocol, 1071, SIZE_16BIT, eGRO_011HoldingRegisters_t::GRIDFIRSTSTOPSOC, "GridFirstStopSOC ", 1., NONE);                       // Stop Discharge soc when Grid First W 0-100 1% Stop Discharge soc when Grid First
addHoldingRegister(Protocol, 1080, SIZE_16BIT, eGRO_011HoldingRegisters_t::GRID_FIRST_START_TIME_1, "Grid First Start Time 1", 1., NONE);          // High eight bit：hour Low eight bit：minute  0-23 0-59
addHoldingRegister(Protocol, 1081, SIZE_16BIT, eGRO_011HoldingRegisters_t::GRID_FIRST_STOP_TIME_1, "Grid First Stop Time 1", 1., NONE);            // High eight bit：hour Low eight bit：minute  0-23 0-59
addHoldingRegister(Protocol, 1082, SIZE_16BIT, eGRO_011HoldingRegisters_t::GRID_FIRST_STOP_SWITCH_1, "Grid First Stop Switch 1", 1., NONE);        // Enable :1 Disable:0  0 or 1  Grid First enable
addHoldingRegister(Protocol, 1083, SIZE_16BIT, eGRO_011HoldingRegisters_t::GRID_FIRST_START_TIME_2, "Grid First Start Time 2", 1., NONE);          // High eight bit：hour Low eight bit：minute  0-23 0-59
addHoldingRegister(Protocol, 1084, SIZE_16BIT, eGRO_011HoldingRegisters_t::GRID_FIRST_STOP_TIME_2, "Grid First Stop Time 2", 1., NONE);            // High eight bit：hour Low eight bit：minute  0-23 0-59
addHoldingRegister(Protocol, 1085, SIZE_16BIT, eGRO_011HoldingRegisters_t::GRID_FIRST_STOP_SWITCH_2, "Grid First Stop Switch 2", 1., NONE);        // ForceDischarge.bSwitch&LCD_SET_FORCE_TRUE_2)==LCD_SET_FORCE_TRUE_2  0 or 1  Grid First enable ForceDischarge; LCD_SET_FORCE_TRUE_2 1086.  Grid First Start Time 3 High eight bit：hour Low eight bit：minute  0-23 0-59
addHoldingRegister(Protocol, 1087, SIZE_16BIT, eGRO_011HoldingRegisters_t::GRID_FIRST_STOP_TIME_3, "Grid First Stop Time 3", 1., NONE);            // High eight bit：hour Low eight bit：minute  0-23 0-59
addHoldingRegister(Protocol, 1088, SIZE_16BIT, eGRO_011HoldingRegisters_t::GRID_FIRST_STOP_SWITCH_3, "Grid First Stop Switch 3", 1., NONE);        // Enable :1 Disable:0  0 or 1  Grid First enable  1089.  / / / / / / reserve
addHoldingRegister(Protocol, 1090, SIZE_16BIT, eGRO_011HoldingRegisters_t::BATFIRSTPOWERRATE, "BatFirstPowerRate ", 1., NONE);                     // Charge Power Rate when Bat First   W 0-100 1% Charge Power Rate when Bat First
addHoldingRegister(Protocol, 1091, SIZE_16BIT, eGRO_011HoldingRegisters_t::WBATFIRST, "wBatFirst ", 1., NONE);                                     // stop SOC Stop  Charge  soc  when  Bat First W 0-100 1% Stop Charge soc when Bat First
addHoldingRegister(Protocol, 1092, SIZE_16BIT, eGRO_011HoldingRegisters_t::AC, "AC ", 1., NONE);                                                   // charge Switch When Bat First   Enable:1 Disable:0  Enable:1 Disable:0  AC
addHoldingRegister(Protocol, 1100, SIZE_16BIT, eGRO_011HoldingRegisters_t::BAT_FIRST_START_TIME_1, "Bat First Start Time 1", 1., NONE);            // High eight bit：hour Low eight bit：minute  0-23 0-59
addHoldingRegister(Protocol, 1101, SIZE_16BIT, eGRO_011HoldingRegisters_t::BAT_FIRST_STOP_TIME_1, "Bat First Stop Time 1", 1., NONE);              // High eight bit：hour Low eight bit：minute  0-23 0-59
addHoldingRegister(Protocol, 1102, SIZE_16BIT, eGRO_011HoldingRegisters_t::BATFIRST, "BatFirst ", 1., NONE);                                       // on/off Switch 1 Enable :1 Disable:0  0 or 1  Bat First Enable1
addHoldingRegister(Protocol, 1103, SIZE_16BIT, eGRO_011HoldingRegisters_t::BAT_FIRST_START_TIME_2, "Bat First Start Time 2", 1., NONE);            // High eight bit：hour Low eight bit：minute  0-23 0-59
addHoldingRegister(Protocol, 1104, SIZE_16BIT, eGRO_011HoldingRegisters_t::BAT_FIRST_STOP_TIME_2, "Bat First Stop Time 2", 1., NONE);              // High eight bit：hour Low eight bit：minute  0-23 0-59
addHoldingRegister(Protocol, 1105, SIZE_16BIT, eGRO_011HoldingRegisters_t::BATFIRSTON, "BatFirston ", 1., NONE);                                   /// off Switch 2 Enable :1 Disable:0  0 or 1  Bat First Enable2
addHoldingRegister(Protocol, 1106, SIZE_16BIT, eGRO_011HoldingRegisters_t::BAT_FIRST_START_TIME_3, "Bat First Start Time 3", 1., NONE);            // High eight bit：hour Low eight bit：minute  0-23 0-59
addHoldingRegister(Protocol, 1107, SIZE_16BIT, eGRO_011HoldingRegisters_t::BAT_FIRST_STOP_TIME_3, "Bat First Stop Time 3", 1., NONE);              // High eight bit：hour Low eight bit：minute  0-23 0-59
addHoldingRegister(Protocol, 1108, SIZE_16BIT, eGRO_011HoldingRegisters_t::BATFIRSTON, "BatFirston ", 1., NONE);                                   /// off Switch 3 Enable :1 Disable:0  0 or 1  Bat First Enable3
addHoldingRegister(Protocol, 1110, SIZE_16BIT, eGRO_011HoldingRegisters_t::LOAD_FIRST_START_TIME_1, "Load First Start Time 1", 1., NONE);          // High eight bit：hour Low eight bit：minute  0-23 0-59   SPA/ reserve
addHoldingRegister(Protocol, 1111, SIZE_16BIT, eGRO_011HoldingRegisters_t::LOAD_FIRST_STOP_TIME_1, "Load First Stop Time 1", 1., NONE);            // High eight bit：hour Low eight bit：minute  0-23 0-59   SPA/ reserve
addHoldingRegister(Protocol, 1112, SIZE_16BIT, eGRO_011HoldingRegisters_t::LOAD First_Switch_1, "Load First   Switch 1 ", 1., NONE);               // Enable :1 Disable:0  0 or 1  Load First Enable SPA/ reserve
addHoldingRegister(Protocol, 1113, SIZE_16BIT, eGRO_011HoldingRegisters_t::LOAD_FIRST_START_TIME_2, "Load First Start Time 2", 1., NONE);          // High eight bit：hour Low eight bit：minute  0-23 0-59   SPA/ reserve
addHoldingRegister(Protocol, 1114, SIZE_16BIT, eGRO_011HoldingRegisters_t::LOAD_FIRST_STOP_TIME_2, "Load First Stop Time 2", 1., NONE);            // High eight bit：hour Low eight bit：minute  0-23 0-59   SPA/ reserve
addHoldingRegister(Protocol, 1115, SIZE_16BIT, eGRO_011HoldingRegisters_t::LOAD First_Switch_2, "Load First   Switch 2 ", 1., NONE);               // Enable :1 Disable:0  0 or 1  Load First Enable SPA/ reserve
addHoldingRegister(Protocol, 1116, SIZE_16BIT, eGRO_011HoldingRegisters_t::LOAD_FIRST_START_TIME_3, "Load First Start Time 3", 1., NONE);          // High eight bit：hour Low eight bit：minute  0-23 0-59   SPA/ reserve
addHoldingRegister(Protocol, 1117, SIZE_16BIT, eGRO_011HoldingRegisters_t::LOAD_FIRST_STOP_TIME_3, "Load First Stop Time 3", 1., NONE);            // High eight bit：hour Low eight bit：minute  0-23 0-59   SPA/ reserve
addHoldingRegister(Protocol, 1118, SIZE_16BIT, eGRO_011HoldingRegisters_t::LOAD First_Switch_3, "Load First   Switch 3 ", 1., NONE);               // Enable :1 Disable:0  0 or 1  Load First Enable SPA/ reserve
// Use for TL-X and TL-XH
addHoldingRegister(Protocol, 3000, SIZE_16BIT, eGRO_011HoldingRegisters_t::EXPORTLIMITFAILEDPOWERRATE, "ExportLimitFailedPowerRate ", 1., NONE);   // The power rate when exportLimit failed   R/W  0.1%    The power rate when exportLimit failed
addHoldingRegister(Protocol, 3001, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIAL_NO_NEW_15, "Serial NO New. 15", 1., NONE);                       // Serial number New 15 R/W  ASCII
addHoldingRegister(Protocol, 3002, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIAL_NO_NEW_14, "Serial NO New. 14", 1., NONE);                       // Serial number New 14 R/W  ASCII
addHoldingRegister(Protocol, 3003, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIAL_NO_NEW_13, "Serial NO New. 13", 1., NONE);                       // Serial number New 13 R/W  ASCII
addHoldingRegister(Protocol, 3004, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIAL_NO_NEW_12, "Serial NO New. 12", 1., NONE);                       // Serial number New 12 R/W  ASCII
addHoldingRegister(Protocol, 3005, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIAL_NO_NEW_11, "Serial NO New. 11", 1., NONE);                       // Serial number New 11 R/W  ASCII
addHoldingRegister(Protocol, 3006, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIAL_NO_NEW_10, "Serial NO New. 10", 1., NONE);                       // Serial number New 10 R/W  ASCII
addHoldingRegister(Protocol, 3007, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIAL_NO_NEW_9, "Serial NO New. 9", 1., NONE);                         // Serial number New 9 R/W  ASCII
addHoldingRegister(Protocol, 3008, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIAL_NO_NEW_8, "Serial NO New. 8", 1., NONE);                         // Serial number New 8 R/W  ASCII
addHoldingRegister(Protocol, 3009, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIAL_NO_NEW_7, "Serial NO New. 7", 1., NONE);                         // Serial number New 7 R/W  ASCII
addHoldingRegister(Protocol, 3010, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIAL_NO_NEW_6, "Serial NO New. 6", 1., NONE);                         // Serial number New 6 R/W  ASCII
addHoldingRegister(Protocol, 3011, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIAL_NO_NEW_5, "Serial NO New. 5", 1., NONE);                         // Serial number New 5 R/W  ASCII
addHoldingRegister(Protocol, 3012, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIAL_NO_NEW_4, "Serial NO New. 4", 1., NONE);                         // Serial number New 4 R/W  ASCII
addHoldingRegister(Protocol, 3013, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIAL_NO_NEW_3, "Serial NO New. 3", 1., NONE);                         // Serial number New 3 R/W  ASCII
addHoldingRegister(Protocol, 3014, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIAL_NO_NEW_2, "Serial NO New. 2", 1., NONE);                         // Serial number New 2 R/W  ASCII
addHoldingRegister(Protocol, 3015, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIAL_NO_NEW_1, "Serial NO New. 1", 1., NONE);                         // Serial number New 1 R/W  ASCII
addHoldingRegister(Protocol, 3016, SIZE_16BIT, eGRO_011HoldingRegisters_t::DRYCONTACTFUNCEN, "DryContactFuncEn ", 1., NONE);                       // DryContact function enable R/W 0:Disable   1: Enable     DryContact function enable
addHoldingRegister(Protocol, 3017, SIZE_16BIT, eGRO_011HoldingRegisters_t::DRYCONTACTONRATE, "DryContactOnRate ", 1., NONE);                       // The power rate of drycontact turn on R/W 0~1000 0.1%    The  power  rate  of drycontact turn on
addHoldingRegister(Protocol, 3024, SIZE_16BIT, eGRO_011HoldingRegisters_t::FLOAT, "Float ", 1., NONE);                                             // charge current limit When charge current battery need is lower than this value, enter into float charge R/W  0.1A 600 CC current
addHoldingRegister(Protocol, 3025, SIZE_16BIT, eGRO_011HoldingRegisters_t::VBATWARNING, "VbatWarning ", 1., NONE);                                 // "Battery-low" warning setup voltage R/W  0.1V 4800 Lead acid battery LV voltage
addHoldingRegister(Protocol, 3026, SIZE_16BIT, eGRO_011HoldingRegisters_t::VBATLOWWARNCLR, "VbatlowWarnClr ", 1., NONE);                           // "Battery-low" warning clear voltage R/W  0.1V    Clear battery low voltage error voltage point  LoadPercent(only lead-Acid):  45.5V(Load < 20%); 48.0V(20%<=Load <=50%); 49.0V(Load > 50%);
addHoldingRegister(Protocol, 3027, SIZE_16BIT, eGRO_011HoldingRegisters_t::VBATSTOPFORDISCHARGE, "Vbatstopfordischarge ", 1., NONE);               // Battery cut off voltage R/W  0.1V    Should stop discharge when lower than this voltage(only lead-Acid):  46.0V(Load < 20%); 44.8V(20%<=Load <=50%); 44.2V(Load > 50%);
addHoldingRegister(Protocol, 3028, SIZE_16BIT, eGRO_011HoldingRegisters_t::VBAT_STOP, "Vbat stop ", 1., NONE);                                     // for charge Battery over charge voltage R/W  0.01V 5800 Should stop charge when higher than this voltage
addHoldingRegister(Protocol, 3029, SIZE_16BIT, eGRO_011HoldingRegisters_t::VBAT_START, "Vbat start ", 1., NONE);                                   // for discharge Battery start discharge voltage R/W  0.01V 4800 Should not discharge when lower than this voltage 3030 Vbat constant charge Battery constant charge voltage R/W  0.01V 5800 CV voltage（acid） can charge when lower than this voltage
addHoldingRegister(Protocol, 3031, SIZE_16BIT, eGRO_011HoldingRegisters_t::BATTEMP, "Battemp ", 1., NONE);                                         // lower limit d Battery temperature lower limit for discharge R/W  0.1°C 1170 0-200:0-20°C 1000-1400：-40-0°C
addHoldingRegister(Protocol, 3032, SIZE_16BIT, eGRO_011HoldingRegisters_t::BAT_TEMP_UPPER, "Bat temp upper ", 1., NONE);                           // limit d Battery temperature upper limit for discharge R/W  0.1°C 420
addHoldingRegister(Protocol, 3033, SIZE_16BIT, eGRO_011HoldingRegisters_t::BAT_TEMP_LOWER, "Bat temp lower", 1., NONE);                            // limit c Battery temperature lower limit for charge R/W  0.1°C 30 Battery temperature lower limit 0-200:0-20°C 1000-1400：-40-0°C
addHoldingRegister(Protocol, 3034, SIZE_16BIT, eGRO_011HoldingRegisters_t::BAT_TEMP_UPPER, "Bat temp upper ", 1., NONE);                           // limit c Battery temperature upper limit for charge R/W  0.1°C 370 Battery temperature upper limit
addHoldingRegister(Protocol, 3035, SIZE_16BIT, eGRO_011HoldingRegisters_t::UWUNDERFREDISCHARGEDELYTIME, "uwUnderFreDischargeDelyTime ", 1., NONE); // Under Fre Delay Time   R/W  50ms    Under Fre Delay Time
addHoldingRegister(Protocol, 3036, SIZE_16BIT, eGRO_011HoldingRegisters_t::GRIDFIRSTDISCHARGEPOWERRATE, "GridFirstDischargePowerRate ", 1., NONE); // Discharge Power Rate when Grid First
addHoldingRegister(Protocol, 3037, SIZE_16BIT, eGRO_011HoldingRegisters_t::GRIDFIRSTSTOPSOC, "GridFirstStopSOC ", 1., NONE);                       // Stop Discharge soc when Grid First
addHoldingRegister(Protocol, 3038, SIZE_16BIT, eGRO_011HoldingRegisters_t::GRID_FIRST_START_TIME_1, "Grid First Start Time 1", 1., NONE);          // Grid First Start Time 1       High eight bit : hour,0-23 Low eight bit : minute,0-59
addHoldingRegister(Protocol, 3039, SIZE_16BIT, eGRO_011HoldingRegisters_t::GRID_FIRST_STOP_TIME_1, "Grid First Stop Time 1", 1., NONE);            // Grid First Stop Time 1       High eight bit : hour,0-23 Low eight bit : minute,0-59
addHoldingRegister(Protocol, 3040, SIZE_16BIT, eGRO_011HoldingRegisters_t::GRID_FIRST_STOP_SWITCH_1, "Grid First Stop Switch 1", 1., NONE);        // Grid first time-1 enable       Enable :1 Disable:0
addHoldingRegister(Protocol, 3041, SIZE_16BIT, eGRO_011HoldingRegisters_t::GRID_FIRST_START_TIME_2, "Grid First Start Time 2", 1., NONE);          // Grid First Start Time 2       High eight bit : hour,0-23 Low eight bit : minute,0-59
addHoldingRegister(Protocol, 3042, SIZE_16BIT, eGRO_011HoldingRegisters_t::GRID_FIRST_STOP_TIME_2, "Grid First Stop Time 2", 1., NONE);            // Grid First Stop Time 2       High eight bit : hour,0-23 Low eight bit : minute,0-59
addHoldingRegister(Protocol, 3043, SIZE_16BIT, eGRO_011HoldingRegisters_t::GRID_FIRST_STOP_SWITCH_2, "Grid First Stop Switch 2", 1., NONE);        // ForceDischarge.bSwitch&LCD_SET_FORCE_TRUE_2)==LCD_SET_FORCE_TRUE_2       ForceDischarge; LCD_SET_FORCE_TRUE_2
addHoldingRegister(Protocol, 3044, SIZE_16BIT, eGRO_011HoldingRegisters_t::GRID_FIRST_START_TIME_3, "Grid First Start Time 3", 1., NONE);          // Grid First Start Time 3       High eight bit : hour,0-23 Low eight bit : minute,0-59
addHoldingRegister(Protocol, 3045, SIZE_16BIT, eGRO_011HoldingRegisters_t::GRID_FIRST_STOP_TIME_3, "Grid First Stop Time 3", 1., NONE);            // Grid First Stop Time 3       High eight bit : hour,0-23 Low eight bit : minute,0-59
addHoldingRegister(Protocol, 3046, SIZE_16BIT, eGRO_011HoldingRegisters_t::GRID_FIRST_STOP_SWITCH_3, "Grid First Stop Switch 3", 1., NONE);        // Grid first time-3 enable       Enable :1 Disable:0
addHoldingRegister(Protocol, 3047, SIZE_16BIT, eGRO_011HoldingRegisters_t::BATFIRSTPOWERRATE, "BatFirstPowerRate ", 1., NONE);                     // Charge Power Rate when Bat First
addHoldingRegister(Protocol, 3048, SIZE_16BIT, eGRO_011HoldingRegisters_t::WBATFIRST, "wBatFirst ", 1., NONE);                                     // stop SOC Stop Charge soc when Bat First
addHoldingRegister(Protocol, 3049, SIZE_16BIT, eGRO_011HoldingRegisters_t::AC, "AC ", 1., NONE);                                                   // charge Switch When Bat First   Enable :1 Disable:0       Enable :1 Disable:0
addHoldingRegister(Protocol, 3050, SIZE_16BIT, eGRO_011HoldingRegisters_t::BAT_FIRST_START_TIME_1, "Bat First Start Time 1", 1., NONE);            // Bat First Start Time 1       High eight bit : hour,0-23 Low eight bit : minute,0-59
addHoldingRegister(Protocol, 3051, SIZE_16BIT, eGRO_011HoldingRegisters_t::BAT_FIRST_STOP_TIME_1, "Bat First Stop Time 1", 1., NONE);              // Bat First Stop Time 1       High eight bit : hour,0-23 Low eight bit : minute,0-59
addHoldingRegister(Protocol, 3052, SIZE_16BIT, eGRO_011HoldingRegisters_t::BATFIRST_ON / off_Switch_1, "BatFirst on/off Switch 1", 1., NONE);      // Battery first time-1 enable       Enable :1 Disable:0
addHoldingRegister(Protocol, 3053, SIZE_16BIT, eGRO_011HoldingRegisters_t::BAT_FIRST_START_TIME_2, "Bat First Start Time 2", 1., NONE);            // Bat First Start Time 2       High eight bit : hour,0-23 Low eight bit : minute,0-59
addHoldingRegister(Protocol, 3054, SIZE_16BIT, eGRO_011HoldingRegisters_t::BAT_FIRST_STOP_TIME_2, "Bat First Stop Time 2", 1., NONE);              // Bat First Stop Time 2       High eight bit : hour,0-23 Low eight bit : minute,0-59
addHoldingRegister(Protocol, 3055, SIZE_16BIT, eGRO_011HoldingRegisters_t::BATFIRST_ON / off_Switch_2, "BatFirst on/off Switch 2 ", 1., NONE);     // Battery first time-2 enable       Enable :1 Disable:0
addHoldingRegister(Protocol, 3056, SIZE_16BIT, eGRO_011HoldingRegisters_t::BAT_FIRST_START_TIME_3, "Bat First Start Time 3", 1., NONE);            // Bat First Start Time 3       High eight bit : hour,0-23 Low eight bit : minute,0-59
addHoldingRegister(Protocol, 3057, SIZE_16BIT, eGRO_011HoldingRegisters_t::BAT_FIRST_STOP_TIME_3, "Bat First Stop Time 3", 1., NONE);              // Bat First Stop Time 3       High eight bit : hour,0-23 Low eight bit : minute,0-59
addHoldingRegister(Protocol, 3058, SIZE_16BIT, eGRO_011HoldingRegisters_t::BATFIRST_ON / off_Switch_3, "BatFirst on/off Switch 3", 1., NONE);      // Battery first time-3 enable       Enable :1 Disable:0
addHoldingRegister(Protocol, 3059, SIZE_16BIT, eGRO_011HoldingRegisters_t::LOAD_FIRST_START_TIME_1, "Load First Start Time 1", 1., NONE);          // Load First Start Time 1       High eight bit : hour,0-23 Low eight bit : minute,0-59
addHoldingRegister(Protocol, 3060, SIZE_16BIT, eGRO_011HoldingRegisters_t::LOAD_FIRST_STOP_TIME_1, "Load First Stop Time 1", 1., NONE);            // Load First Stop Time 1       High eight bit : hour,0-23 Low eight bit : minute,0-59
addHoldingRegister(Protocol, 3061, SIZE_16BIT, eGRO_011HoldingRegisters_t::LOAD_FIRST_SWITCH_1, "Load First Switch 1", 1., NONE);                  // Enable :1 Disable:0       Enable :1 Disable:0
addHoldingRegister(Protocol, 3062, SIZE_16BIT, eGRO_011HoldingRegisters_t::LOAD_FIRST_START_TIME_2, "Load First Start Time 2", 1., NONE);          // Load First Start Time2       High eight bit : hour,0-23 Low eight bit : minute,0-59
addHoldingRegister(Protocol, 3063, SIZE_16BIT, eGRO_011HoldingRegisters_t::LOAD_FIRST_STOP_TIME_2, "Load First Stop Time 2", 1., NONE);            // Load First Stop Time 2       High eight bit : hour,0-23 Low eight bit : minute,0-59
addHoldingRegister(Protocol, 3064, SIZE_16BIT, eGRO_011HoldingRegisters_t::LOAD_FIRST_SWITCH_2, "Load First Switch 2", 1., NONE);                  // Enable :1 Disable:0       Enable :1 Disable:0
addHoldingRegister(Protocol, 3065, SIZE_16BIT, eGRO_011HoldingRegisters_t::LOAD_FIRST_START_TIME_3, "Load First Start Time 3", 1., NONE);          // Load First Start Time 3       High eight bit : hour,0-23 Low eight bit : minute,0-59
addHoldingRegister(Protocol, 3066, SIZE_16BIT, eGRO_011HoldingRegisters_t::LOAD_FIRST_STOP_TIME_3, "Load First Stop Time 3", 1., NONE);            // Load First Stop Time 3       High eight bit : hour,0-23 Low eight bit : minute,0-59
addHoldingRegister(Protocol, 3067, SIZE_16BIT, eGRO_011HoldingRegisters_t::LOAD_FIRST_SWITCH_3_ENABLE, "Load First Switch 3 Enable", 1., NONE);    // :1 Disable:0       Enable :1 Disable:0
addHoldingRegister(Protocol, 3068, SIZE_16BIT, eGRO_011HoldingRegisters_t::BCTMODE, "bCTMode ", 1., NONE);                                         // Use the CTMode to Choose RFCT \ Cable CT\METER R/W      CTMode 0: CT selfAdjust; 1:cWiredCT 2:cWirelessCT 3:METER
addHoldingRegister(Protocol, 3069, SIZE_16BIT, eGRO_011HoldingRegisters_t::PRIORITY, "Priority ", 1., NONE);                                       // ForceChrEn/ForceDischrEn Load first/bat first /grid first R/W      ForceChrEn/ForceDischrEn Load first/bat first /grid first  0.Load(default)/1.Battery/2.Grid
addHoldingRegister(Protocol, 3070, SIZE_16BIT, eGRO_011HoldingRegisters_t::BATTERYTYPE, "BatteryType ", 1., NONE);                                 // Battery type choose of buck-boost input R/W      Battery type 0:Lithium 1:Lead-acid 2:other
addHoldingRegister(Protocol, 3071, SIZE_16BIT, eGRO_011HoldingRegisters_t::BATMDLSERIA, "BatMdlSeria ", 1., NONE);                                 /// ParalNum BatMdlSeria/ParalNum R/W      BatMdlSeria/ParalNum; SPH4-11K used The upper 8 bits indicate the number of series segments； The lower 8 bits indicate the number of parallel
addHoldingRegister(Protocol, 3079, SIZE_16BIT, eGRO_011HoldingRegisters_t::UPSFUNEN, "UpsFunEn ", 1., NONE);                                       // Ups function enable or disable R/W   0 0:disable   1:enable
addHoldingRegister(Protocol, 3080, SIZE_16BIT, eGRO_011HoldingRegisters_t::UPSVOLTSET, "UPSVoltSet ", 1., NONE);                                   // UPS output voltage R/W   0 0:230V 1:208V 2:240V
addHoldingRegister(Protocol, 3081, SIZE_16BIT, eGRO_011HoldingRegisters_t::UPSFREQSET, "UPSFreqSet ", 1., NONE);                                   // UPS output frequency R/W   0 0:50Hz 1:60Hz
addHoldingRegister(Protocol, 3085, SIZE_16BIT, eGRO_011HoldingRegisters_t::COM, "Com ", 1., NONE);                                                 // Address Communication addr R/W   1 1 : Communication addr=1   1 ~ 254 : Communication addr=1~254
addHoldingRegister(Protocol, 3086, SIZE_16BIT, eGRO_011HoldingRegisters_t::BAUDRATE, "BaudRate ", 1., NONE);                                       // Communication BaudRate R/W   0 0: 9600 bps 1: 38400 bps
addHoldingRegister(Protocol, 3087, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIAL_NO_5, "Serial NO. 5", 1., NONE);                                 // Serial Number 5 R/W  ASCII
addHoldingRegister(Protocol, 3088, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIAL_NO_4, "Serial No. 4", 1., NONE);                                 // Serial Number 4 R/W  ASCII
addHoldingRegister(Protocol, 3089, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIAL_NO_3, "Serial No. 3", 1., NONE);                                 // Serial Number 3 R/W  ASCII
addHoldingRegister(Protocol, 3090, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIAL_NO_2, "Serial No. 2", 1., NONE);                                 // Serial Number 2 R/W  ASCII
addHoldingRegister(Protocol, 3091, SIZE_16BIT, eGRO_011HoldingRegisters_t::SERIAL_NO_1, "Serial No. 1", 1., NONE);                                 // Serial Number 1 R/W  ASCII
addHoldingRegister(Protocol, 3092, SIZE_32BIT, eGRO_011HoldingRegisters_t::MODEL, "Model ", 1., NONE);                                             // H Model H R/W
addHoldingRegister(Protocol, 3094, SIZE_32BIT, eGRO_011HoldingRegisters_t::PDISCHR_MAX, "Pdischr max", 1., NONE);                                  //  H  Max Discharge Power R  0.1W
addHoldingRegister(Protocol, 3096, SIZE_32BIT, eGRO_011HoldingRegisters_t::PCHR_MAX, "Pchr max    ", 1., NONE);                                    // H Max Charge Power R  0.1W
addHoldingRegister(Protocol, 3098, SIZE_16BIT, eGRO_011HoldingRegisters_t::DTC, "DTC ", 1., NONE);                                                 // DTC R
addHoldingRegister(Protocol, 3099, SIZE_16BIT, eGRO_011HoldingRegisters_t::FW_CODE1, "FW Code1", 1., NONE);                                        // FW Code1 R  ASCII
addHoldingRegister(Protocol, 3100, SIZE_16BIT, eGRO_011HoldingRegisters_t::FW_CODE2, "FW Code2", 1., NONE);                                        // FW Code2 R  ASCII
addHoldingRegister(Protocol, 3101, SIZE_16BIT, eGRO_011HoldingRegisters_t::PROCESSOR1, "Processor1 ", 1., NONE);                                   // FW Vision Processor1 FW Vision R  ASCII
addHoldingRegister(Protocol, 3102, SIZE_16BIT, eGRO_011HoldingRegisters_t::RESET_USER_INFO, "Reset User Info ", 1., NONE);                         // Reset User Info W
addHoldingRegister(Protocol, 3103, SIZE_16BIT, eGRO_011HoldingRegisters_t::RESET_TO_FACTORY, "Reset to factory", 1., NONE);                        // Reset to factory W

}
