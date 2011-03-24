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

class boss_krityus : public CreatureScript
{
    public:
        boss_krityus()
            : CreatureScript("boss_krityus")
        {
        }

        struct boss_krityusAI : public BossAI
        {
    	    boss_krityusAI(Creature* creature) : BossAI(creature, DATA_KRITYUS)
    	    {
    	        instance = me->GetInstanceScript();
    	    }

    	    void Reset()
    	    {
    	        instance->SetBossState(DATA_KRITYUS, NOT_STARTED);
    	    }

    	    void EnterCombat(Unit*)
    	    {
                instance->SetBossState(DATA_KRITYUS, IN_PROGRESS);
    	    }

            void JustDied(Unit*)
    	    {
                if(instance)
                    instance->SetBossState(DATA_KRITYUS, DONE);
    	    }

    	    void UpdateAI(const uint32 /*diff*/)
    	    {
    	        if(!UpdateVictim())
    	            return;

    		    DoMeleeAttackIfReady();
    	    }

        private:
            InstanceScript* instance;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
    	    return new boss_krityusAI(creature);
        }
};

void AddSC_boss_krityus()
{
    new boss_krityus();
}
