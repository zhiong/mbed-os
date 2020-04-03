/* mbed Microcontroller Library
 * Copyright (c) 2006-2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "drivers/AnalogIn.h"

#if DEVICE_ANALOGIN

namespace mbed {

SingletonPtr<PlatformMutex> AnalogIn::_mutex;

AnalogIn::AnalogIn(PinName pin) : vref(MBED_CONF_TARGET_DEFAULT_ADC_VREF)
{
    lock();
    analogin_init(&_adc, pin);
    unlock();
}

AnalogIn::AnalogIn(const PinMap &pinmap) : vref(MBED_CONF_TARGET_DEFAULT_ADC_VREF)
{
    lock();
    analogin_init_direct(&_adc, &pinmap);
    unlock();
}


float AnalogIn::read()
{
    lock();
    float ret = analogin_read(&_adc);
    unlock();
    return ret;
}

unsigned short AnalogIn::read_u16()
{
    lock();
    unsigned short ret = analogin_read_u16(&_adc);
    unlock();
    return ret;
}

float AnalogIn::read_voltage()
{
    return (this->read() * this->vref);
}

void AnalogIn::set_reference_voltage(float vref)
{
    this->vref = vref;
}

float AnalogIn::get_reference_voltage(void)
{
    return this->vref;
}

} // namespace mbed

#endif
