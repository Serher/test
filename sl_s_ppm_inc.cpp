//bZ 28.03.11
#include "sl_s_ppm_inc2"
#include "x2_inc_itemprop"
#include "tob_rem_temp_ite"


const string PPM_CRED = "<cя  >";
const string PPM_CYELLOW = "<cяя >";
const string PPM_CWHITE = "<cяяя>";
const string PPM_CMAGENTA = "<cя я>";
const string PPM_CGREEN = "<c я >";
const string PPM_CBLUE = "<c  я>";
const string PPM_CCYAN = "<c яя>";
const string PPM_CORANGE = "<cю“>";
const string PPM_CVIOLET = "<chF°>";

const string PPM_CFin = "</c>";



//Merge constants
const string MERGE_A = "_1_0_5_";
const string MERGE_I = "_2_6_7_8_9_10_";
const string MERGE_W = "_4_";
const string MERGE_H = "_3_";


object PPM_GetFormTemplateObject(object oPC); //19.08.13


void PPM_AddPolyMorphProps(object oPC, string sSkinResref, float fDuration = 20.0);


void CheckSkin(object oPC, object oSkin);


void PPM_ChangeAppearanceTo(int nAppearance = -1, object oPC = OBJECT_SELF);


void PPM_ApprearanceCheck(object oPC, int nOriginalApp, int nChangeToOriginal = TRUE);


int PPM_CreateSaves(object oPC);


void PPM_Remorph(object oPC);


void PPM_LockAllSlots(object oPC);


void PPM_UnlockAllSlots(object oPC);


void PPM_LockItem(object oItem);


void PPM_DestroyEquipedPPMItems(object oPC);


void PPM_DestroyPPMItemsInInventory(object oPC);


void PPM_EqiupAndLockNaturalItem(object oPC, object oItem, int nInventorySlot);


void PPM_NaturalWeapon(object oPC, int nPolymorphType);


void PPM_ShifterWeapon(object oPC, string sResrefRighthandWeapon, int nRSlot = INVENTORY_SLOT_RIGHTHAND, string sResrefLefthandWeapon = "", int nLSlot = INVENTORY_SLOT_LEFTHAND);


void PPM_AddPropsFromItemToSkin(object oItem, object oPC, float fDuration);


int PPM_GetItemSlotIsInList(int nInventorySlot, string sMergeSlotList);


void PPM_CheckSlot(int nInventorySlot, object oPC, string sMergeSlotList, object oSafe, float fDuration);


void PPM_SaveItemPropsAndUnequipItemsIntoSafe(object oPC, string sMergeSlotList, float fDuration);


void PPM_DebugForSaves(object oPC, object oSafe, int nPassedStage, object oToken);


void PPM_RemoveFormEffects(object oPC);


void PPM_AddWeaponProps(object oPC, float fDuration);





//////////////////////////////////////////////////////////////////////////


void PPM_RemorphMessage(object oPC);


//from "sl_s_inc2"
void PPM_slDelayedCopyItem(object oItem, object oPC, int nVar = TRUE, int nCurse = TRUE, /*bZ 04.03.12*/int NeedWeaponLink = FALSE, int nEquip = FALSE);

//from "sl_s_inc2"
void PPM_slRecreateItem(object oItem, object oPC, int nVar = TRUE, /*bZ 04.03.12*/int NeedWeaponLink = FALSE, int nEquip = FALSE);


void PPM_ClearSystemOnEnter(object oPC);


//"sl_s_ppm_inc"
//PseudoPolyMorph. Removes PseudoPolyMorph effects from oPC.
//void PPM_RemoveForm(object oPC);


//"sl_s_ppm_inc"
//PseudoPolyMorph. Transform oPC into nPolymorphType form.
void PPM(object oPC, int nPolymorphType, float fDuration);



//void //DBM_Test(string sScript, string sFunction = "", string sInfo = "");






void PPM_FinishStage(object oPC);


void PPM_ApplyEffectPseudoPoly(object oPC, int nForm, float fDuration);


void PPM_ManageParameters(object oPC, int nForm, float fDuration);


void PPM_ClearParameters(object oPC);


void PPM_ApplyMiscEffects(object oPC, float fDuration);


void PPM_RemoveForm_NEW(object oPC);


void PPM_EquipItemsBackAddDestroySaves_NEW(object oPC);


void PPM_CheckItemsEquiped(object oPC);


void PPM_SaveItemOnToken(object oToken, object oItem, int InventorySlot);


void PPM_DeleteItemFromToken(object oPC, int nInventorySlot);


object PPM_RestoreItemFromToken(object oPC, int nInventorySlot);

int GetArcaneLevel(object oPC);
int isRakshasaForm(object oPC);
int MaxRakshasaAllowedSpells(object oPC);
string GetResRefForRakshasaSpellItem(int nSpell);
int isItemInInventory(string sItemResRef, object oPC);
int isSpellAllowedForArcaneRakshasa(int nSpell);
void ClearRakshasaSpells(object oPC);
string GetSpellsForArcaneRakshasa();
string GetSpellsForItemFOAS();
string GetSpellsForItemBS();
string GetEpicSpellsForAR();

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////



void ClearRakshasaSpells(object oPC) {

    DeleteLocalInt(oPC,"rakshasa_total_spells");
    DeleteLocalString(oPC,"rakshasa_used_spells");                              //DBM("sl_s_ppm_inc", "ClearRakshasaSpells", "enter");


    //known issue when rakshasa casts ema and then morphs back to human
    //additional effects are there (crit immun etc)

    // clear EMA effects
    //effect eEffect = GetFirstEffect(oPC);
    // while (GetIsEffectValid(eEffect))
    // {
    //   //DBM("sl_s_ppm_inc", "ClearRakshasaSpells", "eff:" + IToS(GetEffectSpellId(eEffect)));

    //    if (GetEffectSpellId(eEffect) == SPELL_EPIC_MAGE_ARMOR) {
    //        RemoveEffect(oPC, eEffect);
    //    }
    //    eEffect = GetNextEffect(oPC);
    // }
}

int GetArcaneLevel(object oPC) {

   int nResult = 0;
   int nWiz = GetLevelByClass(CLASS_TYPE_WIZARD, oPC);
   int nSorc = GetLevelByClass(CLASS_TYPE_SORCERER, oPC);

   if (nWiz > nSorc) {
      nResult = nWiz;
   } else if (nWiz < nSorc) {
      nResult = nSorc;
   } else if (nWiz == nSorc) {
      nResult = nWiz;
   }

   return nResult;
}

int isRakshasaForm(object oPC) {
    object oToken = GetLocalObject(oPC, "TokenofPersistence");
    if (GetLocalInt(oToken, "isPolymorphed") == 88 || GetLocalInt(oToken, "isPolymorphed") == 89) {
        return TRUE;
    }

    return FALSE;
}

int MaxRakshasaAllowedSpells(object oPC) {
    int nArcaneLevels = GetArcaneLevel(oPC);

    return nArcaneLevels / 8;
}

string GetSpellsForArcaneRakshasa() {
    string sFOAS = GetSpellsForItemFOAS();
    string sBS = GetSpellsForItemBS();
    string sEpics = GetEpicSpellsForAR();
    return sFOAS + sBS + sEpics;
}

string GetEpicSpellsForAR() {
    // epic mage armor
    return "_639_";
}

// for item Fragment of ancient scroll
string GetSpellsForItemFOAS() {
    // order in string is the same
    // improved invis
    // bigbys interposing hand
    // stone to flesh
    // undeath to death
    // meteor swarm
    return "_88_459_486_528_116_";
}
// for item Bright Sphere
string GetSpellsForItemBS() {
    // order in string is the same
    // ironguts
    // balagarns iron horn
    // haste
    // find traps
    // elemental shield
    return "_522_436_78_377_47_";
}

