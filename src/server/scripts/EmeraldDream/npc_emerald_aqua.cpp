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
                    instance->SetData(DATA_AQUA_GHOST,instance->GetData(DATA_AQUA_GHOST)+1);
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

void AddSC_npc_emerald_aqua()
{
    new npc_emerald_aqua_ghost();
    new npc_emerald_aqua_lekion();
}
