

#pragma once
#include <cstdint>
#include <array>

#include "v6502.h"
#include "v2C02.h"
#include "v2A03.h"
#include "Cartridge.h"

class Bus
{
public:
	Bus();
	~Bus();

public: 

	v6502 cpu;	
	
	v2C02 ppu;
	
	v2A03 apu;
	
	std::shared_ptr<Cartridge> cart;
	
	uint8_t cpuRam[2048];
	
	uint8_t controller[2];

public:
	void SetSampleFrequency(uint32_t sample_rate);
	double dAudioSample = 0.0;

private:
	double dAudioTime = 0.0;
	double dAudioGlobalTime = 0.0;
	double dAudioTimePerNESClock = 0.0;
	double dAudioTimePerSystemSample = 0.0f;

public: 
	void    cpuWrite(uint16_t addr, uint8_t data);
	uint8_t cpuRead(uint16_t addr, bool bReadOnly = false);

private:
	
	uint32_t nSystemClockCounter = 0;
	
	uint8_t controller_state[2];

private:

	uint8_t dma_page = 0x00;
	uint8_t dma_addr = 0x00;
	uint8_t dma_data = 0x00;

	bool dma_dummy = true;

	bool dma_transfer = false;

public: 
	
	void insertCartridge(const std::shared_ptr<Cartridge>& cartridge);
	
	void reset();
	
	bool clock();
};