int isSpellAllowedForArcaneRakshasa(int nSpell) {

    string sSpell = "_" + IntToString(nSpell) + "_";
    string sAllowedSpells = GetSpellsForArcaneRakshasa();

    if(FindSubString(sAllowedSpells, sSpell) >= 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

int isRakshasaCastAllowed(object oPC, int nSpell) {

    int nResult = FALSE;
    string sSpell = "_" + IntToString(nSpell) + "_";                            //DBM("sl_s_ppm_inc","isRakshasaCastAllowed","sSpell: " +sSpell);

    if (isRakshasaForm(oPC) && isSpellAllowedForArcaneRakshasa(nSpell)) {
        int nMaxSpellsAllowed = MaxRakshasaAllowedSpells(oPC);                  //DBM("sl_s_ppm_inc","isRakshasaCastAllowed","nMaxSpellsAllowed: " +IToS(nMaxSpellsAllowed));
        //object oToken = GetLocalObject(oPC, "TokenofPersistence");
        int nUsedSpells = GetLocalInt(oPC, "rakshasa_total_spells");         //DBM("sl_s_ppm_inc","isRakshasaCastAllowed","nUsedSpells: " +IToS(nUsedSpells));
        string sSpellAlreadyCast = GetLocalString(oPC, "rakshasa_used_spells");   //DBM("sl_s_ppm_inc","isRakshasaCastAllowed","sSpellAlreadyCast: " +sSpellAlreadyCast);
        string sItemForSpell = GetResRefForRakshasaSpellItem(nSpell);

        // it's an epic spell, no need to log it
        if (FindSubString(GetEpicSpellsForAR(), sSpell) >= 0) {
           nResult = TRUE;
        } else {

            if (!isItemInInventory(sItemForSpell, oPC)) {
               SendMessageToPC(oPC, "У вас нет особого предмета для использования заклинания!");
            } else {
                // player can cast another spell regarding his limits
                if (nMaxSpellsAllowed > nUsedSpells) {

                     // when player casting a new spell, we're updating counters and logging his casted spell
                     if (!(FindSubString(sSpellAlreadyCast, sSpell) >= 0)) {
                        SetLocalString(oPC, "rakshasa_used_spells" , sSpellAlreadyCast + sSpell);
                        SetLocalInt(oPC, "rakshasa_total_spells", nUsedSpells + 1);
                     }
                     nResult = TRUE;
                } else {
                    // when limit of spells reached, but player casts spell that was already casted
                    if (FindSubString(sSpellAlreadyCast, sSpell) >= 0) {
                        nResult = TRUE;
                    } else {
                        SendMessageToPC(oPC, "Вы не можете использовать более " + IntToString(nMaxSpellsAllowed) + " заклинаний!");
                    }
                }
            }
        }
    }
    return nResult;
}


string GetResRefForRakshasaSpellItem(int nSpell) {

    string sFOAS = GetSpellsForItemFOAS();
    string sBS = GetSpellsForItemBS();
    string sItem = "";

    string sSpell = "_" + IntToString(nSpell) + "_";


    if(FindSubString(sFOAS, sSpell) >= 0) {
        sItem = "sl_it_cl_rit";
    } else if (FindSubString(sBS, sSpell) >= 0) {
        sItem = "sl_it_cl_sym17";
    }


   return sItem;
}

int isItemInInventory(string sItemResRef, object oPC) {

   int nResult = FALSE;
   object oItem = GetFirstItemInInventory(oPC);

    while (GetIsObjectValid(oItem) == TRUE)
    {
        if (GetResRef(oItem) == sItemResRef)
        {
            nResult = TRUE;
            break;
        }
        oItem = GetNextItemInInventory(oPC);
    }
    return nResult;
}

object PPM_GetFormTemplateObject(object oPC)
{
    int nForm = GetLocalInt(oPC, "PPM_Form");
    string sModifiedForm = "";
    switch(nForm)
    {
        case 22:
        case 23:
        case 24:
        case 25:
        case 33:
        case 34:
        case 35:
        case 36:
        case 37:    nForm = 21; break;  //animals + Troll
        case 70:    nForm = 59; break;  //drow
        case 77:    nForm = 74; break;  //vampire
        case 86:    nForm = 85; break;  //azer
        case 88:
        case 89:
            nForm = 88; //rakshasa
            //DBM("sl_s_ppm_inc", "PPM_GetFormTemplateObject", "arcanelevel: " + IToS(GetArcaneLevel(oPC)));
            if (GetArcaneLevel(oPC) > 10) {
               sModifiedForm = "ma_";
            }
        break;
    }

    object oResult = GetObjectByTag("ppm_cr_" + sModifiedForm + IntToString(nForm));
    //DBM_Test("sl_s_ppm_inc","PPM_GetFormTemplateObject", "oResult" + OToS(oResult));
    return oResult;
}




void PPM_AddPolyMorphProps(object oPC, string sSkinResref, float fDuration = 20.0)
{
    object oPPMSkin;
    object oPC_Skin = GetItemInSlot(INVENTORY_SLOT_CARMOUR,oPC);                //DBM_Test("sl_s_ppm_inc","AddPolyMorphProps", "oPC_Skin" + OToS(oPC_Skin));
    if (!GetIsObjectValid(oPC_Skin))
    {
        oPC_Skin = CreateItemOnObject("x2_it_emptyskin",oPC);
        AssignCommand(oPC, ClearAllActions(TRUE));
        DelayCommand(0.01, AssignCommand(oPC, ActionEquipItem(oPC_Skin,INVENTORY_SLOT_CARMOUR)));   //DBM_Test("sl_s_ppm_inc","AddPolyMorphProps", "empty Skin" + OToS(oPC_Skin));
        PPM_LockItem(oPC_Skin);
    }

    object oSafe3 = GetLocalObject(oPC, "PPM_Safe3");                           //DBM_Test("sl_s_ppm_inc","AddPolyMorphProps", "oSafe3" + OToS(oSafe3));
    object oFormTemplate = PPM_GetFormTemplateObject(oPC);//19.08.13
    //DBM("sl_s_ppm_inc","PPM_AddPolyMorphProps", "oFormTemplate: " + OToS(oFormTemplate));
    if(GetIsObjectValid(oFormTemplate))
    {
        object oTemplateSkin = GetItemInSlot(INVENTORY_SLOT_CARMOUR, oFormTemplate);  //DBM_Test("sl_s_ppm_inc","AddPolyMorphProps", "oTemplateSkin" + OToS(oTemplateSkin));
        oPPMSkin = CopyItem(oTemplateSkin, oSafe3, TRUE);                       //DBM_Test("sl_s_ppm_inc","AddPolyMorphProps", "oPPMSkin on oFormTemplate" + OToS(oPPMSkin));
    }
    else
    {
        oPPMSkin = CreateItemOnObject(sSkinResref, oSafe3);
    }

    itemproperty ipProp = GetFirstItemProperty(oPPMSkin);
    while(GetIsItemPropertyValid(ipProp))
    {
        IPSafeAddItemProperty(oPC_Skin, ipProp, fDuration, X2_IP_ADDPROP_POLICY_KEEP_EXISTING);//bZ 28.08.13
        //AddItemProperty(DURATION_TYPE_TEMPORARY, ipProp, oPC_Skin, fDuration);
        ipProp = GetNextItemProperty(oPPMSkin);
    }
    DestroyObject(oPPMSkin, 0.3);

    DelayCommand(0.4, CheckSkin(oPC, oPC_Skin));
}


void CheckSkin(object oPC, object oSkin)
{
    object oPC_Skin = GetItemInSlot(INVENTORY_SLOT_CARMOUR,oPC);
    if(!GetIsObjectValid(oPC_Skin))
    {
        AssignCommand(oPC, ClearAllActions(TRUE));
        DelayCommand(0.01, AssignCommand(oPC, ActionEquipItem(oSkin,INVENTORY_SLOT_CARMOUR)));
        DelayCommand(0.2, CheckSkin(oPC, oSkin));
    }
    else
        PPM_FinishStage(oPC);
}





//bZ 27.08.13
void PPM_ChangePortrait(int nBackToOriginal = TRUE, object oPC = OBJECT_SELF)
{
    string sPortrait;
    object oToken = GetLocalObject(oPC, TOKEN_TAG);
    string sOriginalPortrait = GetLocalString(oToken, "OriginalPortrait");

    if(nBackToOriginal)
    {
        sPortrait = sOriginalPortrait;
    }
    else
    {
        if(sOriginalPortrait == "")
            SetLocalString(oToken, "OriginalPortrait", GetPortraitResRef(oPC));

        object oFormTemplate = PPM_GetFormTemplateObject(oPC);
        if(GetIsObjectValid(oFormTemplate))
            sPortrait = GetPortraitResRef(oFormTemplate);
    }

    if(sPortrait != "")
        SetPortraitResRef(oPC, sPortrait);
}



void PPM_ChangeAppearanceTo(int nAppearance = -1, object oPC = OBJECT_SELF)
{                                                                               //DBM_Test("sl_s_ppm_inc","ChangeAppearanceTo", "START with oPC" + OToS(oPC));
                                                                                //DBM_Test("sl_s_ppm_inc","ChangeAppearanceTo", "START with nAppearance" + IToS(nAppearance));
    object oToken = GetLocalObject(oPC, TOKEN_TAG);                             //DBM_Test("sl_s_ppm_inc","ChangeAppearanceTo", "oToken" + OToS(oToken));
    //ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectVisualEffect(VFX_DUR_CUTSCENE_INVISIBILITY), oPC, 1.0);

    int nCurrentApp = GetAppearanceType(oPC);//bZ 06.0.2013
    int nOriginalApp = GetLocalInt(oToken,"OriginalAppType");                   //DBM_Test("sl_s_ppm_inc","ChangeAppearanceTo", "nOriginalApp" + IToS(nOriginalApp));
    if (nAppearance == -1) //Change appearance to original
    {                                                                           //DBM_Test("sl_s_ppm_inc","ChangeAppearanceTo", "Change to original!!!");
        AssignCommand(oPC, ClearAllActions(TRUE));
        DelayCommand(0.01, SetCreatureAppearanceType(oPC, nOriginalApp));
        //DeleteLocalInt(oToken,"OriginalAppType");
        DelayCommand(0.3, PPM_ChangePortrait(TRUE, oPC)); //bZ 27.08.13
        DelayCommand(0.5, PPM_ApprearanceCheck(oPC, nOriginalApp));
    }

    else
    {
        if((nOriginalApp == 0) && (nCurrentApp != APPEARANCE_TYPE_DWARF)) //bZ 25.10.11
            SetLocalInt(oToken, "OriginalAppType", nCurrentApp);

        AssignCommand(oPC, ClearAllActions(TRUE));
        DelayCommand(0.01, SetCreatureAppearanceType(oPC, nAppearance));
        DelayCommand(0.3, PPM_ChangePortrait(FALSE, oPC)); //bZ 27.08.13
        DelayCommand(0.5, PPM_ApprearanceCheck(oPC, nAppearance, FALSE));
    }
}


void PPM_ApprearanceCheck(object oPC, int nTargetApp, int nChangeToOriginal = TRUE)
{                                                                               //DBM_Test("sl_s_ppm_inc","PPM_ApprearanceCheck", "START with oPC" + OToS(oPC));
                                                                                //DBM_Test("sl_s_ppm_inc","PPM_ApprearanceCheck", "START with nTargetApp" + IToS(nTargetApp));
                                                                                //DBM_Test("sl_s_ppm_inc","PPM_ApprearanceCheck", "START with nChangeToOriginal" + IToS(nChangeToOriginal));
    int nCurrentApp = GetAppearanceType(oPC);                                   //DBM_Test("sl_s_ppm_inc","PPM_ApprearanceCheck", "nCurrentApp" + IToS(nCurrentApp));
    if(nChangeToOriginal)
    {
        if (nCurrentApp == nTargetApp)
        {
            object oToken = GetLocalObject(oPC, TOKEN_TAG);
            int nStage = GetLocalInt(oToken, "nPPM_RemoveForm_PassedStage")+1;  //DBM_Test("sl_s_ppm_inc","PPM_ApprearanceCheck", "Set stage to" + IToS(nStage));
            DelayCommand(0.1, SetLocalInt(oToken, "nPPM_RemoveForm_PassedStage", nStage));
            DelayCommand(0.2, ExecuteScript("sl_s_ppm_remove", oPC));
            //DelayCommand(0.7, ExecuteScript("sl_s_ppm_setmrk1", oPC));
        }
        else
            DelayCommand(0.5, PPM_ApprearanceCheck(oPC, nTargetApp));
    }

    else //bZ 09.03.12
    {
        if (nCurrentApp == nTargetApp)
            DelayCommand(0.7, ExecuteScript("sl_s_ppm_setmrk1", oPC));

        else
            DelayCommand(0.3, PPM_ApprearanceCheck(oPC, nTargetApp, FALSE));

    }
}





int PPM_CreateSaves(object oPC)
{
    object oSafe1 = CreateItemOnObject("ppm_safe", oPC, 1, "PPM_Safe1");
    object oSafe2 = CreateItemOnObject("ppm_safe", oPC, 1, "PPM_Safe2");
    object oSafe3 = CreateItemOnObject("ppm_safe", oPC, 1, "PPM_Safe3");

    SetLocalObject(oPC, "PPM_Safe3", oSafe3);

    PPM_LockItem(oSafe1);
    PPM_LockItem(oSafe2);
    PPM_LockItem(oSafe3);

return TRUE;
}




void PPM_Remorph(object oPC)
{
    object oToken = GetLocalObject(oPC, TOKEN_TAG);                         //DBM_Test("sl_s_ppm_inc","PPM_Remorph", "oToken" + OToS(oToken));
    int nForceRemorph = GetLocalInt(oToken, "ForceRemorph");                    //DBM_Test("sl_s_ppm_inc","PPM_Remorph", "nForceRemorph" + IToS(nForceRemorph));
    if (!nForceRemorph)
    {
        if (GetIsInCombat(oPC))
        {
            DelayCommand(15.0, PPM_Remorph(oPC));
            return;
        }
        ClearAllActions(TRUE);
        //ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectCutsceneImmobilize(), oPC, 3.1);
        DelayCommand(1.0, ExecuteScript("sl_s_ppm_remove", oPC));
    }

    else
        SetLocalInt(oToken, "ForceRemorph", (nForceRemorph-1));
}


void PPM_LockAllSlots(object oPC)
{                                                                               //DBM_Test("sl_s_ppm_inc","PPM_LockAllSlots", "START with oPC" + OToS(oPC));
    object oToken = GetLocalObject(oPC, TOKEN_TAG);                         //DBM_Test("sl_s_ppm_inc","PPM_LockAllSlots", "oToken" + OToS(oToken));
    int i;
    for(i=0; i<=13; i++)
        SetLocalInt(oToken, ("LockSlot_"+IntToString(i)), TRUE);
}



void PPM_UnlockAllSlots(object oPC)
{                                                                               //DBM_Test("sl_s_ppm_inc","PPM_UnlockAllSlots", "START with oPC" + OToS(oPC));
    object oToken = GetLocalObject(oPC, TOKEN_TAG);                         //DBM_Test("sl_s_ppm_inc","PPM_UnlockAllSlots", "oToken" + OToS(oToken));
    int i;
    for(i=0; i<=14; i++) // 14 is for setting finish variables
    {                                                                           //DBM_Test("sl_s_ppm_inc","PPM_UnlockAllSlots", "counter i" + IToS(i));
        if (i<14)
            DeleteLocalInt(oToken, ("LockSlot_"+IntToString(i)));

        else
        {
            int nStage = GetLocalInt(oToken, "nPPM_RemoveForm_PassedStage")+1;  //DBM_Test("sl_s_ppm_inc","PPM_UnlockAllSlots", "Set stage to" + IToS(nStage));
            SetLocalInt(oToken, "nPPM_RemoveForm_PassedStage", nStage);
            DelayCommand(0.1, ExecuteScript("sl_s_ppm_remove", oPC));
        }
    }
}



void PPM_LockItem(object oItem)
{
    SetLocalInt(oItem, "PPM_Item", TRUE);
    SetItemCursedFlag(oItem, TRUE);
    SetLocalInt(oItem, "MadeND",1); //bZ 01.10.11 for NonDropLegal
}



void PPM_DestroyEquipedPPMItems(object oPC)
{                                                                               //DBM_Test("sl_s_ppm_inc","PPM_DestroyEquipedPPMItems", "START with oPC" + OToS(oPC));
    object oToken = GetLocalObject(oPC, TOKEN_TAG);                             //DBM_Test("sl_s_ppm_inc","PPM_DestroyEquipedPPMItems", "oToken" + OToS(oToken));
    int i;
    object oItem;
    for(i=0; i<=17; i++)
    {
        if (i<17)
        {
            oItem = GetItemInSlot(i, oPC);                                      //DBM_Test("sl_s_ppm_inc","PPM_DestroyEquipedPPMItems", "oItem in slot" + IToS(i) + OToS(oItem));
            if (PPM_GetIsItemLocked(oItem))
            {
                DeleteLocalInt(oItem, "PPM_Item");//for not to see the message from PPM_GetIsActionUnEquipItemPossible().
                DestroyObject(oItem, 0.2);
            }
        }
        else
        {
            int nStage = GetLocalInt(oToken, "nPPM_RemoveForm_PassedStage")+1;  //DBM_Test("sl_s_ppm_inc","PPM_DestroyEquipedPPMItems", "Set stage to" + IToS(nStage));
            DelayCommand(0.2, SetLocalInt(oToken, "nPPM_RemoveForm_PassedStage", nStage));
            DelayCommand(0.3, ExecuteScript("sl_s_ppm_remove", oPC));
        }
    }
}


void PPM_DestroyPPMItemsInInventory(object oPC)
{                                                                               //DBM_Test("sl_s_ppm_inc","PPM_DestroyPPMItemsInInventory", "START with oPC" + OToS(oPC));
    object oToken = GetLocalObject(oPC, TOKEN_TAG);                         //DBM_Test("sl_s_ppm_inc","PPM_DestroyPPMItemsInInventory", "oToken" + OToS(oToken));
    int i;
    object oItem = GetFirstItemInInventory(oPC);                                //DBM_Test("sl_s_ppm_inc","PPM_DestroyPPMItemsInInventory", "First oItem" + OToS(oItem));
    while(GetIsObjectValid(oItem))
    {
        if (PPM_GetIsItemLocked(oItem))
            DestroyObject(oItem, 0.3);

        else if((GetStringLeft(GetResRef(oItem), 10) == "sl_it_ppm_") || (GetTag(oItem) == "x2_it_emptyskin") || (GetStringLeft(GetResRef(oItem), 5) == "plmr_"))//bZ 09.10.11 Debug against creature items in inventory
        {
            string sMessage = ("WARNING: Pseudopolymorph. Creature item found in inventory! Destroyed: " + GetName(oItem));
            SendMessageToAllDMs(sMessage);
            DestroyObject(oItem, 0.3);
        }
        oItem = GetNextItemInInventory(oPC);                                    //DBM_Test("sl_s_ppm_inc","PPM_DestroyPPMItemsInInventory", "Next oItem" + OToS(oItem));
    }

    DelayCommand(0.2, SetLocalInt(oToken, "nPPM_RemoveForm_PassedStage", GetLocalInt(oToken, "nPPM_RemoveForm_PassedStage")+1));   //DBM_Test("sl_s_ppm_inc","PPM_DestroyPPMItemsInInventory", "Set stage to 6");
    DelayCommand(0.3, ExecuteScript("sl_s_ppm_remove", oPC));

}



void PPM_EqiupAndLockNaturalItem(object oPC, object oItem, int nInventorySlot)
{
    AssignCommand(oPC, ClearAllActions(TRUE));
    AssignCommand(oPC, ActionEquipItem(oItem, nInventorySlot));
    DelayCommand(0.1, PPM_LockItem(oItem));

    //DelayCommand(4.0, //DBM_Test("sl_s_ppm_inc","PPM_EqiupAndLockNaturalItem", ("Item in slot "+ IntToString(nInventorySlot)) + OToS(GetItemInSlot(nInventorySlot, oPC))));
}



void PPM_NaturalWeapon(object oPC, int nPolymorphType)
{                                                                               //DBM_Test("sl_s_ppm_inc","PPM_NaturalWeapon", "START with oPC" + OToS(oPC));
                                                                                //DBM_Test("sl_s_ppm_inc","PPM_NaturalWeapon", "START with nPolymorphType" + IToS(nPolymorphType));
    string sID = IntToString(nPolymorphType);
    object oBite, oClawL, oClawR;

    object oSafe3 = GetLocalObject(oPC, "PPM_Safe3");                           //DBM_Test("sl_s_ppm_inc","PPM_NaturalWeapon", "oSafe3" + OToS(oSafe3));
    object oFormTemplate = PPM_GetFormTemplateObject(oPC);
    if(GetIsObjectValid(oFormTemplate))
    {
        oBite = CopyItem(GetItemInSlot(INVENTORY_SLOT_CWEAPON_B, oFormTemplate), oSafe3, TRUE);     //DBM_Test("sl_s_ppm_inc","PPM_NaturalWeapon", "oBite" + OToS(oBite));
        oClawL = CopyItem(GetItemInSlot(INVENTORY_SLOT_CWEAPON_L, oFormTemplate), oSafe3, TRUE);    //DBM_Test("sl_s_ppm_inc","PPM_NaturalWeapon", "oClawL" + OToS(oClawL));
        oClawR = CopyItem(GetItemInSlot(INVENTORY_SLOT_CWEAPON_R, oFormTemplate), oSafe3, TRUE);    //DBM_Test("sl_s_ppm_inc","PPM_NaturalWeapon", "oClawR" + OToS(oClawR));
    }
    else
    {
        oBite = CreateItemOnObject(("sl_it_ppm_b"+sID), oSafe3);
        oClawL = CreateItemOnObject(("sl_it_ppm_c"+sID), oSafe3);
        oClawR = CreateItemOnObject(("sl_it_ppm_c"+sID+"r"), oSafe3);
        if (!GetIsObjectValid(oClawR))
            oClawR = CreateItemOnObject(("sl_it_ppm_c"+sID), oSafe3);
    }


    //equip natural weapon
    if (GetIsObjectValid(oBite))
    {
        PPM_EqiupAndLockNaturalItem(oPC, oBite, INVENTORY_SLOT_CWEAPON_B);   //bZ 01.02.13
        //AssignCommand(oPC, ClearAllActions(TRUE));
        //AssignCommand(oPC, ActionEquipItem(oBite, INVENTORY_SLOT_CWEAPON_B));
        //DelayCommand(0.1, PPM_LockItem(oBite));
    }

    if (GetIsObjectValid(oClawL))
    {
        DelayCommand(0.1, PPM_EqiupAndLockNaturalItem(oPC, oClawL, INVENTORY_SLOT_CWEAPON_L));
        //AssignCommand(oPC, ClearAllActions(TRUE));
        //DelayCommand(0.1, AssignCommand(oPC, ActionEquipItem(oClawL, INVENTORY_SLOT_CWEAPON_L)));
        //DelayCommand(0.2, PPM_LockItem(oClawL));
    }

    if (GetIsObjectValid(oClawR))
    {
        DelayCommand(0.2, PPM_EqiupAndLockNaturalItem(oPC, oClawR, INVENTORY_SLOT_CWEAPON_R));
        //AssignCommand(oPC, ClearAllActions(TRUE));
        //DelayCommand(0.2, AssignCommand(oPC, ActionEquipItem(oClawR, INVENTORY_SLOT_CWEAPON_R)));
        //DelayCommand(0.3, PPM_LockItem(oClawR));
    }
    DelayCommand(0.4, PPM_FinishStage(oPC));
}
//------------------------------------------------------------------------------
void PPM_ShifterWeapon(object oPC, string sResrefRighthandWeapon, int nRSlot = INVENTORY_SLOT_RIGHTHAND, string sResrefLefthandWeapon = "", int nLSlot = INVENTORY_SLOT_LEFTHAND)
{
    int i = 1;
    int nFinish;
    object oTempWeapon;
    object oRWeapon, oTemplateWeapon;
    int nCreateWeapon = GetLocalInt(oPC, "CreateWeapon");                       //DBM_Test("sl_s_ppm_inc","PPM_ShifterWeapon", "nCreateWeapon" + IToS(nCreateWeapon));
    if(nCreateWeapon)
    {
        DeleteLocalInt(oPC, "CreateWeapon");                                    //DBM_Test("sl_s_ppm_inc","PPM_ShifterWeapon", "Del CreateWeapon!!!");
        object oSafe3 = GetLocalObject(oPC, "PPM_Safe3");                       //DBM_Test("sl_s_ppm_inc","PPM_ShifterWeapon", "oSafe3" + OToS(oSafe3));

        object oFormTemplate = PPM_GetFormTemplateObject(oPC);
        if(GetIsObjectValid(oFormTemplate))
        {
            oTemplateWeapon = GetItemInSlot(INVENTORY_SLOT_RIGHTHAND, oFormTemplate);  //DBM_Test("sl_s_ppm_inc","PPM_ShifterWeapon", "oTemplateWeapon" + OToS(oTemplateWeapon));
            if(GetTag(oTemplateWeapon) != sResrefRighthandWeapon)//for small creatures
                oTemplateWeapon = GetFirstItemInInventory(oFormTemplate);

            oRWeapon = CopyItem(oTemplateWeapon, oSafe3, TRUE);
                                                                                //DBM_Test("sl_s_ppm_inc","PPM_ShifterWeapon", "oRWeapon from inventory" + OToS(oRWeapon));
        }
        else
        {
            oRWeapon = CreateItemOnObject(sResrefRighthandWeapon, oSafe3);      //DBM_Test("sl_s_ppm_inc","PPM_ShifterWeapon", "oRWeapon" + OToS(oRWeapon));
        }



        if (GetIsObjectValid(oRWeapon))
        {
            while(!nFinish)
            {                                                                   //DBM_Test("sl_s_ppm_inc","PPM_ShifterWeapon", "i" + IToS(i));
                if(i == 1)
                {
                    oTempWeapon = CopyItem(oRWeapon, oSafe3, TRUE);
                    i++;
                }

                else if(i == 2)
                {
                    if(GetIsItemPropertyValid(GetFirstItemProperty(oRWeapon)))
                        IPRemoveAllItemProperties(oRWeapon, DURATION_TYPE_PERMANENT);
                    else
                        i++;
                }

                else if(i == 3)
                {

                    AssignCommand(oPC, ClearAllActions(TRUE));
                    AssignCommand(oPC, ActionEquipItem(oRWeapon, nRSlot));
                    PPM_LockItem(oRWeapon);
                    i++;
                }

                else if(i == 4)
                {
                    itemproperty ip = GetFirstItemProperty(oTempWeapon);
                    while(GetIsItemPropertyValid(ip))
                    {
                        IPSafeAddItemProperty(oRWeapon, ip, 99999.0);
                        ip = GetNextItemProperty(oTempWeapon);
                    }
                    DestroyObject(oTempWeapon, 0.5);
                    nFinish = TRUE;
                }
            }
}
        else
            SendMessageToPC(oPC, "ОШИБКА ФУНКЦИИ PPM_ShifterWeapon : NoRWeapon! Если вы видите это сообщение, пожалуйста, сделайте скриншот логов и сообщите разработчикам, или в ДМ-канал");

        DelayCommand(0.4, PPM_FinishStage(oPC));
    }
    else
        DelayCommand(0.5, PPM_ShifterWeapon(oPC, sResrefRighthandWeapon, nRSlot, sResrefLefthandWeapon, nLSlot));
}
//------------------------------------------------------------------------------
void PPM_AddPropsFromItemToSkin(object oItem, object oPC, float fDuration)
{                                                                               //DBM_Test("sl_s_ppm_inc","PPM_AddPropsFromItemToSkin", "START with oItem" + OToS(oItem));
                                                                                //DBM_Test("sl_s_ppm_inc","PPM_AddPropsFromItemToSkin", "START with oPC" + OToS(oPC));
    object oSkin = GetItemInSlot(INVENTORY_SLOT_CARMOUR, oPC);                  //DBM_Test("sl_s_ppm_inc","PPM_AddPropsFromItemToSkin", "oSkin of oPC" + OToS(oSkin));
    itemproperty ip = GetFirstItemProperty(oItem);
    while (GetIsItemPropertyValid(ip))
    {
        AddItemProperty(DURATION_TYPE_TEMPORARY, ip, oSkin, fDuration);
        ip = GetNextItemProperty(oItem);
    }
}
//------------------------------------------------------------------------------
int PPM_GetItemSlotIsInList(int nInventorySlot, string sMergeSlotList)
{                                                                               //DBM_Test("sl_s_ppm_inc","GetItemSlotIsInList", "START with nInventorySlot" + IToS(nInventorySlot));
                                                                                //DBM_Test("sl_s_ppm_inc","GetItemSlotIsInList", "START with sMergeSlotList: " + sMergeSlotList);
    string sSubString = "_" + IntToString(nInventorySlot) + "_";                //DBM_Test("sl_s_ppm_inc","GetItemSlotIsInList", "sSubString: " + sSubString);
    int nPos = FindSubString(sMergeSlotList, sSubString);                       //DBM_Test("sl_s_ppm_inc","GetItemSlotIsInList", "Position" + IToS(nPos));
    if (nPos > -1)
        return TRUE;

return FALSE;
}
//------------------------------------------------------------------------------
void PPM_AddPropsFromGlovesToClaws(object oItem, object oPC, float fDuration)
{
    object oToAddPropsOn;
    int i=13; // INVENTORY_SLOT_CWEAPON_L -1
    while(!GetIsObjectValid(oToAddPropsOn) && i<16) // INVENTORY_SLOT_CWEAPON_B
        oToAddPropsOn = GetItemInSlot(++i, oPC);

    if(GetIsObjectValid(oToAddPropsOn))
    {
        itemproperty ip = GetFirstItemProperty(oItem);
        while (GetIsItemPropertyValid(ip))
        {
            AddItemProperty(DURATION_TYPE_TEMPORARY, ip, oToAddPropsOn, fDuration);
            ip = GetNextItemProperty(oItem);
        }
    }
}
//------------------------------------------------------------------------------
void PPM_CheckSlot(int nInventorySlot, object oPC, string sMergeSlotList, object oSafe, float fDuration)
{                                                                               //DBM_Test("sl_s_ppm_inc","PPM_CheckSlot", "START with nInventorySlot" + IToS(nInventorySlot));
                                                                                //DBM_Test("sl_s_ppm_inc","PPM_CheckSlot", "START with oPC" + OToS(oPC));
                                                                                //DBM_Test("sl_s_ppm_inc","PPM_CheckSlot", "START with sMergeSlotList: " + sMergeSlotList);
                                                                                //DBM_Test("sl_s_ppm_inc","PPM_CheckSlot", "START with oSafe" + OToS(oSafe));
                                                                                //DBM_Test("sl_s_ppm_inc","PPM_CheckSlot", "START with fDuration" + FToS(fDuration));
    int nIsShield;
    int nBaseType;
    int NeedWeaponLink;
    object oToken = GetLocalObject(oPC, TOKEN_TAG);
    //int nItemsPutInSafe;

    object oItem = GetItemInSlot(nInventorySlot, oPC);                          //DBM_Test("sl_s_ppm_inc","PPM_CheckSlot", "oItem in slot" + OToS(oItem));
    if (GetIsObjectValid(oItem))
    {
        //SetLocalString(oToken, ("InvSlot_"+ IntToString(nInventorySlot)), GetResRef(oItem));   //reserved copy. ResRef only. // bZ 25.10.12

        nBaseType = GetBaseItemType(oItem);
        if ((nBaseType == BASE_ITEM_SMALLSHIELD) || (nBaseType == BASE_ITEM_TOWERSHIELD) || (nBaseType == BASE_ITEM_LARGESHIELD))
            nIsShield = TRUE;

        //From the left hand only shields can transfer there props
        if( (nInventorySlot != INVENTORY_SLOT_LEFTHAND) ||
           ((nInventorySlot == INVENTORY_SLOT_LEFTHAND) && nIsShield) )
        {
            if (PPM_GetItemSlotIsInList(nInventorySlot, sMergeSlotList))
            {
                //We add to skin any props except those from weapon. Weapon props would be added separately, on shfter weapon. //bZ 04.03.12
                if (nInventorySlot == INVENTORY_SLOT_RIGHTHAND)
                {
                    NeedWeaponLink = TRUE;
                    DelayCommand(1.5, PPM_AddWeaponProps(oPC, fDuration));
                }
                else if(nInventorySlot == INVENTORY_SLOT_ARMS)
                    PPM_AddPropsFromGlovesToClaws(oItem, oPC, fDuration);
                else
                    PPM_AddPropsFromItemToSkin(oItem, oPC, fDuration);
            }
        }

        SetLocalInt(oItem, "PPM_Slot", nInventorySlot);
        //PPM_SaveItemOnToken(oToken, oItem, nInventorySlot);//bZ 07.01.13
        SetLocalString(oItem, "SafeTag", GetTag(oSafe));//for force unequiping purpose
        SetItemCursedFlag(oItem, TRUE);
        SetLocalInt(oItem, "MadeND",1); //bZ 01.10.11 for NonDropLegal
        //DeleteLocalInt(oItem, "DebugCount"); //bZ 23.01.13
        PPM_slRecreateItem(oItem, oSafe, TRUE, NeedWeaponLink);

    }

    if(nInventorySlot == INVENTORY_SLOT_ARMS)
        PPM_FinishStage(oPC);                   //NEW_PPM //14.10.12
}
//------------------------------------------------------------------------------
void PPM_SaveItemPropsAndUnequipItemsIntoSafe(object oPC, string sMergeSlotList, float fDuration)
{                                                                               //DBM_Test("sl_s_ppm_inc","PPM_SaveItemPropsAndUnequipItemsIntoSafe", "START with oPC" + OToS(oPC));
                                                                                //DBM("sl_s_ppm_inc","PPM_SaveItemPropsAndUnequipItemsIntoSafe", "START with sMergeSlotList: " + sMergeSlotList);
                                                                                //DBM_Test("sl_s_ppm_inc","PPM_SaveItemPropsAndUnequipItemsIntoSafe", "START with fDuration" + FToS(fDuration));
    int nAppIsSuccessfullyChanged = GetLocalInt(oPC, "AppIsSuccessfullyChanged");   //DBM_Test("sl_s_ppm_inc","PPM_SaveItemPropsAndUnequipItemsIntoSafe", "nAppIsSuccessfullyChanged" + IToS(nAppIsSuccessfullyChanged));
    DeleteLocalInt(oPC, "CreateWeapon");                                        //DBM_Test("sl_s_ppm_inc","PPM_SaveItemPropsAndUnequipItemsIntoSafe", "DEL CreateWeapon!!!");
    if(nAppIsSuccessfullyChanged)
    {
        DeleteLocalInt(oPC, "AppIsSuccessfullyChanged");                        //DBM_Test("sl_s_ppm_inc","PPM_SaveItemPropsAndUnequipItemsIntoSafe", "DEL nAppIsSuccessfullyChanged!!!");
        SetLocalInt(oPC, "CreateWeapon", TRUE);                                 //DBM_Test("sl_s_ppm_inc","PPM_SaveItemPropsAndUnequipItemsIntoSafe", "SET CreateWeapon!!!");

        object oSafe1 = GetItemPossessedBy(oPC, "PPM_Safe1");                   //DBM("sl_s_ppm_inc","PPM_SaveItemPropsAndUnequipItemsIntoSafe", "oSafe1" + OToS(oSafe1));
        object oSafe2 = GetItemPossessedBy(oPC, "PPM_Safe2");                   //DBM_Test("sl_s_ppm_inc","PPM_SaveItemPropsAndUnequipItemsIntoSafe", "oSafe2" + OToS(oSafe2));

        //We need a strict stack sequence to prevent loss of items
        //Items from these slots we put into Safe1
        float fDelay;
        //OpenInventory(oSafe1, oPC);
        //AssignCommand(oPC,DoPlaceableObjectAction(oSafe1,PLACEABLE_ACTION_USE));

        PPM_CheckSlot(INVENTORY_SLOT_LEFTHAND, oPC, sMergeSlotList, oSafe1, fDuration);
        DelayCommand(fDelay+=0.05, PPM_CheckSlot(INVENTORY_SLOT_RIGHTHAND, oPC, sMergeSlotList, oSafe1, fDuration));
        DelayCommand(fDelay+=0.05, PPM_CheckSlot(INVENTORY_SLOT_CHEST, oPC, sMergeSlotList, oSafe1, fDuration));
        DelayCommand(fDelay+=0.05, PPM_CheckSlot(INVENTORY_SLOT_ARROWS, oPC, sMergeSlotList, oSafe1, fDuration));
        DelayCommand(fDelay+=0.05, PPM_CheckSlot(INVENTORY_SLOT_BULLETS, oPC, sMergeSlotList, oSafe1, fDuration));
        DelayCommand(fDelay+=0.05, PPM_CheckSlot(INVENTORY_SLOT_BOLTS, oPC, sMergeSlotList, oSafe1, fDuration));


        //Items from these slots we put into Safe2
        DelayCommand(fDelay+=0.05, PPM_CheckSlot(INVENTORY_SLOT_CLOAK, oPC, sMergeSlotList, oSafe2, fDuration));
        DelayCommand(fDelay+=0.05, PPM_CheckSlot(INVENTORY_SLOT_HEAD, oPC, sMergeSlotList, oSafe2, fDuration));
        DelayCommand(fDelay+=0.05, PPM_CheckSlot(INVENTORY_SLOT_BOOTS, oPC, sMergeSlotList, oSafe2, fDuration));
        DelayCommand(fDelay+=0.05, PPM_CheckSlot(INVENTORY_SLOT_NECK, oPC, sMergeSlotList, oSafe2, fDuration));
        DelayCommand(fDelay+=0.05, PPM_CheckSlot(INVENTORY_SLOT_LEFTRING, oPC, sMergeSlotList, oSafe2, fDuration));
        DelayCommand(fDelay+=0.05, PPM_CheckSlot(INVENTORY_SLOT_RIGHTRING, oPC, sMergeSlotList, oSafe2, fDuration));
        DelayCommand(fDelay+=0.05, PPM_CheckSlot(INVENTORY_SLOT_BELT, oPC, sMergeSlotList, oSafe2, fDuration));
        DelayCommand(fDelay+=0.05, PPM_CheckSlot(INVENTORY_SLOT_ARMS, oPC, sMergeSlotList, oSafe2, fDuration));
    }
    else
        DelayCommand(0.5, PPM_SaveItemPropsAndUnequipItemsIntoSafe(oPC, sMergeSlotList, fDuration));
}
//------------------------------------------------------------------------------
void PPM_DebugForSaves(object oPC, object oSafe, int nPassedStage, object oToken)
{                                                                               //DBM_Test("sl_s_ppm_inc","PPM_DebugForSaves", "START with oSafe" + OToS(oSafe));
                                                                                //DBM_Test("sl_s_ppm_inc","PPM_DebugForSaves", "START with nPassedStage" + IToS(nPassedStage));

    object oItem = GetFirstItemInInventory(oSafe);                              //DBM_Test("sl_s_ppm_inc","PPM_DebugForSaves", "DEBUG: oItem from Safe" + OToS(oItem));
    int nDebugCount;

    if (!GetIsObjectValid(oItem))
    {
        DestroyObject(oSafe, 0.01);
        DelayCommand(0.1, SetLocalInt(oToken, "nPPM_RemoveForm_PassedStage", (nPassedStage+1)));
        DelayCommand(0.2, ExecuteScript("sl_s_ppm_equback", oPC));
    }
    else
    {
        SetItemCursedFlag(oItem, TRUE);
        SetLocalInt(oItem, "MadeND", 1);
        SetLocalInt(oItem, "RemoveCurse", 1);
        PPM_slRecreateItem(oItem, oPC, TRUE, FALSE, TRUE);
        DelayCommand(0.6, ExecuteScript("sl_s_ppm_equback", oPC));
    }
}
//------------------------------------------------------------------------------
void PPM_EquipItemsBackAddDestroySaves_NEW(object oPC)
{                                                                               //DBM_Test("sl_s_ppm_inc","PPM_EquipItemsBackAddDestroySaves_NEW", "START with oPC" + OToS(oPC));
    object oSafe1 = GetItemPossessedBy(oPC, "PPM_Safe1");                       //DBM_Test("sl_s_ppm_inc","PPM_EquipItemsBackAddDestroySaves_NEW", "oSafe1" + OToS(oSafe1));
    object oSafe2 = GetItemPossessedBy(oPC, "PPM_Safe2");                       //DBM_Test("sl_s_ppm_inc","PPM_EquipItemsBackAddDestroySaves_NEW", "oSafe2" + OToS(oSafe2));
    int nInventorySlot;
    object oToken = GetLocalObject(oPC, TOKEN_TAG);
    object oItem;
    int nPassedStage = GetLocalInt(oToken, "nPPM_RemoveForm_PassedStage");      //DBM_Test("sl_s_ppm_inc","PPM_EquipItemsBackAddDestroySaves_NEW", "nPassedStage" + IToS(nPassedStage));
    int nItemType;
    object oLeftWeapon;



    if (nPassedStage == 5)
    {
        oItem = GetFirstItemInInventory(oSafe1);                                //DBM_Test("sl_s_ppm_inc","PPM_EquipItemsBackAddDestroySaves_NEW", "oItem from Safe1" + OToS(oItem));
        while(GetIsObjectValid(oItem))
        {
            //debug part //bZ 15.11.11
            nItemType = GetBaseItemType(oItem);                                 //DBM_Test("sl_s_ppm_inc","PPM_EquipItemsBackAddDestroySaves_NEW", "nItemType from Safe1" + IToS(nItemType));
            if ((nItemType == BASE_ITEM_CREATUREITEM) ||
                (nItemType == BASE_ITEM_CBLUDGWEAPON) ||
                (nItemType == BASE_ITEM_CPIERCWEAPON) ||
                (nItemType == BASE_ITEM_CSLASHWEAPON) ||
                (nItemType == BASE_ITEM_CSLSHPRCWEAP))
                DestroyObject(oItem, 0.1);
            //End of debug part

            else if((GetStringLeft(GetResRef(oItem), 10) == "sl_it_ppm_") || (GetTag(oItem) == "x2_it_emptyskin") || (GetStringLeft(GetResRef(oItem), 5) == "plmr_"))//bZ 20.01.13 Debug
            {
                SendMessageToAllDMs("WARNING: Pseudopolymorph. Creature item found in ppm_safe1! Destroyed: " + GetName(oItem));
                DestroyObject(oItem, 0.1);
            }

            else
            {
                SetItemCursedFlag(oItem, FALSE);
                DeleteLocalInt(oItem, "MadeND");
                DeleteLocalString(oItem, "SafeTag");
                nInventorySlot = GetLocalInt(oItem, "PPM_Slot");                //DBM_Test("sl_s_ppm_inc","PPM_EquipItemsBackAddDestroySaves_NEW", "nInventorySlot" + IToS(nInventorySlot));

                if(nInventorySlot == INVENTORY_SLOT_RIGHTHAND)//Weapon in left hand falls to inventory. //bZ 11.02.2015
                {
                    oLeftWeapon = GetItemInSlot(nInventorySlot, oPC);
                    if(GetIsObjectValid(oLeftWeapon))
                        DelayCommand(0.05, AssignCommand(oPC, ActionEquipItem(oLeftWeapon, INVENTORY_SLOT_LEFTHAND)));
                }

                AssignCommand(oPC, ClearAllActions(TRUE));
                DelayCommand(0.01, AssignCommand(oPC, ActionEquipItem(oItem, nInventorySlot)));
            }
            oItem = GetNextItemInInventory(oSafe1);                             //DBM_Test("sl_s_ppm_inc","PPM_EquipItemsBackAddDestroySaves_NEW", "oItem from Safe1" + OToS(oItem));
        }


        //here we need a pause
        DelayCommand(0.2, PPM_DebugForSaves(oPC, oSafe1, nPassedStage, oToken));
    }


    else if (nPassedStage == 6)
    {

        oItem = GetFirstItemInInventory(oSafe2);                                //DBM_Test("sl_s_ppm_inc","PPM_EquipItemsBackAddDestroySaves_NEW", "oItem from Safe2" + OToS(oItem));
        while(GetIsObjectValid(oItem))
        {
            //debug part //bZ 15.11.11
            nItemType = GetBaseItemType(oItem);                                 //DBM_Test("sl_s_ppm_inc","PPM_EquipItemsBackAddDestroySaves_NEW", "nItemType from Safe2" + IToS(nItemType));
            if ((nItemType == BASE_ITEM_CREATUREITEM) ||
                (nItemType == BASE_ITEM_CBLUDGWEAPON) ||
                (nItemType == BASE_ITEM_CPIERCWEAPON) ||
                (nItemType == BASE_ITEM_CSLASHWEAPON) ||
                (nItemType == BASE_ITEM_CSLSHPRCWEAP))
                DestroyObject(oItem, 0.1);
            //End of debug part

            else if((GetStringLeft(GetResRef(oItem), 10) == "sl_it_ppm_") || (GetTag(oItem) == "x2_it_emptyskin") || (GetStringLeft(GetResRef(oItem), 5) == "plmr_"))//bZ 20.01.13 Debug
            {
                SendMessageToAllDMs("WARNING: Pseudopolymorph. Creature item found in ppm_safe2! Destroyed: " + GetName(oItem));
                DestroyObject(oItem, 0.1);
            }

            else
            {
                SetItemCursedFlag(oItem, FALSE);
                DeleteLocalInt(oItem, "MadeND");
                DeleteLocalString(oItem, "SafeTag");
                nInventorySlot = GetLocalInt(oItem, "PPM_Slot");                        //DBM_Test("sl_s_ppm_inc","PPM_EquipItemsBackAddDestroySaves_NEW", "nInventorySlot" + IToS(nInventorySlot));

                AssignCommand(oPC, ClearAllActions(TRUE));
                DelayCommand(0.01, AssignCommand(oPC, ActionEquipItem(oItem, nInventorySlot)));
            }
            oItem = GetNextItemInInventory(oSafe2);                                 //DBM_Test("sl_s_ppm_inc","PPM_EquipItemsBackAddDestroySaves_NEW", "oItem from Safe2" + OToS(oItem));
        }


        //here we need a pause
        DelayCommand(0.2, PPM_DebugForSaves(oPC, oSafe2, nPassedStage, oToken));
    }

    else
        DelayCommand(0.1, ExecuteScript("sl_s_ppm_remove", oPC));
}
//------------------------------------------------------------------------------
void PPM_RemoveFormEffects(object oPC)
{                                                                               //DBM_Test("sl_s_ppm_inc","PPM_RemoveFormEffects", "START with oPC" + OToS(oPC));
    object oVirtCaster = GetObjectByTag("sl_cr_eff_ppm");                       //DBM_Test("sl_s_ppm_inc","PPM_RemoveFormEffects", "oVirtCaster" + OToS(oVirtCaster));
    object oCreator;
    effect eEffect = GetFirstEffect(oPC);
    while (GetIsEffectValid(eEffect))
    {
        oCreator = GetEffectCreator(eEffect);                                   //DBM_Test("sl_s_ppm_inc","PPM_RemoveFormEffects", "oCreator" + OToS(oCreator));
        //DBM("sl_s_ppm_inc", "PPM_RemoveFormEffects", "Removing effect from oPC: " + OToS(oCreator));
        if (oCreator == oVirtCaster) {
            RemoveEffect(oPC, eEffect);

        }
        else if(oCreator == oPC)
        {
            if(GetEffectType(eEffect) == EFFECT_TYPE_AREA_OF_EFFECT)//Dragons' aura
                RemoveEffect(oPC, eEffect);
        }
        eEffect = GetNextEffect(oPC);
    }

    //Debug 07.01.13
    //ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectACDecrease(1, AC_NATURAL_BONUS), oPC, 1.0);
    //ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectAttackDecrease(1), oPC, 1.0);
    //End
    object oToken = GetLocalObject(oPC, TOKEN_TAG);
    int nStage = GetLocalInt(oToken, "nPPM_RemoveForm_PassedStage")+1;          //DBM_Test("sl_s_ppm_inc","PPM_RemoveFormEffects", "Set stage to" + IToS(nStage));
    DelayCommand(0.2, SetLocalInt(oToken, "nPPM_RemoveForm_PassedStage", nStage));
    DelayCommand(0.3, ExecuteScript("sl_s_ppm_remove", oPC));
}
//------------------------------------------------------------------------------
void PPM_AddWeaponProps(object oPC, float fDuration)
{                                                                               //DBM_Test("sl_s_ppm_inc","PPM_AddWeaponProps", "Start with oPC" + OToS(oPC));
                                                                                //DBM_Test("sl_s_ppm_inc","PPM_AddWeaponProps", "Start with fDuration" + FToS(fDuration));
    object oShifterWeapon = GetItemInSlot(INVENTORY_SLOT_RIGHTHAND, oPC);       //DBM_Test("sl_s_ppm_inc","PPM_AddWeaponProps", "oShifterWeapon(in right hand)" + OToS(oShifterWeapon));
    object oSafe1 = GetItemPossessedBy(oPC, "PPM_Safe1");                       //DBM_Test("sl_s_ppm_inc","PPM_AddWeaponProps", "oSafe1" + OToS(oSafe1));
    object oPCWeapon = GetLocalObject(oSafe1, "WeaponInRightHand");             //DBM_Test("sl_s_ppm_inc","PPM_AddWeaponProps", "oPCWeapon(in safe)" + OToS(oPCWeapon));
    itemproperty ipTemp = GetFirstItemProperty(oPCWeapon);
    while (GetIsItemPropertyValid(ipTemp))
    {
        AddItemProperty(DURATION_TYPE_TEMPORARY, ipTemp, oShifterWeapon, fDuration);
        ipTemp = GetNextItemProperty(oPCWeapon);
    }
}
//------------------------------------------------------------------------------
void PPM_RemorphMessage(object oPC)
{
    object oToken = GetLocalObject(oPC, TOKEN_TAG);                             //DBM_Test("sl_s_ppm_inc","PPM_Remorph", "oToken" + OToS(oToken));
    int nForceRemorph = GetLocalInt(oToken, "ForceRemorph");                    //DBM_Test("sl_s_ppm_inc","PPM_Remorph", "nForceRemorph" + IToS(nForceRemorph));
    if (!nForceRemorph)
        FloatingTextStringOnCreature("Вы чувствуете, что ваша сущность постепенно берет верх над измененной формой!", oPC, FALSE);
}
//------------------------------------------------------------------------------
void PPM_slDelayedCopyItem(object oItem, object oPC, int nVar = TRUE, int nCurse = TRUE, /*bZ 04.03.12*/int NeedWeaponLink = FALSE, int nEquip = FALSE)
{                                                                               //DBM_Test("sl_s_inc2","slDelayedCopyItem","start");
    object oNew = CopyItem(oItem, oPC, nVar);
    //DBM_Test("sl_s_inc2","slDelayedCopyItem","GetIdentified(oItem)"+IToS(GetIdentified(oItem)));
    //DBM_Test("sl_s_inc2","slDelayedCopyItem","GetIdentified(oNew)"+IToS(GetIdentified(oNew)));


    //bZ 29.07.12
    DestroyObject(oItem); //07.01.13
    //string sSlot = IntToString(GetLocalInt(oItem, "PPM_Slot"));                 //DBM_Test("sl_s_ppm_inc","PPM_slDelayedCopyItem", "sSlot: " + sSlot);
    //SetLocalObject(GetItemPossessor(oPC), ("ItemInSlot"+sSlot), oItem);
    //End 29.07.12

    //bZ 28.02.13
    if(nEquip)
    {
        int nInventorySlot = GetLocalInt(oNew, "PPM_Slot");                     //DBM_Test("sl_s_ppm_inc","PPM_EquipItemsBackAddDestroySaves_NEW", "nInventorySlot" + IToS(nInventorySlot));

        AssignCommand(oPC, ClearAllActions(TRUE));
        AssignCommand(oPC, ActionEquipItem(oNew, nInventorySlot));
    }
    //End 28.02.13


    //bZ 04.03.12
    if (NeedWeaponLink)
        SetLocalObject(oPC, "WeaponInRightHand", oNew);
    //End 04.03.12

    if (nCurse)
        SetItemCursedFlag(oNew, TRUE);
                                                                                //DBM_Test("sl_s_ppm_inc", "PPM_slDelayedCopyItem", "DROPIT? Plot? Curse?" + IToS(GetLocalInt(oNew,"DROPIT")) + ", " + IToS(GetPlotFlag(oNew)) + ", " + IToS(GetItemCursedFlag(oNew)));
}
//------------------------------------------------------------------------------
void PPM_slRecreateItem(object oItem, object oPC, int nVar = TRUE, /*bZ 04.03.12*/int NeedWeaponLink = FALSE, int nEquip = FALSE)
{                                                                               //DBM_Test("sl_s_ppm_inc", "PPM_slRecreateItem", "DROPIT? Plot? Curse?" + IToS(GetLocalInt(oItem,"DROPIT")) + ", " + IToS(GetPlotFlag(oItem)) + ", " + IToS(GetItemCursedFlag(oItem)));
    object oTemp = GetObjectByTag("sl_cont_temp");                              //DBM_Test("sl_s_inc2","slRecreateItem","oTemp" + OToS(oTemp));
    object oTempItem = CopyItem(oItem, oTemp, nVar);                            //DBM_Test("sl_s_inc2","slRecreateItem","oTempItem" + OToS(oTempItem));
    //ACHTUNG (CHECK) REMOVE
    //slWriteLostLog(oItem, "slRecreateItem");

    int nCurse = GetItemCursedFlag(oItem); //bZ 17.10.11

    DestroyObject(oItem);
    DelayCommand(0.1, PPM_slDelayedCopyItem(oTempItem, oPC, TRUE, nCurse, NeedWeaponLink, nEquip));
}



void PPM_ClearSystemOnEnter(object oPC)
{                                                                               //DBM_Test("sl_s_ppm_inc","PPM_ClearSystemOnEnter", "START with oPC" + OToS(oPC));
    object oToken = GetLocalObject(oPC, TOKEN_TAG);                             //DBM_Test("sl_s_ppm_inc","PPM_ClearSystemOnEnter", "oToken" + OToS(oToken));
    PPM_RemoveForm_NEW(oPC);
    DeleteLocalInt(oToken, "ForceRemorph");
    //PPM_DestroyPPMItemsInInventory(oPC);
    //PPM_UnlockAllSlots(oPC);
}




void PPM(object oPC, int nPolymorphType, float fDuration)
{                                                                               //DBM_Test("sl_s_ppm_inc","PPM", "START with oPC" + OToS(oPC));
                                                                                //DBM_Test("sl_s_ppm_inc","PPM", "START with nPolymorphType" + IToS(nPolymorphType));
                                                                                //DBM_Test("sl_s_ppm_inc","PPM", "START with fDuration" + FToS(fDuration));


    PPM_ApplyEffectPseudoPoly(oPC, nPolymorphType, fDuration);
}





//////////////
//NEW SYSTEM//
//////////////

void PPM_FinishStage(object oPC)
{
    SetLocalInt(oPC, "PPM_StageFinished", GetLocalInt(oPC, "PPM_Stage"));
    DelayCommand(0.1, ExecuteScript("sl_s_ppm_pspoly", oPC));
}


void PPM_ApplyEffectPseudoPoly(object oPC, int nForm, float fDuration = 99999.0)
{
    if (fDuration< 3.0) return;

    object oToken = GetLocalObject(oPC, TOKEN_TAG);                             //DBM_Test("sl_s_ppm_inc","PPM_ApplyEffectPseudoPoly", "oToken" + OToS(oToken));
    if (GetLocalInt(oToken, "isPolymorphed") == 0)
    {
        // bZ 25.04.2018
        int nDamagedHP = GetMaxHitPoints(oPC) - GetCurrentHitPoints(oPC);
        if(nDamagedHP>0)
        {
            SetLocalInt(oPC, "PPM_DamagedHP", nDamagedHP);
            ApplyEffectToObject(DURATION_TYPE_INSTANT, EffectHeal(nDamagedHP), oPC);
        }
        /* OLD
        if (GetCurrentHitPoints(oPC) < (GetMaxHitPoints(oPC)/2))
        {
            FloatingTextStringOnCreature("Вы ранены, и не можете изменить форму!", oPC);
            return;
        }*/

        //To prevent pseudopoly with regalia
        if( GetIsObjectValid(GetItemPossessedBy(oPC,"regalia")))
        {
            SendMessageToPC(oPC, "Вы не можете изменить форму пока в ваших руках Королевские Регалии!");
            return;
        }


        SetLocalInt(oPC, "NoHomeDupeCheck", 1);
        if (PPM_CreateSaves(oPC))//Create storage for equiped items
        {
            SetCutsceneMode(oPC, TRUE);

            AssignCommand(oPC, ClearAllActions(TRUE));
            ApplyEffectToObject(DURATION_TYPE_INSTANT, EffectVisualEffect(VFX_IMP_POLYMORPH), oPC);

            SetLocalInt(oToken, "isPolymorphed", nForm);
            SetLocalInt(oPC, "PPM_Form", nForm);
            SetLocalFloat(oPC, "PPM_Duration", fDuration);

            // Disabled bZ 25.04.2018 // Reason: нахер эта штука не нужна
            //DelayCommand((fDuration-120.0), PPM_RemorphMessage(oPC));
            //DelayCommand(fDuration, PPM_Remorph(oPC));


            DelayCommand(0.5, ExecuteScript("sl_s_ppm_pspoly", oPC));
        }
    }
    else
    {
        //FloatingTextStringOnCreature("Ваша форма уже изменена!", oPC, FALSE);
        SetLocalInt(oPC, "PPM_NextForm", nForm);
        ExecuteScript("sl_s_ppm_remove", oPC);
    }
}




void PPM_ManageParameters(object oPC, int nForm, float fDuration)
{
    int nApp;
    string sSkinResRef;
    int nSize = GetCreatureSize(oPC);

    int nSTR;                   /*1*/
    int nDEX;                   /*2*/
    int nCon;                   /*3*/
    int nDam;                   /*4*/
    int nDamType = DAMAGE_TYPE_BLUDGEONING; /*4.1*/
    int nAC;                    /*5*/
    int nAttack;                /*6*/
    int nHP;                    /*7*/
    int nFort;                  /*8*/
    int nRegen;                 /*9*/
    float fRegInterval;         /*9.1*/

    int nHide;                  /*10*/
    int nMS;                    /*11*/
    int nConc;                  /*12*/
    int nReflex;                /*13*/
    int nSpellImm1 = -1;        /*14*/
    int nSpellImm2 = -1;        /*15*/

    int nSave;                  /*16*/
    int nSpCr;                  /*17*/
    int nSpot;                  /*18*/
    int nDis;                   /*19*/
    int nLis;                   /*20*/
    int nOpL;                   /*21*/
    int nSetTr;                 /*22*/
    int nTum;                   /*23*/

    int nElemImmun;             /*24*/
    int nElemPerc;              /*24.1*/
    int nElemImmun2;            /*25*/
    int nElemPerc2;             /*25.1*/
    //int nAOE;                   /*26 Dragons' aura*/

    int nSD = GetLevelByClass(CLASS_TYPE_SHADOWDANCER, oPC);
    int nArcaneCaster = 0;
    int nWiz = GetLevelByClass(CLASS_TYPE_WIZARD, oPC);
    int nSorc = GetLevelByClass(CLASS_TYPE_SORCERER, oPC);

    int nHasNaturalWeapon;
    string sMerge;
    string sWeapon;
    string sAllowedSpells;


//UNDEAD SHAPE
    if(nForm == POLYMORPH_TYPE_RISEN_LORD)
    {
        nApp = APPEARANCE_TYPE_LICH;//881 - with wings
        sSkinResRef = "plmr_risen_lord";

        nSTR = 5;
        nCon = 5;
        nAC = 10;

        nAttack = 8; //3; // bZ 23.04.2018
        nHP = 100;
        nFort = 5;
        nRegen = 5;
        fRegInterval = 6.0;

        nHasNaturalWeapon = FALSE;
        sMerge = MERGE_A + MERGE_I + MERGE_W;
        sWeapon = "plmr_risen_scyth";

    }


    else if((nForm == POLYMORPH_TYPE_VAMPIRE_MALE) || (nForm == POLYMORPH_TYPE_VAMPIRE_FEMALE))
    {
        if (GetGender(oPC) == GENDER_MALE)
            nApp = APPEARANCE_TYPE_VAMPIRE_MALE;
        else
            nApp = APPEARANCE_TYPE_VAMPIRE_FEMALE;

        sSkinResRef = "plmr_vampire";

        nSTR = 6;
        nDEX = 6;
        nAC = 25;

        nAttack = 3;
        nHP = 100;

        nRegen = 5;
        fRegInterval = 3.0;

        nHide = 15;
        nMS = 15;

        nHasNaturalWeapon = POLYMORPH_TYPE_VAMPIRE_MALE;
        sMerge = MERGE_A + MERGE_I + MERGE_H;
        sAllowedSpells = "_258_";
    }


    else if(nForm == POLYMORPH_TYPE_SPECTRE)
    {
        nApp = APPEARANCE_TYPE_SPECTRE;
        sSkinResRef = "plmr_spectre";

        nSTR = 6;
        nDEX = 8;
        nAC = 20;
        nHP = 100;
        nRegen = 5;
        fRegInterval = 3.0;

        nHide = 15;
        nMS = 15;
        nConc = 50;


        nHasNaturalWeapon = POLYMORPH_TYPE_SPECTRE;
        sMerge = MERGE_A + MERGE_I + MERGE_H;
        sAllowedSpells = "_90_";
    }


//DRAGON SHAPE
    else if(nForm == POLYMORPH_TYPE_ANCIENT_RED_DRAGON)
    {
        nApp = APPEARANCE_TYPE_DRAGON_RED;
        sSkinResRef = "plmr_red_dragon";

        nSTR = 8;
        nDEX = 6;
        nCon = 6;
        nDam = DAMAGE_BONUS_20;
        nAC = 20;

        nAttack = 19;
        nHP = 350;
        nFort = 12;
        nReflex = 12;
        nDis = 25;

        nSpellImm1 = SPELL_BALAGARNSIRONHORN;
        nSpellImm2 = SPELL_EVARDS_BLACK_TENTACLES;

        nElemImmun = DAMAGE_TYPE_FIRE;
        nElemPerc = 100;
        //nAOE = TRUE;

        nHasNaturalWeapon = POLYMORPH_TYPE_RED_DRAGON;
        sMerge = MERGE_A + MERGE_H;
        sWeapon = "";
        sAllowedSpells = "_797_";
    }


    else if(nForm == POLYMORPH_TYPE_ANCIENT_BLUE_DRAGON)
    {
        nApp = APPEARANCE_TYPE_DRAGON_BLUE;
        sSkinResRef = "plmr_blue_dragon";

        nSTR = 8;
        nDEX = 6;
        nCon = 6;
        nDam = DAMAGE_BONUS_20;
        nAC = 20;

        nAttack = 19;
        nHP = 350;
        nFort = 12;
        nReflex = 12;
        nDis = 25;

        nSpellImm1 = SPELL_BALAGARNSIRONHORN;
        nSpellImm2 = SPELL_EVARDS_BLACK_TENTACLES;

        nElemImmun = DAMAGE_TYPE_ELECTRICAL;
        nElemPerc = 100;
        //nAOE = TRUE;

        nHasNaturalWeapon = POLYMORPH_TYPE_RED_DRAGON;
        sMerge = MERGE_A + MERGE_H;
        sWeapon = "";
        sAllowedSpells = "_796_";
    }


    else if(nForm == POLYMORPH_TYPE_ANCIENT_GREEN_DRAGON)
    {
        nApp = APPEARANCE_TYPE_DRAGON_GREEN;
        sSkinResRef = "plmr_greendragon";

        nSTR = 8;
        nDEX = 6;
        nCon = 6;
        nDam = DAMAGE_BONUS_20;
        nAC = 20;

        nAttack = 19;
        nHP = 350;
        nFort = 12;
        nReflex = 12;
        nDis = 25;

        nSpellImm1 = SPELL_BALAGARNSIRONHORN;
        nSpellImm2 = SPELL_EVARDS_BLACK_TENTACLES;

        nElemImmun = DAMAGE_TYPE_ACID;
        nElemPerc = 100;
        //nAOE = TRUE;

        nHasNaturalWeapon = POLYMORPH_TYPE_RED_DRAGON;
        sMerge = MERGE_A + MERGE_H;
        sWeapon = "";
        sAllowedSpells = "_798_";
    }


//CONSTRUCT shape
    else if(nForm == 92) //golem flesh
    {
        nApp = APPEARANCE_TYPE_GOLEM_DEMONFLESH;
        sSkinResRef = "plmr_golem_df";

        nSTR = 5;
        nDam = DAMAGE_BONUS_10;
        nAC = 13;

        nAttack = 5;
        nHP = 90;

        nSpellImm1 = SPELL_BALAGARNSIRONHORN;
        nSpellImm2 = SPELL_EVARDS_BLACK_TENTACLES;

        nElemImmun = DAMAGE_TYPE_ELECTRICAL;
        nElemPerc = 100;

        nHasNaturalWeapon = 92;
        sMerge = MERGE_A + MERGE_I + MERGE_H;
        sWeapon = "";
    }


    else if(nForm == 91) //stone golem
    {
        nApp = APPEARANCE_TYPE_GOLEM_STONE;
        sSkinResRef = "plmr_golem_st";

        nSTR = 6;
        nDam = DAMAGE_BONUS_10;
        nAC = 13;

        nDis = 10;
        nAttack = 5;
        nHP = 90;

        nSpellImm1 = SPELL_BALAGARNSIRONHORN;
        nSpellImm2 = SPELL_EVARDS_BLACK_TENTACLES;

        nHasNaturalWeapon = 91;
        sMerge = MERGE_A + "_2_6_9_" + MERGE_H;
        sWeapon = "";

        /*
        if (nSD >= 10) {
          nSTR += 4;
          nDis += nSD * 2;
          nHP += nSD * 20;
          nHide += 3 * nSD / 2;
          nMS += 3 * nSD / 2;

          nReflex += nSD / 2;
          nSpot += nSD * 2;
          nDEX += nSD / 2;
          nCon += nSD / 3;
          nFort += nSD / 2;
        }*/

    }


    else if(nForm == 90) //iron golem
    {
        nApp = APPEARANCE_TYPE_GOLEM_IRON;
        sSkinResRef = "plmr_golem_ir";

        nSTR = 7;
        nDam = DAMAGE_BONUS_12;
        nAC = 15;

        nAttack = 5;
        nHP = 90;

        nSpellImm1 = SPELL_BALAGARNSIRONHORN;
        nSpellImm2 = SPELL_EVARDS_BLACK_TENTACLES;

        nElemImmun = DAMAGE_TYPE_ELECTRICAL;
        nElemPerc = 90;

        nHasNaturalWeapon = 90;
        sMerge = MERGE_A + MERGE_I + MERGE_H;
        sWeapon = "";
        sAllowedSpells = "_263_";
    }


//OUTSIDER shape
    else if((nForm == 85) || (nForm == 86))//Azer
    {
        if (GetGender(oPC) == GENDER_MALE)
            nApp = APPEARANCE_TYPE_AZER_MALE;
        else
            nApp = APPEARANCE_TYPE_AZER_FEMALE;
        sSkinResRef = "plmr_azer";

        nSTR = 7;
        nCon = 8;
        nAC = 13;
        nHP = 70;

        nElemImmun = DAMAGE_TYPE_FIRE;
        nElemPerc = 100;
        nElemImmun2 = DAMAGE_TYPE_COLD;
        nElemPerc2 = 50;


        nHasNaturalWeapon = FALSE;
        sMerge = MERGE_A + MERGE_I + MERGE_W;
        sWeapon = "plmr_flam_waraxe";
        sAllowedSpells = "_10_801_";
    }


    else if((nForm == 88) || (nForm == 89))//Rakshasa
    {
        if (GetGender(oPC) == GENDER_MALE)
            nApp = APPEARANCE_TYPE_RAKSHASA_TIGER_MALE;
        else
            nApp = APPEARANCE_TYPE_RAKSHASA_TIGER_FEMALE;

        sSkinResRef = "plmr_rakshasa";

        nSTR = 5;
        nDEX = 7;
        nAC = 29;

        nHP = 30;

        nHide = 20;
        nMS = 11;

        nSave = 2;
        nSpCr = 15;
        nSpot = 10;
        nDis = 5;

        if (nWiz > 0) {
           nArcaneCaster = nWiz;
        } else if (nSorc > 0) {
           nArcaneCaster = nSorc;
        }

        if (nArcaneCaster) {
           nDis += nArcaneCaster / 3;
           nSave += nArcaneCaster / 6;
           nHP += nArcaneCaster * 5;
           nSTR += nArcaneCaster / 5;
           nCon += nArcaneCaster / 5;

           sSkinResRef = "plmr_rakshasa_ma";
        }

        nHasNaturalWeapon = FALSE;
        sMerge = MERGE_A + MERGE_I + MERGE_W;
        sWeapon = "plmr_raks_staff";
        sAllowedSpells = "_368_523_41_";
    }


    else if(nForm == 87)  //slaad
    {
        nApp = APPEARANCE_TYPE_SLAAD_DEATH;
        sSkinResRef = "plmr_slaad";

        nSTR = 8;
        nDEX = 6;
        nCon = 6;
        nAC = 16;

        nHP = 100;
        nRegen = 10;
        fRegInterval = 6.0;

        nHasNaturalWeapon = APPEARANCE_TYPE_SLAAD_DEATH;
        sMerge = MERGE_A;
        sWeapon = "";
        sAllowedSpells = "_770_";
    }



//Druid Wildshape
    else if((nForm == POLYMORPH_TYPE_BROWN_BEAR) || (nForm == POLYMORPH_TYPE_DIRE_BROWN_BEAR))//bear
    {
        sSkinResRef = "plmr_empty";

        if (nForm == POLYMORPH_TYPE_BROWN_BEAR)
        {
            nApp = APPEARANCE_TYPE_BEAR_BROWN;

            nSTR = 6;
            nDEX = 3;
            nCon = 4;
            nHP = 10;
            nAC = 2;
        }

        else if (nForm == POLYMORPH_TYPE_DIRE_BROWN_BEAR)
        {
            nApp = APPEARANCE_TYPE_BEAR_DIRE;

            nSTR = 8;
            nDEX = 3;
            nCon = 4;
            nHP = 30;
            nAC = 4;
        }

        nHasNaturalWeapon = FALSE;
        sMerge = MERGE_A;
        sWeapon = "";
    }


    else if((nForm == POLYMORPH_TYPE_PANTHER) || (nForm == POLYMORPH_TYPE_DIRE_PANTHER)) //panter
    {
        sSkinResRef = "plmr_empty";

        if (nForm == POLYMORPH_TYPE_PANTHER)
        {
            nApp = APPEARANCE_TYPE_CAT_PANTHER;

            nSTR = 2;
            nDEX = 2;
            nCon = 6;
            nHP = 10;
            nAC = 4;
        }

        else if (nForm == POLYMORPH_TYPE_DIRE_PANTHER)
        {
            nApp = APPEARANCE_TYPE_CAT_MPANTHER;

            nSTR = 5;
            nDEX = 2;
            nCon = 4;
            nHP = 30;
            nAC = 6;
        }

        nHasNaturalWeapon = FALSE;
        sMerge = MERGE_A;
        sWeapon = "";
    }


    else if((nForm == POLYMORPH_TYPE_WOLF) || (nForm == POLYMORPH_TYPE_DIRE_WOLF)) //panter
    {
        sSkinResRef = "plmr_empty";

        if (nForm == POLYMORPH_TYPE_WOLF)
        {
            nApp = APPEARANCE_TYPE_DOG_WOLF;

            nSTR = 2;
            nDEX = 2;
            nCon = 4;
            nHP = 10;
            nAC = 4;
        }

        else if (nForm == POLYMORPH_TYPE_DIRE_WOLF)
        {
            nApp = APPEARANCE_TYPE_DOG_DIRE_WOLF;

            nSTR = 5;
            nDEX = 2;
            nCon = 5;
            nHP = 30;
            nAC = 6;
        }

        nHasNaturalWeapon = FALSE;
        sMerge = MERGE_A;
        sWeapon = "";
    }


    else if((nForm == POLYMORPH_TYPE_BOAR) || (nForm == POLYMORPH_TYPE_DIRE_BOAR)) //panter
    {
        sSkinResRef = "plmr_empty";

        if (nForm == POLYMORPH_TYPE_BOAR)
        {
            nApp = APPEARANCE_TYPE_BOAR;

            nSTR = 2;
            //nDEX = 2;
            nCon = 3;
            nHP = 10;
            nAC = 4;
        }

        else if (nForm == POLYMORPH_TYPE_DIRE_BOAR)
        {
            nApp = APPEARANCE_TYPE_BOAR_DIRE;

            nSTR = 6;
            //nDEX = 2;
            nCon = 3;
            nHP = 20;
            nAC = 6;
        }

        nHasNaturalWeapon = FALSE;
        sMerge = MERGE_A;
        sWeapon = "";
    }


    else if((nForm == POLYMORPH_TYPE_BADGER) || (nForm == POLYMORPH_TYPE_DIRE_BADGER)) //panter
    {
        sSkinResRef = "plmr_empty";

        if (nForm == POLYMORPH_TYPE_BADGER)
        {
            nApp = APPEARANCE_TYPE_BADGER;

            //nSTR = 2;
            nDEX = 3;
            nCon = 2;
            nHP = 10;
            nAC = 5;
        }

        else if (nForm == POLYMORPH_TYPE_DIRE_BADGER)
        {
            nApp = APPEARANCE_TYPE_BADGER_DIRE;

            //nSTR = 6;
            nDEX = 2;
            nCon = 4;
            nHP = 20;
            nAC = 8;
        }

        nHasNaturalWeapon = FALSE;
        sMerge = MERGE_A;
        sWeapon = "";
    }





//Polymorph Self
    else if(nForm == POLYMORPH_TYPE_GIANT_SPIDER)
    {
        nApp = APPEARANCE_TYPE_SPIDER_GIANT;
        sSkinResRef = "plmr_gspider";

        nSTR = 5;
        nDEX = 3;
        nAC = 5;

        nHP = 30;

        nHasNaturalWeapon = POLYMORPH_TYPE_GIANT_SPIDER;
        sMerge = "_";
        sWeapon = "";
    }


    else if(nForm == POLYMORPH_TYPE_PIXIE)
    {
        nApp = APPEARANCE_TYPE_FAIRY;
        sSkinResRef = "plmr_pixie";

        nDEX = 8;
        nAC = 5;
        nHP = 10;

        nHasNaturalWeapon = POLYMORPH_TYPE_PIXIE;
        sMerge = "_";
        sWeapon = "";
    }


    else if(nForm == POLYMORPH_TYPE_TROLL)
    {
        nApp = APPEARANCE_TYPE_TROLL;
        sSkinResRef = "plmr_empty";

        nSTR = 5;
        nCon = 5;
        nAC = 5;

        nHP = 10;
        nRegen = 5;
        fRegInterval = 6.0;

        nHasNaturalWeapon = POLYMORPH_TYPE_TROLL;
        sMerge = "_";
        sWeapon = "";
    }


    else if(nForm == POLYMORPH_TYPE_UMBER_HULK)
    {
        nApp = APPEARANCE_TYPE_UMBERHULK;
        sSkinResRef = "plmr_uhulk";

        nSTR = 5;
        nDEX = 2;
        nCon = 4;
        nAC = 5;

        nHP = 30;

        nHasNaturalWeapon = POLYMORPH_TYPE_UMBER_HULK;
        sMerge = "_";
        sWeapon = "";
    }


    else if(nForm == POLYMORPH_TYPE_ZOMBIE)
    {
        nApp = APPEARANCE_TYPE_ZOMBIE;
        sSkinResRef = "plmr_zombie";

        nSTR = 2;
        nDEX = 2;
        nCon = 2;

        nHP = 40;

        nHasNaturalWeapon = POLYMORPH_TYPE_ZOMBIE;
        sMerge = "_";
        sWeapon = "";
    }




//SHAPECHANGE
    else if(nForm == POLYMORPH_TYPE_RED_DRAGON)
    {
        nApp = APPEARANCE_TYPE_DRAGON_RED;
        sSkinResRef = "plmr_red_dragon1";

        nSTR = 5;
        nDEX = 5;
        nCon = 5;
        nDam = DAMAGE_BONUS_20;
        nAC = 10;

        nAttack = 10;
        nHP = 250;
        nFort = 5;
        nReflex = 5;

        nSpellImm1 = SPELL_BALAGARNSIRONHORN;
        nSpellImm2 = SPELL_EVARDS_BLACK_TENTACLES;

        nElemImmun = DAMAGE_TYPE_FIRE;
        nElemPerc = 100;

        nHasNaturalWeapon = POLYMORPH_TYPE_RED_DRAGON;
        sMerge = "_";
        sWeapon = "";
    }

    else if(nForm == POLYMORPH_TYPE_IRON_GOLEM)
    {
        nApp = APPEARANCE_TYPE_GOLEM_IRON;
        sSkinResRef = "plmr_golem_ir1";

        nSTR = 5;
        nDam = DAMAGE_BONUS_12;
        nAC = 10;

        nAttack = 5;
        nHP = 300;

        nHasNaturalWeapon = POLYMORPH_TYPE_IRON_GOLEM;
        sMerge = "_";
        sWeapon = "";
    }

    else if(nForm == POLYMORPH_TYPE_BALOR)
    {
        nApp = APPEARANCE_TYPE_BALOR;
        sSkinResRef = "plmr_balor";

        nSTR = 3;
        nDEX = 8;
        nCon = 3;
        nAC = 10;

        nAttack = 3;
        nHP = 250;

        nElemImmun = DAMAGE_TYPE_ELECTRICAL;
        nElemPerc = 100;

        nHasNaturalWeapon = FALSE;
        sMerge = "_";
        sWeapon = "plmr_balor_sword";
    }


    else if(nForm == POLYMORPH_TYPE_FIRE_GIANT)
    {
        if (GetGender(oPC) == GENDER_MALE)
            nApp = APPEARANCE_TYPE_GIANT_FIRE;
        else
            nApp = APPEARANCE_TYPE_GIANT_FIRE_FEMALE;

        sSkinResRef = "plmr_fgiant";

        nSTR = 8;
        nDEX = 8;
        nCon = 6;
        nDam = DAMAGE_BONUS_20;
        nAC = 10;

        nAttack = 8;
        nHP = 200;

        nElemImmun = DAMAGE_TYPE_FIRE;
        nElemPerc = 100;

        nHasNaturalWeapon = POLYMORPH_TYPE_FIRE_GIANT;
        sMerge = "_";
        sWeapon = "";
    }

    else if(nForm == POLYMORPH_TYPE_DEATH_SLAAD)
    {
        if (GetGender(oPC) == GENDER_MALE)
            nApp = APPEARANCE_TYPE_SLAAD_WHITE;
        else
            nApp = APPEARANCE_TYPE_SLAAD_WHITE;

        sSkinResRef = "plmr_slaad1";

        nSTR = 4;
        nDEX = 10;
        nCon = 4;
        nAC = 10;
        nHP = 225;

        nRegen = 5;
        fRegInterval = 6.0;

        nHasNaturalWeapon = POLYMORPH_TYPE_DEATH_SLAAD;
        sMerge = "_";
        sWeapon = "";
        sAllowedSpells = "_36_90_58_157_76_54_56_41_87_";
    }





//ELEMENTAL SHAPE
    else if(nForm == POLYMORPH_TYPE_HUGE_FIRE_ELEMENTAL)//FIRE
    {
        if (GetGender(oPC) == GENDER_MALE)
            nApp = APPEARANCE_TYPE_ELEMENTAL_FIRE;
        else
            nApp = APPEARANCE_TYPE_ELEMENTAL_FIRE;

        sSkinResRef = "plmr_elfire";

        nSTR = 4;
        nDEX = 4;
        nCon = 8;
        nDam = DAMAGE_BONUS_1d8;
        nDamType = DAMAGE_TYPE_FIRE;
        nAC = 5;

        nElemImmun = DAMAGE_TYPE_FIRE;
        nElemPerc = 100;

        nHasNaturalWeapon = POLYMORPH_TYPE_HUGE_FIRE_ELEMENTAL;
        sMerge = MERGE_A;
        sWeapon = "";
    }

    else if(nForm == POLYMORPH_TYPE_HUGE_WATER_ELEMENTAL) //WATER
    {
        if (GetGender(oPC) == GENDER_MALE)
            nApp = APPEARANCE_TYPE_ELEMENTAL_WATER;
        else
            nApp = APPEARANCE_TYPE_ELEMENTAL_WATER;

        sSkinResRef = "plmr_elwater";

        nSTR = 6;
        nDEX = 6;
        nCon = 5;
        nAC = 10;

        nElemImmun = DAMAGE_TYPE_FIRE;
        nElemPerc = 100;

        nHasNaturalWeapon = POLYMORPH_TYPE_HUGE_WATER_ELEMENTAL;
        sMerge = MERGE_A;
        sWeapon = "";
        sAllowedSpells = "_437_";
    }

    else if(nForm == POLYMORPH_TYPE_HUGE_EARTH_ELEMENTAL) //EARTH
    {
        if (GetGender(oPC) == GENDER_MALE)
            nApp = APPEARANCE_TYPE_ELEMENTAL_EARTH;
        else
            nApp = APPEARANCE_TYPE_ELEMENTAL_EARTH;

        sSkinResRef = "plmr_elearth";

        nSTR = 8;
        nDEX = 2;
        nCon = 6;
        nAC = 5;

        nHasNaturalWeapon = POLYMORPH_TYPE_HUGE_WATER_ELEMENTAL;
        sMerge = MERGE_A;
        sWeapon = "";
    }


    else if(nForm == POLYMORPH_TYPE_HUGE_AIR_ELEMENTAL) //AIR
    {
        if (GetGender(oPC) == GENDER_MALE)
            nApp = APPEARANCE_TYPE_ELEMENTAL_AIR;
        else
            nApp = APPEARANCE_TYPE_ELEMENTAL_AIR;

        sSkinResRef = "plmr_elair";

        nSTR = 4;
        nDEX = 8;
        nCon = 4;
        nAC = 12;

        nHasNaturalWeapon = POLYMORPH_TYPE_HUGE_FIRE_ELEMENTAL;
        sMerge = MERGE_A;
        sWeapon = "";
    }



//Elder
    else if(nForm == POLYMORPH_TYPE_ELDER_FIRE_ELEMENTAL)//FIRE
    {
        if (GetGender(oPC) == GENDER_MALE)
            nApp = APPEARANCE_TYPE_ELEMENTAL_FIRE_ELDER;
        else
            nApp = APPEARANCE_TYPE_ELEMENTAL_FIRE_ELDER;

        sSkinResRef = "plmr_elfire";

        nSTR = 6;
        nDEX = 4;
        nCon = 10;
        nDam = DAMAGE_BONUS_1d8;
        nDamType = DAMAGE_TYPE_FIRE;
        nAC = 6;

        nElemImmun = DAMAGE_TYPE_FIRE;
        nElemPerc = 100;

        nHasNaturalWeapon = POLYMORPH_TYPE_HUGE_FIRE_ELEMENTAL;
        sMerge = MERGE_A;
        sWeapon = "";
    }

    else if(nForm == POLYMORPH_TYPE_ELDER_WATER_ELEMENTAL) //WATER
    {
        if (GetGender(oPC) == GENDER_MALE)
            nApp = APPEARANCE_TYPE_ELEMENTAL_WATER_ELDER;
        else
            nApp = APPEARANCE_TYPE_ELEMENTAL_WATER_ELDER;

        sSkinResRef = "plmr_elwater";

        nSTR = 8;
        nDEX = 6;
        nCon = 7;
        nAC = 10;

        nElemImmun = DAMAGE_TYPE_FIRE;
        nElemPerc = 100;

        nHasNaturalWeapon = POLYMORPH_TYPE_HUGE_WATER_ELEMENTAL;
        sMerge = MERGE_A;
        sWeapon = "";
        sAllowedSpells = "_437_";
    }

    else if(nForm == POLYMORPH_TYPE_ELDER_EARTH_ELEMENTAL) //EARTH
    {
        if (GetGender(oPC) == GENDER_MALE)
            nApp = APPEARANCE_TYPE_ELEMENTAL_EARTH_ELDER;
        else
            nApp = APPEARANCE_TYPE_ELEMENTAL_EARTH_ELDER;

        sSkinResRef = "plmr_elearth";

        nSTR = 10;
        nDEX = 2;
        nCon = 6;
        nAC = 8;

        nHasNaturalWeapon = POLYMORPH_TYPE_HUGE_WATER_ELEMENTAL;
        sMerge = MERGE_A;
        sWeapon = "";
    }


    else if(nForm == POLYMORPH_TYPE_ELDER_AIR_ELEMENTAL) //AIR
    {
        if (GetGender(oPC) == GENDER_MALE)
            nApp = APPEARANCE_TYPE_ELEMENTAL_AIR_ELDER;
        else
            nApp = APPEARANCE_TYPE_ELEMENTAL_AIR_ELDER;

        sSkinResRef = "plmr_elair";

        nSTR = 6;
        nDEX = 10;
        nCon = 4;
        nAC = 12;

        nHasNaturalWeapon = POLYMORPH_TYPE_HUGE_FIRE_ELEMENTAL;
        sMerge = MERGE_A;
        sWeapon = "";
    }



//GREATER WILDSHAPE I
    else if(nForm == POLYMORPH_TYPE_WYRMLING_BLACK)
    {
        if (GetGender(oPC) == GENDER_MALE)
            nApp = APPEARANCE_TYPE_WYRMLING_BLACK;
        else
            nApp = APPEARANCE_TYPE_WYRMLING_BLACK;

        sSkinResRef = "plmr_wyrbl";

        nSTR = 2;
        nDEX = 4;
        nAC = 5;
        nHP = 15;

        nElemImmun = DAMAGE_TYPE_ACID;
        nElemPerc = 100;

        nHasNaturalWeapon = POLYMORPH_TYPE_WYRMLING_BLACK;// =56
        sMerge = MERGE_A + MERGE_I;
        sAllowedSpells = "_664_667_666_665_663_";
    }

    else if(nForm == POLYMORPH_TYPE_WYRMLING_BLUE)
    {
        if (GetGender(oPC) == GENDER_MALE)
            nApp = APPEARANCE_TYPE_WYRMLING_BLUE;
        else
            nApp = APPEARANCE_TYPE_WYRMLING_BLUE;

        sSkinResRef = "plmr_wyrbe";

        nSTR = 2;
        nCon = 2;
        nAC = 5;
        nHP = 15;

        nElemImmun = DAMAGE_TYPE_ELECTRICAL;
        nElemPerc = 100;

        nHasNaturalWeapon = POLYMORPH_TYPE_WYRMLING_BLUE;// =53
        sMerge = MERGE_A + MERGE_I;
        sAllowedSpells = "_664_667_666_665_663_";
    }

    else if(nForm == POLYMORPH_TYPE_WYRMLING_GREEN)
    {
        if (GetGender(oPC) == GENDER_MALE)
            nApp = APPEARANCE_TYPE_WYRMLING_GREEN;
        else
            nApp = APPEARANCE_TYPE_WYRMLING_GREEN;

        sSkinResRef = "plmr_wyrbl"; //Equal to black

        nSTR = 2;
        nCon = 3;
        nAC = 5;
        nHP = 15;

        nElemImmun = DAMAGE_TYPE_ACID;
        nElemPerc = 100;

        nHasNaturalWeapon = POLYMORPH_TYPE_WYRMLING_GREEN;// =55
        sMerge = MERGE_A + MERGE_I;
        sAllowedSpells = "_664_667_666_665_663_";
    }

    else if(nForm == POLYMORPH_TYPE_WYRMLING_RED)
    {
        if (GetGender(oPC) == GENDER_MALE)
            nApp = APPEARANCE_TYPE_WYRMLING_RED;
        else
            nApp = APPEARANCE_TYPE_WYRMLING_RED;

        sSkinResRef = "plmr_wyrrd";

        nSTR = 3;
        nCon = 2;
        nAC = 5;
        nHP = 15;

        nElemImmun = DAMAGE_TYPE_FIRE;
        nElemPerc = 100;

        nHasNaturalWeapon = POLYMORPH_TYPE_WYRMLING_RED;// =54
        sMerge = MERGE_A + MERGE_I;
        sAllowedSpells = "_664_667_666_665_663_";
    }

    else if(nForm == POLYMORPH_TYPE_WYRMLING_WHITE)
    {
        if (GetGender(oPC) == GENDER_MALE)
            nApp = APPEARANCE_TYPE_WYRMLING_WHITE;
        else
            nApp = APPEARANCE_TYPE_WYRMLING_WHITE;

        sSkinResRef = "plmr_wyrwh";

        nSTR = 2;
        nDEX = 4;
        nAC = 5;
        nHP = 15;

        nElemImmun = DAMAGE_TYPE_COLD;
        nElemPerc = 100;

        nHasNaturalWeapon = POLYMORPH_TYPE_WYRMLING_BLACK;// =56 Equal to white
        sMerge = MERGE_A + MERGE_I;
        sAllowedSpells = "_664_667_666_665_663_";
    }



//GREATER WILDSHAPE II
    else if(nForm == POLYMORPH_TYPE_HARPY)
    {
        if (GetGender(oPC) == GENDER_MALE)
            nApp = APPEARANCE_TYPE_HARPY;  // = 419
        else
            nApp = APPEARANCE_TYPE_HARPY;

        sSkinResRef = "plmr_harpy";

        nSTR = 5;
        nDEX = 5;
        nAC = 8;
        nHP = 20;

        nHasNaturalWeapon = POLYMORPH_TYPE_HARPY; // = 60
        sMerge = MERGE_A + MERGE_I;
        sWeapon = "";
        sAllowedSpells = "_686_";
    }



    else if(nForm == POLYMORPH_TYPE_GARGOYLE)
    {
        if (GetGender(oPC) == GENDER_MALE)
            nApp = APPEARANCE_TYPE_GARGOYLE;  // = 73
        else
            nApp = APPEARANCE_TYPE_GARGOYLE;

        sSkinResRef = "plmr_gargoyle";

        nDEX = 5;
        nCon = 5;
        nAC = 8;
        nHP = 20;

        nHasNaturalWeapon = POLYMORPH_TYPE_GARGOYLE; // = 65
        sMerge = MERGE_A + MERGE_I;
        sWeapon = "";
    }


    else if(nForm == POLYMORPH_TYPE_MINOTAUR)// = 66
    {
        if (GetGender(oPC) == GENDER_MALE)
            nApp = APPEARANCE_TYPE_MINOTAUR;  // = 120
        else
            nApp = APPEARANCE_TYPE_MINOTAUR;

        sSkinResRef = "plmr_minotaur";

        nSTR = 6;
        nCon = 4;
        nAC = 6;
        nHP = 25;

        nHasNaturalWeapon = FALSE;
        sMerge = MERGE_A + MERGE_I + MERGE_W;
        if(nSize<3)
            sWeapon = "plmr_taur_axe_s";
        else
            sWeapon = "plmr_taur_axe";
    }




//Greater Wildshape III
    else if(nForm == POLYMORPH_TYPE_BASILISK)// = 61
    {
        if (GetGender(oPC) == GENDER_MALE)
            nApp = APPEARANCE_TYPE_BASILISK;  // = 369
        else
            nApp = APPEARANCE_TYPE_BASILISK;

        sSkinResRef = "plmr_basilisk";

        nSTR = 4;
        nAC = 10;
        nHP = 30;

        nHasNaturalWeapon = POLYMORPH_TYPE_BASILISK;
        sMerge = MERGE_A;
        sWeapon = "";
        sAllowedSpells = "_687_";
    }



    else if(nForm == POLYMORPH_TYPE_DRIDER)// = 62
    {
        if (GetGender(oPC) == GENDER_MALE)
            nApp = APPEARANCE_TYPE_DRIDER;  // = 406
        else
            nApp = APPEARANCE_TYPE_DRIDER;

        sSkinResRef = "plmr_drider";

        nSTR = 4;
        nDEX = 4;
        nCon = 3;
        nAC = 8;
        nHP = 20;

        nHasNaturalWeapon = FALSE;
        sMerge = MERGE_A + MERGE_I + MERGE_W;
        if(nSize<3)
            sWeapon = "plmr_drid_trid";
        else
            sWeapon = "plmr_drid_spear";

        sAllowedSpells = "_688_";
    }



    else if(nForm == POLYMORPH_TYPE_MANTICORE)// = 58
    {
        if (GetGender(oPC) == GENDER_MALE)
            nApp = APPEARANCE_TYPE_MANTICORE;  // = 366
        else
            nApp = APPEARANCE_TYPE_MANTICORE;

        sSkinResRef = "plmr_manticore";

        nSTR = 6;
        nDEX = 5;
        nCon = 3;
        nAC = 7;
        nHP = 30;

        nHasNaturalWeapon = POLYMORPH_TYPE_MANTICORE;
        sMerge = MERGE_A;
        sWeapon = "";
        sAllowedSpells = "_692_";
    }






//Humanoid Shape
    else if((nForm == POLYMORPH_TYPE_MALE_DROW) || (nForm == POLYMORPH_TYPE_FEMALE_DROW))// = 59 / 70
    {
        if (GetGender(oPC) == GENDER_MALE)
            nApp = APPEARANCE_TYPE_DROW_WARRIOR_1;
        else
            nApp = APPEARANCE_TYPE_DROW_FEMALE_1;

        sSkinResRef = "plmr_drow";

        nSTR = 5;
        nDEX = 6;
        nAC = 8;
        nHP = 30;

        nHasNaturalWeapon = FALSE;
        sMerge = MERGE_A + MERGE_I + MERGE_W;
        sWeapon = "plmr_drow_sword";
        sAllowedSpells = "_688_";
    }


    else if(nForm == 82)// LIZARD
    {
        if (GetGender(oPC) == GENDER_MALE)
            nApp = APPEARANCE_TYPE_LIZARDFOLK_A; //134
        else
            nApp = APPEARANCE_TYPE_LIZARDFOLK_A;

        sSkinResRef = "plmr_lizard";

        nSTR = 4;
        nDEX = 8;
        nAC = 9;
        nHP = 35;
        nSave = 2;
        nDis = 10;
        nLis = 4;

        nHasNaturalWeapon = FALSE;
        sMerge = MERGE_A + MERGE_I + MERGE_W;
        sWeapon = "plmr_liz_whip";
    }


    else if(nForm == 83)// Kobold
    {
        if (GetGender(oPC) == GENDER_MALE)
            nApp = APPEARANCE_TYPE_KOBOLD_A; //302
        else
            nApp = APPEARANCE_TYPE_KOBOLD_A;

        sSkinResRef = "plmr_kobold";

        nDEX = 10;
        nAC = 10;
        nHP = 10;

        nHide = 10;
        nMS = 10;
        nSpot = 5;
        nLis = 5;
        nOpL = 7;
        nSetTr = 7;
        nTum = 10;

        nHasNaturalWeapon = FALSE;
        sMerge = MERGE_A + MERGE_I + MERGE_W;
        sWeapon = "plmr_kob_sword";
    }





//Greater Wildshape IV
    else if(nForm == POLYMORPH_TYPE_DIRETIGER)// Tiger  =69
    {
        if (GetGender(oPC) == GENDER_MALE)
            nApp = APPEARANCE_TYPE_CAT_CAT_DIRE; //95
        else
            nApp = APPEARANCE_TYPE_CAT_CAT_DIRE;

        sSkinResRef = "plmr_empty";

        nSTR = 8;
        nDEX = 4;
        nCon = 3;
        nAC = 8;
        nHP = 60;

        nHasNaturalWeapon = POLYMORPH_TYPE_DIRETIGER;
        sMerge = MERGE_A;
        sWeapon = "";
    }


    else if(nForm == POLYMORPH_TYPE_MEDUSA)// Medusa  =64
    {
        if (GetGender(oPC) == GENDER_MALE)
            nApp = APPEARANCE_TYPE_MEDUSA; //352
        else
            nApp = APPEARANCE_TYPE_MEDUSA;

        sSkinResRef = "plmr_medusa";

        nSTR = 8;
        nDEX = 4;
        nAC = 10;
        nHP = 35;

        nHasNaturalWeapon = POLYMORPH_TYPE_MEDUSA;
        sMerge = MERGE_A + MERGE_I;
        sWeapon = "";
        sAllowedSpells = "_687_";
    }


    else if(nForm == POLYMORPH_TYPE_MINDFLAYER)// Mindflayer  =68
    {
        if (GetGender(oPC) == GENDER_MALE)
            nApp = APPEARANCE_TYPE_MINDFLAYER; //413
        else
            nApp = APPEARANCE_TYPE_MINDFLAYER;

        sSkinResRef = "plmr_mindflayer";

        nDEX = 6;
        nAC = 7;
        nHP = 30;

        nSpot = 6;
        nLis = 6;

        nHasNaturalWeapon = POLYMORPH_TYPE_MINDFLAYER;
        sMerge = MERGE_A + MERGE_I;
        sWeapon = "";
        sAllowedSpells = "_693_741_";
    }





//EPIC WILDSHAPE II
    else if(nForm == 97) //Epic Harpy
    {
        if (GetGender(oPC) == GENDER_MALE)
            nApp = APPEARANCE_TYPE_HARPY;  // = 419
        else
            nApp = APPEARANCE_TYPE_HARPY;

        sSkinResRef = "plmr_harpy";

        nSTR = 7;
        nDEX = 7;
        nAC = 11;
        nHP = 40;

        nHasNaturalWeapon = 97;
        sMerge = MERGE_A + MERGE_I;
        sWeapon = "";
        sAllowedSpells = "_686_";
    }



    else if(nForm == 98) //Epic Gargoyle
    {
        if (GetGender(oPC) == GENDER_MALE)
            nApp = APPEARANCE_TYPE_GARGOYLE;  // = 73
        else
            nApp = APPEARANCE_TYPE_GARGOYLE;

        sSkinResRef = "plmr_gargoyle1";

        nDEX = 7;
        nCon = 7;
        nAC = 12;
        nHP = 60;

        nHasNaturalWeapon = 98;
        sMerge = MERGE_A + MERGE_I;
        sWeapon = "";
    }


    else if(nForm == 96)// Epic Minotaur
    {
        if (GetGender(oPC) == GENDER_MALE)
            nApp = APPEARANCE_TYPE_MINOTAUR_CHIEFTAIN;  // = 121
        else
            nApp = APPEARANCE_TYPE_MINOTAUR_CHIEFTAIN;

        sSkinResRef = "plmr_minotaur";

        nSTR = 9;
        nCon = 7;
        nAC = 10;
        nHP = 50;

        nHasNaturalWeapon = FALSE;
        sMerge = MERGE_A + MERGE_I + MERGE_W;

        if(nSize<3)
            sWeapon = "plmr_taur_axe1_s";
        else
            sWeapon = "plmr_taur_axe1";
    }






//EPIC Wildshape III
    else if(nForm == 99) // BASILISK
    {
        if (GetGender(oPC) == GENDER_MALE)
            nApp = APPEARANCE_TYPE_BASILISK;  // = 369
        else
            nApp = APPEARANCE_TYPE_BASILISK;

        sSkinResRef = "plmr_basilisk";

        nSTR = 5;
        nDEX = 5;
        nAC = 10;
        nHP = 60;

        nHasNaturalWeapon = POLYMORPH_TYPE_BASILISK;
        sMerge = MERGE_A;
        sWeapon = "";
        sAllowedSpells = "_687_";
    }



    else if(nForm == 100) // DRIDER
    {
        if (GetGender(oPC) == GENDER_MALE)
            nApp = APPEARANCE_TYPE_DRIDER;  // = 406
        else
            nApp = APPEARANCE_TYPE_DRIDER;

        sSkinResRef = "plmr_drider1";

        nSTR = 8;
        nDEX = 5;
        nCon = 6;
        nAC = 8;
        nHP = 60;

        nHide = 8;
        nMS = 8;

        nHasNaturalWeapon = FALSE;
        sMerge = MERGE_A + MERGE_I + MERGE_W;
        if(nSize<3)
            sWeapon = "plmr_drid_trid1";
        else
            sWeapon = "plmr_drid_spear1";

        sAllowedSpells = "_688_107_";
    }



    else if(nForm == 101)// MANTICORE
    {
        if (GetGender(oPC) == GENDER_MALE)
            nApp = APPEARANCE_TYPE_MANTICORE;  // = 366
        else
            nApp = APPEARANCE_TYPE_MANTICORE;

        sSkinResRef = "plmr_manticore1";

        nSTR = 6;
        nDEX = 5;
        nCon = 3;
        nAC = 12;
        nHP = 60;

        nHasNaturalWeapon = 101;
        sMerge = MERGE_A;
        sWeapon = "";
        sAllowedSpells = "_692_";
    }



    //EPIC Humanoid Shape
    else if((nForm == 105) || (nForm == 106))// DROW
    {
        if (GetGender(oPC) == GENDER_MALE)
            nApp = 409;
        else
            nApp = 410;

        sSkinResRef = "plmr_drow1";

        nDEX = 6;
        nAC = 10;
        nHP = 30;

        nHasNaturalWeapon = FALSE;
        sMerge = MERGE_A + MERGE_I + MERGE_W;
        sWeapon = "plmr_drow_staff";
        sAllowedSpells = "_107_90_78_157_368_76_447_72_87_";
    }


    else if(nForm == 104)// LIZARD
    {
        if (GetGender(oPC) == GENDER_MALE)
            nApp = 130;
        else
            nApp = 130;

        sSkinResRef = "plmr_lizard1";

        nSTR = 8;
        nDEX = 8;
        nAC = 12;
        nHP = 75;
        nSave = 4;
        nDis = 15;
        nLis = 8;

        nHasNaturalWeapon = FALSE;
        sMerge = MERGE_A + MERGE_I + MERGE_W;
        sWeapon = "plmr_liz_whip1";
    }


    else if(nForm == 103)// Kobold
    {
        if (GetGender(oPC) == GENDER_MALE)
            nApp = APPEARANCE_TYPE_KOBOLD_A; //302
        else
            nApp = APPEARANCE_TYPE_KOBOLD_A;

        sSkinResRef = "plmr_kobold1";

        nDEX = 12;
        nAC = 13;
        nHP = 70;

        nHide = 20;
        nMS = 20;
        nSpot = 10;
        nLis = 10;
        nOpL = 20;
        nSetTr = 20;
        nTum = 10;

        nHasNaturalWeapon = FALSE;
        sMerge = MERGE_A + MERGE_I + MERGE_W;
        sWeapon = "plmr_osa";
        sAllowedSpells = "_90_";
    }




    /*
    else if(nForm == default)
    {
        if (GetGender(oPC) == GENDER_MALE)
            nApp = ;
        else
            nApp = ;

        sSkinResRef = "";

        nSTR = ;
        nDEX = ;
        nCon = ;
        nDam = ;
        nDamType = ;
        nAC = ;

        nAttack = ;
        nHP = ;
        nFort = ;
        nReflex = ;
        nRegen = ;
        fRegInterval = 6.0;

        nHide = ;
        nMS = ;
        nConc = ;

        nSpellImm1 = ;
        nSpellImm2 = ;

        nSave = ;
        nSpCr = ;
        nSpot = ;
        nDis = ;
        nLis = ;
        nOpL = ;
        nSetTr = ;
        nTum = ;


        nHasNaturalWeapon = FALSE;
        sMerge = MERGE_A + MERGE_I + MERGE_W;
        sWeapon = "";
    }
    */



    SetLocalInt(oPC, "PPM_App", nApp);
    SetLocalString(oPC, "PPM_Skin", sSkinResRef);

    if(nSTR)/*1 */
        SetLocalInt(oPC, "PPM_STR", nSTR);

    if(nDEX)/*2 */
        SetLocalInt(oPC, "PPM_DEX", nDEX);

    if(nCon)/*3 */
        SetLocalInt(oPC, "PPM_Con", nCon);

    if(nDam)/*4 */
        SetLocalInt(oPC, "PPM_Damage", nDam);

            /*4.1*/
    SetLocalInt(oPC, "PPM_DamType", nDamType);


    if(nAC)/*5 */
    {
        ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectACDecrease(1, AC_NATURAL_BONUS), oPC, 0.3);
        SetLocalInt(oPC, "PPM_AC", nAC);
    }

    if(nAttack)/*6 */
        SetLocalInt(oPC, "PPM_Attack", nAttack);

    if(nHP)/*7 */
        SetLocalInt(oPC, "PPM_HP", nHP);

    if(nFort)/*8 */
        SetLocalInt(oPC, "PPM_Fort", nFort);

    if(nReflex)/*13 */
        SetLocalInt(oPC, "PPM_Reflex", nReflex);

    if(nRegen)/*9 */
    {
        SetLocalInt(oPC, "PPM_Regen", nRegen);
        if(fRegInterval == 0.0)
            fRegInterval = 6.0;
        SetLocalFloat(oPC, "PPM_RegInterval", fRegInterval);
    }


    if(nHide)/*10 */
    {
        int nHideBase = GetSkillRank(SKILL_HIDE, oPC, TRUE);
        int nHideAll = GetSkillRank(SKILL_HIDE, oPC);
        nHide = nHide + nHideAll - nHideBase - GetAbilityModifier(ABILITY_DEXTERITY, oPC) - /*bZ 23.10.2014 - bard song */GetLocalInt(oPC,"BS_Skill");
        SetLocalInt(oPC, "PPM_Hide", nHide);
    }

    if(nMS)/*11 */
    {
        int nMSBase = GetSkillRank(SKILL_MOVE_SILENTLY, oPC, TRUE);
        int nMSAll = GetSkillRank(SKILL_MOVE_SILENTLY, oPC);
        nMS = nMS+nMSAll - nMSBase - GetAbilityModifier(ABILITY_DEXTERITY, oPC) - /*bZ 23.10.2014 - bard song */GetLocalInt(oPC,"BS_Skill");
        SetLocalInt(oPC, "PPM_MS", nMS);
    }

    if(nConc)/*12 */
        SetLocalInt(oPC, "PPM_Conc", nConc);

    if(nSpellImm1 > -1)/*14*/
        SetLocalInt(oPC, "PPM_SpellImm1", nSpellImm1);

    if(nSpellImm2 > -1)/*15*/
        SetLocalInt(oPC, "PPM_SpellImm2", nSpellImm2);


    if(nSave)/*16*/
        SetLocalInt(oPC, "PPM_Save", nSave);

    if(nSpCr)/*17*/
        SetLocalInt(oPC, "PPM_SpCr", nSpCr);

    if(nSpot)/*18*/
    {
        int nSpotBase = GetSkillRank(SKILL_SPOT, oPC, TRUE);
        int nSpotAll = GetSkillRank(SKILL_SPOT, oPC);
        nSpot = nSpot + nSpotAll - nSpotBase - GetAbilityModifier(ABILITY_WISDOM, oPC) - /*bZ 23.10.2014 - bard song */GetLocalInt(oPC,"BS_Skill");
        SetLocalInt(oPC, "PPM_Spot", nSpot);
    }
    if(nDis)/*19*/
    {
        int nDisBase = GetSkillRank(SKILL_DISCIPLINE, oPC, TRUE);
        int nDisAll = GetSkillRank(SKILL_DISCIPLINE, oPC);
        nDis = nDis + nDisAll - nDisBase - GetAbilityModifier(ABILITY_CONSTITUTION, oPC) - /*bZ 23.10.2014 - bard song */GetLocalInt(oPC,"BS_Skill");
        if(GetHasFeat(FEAT_EPIC_SKILL_FOCUS_DISCIPLINE))
            nDis = nDis-10;

        SetLocalInt(oPC, "PPM_Dis", nDis);
    }
    if(nLis)/*20*/
    {
        int nLisBase = GetSkillRank(SKILL_LISTEN, oPC, TRUE);
        int nLisAll = GetSkillRank(SKILL_LISTEN, oPC);
        nLis = nLis + nLisAll - nLisBase - GetAbilityModifier(ABILITY_WISDOM, oPC) - /*bZ 23.10.2014 - bard song */GetLocalInt(oPC,"BS_Skill");
        SetLocalInt(oPC, "PPM_Lis", nLis);
    }
    if(nOpL)/*21*/
        SetLocalInt(oPC, "PPM_OpL", nOpL);

    if(nSetTr)/*22*/
        SetLocalInt(oPC, "PPM_SetTr", nSetTr);

    if(nTum)/*23*/
        SetLocalInt(oPC, "PPM_Tum", nTum);

    if(nElemImmun)/*24*/
    {
        SetLocalInt(oPC, "PPM_ElemImmun", nElemImmun);
        SetLocalInt(oPC, "PPM_ElemPerc", nElemPerc);
    }

    if(nElemImmun2)/*25*/
    {
        SetLocalInt(oPC, "PPM_ElemImmun2", nElemImmun2);
        SetLocalInt(oPC, "PPM_ElemPerc2", nElemPerc2);
    }
    /*
    if(nAOE)//26
        SetLocalInt(oPC, "PPM_AOE", nAOE);*/



    if(nHasNaturalWeapon)
        SetLocalInt(oPC, "PPM_HasNaturalWeapon", nHasNaturalWeapon);

    if(sMerge == "")
        sMerge = MERGE_A;
    SetLocalString(oPC, "PPM_Merge", sMerge);

    if(sWeapon != "")
        SetLocalString(oPC, "PPM_Weapon", sWeapon);

    if(sAllowedSpells != "")
        SetLocalString(oPC, "PPM_AllowedSpells", sAllowedSpells);


    SetLocalFloat(oPC, "PPM_Duration", fDuration);




    PPM_FinishStage(oPC);
}



void PPM_ClearParameters(object oPC)
{
    ClearRakshasaSpells(oPC);

    DeleteLocalInt(oPC, "PPM_App");
    DeleteLocalString(oPC, "PPM_Skin");

    DeleteLocalInt(oPC, "PPM_STR");             /*1 */
    DeleteLocalInt(oPC, "PPM_DEX");             /*2 */
    DeleteLocalInt(oPC, "PPM_Con");             /*3 */
    DeleteLocalInt(oPC, "PPM_Damage");          /*4 */
    DeleteLocalInt(oPC, "PPM_DamType");         /*4.1*/
    DeleteLocalInt(oPC, "PPM_AC");              /*5 */
    DeleteLocalInt(oPC, "PPM_Attack");          /*6 */
    DeleteLocalInt(oPC, "PPM_HP");              /*7 */
    DeleteLocalInt(oPC, "PPM_Fort");            /*8 */
    DeleteLocalInt(oPC, "PPM_Regen");           /*9 */
    DeleteLocalFloat(oPC, "PPM_RegInterval");   /*9.1 */
    DeleteLocalInt(oPC, "PPM_Hide");            /*10 */
    DeleteLocalInt(oPC, "PPM_MS");              /*11 */
    DeleteLocalInt(oPC, "PPM_Conc");            /*12 */
    DeleteLocalInt(oPC, "PPM_Reflex");          /*13 */
    DeleteLocalInt(oPC, "PPM_SpellImm1");       /*14 */
    DeleteLocalInt(oPC, "PPM_SpellImm2");       /*15 */
    DeleteLocalInt(oPC, "PPM_Save");            /*16 */
    DeleteLocalInt(oPC, "PPM_SpCr");            /*17 */
    DeleteLocalInt(oPC, "PPM_Spot");            /*18 */
    DeleteLocalInt(oPC, "PPM_Dis");             /*19 */
    DeleteLocalInt(oPC, "PPM_Lis");             /*20 */
    DeleteLocalInt(oPC, "PPM_OpL");             /*21 */
    DeleteLocalInt(oPC, "PPM_SetTr");           /*22 */
    DeleteLocalInt(oPC, "PPM_Tum");             /*23 */
    DeleteLocalInt(oPC, "PPM_ElemImmun");       /*24 */
    DeleteLocalInt(oPC, "PPM_ElemPerc");        /*24.1 */
    DeleteLocalInt(oPC, "PPM_ElemImmun2");      /*25 */
    DeleteLocalInt(oPC, "PPM_ElemPerc2");       /*25.1 */
    //DeleteLocalInt(oPC, "PPM_AOE");             /*26*/

    DeleteLocalInt(oPC, "PPM_HasNaturalWeapon");
    DeleteLocalString(oPC, "PPM_Merge");
    DeleteLocalString(oPC, "PPM_Weapon");


    DeleteLocalFloat(oPC, "PPM_Duration");
    DeleteLocalInt(oPC, "PPM_Stage");
    DeleteLocalInt(oPC, "PPM_StageFinished");
    DeleteLocalInt(oPC, "PPM_NEW_Count");
    DeleteLocalInt(oPC, "PPM_ERROR");

    DestroyObject(GetLocalObject(oPC, "PPM_Safe3"), 0.1);
}


/*
void CheckHaste(object oTarget)
{
    object oCaster;
    effect eCheck = GetFirstEffect(oTarget);
    while(GetIsEffectValid(eCheck))
    {
        if(GetEffectType(eCheck) == EFFECT_TYPE_HASTE)
        {
            RemoveEffect(oTarget, eCheck);
            oCaster = GetLocalObject(oTarget, "PPM_LastHasteCaster");
            if(GetIsObjectValid(oCaster))
            {
                SetLocalObject(oCaster, "PPM_HasteTarget", oTarget);
                SetLocalInt(oCaster, "PPM_HasteDuration", GetLocalInt(oTarget, "PPM_LastHasteDuration"));

                DeleteLocalObject(oTarget, "PPM_LastHasteCaster");
                DeleteLocalInt(oTarget, "PPM_LastHasteDuration");

                DelayCommand(1.0, ExecuteScript("sl_s_ppm_haste", oCaster));
            }
            else
                DelayCommand(1.0, ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectHaste(), oTarget, RoundsToSeconds(10)));
        }
        eCheck = GetNextEffect(oTarget);
    }
}
*/


void PPM_ApplyMiscEffects(object oPC, float fDuration)
{
    object oVirtCaster = GetObjectByTag("sl_cr_eff_ppm");
    effect eHP = ExtraordinaryEffect(EffectTemporaryHitpoints(GetLocalInt(oPC, "PPM_HP")));
    effect eLink;

    int nSTR = GetLocalInt(oPC, "PPM_STR");                     /*1 */          //DBM_Test("sl_s_ppm_inc","PPM_ApplyMiscEffects", "nSTR" + IToS(nSTR));
    int nDEX = GetLocalInt(oPC, "PPM_DEX");                     /*2 */          //DBM_Test("sl_s_ppm_inc","PPM_ApplyMiscEffects", "nDEX" + IToS(nDEX));
    int nCon = GetLocalInt(oPC, "PPM_Con");                     /*3 */          //DBM_Test("sl_s_ppm_inc","PPM_ApplyMiscEffects", "nCon" + IToS(nCon));
    int nDam = GetLocalInt(oPC, "PPM_Damage");                  /*4 */          //DBM_Test("sl_s_ppm_inc","PPM_ApplyMiscEffects", "nDamage" + IToS(nDam));
    int nDamType = GetLocalInt(oPC, "PPM_DamType");             /*4.1*/         //DBM_Test("sl_s_ppm_inc","PPM_ApplyMiscEffects", "nDamType" + IToS(nDamType));
    int nAC = GetLocalInt(oPC, "PPM_AC");                       /*5 */          //DBM_Test("sl_s_ppm_inc","PPM_ApplyMiscEffects", "nAC" + IToS(nAC));
    int nAttack = GetLocalInt(oPC, "PPM_Attack");               /*6 */          //DBM_Test("sl_s_ppm_inc","PPM_ApplyMiscEffects", "nAttack" + IToS(nAttack));
    int nHP = GetLocalInt(oPC, "PPM_HP");                       /*7 */          //DBM_Test("sl_s_ppm_inc","PPM_ApplyMiscEffects", "nHP" + IToS(nHP));
    int nFort = GetLocalInt(oPC, "PPM_Fort");                   /*8 */          //DBM_Test("sl_s_ppm_inc","PPM_ApplyMiscEffects", "nFort" + IToS(nFort));
    int nRegen = GetLocalInt(oPC, "PPM_Regen");                 /*9 */          //DBM_Test("sl_s_ppm_inc","PPM_ApplyMiscEffects", "nRegen" + IToS(nRegen));
    float fRegInterval = GetLocalFloat(oPC, "PPM_RegInterval"); /*9.1 */        //DBM_Test("sl_s_ppm_inc","PPM_ApplyMiscEffects", "fRegInterval" + FToS(fRegInterval));

    int nHide = GetLocalInt(oPC, "PPM_Hide");                   /*10 */         //DBM_Test("sl_s_ppm_inc","PPM_ApplyMiscEffects", "nHide" + IToS(nHide));
    int nMS = GetLocalInt(oPC, "PPM_MS");                       /*11 */         //DBM_Test("sl_s_ppm_inc","PPM_ApplyMiscEffects", "nMS" + IToS(nMS));
    int nConc = GetLocalInt(oPC, "PPM_Conc");                   /*12 */         //DBM_Test("sl_s_ppm_inc","PPM_ApplyMiscEffects", "nConc" + IToS(nConc));
    int nReflex = GetLocalInt(oPC, "PPM_Reflex");               /*13 */         //DBM_Test("sl_s_ppm_inc","PPM_ApplyMiscEffects", "nReflex" + IToS(nReflex));
    int nSpellImm1 = GetLocalInt(oPC, "PPM_SpellImm1");         /*14 */         //DBM_Test("sl_s_ppm_inc","PPM_ApplyMiscEffects", "nSpellImm1" + IToS(nSpellImm1));
    int nSpellImm2 = GetLocalInt(oPC, "PPM_SpellImm2");         /*15 */         //DBM_Test("sl_s_ppm_inc","PPM_ApplyMiscEffects", "nSpellImm2" + IToS(nSpellImm2));

    int nSave = GetLocalInt(oPC, "PPM_Save");                   /*16 */         //DBM_Test("sl_s_ppm_inc","PPM_ApplyMiscEffects", "nSave" + IToS(nSave));
    int nSpCr = GetLocalInt(oPC, "PPM_SpCr");                   /*17 */         //DBM_Test("sl_s_ppm_inc","PPM_ApplyMiscEffects", "nSpCr" + IToS(nSpCr));
    int nSpot = GetLocalInt(oPC, "PPM_Spot");                   /*18 */         //DBM_Test("sl_s_ppm_inc","PPM_ApplyMiscEffects", "nSpot" + IToS(nSpot));
    int nDis = GetLocalInt(oPC, "PPM_Dis");                     /*19 */         //DBM_Test("sl_s_ppm_inc","PPM_ApplyMiscEffects", "nDis" + IToS(nDis));
    int nLis = GetLocalInt(oPC, "PPM_Lis");                     /*20 */         //DBM_Test("sl_s_ppm_inc","PPM_ApplyMiscEffects", "nLis" + IToS(nLis));
    int nOpL = GetLocalInt(oPC, "PPM_OpL");                     /*21 */         //DBM_Test("sl_s_ppm_inc","PPM_ApplyMiscEffects", "nOpL" + IToS(nOpL));
    int nSetTr = GetLocalInt(oPC, "PPM_SetTr");                 /*22 */         //DBM_Test("sl_s_ppm_inc","PPM_ApplyMiscEffects", "nSetTr" + IToS(nSetTr));
    int nTum = GetLocalInt(oPC, "PPM_Tum");                     /*23 */         //DBM_Test("sl_s_ppm_inc","PPM_ApplyMiscEffects", "nTum" + IToS(nTum));

    int nElemImmun = GetLocalInt(oPC, "PPM_ElemImmun");         /*24 */         //DBM_Test("sl_s_ppm_inc","PPM_ApplyMiscEffects", "nElemImmun" + IToS(nElemImmun));
    int nElemPerc = GetLocalInt(oPC, "PPM_ElemPerc");           /*24.1 */       //DBM_Test("sl_s_ppm_inc","PPM_ApplyMiscEffects", "nElemPerc" + IToS(nElemPerc));
    int nElemImmun2 = GetLocalInt(oPC, "PPM_ElemImmun2");       /*25 */         //DBM_Test("sl_s_ppm_inc","PPM_ApplyMiscEffects", "nElemImmun2" + IToS(nElemImmun2));
    int nElemPerc2 = GetLocalInt(oPC, "PPM_ElemPerc2");         /*25.1 */       //DBM_Test("sl_s_ppm_inc","PPM_ApplyMiscEffects", "nElemPerc2" + IToS(nElemPerc2));
    //int nAOE = GetLocalInt(oPC, "PPM_AOE");                     /*26*/          //DBM_Test("sl_s_ppm_inc","PPM_ApplyMiscEffects", "nAOE" + IToS(nAOE));


    if(nSTR) eLink = EffectLinkEffects(eLink, EffectAbilityIncrease(ABILITY_STRENGTH, nSTR));               /*1*/
    if(nDEX) eLink = EffectLinkEffects(eLink, EffectAbilityIncrease(ABILITY_DEXTERITY, nDEX));              /*2*/
    if(nCon) eLink = EffectLinkEffects(eLink, EffectAbilityIncrease(ABILITY_CONSTITUTION, nCon));           /*3*/
    if(nDam) eLink = EffectLinkEffects(eLink, EffectDamageIncrease(nDam, nDamType));                        /*4*/
    if(nAC) eLink = EffectLinkEffects(eLink, EffectACIncrease(nAC));                                        /*5*/
    if(nAttack) eLink = EffectLinkEffects(eLink, EffectAttackIncrease(nAttack));                            /*6*/
    if(nFort) eLink = EffectLinkEffects(eLink, EffectSavingThrowIncrease(SAVING_THROW_FORT, nFort));        /*8*/
    if(nRegen) eLink = EffectLinkEffects(eLink, EffectRegenerate(nRegen, fRegInterval));                    /*9*/

    if(nHide) eLink = EffectLinkEffects(eLink, EffectSkillIncrease(SKILL_HIDE, nHide));                     /*10*/
    if(nMS) eLink = EffectLinkEffects(eLink, EffectSkillIncrease(SKILL_MOVE_SILENTLY, nMS));                /*11*/
    if(nConc) eLink = EffectLinkEffects(eLink, EffectConcealment(nConc));                                   /*12*/
    if(nReflex) eLink = EffectLinkEffects(eLink, EffectSavingThrowIncrease(SAVING_THROW_REFLEX, nReflex));  /*13*/

    if(nSpellImm1) eLink = EffectLinkEffects(eLink, EffectSpellImmunity(nSpellImm1));                       /*14*/
    if(nSpellImm2) eLink = EffectLinkEffects(eLink, EffectSpellImmunity(nSpellImm2));                       /*15*/

    if(nSave) eLink = EffectLinkEffects(eLink, EffectSavingThrowIncrease(SAVING_THROW_ALL, nSave));         /*16*/
    if(nSpCr) eLink = EffectLinkEffects(eLink, EffectSkillIncrease(SKILL_SPELLCRAFT, nSpCr));               /*17*/
    if(nSpot) eLink = EffectLinkEffects(eLink, EffectSkillIncrease(SKILL_SPOT, nSpot));                     /*18*/
    if(nDis) eLink = EffectLinkEffects(eLink, EffectSkillIncrease(SKILL_DISCIPLINE, nDis));                 /*19*/
    if(nLis) eLink = EffectLinkEffects(eLink, EffectSkillIncrease(SKILL_LISTEN, nLis));                     /*20*/
    if(nOpL) eLink = EffectLinkEffects(eLink, EffectSkillIncrease(SKILL_OPEN_LOCK, nOpL));                  /*21*/
    if(nSetTr) eLink = EffectLinkEffects(eLink, EffectSkillIncrease(SKILL_SET_TRAP, nSetTr));               /*22*/
    if(nTum) eLink = EffectLinkEffects(eLink, EffectSkillIncrease(SKILL_TUMBLE, nTum));                     /*23*/
    if(nElemImmun) eLink = EffectLinkEffects(eLink, EffectDamageImmunityIncrease(nElemImmun, nElemPerc));   /*24*/
    if(nElemImmun2) eLink = EffectLinkEffects(eLink, EffectDamageImmunityIncrease(nElemImmun2, nElemPerc2));/*25*/
    /*
    if(nAOE)                                                                                               // 26
    {
        effect eAura = EffectAreaOfEffect(AOE_MOB_DRAGON_FEAR, "ppm_dragaura_ent", "", "ppm_dragaura_ext");
        eAura = ExtraordinaryEffect(eAura);
        AssignCommand(oVirtCaster, ApplyEffectToObject(DURATION_TYPE_PERMANENT, eAura, oPC));
    }*/

    eLink = ExtraordinaryEffect(eLink);
    AssignCommand(oVirtCaster, ApplyEffectToObject(DURATION_TYPE_TEMPORARY, eLink, oPC, fDuration));

    /* Do not need any more
    int nMonkLvl = GetLevelByClass(CLASS_TYPE_MONK, oPC);
    if(nMonkLvl)
    {
        CheckHaste(oPC);
        effect eSpeed = ExtraordinaryEffect(EffectMovementSpeedIncrease(3*nMonkLvl));
        AssignCommand(oVirtCaster, ApplyEffectToObject(DURATION_TYPE_PERMANENT, eSpeed, oPC));
    }*/

    if(nHP && !GetLocalInt(oPC, "PPM_DamagedHP"))
    {
        effect eHP = ExtraordinaryEffect(EffectTemporaryHitpoints(nHP));                                    /*7*/
        AssignCommand(oVirtCaster, ApplyEffectToObject(DURATION_TYPE_TEMPORARY, eHP, oPC, fDuration));
    }
}


void PPM_RemoveSkinProps(object oSkin, object oPC)
{
    int nIPShouldBeRemoved;
    object oToken = GetLocalObject(oPC, TOKEN_TAG);
    int nType, nSubType, nCost, nDestroy;

    itemproperty ip = GetFirstItemProperty(oSkin);
    while(GetIsItemPropertyValid(ip) && !nDestroy)
    {
        nType = GetItemPropertyType(ip);                                        //DBM_Test("sl_s_ppm_inc","PPM_RemoveSkinProps", "nType" + IToS(nType));
        nSubType = GetItemPropertySubType(ip);                                  //DBM_Test("sl_s_ppm_inc","PPM_RemoveSkinProps", "nSubType" + IToS(nSubType));
        nIPShouldBeRemoved = TRUE;

        if((nType == ITEM_PROPERTY_IMMUNITY_DAMAGE_TYPE) && (nSubType>4)) //Bug: this ip could not be deleted//Zoran
            nDestroy = TRUE;

        else if(nType == 12)
        {
            if((nSubType>=169) && (nSubType<=178)) //Feats Player_Tool01 - 10
                nIPShouldBeRemoved = FALSE;
        }
        else if(nType == 82)//ITEM_PROPERTY_ONHITCASTSPELL
        {
            if(nSubType==125) //IP_CONST_ONHIT_CASTSPELL_ONHIT_UNIQUEPOWER
                nIPShouldBeRemoved = FALSE;
        }


        if(nIPShouldBeRemoved)
            DelayCommand(0.1, RemoveItemProperty(oSkin, ip));

        ip = GetNextItemProperty(oSkin);
    }

    if(nDestroy)
    {
        DeleteLocalInt(oSkin, "PPM_Item");
        DestroyObject(oSkin, 0.1);
    }

    DelayCommand(1.1, SetLocalInt(oToken, "nPPM_RemoveForm_PassedStage", 1));
    DelayCommand(1.2, ExecuteScript("sl_s_ppm_remove", oPC));
}




void PPM_RemoveForm_NEW(object oPC)
{                                                                               //DBM_Test("sl_s_ppm_inc","PPM_RemoveForm_NEW", "START with oPC" + OToS(oPC));
    /*
    if (GetArea(oPC) == OBJECT_INVALID)
    {                                                                           //DBM_Test("sl_s_ppm_inc","PPM_RemoveForm", "Area is OBJECT_INVALID. oPC is nowhere");
        DelayCommand(3.0, ExecuteScript("sl_s_ppm_remove", oPC));
        return;
    }
    */


    if(GetLocalInt(oPC, "PPM_Stage"))//oPC is currently morphing //bZ 14.03.2015
    {
        DelayCommand(7.0, ExecuteScript("sl_s_ppm_remove", oPC));
        return;
    }

    object oToken = GetLocalObject(oPC, TOKEN_TAG);
    if (GetLocalInt(oToken, "isPolymorphed"))
    {
        //ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectCutsceneParalyze(), oPC, 2.5);
        int nPassedStage = GetLocalInt(oToken, "nPPM_RemoveForm_PassedStage");  //DBM_Test("sl_s_ppm_inc","PPM_RemoveForm_NEW", "nPassedStage" + IToS(nPassedStage));
        if (!nPassedStage)
        {
            SetLocalInt(oPC, "NoHomeDupeCheck", 1);
            SetCutsceneMode(oPC, TRUE);
            DeleteLocalInt(oPC, "RemorphAlreadyStarted");//for tool10

            // bZ 25.04.2018
            int nDamagedHP = GetMaxHitPoints(oPC) - GetCurrentHitPoints(oPC);
            if(nDamagedHP>0)
            {
                SetLocalInt(oPC, "PPM_DamagedHP", nDamagedHP);
                ApplyEffectToObject(DURATION_TYPE_INSTANT, EffectHeal(nDamagedHP), oPC);
            }

            AssignCommand(oPC, ClearAllActions(TRUE));
            ApplyEffectToObject(DURATION_TYPE_INSTANT, EffectVisualEffect(VFX_IMP_POLYMORPH), oPC);
            //ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectVisualEffect(VFX_DUR_CUTSCENE_INVISIBILITY), oPC, 5.0);
            object oPC_Skin = GetItemInSlot(INVENTORY_SLOT_CARMOUR,oPC);        //DBM_Test("sl_s_ppm_inc","PPM_RemoveForm_NEW", "oPC_Skin" + OToS(oPC_Skin));

            PPM_RemoveSkinProps(oPC_Skin, oPC);
            //DeleteLocalInt(oPC_Skin, "PPM_Item");
            //DestroyObject(oPC_Skin);
            //DelayCommand(0.1, SetLocalInt(oToken, "nPPM_RemoveForm_PassedStage", 1));
            //DelayCommand(0.2, ExecuteScript("sl_s_ppm_remove", oPC));

            DeleteLocalString(oPC, "PPM_AllowedSpells");
            return;
        }




        else if (nPassedStage == 1)
        {
            //DelayCommand(0.6, PPM_ChangeAppearanceTo(-1, oPC));// Change app to original
            ExecuteScript("sl_s_ppm_appback", oPC);
            return;
        }

        else if (nPassedStage == 2)
        {
            //PPM_RemoveFormEffects(oPC);//Removes effects that were applied on oPC, not on his skin. Such effects as: Temp HP, STR bonus, DEX bonus, etc.
            //AssignCommand(oPC, ClearAllActions(TRUE));
            ExecuteScript("sl_s_ppm_clreffe", oPC);
            return;
        }

        else if (nPassedStage == 3)
        {
            //PPM_DestroyEquipedPPMItems(oPC);//destroy any shifter's weapon
            //AssignCommand(oPC, ClearAllActions(TRUE));
            ExecuteScript("sl_s_ppm_desitem", oPC);
            return;
        }

        else if (nPassedStage == 4)
        {
            //PPM_UnlockAllSlots(oPC);//allow to equip/unequip items
            //AssignCommand(oPC, ClearAllActions(TRUE));
            ExecuteScript("sl_s_ppm_unlock", oPC);
            return;
        }

        else if ((nPassedStage == 5) || (nPassedStage == 6))
        {
            //PPM_EquipItemsBackAddDestroySaves(oPC);//equip items that were on oPC before polymorph
            ExecuteScript("sl_s_ppm_equback", oPC);
            return;
        }

        else if (nPassedStage == 7)
        {
            //PPM_EquipItemsBackAddDestroySaves(oPC);//equip items that were on oPC before polymorph
            ExecuteScript("sl_s_ppm_clrinv", oPC);
            return;
        }

        else if (nPassedStage == 8)
        {
            int nStage = GetLocalInt(oToken, "nPPM_RemoveForm_PassedStage")+1;          //DBM_Test("sl_s_ppm_inc","PPM_CheckItemsEquiped", "Set stage to" + IToS(nStage));
            DelayCommand(0.1, SetLocalInt(oToken, "nPPM_RemoveForm_PassedStage", nStage));
            DelayCommand(0.2, ExecuteScript("sl_s_ppm_remove", oPC));

            //DelayCommand(1.0, PPM_CheckItemsEquiped(oPC));
            return;
        }

        else if (nPassedStage == 9)
        {
            DelayCommand(0.2, DeleteLocalInt(oToken,"nPPM_RemoveForm_PassedStage"));
            DelayCommand(0.2, DeleteLocalInt(oToken,"isPolymorphed"));
            //PPM_RemoveFormEffects(oPC);
            DelayCommand(0.2, DeleteLocalInt(oPC, "nPassedStageDebugVar"));
            //DestroyObject(GetLocalObject(oPC, "PPM_Safe3"), 0.3);
            //DelayCommand(0.3, PPM_ClearTempContainer(oPC));//bZ 29.07.12

            int nNextForm = GetLocalInt(oPC, "PPM_NextForm");
            if(!nNextForm)
            {
                int nDamagedHP = GetLocalInt(oPC, "PPM_DamagedHP");
                if(nDamagedHP)
                {
                    DeleteLocalInt(oPC, "PPM_DamagedHP");
                    DelayCommand(1.0, ApplyEffectToObject(DURATION_TYPE_INSTANT, EffectDamage(nDamagedHP), oPC));
                }

                DelayCommand(0.4, SetCutsceneMode(oPC, FALSE));
                DelayCommand(1.0, DeleteLocalInt(oPC, "NoHomeDupeCheck"));
            }
            else
            {
                DeleteLocalInt(oPC, "PPM_NextForm");
                DelayCommand(0.3, PPM(oPC, nNextForm, 99999.0));
            }
        }
        else if(nPassedStage>9)//antibug bZ 09.01.2015
        {
            DeleteLocalInt(oToken,"nPPM_RemoveForm_PassedStage");
            DelayCommand(0.1, ExecuteScript("sl_s_ppm_remove", oPC));
            return;
        }
    }

    else
        DelayCommand(0.1, DeleteLocalInt(oToken,"nPPM_RemoveForm_PassedStage"));

}
//------------------------------------------------------------------------------







// Shifter Attack
//------------------------------------------------------------------------------
void DoShifterAttack(object oPC, object oTarget, int bFirstActivation = FALSE, int bNeedBeginAttackMess = TRUE);
//------------------------------------------------------------------------------
object PPM_GetTarget(object oPC)
{
    return GetLocalObject(oPC, "PPM_ShifterAttackTarget");
}
//------------------------------------------------------------------------------
void PPM_SetTarget(object oPC, object oTarget)
{
    SetLocalObject(oPC, "PPM_ShifterAttackTarget", oTarget);
}
//------------------------------------------------------------------------------
string ShifterAttackLogString(object oPC, object oTarget, int nRoll, int nAB, int nMiss, int nCritRoll = 0)
{
    string sLog = PPM_CCYAN + GetName(oPC) + PPM_CORANGE + " атакует " + GetName(oTarget) + PPM_CORANGE +" : ";
    string sHit = nMiss ? "*промах*" : "*попадание*";
    sLog += sHit + " : (" + IntToString(nRoll) + " + " + IntToString(nAB) + " = " + IntToString(nRoll + nAB);
    if(nCritRoll)
        sLog += " : Бросок критической угрозы: " + IntToString(nCritRoll) + " + " + IntToString(nAB) + " = " + IntToString(nCritRoll + nAB);
    sLog += ")";
return sLog;
}
//------------------------------------------------------------------------------
int PPM_GetHasEffect(int nEffectType, object oTarget = OBJECT_SELF)
{
    effect eInvalid;
    effect eEffect = GetFirstEffect(oTarget);
    while(GetIsEffectValid(eEffect))
    {
        if(GetEffectType(eEffect) == nEffectType)
            return TRUE;
        eEffect = GetNextEffect(oTarget);
    }
return FALSE;
}
//------------------------------------------------------------------------------
void PPM_RemoveInvis(object oPC)
{
    effect eEffect = GetFirstEffect(oPC);
    while(GetIsEffectValid(eEffect))
    {
        if(GetEffectType(eEffect) == EFFECT_TYPE_INVISIBILITY)
            RemoveEffect(oPC, eEffect);
        eEffect = GetNextEffect(oPC);
    }
}
//------------------------------------------------------------------------------
void PPM_ManageOnHitProps(object oPC)
{
    object oTarget = PPM_GetTarget(oPC);
    if(GetIsObjectValid(oTarget))
    {
        int nPoly = GetLocalInt(GetLocalObject(oPC, TOKEN_TAG), "isPolymorphed");
        if(nPoly == POLYMORPH_TYPE_VAMPIRE_MALE || nPoly == POLYMORPH_TYPE_VAMPIRE_FEMALE) // Level Drain, DC = 30
        {
            if(!FortitudeSave(oTarget, 30, SAVING_THROW_TYPE_NEGATIVE, oPC))
            {
                ApplyEffectToObject(DURATION_TYPE_INSTANT, EffectVisualEffect(VFX_IMP_REDUCE_ABILITY_SCORE), oTarget);
                ApplyEffectToObject(DURATION_TYPE_PERMANENT, EffectNegativeLevel(d2()), oTarget);
            }
        }
    }
}
//------------------------------------------------------------------------------
int GetHighestDamage(int nDam1, int nDam2)
{
/*  Порядок такой:
int    DAMAGE_BONUS_1           = 1;
int    DAMAGE_BONUS_2           = 2;
int    DAMAGE_BONUS_1d4         = 6;
int    DAMAGE_BONUS_3           = 3;
int    DAMAGE_BONUS_1d6         = 7;
int    DAMAGE_BONUS_4           = 4;
int    DAMAGE_BONUS_1d8         = 8;
int    DAMAGE_BONUS_2d4         = 12;
int    DAMAGE_BONUS_5           = 5;
int    DAMAGE_BONUS_1d10        = 9;
int    DAMAGE_BONUS_6           = 16;
int    DAMAGE_BONUS_1d12        = 14;
int    DAMAGE_BONUS_7           = 17;
int    DAMAGE_BONUS_2d6         = 10;
int    DAMAGE_BONUS_8           = 18;
int    DAMAGE_BONUS_2d8         = 11;
int    DAMAGE_BONUS_9           = 19;
int    DAMAGE_BONUS_10          = 20;
int    DAMAGE_BONUS_2d10        = 13;
int    DAMAGE_BONUS_11          = 21;
int    DAMAGE_BONUS_12          = 22;
int    DAMAGE_BONUS_13          = 23;
int    DAMAGE_BONUS_2d12        = 15;
int    DAMAGE_BONUS_14          = 24;
int    DAMAGE_BONUS_15          = 25;
int    DAMAGE_BONUS_16          = 26;
int    DAMAGE_BONUS_17          = 27;
int    DAMAGE_BONUS_18          = 28;
int    DAMAGE_BONUS_19          = 29;
int    DAMAGE_BONUS_20          = 30;
*/
    string sLine = " 1 2 6 3 7 4 8 12 5 9 16 14 17 10 18 11 19 20 13 21 22 23 15 24 25 26 27 28 29 30 ";
    int nPos1 = FindSubString(sLine, " " + IntToString(nDam1) + " ");
    int nPos2 = FindSubString(sLine, " " + IntToString(nDam2) + " ");
return (nPos1>nPos2) ? nDam1 : nDam2;
}
//------------------------------------------------------------------------------
int GetDamageFromNaturalWeapon(object oPC)
{
    int nDamage, nTemp;
    itemproperty ip;
    object oItem;
    int i;
    for(i=14; i<=16; i++)
    {
        oItem = GetItemInSlot(i, oPC);
        if(GetIsObjectValid(oItem))
        {
            ip = GetFirstItemProperty(oItem);
            while(GetIsItemPropertyValid(ip))
            {
                if(GetItemPropertyType(ip) == ITEM_PROPERTY_DAMAGE_BONUS)
                {
                    nTemp = GetItemPropertyCostTableValue(ip);
                    nDamage = GetHighestDamage(nTemp, nDamage);
                }
                ip = GetNextItemProperty(oItem);
            }
        }
    }
return nDamage;
}
//------------------------------------------------------------------------------
effect EffectShifterDamage(object oPC, int nMult = 1, int bLog = FALSE)
{
    int nDamagePower, nMagicMin, nMagicMax, nPhysMax, nPhysType;
    int nPhysMin = GetLocalInt(oPC, "PPM_ShifterPhysMin");

    if(!nPhysMin) // Should we recalculate or take from cash?
    {
        PPM_ManageOnHitProps(oPC);

        int nTemp;
        int nPoly = GetLocalInt(GetLocalObject(oPC, TOKEN_TAG), "isPolymorphed");
        string sPhysLog = "Подробнее(физ.):" + PPM_CORANGE;
        string sMagLog = "Подробнее(маг.):" + PPM_CVIOLET;
        // Strength
        nPhysMin = (GetAbilityScore(oPC, ABILITY_STRENGTH) - GetAbilityScore(oPC, ABILITY_STRENGTH, TRUE))/2;
        nPhysMax = nPhysMin;
        if(bLog && (nPhysMin>0))
            sPhysLog += " +" + IntToString(nPhysMin)+"(мод силы)";


        // RACE // Берем через APP чтобы работало в форме
        if(GetLocalInt(GetLocalObject(oPC, TOKEN_TAG), "OriginalAppType") == APPEARANCE_TYPE_HALF_ORC) // 5 = RACIAL_TYPE_HALFORC
        {
            nPhysMin += 6;
            nPhysMax += 6;
            if(bLog)
                sPhysLog += " +6(раса Могучий Человек)";
        }


        // CLASSES
        // Shifter +1d10 lvl/10
        nTemp = GetLevelByClass(CLASS_TYPE_SHIFTER, oPC)/10;
        nPhysMin += nTemp;
        nPhysMax += nTemp * 10;
        if(bLog && nTemp)
            sPhysLog += " +" + IntToString(nTemp)+"d10(уровни Оборотня)";

        // DD +1d4 lvl/10
        nTemp = GetLevelByClass(CLASS_TYPE_DWARVEN_DEFENDER, oPC)/10;
        nMagicMin = nTemp;
        nMagicMax = nTemp *4;
        if(bLog && nTemp)
            sMagLog += " +" + IntToString(nTemp)+"d4(уровни Защитника Дварфов)";

        // BG +1д8 лвл/10(маг.)
        nTemp = GetLevelByClass(CLASS_TYPE_BLACKGUARD, oPC)/10;
        nMagicMin += nTemp;
        nMagicMax += nTemp *8;
        if(bLog && nTemp)
            sMagLog += " +" + IntToString(nTemp)+"d8(уровни Черного Стража)";

        // ChoT  +1д6 лвл/5(маг.) // Для драконов +1д6 лвл/10
        nTemp = GetLevelByClass(CLASS_TYPE_DIVINE_CHAMPION, oPC)/ (5 * (1+(nPoly == POLYMORPH_TYPE_ANCIENT_RED_DRAGON || nPoly == POLYMORPH_TYPE_ANCIENT_BLUE_DRAGON || nPoly == POLYMORPH_TYPE_ANCIENT_GREEN_DRAGON)));
        nMagicMin += nTemp;
        nMagicMax += nTemp *6;
        if(bLog && nTemp)
            sMagLog += " +" + IntToString(nTemp)+"d6(уровни Воина Богов)";


        // Чтоб 2 раза не вставать
        // SPELLS and FEATS
        if(GetHasFeatEffect(FEAT_DIVINE_WRATH, oPC))
        {
            nTemp-=1; // Это lvl чота для формул

            // LVL: 1 - 2 - 3 - 4...
            // DAM: 5 - 7 - 9 - 11...
            nTemp = nTemp*2;
            if(nTemp>0)
            {
                nTemp+=3;
                nMagicMin += nTemp;
                nMagicMax += nTemp;
                if(bLog && nTemp)
                    sMagLog += " +" + IntToString(nTemp)+"(Divine Wrath)";
            }
        }
        if(GetHasSpellEffect(SPELL_DIVINE_FAVOR, oPC))
        {
            nMagicMin += 5;
            nMagicMax += 5;
            if(bLog)
                sMagLog += " +5(Divine Favor)";
        }
        if(GetHasSpellEffect(SPELL_DIVINE_MIGHT, oPC))
        {
            nTemp = GetAbilityModifier(ABILITY_CHARISMA, oPC);
            nMagicMin += nTemp;
            nMagicMax += nTemp;
            if(bLog && nTemp)
                sMagLog += " +" + IntToString(nTemp)+"(Divine Might)";
        }
        if(GetActionMode(oPC, ACTION_MODE_POWER_ATTACK))
        {
            nPhysMin += 5;
            nPhysMax += 5;
            if(bLog)
                sPhysLog += " +5(Power Attack)";
        }
        if(GetActionMode(oPC, ACTION_MODE_IMPROVED_POWER_ATTACK))
        {
            nPhysMin += 10;
            nPhysMax += 10;
            if(bLog)
                sPhysLog += " +10(Improved Power Attack)";
        }


        int nBonusPower;

        if(nPoly == POLYMORPH_TYPE_ANCIENT_RED_DRAGON || nPoly == POLYMORPH_TYPE_ANCIENT_BLUE_DRAGON || nPoly == POLYMORPH_TYPE_ANCIENT_GREEN_DRAGON)
        {
            nDamagePower = DAMAGE_POWER_PLUS_SIX;
            nPhysType = DAMAGE_TYPE_SLASHING;
            // 3d8 + 10
            nPhysMin += 13; // 3+10;
            nPhysMax += 34; // 24+10;
            if(bLog)
                sPhysLog += " +3d8+10(форма Дракона)";
        }
        else if(nPoly == 90) // Iron golem
        {
            nDamagePower = DAMAGE_POWER_PLUS_FIVE;
            nPhysType = DAMAGE_TYPE_BLUDGEONING;
            // 2d10 + 11
            nPhysMin += 13; // 2+11;
            nPhysMax += 31; // 20+11;
            if(bLog)
                sPhysLog += " +2d10+11(форма Железного Голема)";
        }
        else if(nPoly == 91) // Stone golem
        {
            nDamagePower = DAMAGE_POWER_PLUS_FOUR;
            nBonusPower = GetLevelByClass(CLASS_TYPE_MONK, oPC)/5;
            if(nBonusPower > nDamagePower)
                nDamagePower = nBonusPower;

            nPhysType = DAMAGE_TYPE_BLUDGEONING;
            // 2d10 + 10
            nPhysMin += 12; // 2+10;
            nPhysMax += 30; // 20+10;
            if(bLog)
                sPhysLog += " +2d10+10(форма Каменного Голема)";
        }
        else if(nPoly == 92) // Flesh
        {
            nDamagePower = DAMAGE_POWER_PLUS_SIX;
            nPhysType = DAMAGE_TYPE_BLUDGEONING;
            // 6d6 + 9
            nPhysMin += 15; // 6+9;
            nPhysMax += 45; // 36+9;
            if(bLog)
                sPhysLog += " +6d6+9(форма Голема Плоти)";
        }
        else if(nPoly == POLYMORPH_TYPE_VAMPIRE_MALE || nPoly == POLYMORPH_TYPE_VAMPIRE_FEMALE)
        {
            nDamagePower = DAMAGE_POWER_PLUS_FOUR;
            nBonusPower = GetLevelByClass(CLASS_TYPE_MONK, oPC)/4;
            if(nBonusPower > nDamagePower)
                nDamagePower = nBonusPower;

            nBonusPower = GetLevelByClass(CLASS_TYPE_SHADOWDANCER, oPC)/5;
            if(nBonusPower > nDamagePower)
                nDamagePower = nBonusPower;

            nPhysType = DAMAGE_TYPE_SLASHING;
            // 3d8 + 5
            nPhysMin += 8; // 3+5;
            nPhysMax += 29; // 24+5;
            if(bLog)
                sPhysLog += " +3d8+5(форма Вампира)";
        }
        else if(nPoly == POLYMORPH_TYPE_SPECTRE)
        {
            nDamagePower = DAMAGE_POWER_PLUS_FOUR;
            nBonusPower = GetLevelByClass(CLASS_TYPE_MONK, oPC)/5;
            if(nBonusPower > nDamagePower)
                nDamagePower = nBonusPower;

            nBonusPower = GetLevelByClass(CLASS_TYPE_SHADOWDANCER, oPC)/4;
            if(nBonusPower > nDamagePower)
                nDamagePower = nBonusPower;

            nPhysType = DAMAGE_TYPE_SLASHING;
            // 3d6 + 6
            nPhysMin += 9; // 3+6;
            nPhysMax += 30; // 24+6;
            if(bLog)
                sPhysLog += " +3d6+6(форма Призрака)";
        }

        // В ряд констант пауэра затесалась одна левая константа, из-за которой дальше идет смещений на +1
        if(nDamagePower>5)
            nDamagePower+=1;


        // Урон с клыков кулаков и т.п. // Берется только 1, самый большой
        nTemp = GetDamageFromNaturalWeapon(oPC);
        if(nTemp)
        {
            if(nTemp<6 || nTemp>15)
            {
                if(nTemp>15)
                    nTemp-= 10;

                nPhysMin += nTemp;
                nPhysMax += nTemp;
                if(bLog)
                    sPhysLog += " +" + IntToString(nTemp);

            }
            else if(nTemp>=6 && nTemp<=9)
            {
                nTemp = (nTemp - 4)*2;
                nPhysMin += 1;
                nPhysMax += nTemp;
                if(bLog)
                    sPhysLog += " +1d" + IntToString(nTemp);
            }
            else if(nTemp == DAMAGE_BONUS_2d6)
            {
                nPhysMin += 2;
                nPhysMax += 12;
                if(bLog)
                    sPhysLog += " +2d6";
            }
            else if(nTemp == DAMAGE_BONUS_2d8)
            {
                nPhysMin += 2;
                nPhysMax += 16;
                if(bLog)
                    sPhysLog += " +2d8";
            }
            else if(nTemp == DAMAGE_BONUS_2d4)
            {
                nPhysMin += 2;
                nPhysMax += 8;
                if(bLog)
                    sPhysLog += " +2d4";
            }
            else if(nTemp == DAMAGE_BONUS_2d10)
            {
                nPhysMin += 2;
                nPhysMax += 20;
                if(bLog)
                    sPhysLog += " +2d10";
            }
            else if(nTemp == DAMAGE_BONUS_1d12)
            {
                nPhysMin += 1;
                nPhysMax += 12;
                if(bLog)
                    sPhysLog += " +1d12";
            }
            else if(nTemp == DAMAGE_BONUS_2d12)
            {
                nPhysMin += 2;
                nPhysMax += 24;
                if(bLog)
                    sPhysLog += " +2d12";
            }
            if(bLog)
                sPhysLog += "(оружие существа)";
        }


        if(bLog)
        {
            if(GetStringLength(sMagLog)>23)
                SetLocalString(oPC, "PPM_ShifterMagDamLog", sMagLog);
            if(GetStringLength(sPhysLog)>23)
                SetLocalString(oPC, "PPM_ShifterPhysDamLog", sPhysLog);
        }




        // Cashing
        SetLocalInt(oPC, "PPM_ShifterDamPow", nDamagePower);
        // Magic Damage
        SetLocalInt(oPC, "PPM_ShifterMagicMin", nMagicMin);
        SetLocalInt(oPC, "PPM_ShifterMagicMax", nMagicMax);

        // Phys Damage
        SetLocalInt(oPC, "PPM_ShifterPhysMin", nPhysMin);
        SetLocalInt(oPC, "PPM_ShifterPhysMax", nPhysMax);
        SetLocalInt(oPC, "PPM_ShifterPhysType", nPhysType);


        // Delete only 1 var to recalculate
        DelayCommand(5.8, DeleteLocalInt(oPC, "PPM_ShifterPhysMin"));
    }
    else  // Get Info from Cash
    {
        nDamagePower = GetLocalInt(oPC, "PPM_ShifterDamPow");
        // Magic Damage
        nMagicMin = GetLocalInt(oPC, "PPM_ShifterMagicMin");
        nMagicMax = GetLocalInt(oPC, "PPM_ShifterMagicMax");

        // Phys Damage
        nPhysMax = GetLocalInt(oPC, "PPM_ShifterPhysMax");
        nPhysType = GetLocalInt(oPC, "PPM_ShifterPhysType");
    }

    effect ePhysDam = EffectDamage((1+Random(nPhysMax-nPhysMin) + nPhysMin) * nMult, nPhysType, nDamagePower);
    effect eMagicDam = EffectDamage((1+Random(nMagicMax-nMagicMin) + nMagicMin) * nMult, DAMAGE_TYPE_MAGICAL, nDamagePower);

    return EffectLinkEffects(ePhysDam, eMagicDam);
}
//------------------------------------------------------------------------------
void DoShifterSingleHit(object oPC, object oTarget, int nMult = 1)
{
    SetActionMode(oPC, ACTION_MODE_STEALTH, FALSE);
    PPM_RemoveInvis(oPC);

    ApplyEffectToObject(DURATION_TYPE_INSTANT, EffectVisualEffect(VFX_COM_HIT_SONIC), oTarget);
    AssignCommand(oPC, ApplyEffectToObject(DURATION_TYPE_INSTANT, EffectShifterDamage(oPC, nMult), oTarget));
}
//------------------------------------------------------------------------------
int GetAbilityBonusScore(int nAbility, object oPC)
{
    return GetAbilityScore(oPC, nAbility) - GetAbilityScore(oPC, nAbility, TRUE);
}
//------------------------------------------------------------------------------
int PPM_GetABFromStats(object oPC)
{
    if(!GetIsObjectValid(GetItemInSlot(INVENTORY_SLOT_RIGHTHAND, oPC)) && GetHasFeat(FEAT_WEAPON_FINESSE, oPC))
        return GetAbilityBonusScore(ABILITY_DEXTERITY, oPC)/2;
    else
        return GetAbilityBonusScore(ABILITY_STRENGTH, oPC)/2;
}
//------------------------------------------------------------------------------
string PPM_ManageAttackLog(object oPC, string sLog, int nNewValue, string sMessage, string sBonus = "")
{
    if(sBonus != "")
        sLog += " +" + sBonus + sMessage;
    else
    {
        int nOldValue = GetLocalInt(oPC, "PPM_ShifterAttackLogTempValue");
        int nBonus = nNewValue-nOldValue;
        if(nBonus>0)
            sLog += " +" + IntToString(nBonus) + sMessage;
    }
    SetLocalInt(oPC, "PPM_ShifterAttackLogTempValue", nNewValue);
return sLog;
}
//------------------------------------------------------------------------------
int GetABFromCreatureItems(object oPC)
{
    int nAB, nTemp;
    itemproperty ip;
    object oItem;
    int i;
    for(i=14; i<=16; i++)
    {
        oItem = GetItemInSlot(i, oPC);
        if(GetIsObjectValid(oItem))
        {
            ip = GetFirstItemProperty(oItem);
            while(GetIsItemPropertyValid(ip))
            {
                if(GetItemPropertyType(ip) == ITEM_PROPERTY_ATTACK_BONUS || GetItemPropertyType(ip) == ITEM_PROPERTY_ENHANCEMENT_BONUS)
                {
                    nTemp = GetItemPropertyCostTableValue(ip);
                    if(nTemp>nAB)
                        nAB = nTemp;
                }
                ip = GetNextItemProperty(oItem);
            }
        }
    }
return nAB;
}
//------------------------------------------------------------------------------
int GetShifterAttackBonus(object oPC, int bLog = FALSE)
{
    int nAB = GetLocalInt(oPC, "PPM_ShifterAB"); // Get from cash
    if(!nAB)
    {
        string sLog;
        int nTemp, nBonus;
        nAB = GetBaseAttackBonus(oPC);
        if(bLog)
        {
            sLog = "Подробнее: " + PPM_CGREEN + IntToString(nAB)+"(база)";
            SetLocalInt(oPC, "PPM_ShifterAttackLogTempValue", nAB);
        }
        // Get AB from spells / spell-feats
        if(GetHasSpellEffect(SPELL_DIVINE_POWER))
        {
            nAB = 20;
            int nHD = GetHitDice(oPC);
            if(nHD > 20)
                nAB+= (nHD-20)/2;

            if(bLog)
                sLog = PPM_ManageAttackLog(oPC, sLog, nAB, "(Divine Power)");
        }
        if(GetHasSpellEffect(SPELL_BLESS))
        {
            nAB+= 1;
            if(bLog)
                sLog = PPM_ManageAttackLog(oPC, sLog, nAB, "(Bless)", "1");
        }
        if(GetHasSpellEffect(SPELL_AID))
        {
            nAB+= 2;
            if(bLog)
                sLog = PPM_ManageAttackLog(oPC, sLog, nAB, "(Aid)", "2");
        }
        if(GetHasSpellEffect(SPELL_PRAYER))
        {
            nAB+= 3;
            if(bLog)
                sLog = PPM_ManageAttackLog(oPC, sLog, nAB, "(Prayer)", "3");
        }
        if(GetHasSpellEffect(SPELL_DIVINE_FAVOR))
        {
            nAB+= 5;
            if(bLog)
                sLog = PPM_ManageAttackLog(oPC, sLog, nAB, "(Divine Favor)", "5");
        }
        if(GetHasFeatEffect(FEAT_DIVINE_WRATH))
        {
            nAB += GetLevelByClass(CLASS_TYPE_DIVINE_CHAMPION, oPC)/5*2 + 1;
            if(bLog)
                sLog = PPM_ManageAttackLog(oPC, sLog, nAB, "(Divine Wrath)");
        }


        // Get AB from Classes
        // Shifter
        nAB += GetLevelByClass(CLASS_TYPE_SHIFTER, oPC)/5;
        if(bLog)
            sLog = PPM_ManageAttackLog(oPC, sLog, nAB, "(уровни Оборотня)");
        // DD
        nAB += GetLevelByClass(CLASS_TYPE_DWARVEN_DEFENDER, oPC)/5;
        if(bLog)
            sLog = PPM_ManageAttackLog(oPC, sLog, nAB, "(уровни Защитника Дварфов)");
        // ShD
        nAB += GetLevelByClass(CLASS_TYPE_SHADOWDANCER, oPC)/5;
        if(bLog)
            sLog = PPM_ManageAttackLog(oPC, sLog, nAB, "(уровни ШД)");
        // BG
        nAB += GetLevelByClass(CLASS_TYPE_BLACKGUARD, oPC)/5;
        if(bLog)
            sLog = PPM_ManageAttackLog(oPC, sLog, nAB, "(уровни Черного Стража)");


        // Get AB from Forms and from Classes
        int nPoly = GetLocalInt(GetLocalObject(oPC, TOKEN_TAG), "isPolymorphed");
        if(nPoly == POLYMORPH_TYPE_ANCIENT_RED_DRAGON || nPoly == POLYMORPH_TYPE_ANCIENT_BLUE_DRAGON || nPoly == POLYMORPH_TYPE_ANCIENT_GREEN_DRAGON)
        {
            // Form
            nAB+=20; // 19 + 6 // -5
            if(bLog)
                sLog = PPM_ManageAttackLog(oPC, sLog, nAB, "(форма Дракона)", "20");

            // Monk
            nAB += GetLevelByClass(CLASS_TYPE_MONK, oPC)/8;
            if(bLog)
                sLog = PPM_ManageAttackLog(oPC, sLog, nAB, "(уровни Монаха)");

            // ChT
            nAB += GetLevelByClass(CLASS_TYPE_DIVINE_CHAMPION, oPC)/8;
            if(bLog)
                sLog = PPM_ManageAttackLog(oPC, sLog, nAB, "(уровни Воина Богов)");
        }
        else if(nPoly == 90) // Iron Golem
        {
            nAB+=16; // 11 + 5
            if(bLog)
                sLog = PPM_ManageAttackLog(oPC, sLog, nAB, "(форма Железного Голема)", "16");
            // Monk
            nAB += GetLevelByClass(CLASS_TYPE_MONK, oPC)/8;
            if(bLog)
                sLog = PPM_ManageAttackLog(oPC, sLog, nAB, "(уровни Монаха)");
            // ChT
            nAB += GetLevelByClass(CLASS_TYPE_DIVINE_CHAMPION, oPC)/5;
            if(bLog)
                sLog = PPM_ManageAttackLog(oPC, sLog, nAB, "(уровни Воина Богов)");
        }
        else if(nPoly == 91) // Stone Golem
        {
            nAB+=16; // 11 + 5
            if(bLog)
                sLog = PPM_ManageAttackLog(oPC, sLog, nAB, "(форма Каменного Голема)", "16");
            // Monk
            nAB += GetLevelByClass(CLASS_TYPE_MONK, oPC)/8;
            if(bLog)
                sLog = PPM_ManageAttackLog(oPC, sLog, nAB, "(уровни Монаха)");
            // ChT
            nAB += GetLevelByClass(CLASS_TYPE_DIVINE_CHAMPION, oPC)/8;
            if(bLog)
                sLog = PPM_ManageAttackLog(oPC, sLog, nAB, "(уровни Воина Богов)");
        }
        else if(nPoly == 92) // Flesh Golem
        {
            nAB+=16; // 11 + 5
            if(bLog)
                sLog = PPM_ManageAttackLog(oPC, sLog, nAB, "(форма Голема Плоти)", "16");
            // Monk
            nAB += GetLevelByClass(CLASS_TYPE_MONK, oPC)/8;
            if(bLog)
                sLog = PPM_ManageAttackLog(oPC, sLog, nAB, "(уровни Монаха)");
            // ChT
            nAB += GetLevelByClass(CLASS_TYPE_DIVINE_CHAMPION, oPC)/5;
            if(bLog)
                sLog = PPM_ManageAttackLog(oPC, sLog, nAB, "(уровни Воина Богов)");
        }
        else if(nPoly == POLYMORPH_TYPE_VAMPIRE_MALE || nPoly == POLYMORPH_TYPE_VAMPIRE_FEMALE)
        {
            nAB+=12; // 7 + 5
            if(bLog)
                sLog = PPM_ManageAttackLog(oPC, sLog, nAB, "(форма Вампира)", "12");
            // Monk
            nAB += GetLevelByClass(CLASS_TYPE_MONK, oPC)/5;
            if(bLog)
                sLog = PPM_ManageAttackLog(oPC, sLog, nAB, "(уровни Монаха)");
            // ChT
            nAB += GetLevelByClass(CLASS_TYPE_DIVINE_CHAMPION, oPC)/8;
            if(bLog)
                sLog = PPM_ManageAttackLog(oPC, sLog, nAB, "(уровни Воина Богов)");
        }
        else if(nPoly == POLYMORPH_TYPE_SPECTRE)
        {
            nAB+=6; // 5 + 6 // -5
            if(bLog)
                sLog = PPM_ManageAttackLog(oPC, sLog, nAB, "(форма Призрака)", "6");
            // Monk
            nAB += GetLevelByClass(CLASS_TYPE_MONK, oPC)/8;
            if(bLog)
                sLog = PPM_ManageAttackLog(oPC, sLog, nAB, "(уровни Монаха)");
            // ChT
            nAB += GetLevelByClass(CLASS_TYPE_DIVINE_CHAMPION, oPC)/8;
            if(bLog)
                sLog = PPM_ManageAttackLog(oPC, sLog, nAB, "(уровни Воина Богов)");
        }

        // Get AB from stats
        nAB+= PPM_GetABFromStats(oPC);
        if(bLog)
            sLog = PPM_ManageAttackLog(oPC, sLog, nAB, "(модификаторы характеристик)");

        // Get AB from feats
        if(GetHasFeat(FEAT_WEAPON_FOCUS_UNARMED_STRIKE, oPC))
        {
            nAB+= 1;
            if(bLog)
                sLog = PPM_ManageAttackLog(oPC, sLog, nAB, "(фокус Безоружный Бой)", "1");
        }
        if(GetHasFeat(FEAT_EPIC_WEAPON_FOCUS_UNARMED, oPC))
        {
            nAB+= 3;
            if(bLog)
                sLog = PPM_ManageAttackLog(oPC, sLog, nAB, "(эпический фокус Безоружный Бой)", "3");
        }
        if(GetHasFeat(FEAT_EPIC_PROWESS, oPC))
        {
            nAB+= 1;
            if(bLog)
                sLog = PPM_ManageAttackLog(oPC, sLog, nAB, "(Эпическая Доблесть)", "1");
        }
        if(GetActionMode(oPC, ACTION_MODE_POWER_ATTACK))
        {
            nAB-= 5;
            if(bLog)
                sLog = PPM_ManageAttackLog(oPC, sLog, nAB, "(Мощная атака)", PPM_CRED + "-5" + PPM_CFin);
        }
        if(GetActionMode(oPC, ACTION_MODE_IMPROVED_POWER_ATTACK))
        {
            nAB-= 10;
            if(bLog)
                sLog = PPM_ManageAttackLog(oPC, sLog, nAB, "(Улучшенная мощная атака)", PPM_CRED + "-10" + PPM_CFin);
        }
        if(GetActionMode(oPC, ACTION_MODE_EXPERTISE))
        {
            nAB-= 5;
            if(bLog)
                sLog = PPM_ManageAttackLog(oPC, sLog, nAB, "(Экспертиза)", PPM_CRED + "-5" + PPM_CFin);
        }
        if(GetActionMode(oPC, ACTION_MODE_IMPROVED_EXPERTISE))
        {
            nAB-= 10;
            if(bLog)
                sLog = PPM_ManageAttackLog(oPC, sLog, nAB, "(Улучшенная экспертиза)", PPM_CRED + "-10" + PPM_CFin);
        }



        // Race
        if(GetLocalInt(GetLocalObject(oPC, TOKEN_TAG), "OriginalAppType") == APPEARANCE_TYPE_HALF_ELF) // 4 = RACIAL_TYPE_HALFELF
        {
            nAB+= 6;
            if(bLog)
                sLog = PPM_ManageAttackLog(oPC, sLog, nAB, "(раса Светлый Эльф)", "6");
        }

        // Claws
        nAB += GetABFromCreatureItems(oPC);
        if(bLog)
            sLog = PPM_ManageAttackLog(oPC, sLog, nAB, "(естественное оружие существа)");

        DeleteLocalInt(oPC, "PPM_ShifterAttackLogTempValue");
        if(bLog)
            SetLocalString(oPC, "PPM_ShifterAttackLog", sLog);

        // Cash
        SetLocalInt(oPC, "PPM_ShifterAB", nAB);
        DelayCommand(5.8, DeleteLocalInt(oPC, "PPM_ShifterAB"));
    }
return nAB;
}
//------------------------------------------------------------------------------
int GetIsMonkAttack(object oPC)
{
    if(!GetLevelByClass(CLASS_TYPE_MONK, oPC))
        return FALSE;

    // Use weapon?
    object oLeftWeapon = GetItemInSlot(INVENTORY_SLOT_LEFTHAND);
    object oRightWeapon = GetItemInSlot(INVENTORY_SLOT_RIGHTHAND);
    int nLBase = GetBaseItemType(oLeftWeapon);
    int nRBase = GetBaseItemType(oRightWeapon);
    int bUseWeapon = (GetIsObjectValid(oRightWeapon) && nRBase != BASE_ITEM_KAMA) || (GetIsObjectValid(oLeftWeapon) && nLBase!= BASE_ITEM_TORCH && nLBase!= BASE_ITEM_KAMA);
    if(bUseWeapon)
        return FALSE;

    // Use armor?
    object oArmor = GetItemInSlot(INVENTORY_SLOT_CHEST);
    if(GetIsObjectValid(oArmor) && (GetItemACBaseValue(oArmor)>0))
        return FALSE;
return TRUE;
}
//------------------------------------------------------------------------------
int GetShifterAttacksCount(object oPC)
{
    int nAttacksCount = GetLocalInt(oPC, "PPM_ShifterAttacksCount");
    if(!nAttacksCount)
    {
        // General
        int nLevelsAbove20 = GetHitDice(oPC)>20 ? GetHitDice(oPC)-20 : 0;
        int nBAB = GetBaseAttackBonus(oPC) - ((nLevelsAbove20-1)/2 + 1);

        if(GetIsMonkAttack(oPC))
        {
            nAttacksCount = (nBAB-1)/3 + 1;
            if(nAttacksCount>6)
                nAttacksCount = 6;
        }
        else
            nAttacksCount = (nBAB-1)/5 + 1;

        if(PPM_GetHasEffect(EFFECT_TYPE_HASTE, oPC))
            nAttacksCount++;

        if(GetActionMode(oPC, ACTION_MODE_FLURRY_OF_BLOWS))
            nAttacksCount++;
        // End of general

        // Classes
        nAttacksCount+= GetLevelByClass(CLASS_TYPE_DWARVEN_DEFENDER, oPC)/20;

        // To special forms
        int nPoly = GetLocalInt(GetLocalObject(oPC, TOKEN_TAG), "isPolymorphed");
        if(nPoly == POLYMORPH_TYPE_VAMPIRE_MALE || nPoly == POLYMORPH_TYPE_VAMPIRE_FEMALE || nPoly == POLYMORPH_TYPE_SPECTRE)
            nAttacksCount+= GetLevelByClass(CLASS_TYPE_SHADOWDANCER, oPC)/10;

        // Cashing
        SetLocalInt(oPC, "PPM_ShifterAttacksCount", nAttacksCount);
        DelayCommand(5.8, DeleteLocalInt(oPC, "PPM_ShifterAttacksCount"));
    }
return nAttacksCount;
}
//------------------------------------------------------------------------------
int GetShifterCritRange(object oPC)
{
    int nCritRange = GetLocalInt(oPC, "PPM_ShifterCritRange");
    if(!nCritRange)
    {
        nCritRange = 20;
        if(GetHasFeat(FEAT_IMPROVED_CRITICAL_UNARMED_STRIKE))
            nCritRange-=1;

        nCritRange -= GetLevelByClass(CLASS_TYPE_SHIFTER, oPC)/9;
        nCritRange -= GetLevelByClass(CLASS_TYPE_DIVINE_CHAMPION, oPC)/8;
        int nPoly = GetLocalInt(GetLocalObject(oPC, TOKEN_TAG), "isPolymorphed");
        if(nPoly == POLYMORPH_TYPE_VAMPIRE_MALE || nPoly == POLYMORPH_TYPE_VAMPIRE_FEMALE)
        {
            nCritRange -= GetLevelByClass(CLASS_TYPE_MONK, oPC)/6;
            nCritRange -= GetLevelByClass(CLASS_TYPE_SHADOWDANCER, oPC)/12;
            nCritRange -= GetLevelByClass(CLASS_TYPE_BLACKGUARD, oPC)/5;
        }
        else if(nPoly == POLYMORPH_TYPE_SPECTRE)
            nCritRange -= GetLevelByClass(CLASS_TYPE_BLACKGUARD, oPC)/5;
        else
            nCritRange -= GetLevelByClass(CLASS_TYPE_BLACKGUARD, oPC)/8;

        // Cashing
        SetLocalInt(oPC, "PPM_ShifterCritRange", nCritRange);
        DelayCommand(5.8, DeleteLocalInt(oPC, "PPM_ShifterCritRange"));
    }
return nCritRange;
}
//------------------------------------------------------------------------------
int GetShifterCritMult(object oPC)
{
    int nCritMult = GetLocalInt(oPC, "PPM_ShifterCritMult");
    if(!nCritMult)
    {
        nCritMult = 2;
        nCritMult += GetLevelByClass(CLASS_TYPE_SHIFTER, oPC)/20;
        nCritMult += GetLevelByClass(CLASS_TYPE_DWARVEN_DEFENDER, oPC)/10;

        int nPoly = GetLocalInt(GetLocalObject(oPC, TOKEN_TAG), "isPolymorphed");
        if(nPoly == POLYMORPH_TYPE_SPECTRE)
        {
            nCritMult += GetLevelByClass(CLASS_TYPE_MONK, oPC)/20;
            nCritMult += GetLevelByClass(CLASS_TYPE_SHADOWDANCER, oPC)/20;
        }
        else if(nPoly == POLYMORPH_TYPE_VAMPIRE_MALE || nPoly == POLYMORPH_TYPE_VAMPIRE_FEMALE)
            nCritMult += GetLevelByClass(CLASS_TYPE_MONK, oPC)/20;


        // Cash
        SetLocalInt(oPC, "PPM_ShifterCritMult", nCritMult);
        DelayCommand(5.8, DeleteLocalInt(oPC, "PPM_ShifterCritMult"));
    }
return nCritMult;
}
//------------------------------------------------------------------------------
int GetShifterAttackPenalty(object oPC)
{
    if(GetIsMonkAttack(oPC))
        return 3;
return 5;
}
//------------------------------------------------------------------------------
float GetShifterAttackDistance(object oPC, object oTarget)
{
    float fRes;
    int nTargetSize = GetCreatureSize(oTarget);
    switch(nTargetSize)
    {
        case CREATURE_SIZE_HUGE: fRes = 4.5;    break;
        case CREATURE_SIZE_LARGE: fRes = 3.5;    break;
        case CREATURE_SIZE_MEDIUM: fRes = 2.5;    break;
        default: fRes = 2.0;
    }
return fRes; //3.0;
}
//------------------------------------------------------------------------------
int GetStunningFistDC(object oPC)
{
    int nFeat = FEAT_EPIC_IMPROVED_STUNNING_FIST_10;
    int nFeatBonus = 20;
    while(!GetHasFeat(nFeat, oPC) && nFeatBonus>0)
    {
        nFeat--;
        nFeatBonus-=2;
    }
return 10 + nFeatBonus + GetHitDice(oPC)/2 + GetAbilityModifier(ABILITY_WISDOM, oPC);
}
//------------------------------------------------------------------------------
void ShifterUseCombatFeat(object oPC, object oTarget, int nAB)
{
    int nFeat = GetLocalInt(oPC, "ShifterUseFeat");
    DeleteLocalInt(oPC, "ShifterUseFeat");

    if(!nFeat || !GetHasFeat(nFeat, oPC))
        return;

    string sLog;
    switch(nFeat)
    {
        case FEAT_IMPROVED_KNOCKDOWN:
            FloatingTextStringOnCreature("*Улучшенное сбивание с ног*", oPC);
            sLog = PPM_CCYAN + GetName(oPC) + PPM_CORANGE + " применяет улучшенное сбивание с ног против <cя я>" + GetName(oTarget) + PPM_CORANGE +" : ";
            if(!GetIsSkillSuccessful(oTarget, SKILL_DISCIPLINE, nAB-4))
            {
                sLog+= "*попадание*";
                ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectKnockdown(), oTarget, 6.0);
            }
            else
                sLog+= "*отражено*";

            SendMessageToPC(oPC, sLog);
            SendMessageToPC(oTarget, sLog);
        break;

        case FEAT_KNOCKDOWN:
            FloatingTextStringOnCreature("*Cбивание с ног*", oPC);
            sLog = PPM_CCYAN + GetName(oPC) + PPM_CORANGE + " применяет сбивание с ног против <cя я>" + GetName(oTarget) + PPM_CORANGE +" : ";
            if(!GetIsSkillSuccessful(oTarget, SKILL_DISCIPLINE, nAB-4))
            {
                sLog+= "*попадание*";
                ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectKnockdown(), oTarget, 6.0);
            }
            else
                sLog+= "*отражено*";

            SendMessageToPC(oPC, sLog);
            SendMessageToPC(oTarget, sLog);
        break;

        case FEAT_STUNNING_FIST:
            FloatingTextStringOnCreature("*Оглушающий кулак*", oPC);
            sLog = PPM_CCYAN + GetName(oPC) + PPM_CORANGE + " применяет оглушающий кулак против <cя я>" + GetName(oTarget) + PPM_CORANGE +" : ";
            if(!FortitudeSave(oTarget, GetStunningFistDC(oPC)))
            {
                sLog+= "*попадание*";
                ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectStunned(), oTarget, 18.0);
            }
            else
                sLog+= "*отражено*";

            SendMessageToPC(oPC, sLog);
            SendMessageToPC(oTarget, sLog);
        break;
    }

}
//------------------------------------------------------------------------------
void DoShifterSingleAttack(object oPC, object oTarget, int nAB)
{
    int nCritRange = GetShifterCritRange(oPC);
    int nTargetAC = GetAC(oTarget);
    int nCrit, nRoll = d20();
    int nMiss = FALSE;

    if(nRoll==1)
        nMiss = TRUE;
    else if(nRoll==20)
        nMiss = FALSE;
    else
    {
        if(nTargetAC > nRoll + nAB)
            nMiss = TRUE;
    }

    if(!nMiss)
    {
        if(nRoll>=nCritRange)
        {
            nCrit = d20();
            if(nTargetAC > nCrit + nAB)
                nCrit = 0;
        }
    }

    // Сначала лог, чтобы расчеты атаки в логах появились раньше урона
    string sLog = ShifterAttackLogString(oPC, oTarget, nRoll, nAB, nMiss, nCrit);
    SendMessageToPC(oPC, sLog);
    SendMessageToPC(oTarget, sLog);

    if(!nMiss)
    {
        ShifterUseCombatFeat(oPC, oTarget, nAB+nRoll);
        if(!nCrit)
            DoShifterSingleHit(oPC, oTarget);
        else
        {
            if(GetIsImmune(oTarget, IMMUNITY_TYPE_CRITICAL_HIT))
            {
                DoShifterSingleHit(oPC, oTarget);
                sLog = GetName(oTarget) + " : Иммунитет к Критическим ударам.";
                SendMessageToPC(oPC, sLog);
                SendMessageToPC(oTarget, sLog);
            }
            else
            {
                nCrit = GetShifterCritMult(oPC);
                DoShifterSingleHit(oPC, oTarget, nCrit);
            }
        }
    }
}
//------------------------------------------------------------------------------
void DoAttackFlurry(object oPC, object oTarget, int nInitAB, int nAttacksPerTurn)
{
    object oNextTarget = PPM_GetTarget(oPC);
    if(GetIsObjectValid(oNextTarget) && oNextTarget != oTarget)
    {
        SetLocalInt(oPC, "PPM_StopAttack", TRUE);
        AssignCommand(oPC, SetFacingPoint(GetPosition(oNextTarget)));
        AssignCommand(oPC, PlayAnimation(ANIMATION_LOOPING_CONJURE1, 1.0, 2.0));
        return;
    }

    if(GetLocalInt(oPC, "PPM_StopAttack"))
        return;

    if( PPM_GetHasEffect(EFFECT_TYPE_CHARMED, oPC) ||
        PPM_GetHasEffect(EFFECT_TYPE_CONFUSED, oPC) ||
        PPM_GetHasEffect(EFFECT_TYPE_CUTSCENE_PARALYZE, oPC) ||
        PPM_GetHasEffect(EFFECT_TYPE_DAZED, oPC) ||
        PPM_GetHasEffect(EFFECT_TYPE_DOMINATED, oPC) ||
        PPM_GetHasEffect(EFFECT_TYPE_FRIGHTENED, oPC) ||
        PPM_GetHasEffect(EFFECT_TYPE_PARALYZE, oPC) ||
        PPM_GetHasEffect(EFFECT_TYPE_PETRIFY, oPC) ||
        PPM_GetHasEffect(EFFECT_TYPE_SLEEP, oPC) ||
        PPM_GetHasEffect(EFFECT_TYPE_STUNNED, oPC) ||
        PPM_GetHasEffect(EFFECT_TYPE_TIMESTOP, oPC) ||
        GetHasFeatEffect(FEAT_KNOCKDOWN, oPC) || GetHasFeatEffect(FEAT_IMPROVED_KNOCKDOWN, oPC))
    {
        SetLocalInt(oPC, "PPM_StopAttack", TRUE);
        return;
    }


    if(GetIsDead(oTarget))
    {
        SetLocalInt(oPC, "PPM_StopAttack", TRUE);
        oNextTarget = GetNearestCreature(CREATURE_TYPE_REPUTATION, REPUTATION_TYPE_ENEMY, oPC);
        if(GetIsObjectValid(oNextTarget) && !GetIsDead(oNextTarget) && GetDistanceBetween(oPC, oNextTarget)<=5.0)
        {
            PPM_SetTarget(oPC, oNextTarget);
            AssignCommand(oPC, SetFacingPoint(GetPosition(oNextTarget)));
            AssignCommand(oPC, PlayAnimation(ANIMATION_LOOPING_CONJURE1, 1.0, 2.0));
        }
        return;
    }

    if(!GetObjectSeen(oTarget, oPC) && !GetHasFeat(FEAT_BLIND_FIGHT, oPC))
    {
        SetLocalInt(oPC, "PPM_StopAttack", TRUE);
        AssignCommand(oPC, ClearAllActions());
        FloatingTextStringOnCreature("Вы не видите врага!", oPC);
        return;
    }


    int nAction = GetCurrentAction(oPC);
    if(nAction == ACTION_ATTACKOBJECT) // Автоатака
        AssignCommand(oPC, ClearAllActions());
    else if(nAction != ACTION_INVALID && nAction != ACTION_FOLLOW)
    {
        SetLocalInt(oPC, "PPM_StopAttack", TRUE);
        return;
    }
    float fAttackDist = GetShifterAttackDistance(oPC, oTarget);
    float fDist = GetDistanceBetween(oPC, oTarget);
    if(fDist > (fAttackDist+1.5))
    {
        if(fDist < 15.0)
            AssignCommand(oPC, ActionForceFollowObject(oTarget, fAttackDist-0.5));
        else
        {
            FloatingTextStringOnCreature("Цель слишком далеко!", oPC);
            AssignCommand(oPC, ClearAllActions());
            SetLocalInt(oPC, "PPM_StopAttack", TRUE);
        }
        return;
    }

    AssignCommand(oPC, SetFacingPoint(GetPosition(oTarget)));
    AssignCommand(oPC, PlayAnimation(ANIMATION_LOOPING_GET_MID, 1.0, 1.0));
    int nPennalty = GetShifterAttackPenalty(oPC);
    int i;
    for(i = 0; i<nAttacksPerTurn; i++)
        DelayCommand(0.5+0.3*i, DoShifterSingleAttack(oPC, oTarget, nInitAB - nPennalty*i));
    //DelayCommand(0.7, AssignCommand(oPC, PlayAnimation(ANIMATION_LOOPING_CONJURE1, 1.0, 1.3)));
}
//------------------------------------------------------------------------------
void CheckForContinueAttack(object oPC, object oTarget)
{
    int nStopAttack = GetLocalInt(oPC, "PPM_StopAttack");
    DeleteLocalInt(oPC, "PPM_StopAttack");

    object oNextTarget = PPM_GetTarget(oPC);
    DeleteLocalObject(oPC, "PPM_ShifterAttackTarget");
    if(GetIsObjectValid(oNextTarget))
        oTarget = oNextTarget;
    else if(nStopAttack)
    {
        FloatingTextStringOnCreature("*Атака оборотня завершена*", oPC, FALSE);
        return;
    }


    if(!GetObjectSeen(oTarget, oPC) || GetIsDead(oTarget))
    {
        oNextTarget = GetNearestCreature(CREATURE_TYPE_REPUTATION, REPUTATION_TYPE_ENEMY, oPC);
        if(GetIsObjectValid(oNextTarget) && !GetIsDead(oNextTarget) && GetDistanceBetween(oPC, oNextTarget)<=2.0)
            PPM_SetTarget(oPC, oNextTarget);
        else
            FloatingTextStringOnCreature("*Атака оборотня завершена*", oPC, FALSE);
        return;
    }
    int nAction = GetCurrentAction(oPC);
    if(nAction == ACTION_ATTACKOBJECT) // Автоатака
        AssignCommand(oPC, ClearAllActions());
    else if(nAction != ACTION_INVALID && nAction != ACTION_FOLLOW)
    {
        FloatingTextStringOnCreature("*Атака оборотня завершена*", oPC, FALSE);
        return;
    }
    if((GetArea(oPC) != GetArea(oTarget)) || (GetDistanceBetween(oPC, oTarget) > 6.0))
    {
        FloatingTextStringOnCreature("*Атака оборотня завершена*", oPC, FALSE);
        return;
    }

    AssignCommand(oPC, ActionForceFollowObject(oTarget, GetShifterAttackDistance(oPC, oTarget)-0.5));
    PPM_SetTarget(oPC, oTarget); // Нужна тут для OnHit еффектов
    DoShifterAttack(oPC, oTarget, TRUE, FALSE);
}
//------------------------------------------------------------------------------
void DoShifterAttack(object oPC, object oTarget, int bFirstActivation = FALSE, int bNeedBeginAttackMess = TRUE)
{
    // Для рекурсивной проверки дистанции
    if(GetLocalInt(oPC, "ShifterAttackAlreadyUsed"))
        return;
    SetLocalInt(oPC, "ShifterAttackAlreadyUsed", TRUE);
    DelayCommand(0.99, DeleteLocalInt(oPC, "ShifterAttackAlreadyUsed"));

    // Проверки видимости
    if(!GetObjectSeen(oTarget, oPC) || GetIsDead(oTarget))
    {
        AssignCommand(oPC, ClearAllActions());
        return;
    }

    // Проверка локации
    if(GetArea(oPC) != GetArea(oTarget)) // Цель сбежала в другую локу
    {
        AssignCommand(oPC, ClearAllActions());
        return;
    }

    // Проверка дистанции
    float fAttackDist = GetShifterAttackDistance(oPC, oTarget);
    float fDist = GetDistanceBetween(oPC, oTarget);
    if(fDist > fAttackDist)
    {
        if(fDist > 15.0)
        {
            FloatingTextStringOnCreature("Цель слишком далеко!", oPC);
            AssignCommand(oPC, ClearAllActions());
            return;
        }

        // Для отмены атаки
        if(GetCurrentAction(oPC) == ACTION_FOLLOW || bFirstActivation) // Действие Follow запускается дольше чем выполнение доходит до этого места. Поэтому нужна bFirstActivation
            DelayCommand(1.0, DoShifterAttack(oPC, oTarget));
        return;
    }
    else
        AssignCommand(oPC, ClearAllActions());


    // Основной код атаки
    if(GetLocalInt(oPC, "ShifterAttackInProccess"))
        return;
    SetLocalInt(oPC, "ShifterAttackInProccess", TRUE);
    if(bNeedBeginAttackMess)
        FloatingTextStringOnCreature("*Атака оборотня*", oPC);
    DelayCommand(5.9, DeleteLocalInt(oPC, "ShifterAttackInProccess"));
    //DelayCommand(5.9, FloatingTextStringOnCreature("*Атака оборотня завершена*", oPC, FALSE));

    int nAttacksCount = GetShifterAttacksCount(oPC);                            //DBM("ppm_inc", "DoShifterAttack", "nAttacksCount" + IToS(nAttacksCount));
    int nAttacksPerFlurry3 = nAttacksCount/3;
    int nAttacksPerFlurry2 = (nAttacksCount%3)/2 + nAttacksPerFlurry3;
    int nAttacksPerFlurry1 = nAttacksCount - nAttacksPerFlurry2 - nAttacksPerFlurry3;
    int nInitAB = GetShifterAttackBonus(oPC);

    DoAttackFlurry(oPC, oTarget, nInitAB, nAttacksPerFlurry1);
    if(nAttacksPerFlurry2)
        DelayCommand(2.0, DoAttackFlurry(oPC, oTarget, nInitAB - GetShifterAttackPenalty(oPC)*nAttacksPerFlurry1, nAttacksPerFlurry2));

    if(nAttacksPerFlurry3)
        DelayCommand(4.0, DoAttackFlurry(oPC, oTarget, nInitAB - GetShifterAttackPenalty(oPC)*(nAttacksPerFlurry1+nAttacksPerFlurry2), nAttacksPerFlurry3));


    DelayCommand(6.0, CheckForContinueAttack(oPC, oTarget));
}
//------------------------------------------------------------------------------
void ShowShifterAttackInfo(object oPC)
{
    SendMessageToPC(oPC, PPM_CWHITE + "ПАРАМЕТРЫ АТАКИ ОБОРОТНЯ:");
    SendMessageToPC(oPC, "Бонус атаки: " + PPM_CGREEN + IntToString(GetShifterAttackBonus(oPC, TRUE)));
    SendMessageToPC(oPC, GetLocalString(oPC, "PPM_ShifterAttackLog"));
    DeleteLocalString(oPC, "PPM_ShifterAttackLog");

    string sTemp1, sTemp2;
    effect edam = EffectShifterDamage(oPC, 1, TRUE); // Чтобы закэшировались рассчеты
    sTemp1 = IntToString(GetLocalInt(oPC, "PPM_ShifterPhysMin"));
    sTemp2 = IntToString(GetLocalInt(oPC, "PPM_ShifterPhysMax"));
    SendMessageToPC(oPC, "Физический урон: " + PPM_CORANGE + sTemp1 + "-" + sTemp2);
    SendMessageToPC(oPC, GetLocalString(oPC, "PPM_ShifterPhysDamLog"));
    DeleteLocalString(oPC, "PPM_ShifterPhysDamLog");

    sTemp1 = IntToString(GetLocalInt(oPC, "PPM_ShifterMagicMin"));
    sTemp2 = IntToString(GetLocalInt(oPC, "PPM_ShifterMagicMax"));
    SendMessageToPC(oPC, "Магический урон: " + PPM_CVIOLET + sTemp1 + "-" + sTemp2);
    SendMessageToPC(oPC, GetLocalString(oPC, "PPM_ShifterMagDamLog"));
    DeleteLocalString(oPC, "PPM_ShifterMagDamLog");
    int nPower = GetLocalInt(oPC, "PPM_ShifterDamPow");
    if(nPower>6)
        nPower-= 1;
    SendMessageToPC(oPC, "Улучшение: " + PPM_CWHITE + IntToString(nPower));

    SendMessageToPC(oPC, "Диапазон критического удара: " + PPM_CRED + IntToString(GetShifterCritRange(oPC)) + "-20");
    SendMessageToPC(oPC, "Множитель критического удара: " + PPM_CRED + "х" + IntToString(GetShifterCritMult(oPC)));

    SendMessageToPC(oPC, "Количество атак в раунд: " + PPM_CBLUE + IntToString(GetShifterAttacksCount(oPC)));
    SendMessageToPC(oPC, "Штраф следующей атаки: " + PPM_CCYAN + IntToString(GetShifterAttackPenalty(oPC)));
}
