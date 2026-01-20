namespace offsets
{
    inline uintptr_t base = (uintptr_t)GetModuleHandleA("GameAssembly.dll");
    inline uintptr_t GameAssembly = 0;

    // localplayer
    namespace localplayer
    {
        inline uintptr_t SetfieldOfView = 0x2C841A0; // fov - unityengine_camera$$set_fieldofview
        inline uintptr_t GetStackLimit = 0x997CC0; // stack limit - scheduleone_itemframework_iteminstance$$get_stacklimit
        inline uintptr_t CanTakeDamage = 0x664850; // can take damage - scheduleone_playerscripts_health_playerhealth$$get_cantakedamage
        inline uintptr_t RpcTakeDamage = 0x663110; // rpc take damage - scheduleone_playerscripts_health_playerhealth$$rpctakedamage
        inline uintptr_t GrassUpdate = 0x7B4F40; // stylizedgrassdemo_playercontroller$$update
    }

    // debug
    namespace debug
    {
        inline uintptr_t DebugValue = 0xAADD90; // debug - scheduleone_debug$$debugvalue
    }

    // unity
    namespace unity
    {
        inline uintptr_t SetLockState = 0x2CA5710; // cursor lock - unityengine_cursor$$set_lockstate
        inline uintptr_t SetVisible = 0x2CA5750; // cursor visible - unityengine_cursor$$set_visible
        inline uintptr_t WorldToScreenPoint = 0x2C82EF0; // w2s - unityengine_camera$$worldtoscreenpoint
        inline uintptr_t GetTransform = 0x2CBA530; // transform - unityengine_component$$get_transform
        inline uintptr_t GetPosition = 0x2CCEAD0; // position - unityengine_transform$$get_position
        inline uintptr_t GetName = 0x2CC20E0; // name - unityengine_gameobject$$get_name
        inline uintptr_t GetRotation = 0x2CCEC40; // rotation - unityengine_transform$$get_rotation
    }

    // casino
    namespace casino
    {
        inline uintptr_t GetRandomSymbol = 0x7EE610; // reels - scheduleone_casino_slotmachine_slotmachinereel$$getrandomsymbol
        inline uintptr_t GetCurrentBet = 0x7F0870; // bet - scheduleone_casino_slotmachine_slotmachinecontroller$$get_currentbet
    }

    // equippable
    namespace equippable
    {
        inline uintptr_t TrashGrabberGetCapacity = 0x8B4AD0; // capacity - scheduleone_equipping_equippable_trashgrabber$$getcapacity
    }

    // player
    namespace player
    {
        inline uintptr_t PlayerUpdate = 0x642620; // player list - scheduleone_playerscripts_player$$update

        // offsets
        inline uintptr_t StaticPlayerList = 0x0; // public static list<player> players;
        inline uintptr_t ListItems = 0x10; // internal array buffer
        inline uintptr_t ListSize = 0x18; // current count
        inline uintptr_t ArrayStart = 0x20; // start of elements in array
        inline uintptr_t PointerStep = 0x8; // size of x64 pointer

        inline uintptr_t PlayerMovementUpdate = 0x66A720; // movement - scheduleone_playerscripts_playercontroller$$update
        inline uintptr_t TakeDamage = 0x6F8CA0; // damage - scheduleone_playerscripts_health_playerhealth$$takedamage

        // verified offsets
        inline uintptr_t moveSpeed = 0x38; // multiplier
        inline uintptr_t verticalVelocity = 0x9C; // jump/gravity
        inline uintptr_t isGrounded = 0xC8; // infinite jump flag
        inline uintptr_t stamina = 0x54; // stamina value
    }

    // atm
    namespace atm
    {
        inline uintptr_t GetRelevantBalance = 0x973AE0; // balance - scheduleone_ui_atm_atminterface$$get_relevantbalance
        inline uintptr_t WithdrawButtonPressed = 0x973820; // withdraw - scheduleone_ui_atm_atminterface$$withdrawbuttonpressed
        inline uintptr_t ProcessTransaction = 0x972330; // transaction - scheduleone_ui_atm_atminterface$$processtransaction
        inline uintptr_t GetAmountFromIndex = 0x971E90; // amount - scheduleone_ui_atm_atminterface$$getamountfromindex
        inline uintptr_t GetRemainingAllowedDeposit = 0x973BC0; // remaining - scheduleone_ui_atm_atminterface$$get_remainingalloweddeposit
    }

    // dealer
    namespace dealer
    {
        inline uintptr_t DealerPriceMultiplier = 0x6D40A0; // multiplier - scheduleone_economy_dealer$$getpricemultiplier
    }

    // item
    namespace item
    {
        inline uintptr_t ItemGetValue = 0x70E5C0; // value - scheduleone_items_item$$get_value
    }

    // npc
    namespace npc
    {
        inline uintptr_t MovementUpdate = 0x7254D0; // npc move - npc_npcmodel$$movementupdate
        inline uintptr_t AddCash = 0x704AC0; // npc cash - npc_npcmodel$$addcash
        inline uintptr_t CanSeeTarget = 0x7A9520; // awareness - scheduleone_npcs_npcawareness$$canseetarget 
    }

    // world
    namespace world
    {
        inline uintptr_t GetTempMultiplier = 0xA3FA20; // growth - scheduleone_growing_growcontainer$$gettemperaturegrowthmultiplier
    }

    // skating
    namespace skating
    {
        inline uintptr_t EffectsFixedUpdate = 0xAC2CA0; // skate update - scheduleone_skating_skateboardeffects$$fixedupdate
        inline uintptr_t boardInstance = 0x20;

        inline uintptr_t currentSpeed = 0x118; // float
        inline uintptr_t topSpeed = 0x214; // float: max kmh forward
        inline uintptr_t reverseTopSpeed = 0x1A8; // float: max kmh backward
        inline uintptr_t pushForce = 0x218; // float: acceleration per kick
        inline uintptr_t pushDuration = 0x228; // float: how long acceleration lasts after kicking

        // handling
        inline uintptr_t turnForce = 0x188; // float: how hard it turns
        inline uintptr_t turnChangeRate = 0x18C; // float: response time
        inline uintptr_t turnReturnRate = 0x190; // float: snappiness
        inline uintptr_t turnSpeedBoost = 0x194; // float: speed gained while turning
        inline uintptr_t rotationClamp = 0x1B8; // float: max rotation speed

        // physics
        inline uintptr_t gravity = 0x1A0; // float: downward force
        inline uintptr_t brakeForce = 0x1A4; // float: rolling resistance
        inline uintptr_t slowOnTerrain = 0x1BC; // bool: does grass/dirt slow you down?
        inline uintptr_t frictionEnabled = 0x1BD; // bool: master friction switch
        inline uintptr_t longFriction = 0x1C8; // float: longitudinal grip
        inline uintptr_t latFriction = 0x1CC; // float: lateral grip

        // jump
        inline uintptr_t jumpCharge = 0x120; // float: current charge
        inline uintptr_t jumpForce = 0x1D0; // float: base vertical power
        inline uintptr_t jumpDurMin = 0x1D4; // float: minimum time force is applied
        inline uintptr_t jumpDurMax = 0x1D8; // float: maximum time force is applied
        inline uintptr_t jumpFwdBoost = 0x1F8; // float: forward velocity added on jump

        // air control
        inline uintptr_t airMoveEnabled = 0x238; // bool: can you steer while airborne?
        inline uintptr_t airMoveForce = 0x23C; // float: power of air steering

        // hover
        inline uintptr_t hoverForce = 0x1FC; // float: upward lifting force
        inline uintptr_t hoverRayLen = 0x200; // float: how far down to look for ground
        inline uintptr_t hoverHeight = 0x204; // float: target floating height
    }

    // police
    namespace police
    {
        inline uintptr_t CanInvestigatePlayer = 0x7E5F10; // police - scheduleone_police_policeofficer$$caninvestigateplayer
        inline uintptr_t CanInvestigate = 0x7E5FE0; // police - scheduleone_police_policeofficer$$caninvestigate
        inline uintptr_t OfficerUpdate = 0x7E9D30; // police - scheduleone_police_policeofficer$$update

        // behaviour
        inline uintptr_t UpdateLethalBehaviour = 0x76CDC0; // pursuit - scheduleone_npcs_behaviour_pursuitbehaviour$$updatelethalbehaviour
        inline uintptr_t UpdateNonLethalBehaviour = 0x76CEA0; // pursuit - scheduleone_npcs_behaviour_pursuitbehaviour$$updatenonlethalbehaviour
        inline uintptr_t UpdateArrestBehaviour = 0x76C2D0; // pursuit - scheduleone_npcs_behaviour_pursuitbehaviour$$updatearrestbehaviour
    }

    // law
    namespace law
    {
        inline uintptr_t SetCheckpointEnabled = 0x60CBB0; // checkpoint - scheduleone_law_checkpointmanager$$setcheckpointenabled
    }

    // itemframework
    namespace ItemFramework
    {
        inline uintptr_t SetBalance = 0x994440; // money - scheduleone_itemframework_cashinstance$$setbalance
        inline uintptr_t SetBankBalance = 0x994210; // bank - scheduleone_itemframework_bankinstance$$setbalance
    }
}