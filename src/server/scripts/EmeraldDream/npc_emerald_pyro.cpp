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
                    instance->SetData(DATA_PYRO_DRAKE,instance->GetData(DATA_PYRO_DRAKE)+4);
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

void AddSC_npc_emerald_pyro()
{
    new npc_emerald_pyro();
}
