/**
  * Copyright (C) 2019 fleroviux (Frederic Meyer)
  *
  * This file is part of NanoboyAdvance.
  *
  * NanoboyAdvance is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * NanoboyAdvance is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with NanoboyAdvance. If not, see <http://www.gnu.org/licenses/>.
  */

#pragma once

#include <cstdint>

namespace GameBoyAdvance {

class CPU;
  
class TimerController {
public:
  TimerController(CPU* cpu) : cpu(cpu) { }
  
  void Reset();
  void Run(int cycles);
  auto GetCyclesUntilIrq() -> int;
  auto Read(int id, int offset) -> std::uint8_t;
  void Write(int id, int offset, std::uint8_t value);
  
private:
  void Increment(int id, int increment);
  void LatchAudioFromFIFO(int id, int increment); 
  
  CPU* cpu;
  
  struct Timer {
    int id;

    struct Control {
      int frequency;
      bool cascade;
      bool interrupt;
      bool enable;
    } control;

    int cycles;
    std::uint16_t reload;
    std::uint32_t counter;

    /* internal */
    int  shift;
    int  mask;
    bool overflow;
  } timer[4];
};

}