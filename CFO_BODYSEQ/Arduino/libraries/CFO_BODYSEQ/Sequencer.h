/*
 Sequencer.h - Friction Music library
 Copyright (c) 2014 Science Friction.
 All right reserved.
 
 This library is free software: you can redistribute it and/or modify
 it under the terms of the GNU Lesser Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your optionosc1modShape_ptr) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser Public License for more details.
 
 You should have received a copy of the GNU Lesser Public License
 along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 + author: gauthiier
 + contact: d@gauthiier.info
 */

#pragma once

#define MAX_SEQ 3
#define MAX_STEPS 16
#define INSTR_SEQ 4
#define ISEQ_NBR_STEPS 32


#define TICKS_PER_QUARTER_NOTE 24 //

enum SUBDIV {
    NOTE_0,
    NOTE_1 = (TICKS_PER_QUARTER_NOTE * 4),
    NOTE_1DOT = (TICKS_PER_QUARTER_NOTE * 3),
    NOTE_2 = (TICKS_PER_QUARTER_NOTE * 2),
    NOTE_3 = ((TICKS_PER_QUARTER_NOTE * 3) / 2),
    NOTE_4 = (TICKS_PER_QUARTER_NOTE * 1),
    NOTE_6 = ((TICKS_PER_QUARTER_NOTE * 2) / 3),
    NOTE_8 = (TICKS_PER_QUARTER_NOTE / 2),
    NOTE_12 = (TICKS_PER_QUARTER_NOTE / 3),
    NOTE_16 = (TICKS_PER_QUARTER_NOTE / 4),
    NOTE_24 = (TICKS_PER_QUARTER_NOTE / 6),
    NOTE_32 = (TICKS_PER_QUARTER_NOTE / 8),
    NOTE_48 = (TICKS_PER_QUARTER_NOTE / 12),
    NOTE_64 = (TICKS_PER_QUARTER_NOTE / 16),
    NOTE_96 = (TICKS_PER_QUARTER_NOTE / 24)
//    NOTE_128 = (TICKS_PER_QUARTER_NOTE / 32),
//    NOTE_192 = (TICKS_PER_QUARTER_NOTE / 48),
//    NOTE_256 = (TICKS_PER_QUARTER_NOTE / 64),
//    NOTE_384 = (TICKS_PER_QUARTER_NOTE / 96)
};

enum SEQ_LOOP_TYPE {
    ONCE = 0,
    LOOP = 1,
    PINGPONG = 2
};

#define REVERSE true

typedef void (*func_cb)(void);

class seq;
class iseq;

class MSequencer {
public:
    void init(int bpm);
    void timerClock();
    void midiClock();
    void tick();
    void update();
    void midiStart();
    void midiContinue();
    void midiStop();
    void sequencerStart();
    void sequencerContinue();
    void sequencerStop();
    
    int newSequence(SUBDIV subdiv, func_cb cb);
    int newSequence(SUBDIV subdiv, int steps, SEQ_LOOP_TYPE loop);
    int newSequence(SUBDIV subdiv, int steps, SEQ_LOOP_TYPE loop, bool reverse);
    
    bool stopSequence(int index);
    bool startSequence(int index);
    bool continueSequence(int index);

    void setMidiClock(bool mc);
    bool getMidiClock();
    
    void setbpm(int v);
    int getbpm();
    
    bool setSteps(int index, int s);
    int getSteps(int index);
    
    bool setPosition(int index, int p);
    int getPosition(int index);
    
    bool setBegin(int index, int b);
    int getBegin(int index);
    
    bool setEnd(int index, int e);
    int getEnd(int index);
    
    bool setReverse(int index, bool r);
    bool getReverse(int index);
    
    bool setSubdiv(int index, SUBDIV subdiv);
    int getSubdiv(int index);
    
    bool setLoopType(int index, SEQ_LOOP_TYPE loop);
    int getLoopType(int index);
    
    bool setCallback(int index, func_cb cb);
    func_cb getCallback(int index);
    
    bool insertNotes(int index, int notes[], int numNotes, int newPosition);


private:
    seq* _sequences[MAX_SEQ];
    int _bpm;
    int _bpmInClockTicks;
    bool _midiClock;
    unsigned long clockTick;
    unsigned long timeNow;
    unsigned long lastTime;
    unsigned long tickTime;

    
};


class iSequencer {
public:
    void init(int bpm);
    void update();
    
    int newSequence(SUBDIV subdiv, int steps, SEQ_LOOP_TYPE loop);
    
    bool stopSequence(int index);
    bool startSequence(int index);
    
    bool setSequenceSubdiv(int index, SUBDIV subdiv);
    
    int getSequenceSubdiv(int index);
    
//    bool setCallback(int index, func_cb cb);
//    func_cb getCallback(int index);
    
    unsigned long clockStep;
    
    void setbpm(int v);
    int getbpm();
    
    
    
private:
    iseq* _sequences[INSTR_SEQ];
    int _bpm;
    int _bpmInClockSteps;
    
    
};


class seq {
    
    friend class MSequencer;
    
private:
    
    seq(int id, SUBDIV subdiv, func_cb cb);
    seq(int id, SUBDIV subdiv, int steps, SEQ_LOOP_TYPE loop);
    seq(int id, SUBDIV subdiv, int steps, SEQ_LOOP_TYPE loop, bool reverse);
    
    int _id;
    int _steps;
    int _begin;
    int _end;
    int _position;
    bool _reverse;
    bool _stopped;
    SUBDIV _subdiv;
    SEQ_LOOP_TYPE _loop;
    
    
    int _notes[MAX_STEPS];
    int _velocity[MAX_STEPS];
    int _ccNumbers[MAX_STEPS];
    int _ccValues[MAX_STEPS];

    unsigned long step;
    
    void trigger();

    void setsteps(int s);
    int getsteps();
    
    void setposition(int p);
    int getposition();
    
    void setbegin(int b);
    int getbegin();
    
    void setend(int e);
    int getend();
    
    void setreverse(bool reverse);
    bool getreverse();
    
    void setsubdiv(SUBDIV v);
    SUBDIV getsubdiv();
    
    void setlooptype(SEQ_LOOP_TYPE loop);
    SEQ_LOOP_TYPE getlooptype();
    
    void callback(func_cb cb);
    
    func_cb _callback;
    
    void insertnotes(int notes[], int numNotes, int newPosition);
};


extern MSequencer Sequencer;
