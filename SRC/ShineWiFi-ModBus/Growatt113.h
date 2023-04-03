#ifndef _GROWATT_ET340_H_
#define _GROWATT_ET340_H_

#include "Arduino.h"
#include "GrowattTypes.h"

typedef enum { LASTInput } eGRO_113InputRegisters_t;

typedef enum { LASTHolding } eGRO_113HoldingRegisters_t;

void init_growatt113(sProtocolDefinition_t &Protocol);

#endif  // _GROWATT_ET340_H_