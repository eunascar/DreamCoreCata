/*
 * Copyright (C) 2008-2011 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2010-2011 Chronos Server <http://chronoserverwow.net/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScriptPCH.h"
#include "emerald_dream.h"

enum eSpells
{
    SPELL_FLAME_JETS	= 62680,
    SPELL_BURNING_FURY 	= 66721
};

enum Events
{
    EVENT_FLAME_JETS      = 1,
    EVENT_BURNING_FURY    = 2
};

class boss_firemist : public CreatureScript
{
    public:
        boss_firemist()
            : CreatureScript("boss_firemist")
        {
        }

        struct boss_firemistAI : public BossAI
        {
    	    boss_firemistAI(Creature* creature) : BossAI(creature, DATA_FIREMIST)
    	    {
    	        instance = me->GetInstanceScript();
    	    }
 
            EventMap events;

    	    void Reset()
    	    {
                events.Reset();

    	        instance->SetBossState(DATA_FIREMIST, NOT_STARTED);
    	    }

    	    void EnterCombat(Unit*)
    	    {
                instance->SetBossState(DATA_FIREMIST, IN_PROGRESS);

                events.ScheduleEvent(EVENT_FLAME_JETS, 250000);
                events.ScheduleEvent(EVENT_BURNING_FURY, 300000);
    	    }

    	    void JustDied(Unit*)
    	    {
                if(instance)
                    instance->SetBossState(DATA_FIREMIST, DONE);
    	    }

    	    void UpdateAI(const uint32 diff)
    	    {
    	        if(!UpdateVictim())
    	            return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STAT_CASTING))
                    return;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                        case EVENT_FLAME_JETS:
                            DoCast(SPELL_FLAME_JETS);
                            events.ScheduleEvent(EVENT_FLAME_JETS, 350000);
                            return;

                        case EVENT_BURNING_FURY:
                        {
                            DoCast(me, SPELL_BURNING_FURY);
                            events.ScheduleEvent(EVENT_BURNING_FURY, 250000);
                            return;
                        }
                    }
                }

    		DoMeleeAttackIfReady();
    	    }

        private:
            InstanceScript* instance;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
    	    return new boss_firemistAI(creature);
        }
};

class npc_emerald_pyro : public CreatureScript
{
    public:
        npc_emerald_pyro()
            : CreatureScript("npc_emerald_pyro")
        {
        }

        struct npc_emerald_pyroAI : public ScriptedAI
        {
    	    npc_emerald_pyroAI(Creature* creature) : ScriptedAI(creature)
    	    {
    	        instance = me->GetInstanceScript();
    	    }

    	    void JustDied(Unit* /*Who*/)
            {
                if (instance)
                    instance->SetData(DATA_PYRO_DRAKE, instance->GetData(DATA_PYRO_DRAKE) + 1);
            }

            void UpdateAI(const uint32 /*diff*/)
            {
                if (!UpdateVictim())
                    return;

                DoMeleeAttackIfReady() ;
            }

        private:
            InstanceScript* instance;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
    	    return new npc_emerald_pyroAI(creature);
        }
};

void AddSC_boss_firemist()
{
    new boss_firemist();
    new npc_emerald_pyro();
}
