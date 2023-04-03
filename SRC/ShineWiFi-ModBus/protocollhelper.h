#pragma once

#include "GrowattTypes.h"
#include <stdint.h>

template <typename T>
void addInputRegister(sProtocolDefinition_t& Protocol, const uint16_t& address,
                      const RegisterSize_t& size, const T id,
                      const char name[64], const float multiplier,
                      const RegisterUnit_t& unit, const bool frontend = false,
                      const bool plot = false) {
  // todo calculate the resolution
  Protocol.InputRegisters[static_cast<unsigned int>(id)] = sGrowattModbusReg_t{
      address, 0, size, *name, multiplier, multiplier, unit, frontend, plot};
}

template <typename T>
void addHoldingRegister(sProtocolDefinition_t& Protocol,
                        const uint16_t& address, const RegisterSize_t& size,
                        const T id, const char name[64],
                        const float& multiplier, const RegisterUnit_t& unit,
                        const bool frontend = false, const bool plot = false) {
  // todo calculate the resolution
  Protocol.HoldingRegisters[static_cast<unsigned int>(id)] =
      sGrowattModbusReg_t{address,    0,    size,     *name, multiplier,
                          multiplier, unit, frontend, plot};
}

inline uint8_t getSizeFromEnum(const RegisterSize_t& s) {
  switch (s) {
    case RegisterSize_t::SIZE_16BIT:
    case RegisterSize_t::SIZE_16BIT_S:
      return 1;
    case RegisterSize_t::SIZE_32BIT:
    case RegisterSize_t::SIZE_32BIT_S:
      return 2;
  }
  return 2;  // max size...
}

// assuming the register are in order (by address)
template <typename T>
void makeSegments(const T slastID, const uint8_t maxFragmentLength,
                  const sGrowattModbusReg_t* Registers,
                  sGrowattReadFragment_t*Fragments,
                  uint8_t& FragmentCount
                  ) {
  uint8_t currentFragmentID = 0;

  uint16_t start = Registers[0].address;
  uint8_t len = 0;

  uint16_t lastID = static_cast<uint16_t>(slastID);

  for (uint8_t id = 0; id < static_cast<unsigned int>(lastID); id++) {
    auto x = getSizeFromEnum(Registers[id].size);
    auto f = Registers[id].address + x - start;

    if (f > maxFragmentLength) {
      auto a = start;
      auto b =
          static_cast<uint8_t>(Registers[id - 1].address +
                               getSizeFromEnum(Registers[id - 1].size) - start);

      // buffer ueberschritten
      Fragments[currentFragmentID++] =
          sGrowattReadFragment_t{a, b};
      start =
          Registers[id - 1].address + getSizeFromEnum(Registers[id - 1].size);
    }
  }

  if (start != Registers[lastID - 1].address)
    Fragments[currentFragmentID++] = sGrowattReadFragment_t{
        start,
        static_cast<uint8_t>(start - Registers[lastID - 1].address +
                             getSizeFromEnum(Registers[lastID - 1].size))};

  FragmentCount = currentFragmentID - 1;
}
