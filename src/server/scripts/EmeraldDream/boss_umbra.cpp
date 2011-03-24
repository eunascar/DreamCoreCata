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

static Position MovementPoint[] =
{
    {2667.385010f, -3271.108398f, 95.495941f, 0.092777f},    //Isidorus Posicion Intro 1
    {2685.518799f, -3266.415527f, 94.878540f, 0.996771f},    //Isidorus Posicion Intro 2
    {2699.969727f, -3250.528809f, 93.301346f, 0.931583f}     //Isidorus Posicion Intro 3
};

enum eEvents
{
    EVENT_PAIN_AND_SUFFERING    = 1,
    EVENT_SHADOW_BOLT           = 2
};

enum eSpells
{
    SPELL_VISUAL                = 65633,
    AURA_VISUAL_1               = 54141,
    AURA_VISUAL_2               = 50772,
    AURA_VISUAL_3               = 45213,
    SPELL_PAIN_AND_SUFFERING    = 65719,
    SPELL_SHADOW_BOLT           = 72504
};

enum eYells
{
// Isidorus
    SAY_LAUGH                = 0,
    SAY_INTRO_1              = 1,
    SAY_INTRO_2              = 2,
    SAY_REVERENCE_EMOTE_1    = 3,
    SAY_INTRO_3              = 4,
    SAY_INTRO_5              = 5,
    SAY_OUTRO_1              = 6,
    SAY_REVERENCE_EMOTE_2    = 7,
// Umbra
    SAY_INTRO_4              = 0,
    SAY_AGROO                = 1
};

#define UMBRA           200 
#define MODEL_PRIEST    23158

Creature* pUmbra;
Creature* pIsidorus;

class boss_umbra : public CreatureScript
{
    public:
        boss_umbra()
            : CreatureScript("boss_umbra")
        {
        }

        struct boss_umbraAI : public BossAI
        {
    	    boss_umbraAI(Creature* creature) : BossAI(creature, DATA_UMBRA)
    	    {
    	        instance = me->GetInstanceScript();
                pUmbra = me;
    	    }
        
            EventMap events;

    	    void Reset()
    	    {
                events.Reset();

    	        instance->SetBossState(DATA_UMBRA, NOT_STARTED);

                uiTimer = 1000;
    	    }

    	    void EnterCombat(Unit*) 
            { 
                Talk(SAY_AGROO);
                DoCast(me, AURA_VISUAL_1, true);
                DoCast(me, AURA_VISUAL_2, true);

                events.ScheduleEvent(EVENT_PAIN_AND_SUFFERING, 30000);
                events.ScheduleEvent(EVENT_SHADOW_BOLT, 10000);
            }

    	    void JustDied(Unit*)
    	    {
                pIsidorus->setDeathState(JUST_ALIVED);

                DoCast(me, AURA_VISUAL_1, false);
                DoCast(me, AURA_VISUAL_2, false);

                if(instance)
                    instance->SetBossState(DATA_UMBRA, DONE);
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
                        case EVENT_PAIN_AND_SUFFERING:
                            DoCast(SPELL_PAIN_AND_SUFFERING);
                            events.ScheduleEvent(EVENT_PAIN_AND_SUFFERING, 50000);
                            return;

                        case EVENT_SHADOW_BOLT:
                        {
                            DoCast(SPELL_SHADOW_BOLT);
                            events.ScheduleEvent(EVENT_SHADOW_BOLT, 15000);
                            return;
                        }
                    }
                }

    		DoMeleeAttackIfReady();
    	    }

        private:
            InstanceScript* instance;
           
            uint32 uiTimer;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
    	    return new boss_umbraAI(creature);
        }
};

class npc_emerald_isidorus : public CreatureScript
{
    public:
        npc_emerald_isidorus() : CreatureScript("npc_emerald_isidorus") { }

        struct npc_emerald_isidorusAI : public ScriptedAI
        {
    	    npc_emerald_isidorusAI(Creature* creature) : ScriptedAI(creature)
    	    {
    	        instance = me->GetInstanceScript();
                pIsidorus = me;
    	    }

            bool bIntro;
            bool bFinal;

