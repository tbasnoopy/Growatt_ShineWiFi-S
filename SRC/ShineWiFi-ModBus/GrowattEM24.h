#ifndef _GROWATT_ET340_H_
#define _GROWATT_ET340_H_

#include "Arduino.h"
#include "GrowattTypes.h"

typedef enum {
  EM24_V_L1_N = 0,
  EM24_V_L2_N,
  EM24_V_L3_N,
  EM24_V_L1_L2,
  EM24_V_L2_L3,
  EM24_V_L3_L1,
  EM24_A_L1,
  EM24_A_L2,
  EM24_A_L3,
  EM24_W_L1,
  EM24_W_L2,
  EM24_W_L3,
  EM24_VA_L1,
  EM24_VA_L2,
  EM24_VA_L3,
  EM24_VAR_L1,
  EM24_VAR_L2,
  EM24_VAR_L3,
  EM24_V_L_N_Epsilon,
  EM24_V_L_L_Epsilon,
  EM24_W_Epsilon,
  EM24_VA_Epsilon,
  EM24_VAR_Epsilon,
  EM24_DMD_W_Epsilon,
  EM24_DMD_VA_Epsilon,
  EM24_PF_L1,
  EM24_PF_L2,
  EM24_PF_L3,
  EM24_PF_Epsilon,
  EM24_Phase_sequence,
  EM24_Hz,
  EM24_DMD_W_Epsilon_max,
  EM24_DMD_VA_Epsilon_max,
  EM24_DMD_A_max,
  EM24_kWh_PLUS_TOT,
  EM24_kvarh_PLUS_TOT,
  EM24_KWh_PLUS_PAR,
  EM24_kvarh_PLUS_PAR,
  EM24_kWh_PLUS_L1,
  EM24_kWh_PLUS_L2,
  EM24_kWh_PLUS_L3,
  EM24_kWh_PLUS_T1,
  EM24_kWh_PLUS_T2,
  EM24_kWh_PLUS_T3,
  EM24_kWh_PLUS_T4,
  EM24_kvarh_PLUS_T1,
  EM24_kvarh_PLUS_T2,
  EM24_kvarh_PLUS_T3,
  EM24_kvarh_PLUS_T4,
  EM24_kWh_MINUS_TOT,
  EM24_kvarh_MINUS_TOT,
  EM24_Hour,
  EM24_Counter_1,
  EM24_Counter_2,
  EM24_Counter_3,
  EM24_Digital_Input_Status,
  EM24_Current_Tariff,
  LASTInput
} eEM24InputRegisters_t;

typedef enum { LASTHolding } eEM24HoldingRegisters_t;

void init_growattEM24(sProtocolDefinition_t &Protocol);

#endif  // _GROWATT_ET340_H_