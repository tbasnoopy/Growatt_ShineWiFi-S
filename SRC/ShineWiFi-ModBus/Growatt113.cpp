#include "Arduino.h"

#include "Growatt113.h"

// information from:
// https://www.amosplanet.org/wp-content/uploads/2022/12/%E9%80%9A%E4%BF%A1%E5%8D%8F%E8%AE%AEMAX_Growatt-Inverter-Modbus-RTU-Protocol_II-V1_13_20190116-English.pdf

// Supported inverters:
// ????

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
                 const eGRO_113InputRegisters_t& start,
                 const eGRO_113InputRegisters_t& end) {
  Protocol.InputReadFragments[Protocol.InputFragmentCount++] =
      sGrowattReadFragment_t{
          Protocol.InputRegisters[start].address,
          static_cast<uint8_t>(
              Protocol.InputRegisters[end].address +
              getSizeFromEnum(Protocol.InputRegisters[end].size) -
              Protocol.InputRegisters[start].address)};
}

void init_growatt113(sProtocolDefinition_t& Protocol) {
  // definition of input registers

  // max 11 words per request

  // 2.3 Instantaneous variables and meters
  // general informations
  Protocol.InputRegisterCount = eGRO_113InputRegisters_t::LASTInput;

  //   addFragment(Protocol,
  //   eGRO_113InputRegisters_t::GRO_113_Digital_Input_Status,eGRO_113InputRegisters_t::GRO_113_Digital_Input_Status);

  // definition of holding registers
  Protocol.HoldingRegisterCount = eGRO_113HoldingRegisters_t::LASTHolding;
  Protocol.HoldingFragmentCount = 0;
}