            void Reset()
            {
                uiTimer = 1000;
                uiPhase = 1;
                uiPhasef = 1;

                bIntro = false;
                bFinal = false;

                me->setFaction(35);
                me->SetReactState(REACT_PASSIVE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            }

            void Intro ()
            {
                if(uiTimer)
                {
                    switch(uiPhase)
                    {
                        case 1:
                            instance->SetBossState(DATA_UMBRA, IN_PROGRESS);
                            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                            me->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
                            me->SetSpeed(MOVE_WALK, 1.2f);
                            me->GetMotionMaster()->MovePoint(0, MovementPoint[0]);                    
                            uiTimer = 10000;
                            ++uiPhase;
                            break;
                        case 2:
                            me->GetMotionMaster()->MovePoint(0, MovementPoint[1]);
                            uiTimer = 7000;
                            ++uiPhase;
                            break;
                        case 3:
                            me->GetMotionMaster()->MovePoint(0, MovementPoint[2]);
                            uiTimer = 6000;
                            ++uiPhase;
                            break;
                        case 4:
                            me->setFaction(14);
                            me->SetReactState(REACT_PASSIVE);
                            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                            Talk(SAY_LAUGH);
                            uiTimer = 3000;
                            ++uiPhase;
                            break;
                        case 5:
                            Talk(SAY_INTRO_1);
                            uiTimer = 5000;
                            ++uiPhase;
                            break;
                        case 6:
                            DoCast(me, SPELL_VISUAL);
                            uiTimer = 5000;
                            ++uiPhase;
                            break;
                        case 7:
                            pUmbra->SetVisible(true);
                            pUmbra->SetUInt32Value(UNIT_NPC_EMOTESTATE, 15);
                            uiTimer = 2000;
                            ++uiPhase;
                            break;
                        case 8:
                            pUmbra->SetUInt32Value(UNIT_NPC_EMOTESTATE, 0);
                            Talk(SAY_INTRO_2);
                            uiTimer = 10000;
                            ++uiPhase;
                            break;
                        case 9:
                            Talk(SAY_REVERENCE_EMOTE_1);
                            uiTimer = 2000;
                            ++uiPhase;
                            break;
                        case 10:
                            Talk(SAY_INTRO_3);
                            uiTimer = 10000;
                            ++uiPhase;
                            break;
                        case 11:
                            Talk(SAY_INTRO_4);
                            uiTimer = 8000;
                            ++uiPhase;
                            break;
                        case 12:
                            Talk(SAY_INTRO_5);
                            pUmbra->SetReactState(REACT_AGGRESSIVE);
                            pUmbra->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                            me->setDeathState(JUST_DIED);
                            uiTimer = 5000;
                            ++uiPhase;
                            break;
                    }
                }
            }

            void Final ()
            {
                if(uiTimer)
                {
                    switch(uiPhasef)
                    {
                        case 1:
                            pIsidorus->SetDisplayId(MODEL_PRIEST); 
                            Talk(SAY_OUTRO_1);
                            uiTimer = 8000;
                            ++uiPhasef;
                            break;
                        case 2:
                            DoCast(me, AURA_VISUAL_3);
                            uiTimer = 3000;
                            ++uiPhasef;
                            break;
                        case 3:
                            me->setFaction(35);
                            uiTimer = 2000;
                            ++uiPhasef;
                            break;
                        case 4:
                            Talk(SAY_REVERENCE_EMOTE_2);
                            uiTimer = 5000;
                            ++uiPhasef;
                            break;
                    }
                }
            }
           
            void UpdateAI(const uint32 diff)
    	    {
    	        if (uiTimer <= diff)
                {
                    if (bIntro)
                        Intro();

                    if (bFinal)
                        Final();
                    
                    if (instance->GetBossState(DATA_UMBRA) == DONE)
                        bFinal = true;
                }
                else (uiTimer -= diff);
    	    }

        private:
            InstanceScript* instance;

            uint32 uiTimer;
            uint32 uiPhase;
            uint32 uiPhasef;
        };

        bool OnGossipHello(Player* player, Creature* creature)
        {
            InstanceScript* instance = creature->GetInstanceScript();
            if (!instance)
                return false;

            if ((instance->GetBossState(DATA_HYOTON) == DONE && instance->GetBossState(DATA_FIREMIST) == DONE && instance->GetBossState(DATA_UMBRA) == NOT_STARTED) || player->isGameMaster())
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Proseguir con el Siguiente Evento", GOSSIP_SENDER_MAIN, UMBRA);
            
            player->SEND_GOSSIP_MENU(10600, creature->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 uiSender, uint32 uiAction)
        {
            player->PlayerTalkClass->ClearMenus();
            if (uiSender != GOSSIP_SENDER_MAIN)
                return false;

            if (!player->getAttackers().empty())
                return false;

            switch(uiAction)
            {
	            case UMBRA:
                    CAST_AI(npc_emerald_isidorus::npc_emerald_isidorusAI, creature->AI())->bIntro = true;
                    player->CLOSE_GOSSIP_MENU();
                    break;
            }
            return true;
        }

        CreatureAI* GetAI(Creature* creature) const
        {
    	    return new npc_emerald_isidorusAI(creature);
        }
};

void AddSC_boss_umbra()
{
    new boss_umbra();
    new npc_emerald_isidorus();
}
