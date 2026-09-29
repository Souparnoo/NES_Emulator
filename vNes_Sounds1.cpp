

#include <iostream>
#include <sstream>
#include <deque>

#include "Bus.h"

#define V_PGE_APPLICATION
#include "vPixelGameEngine.h"

#define V_PGEX_SOUND
#include "vPGEX_Sound.h"

class Demo_vNES : public v::PixelGameEngine
{
public:
	Demo_vNES() { sAppName = "vNES Sound Demonstration"; }

private: 
	
	Bus nes;
	std::shared_ptr<Cartridge> cart;
	bool bEmulationRun = false;
	float fResidualTime = 0.0f;

	uint8_t nSelectedPalette = 0x00;

	std::list<uint16_t> audio[4];
	float fAccumulatedTime = 0.0f;

private: 
	
	std::map<uint16_t, std::string> mapAsm;

	std::string hex(uint32_t n, uint8_t d)
	{
		std::string s(d, '0');
		for (int i = d - 1; i >= 0; i--, n >>= 4)
			s[i] = "0123456789ABCDEF"[n & 0xF];
		return s;
	};

	void DrawRam(int x, int y, uint16_t nAddr, int nRows, int nColumns)
	{
		int nRamX = x, nRamY = y;
		for (int row = 0; row < nRows; row++)
		{
			std::string sOffset = "$" + hex(nAddr, 4) + ":";
			for (int col = 0; col < nColumns; col++)
			{
				sOffset += " " + hex(nes.cpuRead(nAddr, true), 2);
				nAddr += 1;
			}
			DrawString(nRamX, nRamY, sOffset);
			nRamY += 10;
		}
	}

	void DrawCpu(int x, int y)
	{
		std::string status = "STATUS: ";
		DrawString(x , y , "STATUS:", v::WHITE);
		DrawString(x  + 64, y, "N", nes.cpu.status & v6502::N ? v::GREEN : v::RED);
		DrawString(x  + 80, y , "V", nes.cpu.status & v6502::V ? v::GREEN : v::RED);
		DrawString(x  + 96, y , "-", nes.cpu.status & v6502::U ? v::GREEN : v::RED);
		DrawString(x  + 112, y , "B", nes.cpu.status & v6502::B ? v::GREEN : v::RED);
		DrawString(x  + 128, y , "D", nes.cpu.status & v6502::D ? v::GREEN : v::RED);
		DrawString(x  + 144, y , "I", nes.cpu.status & v6502::I ? v::GREEN : v::RED);
		DrawString(x  + 160, y , "Z", nes.cpu.status & v6502::Z ? v::GREEN : v::RED);
		DrawString(x  + 178, y , "C", nes.cpu.status & v6502::C ? v::GREEN : v::RED);
		DrawString(x , y + 10, "PC: $" + hex(nes.cpu.pc, 4));
		DrawString(x , y + 20, "A: $" +  hex(nes.cpu.a, 2) + "  [" + std::to_string(nes.cpu.a) + "]");
		DrawString(x , y + 30, "X: $" +  hex(nes.cpu.x, 2) + "  [" + std::to_string(nes.cpu.x) + "]");
		DrawString(x , y + 40, "Y: $" +  hex(nes.cpu.y, 2) + "  [" + std::to_string(nes.cpu.y) + "]");
		DrawString(x , y + 50, "Stack P: $" + hex(nes.cpu.stkp, 4));
	}

	void DrawCode(int x, int y, int nLines)
	{
		auto it_a = mapAsm.find(nes.cpu.pc);
		int nLineY = (nLines >> 1) * 10 + y;
		if (it_a != mapAsm.end())
		{
			DrawString(x, nLineY, (*it_a).second, v::CYAN);
			while (nLineY < (nLines * 10) + y)
			{
				nLineY += 10;
				if (++it_a != mapAsm.end())
				{
					DrawString(x, nLineY, (*it_a).second);
				}
			}
		}

		it_a = mapAsm.find(nes.cpu.pc);
		nLineY = (nLines >> 1) * 10 + y;
		if (it_a != mapAsm.end())
		{
			while (nLineY > y)
			{
				nLineY -= 10;
				if (--it_a != mapAsm.end())
				{
					DrawString(x, nLineY, (*it_a).second);
				}
			}
		}
	}

	void DrawAudio(int channel, int x, int y)
	{
		FillRect(x, y, 120, 120, v::BLACK);
		int i = 0;
		for (auto s : audio[channel])
		{
			Draw(x + i, y + (s >> (channel == 2 ? 5 : 4)), v::YELLOW);
			i++;
		}
	}

	static Demo_vNES* pInstance; 

	static float SoundOut(int nChannel, float fGlobalTime, float fTimeStep)
	{
		if (nChannel == 0)
		{
			while (!pInstance->nes.clock()) {};
			return static_cast<float>(pInstance->nes.dAudioSample);
		}
		else
			return 0.0f;
	}

	bool OnUserCreate() override
	{
		
		cart = std::make_shared<Cartridge>("pacman.nes");
		
		if (!cart->ImageValid())
			return false;

		nes.insertCartridge(cart);

		for (int i = 0; i < 4; i++)
		{			
			for (int j = 0; j < 120; j++)
				audio[i].push_back(0);
		}

		nes.reset();

		pInstance = this;
		nes.SetSampleFrequency(44100);
		v::SOUND::InitialiseAudio(44100, 1, 8, 512);
		v::SOUND::SetUserSynthFunction(SoundOut);
		return true;
	}

	bool OnUserDestroy() override
	{
		v::SOUND::DestroyAudio();
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		EmulatorUpdateWithAudio(fElapsedTime);
		return true;
	}

