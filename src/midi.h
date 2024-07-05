#pragma once
#include "MIDIUSB.h"

void noteOn(byte channel, byte pitch, byte velocity, bool isCc = false)
{
  if (isCc)
  {
    midiEventPacket_t cc = {0x0B, 0xB0 | channel, pitch, velocity};
    MidiUSB.sendMIDI(cc);
    return;
  }
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity, bool isCc = false)
{
  if (isCc)
  {
    midiEventPacket_t cc = {0x0B, 0xB0 | channel, pitch, 0};
    MidiUSB.sendMIDI(cc);
    return;
  }
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

void flushMidi()
{
  MidiUSB.flush();
}