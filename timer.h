/* * GameEngine - A cross platform game engine made using OpenGL and c++
 * Copyright (C) 2016-2020 Matan Keren <xmakerenx@gmail.com>
 *
 * This file is part of GameEngine.
 *
 * GameEngine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GameEngine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GameEngine.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef  _TIMER_H
#define  _TIMER_H

#ifdef _WIN32
    #include <windows.h>
    #undef max
    #undef min
#else
    #include <sys/time.h>
    // Helpful conversion constants.
    static const unsigned usec_per_sec = 1000000;
    static const unsigned usec_per_msec = 1000;
#endif

#include <cinttypes>
#include <cassert>
#include <cstring>
#include <iostream>
#include <list>
#include <functional>

const unsigned long MAX_SAMPLE_COUNT = 50;  // Maximum frame time sample count

class Timer
{
    
    struct alarm
    {
        alarm(int64_t _creationTime, int64_t _fireTime, const std::function<void (void)>& _callback, int64_t _repeat)
            :creationTime(_creationTime), fireTime(_fireTime), callback(_callback), repeat(_repeat)
        {}
        
        alarm(int64_t _creationTime, int64_t _fireTime, std::function<void (void)>&& _callback, int64_t _repeat)
            :creationTime(_creationTime), fireTime(_fireTime), callback(_callback), repeat(_repeat)
        {}
        
        int64_t creationTime;
        int64_t fireTime;
        std::function<void (void)> callback;
        int64_t repeat;
    };
    
public:
    typedef std::list<alarm>::iterator AlarmIterator;
    
    Timer(void);
    virtual ~Timer(void);

    // These functions are written to match the win32
    // signatures and behavior as closely as possible.
    static bool  getPerformanceFrequency(int64_t* frequency);
    static bool  getPerformanceCounter(int64_t* performance_count);

    void                   frameAdvanced   ();
    double                 getTimeElapsed  ();
    double                 getCurrentTime  ();
    double                 getLastTime     ();
    unsigned long          getFPS          ();
    bool                   isCap           ();
    
    std::list<alarm>::iterator addAlram(int64_t duration, const std::function<void (void)>& callback ,int64_t repeated);
    std::list<alarm>::iterator addAlram(int64_t duration, std::function<void (void)>&& callback ,int64_t repeated);
    void removeAlarm(std::list<alarm>::iterator itemIndex);
    
    int64_t convertTime(unsigned int seconds, unsigned int microseconds);

private:
    int64_t                m_lastTime;
    int64_t                m_PerfFreq;
    double                 m_TimeScale;
    double                 m_avgTimeDelta;
    double                 m_timeDeltas[MAX_SAMPLE_COUNT];
    unsigned long          m_SampleCount;

    unsigned long          m_FrameRate;       // Stores current framerate
    unsigned long          m_FPSFrameCount;   // Elapsed frames in any given second
    float                  m_FPSTimeElapsed;  // How much time has passed during FPS sample
    bool                   m_cap;
    
    std::list<alarm> m_alarms;

};

#endif  //_TIMER_H