	bool EmulatorUpdateWithAudio(float fElapsedTime)
	{
		
		fAccumulatedTime += fElapsedTime;
		if (fAccumulatedTime >= 1.0f / 60.0f)
		{
			fAccumulatedTime -= (1.0f / 60.0f);
			audio[0].pop_front();
			audio[0].push_back(nes.apu.pulse1_visual);
			audio[1].pop_front();
			audio[1].push_back(nes.apu.pulse2_visual);
			audio[2].pop_front();
			audio[2].push_back(nes.apu.noise_visual);
		}

		Clear(v::DARK_BLUE);

		nes.controller[0] = 0x00;
		nes.controller[0] |= GetKey(v::Key::X).bHeld ? 0x80 : 0x00;     
		nes.controller[0] |= GetKey(v::Key::Z).bHeld ? 0x40 : 0x00;     
		nes.controller[0] |= GetKey(v::Key::A).bHeld ? 0x20 : 0x00;     
		nes.controller[0] |= GetKey(v::Key::S).bHeld ? 0x10 : 0x00;     
		nes.controller[0] |= GetKey(v::Key::UP).bHeld ? 0x08 : 0x00;
		nes.controller[0] |= GetKey(v::Key::DOWN).bHeld ? 0x04 : 0x00;
		nes.controller[0] |= GetKey(v::Key::LEFT).bHeld ? 0x02 : 0x00;
		nes.controller[0] |= GetKey(v::Key::RIGHT).bHeld ? 0x01 : 0x00;

		if (GetKey(v::Key::R).bPressed) nes.reset();
		if (GetKey(v::Key::P).bPressed) (++nSelectedPalette) &= 0x07;

		DrawCpu(516, 2);

		DrawAudio(0, 520, 72);
		DrawAudio(1, 644, 72);
		DrawAudio(2, 520, 196);
		DrawAudio(3, 644, 196);

		const int nSwatchSize = 6;
		for (int p = 0; p < 8; p++) 
			for(int s = 0; s < 4; s++) 
				FillRect(516 + p * (nSwatchSize * 5) + s * nSwatchSize, 340, 
					nSwatchSize, nSwatchSize, nes.ppu.GetColourFromPaletteRam(p, s));

		DrawRect(516 + nSelectedPalette * (nSwatchSize * 5) - 1, 339, (nSwatchSize * 4), nSwatchSize, v::WHITE);

		DrawSprite(516, 348, &nes.ppu.GetPatternTable(0, nSelectedPalette));
		DrawSprite(648, 348, &nes.ppu.GetPatternTable(1, nSelectedPalette));

		DrawSprite(0, 0, &nes.ppu.GetScreen(), 2);
		return true;
	}

	bool EmulatorUpdateWithoutAudio(float fElapsedTime)
	{
		Clear(v::DARK_BLUE);

		nes.controller[0] = 0x00;
		nes.controller[0] |= GetKey(v::Key::X).bHeld ? 0x80 : 0x00;     
		nes.controller[0] |= GetKey(v::Key::Z).bHeld ? 0x40 : 0x00;     
		nes.controller[0] |= GetKey(v::Key::A).bHeld ? 0x20 : 0x00;     
		nes.controller[0] |= GetKey(v::Key::S).bHeld ? 0x10 : 0x00;     
		nes.controller[0] |= GetKey(v::Key::UP).bHeld ? 0x08 : 0x00;
		nes.controller[0] |= GetKey(v::Key::DOWN).bHeld ? 0x04 : 0x00;
		nes.controller[0] |= GetKey(v::Key::LEFT).bHeld ? 0x02 : 0x00;
		nes.controller[0] |= GetKey(v::Key::RIGHT).bHeld ? 0x01 : 0x00;

		if (GetKey(v::Key::SPACE).bPressed) bEmulationRun = !bEmulationRun;
		if (GetKey(v::Key::R).bPressed) nes.reset();
		if (GetKey(v::Key::P).bPressed) (++nSelectedPalette) &= 0x07;

		if (bEmulationRun)
		{
			if (fResidualTime > 0.0f)
				fResidualTime -= fElapsedTime;
			else
			{
				fResidualTime += (1.0f / 60.0f) - fElapsedTime;
				do { nes.clock(); } while (!nes.ppu.frame_complete);
				nes.ppu.frame_complete = false;
			}
		}
		else
		{
			
			if (GetKey(v::Key::C).bPressed)
			{
				
				do { nes.clock(); } while (!nes.cpu.complete());

				do { nes.clock(); } while (nes.cpu.complete());
			}

			if (GetKey(v::Key::F).bPressed)
			{
				
				do { nes.clock(); } while (!nes.ppu.frame_complete);
				
				do { nes.clock(); } while (!nes.cpu.complete());
				
				nes.ppu.frame_complete = false;
			}
		}

		DrawCpu(516, 2);

		const int nSwatchSize = 6;
		for (int p = 0; p < 8; p++) 
			for (int s = 0; s < 4; s++) 
				FillRect(516 + p * (nSwatchSize * 5) + s * nSwatchSize, 340,
					nSwatchSize, nSwatchSize, nes.ppu.GetColourFromPaletteRam(p, s));

		DrawRect(516 + nSelectedPalette * (nSwatchSize * 5) - 1, 339, (nSwatchSize * 4), nSwatchSize, v::WHITE);

		DrawSprite(516, 348, &nes.ppu.GetPatternTable(0, nSelectedPalette));
		DrawSprite(648, 348, &nes.ppu.GetPatternTable(1, nSelectedPalette));

		DrawSprite(0, 0, &nes.ppu.GetScreen(), 2);
		return true;
	}
};

Demo_vNES* Demo_vNES::pInstance = nullptr;

int main()
{
	Demo_vNES demo;
	demo.Construct(780, 480, 2, 2);
	demo.Start();
	return 0;
}