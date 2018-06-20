/*
 * This file is part of Cleanflight and Betaflight.
 *
 * Cleanflight and Betaflight are free software. You can redistribute
 * this software and/or modify this software under the terms of the
 * GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * Cleanflight and Betaflight are distributed in the hope that they
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software.
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */

/* Created by jflyper */

#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#include "build/debug.h"

#if defined(USE_VTX_COMMON)

#define VTX_STRING_BAND_COUNT 2
#define VTX_STRING_CHAN_COUNT 8

const uint16_t vtx58frequencyTable[VTX_STRING_BAND_COUNT][VTX_STRING_CHAN_COUNT] =
{
    { 5658, 5695, 5732, 5769, 5806, 5843, 5880, 5917 }, // RaceBand
    { 5362, 5399, 5436, 5473, 5510, 5547, 5584, 5621 }, // LowRaceBand
};

const char * const vtx58BandNames[] = {
    "--------",
    "RACEBAND",
    "LOWRACEB",
};

const char vtx58BandLetter[] = "-RL";

const char * const vtx58ChannelNames[] = {
    "-", "1", "2", "3", "4", "5", "6", "7", "8",
};

//Converts frequency (in MHz) to band and channel values.
bool vtx58_Freq2Bandchan(uint16_t freq, uint8_t *pBand, uint8_t *pChannel)
{
    // Use reverse lookup order so that 5880Mhz
    // get Raceband 7 instead of Fatshark 8.
    for (int band = VTX_STRING_BAND_COUNT - 1 ; band >= 0 ; band--) {
        for (int channel = 0 ; channel < VTX_STRING_CHAN_COUNT ; channel++) {
            if (vtx58frequencyTable[band][channel] == freq) {
                *pBand = band + 1;
                *pChannel = channel + 1;
                return true;
            }
        }
    }

    *pBand = 0;
    *pChannel = 0;

    return false;
}

//Converts band and channel values to a frequency (in MHz) value.
// band:  Band value (1 to 5).
// channel:  Channel value (1 to 8).
// Returns frequency value (in MHz), or 0 if band/channel out of range.
uint16_t vtx58_Bandchan2Freq(uint8_t band, uint8_t channel)
{
    if (band > 0 && band <= VTX_STRING_BAND_COUNT &&
                          channel > 0 && channel <= VTX_STRING_CHAN_COUNT) {
        return vtx58frequencyTable[band - 1][channel - 1];
    }
    return 0;
}

#endif
