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
    SPELL_WHITEOUT         = 72096,
    SPELL_FROST_BREATH     = 72641
};

enum Events
{
    EVENT_WHITEOUT         = 1,
    EVENT_BREATH           = 2
};

class boss_hyoton : public CreatureScript
{
    public:
        boss_hyoton()
            : CreatureScript("boss_hyoton")
        {
        }

        struct boss_hyotonAI : public BossAI
        {
    	    boss_hyotonAI(Creature* creature) : BossAI(creature, DATA_HYOTON) { }

            EventMap events;

    	    void Reset()
    	    {
                events.Reset();

    	        instance->SetBossState(DATA_HYOTON, NOT_STARTED);
    	    }

    	    void EnterCombat(Unit*)
    	    {
                instance->SetBossState(DATA_HYOTON, IN_PROGRESS);
                
                events.ScheduleEvent(EVENT_WHITEOUT, 150000);
                events.ScheduleEvent(EVENT_BREATH, 180000);
    	    }

    	    void JustDied(Unit*)
    	    {
                if(instance)
                    instance->SetBossState(DATA_HYOTON, DONE);
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
                        case EVENT_WHITEOUT:
                            DoCast(me, SPELL_WHITEOUT);
                            events.ScheduleEvent(EVENT_WHITEOUT, 250000);
                            return;

                        case EVENT_BREATH:
                        {
                            DoCastAOE(SPELL_FROST_BREATH);
                            events.ScheduleEvent(EVENT_BREATH, 280000);
                            return;
                        }
                    }
                }

    		    DoMeleeAttackIfReady();
    	    }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
    	    return new boss_hyotonAI(creature);
        }
};

class npc_emerald_aqua_ghost : public CreatureScript
{
    public:
        npc_emerald_aqua_ghost()
            : CreatureScript("npc_emerald_aqua_ghost")
        {
        }

        struct npc_emerald_aqua_ghostAI : public ScriptedAI
        {
    	    npc_emerald_aqua_ghostAI(Creature* creature) : ScriptedAI(creature)
    	    {
    	        instance = me->GetInstanceScript();
    	    }

    	    void JustDied(Unit* /*Who*/)
            {
                if (instance)
                    instance->SetData(DATA_AQUA_GHOST,instance->GetData(DATA_AQUA_GHOST) + 1);
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
    	    return new npc_emerald_aqua_ghostAI(creature);
        }
};

class npc_emerald_aqua_lekion : public CreatureScript
{
    public:
        npc_emerald_aqua_lekion() : CreatureScript("npc_emerald_aqua_lekion") { }

        struct npc_emerald_aqua_lekionAI : public ScriptedAI
        {
    	    npc_emerald_aqua_lekionAI(Creature* creature) : ScriptedAI(creature)
    	    {
    	        instance = me->GetInstanceScript();
    	    }

    	    void JustDied(Unit* /*Who*/)
            {
                if (instance)
                    instance->SetData(DATA_AQUA_LEKION,instance->GetData(DATA_AQUA_LEKION)+1);
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
    	    return new npc_emerald_aqua_lekionAI(creature);
        }
};

void AddSC_boss_hyoton()
{
    new boss_hyoton();
    new npc_emerald_aqua_ghost();
    new npc_emerald_aqua_lekion();
}
