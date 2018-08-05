//#include "sl_s_dbsys_inc"
//#include "x2_inc_itemprop"
#include "tob_check_inc"
#include "sl_s_grade_inc"


const int IP_GROUP_MELEE_WEAPON         = 1;
const int IP_GROUP_RANGED_WEAPON        = 2;
const int IP_GROUP_ARMOR                = 3;
const int IP_GROUP_HELM                 = 4;
const int IP_GROUP_CLOAK                = 5;
const int IP_GROUP_AMULET               = 6;
const int IP_GROUP_BOOTS                = 7;
const int IP_GROUP_RINGS                = 8;
const int IP_GROUP_BELTS                = 9;
const int IP_GROUP_GLOVES               = 10;
const int IP_GROUP_SHIELDS              = 12;
const int IP_GROUP_BRACERS              = 13;


const int IP_GRADE_1                    = 1;
const int IP_GRADE_2                    = 2;
const int IP_GRADE_3                    = 3;

//Проверка на имбу Рекс-Ферона. Значение выше которого вещь нельзя пропускать в игру. Если задан 0, проверка выключена
const int IMBO_LIMIT                    = 400;


//const int ITEM_EXP_NEED_FOR_THE_FIRST_LEVELUP = 100;
//const int ITEM_EXP_ADDITIONAL_COST = 10;


/////////////////////////////////////////////////////////////////////////

void LevelUpItemIfNecessary(object oItem); // v3.0 //bZ 09.2017

//Upgrading-Items system by Zoran "sl_s_slw_inc"
void DivideExpBetweenItems(object oPC, float fExp);

object CreateLevelingUpItem_New(object oItem1, object oPC, int bTest = FALSE);

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


////////////////////////// 2013 PART(NEW) ////////////////////////////////
//"inc_adutils"
int getItemLevel_New(object oItem)
{                                                                               //DBM("sl_s_slw_inc", "getItemLevel_New", "START with oItem" + OToS(oItem));
    int n;
    if (GetIdentified(oItem))
    {
        n = GetGoldPieceValue(oItem);
    }
    else
    {
        SetIdentified(oItem, TRUE);
        n = GetGoldPieceValue(oItem);
        SetIdentified(oItem, FALSE);
    }
                                                                                //DBM("sl_s_slw_inc", "getItemLevel_New", "GoldPieceValue" + IToS(n));
    if(n>=0 && n<=1000)
     return 1;
    else if(n>1000 && n<=1500)
     return 2;
    else if(n>1500 && n<=2500)
     return 3;
    else if(n>2500 && n<=3500)
     return 4;
    else if(n>3500 && n<=5000)
     return 5;
    else if(n>5000 && n<=6500)
     return 6;
    else if(n>6500 && n<=9000)
     return 7;
    else if(n>9000 && n<=12000)
     return 8;
    else if(n>12000 && n<=15000)
     return 9;
    else if(n>15000 && n<=19500)
     return 10;
    else if(n>19500 && n<=25000)
     return 11;
    else if(n>25000 && n<=30000)
     return 12;
    else if(n>30000 && n<=35000)
     return 13;
    else if(n>35000 && n<=40000)
     return 14;
    else if(n>40000 && n<=50000)
     return 15;
    else if(n>50000 && n<=65000)
     return 16;
    else if(n>65000 && n<=75000)
     return 17;
    else if(n>75000 && n<=90000)
     return 18;
    else if(n>90000 && n<=110000)
     return 19;
    else if(n>110000 && n<=130000)
     return 20;
    else if(n>130000 && n<=150000)
     return 21;
    else if(n>150000 && n<=170000)
     return 22;
    else if(n>170000 && n<=200000)
     return 23;
    else if(n>200000 && n<=250000)
     return 24;
    else if(n>250000 && n<=300000)
     return 25;
    else if(n>300000 && n<=350000)
     return 26;
    else if(n>350000 && n<=400000)
     return 27;
    else if(n>400000 && n<=450000)
     return 28;
    else if(n>450000 && n<=500000)
     return 29;
    else if(n>500000 && n<=550000)
     return 30;
    else if(n>550000 && n<=600000)
     return 31;
    else if(n>600000 && n<=650000)
     return 32;
    else if(n>650000 && n<=700000)
     return 33;
    else if(n>700000 && n<=750000)
     return 34;
    else if(n>750000 && n<=800000)
     return 35;
    else if(n>800000 && n<=850000)
     return 36;
    else if(n>850000 && n<=900000)
     return 37;
    else if(n>900000 && n<=950000)
     return 38;
    else if(n>950000 && n<=1000000)
     return 39;
    else if(n>1000000 && n<=1100000)
     return 40;

    else
        return 40;

    /*
    else if(n>1100000 && n<=1200000)
     return 41;
    else if(n>1200000 && n<=1300000)
     return 42;
    else if(n>1300000 && n<=1400000)
     return 43;
    else if(n>1400000 && n<=1500000)
     return 44;
    else if(n>1500000 && n<=1600000)
     return 45;
    else if(n>1600000 && n<=1700000)
     return 46;
    else if(n>1700000 && n<=1800000)
     return 47;
    else if(n>1800000 && n<=1900000)
     return 48;
    else if(n>1900000 && n<=2000000)
     return 49;
    else if(n>2000000 && n<=2100000)
     return 50;
    else if(n>2100000 && n<=2200000)
     return 51;
    else if(n>2200000 && n<=2300000)
     return 52;
    else if(n>2300000 && n<=2400000)
     return 53;
    else if(n>2400000 && n<=2500000)
     return 54;
    else if(n>2500000 && n<=2600000)
     return 55;
    else if(n>2600000 && n<=2700000)
     return 56;
    else if(n>2700000 && n<=2800000)
     return 57;
    else if(n>2800000 && n<=2900000)
     return 58;
    else if(n>2900000 && n<=3000000)
     return 59;
    else if(n>3000000 && n<=3500000)
     return 60;
    else
     return 61;
    */
}




//////////////////////////////////////////////////////////////////////////
//                                                                      //
//                         EXP DIVISION FUNCTIONS                       //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

int GetItemExp(object oItem)
{
    int nResult = GetLocalInt(oItem, "nItemExp");                               //DBM("sl_s_slw_inc", "GetItemExp", "nResult" + IToS(nResult));
return nResult;
}
//------------------------------------------------------------------------------
void SetItemExp(object oItem, int nExp)
{
    SetLocalInt(oItem, "nItemExp", nExp);                                       //DBM("sl_s_slw_inc", "SetItemExp", "nExp" + IToS(nExp));
return;
}
//------------------------------------------------------------------------------
int GetItemPseudoLevel(object oItem)
{
    int nResult = GetLocalInt(oItem, "nItemLvl");                               //DBM("sl_s_slw_inc", "GetItemPseudoLevel", "nResult" + IToS(nResult));
return nResult;
}
//------------------------------------------------------------------------------
// v2.0
int ItemLevelToItemExp(int nItemLevel, int nGrade)
{                                                                               //DBM("sl_s_slw_inc", "ItemLevelToItemExp", "Begin with nItemLevel" + IToS(nItemLevel));
    int nItemExp;

    // v3.0
    int i, nAddBase, nAddition, nLimit;
    switch(nGrade)
    {
        case 1: nAddBase = 10;  nLimit = 200;   break;
        case 2: nAddBase = 50;  nLimit = 600;   break;
        case 3: nAddBase = 100; nLimit = 1200;  break;
    }
    for(i=0; i<nItemLevel; i++)
    {
        nAddition = nAddBase*i + 100;
        if(nAddition>nLimit)
            nAddition = nLimit;
        nItemExp += nAddition;
    }


    /* v2.0
    switch(nItemLevel)
    {
        case 1:     nItemExp = 100;  break;
        case 2:     nItemExp = 210;  break;
        case 3:     nItemExp = 330;  break;
        case 4:     nItemExp = 460;  break;
        case 5:     nItemExp = 600;  break;
        case 6:     nItemExp = 750;  break;
        case 7:     nItemExp = 910;  break;
        case 8:     nItemExp = 1080;  break;
        case 9:     nItemExp = 1260;  break;
        case 10:    nItemExp = 1450;  break;
        case 11:    nItemExp = 1650;  break;
        case 12:    nItemExp = 1860;  break;
        case 13:    nItemExp = 2080;  break;
        case 14:    nItemExp = 2310;  break;
        case 15:    nItemExp = 2550;  break;
        case 16:    nItemExp = 2800;  break;
        case 17:    nItemExp = 3060;  break;
        case 18:    nItemExp = 3330;  break;
        case 19:    nItemExp = 3610;  break;
        case 20:    nItemExp = 3900;  break;
        case 21:    nItemExp = 4200;  break;
        case 22:    nItemExp = 4510;  break;
        case 23:    nItemExp = 4830;  break;
        case 24:    nItemExp = 5160;  break;
        case 25:    nItemExp = 5500;  break;
        case 26:    nItemExp = 5850;  break;
        case 27:    nItemExp = 6210;  break;
        case 28:    nItemExp = 6580;  break;
        case 29:    nItemExp = 6960;  break;
        case 30:    nItemExp = 7350;  break;
    }

    if(nItemLevel>30)
        nItemExp = 400*(nItemLevel-30)+7350;
    */


    /* v1.0
    int nLvl = 3;
    int nExpForNextLvlUp;
    int nHighestCoeff;
    int nArithMean;

    if (nItemLevel < 2)
        nItemExp = 0;

    else if (nItemLevel >= 2)
        nItemExp = ITEM_EXP_NEED_FOR_THE_FIRST_LEVELUP;


    else
    {
        nHighestCoeff = ITEM_EXP_ADDITIONAL_COST*(nItemLevel-2);                //DBM("sl_s_slw_inc", "ItemLevelToItemExp", "Result nItemExp" + IToS(nItemExp));
        nArithMean = (nHighestCoeff + ITEM_EXP_ADDITIONAL_COST) / 2;            //DBM("sl_s_slw_inc", "ItemLevelToItemExp", "Result nItemExp" + IToS(nItemExp));
        nItemExp = (ITEM_EXP_NEED_FOR_THE_FIRST_LEVELUP*(nItemLevel-1)) + (nArithMean*(nItemLevel-2));
    }*/
                                                                                //DBM("sl_s_slw_inc", "ItemLevelToItemExp", "Result nItemExp" + IToS(nItemExp));
return nItemExp;
}
//------------------------------------------------------------------------------
/*
// v2.0
void DivideExpBetweenItems(object oPC, float fExp)
{                                                                               //DBM("sl_s_slw_inc", "DivideExpBetweenItems", "Begin with oPC" + OToS(oPC));
                                                                                //DBM("sl_s_slw_inc", "DivideExpBetweenItems", "Begin with fExp" + FToS(fExp));
    object oItem;
    int nInventorySlot, nNumberOfItems, nItemExp;
    for(nInventorySlot = 0; nInventorySlot < 11; nInventorySlot++)
    {
        oItem = GetItemInSlot(nInventorySlot, oPC);                             //DBM("sl_s_slw_inc", "DivideExpBetweenItems", "oItem" + OToS(oItem));
        if(GetLocalInt(oItem, "nRemainLvlUps"))  // && (GetLocalInt(oItem, "AlreadyHasLevelUp") != GetHitDice(oPC)))
        {
            nNumberOfItems++;
            SetLocalObject(oPC, ("LvlingUpItem_" + IntToString(nNumberOfItems)), oItem);
        }
    }

    if(nNumberOfItems)
    {
        int n;
        int nExpForItems = FloatToInt(fExp * 0.3 / nNumberOfItems);
        if(nExpForItems < nNumberOfItems)
            nExpForItems = nNumberOfItems;
                                                                                //DBM("sl_s_slw_inc", "DivideExpBetweenItems", "nExpForItems" + IToS(nExpForItems));
        for (n = 1; n <= nNumberOfItems; n++)
        {
            oItem = GetLocalObject(oPC, ("LvlingUpItem_" + IntToString(n)));    //DBM("sl_s_slw_inc", "DivideExpBetweenItems", "oItem" + OToS(oItem));
            nItemExp = GetItemExp(oItem);
            SetItemExp(oItem, (nItemExp + nExpForItems));
            if(GetLocalInt(oItem, "AlreadyHasLevelUp") != GetHitDice(oPC))
                LevelUpItemIfNecessary(oItem);

            DeleteLocalObject(oPC, ("LvlingUpItem_" + IntToString(n)));
        }
    }
    //int nExpToPlayer = nExp - nExpForItems;                                     //DBM("sl_s_slw_inc", "DivideExpBetweenItemsAndReturnExpForPlayer", "nExpToPlayer" + IToS(nExpToPlayer));

//return nExp;//nExpToPlayer;
}*/
//------------------------------------------------------------------------------
void DivideExpBetweenItems(object oPC, float fExp) // v3.0 //bZ 09.2017
{                                                                               //DBM("SLW", "DivideExpBetweenItems", "fExp" + FToS(fExp));
    object oItem;
    int nInventorySlot, nNumberOfItems, nStatus;
    for(nInventorySlot = 0; nInventorySlot < 11; nInventorySlot++)
    {
        oItem = GetItemInSlot(nInventorySlot, oPC);
        nStatus = GetLocalInt(oItem, "SLW_Status");
        if(nStatus==1)
        {
            nNumberOfItems++;
            SetLocalObject(oPC, ("LvlingUpItem_" + IntToString(nNumberOfItems)), oItem);
        }
        else if((nStatus>1) && (nStatus!=GetHitDice(oPC)))
            LevelUpItemIfNecessary(oItem);
    }

    if(nNumberOfItems)
    {
        int n;
        int nExpForItems = FloatToInt(fExp * 0.3 / nNumberOfItems);
        if(nExpForItems < nNumberOfItems)
            nExpForItems = nNumberOfItems;

        for (n = 1; n <= nNumberOfItems; n++)
        {
            oItem = GetLocalObject(oPC, ("LvlingUpItem_" + IntToString(n)));
            SetItemExp(oItem, (GetItemExp(oItem) + nExpForItems));
            LevelUpItemIfNecessary(oItem);

            DeleteLocalObject(oPC, ("LvlingUpItem_" + IntToString(n)));
        }
    }
}
//------------------------------------------------------------------------------
int GetItemGrade(object oItem)
{                                                                               //DBM("sl_s_slw_inc", "GetItemGrade", "Begin with oItem" + OToS(oItem));
    int nGrade = GetLocalInt(oItem, "nItemGrade");                              //DBM("sl_s_slw_inc", "GetItemGrade", "nGrade" + IToS(nGrade));

return nGrade;
}
//------------------------------------------------------------------------------



//////////////////////////////////////////////////////////////////////////
//                                                                      //
//                          LEVELUP FUNCTIONS                           //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

int GetIsLevelingUpProperty(itemproperty ipProp)
{
    if (GetItemPropertyDurationType(ipProp) == DURATION_TYPE_TEMPORARY)
        return FALSE;

    int nPropType = GetItemPropertyType(ipProp);
    if ((nPropType == ITEM_PROPERTY_ABILITY_BONUS)                  ||
        (nPropType == ITEM_PROPERTY_SKILL_BONUS)                    ||
        (nPropType == ITEM_PROPERTY_ATTACK_BONUS)                   ||
        (nPropType == ITEM_PROPERTY_ENHANCEMENT_BONUS)              ||
        (nPropType == ITEM_PROPERTY_IMMUNITY_DAMAGE_TYPE)           || //20.09.2013
        (nPropType == ITEM_PROPERTY_DAMAGE_BONUS)                   ||
        (nPropType == ITEM_PROPERTY_DAMAGE_RESISTANCE)              || //21.09.2013
        (nPropType == ITEM_PROPERTY_SAVING_THROW_BONUS)             ||
        (nPropType == ITEM_PROPERTY_SAVING_THROW_BONUS_SPECIFIC)    ||
        (nPropType == ITEM_PROPERTY_AC_BONUS)                       ||
        (nPropType == ITEM_PROPERTY_REGENERATION)                   ||
        (nPropType == ITEM_PROPERTY_DAMAGE_REDUCTION)               ||
        (nPropType == ITEM_PROPERTY_MIGHTY)                         ||
        (nPropType == ITEM_PROPERTY_MASSIVE_CRITICALS)              ||
        (nPropType == ITEM_PROPERTY_REGENERATION_VAMPIRIC)          ||
        (nPropType == ITEM_PROPERTY_ON_HIT_PROPERTIES)              || //10.09.2017
        (nPropType == ITEM_PROPERTY_SPELL_RESISTANCE))
        return TRUE;

return FALSE;
}



itemproperty ItemProperty(int nIpType, int nCostTableValue, int nIpSubType = -1, int nParam1 = -1);
// v2.0
itemproperty ItemProperty(int nIpType, int nCostTableValue, int nIpSubType = -1, int nParam1 = -1)
{                                                                               //DBM("sl_s_slw_inc", "ItemProperty", "IP Type" + IToS(nIpType));
                                                                                //DBM("sl_s_slw_inc", "ItemProperty", "nValue" + IToS(nCostTableValue));
                                                                                //DBM("sl_s_slw_inc", "ItemProperty", "IP SubType" + IToS(nIpSubType));
    itemproperty ipResult;
    if (nIpType == ITEM_PROPERTY_ABILITY_BONUS)
        ipResult = ItemPropertyAbilityBonus(nIpSubType, nCostTableValue);

    else if (nIpType == ITEM_PROPERTY_SKILL_BONUS)
        ipResult = ItemPropertySkillBonus(nIpSubType, nCostTableValue);

    else if (nIpType == ITEM_PROPERTY_ATTACK_BONUS)
        ipResult = ItemPropertyAttackBonus(nCostTableValue);

    else if (nIpType == ITEM_PROPERTY_ENHANCEMENT_BONUS)
        ipResult = ItemPropertyEnhancementBonus(nCostTableValue);

    else if (nIpType == ITEM_PROPERTY_DAMAGE_BONUS)
        ipResult = ItemPropertyDamageBonus(nIpSubType, nCostTableValue);

    else if (nIpType == ITEM_PROPERTY_SAVING_THROW_BONUS)
        ipResult = ItemPropertyBonusSavingThrowVsX(nIpSubType, nCostTableValue);

    else if (nIpType == ITEM_PROPERTY_SAVING_THROW_BONUS_SPECIFIC)
        ipResult = ItemPropertyBonusSavingThrow(nIpSubType, nCostTableValue);

    else if (nIpType == ITEM_PROPERTY_AC_BONUS)
        ipResult = ItemPropertyACBonus(nCostTableValue);

    else if (nIpType == ITEM_PROPERTY_REGENERATION)
        ipResult = ItemPropertyRegeneration(nCostTableValue);

    else if (nIpType == ITEM_PROPERTY_DAMAGE_REDUCTION)
        ipResult = ItemPropertyDamageReduction(nIpSubType, nCostTableValue);

    else if (nIpType == ITEM_PROPERTY_MIGHTY)
        ipResult = ItemPropertyMaxRangeStrengthMod(nCostTableValue);

     else if (nIpType == ITEM_PROPERTY_MASSIVE_CRITICALS)
        ipResult = ItemPropertyMassiveCritical(nCostTableValue);

     else if (nIpType == ITEM_PROPERTY_REGENERATION_VAMPIRIC)
        ipResult = ItemPropertyVampiricRegeneration(nCostTableValue);

    else if (nIpType == ITEM_PROPERTY_SPELL_RESISTANCE)
        ipResult = ItemPropertyBonusSpellResistance(nCostTableValue);

    else if (nIpType == ITEM_PROPERTY_IMMUNITY_DAMAGE_TYPE)
        ipResult = ItemPropertyDamageImmunity(nIpSubType, nCostTableValue);


    else if (nIpType == ITEM_PROPERTY_KEEN)
        ipResult = ItemPropertyKeen();

    else if (nIpType == ITEM_PROPERTY_CAST_SPELL)
        ipResult = ItemPropertyCastSpell(nIpSubType, nCostTableValue);

    else if (nIpType == ITEM_PROPERTY_BONUS_FEAT)
        ipResult = ItemPropertyBonusFeat(nIpSubType);

    else if (nIpType == ITEM_PROPERTY_UNLIMITED_AMMUNITION)
        ipResult = ItemPropertyUnlimitedAmmo(nIpSubType);

    else if (nIpType == ITEM_PROPERTY_DAMAGE_RESISTANCE)
        ipResult = ItemPropertyDamageResistance(nIpSubType, nCostTableValue);

    else if (nIpType == ITEM_PROPERTY_BONUS_SPELL_SLOT_OF_LEVEL_N)
        ipResult = ItemPropertyBonusLevelSpell(nIpSubType, nCostTableValue);

    // 09.2017
    else if(nIpType == ITEM_PROPERTY_ON_HIT_PROPERTIES)
    {
        // Забавный недочет в движке. Если взять с вещи свойство к примеру "при ударе малый диспел",
        // разложить его на составляющие параметры(Type, SubType, Param1 и т.д.), затем при помощи этих же данных
        // собраться свойство заново - оно уже будет невалидным. Причина в том что конкретно в малом диспеле(и не только)
        // не используется Param1. Соответственно, когда берем этот параметр со свойства, получаем -1. Но если
        // в функцию ItemPropertyOnHitProps(), в аргумент Special, куда идет Param1, мы подставим -1, свойство не будет создано.
        // Исправляем эту херню
        if(nParam1==-1)
            nParam1 = 0;
        ipResult = ItemPropertyOnHitProps(nIpSubType, nCostTableValue, nParam1);
    }
    // 09.2017
    else if(nIpType == ITEM_PROPERTY_EXTRA_RANGED_DAMAGE_TYPE)
        ipResult = ItemPropertyExtraRangeDamageType(nIpSubType);
    // 05.2018
    else if(nIpType == ITEM_PROPERTY_ONHITCASTSPELL)
        ipResult = ItemPropertyOnHitCastSpell(nIpSubType, nCostTableValue);



    if(!GetIsItemPropertyValid(ipResult))
    {
        string sMessage = "<cя  >[SLW] Критическая ошибка. Не существует свойства с параметрами: nIpType="+IntToString(nIpType) + ", nIpSubType=" + IntToString(nIpSubType) + ", nCostTableValue=" + IntToString(nCostTableValue) + ", nParam1=" + IntToString(nParam1);
        object oPC = GetFirstPC();
        while(GetIsObjectValid(oPC))
        {
            SendMessageToPC(oPC, sMessage);
            oPC = GetNextPC();
        }

        //SendMessageToAllDMs(sMessage);
        WriteTimestampedLogEntry(sMessage);

    }
return ipResult;
}


/*
// v2.0
itemproperty UpgradeItemProperty(int nIpType, int nCostTableValue, int nIpSubType = -1)
{
    itemproperty ipResult;
    int nNewValue, nMaxValue, nRandom;
    if(nIpType == ITEM_PROPERTY_SPELL_RESISTANCE)
    {
        switch(nCostTableValue)
        {
            case 3:     nNewValue = 5;      break;
            case 5:     nNewValue = 7;      break;
            case 7:     nNewValue = 9;      break;
            case 9:     nNewValue = 11;     break;
        }
        if(nNewValue>0)
            ipResult = ItemPropertyBonusSpellResistance(nNewValue);
    }

    else if(nIpType == ITEM_PROPERTY_MASSIVE_CRITICALS)
    {
        switch(nCostTableValue)
        {
            case 12:    nNewValue = 10;      break;
            case 10:    nNewValue = 11;      break;
            case 11:    nNewValue = 13;      break;
            case 13:    nNewValue = 15;      break;
        }
        if(nNewValue>0)
            ipResult = ItemPropertyMassiveCritical(nNewValue);
    }
    else if(nIpType == ITEM_PROPERTY_DAMAGE_BONUS)
    {
        switch(nCostTableValue)
        {   //2-4-6-8-10
            case 2: nNewValue = 4;      break;
            case 4: nNewValue = 16;     break;
            case 16: nNewValue = 18;    break;
            case 18: nNewValue = 20;    break;

            //2d4-2d6-2d8-2d10-2d12
            case 12:    nNewValue = 10;      break;
            case 10:    nNewValue = 11;      break;
            case 11:    nNewValue = 13;      break;
            case 13:    nNewValue = 15;      break;
        }
        if(nNewValue>0)
            ipResult = ItemPropertyDamageBonus(nIpSubType, nNewValue);
    }
    else if(nIpType == ITEM_PROPERTY_DAMAGE_REDUCTION)
    {
        nRandom = Random(2);//Value or Subtype?
        if(nRandom)
        {
            if(nCostTableValue<3)
            {
                nCostTableValue +=1;
                ipResult = ItemPropertyDamageReduction(nIpSubType, nCostTableValue);
            }
        }
        else
        {
            if(nIpSubType<6)
            {
                nIpSubType +=1;
                ipResult = ItemPropertyDamageReduction(nIpSubType, nCostTableValue);
            }
        }
    }

    else
    {
        if(nIpType == ITEM_PROPERTY_SKILL_BONUS)
            nMaxValue = 12;
        else if (nIpType == ITEM_PROPERTY_MIGHTY)
            nMaxValue = 8;
        else if ((nIpType == ITEM_PROPERTY_IMMUNITY_DAMAGE_TYPE) || (nIpType == ITEM_PROPERTY_DAMAGE_RESISTANCE))
            nMaxValue = 3;
        else
            nMaxValue = 5;

        if(nCostTableValue < nMaxValue)
        {
            nCostTableValue +=1;
            ipResult = ItemProperty(nIpType, nCostTableValue, nIpSubType);
        }
    }

return ipResult;
}




// v2.0
void DelPropParams(object oItem, int nID)
{
    string sID = IntToString(nID);
    DeleteLocalInt(oItem, "Prop_"+sID+"_Type");
    DeleteLocalInt(oItem, "Prop_"+sID+"_SubType");
    DeleteLocalInt(oItem, "Prop_"+sID+"_Value");
    DeleteLocalInt(oItem, "Prop_"+sID+"_Added");
}


// v2.0
void MovePropertyTo(object oItem, int nOldID, int nNewID)
{
    int nIpType, nIpSubType, nIpValue, nAdded;
    string sOldID = IntToString(nOldID);
    string sNewID = IntToString(nNewID);

    //Get prop parameters
    nIpType = GetLocalInt(oItem, "Prop_"+sOldID+"_Type");
    nIpSubType = GetLocalInt(oItem, "Prop_"+sOldID+"_SubType");
    nIpValue = GetLocalInt(oItem, "Prop_"+sOldID+"_Value");
    nAdded = GetLocalInt(oItem, "Prop_"+sOldID+"_Added");
    //Save prop param with new ID
    SetLocalInt(oItem, "Prop_"+sNewID+"_Type", nIpType);
    SetLocalInt(oItem, "Prop_"+sNewID+"_SubType", nIpSubType);
    SetLocalInt(oItem, "Prop_"+sNewID+"_Value", nIpValue);
    SetLocalInt(oItem, "Prop_"+sNewID+"_Added", nAdded);

    //Del prop param with old ID
    DelPropParams(oItem, nOldID);
}



// v2.0
void MovePropertyFromDynamicListToStatic(object oItem, int nID)
{
    int nIpType, nIpSubType, nIpValue, nAdded;
    int nMaxProps = GetLocalInt(oItem, "nMaxStatProps");
    if(!nMaxProps)
        nMaxProps = 100;//Static props would have ID started from 101.

    //Part 1 //Move prop nID to stat list
    nMaxProps++;
    MovePropertyTo(oItem, nID, nMaxProps);
    SetLocalInt(oItem, "nMaxStatProps", nMaxProps);

    //Part 2 //Arrange dyn list
    nMaxProps = GetLocalInt(oItem, "nMaxDynProps");
    if(nMaxProps == nID)//The removed prop was the last in dyn list
        DelPropParams(oItem, nID);
    else//The removed prop was not the last in dyn list
        MovePropertyTo(oItem, nMaxProps, nID);
    nMaxProps--;

    if(nMaxProps<=0)
        DeleteLocalInt(oItem, "nRemainLvlUps");
    else
        SetLocalInt(oItem, "nMaxDynProps", nMaxProps);
}



int TestItemAgainstPC(object oItem, object oPC, itemproperty ip)
{                                                                               //DBM("sl_s_slw_inc", "TestItemAgainstPC", "START with oItem" + OToS(oItem));
                                                                                //DBM("sl_s_slw_inc", "TestItemAgainstPC", "START with oPC" + OToS(oPC));
    int nPcLvl = GetHitDice(oPC);                                               //DBM("sl_s_slw_inc", "TestItemAgainstPC", "nPcLvl" + IToS(nPcLvl));
    object oTemp = GetObjectByTag("sl_cont_temp");
    object oTestItem = CopyItem(oItem, oTemp, TRUE);                            //DBM("sl_s_slw_inc", "TestItemAgainstPC", "START with oItem" + OToS(oItem));
    SetIdentified(oTestItem, TRUE);
    IPSafeAddItemProperty(oTestItem, ip);

    int nItemLvl = getItemLevel_New(oTestItem);                                 //DBM("sl_s_slw_inc", "TestItemAgainstPC", "nItemRestrictLvl" + IToS(nItemLvl));
    DestroyObject(oTestItem, 0.1);

    if(nItemLvl<=nPcLvl)
        return TRUE;
return FALSE;
}



void LevelUpItem(object oItem, int nShowMessages = TRUE)
{                                                                               //DBM("sl_s_slw_inc", "LevelUpItem", "nShowMessages" + IToS(nShowMessages));
    int nIpType, nIpSubType, nIpValue, nFailCount;
    itemproperty ip;
    object oPC = GetItemPossessor(oItem);
    if(!GetIsObjectValid(oPC))
        oPC = GetNearestCreature(CREATURE_TYPE_PLAYER_CHAR, PLAYER_CHAR_IS_PC, oItem);
                                                                                //DBM("sl_s_slw_inc", "LevelUpItem", "oPC" + OToS(oPC));
    int nItemLvl = GetLocalInt(oItem, "nItemLvl");                              //DBM("sl_s_slw_inc", "LevelUpItem", "Item Level" + IToS(nItemLvl));
    int nRemainLvlUps = GetLocalInt(oItem, "nRemainLvlUps");                    //DBM("sl_s_slw_inc", "LevelUpItem", "Remain LvlUps" + IToS(nRemainLvlUps));

    //bZ 24.09.2014
    int nNonSLWProps = GetLocalInt(oItem, "NonSLWProps");//Check for NonSLW-System props presence
                                                                                //DBM("sl_s_slw_inc", "LevelUpItem", "nNonSLWProps" + IToS(nNonSLWProps));
    if(!nShowMessages && (nNonSLWProps>0))//only on first aqcuire
    {                                                                           //DBM("sl_s_slw_inc", "LevelUpItem", "!nShowMessages");
        nNonSLWProps--;
        SetLocalInt(oItem, "NonSLWProps", nNonSLWProps);
    }//End 24.09.2014

    else if (nRemainLvlUps != 0)
    {
        DeleteLocalInt(oItem, "NonSLWProps");//clearing trash

        int nMaxProps = GetLocalInt(oItem, "nMaxDynProps");                     //DBM("sl_s_slw_inc", "LevelUpItem", "nMaxDynProps" + IToS(nMaxProps));
        int nPropNumber = 1+Random(nMaxProps);                                  //DBM("sl_s_slw_inc", "LevelUpItem", "nPropNumber" + IToS(nPropNumber));
        string sID = IntToString(nPropNumber);

        nIpType = GetLocalInt(oItem, "Prop_"+sID+"_Type");                      //DBM("sl_s_slw_inc", "LevelUpItem", "nIpType" + IToS(nIpType));
        nIpSubType = GetLocalInt(oItem, "Prop_"+sID+"_SubType");                //DBM("sl_s_slw_inc", "LevelUpItem", "nIpSubType" + IToS(nIpSubType));
        nIpValue = GetLocalInt(oItem, "Prop_"+sID+"_Value");                    //DBM("sl_s_slw_inc", "LevelUpItem", "nIpValue" + IToS(nIpValue));

        if(!GetLocalInt(oItem, "Prop_"+sID+"_Added"))//first time
        {                                                                       //DBM("sl_s_slw_inc", "LevelUpItem", "Added == FALSE");
            //Add ip without upgrading
            ip = ItemProperty(nIpType, nIpValue, nIpSubType);
            SetLocalInt(oItem, "Prop_"+sID+"_Added", TRUE);
        }
        else  //Uprade ip and add
            ip = UpgradeItemProperty(nIpType, nIpValue, nIpSubType);

        if(GetIsItemPropertyValid(ip))
        {                                                                       //DBM("sl_s_slw_inc", "LevelUpItem", "ip is valid");
            if(TestItemAgainstPC(oItem, oPC, ip))
            {                                                                   //DBM("sl_s_slw_inc", "LevelUpItem", "TestItemAgainstPC - OK");
                if(nIpType == ITEM_PROPERTY_DAMAGE_REDUCTION)//22
                    IPSafeAddItemProperty(oItem, ip, 0.0, X2_IP_ADDPROP_POLICY_REPLACE_EXISTING, FALSE, TRUE);//to ignore subtype!
                else
                    IPSafeAddItemProperty(oItem, ip);

                nItemLvl++;                                                     //DBM("sl_s_slw_inc", "LevelUpItem", "nItemLvl++" + IToS(nItemLvl));
                nRemainLvlUps--;                                                //DBM("sl_s_slw_inc", "LevelUpItem", "nRemainLvlUps--" + IToS(nRemainLvlUps));
                SetLocalInt(oItem, "nItemLvl", nItemLvl);
                SetLocalInt(oItem, "nRemainLvlUps", nRemainLvlUps);

                nIpType = GetItemPropertyType(ip);                              //DBM("sl_s_slw_inc", "LevelUpItem", "nIpType after upg" + IToS(nIpType));
                nIpSubType = GetItemPropertySubType(ip);                        //DBM("sl_s_slw_inc", "LevelUpItem", "nIpSubType after upg" + IToS(nIpSubType));
                nIpValue = GetItemPropertyCostTableValue(ip);                   //DBM("sl_s_slw_inc", "LevelUpItem", "nIpValue after upg" + IToS(nIpValue));

                SetLocalInt(oItem, "Prop_"+sID+"_Type", nIpType);
                SetLocalInt(oItem, "Prop_"+sID+"_SubType", nIpSubType);
                SetLocalInt(oItem, "Prop_"+sID+"_Value", nIpValue);

                DeleteLocalInt(oItem, "SLW_FailCount");
                if(nShowMessages)
                    FloatingTextStringOnCreature("Ваше снаряжение улучшилось!", oPC, FALSE);
                LevelUpItemIfNecessary(oItem, nShowMessages);
            }
            else
            {
                nFailCount = GetLocalInt(oItem, "SLW_FailCount");
                if(nFailCount<4)//Several times try to select other props
                {
                    nFailCount++;
                    SetLocalInt(oItem, "SLW_FailCount", nFailCount);
                    LevelUpItem(oItem, nShowMessages);
                }
                else
                {
                    DeleteLocalInt(oItem, "SLW_FailCount");
                    if(nShowMessages)
                        FloatingTextStringOnCreature("Ваше снаряжение улучшится, когда вы будете достаточно опытны чтобы им пользоваться!", oPC, FALSE);
                    SetLocalInt(oItem, "AlreadyHasLevelUp", GetHitDice(oPC));//for comfort this variable contains not simply TRUE/FALSE, but the PC level, when the check was done last time
                }
            }

        }
        else
        {
            MovePropertyFromDynamicListToStatic(oItem, nPropNumber);
            DelayCommand(0.2, LevelUpItem(oItem, nShowMessages));
        }
    }
}


// v2.0
void LevelUpItemIfNecessary(object oItem, int nShowMessages = TRUE)
{                                                                               //DBM("sl_s_slw_inc", "LevelUpItemIfNecessary", "Begin with oItem" + OToS(oItem));
                                                                                //DBM("sl_s_slw_inc", "LevelUpItemIfNecessary", "Begin with nShowMessages" + IToS(nShowMessages));
    int nAlreadyHasLevelUp = GetLocalInt(oItem, "AlreadyHasLevelUp");           //DBM("sl_s_slw_inc", "LevelUpItemIfNecessary", "nAlreadyHasLevelUp" + IToS(nAlreadyHasLevelUp));
    object oPC = GetItemPossessor(oItem);
    if(!GetIsObjectValid(oPC))
        oPC = GetNearestCreature(CREATURE_TYPE_PLAYER_CHAR, PLAYER_CHAR_IS_PC, oItem);
                                                                                //DBM("sl_s_slw_inc", "LevelUpItemIfNecessary", "oPC" + OToS(oPC));
    if(GetHitDice(oPC) != nAlreadyHasLevelUp)
    {
        nAlreadyHasLevelUp = FALSE;
        DeleteLocalInt(oItem, "AlreadyHasLevelUp");
    }
    int nItemLvl = GetItemPseudoLevel(oItem);                                   //DBM("sl_s_slw_inc", "LevelUpItemIfNecessary", "nItemLvl" + IToS(nItemLvl));
    int nItemExp = GetItemExp(oItem);                                           //DBM("sl_s_slw_inc", "LevelUpItemIfNecessary", "nItemExp" + IToS(nItemExp));

    int nNextLvlExp = ItemLevelToItemExp(nItemLvl+1);                           //DBM("sl_s_slw_inc", "LevelUpItemIfNecessary", "nNextLvlExp" + IToS(nNextLvlExp));
    if ((nItemExp >= nNextLvlExp) && !nAlreadyHasLevelUp)
        LevelUpItem(oItem, nShowMessages);

return;
}
*/


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
//                                                                      //
//                  FUNCTIONS FOR CREATION ITEMS                        //
//                                                                      //
//////////////////////////////////////////////////////////////////////////



int GetIPGroup(object oItem)
{
    int nResult;
    int nBaseItemType = GetBaseItemType(oItem);

    switch(nBaseItemType)
    {
        case BASE_ITEM_AMULET:          nResult = IP_GROUP_AMULET;      break;
        case BASE_ITEM_ARMOR:           nResult = IP_GROUP_ARMOR;       break;
        case BASE_ITEM_BOOTS:           nResult = IP_GROUP_BOOTS;       break;
        case BASE_ITEM_CLOAK:           nResult = IP_GROUP_CLOAK;       break;
        case BASE_ITEM_HELMET:          nResult = IP_GROUP_HELM;        break;
        case BASE_ITEM_RING:            nResult = IP_GROUP_RINGS;       break;
        case BASE_ITEM_BELT:            nResult = IP_GROUP_BELTS;       break;
        case BASE_ITEM_BRACER:          nResult = IP_GROUP_BRACERS;     break;
        case BASE_ITEM_GLOVES:          nResult = IP_GROUP_GLOVES;      break;

        case BASE_ITEM_SMALLSHIELD:
        case BASE_ITEM_LARGESHIELD:
        case BASE_ITEM_TOWERSHIELD:     nResult = IP_GROUP_SHIELDS;       break;

        case BASE_ITEM_HEAVYCROSSBOW:
        case BASE_ITEM_LIGHTCROSSBOW:
        case BASE_ITEM_LONGBOW:
        case BASE_ITEM_SHORTBOW:        nResult = IP_GROUP_RANGED_WEAPON; break;
    }

    if (!nResult)
        nResult = IP_GROUP_MELEE_WEAPON;
                                                                                //DBM("sl_s_slw_inc", "GetIPGroup", "nResult" + IToS(nResult));
return nResult;
}
//------------------------------------------------------------------------------
/* OLD
int GetItemHasAttackBonus(object oItem, itemproperty ip)
{
    int nipType = GetItemPropertyType(ip);
    if ((nipType == ITEM_PROPERTY_ATTACK_BONUS) || (nipType == ITEM_PROPERTY_ENHANCEMENT_BONUS))
    {
        //if (IPGetItemHasProperty(oItem, ItemPropertyEnhancementBonus(1), -1))
        if(!GetLocalInt(oItem, "HasAttackBonus"))
        {
            SetLocalInt(oItem, "HasAttackBonus", TRUE);
            return FALSE;
        }
        else
            return TRUE;
    }
return FALSE;
}
//------------------------------------------------------------------------------
int GetMaxOfPropsOfType(int nPropType)
{                                                                               //DBM("sl_s_slw_inc", "GetMaxOfPropsOfType", "Start with nPropType" + IToS(nPropType));
    int nMax;
    switch (nPropType)
    {
        case ITEM_PROPERTY_IMMUNITY_DAMAGE_TYPE:
        case ITEM_PROPERTY_DAMAGE_BONUS:                    nMax = 2;   break;

        case ITEM_PROPERTY_CAST_SPELL:
        case ITEM_PROPERTY_BONUS_SPELL_SLOT_OF_LEVEL_N:     nMax = 3;   break;

        case ITEM_PROPERTY_ABILITY_BONUS:                   nMax = 4;   break;
        case ITEM_PROPERTY_SKILL_BONUS:                     nMax = 10;  break;
    }
    if (!nMax)
        nMax = 1;
                                                                                //DBM("sl_s_slw_inc", "GetMaxOfPropsOfType", "Result nMax" + IToS(nMax));
return nMax;
}
//------------------------------------------------------------------------------
void DelVarsForCountOfSpecProp(object oItem)
{
    int nPropType;

    itemproperty ip = GetFirstItemProperty(oItem);
    while (GetIsItemPropertyValid(ip))
    {
        nPropType = GetItemPropertyType(ip);
        DeleteLocalInt(oItem, ("CounterOfSpecialProperty_"+ IntToString(nPropType)));
        ip = GetNextItemProperty(oItem);
    }
return;
}
*/









//------------------------------------------------------------------------------
itemproperty RandomAbilityBonus()
{
    itemproperty ipResult;
    int nRandom = Random(6);                                                    //DBM("sl_s_slw_inc", "RandomAbilityBonus", "nRandom" + IToS(nRandom));

    ipResult = ItemProperty(ITEM_PROPERTY_ABILITY_BONUS, 1, nRandom);

return ipResult;
}
//------------------------------------------------------------------------------
itemproperty RandomSkillBonus(int nIpGroup, int nValue = FALSE)
{
    itemproperty ipResult;
    int nSubType;
    int nRandom;
    int nSkillValue = nValue;


    if (nIpGroup == IP_GROUP_MELEE_WEAPON)
    {
        nRandom = Random(9);                                                    //DBM("sl_s_slw_inc", "RandomSkillBonus", "IP_GROUP_MELEE_WEAPON, nRandom = " + IToS(nRandom));
        switch (nRandom)
        {
            case 0:     nSubType = SKILL_DISCIPLINE;    break;
            case 1:     nSubType = SKILL_HEAL;          break;
            case 2:     nSubType = SKILL_PARRY;         break;
            case 3:     nSubType = SKILL_TAUNT;         break;
            case 4:     nSubType = SKILL_INTIMIDATE;    break;
            case 5:     nSubType = SKILL_BLUFF;         break;
            case 6:     nSubType = SKILL_PERSUADE;      break;
            case 7:     nSubType = SKILL_DISABLE_TRAP;  break;
            case 8:     nSubType = SKILL_CONCENTRATION; break;
        }
    }

    else if (nIpGroup == IP_GROUP_RANGED_WEAPON)
    {
        nRandom = Random(8);                                                    //DBM("sl_s_slw_inc", "RandomSkillBonus", "IP_GROUP_RANGED_WEAPON, nRandom = " + IToS(nRandom));
        switch (nRandom)
        {
            case 0:     nSubType = SKILL_DISCIPLINE;        break;
            case 1:     nSubType = SKILL_HEAL;              break;
            case 2:     nSubType = SKILL_HIDE;              break;
            case 3:     nSubType = SKILL_MOVE_SILENTLY;     break;
            case 4:     nSubType = SKILL_PERFORM;           break;
            case 5:     nSubType = SKILL_LISTEN;            break;
            case 6:     nSubType = SKILL_SPOT;              break;
            case 7:     nSubType = SKILL_ANIMAL_EMPATHY;    break;
        }
    }

    else if ((nIpGroup == IP_GROUP_ARMOR)      ||
             (nIpGroup == IP_GROUP_AMULET)     ||
             (nIpGroup == IP_GROUP_BELTS)      ||
             (nIpGroup == IP_GROUP_BRACERS))
    {
        nSubType = Random(27);                                                  //DBM("sl_s_slw_inc", "RandomSkillBonus", "ARMOR, AMULET, BELTS; nSubType = " + IToS(nSubType));
    }

    else if (nIpGroup == IP_GROUP_HELM)
    {
        nRandom = Random(11);                                                   //DBM("sl_s_slw_inc", "RandomSkillBonus", "IP_GROUP_HELM; nRandom = " + IToS(nRandom));
        switch (nRandom)
        {
            case 0:     nSubType = SKILL_DISCIPLINE;        break;
            case 1:     nSubType = SKILL_HEAL;              break;
            case 2:     nSubType = SKILL_SPOT;              break;
            case 3:     nSubType = SKILL_LISTEN;            break;
            case 4:     nSubType = SKILL_LORE;              break;
            case 5:     nSubType = SKILL_SEARCH;            break;
            case 6:     nSubType = SKILL_USE_MAGIC_DEVICE;  break;
            case 7:     nSubType = SKILL_ANIMAL_EMPATHY;    break;
            case 8:     nSubType = SKILL_PERSUADE;          break;
            case 9:     nSubType = SKILL_SPELLCRAFT;        break;
            case 10:    nSubType = SKILL_CONCENTRATION;     break;
        }
    }

    else if ((nIpGroup == IP_GROUP_CLOAK)      ||
             (nIpGroup == IP_GROUP_BOOTS))
    {
        nRandom = Random(9);                                                    //DBM("sl_s_slw_inc", "RandomSkillBonus", "CLOAK, BOOTS; nRandom = " + IToS(nRandom));
        switch (nRandom)
        {
            case 0:     nSubType = SKILL_DISCIPLINE;        break;
            case 1:     nSubType = SKILL_HEAL;              break;
            case 2:     nSubType = SKILL_USE_MAGIC_DEVICE;  break;
            case 3:     nSubType = SKILL_ANIMAL_EMPATHY;    break;
            case 4:     nSubType = SKILL_CONCENTRATION;     break;
            case 5:     nSubType = SKILL_PERFORM;           break;
            case 6:     nSubType = SKILL_TUMBLE;            break;
            case 7:     nSubType = SKILL_MOVE_SILENTLY;     break;
            case 8:     nSubType = SKILL_HIDE;              break;
        }
    }

    else //if ((nIpGroup == IP_GROUP_RINGS)  ||
         //    (nIpGroup == IP_GROUP_GLOVES))
    {
        nRandom = Random(16);                                                   //DBM("sl_s_slw_inc", "RandomSkillBonus", "RINGS, GLOVES; nRandom = " + IToS(nRandom));
        switch (nRandom)
        {
            case 0:     nSubType = SKILL_DISCIPLINE;        break;
            case 1:     nSubType = SKILL_HEAL;              break;
            case 2:     nSubType = SKILL_USE_MAGIC_DEVICE;  break;
            case 3:     nSubType = SKILL_CONCENTRATION;     break;
            case 4:     nSubType = SKILL_CRAFT_ARMOR;       break;
            case 5:     nSubType = SKILL_CRAFT_TRAP;        break;
            case 6:     nSubType = SKILL_CRAFT_WEAPON;      break;
            case 7:     nSubType = SKILL_DISABLE_TRAP;      break;
            case 8:     nSubType = SKILL_SET_TRAP;          break;
            case 9:     nSubType = SKILL_PARRY;             break;
            case 10:    nSubType = SKILL_OPEN_LOCK;         break;
            case 11:    nSubType = SKILL_PICK_POCKET;       break;
            case 12:    nSubType = SKILL_ANIMAL_EMPATHY;    break;
            case 13:    nSubType = SKILL_LORE;              break;
            case 14:    nSubType = SKILL_SEARCH;            break;
            case 15:    nSubType = SKILL_SPELLCRAFT;        break;
        }
    }

    /* OLD
    if (!nValue)
    {
        nRandom = Random(2);
        nSkillValue = nRandom+1;                                                //DBM("sl_s_slw_inc", "RandomSkillBonus", "nSkillValue" + IToS(nSkillValue));
    }*/

    ipResult = ItemProperty(ITEM_PROPERTY_SKILL_BONUS, 1, nSubType);

return ipResult;
}
//------------------------------------------------------------------------------
itemproperty RandomDamageBonus()
{
    itemproperty ipResult;
    int nSubType, nValue;

    int nRandom = Random(12);                                                   //DBM("sl_s_slw_inc", "RandomDamageBonus", "nRandom" + IToS(nRandom));
    switch (nRandom)
    {
        case 0:     nSubType = DAMAGE_TYPE_BLUDGEONING;     break;
        case 1:     nSubType = DAMAGE_TYPE_PIERCING;        break;
        case 2:     nSubType = DAMAGE_TYPE_SLASHING;        break;
        case 3:     nSubType = DAMAGE_TYPE_MAGICAL;         break;
        case 4:     nSubType = DAMAGE_TYPE_ACID;            break;
        case 5:     nSubType = DAMAGE_TYPE_COLD;            break;
        case 6:     nSubType = DAMAGE_TYPE_DIVINE;          break;
        case 7:     nSubType = DAMAGE_TYPE_ELECTRICAL;      break;
        case 8:     nSubType = DAMAGE_TYPE_FIRE;            break;
        case 9:     nSubType = DAMAGE_TYPE_NEGATIVE;        break;
        case 10:    nSubType = DAMAGE_TYPE_POSITIVE;        break;
        case 11:    nSubType = DAMAGE_TYPE_SONIC;           break;
    }
    /*  Old variant
    nRandom = Random(3);
    if(!nRandom)
        nValue = IP_CONST_DAMAGEBONUS_2d4; //12
    else
        nValue = IP_CONST_DAMAGEBONUS_2; //2
    ipResult = ItemProperty(ITEM_PROPERTY_DAMAGE_BONUS, nValue, nRandom);
    */

    ipResult = ItemProperty(ITEM_PROPERTY_DAMAGE_BONUS, IP_CONST_DAMAGEBONUS_2, nSubType);

return ipResult;
}
//------------------------------------------------------------------------------
itemproperty RandomFeatBonus(int nIpGroup)
{
    itemproperty ipResult;
    int nFeat;
    int nRandom;

    if (nIpGroup == IP_GROUP_MELEE_WEAPON)
    {
        nRandom = Random(5);                                                    //DBM("sl_s_slw_inc", "RandomFeatBonus", "MELEE_WEAPON; nRandom = " + IToS(nRandom));
        switch (nRandom)
        {
            case 0:     nFeat = IP_CONST_FEAT_POWERATTACK;  break;
            case 1:     nFeat = IP_CONST_FEAT_DISARM;       break;
            case 2:     nFeat = IP_CONST_FEAT_CLEAVE;       break;
            case 3:     nFeat = IP_CONST_FEAT_KNOCKDOWN;    break;
            case 4:     nFeat = IP_CONST_FEAT_WHIRLWIND;    break;
        }
    }

    else if ((nIpGroup == IP_GROUP_GLOVES) || (nIpGroup == IP_GROUP_BRACERS))
    {
        nRandom = Random(2);                                                    //DBM("sl_s_slw_inc", "RandomFeatBonus", "GLOVES; nRandom = " + IToS(nRandom));
        switch (nRandom)
        {
            case 0:     nFeat = IP_CONST_FEAT_AMBIDEXTROUS;             break;
            case 1:     nFeat = IP_CONST_FEAT_TWO_WEAPON_FIGHTING;      break;
        }
    }

    else if (nIpGroup == IP_GROUP_BOOTS)
    {
        nRandom = Random(2);                                                    //DBM("sl_s_slw_inc", "RandomFeatBonus", "BOOTS; nRandom = " + IToS(nRandom));
        switch (nRandom)
        {
            case 0:     nFeat = IP_CONST_FEAT_DODGE;        break;
            case 1:     nFeat = IP_CONST_FEAT_MOBILITY;     break;
        }
    }

    else
        nFeat = -1;

                                                                                //DBM("sl_s_slw_inc", "RandomFeatBonus", "nFeat = " + IToS(nFeat));
    ipResult = ItemPropertyBonusFeat(nFeat);

return ipResult;
}
//------------------------------------------------------------------------------
itemproperty RandomSpellBonus(int nDefensiveSpells = FALSE)
{
    itemproperty ipResult;
    int nSpell;
    int nRandom = Random(20);                                                   //DBM("sl_s_slw_inc", "RandomSpellBonus", "nRandom" + IToS(nRandom));

    nRandom = nRandom + 10 * nDefensiveSpells;
    switch (nRandom)
    {
        //ofensive spells
        case 0:     nSpell = IP_CONST_CASTSPELL_TRUE_STRIKE_5;          break;
        case 1:     nSpell = IP_CONST_CASTSPELL_FEAR_5;                 break;
        case 2:     nSpell = IP_CONST_CASTSPELL_FIND_TRAPS_3;           break;
        case 3:     nSpell = IP_CONST_CASTSPELL_WEB_3;                  break;
        case 4:     nSpell = IP_CONST_CASTSPELL_VAMPIRIC_TOUCH_5;       break;
        case 5:     nSpell = IP_CONST_CASTSPELL_PHANTASMAL_KILLER_7;    break;
        case 6:     nSpell = IP_CONST_CASTSPELL_PRISMATIC_SPRAY_13;     break;
        case 7:     nSpell = IP_CONST_CASTSPELL_CONE_OF_COLD_15;        break;
        case 8:     nSpell = IP_CONST_CASTSPELL_FIREBALL_10;            break;
        case 9:     nSpell = IP_CONST_CASTSPELL_FLAME_ARROW_18;         break;

        case 10:    nSpell = IP_CONST_CASTSPELL_BALAGARNSIRONHORN_7;    break;
        case 11:    nSpell = IP_CONST_CASTSPELL_DARKNESS_3;             break;
        case 12:    nSpell = IP_CONST_CASTSPELL_ELECTRIC_JOLT_1;        break;
        case 13:    nSpell = IP_CONST_CASTSPELL_ENTANGLE_5;             break;
        case 14:    nSpell = IP_CONST_CASTSPELL_SOUND_BURST_3;          break;
        case 15:    nSpell = IP_CONST_CASTSPELL_SLOW_5;                 break;
        case 16:    nSpell = IP_CONST_CASTSPELL_SLEEP_5;                break;
        case 17:    nSpell = IP_CONST_CASTSPELL_SILENCE_3;              break;
        case 18:    nSpell = IP_CONST_CASTSPELL_SEE_INVISIBILITY_3;     break;
        case 19:    nSpell = IP_CONST_CASTSPELL_POISON_5;               break;


        //defensive spells
        case 20:    nSpell = IP_CONST_CASTSPELL_AID_3;                  break;
        case 21:    nSpell = IP_CONST_CASTSPELL_HASTE_10;               break;
        case 22:    nSpell = IP_CONST_CASTSPELL_BLESS_2;                break;
        case 23:    nSpell = IP_CONST_CASTSPELL_BULLS_STRENGTH_3;       break;
        case 24:    nSpell = IP_CONST_CASTSPELL_CAMOFLAGE_5;            break;
        case 25:    nSpell = IP_CONST_CASTSPELL_CATS_GRACE_3;           break;
        case 26:    nSpell = IP_CONST_CASTSPELL_CLARITY_3;              break;
        case 27:    nSpell = IP_CONST_CASTSPELL_HEAL_11;                break;
        case 28:    nSpell = IP_CONST_CASTSPELL_DEATH_WARD_7;           break;
        case 29:    nSpell = IP_CONST_CASTSPELL_REGENERATE_13;          break;

        case 30:    nSpell = IP_CONST_CASTSPELL_EAGLE_SPLEDOR_3;        break;
        case 31:    nSpell = IP_CONST_CASTSPELL_ELEMENTAL_SHIELD_12;    break;
        case 32:    nSpell = IP_CONST_CASTSPELL_ENDURANCE_3;            break;
        case 33:    nSpell = IP_CONST_CASTSPELL_ETHEREAL_VISAGE_9;      break;
        case 34:    nSpell = IP_CONST_CASTSPELL_INVISIBILITY_3;         break;
        case 35:    nSpell = IP_CONST_CASTSPELL_EXPEDITIOUS_RETREAT_5;  break;
        case 36:    nSpell = IP_CONST_CASTSPELL_FOXS_CUNNING_3;         break;
        case 37:    nSpell = IP_CONST_CASTSPELL_FREEDOM_OF_MOVEMENT_7;  break;
        case 38:    nSpell = IP_CONST_CASTSPELL_GHOSTLY_VISAGE_3;       break;
        case 39:    nSpell = IP_CONST_CASTSPELL_OWLS_WISDOM_3;          break;
    }

    nRandom = 8+Random(3); // 1, 2 or 3 uses per day
    ipResult = ItemPropertyCastSpell(nSpell, nRandom);

return ipResult;
}
//------------------------------------------------------------------------------
itemproperty RandomAmmo(int nGrade)
{
    itemproperty ipResult;
    // Даже если выпала рандомом эта функция, еще не факт что она вернет валидное свойство
    // Чем выше грэйд, тем ниже вероятность
    int nRandom = Random(1+nGrade); // Будет свойство создано или нет? 0 - да
    if(!nRandom)
    {
        nRandom = Random(5); // Выбор типа стрелы, варианты значений: 2, 3, 4 - 1d6 элементами; 15 - стрела +5
        if(nRandom<2)// 0 нет вообще свойства, 1 - хрень, заменяем на +5
            nRandom = 15;
        ipResult = ItemPropertyUnlimitedAmmo(nRandom);
    }
return ipResult;
}
//------------------------------------------------------------------------------
itemproperty RandomSavingThrow()
{
    itemproperty ipResult;
    int nSaveType;
    int i = Random(2);
    if (!i)
    {
        nSaveType = (1+Random(3));
        ipResult = ItemPropertyBonusSavingThrow(nSaveType, 1);
    }

    else
    {
        nSaveType = Random(20);
        if (nSaveType>15)
            nSaveType = 0;

        ipResult = ItemPropertyBonusSavingThrowVsX(nSaveType, 1);
    }

return ipResult;
}
//------------------------------------------------------------------------------
itemproperty RandomSpellSlot()
{
    itemproperty ip;
    int nClass;
    int nSpellLevel;

    int nRandom = Random(7);
    switch(nRandom)
    {
        case 0:     nClass = IP_CONST_CLASS_BARD;       break;
        case 1:     nClass = IP_CONST_CLASS_CLERIC;     break;
        case 2:     nClass = IP_CONST_CLASS_DRUID;      break;
        case 3:     nClass = IP_CONST_CLASS_PALADIN;    break;
        case 4:     nClass = IP_CONST_CLASS_RANGER;     break;
        case 5:     nClass = IP_CONST_CLASS_SORCERER;   break;
        case 6:     nClass = IP_CONST_CLASS_WIZARD;     break;
    }

    if ((nClass == IP_CONST_CLASS_PALADIN)  || (nClass == IP_CONST_CLASS_RANGER))
        nSpellLevel = (Random(4) + 1);

    else if(nClass = IP_CONST_CLASS_BARD)
        nSpellLevel = (Random(6) + 1);

    else
        nSpellLevel = (Random(9) + 1);

    ip = ItemPropertyBonusLevelSpell(nClass, nSpellLevel);

return ip;
}
//------------------------------------------------------------------------------
itemproperty RandomDamageResistance(int nIPGrade)
{
    itemproperty ipResult;
    int nHPResist;

    int nDamageType = Random(11);
    if(nDamageType>2)
        nDamageType+=3;

    ipResult = ItemPropertyDamageResistance(nDamageType, IP_CONST_DAMAGERESIST_5);

return ipResult;
}
//------------------------------------------------------------------------------
itemproperty RandomDamageImmunity()
{
    itemproperty ipResult;
    int nRandom;
    int nImmuneBonus;

    int nDamageType = Random(11);
    if (nDamageType>2)
        nDamageType = nDamageType+3;

    ipResult = ItemPropertyDamageImmunity(nDamageType, IP_CONST_DAMAGEIMMUNITY_5_PERCENT);

return ipResult;
}
//------------------------------------------------------------------------------
itemproperty RandomOnHitProps(int nIPGrade)
{
    itemproperty ipResult;
    int nRandom, nPropNum, nSubType, nSpecial, nSaveDC;
    switch(nIPGrade)
    {
        case 1: nPropNum = 7;   break;
        case 2: nPropNum = 16;  break;
        case 3: nPropNum = 19;  break;
    }

    nRandom = Random(nPropNum);                                                 //DBM("slw", "RandomOnHitProps", "Random (SubType)" + IToS(nRandom));
    switch(nRandom)
    {
        // Grade 1
        case 0:     nSubType = IP_CONST_ONHIT_SLEEP;            break;
        case 1:     nSubType = IP_CONST_ONHIT_CONFUSION;        break;
        case 2:     nSubType = IP_CONST_ONHIT_DAZE;             break;
        case 3:     nSubType = IP_CONST_ONHIT_KNOCK;            break;
        case 4:     nSubType = IP_CONST_ONHIT_LESSERDISPEL;     break;
        case 5:     nSubType = IP_CONST_ONHIT_DEAFNESS;         break;
        case 6:     nSubType = IP_CONST_ONHIT_WOUNDING;         break;

        // Grade 2
        case 7:     nSubType = IP_CONST_ONHIT_STUN;             break;
        case 8:     nSubType = IP_CONST_ONHIT_HOLD;             break;
        case 9:     nSubType = IP_CONST_ONHIT_DOOM;             break;
        case 10:    nSubType = IP_CONST_ONHIT_FEAR;             break;
        case 11:    nSubType = IP_CONST_ONHIT_SLOW;             break;
        case 12:    nSubType = IP_CONST_ONHIT_GREATERDISPEL;    break;
        case 13:    nSubType = IP_CONST_ONHIT_SILENCE;          break;
        case 14:    nSubType = IP_CONST_ONHIT_ITEMPOISON;       break;
        case 15:    nSubType = IP_CONST_ONHIT_DISEASE;          break;

        // Grade 3
        case 16:    nSubType = IP_CONST_ONHIT_BLINDNESS;        break;
        case 17:    nSubType = IP_CONST_ONHIT_LEVELDRAIN;       break;
        case 18:    nSubType = IP_CONST_ONHIT_ABILITYDRAIN;     break;
    }
                                                                                //DBM("slw", "RandomOnHitProps", "nSubType" + IToS(nSubType));
    if(nSubType == IP_CONST_ONHIT_ABILITYDRAIN || nSubType == IP_CONST_ONHIT_ITEMPOISON)
        nSpecial = Random(6);  // IP_CONST_ABILITY_  // IP_CONST_POISON_
    else if(nSubType == IP_CONST_ONHIT_DISEASE)
        nSpecial = Random(17); // DISEASE_
    else if(nSubType == IP_CONST_ONHIT_LEVELDRAIN)
        nSaveDC = 1; // Иначе свойство невалидно именно с этим сабтайпом
    else if(nSubType == IP_CONST_ONHIT_KNOCK || nSubType == IP_CONST_ONHIT_LESSERDISPEL || nSubType == IP_CONST_ONHIT_WOUNDING || nSubType == IP_CONST_ONHIT_GREATERDISPEL)
        nSpecial = 0;
    else
        nSpecial = IP_CONST_ONHIT_DURATION_25_PERCENT_3_ROUNDS;
                                                                                //DBM("slw", "RandomOnHitProps", "nSpecial" + IToS(nSpecial));
    ipResult = ItemPropertyOnHitProps(nSubType, nSaveDC, nSpecial);

return ipResult;
}
//------------------------------------------------------------------------------


















//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
itemproperty PropForMeleeWeapon(int nIPGrade)
{
    itemproperty ip;
    int nPropNum;

    switch(nIPGrade)
    {
        case 1: nPropNum = 7;       break;
        case 2: nPropNum = 9;       break;
        case 3: nPropNum = 10;      break;
    }

    int nRandomProp = Random(nPropNum);                                         //DBM("sl_s_slw_inc", "PropForMeleeWeapon", "nRandomProp" + IToS(nRandomProp));
    if (nRandomProp == 0)
        ip = RandomAbilityBonus();

    else if (nRandomProp == 1)
        ip = RandomSkillBonus(IP_GROUP_MELEE_WEAPON);

    else if (nRandomProp == 2)
        ip = ItemPropertyAttackBonus(1);

    else if (nRandomProp == 3)
        ip = ItemPropertyEnhancementBonus(1);

    else if (nRandomProp == 4)
        ip = RandomSpellBonus();

    else if (nRandomProp == 5)
        ip = RandomDamageBonus();

    else if(nRandomProp == 6)
        ip = RandomOnHitProps(nIPGrade);

    //2
    else if (nRandomProp == 7)
        ip = RandomFeatBonus(IP_GROUP_MELEE_WEAPON);

    else if (nRandomProp == 8)
        ip = ItemPropertyKeen();

    //3
    else if (nRandomProp == 9)
        ip = ItemPropertyVampiricRegeneration(1);


    //TEST
    if(!GetIsItemPropertyValid(ip))
        DBM("slw", "PropForMeleeWeapon", "RANDOM IP FAILED, nRandomProp" + IToS(nRandomProp));

return ip;
}
//------------------------------------------------------------------------------
itemproperty PropForRangedWeapon(int nIPGrade)
{
    itemproperty ip;
    int nPropNum;

    switch(nIPGrade)
    {
        case 1: nPropNum = 7;       break;
        case 2: nPropNum = 10;      break;
        case 3: nPropNum = 10;      break;
    }

    int nRandomProp = Random(nPropNum);                                         //DBM("sl_s_slw_inc", "PropForRangedWeapon", "nRandomProp" + IToS(nRandomProp));
    if (nRandomProp == 0)
        ip = RandomAbilityBonus();

    else if (nRandomProp == 1)
        ip = RandomSkillBonus(IP_GROUP_RANGED_WEAPON);

    else if (nRandomProp == 2)
        ip = ItemPropertyAttackBonus(1);

    else if (nRandomProp == 3)
        ip = ItemPropertyMaxRangeStrengthMod(1);

    else if (nRandomProp == 4)
        ip = RandomSpellBonus();

    else if (nRandomProp == 5)
        ip = RandomSavingThrow();

    else if (nRandomProp == 6)
        ip = ItemPropertyRegeneration(1);


    //2
    else if (nRandomProp == 7)
        ip = ItemPropertyMassiveCritical(IP_CONST_DAMAGEBONUS_2d4);

    else if (nRandomProp == 8)
        ip = RandomAmmo(nIPGrade);

    else if (nRandomProp == 9)
        ip = ItemPropertyExtraRangeDamageType(IP_CONST_DAMAGETYPE_BLUDGEONING);





    //TEST
    if(!GetIsItemPropertyValid(ip))
        DBM("slw", "PropForRangedWeapon", "RANDOM IP FAILED, nRandomProp" + IToS(nRandomProp));


return ip;
}
//------------------------------------------------------------------------------
itemproperty PropForClothes(int nIPGrade, int nIpGroup)
{
    itemproperty ip;
    int nPropNum;

    switch(nIPGrade)
    {
        case 1: nPropNum = 7;       break;
        case 2: nPropNum = 10;      break;
        case 3: nPropNum = 12;      break;
    }


    int nRandomProp = Random(nPropNum);                                         //DBM("sl_s_slw_inc", "PropForClothes", "nRandomProp" + IToS(nRandomProp));
    if (nRandomProp == 0)
        ip = RandomAbilityBonus();

    else if (nRandomProp == 1)
        ip = RandomSkillBonus(nIpGroup);

    else if (nRandomProp == 2)
        ip = RandomSavingThrow();

    else if (nRandomProp == 3)
        ip = RandomSpellBonus(TRUE);

    else if (nRandomProp == 4)
        ip = ItemPropertyRegeneration(1);

    else if (nRandomProp == 5)
        ip = ItemPropertyACBonus(1);

    else if (nRandomProp == 6)
        ip = ItemPropertyDamageReduction(IP_CONST_DAMAGEREDUCTION_1, IP_CONST_DAMAGESOAK_5_HP);

    //2
    else if (nRandomProp == 7)
        ip = RandomFeatBonus(nIpGroup);

    else if (nRandomProp == 8)
        ip = RandomDamageResistance(nIPGrade);

    else if (nRandomProp == 9)
        ip = RandomSpellSlot();

    //3
    else if (nRandomProp == 10)
        ip = RandomDamageImmunity();

    else if (nRandomProp == 11)
        ip = ItemPropertyBonusSpellResistance(IP_CONST_SPELLRESISTANCEBONUS_16);


    //TEST
    if(!GetIsItemPropertyValid(ip))
        DBM("slw", "PropForClothes", "RANDOM IP FAILED, nRandomProp" + IToS(nRandomProp));


return ip;
}
//------------------------------------------------------------------------------
itemproperty PropForGloves(int nIPGrade)
{
    itemproperty ip;
    int nPropNum;

    switch(nIPGrade)
    {
        case 1: nPropNum = 9;       break;
        case 2: nPropNum = 12;      break;
        case 3: nPropNum = 13;      break;
    }


    int nRandomProp = Random(nPropNum);                                         //DBM("sl_s_slw_inc", "PropForGloves", "nRandomProp" + IToS(nRandomProp));
    if (nRandomProp == 0)
        ip = RandomAbilityBonus();

    else if (nRandomProp == 1)
        ip = RandomSkillBonus(IP_GROUP_GLOVES);

    else if (nRandomProp == 2)
        ip = ItemPropertyAttackBonus(1);

    else if (nRandomProp == 3)
        ip = RandomSavingThrow();

    else if (nRandomProp == 4)
        ip = RandomSpellBonus();

    else if (nRandomProp == 5)
        ip = ItemPropertyRegeneration(1);

    else if (nRandomProp == 6)
        ip = ItemPropertyACBonus(1);

    else if (nRandomProp == 7)
        ip = ItemPropertyDamageReduction(IP_CONST_DAMAGEREDUCTION_1, IP_CONST_DAMAGESOAK_5_HP);
    else if (nRandomProp == 8)
        ip = RandomOnHitProps(nIPGrade);

    //2
    else if (nRandomProp == 9)
        ip = RandomFeatBonus(IP_GROUP_GLOVES);

    else if (nRandomProp == 10)
        ip = RandomSpellSlot();

    else if (nRandomProp == 11)
        ip = RandomDamageBonus();

    //3
    else if (nRandomProp == 12)
        ip = ItemPropertyBonusSpellResistance(IP_CONST_SPELLRESISTANCEBONUS_16);


    //TEST
    if(!GetIsItemPropertyValid(ip))
        DBM("slw", "PropForGloves", "RANDOM IP FAILED, nRandomProp" + IToS(nRandomProp));


return ip;
}
/*
//------------------------------------------------------------------------------
itemproperty ResetItemProperty(itemproperty ip)
{
    int nIpType = GetItemPropertyType(ip);                                      //DBM("sl_s_slw_inc", "ResetItemProperty", "nIpType" + IToS(nIpType));
    int nIpSubType = GetItemPropertySubType(ip);                                //DBM("sl_s_slw_inc", "ResetItemProperty", "nIpSubType" + IToS(nIpSubType));
    int nCostTableValue = 1;                                                    //DBM("sl_s_slw_inc", "ResetItemProperty", "nIpSubType" + IToS(GetItemPropertyCostTableValue(ip)));

    switch(nIpType)
    {
        case ITEM_PROPERTY_SPELL_RESISTANCE:
            nCostTableValue = 3;
            break;
        case ITEM_PROPERTY_MASSIVE_CRITICALS:
            nCostTableValue = 12;
            break;
        case ITEM_PROPERTY_DAMAGE_BONUS:
            nCostTableValue = 2 + 10*Random(2);//2(2) or 12(2d4)
            break;
        case ITEM_PROPERTY_DAMAGE_REDUCTION:
            nIpSubType = 0;
            break;
        case ITEM_PROPERTY_SKILL_BONUS:
            nCostTableValue = 1 + Random(2);//1,2,3... or 2,4,6...?
            break;

        //case ITEM_PROPERTY_IMMUNITY_DAMAGE_TYPE:
        //case ITEM_PROPERTY_DAMAGE_RESISTANCE:
        //case ITEM_PROPERTY_SAVING_THROW_BONUS:
        //case ITEM_PROPERTY_SAVING_THROW_BONUS_SPECIFIC:
        //case ITEM_PROPERTY_ABILITY_BONUS:
        //case ITEM_PROPERTY_ABILITY_BONUS:
        //case ITEM_PROPERTY_ATTACK_BONUS:
        //case ITEM_PROPERTY_ENHANCEMENT_BONUS:
        //case ITEM_PROPERTY_MIGHTY:
        //case ITEM_PROPERTY_REGENERATION_VAMPIRIC:
        //case ITEM_PROPERTY_AC_BONUS:
        //case ITEM_PROPERTY_REGENERATION:            nCostTableValue = 1;
            //break;
    }
    //DBM("sl_s_slw_inc", "ResetItemProperty", "nIpSubType after reset" + IToS(nIpSubType));
    //DBM("sl_s_slw_inc", "ResetItemProperty", "nCostTableValue after reset" + IToS(nCostTableValue));

return ItemProperty(nIpType, nCostTableValue, nIpSubType);
}
//------------------------------------------------------------------------------
void AddPropertyToItemVars_New(object oItem, itemproperty ip, int nReset = FALSE)
{
    int nIpType, nIpSubType, nIpValue;
    int nMaxProps;
    string sID, sVarName;


    sVarName = "nMaxDynProps";//Dynamic(LevelingUp) properties
    nMaxProps = GetLocalInt(oItem, sVarName);                                   //DBM("sl_s_slw_inc", "AddPropertyToItemVars_New", "nMaxProps(Dyn)" + IToS(nMaxProps));
    nMaxProps++;
    sID = IntToString(nMaxProps);                                               //DBM("sl_s_slw_inc", "AddPropertyToItemVars_New", "sID: " + sID);

    if(nReset && GetIsLevelingUpProperty(ip))
        ip = ResetItemProperty(ip);

    nIpType = GetItemPropertyType(ip);                                          //DBM("sl_s_slw_inc", "AddPropertyToItemVars_New", "nIpType" + IToS(nIpType));
    nIpSubType = GetItemPropertySubType(ip);                                    //DBM("sl_s_slw_inc", "AddPropertyToItemVars_New", "nIpSubType" + IToS(nIpSubType));
    nIpValue = GetItemPropertyCostTableValue(ip);                               //DBM("sl_s_slw_inc", "AddPropertyToItemVars_New", "nIpValue" + IToS(nIpValue));

    SetLocalInt(oItem, "Prop_"+sID+"_Type", nIpType);
    SetLocalInt(oItem, "Prop_"+sID+"_SubType", nIpSubType);
    SetLocalInt(oItem, "Prop_"+sID+"_Value", nIpValue);


    SetLocalInt(oItem, sVarName, nMaxProps);                                    //DBM("sl_s_slw_inc", "AddPropertyToItemVars_New", "nMaxPropsTEST" + IToS(GetLocalInt(oItem, sVarName)));

    if(GetIsLevelingUpProperty(ip))
        SetLocalInt(oItem, "nLVLProps", (GetLocalInt(oItem, "nLVLProps")+1)); //LevelingUpProps
    else
        SetLocalInt(oItem, "nNonLVLProps", (GetLocalInt(oItem, "nNonLVLProps")+1));//non LevelingUpProps
                                                                                //DBM("sl_s_slw_inc", "AddPropertyToItemVars_New", "nLVLPropsTEST" + IToS(GetLocalInt(oItem, "nLVLProps")));
                                                                                //DBM("sl_s_slw_inc", "AddPropertyToItemVars_New", "nNonLVLPropsTEST" + IToS(GetLocalInt(oItem, "nNonLVLProps")));
}


// v2.0
void SetAndAddPropsForItem(object oItem, int nIPGrade, int nIpGroup, int nNumberOfProps)
{                                                                               //DBM("sl_s_slw_inc", "SetAndAddPropsForItem", "Begin with oItem" + OToS(oItem));
                                                                                //DBM("sl_s_slw_inc", "SetAndAddPropsForItem", "Begin with nIPGrade" + IToS(nIPGrade));
                                                                                //DBM("sl_s_slw_inc", "SetAndAddPropsForItem", "Begin with nIpGroup" + IToS(nIpGroup));
                                                                                //DBM("sl_s_slw_inc", "SetAndAddPropsForItem", "Begin with nNumberOfProps" + IToS(nNumberOfProps));
    int nCounter;
    itemproperty ip;
    int nPropType;
    int nSubType;
    int nCountOfSpecProp;
    int nMax;

    while (nCounter<nNumberOfProps)
    {
        if (nIpGroup == IP_GROUP_MELEE_WEAPON)
            ip = PropForMeleeWeapon(nIPGrade);

        else if (nIpGroup == IP_GROUP_RANGED_WEAPON)
            ip = PropForRangedWeapon(nIPGrade);

        else if (nIpGroup == IP_GROUP_GLOVES)
            ip = PropForGloves(nIPGrade);

        else
            ip = PropForClothes(nIPGrade, nIpGroup);


        if (GetIsItemPropertyValid(ip) && (!IPGetItemHasProperty(oItem, ip, -1)))
        {
            if (!GetItemHasAttackBonus(oItem, ip))
            {
                nPropType = GetItemPropertyType(ip);                            //DBM("sl_s_slw_inc", "SetAndAddPropsForItem", "nPropType" + IToS(nPropType));
                nCountOfSpecProp = GetLocalInt(oItem, ("CounterOfSpecialProperty_"+ IntToString(nPropType)));  //DBM("sl_s_slw_inc", "SetAndAddPropsForItem", "nCountOfSpecProp" + IToS(nCountOfSpecProp));
                nMax = GetMaxOfPropsOfType(nPropType);                          //DBM("sl_s_slw_inc", "SetAndAddPropsForItem", "nMax" + IToS(nMax));
                if (nCountOfSpecProp < nMax)
                {
                    nCounter++;                                                 //DBM("sl_s_slw_inc", "SetAndAddPropsForItem", "nCounter++" + IToS(nCounter));
                    //IPSafeAddItemProperty(oItem, ip);
                    AddPropertyToItemVars_New(oItem, ip);
                    if (nPropType == ITEM_PROPERTY_BONUS_SPELL_SLOT_OF_LEVEL_N)
                    {
                        nSubType = GetItemPropertySubType(ip);                  //DBM("sl_s_slw_inc", "SetAndAddPropsForItem", "nSubType of bonus slot" + IToS(nSubType));
                        IPSafeAddItemProperty(oItem, ItemPropertyLimitUseByClass(nSubType));
                    }

                    if ((nPropType == ITEM_PROPERTY_ATTACK_BONUS) && (nIpGroup == IP_GROUP_GLOVES))
                        IPSafeAddItemProperty(oItem, ItemPropertyLimitUseByClass(IP_CONST_CLASS_MONK));

                    nCountOfSpecProp++;
                    SetLocalInt(oItem, ("CounterOfSpecialProperty_"+ IntToString(nPropType)), nCountOfSpecProp);
                }
            }
        }
    }
    DelVarsForCountOfSpecProp(oItem);

return;
}*/
//-----------------------------------------------------------------------------
int GetIsSLWProperty(itemproperty ip)
{
    int nIpType = GetItemPropertyType(ip);
    switch(nIpType)
    {
        case ITEM_PROPERTY_ABILITY_BONUS:
        case ITEM_PROPERTY_AC_BONUS:
        case ITEM_PROPERTY_ATTACK_BONUS:
        case ITEM_PROPERTY_BONUS_FEAT:
        case ITEM_PROPERTY_BONUS_SPELL_SLOT_OF_LEVEL_N:
        case ITEM_PROPERTY_CAST_SPELL:
        case ITEM_PROPERTY_DAMAGE_BONUS:
        case ITEM_PROPERTY_DAMAGE_REDUCTION:
        case ITEM_PROPERTY_DAMAGE_RESISTANCE:
        case ITEM_PROPERTY_ENHANCEMENT_BONUS:
        case ITEM_PROPERTY_IMMUNITY_DAMAGE_TYPE:
        case ITEM_PROPERTY_KEEN:
        case ITEM_PROPERTY_MASSIVE_CRITICALS:
        case ITEM_PROPERTY_MIGHTY:
        case ITEM_PROPERTY_ONHITCASTSPELL:
        case ITEM_PROPERTY_REGENERATION:
        case ITEM_PROPERTY_REGENERATION_VAMPIRIC:
        case ITEM_PROPERTY_SAVING_THROW_BONUS:
        case ITEM_PROPERTY_SKILL_BONUS:
        case ITEM_PROPERTY_SAVING_THROW_BONUS_SPECIFIC:
        case ITEM_PROPERTY_SPELL_RESISTANCE:
        case ITEM_PROPERTY_UNLIMITED_AMMUNITION:
        case ITEM_PROPERTY_ON_HIT_PROPERTIES:         // 09.2017
        case ITEM_PROPERTY_EXTRA_RANGED_DAMAGE_TYPE:  // 09.2017
            return TRUE;
    }
return FALSE;
}
//------------------------------------------------------------------------------
int GetIsUseLimitationIP(itemproperty ip)
{
    int nIpType = GetItemPropertyType(ip);
    switch(nIpType)
    {
        case ITEM_PROPERTY_USE_LIMITATION_ALIGNMENT_GROUP:
        case ITEM_PROPERTY_USE_LIMITATION_CLASS:
        case ITEM_PROPERTY_USE_LIMITATION_RACIAL_TYPE:
        case ITEM_PROPERTY_USE_LIMITATION_SPECIFIC_ALIGNMENT:
        case ITEM_PROPERTY_USE_LIMITATION_TILESET:
        case ITEM_PROPERTY_QUALITY:
            return TRUE;
    }
return FALSE;
}
//------------------------------------------------------------------------------
/*
void ManageAllItemProps(object oItem)//returns nonSLW-system LevelingUp props
{
    int nNonSLWProps, nOneOriginalProprtyWasRemoved;
    itemproperty ip = GetFirstItemProperty(oItem);
    while(GetIsItemPropertyValid(ip))
    {
        if(GetIsUseLimitationIP(ip))
            RemoveItemProperty(oItem, ip); //system manages use limitations itself
        else if(!nOneOriginalProprtyWasRemoved && !Random(10))//random. Remove maximum 1 proprerty
        {
            nOneOriginalProprtyWasRemoved = TRUE;                               //DBM("sl_s_slw_inc", "ManageAllItemProps", "nOneOriginalProprtyWasRemoved");
            RemoveItemProperty(oItem, ip);
        }
        else if(GetIsSLWProperty(ip))//does the property exits in SLW-system?
        {                                                                       //DBM("sl_s_slw_inc", "ManageAllItemProps", "IsSLWProperty!");
            AddPropertyToItemVars_New(oItem, ip, TRUE);//function not only adds property to list, but counts LVL- and NonLVL- propperties
            RemoveItemProperty(oItem, ip);
        }
        else
        {
            if(!nOneOriginalProprtyWasRemoved && !Random(5))//for NonSLWProps more chance to be removed
            {                                                                   //DBM("sl_s_slw_inc", "ManageAllItemProps", "nOneOriginalProprtyWasRemoved_Random(5)");
                nOneOriginalProprtyWasRemoved = TRUE;
                RemoveItemProperty(oItem, ip);
            }
            else
                nNonSLWProps++;   //non SLW-sytem props
        }
        ip = GetNextItemProperty(oItem);
    }
    SetLocalInt(oItem, "OneOriginalProprtyWasRemoved", nOneOriginalProprtyWasRemoved);
    SetLocalInt(oItem, "NonSLWProps", nNonSLWProps);                            //DBM("sl_s_slw_inc", "ManageAllItemProps", "nNonSLWProps" + IToS(nNonSLWProps));
    DeleteLocalString(oItem, "ItemCode");
}
*/

//------------------------------------------------------------------------------
int GetQuality(int nIpGrade)
{
    switch(nIpGrade)
    {
        case 1: return IP_CONST_QUALITY_VERY_POOR;
        case 2: return IP_CONST_QUALITY_AVERAGE;
    }
return IP_CONST_QUALITY_EXCELLENT;
}
//------------------------------------------------------------------------------
// v2.0 -> v3.0
object SetMainVariables(object oItem, int nIPGrade)
{                                                                               //DBM("sl_s_slw_inc", "SetMainVariables", "Start with oOldItem" + OToS(oItem));
                                                                                //DBM("sl_s_slw_inc", "SetMainVariables", "Start with oPC" + OToS(oPC));
    SetName(oItem, "Бездушный союзник");
    string sDescription = "Иногда маленькая искорка силы воина, погибшего под действием темного шаманства, оставляла отпечаток жизни на вещах, когда-то ему принадлежавших. Получая бесценный дар жизнь, насыщаясь в боях силой духа своего хозяина, бездушное существо безропотно служило своему новому обладателю.";
    SetDescription(oItem, sDescription);

    IPSafeAddItemProperty(oItem, ItemPropertyCastSpell(536, IP_CONST_CASTSPELL_NUMUSES_UNLIMITED_USE));
    IPSafeAddItemProperty(oItem, ItemPropertyQuality(GetQuality(nIPGrade)));

    if(GetBaseItemType(oItem) == BASE_ITEM_CLOAK)
        SetLocalInt(oItem, "NewCloak", 1); // Чтоб не пересоздавалась при первом активэйте

    SetLocalInt(oItem, "NoRecycle", 1);//Denies vendor sales
    SetLocalInt(oItem, "SLW_Status", 1);
    SetIdentified(oItem, FALSE);

    DeleteLocalInt(oItem, "SLW_PropsLeft");
    DeleteLocalInt(oItem, "SLW_PropsDeleted");

    SetLocalInt(oItem, "SLW_NewItem", 1);
return oItem;
}
//------------------------------------------------------------------------------
int GetIsPotentialUpgradingItem(object oItem)
{                                                                               //DBM("sl_s_slw_inc", "GetIsPotentialUpgradingItem", "Start with oItem" + OToS(oItem));
    int nGroup = GetIPGroup(oItem);                                             //DBM("sl_s_slw_inc", "GetIsPotentialUpgradingItem", "nGroup" + IToS(nGroup));
    if(nGroup == IP_GROUP_MELEE_WEAPON)
        return IPGetIsMeleeWeapon(oItem);
return TRUE;
}
//------------------------------------------------------------------------------

/*
object CreateLevelingUpItem_New(object oItem1, object oPC)
{                                                                               //DBM("sl_s_slw_inc", "CreateLevelingUpItem_New", "Start with oItem1" + OToS(oItem1));
                                                                                //DBM("sl_s_slw_inc", "CreateLevelingUpItem_New", "Start with oPC" + OToS(oPC));

    if(GetLocalInt(oItem1, "SLW_ItemChecked"))  return oItem1; //To check an item only once
    if(!GetIsPotentialUpgradingItem(oItem1))
    {
        SetLocalInt(oItem1, "SLW_ItemChecked", TRUE);
        return oItem1;
    }

    if(GetLocalInt(GetModule(), "SLW_ON"))//In test period variable is set only by DM online
    {
        if(!Random(40))
            SetLocalInt(oPC, "GiveLvlItem", TRUE);
        else
            SetLocalInt(oItem1, "SLW_ItemChecked", TRUE);
    }

    if(!GetLocalInt(oPC, "GiveLvlItem"))  return oItem1;
    DeleteLocalInt(oPC, "GiveLvlItem");

    //Recreation for new tag
    object oItem = CopyObject(oItem1, GetLocation(oPC), OBJECT_INVALID, "sl_it_slw_tag");   //DBM("sl_s_slw_inc", "CreateLevelingUpItem_New", "oItem copy" + OToS(oItem));
    SetIdentified(oItem1, FALSE);
    if(GetTag(oItem1) == "symbfaith001")//For cleric swords
        SetLocalInt(oItem, "symbfaith001", TRUE);

    DestroyObject(oItem1, 0.1);
    SetIdentified(oItem, TRUE);
    FloatingTextStringOnCreature("Непонятным образом находка выскользнула из ваших рук!", oPC);
    //End rec

    SetLocalInt(oItem, "SLW_ItemChecked", TRUE);

    //Get grade of Item
    int nIPGrade;
    int nItemRestrictLevel = getItemLevel_New(oItem);                           //DBM("sl_s_slw_inc", "CreateLevelingUpItem_New", "nItemRestrictLevel" + IToS(nItemRestrictLevel));

    if(nItemRestrictLevel<=15)
        nIPGrade = 1;
    else if((nItemRestrictLevel>15) && (nItemRestrictLevel<=26))
        nIPGrade = 2;
    else if(nItemRestrictLevel>26)
        nIPGrade = 3;
    SetLocalInt(oItem, "nItemGrade", nIPGrade);

    //Manage props
    SetIdentified(oItem, TRUE);
    ManageAllItemProps(oItem);//Remove all SLW-system props

    //Add props
    int nIPGroup = GetIPGroup(oItem);//type of item                             //DBM("sl_s_slw_inc", "CreateLevelingUpItem_New", "nIPGroup" + IToS(nIPGroup));
    SetAndAddPropsForItem(oItem, nIPGrade, nIPGroup, GetLocalInt(oItem, "OneOriginalProprtyWasRemoved") + Random(2));
    //Count LevelUps
    int nLVLProps = GetLocalInt(oItem, "nLVLProps");
    int nNonLVLProps = GetLocalInt(oItem, "nNonLVLProps"); //non LevelingUpProps

    int nRemainLvlUps = nNonLVLProps + nLVLProps*nIPGrade + Random(nLVLProps) + (Random(nLVLProps) * (GetRank(oPC)>Random(10))); //bZ 01.01.2015
    SetLocalInt(oItem, "nRemainLvlUps", nRemainLvlUps);

    //del vars
    DeleteLocalInt(oItem, "OneOriginalProprtyWasRemoved");
    DeleteLocalInt(oItem, "nLVLProps");
    DeleteLocalInt(oItem, "nNonLVLProps");

    //Set main vars
    object oNewItem = SetMainVariables(oItem, oPC, nIPGrade);
return oNewItem;
}
*/



//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

//v3.0
// BreakString Part
void Vector_BreakString(object oItem, string sName, string str, string sDelimiter = "_")
{
    string sPart;
    int nMax, nPos = FindSubString(str, sDelimiter);
    while(nPos>=0)
    {
        sPart = GetStringLeft(str, nPos);
        str = GetStringRight(str, GetStringLength(str) - nPos - 1);
        nMax++;
        SetLocalString(oItem, sName+"_"+ IntToString(nMax), sPart);

        nPos = FindSubString(str, sDelimiter);
    }

    if(str != "")
    {
        nMax++;
        SetLocalString(oItem, sName+"_"+ IntToString(nMax), str);
    }
    SetLocalInt(oItem, sName+"_MAX", nMax);
}
//------------------------------------------------------------------------------
void Vector_Destroy(object oItem, string sName)
{
    int i, nMax = GetLocalInt(oItem, sName+"_MAX");
    for(i=1; i<=nMax; i++)
        DeleteLocalString(oItem, sName+"_"+IntToString(i));
    DeleteLocalInt(oItem, sName+"_MAX");
}
//------------------------------------------------------------------------------
string Vector_GetElement(object oItem, string sName, int nNumber)
{
    return GetLocalString(oItem, sName+"_"+IntToString(nNumber));
}
//------------------------------------------------------------------------------
int Vector_GetSize(object oItem, string sName)
{
    return GetLocalInt(oItem, sName+"_MAX");
}
//------------------------------------------------------------------------------




//GENERAL
itemproperty VarsToProperty(object oItem, int nPropNumber);

void PropertyToVars(object oItem, itemproperty ip);

string GetIPUpgradeLine(itemproperty ip, int bAlternative = FALSE);

string GetNextIPValueFromLine(object oItem, string sLine, int nCurrentStage);

string GetPreviousIPValueFromLine(object oItem, string sLine, int nCurrentStage); // Не написана

int GetMaxStage(int nGrade, int nPropType, int nSubType);

// Создает разные списки. Выбирается список в зависимости от значени пеерменной nListType
// 0 - для рандомного апгрэйда
// 1 - для рандомного дегрэйда
// 2 - для имбы
// Возвращает количество элементов в списке
int CreateTempIPList(object oItem, int nListType = 0);


// Temp list subpart
//------------------------------------------------------------------------------
void AddVarToTempIPList(object oItem, int nMainListPropNumber)
{
    int nTempMax = GetLocalInt(oItem, "SLW_TEMP_MAX");
    nTempMax++;
    SetLocalInt(oItem, "SLW_TEMP_"+IntToString(nTempMax), nMainListPropNumber);
    SetLocalInt(oItem, "SLW_TEMP_MAX", nTempMax);
}
//------------------------------------------------------------------------------
void DeleteVarFromTempIPList(object oItem, int nTempPropNumber)
{
    DeleteLocalInt(oItem, "SLW_TEMP_"+IntToString(nTempPropNumber));
    int nTempMax = GetLocalInt(oItem, "SLW_TEMP_MAX");
    if(nTempPropNumber != nTempMax)
    {
        SetLocalInt(oItem, "SLW_TEMP_"+IntToString(nTempPropNumber), GetLocalInt(oItem, "SLW_TEMP_"+IntToString(nTempMax)));
        DeleteLocalInt(oItem, "SLW_TEMP_"+IntToString(nTempMax));
    }
    SetLocalInt(oItem, "SLW_TEMP_MAX", nTempMax-1);
}
//------------------------------------------------------------------------------
void ClearTempIPList(object oItem)
{
    int i, nMax = GetLocalInt(oItem, "SLW_TEMP_MAX");
    for(i=1; i<=nMax; i++)
        DeleteLocalInt(oItem, "SLW_TEMP_"+IntToString(i));
    DeleteLocalInt(oItem, "SLW_TEMP_MAX");
}
//------------------------------------------------------------------------------
int CreateTempIPList(object oItem, int nListType = 0)
{
    ClearTempIPList(oItem);

    int nCurrentStage, nMaxStage;
    int nType, nSubType;
    int i, k, nPropsCount = GetLocalInt(oItem, "PropsCount");                   //DBM("slw", "CreateTempIPList", "nPropsCount" + IToS(nPropsCount));
    for(i=1; i<=nPropsCount; i++)
    {
        nType = GetLocalInt(oItem, "Prop_"+IntToString(i));                     //DBM("slw", "CreateTempIPList", "nType" + IToS(nType));
        nSubType = GetLocalInt(oItem, "SubType_Prop_"+IntToString(i));          //DBM("slw", "CreateTempIPList", "nSubType" + IToS(nSubType));
        nCurrentStage = GetLocalInt(oItem, "Stage_Prop_"+IntToString(i));       //DBM("slw", "CreateTempIPList", "nCurrentStage" + IToS(nCurrentStage));
        nMaxStage = GetLocalInt(oItem, "MaxStage_Prop_"+IntToString(i));        //DBM("slw", "CreateTempIPList", "nMaxStage" + IToS(nMaxStage));

        if(!nListType)
        {
            if(nCurrentStage != nMaxStage)
                AddVarToTempIPList(oItem, i);
        }
        else if(nListType == 1)
        {
            if(nMaxStage > 1)
                AddVarToTempIPList(oItem, i);
        }
        else if(nListType == 2)
        {
            if((GetMaxStage(GetItemGrade(oItem), nType, nSubType) == nMaxStage) && (nMaxStage>1))
                AddVarToTempIPList(oItem, i);
        }
    }
return GetLocalInt(oItem, "SLW_TEMP_MAX");
}
//------------------------------------------------------------------------------
int SelectRandomPropNumberThroughTempList(object oItem)
{
    int nMax = GetLocalInt(oItem, "SLW_TEMP_MAX");
    if(!nMax)
        return 0;

    int nRandom = 1+Random(nMax);
return GetLocalInt(oItem, "SLW_TEMP_"+IntToString(nRandom));
}
//------------------------------------------------------------------------------
// End of Temp list subpart

//------------------------------------------------------------------------------
itemproperty VarsToProperty(object oItem, int nPropNumber)
{
    int nIpType = GetLocalInt(oItem, "Prop_"+IntToString(nPropNumber));
    int nIpSubType = GetLocalInt(oItem, "SubType_Prop_"+IntToString(nPropNumber));
    int nCostTableValue = GetLocalInt(oItem, "Value_Prop_"+IntToString(nPropNumber));
    int nParam1 = GetLocalInt(oItem, "Param1_Prop_"+IntToString(nPropNumber));

    return ItemProperty(nIpType, nCostTableValue, nIpSubType, nParam1);
}
//------------------------------------------------------------------------------
void PropertyToVars(object oItem, itemproperty ip)
{
    int nType = GetItemPropertyType(ip);                                        //DBM("slw", "PropertyToVars", "nType" + IToS(nType));
    int nSubType = GetItemPropertySubType(ip);                                  //DBM("slw", "PropertyToVars", "nSubType" + IToS(nSubType));
    int nValue = GetItemPropertyCostTableValue(ip);                             //DBM("slw", "PropertyToVars", "nValue" + IToS(nValue));
    int nParam1 = GetItemPropertyParam1Value(ip);                               //DBM("slw", "PropertyToVars", "nParam1" + IToS(nParam1));

    int nMax = GetLocalInt(oItem, "PropsCount");                                //DBM("slw", "PropertyToVars", "nMax before" + IToS(nMax));
    nMax++;
    SetLocalInt(oItem, "Prop_"+IntToString(nMax), nType);
    SetLocalInt(oItem, "SubType_Prop_"+IntToString(nMax), nSubType);
    SetLocalInt(oItem, "Value_Prop_"+IntToString(nMax), nValue);
    SetLocalInt(oItem, "Param1_Prop_"+IntToString(nMax), nParam1);

    SetLocalInt(oItem, "PropsCount", nMax);                                     //DBM("slw", "PropertyToVars", "PropsCount after" + IToS(nMax));
}
//------------------------------------------------------------------------------
int GetMaxStage(int nGrade, int nPropType, int nSubType)
{
    int nResult;
    switch(nPropType)
    {
        // Props without upgrade
        case ITEM_PROPERTY_BONUS_FEAT:
        case ITEM_PROPERTY_BONUS_SPELL_SLOT_OF_LEVEL_N:
        case ITEM_PROPERTY_CAST_SPELL:
        case ITEM_PROPERTY_KEEN:
        case ITEM_PROPERTY_ONHITCASTSPELL:
        case ITEM_PROPERTY_UNLIMITED_AMMUNITION:
        case ITEM_PROPERTY_EXTRA_RANGED_DAMAGE_TYPE:
            nResult = 1;
            break;

        case ITEM_PROPERTY_SPELL_RESISTANCE: // Grade 3
            nResult = 2+nGrade;     break;
        case ITEM_PROPERTY_MASSIVE_CRITICALS: // Grade 2  //sLine = "12_10_11_13_15";
            if(nGrade == 4)
                nResult = 5;
            else
                nResult = 2+nGrade;
            break;

        case ITEM_PROPERTY_DAMAGE_BONUS:  // Grade 1
            if(nGrade == 4)
                nResult = 9;
            else if(nGrade == 3)
                nResult = 8;
            else
                nResult = 1+nGrade;
            // ALT sLine = "2_4_16_18_20_22_24_26_30";  // от 2 до 20  // Imbo = 9
            // sLine = "12_10_11_13_15_22_24_26_30"; // от 2d4 до 2d12, дальше от 10 до 20 // Imbo = 9
            break;
        case ITEM_PROPERTY_DAMAGE_REDUCTION: // Grade 1
            if(nGrade == 4)
                nResult = 9;
            else
                nResult = nGrade*2+2;
            //sLine = "1s1_2s1_3s1_3s2_3s3_3s4_3s5_4s5_4s6"; // Сначала поднимается Val до 15, затем Sub до +5, затем еще раз Val до 20 // Imbo > 8  Sub +6
            break;

        case ITEM_PROPERTY_IMMUNITY_DAMAGE_TYPE: // Grade 3
            switch(nSubType)
            {
                case IP_CONST_DAMAGETYPE_MAGICAL:
                    nResult = nGrade-2; break;
                    //sLine = "1_2";   // 5%  // Imbo > 1 10%
                case IP_CONST_DAMAGETYPE_BLUDGEONING:
                case IP_CONST_DAMAGETYPE_SLASHING:
                case IP_CONST_DAMAGETYPE_PIERCING:
                case IP_CONST_DAMAGETYPE_DIVINE:
                    nResult = nGrade-1;  break;
                    //sLine = "1_2_3";   // 10%  // Imbo > 2 25%
                default:
                    nResult = nGrade;     break;
                    //sLine = "1_2_3_4";  // 25% // Imbo > 3  50%
            }
            break;

        case ITEM_PROPERTY_DAMAGE_RESISTANCE: // Grade 2
            switch(nSubType)
            {
                case IP_CONST_DAMAGETYPE_MAGICAL:
                    nResult = nGrade-1; break;
                    //sLine = "1_2_3";      // 10/- // Imbo > 2  15/-
                default:
                    nResult = nGrade;  break;
                    //sLine = "1_2_3_4";    // 15/-  // Imbo > 3  20/-
            }
            break;

        case ITEM_PROPERTY_SKILL_BONUS:  // Grade 1
            if(nGrade == 4)
                nResult = 9;
            else if(nGrade == 3)
            {
                if(nSubType == SKILL_DISCIPLINE || nSubType == SKILL_HIDE || nSubType == SKILL_MOVE_SILENTLY)
                    nResult = 5;
                else
                    nResult = 8;
            }
            else if(nGrade == 2)
                nResult = 6;
            else
                nResult = 3;
            //sLine = "1_2_3_4_5_6_7_8_12"; // Imbo > 12
            break;

        case ITEM_PROPERTY_REGENERATION:
            if(nGrade == 4)
                nResult = 9;
            else if(nGrade == 3)
                nResult = 8;
            else if(nGrade == 2)
                nResult = 6;
            else
                nResult = 3;
            //sLine = "1_2_3_4_5_6_7_8_12"; // Imbo > 9
            break;

        case ITEM_PROPERTY_MIGHTY: // Grade 2
            nResult = nGrade*2+2; // 6 - 8 - 10
            //sLine = "1_2_3_4_5_6_7_8_9_10"; // Imbo > 8
            break;

        case ITEM_PROPERTY_ON_HIT_PROPERTIES:  // Grade 1
            if(nGrade == 4)
                nResult = 9;
            else if(nGrade == 3)
                nResult = 8;
            else if(nGrade == 2)
                nResult = 6;
            else
                nResult = 3;
            //sLine = "1_3_5_8_11_14_15_16_18"; // Gr1: 16 20 24 Gr2: 30 36 42 Gr3: 44 46 48 Imbo: 50
            break;

        default:
            nResult = nGrade+2;
            //sLine = "1_2_3_4_5_6"; // Imbo > 5
            break;
    }
    if(nResult<1)
        nResult = 1;

return nResult;
}
//------------------------------------------------------------------------------
string GetIPUpgradeLine(itemproperty ip, int bAlternative = FALSE)
{
    string sLine;
    int nIpType = GetItemPropertyType(ip);
    int nSubType = GetItemPropertySubType(ip);
    switch(nIpType)
    {
        case ITEM_PROPERTY_SPELL_RESISTANCE:
            sLine = "3_5_7_9_11_13"; // от 16 до 32 // Imbo > 5 36?
            break;

        case ITEM_PROPERTY_MASSIVE_CRITICALS:
            sLine = "12_10_11_13_15";   // 2d12 Imbo нет
            break;

        // ALT sLine = "2_4_16_18_20_22_24_26_30";  // от 2 до 20  // Imbo = 9
            // sLine = "12_10_11_13_15_22_24_26_30";

        case ITEM_PROPERTY_DAMAGE_BONUS:
            if(bAlternative)
                sLine = "2_4_16_18_20_22_24_26_30";  // от 2 до 16, имбо 20 // Imbo = 9
            else
                sLine = "12_10_11_13_15_22_24_26_30"; // от 2d4 до 2d12, дальше от 10 до 16, имбо 20 // Imbo = 9
            break;

        case ITEM_PROPERTY_DAMAGE_REDUCTION:
            sLine = "1s1_2s1_3s1_3s2_3s3_3s4_3s5_4s5_4s6"; // Сначала поднимается Val до 15, затем Sub до +5, затем еще раз Val до 20 // Imbo > 8  Sub +6
            break;

        case ITEM_PROPERTY_IMMUNITY_DAMAGE_TYPE:
            switch(nSubType)
            {
                case IP_CONST_DAMAGETYPE_MAGICAL:
                    sLine = "1_2_3";          break; // 10%  // Imbo > 2 15%

                case IP_CONST_DAMAGETYPE_BLUDGEONING:
                case IP_CONST_DAMAGETYPE_SLASHING:
                    sLine = "1_2_3_4";        break; // 25%  // Imbo > 3 50%

                default:
                    sLine = "1_2_3_4_5";    break; // 50% // Imbo > 4  75%
            }
            break;

        case ITEM_PROPERTY_DAMAGE_RESISTANCE:
            switch(nSubType)
            {
                case IP_CONST_DAMAGETYPE_MAGICAL:
                    sLine = "1_2_3";        break; // 10/- // Imbo > 2  15/-
                default:
                    sLine = "1_2_3_4";      break; // 15/-  // Imbo > 3  20/-
            }
            break;

        case ITEM_PROPERTY_SKILL_BONUS:
            sLine = "1_2_3_4_5_6_7_8_12"; // Imbo > 8
            break;

        case ITEM_PROPERTY_REGENERATION:
            sLine = "1_2_3_4_5_6_7_8_12"; // Imbo > 8
            break;

        case ITEM_PROPERTY_MIGHTY:
            sLine = "1_2_3_4_5_6_7_8_9_10"; // Imbo > 8
            break;

        case ITEM_PROPERTY_ON_HIT_PROPERTIES:
            sLine = "1_3_5_8_11_14_15_16_18"; // Gr1: 16 20 24 Gr2: 30 36 42 Gr3: 44 46 Imbo: 50
            break;

        default:
            sLine = "1_2_3_4_5_6"; // Imbo > 5
            break;
    }
return sLine;
}
//------------------------------------------------------------------------------
string GetNextIPValueFromLine(object oItem, string sLine, int nCurrentStage)
{
    string sValue;
    Vector_BreakString(oItem, "Line", sLine);
    nCurrentStage++;
    if(Vector_GetSize(oItem, "Line")>=nCurrentStage)
        sValue = Vector_GetElement(oItem, "Line", nCurrentStage);

    Vector_Destroy(oItem, "Line");
return sValue;  // Вернет "" если nCurrentStage > Vector_GetSize
}
//------------------------------------------------------------------------------
int GetItemHasAttackOrEnhanceProp(object oItem)
{
    int i, nType, nPropsCount = GetLocalInt(oItem, "PropsCount");
    for(i=1; i<=nPropsCount; i++)
    {
        nType = GetLocalInt(oItem, "Prop_"+IntToString(i));
        if(nType == ITEM_PROPERTY_ATTACK_BONUS || nType == ITEM_PROPERTY_ENHANCEMENT_BONUS)
            return TRUE;
    }
return FALSE;
}
//------------------------------------------------------------------------------
int SLW_IPGetItemHasProperty(object oItem, itemproperty ip)
{
    int nType = GetItemPropertyType(ip);
    int nSubType = GetItemPropertySubType(ip);
    int nTempType, nTempSubType;

    if(nType == ITEM_PROPERTY_ATTACK_BONUS || nType == ITEM_PROPERTY_ENHANCEMENT_BONUS)
        return GetItemHasAttackOrEnhanceProp(oItem);


    int nPropsCount = GetLocalInt(oItem, "PropsCount");
    int i;
    for(i=1; i<=nPropsCount; i++)
    {
        nTempType = GetLocalInt(oItem, "Prop_"+IntToString(i));
        nTempSubType = GetLocalInt(oItem, "SubType_Prop_"+IntToString(i));
        if(nType == nTempType)
        {
            // Свойства чьи сабтайпы проверять нельзя или не нужно
            if(nType == ITEM_PROPERTY_AC_BONUS || nType == ITEM_PROPERTY_DAMAGE_REDUCTION || nType == ITEM_PROPERTY_UNLIMITED_AMMUNITION)
                return TRUE;
            // Все остальные свойства
            if(nSubType == nTempSubType)
                return TRUE;
        }
    }
return FALSE;
}
//------------------------------------------------------------------------------
void DeleteProperty(object oItem, int nNumberToDelete)
{
    string sNumberToDelete = IntToString(nNumberToDelete);

    int nPropsCount = GetLocalInt(oItem, "PropsCount");
    string sPropsCount = IntToString(nPropsCount);

    if(nNumberToDelete != nPropsCount)
    {   // Переносим последний элемент на место удаляемого
        SetLocalInt(oItem, "Prop_"+sNumberToDelete, GetLocalInt(oItem, "Prop_"+sPropsCount));
        SetLocalInt(oItem, "SubType_Prop_"+sNumberToDelete, GetLocalInt(oItem, "SubType_Prop_"+sPropsCount));
        SetLocalInt(oItem, "Value_Prop_"+sNumberToDelete, GetLocalInt(oItem, "Value_Prop_"+sPropsCount));
        SetLocalInt(oItem, "Param1_Prop_"+sNumberToDelete, GetLocalInt(oItem, "Param1_Prop_"+sPropsCount));
        SetLocalInt(oItem, "Stage_Prop_"+sNumberToDelete, GetLocalInt(oItem, "Stage_Prop_"+sPropsCount));
        SetLocalInt(oItem, "MaxStage_Prop_"+sNumberToDelete, GetLocalInt(oItem, "MaxStage_Prop_"+sPropsCount));
        SetLocalInt(oItem, "Alt_Prop_"+sNumberToDelete, GetLocalInt(oItem, "Alt_Prop_"+sPropsCount));
        sNumberToDelete = sPropsCount; // Чтобы удалить уже последний элемент
    }                                                                           //DBM("slw", "DeleteProperty", "Удаляем свойство" + IToS(GetLocalInt(oItem, "Prop_"+sNumberToDelete)));
    DeleteLocalInt(oItem, "Prop_"+sNumberToDelete);
    DeleteLocalInt(oItem, "SubType_Prop_"+sNumberToDelete);
    DeleteLocalInt(oItem, "Value_Prop_"+sNumberToDelete);
    DeleteLocalInt(oItem, "Param1_Prop_"+sNumberToDelete);
    DeleteLocalInt(oItem, "Stage_Prop_"+sNumberToDelete);
    DeleteLocalInt(oItem, "MaxStage_Prop_"+sNumberToDelete);
    DeleteLocalInt(oItem, "Alt_Prop_"+sNumberToDelete);

    nPropsCount--;
    SetLocalInt(oItem, "PropsCount", nPropsCount);
}



// End of GENERAL part



















// UPGRADE PART
//------------------------------------------------------------------------------
itemproperty UpgradeProperty(object oItem, string sPropNumber, string sNextValue)
{
    int nNextValue;
    int nType = GetLocalInt(oItem, "Prop_"+sPropNumber);
    int nSub, nValue, nParam1;

    Vector_BreakString(oItem, "Temp_ForUPG", sNextValue, "s");
    if(Vector_GetSize(oItem, "Temp_ForUPG")>1) // значит в sNextValue присутствует и Value(element[1]) и Subtype(element[2])
    {
        nValue = StringToInt(Vector_GetElement(oItem, "Temp_ForUPG", 1));
        nSub = StringToInt(Vector_GetElement(oItem, "Temp_ForUPG", 2));
    }
    else
    {
        nNextValue = StringToInt(sNextValue);
        nSub = GetLocalInt(oItem, "SubType_Prop_"+sPropNumber);
        nValue = nNextValue;
    }
    nParam1 = GetLocalInt(oItem, "Param1_Prop_"+sPropNumber);

    Vector_Destroy(oItem, "Temp_ForUPG");
return ItemProperty(nType, nValue, nSub, nParam1);
}
//------------------------------------------------------------------------------
itemproperty UpgradePropertyToMaxStage(object oItem, int nPropNumber)
{
    itemproperty ip = VarsToProperty(oItem, nPropNumber);
    string sPropNumber = IntToString(nPropNumber);
    int nMaxStage = GetLocalInt(oItem, "MaxStage_Prop_"+sPropNumber);
    if(nMaxStage == 1)
        return ip;

    string sLine = GetIPUpgradeLine(ip, GetLocalInt(oItem, "Alt_Prop_"+sPropNumber));
    string sNextValue = GetNextIPValueFromLine(oItem, sLine, nMaxStage-1);
return UpgradeProperty(oItem, sPropNumber, sNextValue);
}
//------------------------------------------------------------------------------
int CharCanEquipNewItem(int nHitDice, object oItem, itemproperty ip)
{
    object oTemp = GetObjectByTag("sl_cont_temp");
    object oTestItem = CopyItem(oItem, oTemp, TRUE);
    SetIdentified(oTestItem, TRUE);
    IPSafeAddItemProperty(oTestItem, ip);

    int nItemLvl = getItemLevel_New(oTestItem);
    DestroyObject(oTestItem, 0.1);

    if(nItemLvl<=nHitDice)
        return TRUE;
return FALSE;
}
//------------------------------------------------------------------------------
void ManageItemMaximumLevel(object oItem, string sPropNumber, int nTempMax)
{
    int nCurrent = GetLocalInt(oItem, "Stage_Prop_"+sPropNumber);
    int nMax = GetLocalInt(oItem, "MaxStage_Prop_"+sPropNumber);
    if(nCurrent==nMax && nTempMax==1)
        DeleteLocalInt(oItem, "SLW_Status");
    else
        SetLocalInt(oItem, "SLW_Status", 1);

}
//------------------------------------------------------------------------------
void SLW_UpgradeItem(object oPC, object oItem, int nTest = FALSE)
{
    int nStatus = GetLocalInt(oItem, "SLW_Status"); //Если у вещи максимальный уровень, будет равно 0; а если > 1, значит содержит уровень игрока на котором была последняя попытка проапгрэйдить вещь
    int nHD = GetHitDice(oPC);
    if(nTest)
        nHD = 40;

    if(nStatus && (nStatus < nHD))
    {
        // Составляем список для выбора свойства
        int nTempMax = CreateTempIPList(oItem);// Возвращает длину списка, которая не будет изменяться в процессе работы функции, она нам понадобится в конце
                                                                                //DBM("slw", "SLW_UpgradeItem", "nTempMax" + IToS(nTempMax));
        // Выбираем свойство для подъема
        itemproperty ip, ipResult;
        string sLine, sNextValue, sPropNumber;
        int nPropNumber, nRandom, nCurrentStage, nListLenth = GetLocalInt(oItem, "SLW_TEMP_MAX");
        while(nListLenth && !GetIsItemPropertyValid(ipResult))
        {
            // Рандомом выбираем номер из временного списка, затем по нему берем номер в основном списке
            nRandom = Random(nListLenth)+1;                                     //DBM("slw", "SLW_UpgradeItem", "nRandom" + IToS(nRandom));
            nPropNumber = GetLocalInt(oItem, "SLW_TEMP_" + IntToString(nRandom));   //DBM("slw", "SLW_UpgradeItem", "nPropNumber" + IToS(nPropNumber));
            sPropNumber = IntToString(nPropNumber);

            // Берем свойство
            ip = VarsToProperty(oItem, nPropNumber);
            nCurrentStage = GetLocalInt(oItem, "Stage_Prop_"+sPropNumber);      //DBM("slw", "SLW_UpgradeItem", "nCurrentStage" + IToS(nCurrentStage));

            // Проверяем является ли свойство улучшаемым. Если нет, тогда с ip ничего не делаем
            if(GetLocalInt(oItem, "MaxStage_Prop_" + sPropNumber) > 1) // SLW property
            {
                // Вычисляем следующее значение свойства по апгрэйд-линейке, и улучшаем свойство
                sLine = GetIPUpgradeLine(ip, GetLocalInt(oItem, "Alt_Prop_" + sPropNumber));    //DBM("slw", "SLW_UpgradeItem", "sLine: " + sLine);
                sNextValue = GetNextIPValueFromLine(oItem, sLine, nCurrentStage);   //DBM("slw", "SLW_UpgradeItem", "sNextValue: " + sNextValue);
                ip = UpgradeProperty(oItem, sPropNumber, sNextValue); // Улучшаем свойство
            }

            // Проверяем свожет ли персонаж носить обновленную вещь
            if(CharCanEquipNewItem(nHD, oItem, ip))
                ipResult = ip; // Если сможет, свойство подходит, созраняем его в результат чтобы цикл завершился
            else
                DeleteVarFromTempIPList(oItem, nRandom); // Если не сможет, удаляем это свойство из временного списка, чтобы на него больше не падал выбор

            nListLenth = GetLocalInt(oItem, "SLW_TEMP_MAX");
        }

        // Если ipResult невалидный, значит ни одно улучшение невозможно ввиду низкого уровня персонажа
        if(GetIsItemPropertyValid(ipResult))
        {
            if(GetItemPropertyType(ipResult) == ITEM_PROPERTY_UNLIMITED_AMMUNITION || GetItemPropertyType(ipResult) == ITEM_PROPERTY_DAMAGE_REDUCTION)
                IPSafeAddItemProperty(oItem, ipResult, 0.0, X2_IP_ADDPROP_POLICY_REPLACE_EXISTING, FALSE, TRUE); // Иначе баг с арбалетами - несколько видов анлим стрел // И несколько разных редактов(+1, +2, +3 и т.д.)
            else
                IPSafeAddItemProperty(oItem, ipResult);
            SetLocalInt(oItem, "Stage_Prop_"+sPropNumber, ++nCurrentStage);
            SetLocalInt(oItem, "SubType_Prop_"+sPropNumber, GetItemPropertySubType(ipResult));
            SetLocalInt(oItem, "Value_Prop_"+sPropNumber, GetItemPropertyCostTableValue(ipResult));
            ManageItemMaximumLevel(oItem, sPropNumber, nTempMax);

            SetLocalInt(oItem, "nItemLvl", GetItemPseudoLevel(oItem)+1);
            FloatingTextStringOnCreature("Ваше снаряжение улучшилось!", oPC, FALSE);
            LevelUpItemIfNecessary(oItem);
        }
        else
        {
            SetLocalInt(oItem, "SLW_Status", nHD); // Запоминаем уровень игрока при котором последний раз была попытка улучшить вещь
            FloatingTextStringOnCreature("Ваше снаряжение улучшится, когда вы будете достаточно опытны чтобы им пользоваться!", oPC, FALSE);
        }

       // Чистим временные переменные
       ClearTempIPList(oItem);
    }
}
//------------------------------------------------------------------------------
void UpgradeItemToMaxStage(object oItem)
{
    itemproperty ip;
    int i, nPropsCount = GetLocalInt(oItem, "PropsCount");
    for(i=1; i<=nPropsCount; i++)
    {
        ip = UpgradePropertyToMaxStage(oItem, i);                               //DBM("slw", "UpgradeItemToMaxStage", "Поднимаем до максимума свойство" + IToS(GetItemPropertyType(ip)));
        IPSafeAddItemProperty(oItem, ip);
    }
    DeleteLocalInt(oItem, "SLW_Status");

    // Так нельзя делать - слишком много инструкций
    //while(GetLocalInt(oItem, "SLW_Status"))
    //    SLW_UpgradeItem(OBJECT_INVALID, oItem, TRUE);
}
//------------------------------------------------------------------------------
void LevelUpItemIfNecessary(object oItem) // v3.0 //bZ 09.2017
{
    int nStatus = GetLocalInt(oItem, "SLW_Status");
    object oPC = GetItemPossessor(oItem);
    //if(!GetIsObjectValid(oPC))  // Я не знаю зачем эти строки были нужны, возможно для теста
    //    oPC = GetNearestCreature(CREATURE_TYPE_PLAYER_CHAR, PLAYER_CHAR_IS_PC, oItem);

    if(nStatus && (GetHitDice(oPC) > nStatus))
    {
        nStatus = 1;
        SetLocalInt(oItem, "SLW_Status", 1);
    }

    int nItemLvl = GetItemPseudoLevel(oItem);
    int nItemExp = GetItemExp(oItem);

    int nNextLvlExp = ItemLevelToItemExp(nItemLvl+1, GetItemGrade(oItem));
    if ((nItemExp >= nNextLvlExp) && (nStatus==1))
        DelayCommand(0.1, SLW_UpgradeItem(oPC, oItem));
return;
}






// ITEM CREATION PART
//------------------------------------------------------------------------------
void ManageAllItemProps(object oItem)
{
    int nSLW_PropsLeft, nSLW_PropsDeleted;
    itemproperty ip = GetFirstItemProperty(oItem);
    while(GetIsItemPropertyValid(ip))
    {                                                                           //DBM("slw", "ManageAllItemProps_v3", "Обрабатываемое свойство" + IToS(GetItemPropertyType(ip)));
        if(GetIsUseLimitationIP(ip))
            RemoveItemProperty(oItem, ip); //system manages use limitations itself
        else if(GetIsSLWProperty(ip))//does the property exits in SLW-system?
        {                                                                       //DBM("slw", "ManageAllItemProps_v3", "SLW!!!");
            PropertyToVars(oItem, ip);
            RemoveItemProperty(oItem, ip);
        }
        else
        {                                                                       //DBM("slw", "ManageAllItemProps_v3", "NON SLW!!!");
            if(Random(3))
                nSLW_PropsLeft++;
            else
            {                                                                   //DBM("slw", "ManageAllItemProps_v3", "Removed");
                RemoveItemProperty(oItem, ip);
                nSLW_PropsDeleted++;
            }
        }
        ip = GetNextItemProperty(oItem);
    }
    SetLocalInt(oItem, "SLW_PropsDeleted", nSLW_PropsDeleted);                  //DBM("slw", "ManageAllItemProps_v3", "SLW_PropsDeleted" + IToS(nSLW_PropsDeleted));
    SetLocalInt(oItem, "SLW_PropsLeft", nSLW_PropsLeft);                        //DBM("slw", "ManageAllItemProps_v3", "SLW_PropsLeft" + IToS(nSLW_PropsLeft));
    DeleteLocalString(oItem, "ItemCode");                                       //DBM("slw", "ManageAllItemProps_v3", "PROPS COUNT" + IToS(GetLocalInt(oItem, "PropsCount")));
}
//------------------------------------------------------------------------------
void AddRandomProperty(object oItem, int nTry = 0)
{
    itemproperty ip;
    int nIPGrade = GetItemGrade(oItem);
    int nIPGroup = GetIPGroup(oItem);                                           //DBM("slw", "AddRandomProperty", "nIPGroup" + IToS(nIPGroup));

    if (nIPGroup == IP_GROUP_MELEE_WEAPON)
        ip = PropForMeleeWeapon(nIPGrade);

    else if (nIPGroup == IP_GROUP_RANGED_WEAPON)
        ip = PropForRangedWeapon(nIPGrade);

    else if (nIPGroup == IP_GROUP_GLOVES)
        ip = PropForGloves(nIPGrade);

    else
        ip = PropForClothes(nIPGrade, nIPGroup);
                                                                                //DBM("slw", "AddRandomProperty", "Выбранное свойство");
                                                                                //DBM("slw", "AddRandomProperty", "nType" + IToS(GetItemPropertyType(ip)));
                                                                                //DBM("slw", "AddRandomProperty", "SybType" + IToS(GetItemPropertySubType(ip)));
                                                                                //DBM("slw", "AddRandomProperty", "Value" + IToS(GetItemPropertyCostTableValue(ip)));
                                                                                //DBM("slw", "AddRandomProperty", "Param1" + IToS(GetItemPropertyParam1Value(ip)));

    if (GetIsItemPropertyValid(ip) && !SLW_IPGetItemHasProperty(oItem, ip))
    {                                                                           //DBM("slw", "AddRandomProperty", "Добавляем свойство");
        PropertyToVars(oItem, ip);
        // Manage use limitations
        /* А зачем? Я передумал // bZ 11.09.2017
        int nSubType, nType = GetItemPropertyType(ip);
        if(nType == ITEM_PROPERTY_BONUS_SPELL_SLOT_OF_LEVEL_N)
        {
            nSubType = GetItemPropertySubType(ip);
            IPSafeAddItemProperty(oItem, ItemPropertyLimitUseByClass(nSubType));
        }
        if ((nType == ITEM_PROPERTY_ATTACK_BONUS || nType == ITEM_PROPERTY_ON_HIT_PROPERTIES) && (nIPGroup == IP_GROUP_GLOVES))
            IPSafeAddItemProperty(oItem, ItemPropertyLimitUseByClass(IP_CONST_CLASS_MONK));
        */
    }
    else
    {
        nTry++;
        if(nTry<5)
            AddRandomProperty(oItem, nTry);
    }
}
//------------------------------------------------------------------------------
void DeleteRandomProperty(object oItem)
{
    itemproperty ip;
    int nSLW_PropsLeft = GetLocalInt(oItem, "SLW_PropsLeft");
    int nRandom = Random(nSLW_PropsLeft+1); // Если выпадет 0 удаляем свойство из переменных из основного списка. Если >0, тогда удаляем оставленное свойство по номеру который выпадет тут.
                                                                                //DBM("slw", "DeleteRandomProperty", "Выбираем свойство на удаление" + IToS(nRandom));
    if(nRandom)
    {
        int nCounter;
        ip = GetFirstItemProperty(oItem);
        while(GetIsItemPropertyValid(ip))
        {
            nCounter++;
            if(nCounter == nRandom)
            {                                                                   //DBM("slw", "DeleteRandomProperty", "Удаляем оставленное свойство" + IToS(GetItemPropertyType(ip)));
                RemoveItemProperty(oItem, ip);
                break;
            }
            ip = GetNextItemProperty(oItem);
        }
        nSLW_PropsLeft--;
        SetLocalInt(oItem, "SLW_PropsLeft", nSLW_PropsLeft);
    }
    else // Удаляем свойство из переменных
    {
        int nPropsCount = GetLocalInt(oItem, "PropsCount");
        nRandom = 1+Random(nPropsCount);                                        //DBM("slw", "DeleteRandomProperty", "Удаляем свойство из списка под номером" + IToS(nRandom));
        DeleteProperty(oItem, nRandom);
    }
}
//------------------------------------------------------------------------------
int DecreaseRandomMaxStage(object oItem)
{
    int nMax = GetLocalInt(oItem, "SLW_TEMP_MAX");
    if(!nMax)
        return FALSE;

    int nRandom;
    if(nMax == 1)
        nRandom = 1;
    else
        nRandom = 1+Random(nMax);

    int nPropNumber = GetLocalInt(oItem, "SLW_TEMP_"+IntToString(nRandom));
    string sPropNumber = IntToString(nPropNumber);                              //DBM("slw", "DecreaseRandomMaxStage", "Понижаем максимум свойства " + sPropNumber);
    int nNewValue = GetLocalInt(oItem, "MaxStage_Prop_"+sPropNumber)-1;         //DBM("slw", "DecreaseRandomMaxStage", "новое значение" + IToS(nNewValue));
    SetLocalInt(oItem, "MaxStage_Prop_"+sPropNumber, nNewValue);

    if(nNewValue == 1)
        DeleteVarFromTempIPList(oItem, nRandom);
return TRUE;
}
//------------------------------------------------------------------------------
void SetPropsMaxStages(object oItem)
{
    int nGrade = GetItemGrade(oItem);
    int i, nType, nSub, nMax, nPropsCount = GetLocalInt(oItem, "PropsCount");
    int nRandom, nDecrease, nDecreaseSum;
    string sPropNumber;
    for(i=1; i<=nPropsCount; i++) // Опреденение максимального значения каждого свойства
    {
        sPropNumber = IntToString(i);
        nType = GetLocalInt(oItem, "Prop_"+sPropNumber);
        nSub = GetLocalInt(oItem, "SubType_Prop_"+sPropNumber);
        nMax = GetMaxStage(nGrade, nType, nSub);
        if(nMax>2) // Рандомизация максимального значения
        {
            nRandom = Random(10);
            if(!nRandom)
                nDecrease=2;
            else if(nRandom<4)
                nDecrease=1;
            else
                nDecrease=0;

            nMax-=nDecrease;
            nDecreaseSum+= nDecrease;
        }
        SetLocalInt(oItem, "MaxStage_Prop_"+sPropNumber, nMax);                 //DBM("slw", "SetPropsMaxStages", "Для свойства " + IntToString(nType) + " nMax" + IToS(nMax));
    }

    // Проверяем на количество свойств. Если их слишком много, минусуем максимумы
    int nMaxPropsForGrade;
    switch(nGrade)
    {
        case 1:  nMaxPropsForGrade = 3; break;
        case 2:  nMaxPropsForGrade = 4; break;
        case 3:  nMaxPropsForGrade = 6; break;
    }
    // За каждое свойство сверх нормы ^^ дважды производим выбор рандомного свойства и понижаем его максимум на единицу
    // Считаем сколько раз нужно произвезти выбор и отнимаем тот минус что "съела" рандомизация выше
    int nRepeatDecrease = (nPropsCount + GetLocalInt(oItem, "SLW_PropsLeft") - nMaxPropsForGrade)*2 - nDecreaseSum;
    if(nRepeatDecrease>0)
    {                                                                           //DBM("slw", "SetPropsMaxStages", "Понижение максимума, nRepeatDecrease" + IToS(nRepeatDecrease));
        CreateTempIPList(oItem, 1);

        for(i=0; i<nRepeatDecrease; i++)
            DecreaseRandomMaxStage(oItem);

        ClearTempIPList(oItem);
    }

    // Imbo // Рандом на добавление одному свойству "имбо" ступени
    if((nGrade == 3) && Random(50) == 7)// 0 выпадает слишком часто
    {
        CreateTempIPList(oItem, 2);
        int nImboPropNumber = SelectRandomPropNumberThroughTempList(oItem);
        if(nImboPropNumber)
        {
            nType = GetLocalInt(oItem, "Prop_"+IntToString(nImboPropNumber));
            nSub = GetLocalInt(oItem, "SubType_Prop_"+IntToString(nImboPropNumber));
            nMax = GetMaxStage(4, nType, nSub);

            SetLocalInt(oItem, "MaxStage_Prop_"+IntToString(nImboPropNumber), nMax);
        }
        ClearTempIPList(oItem);
    }
}
//------------------------------------------------------------------------------
void RexFeronImboCheck(object oItem)
{
    if(IMBO_LIMIT == 0)
        return;

    object oTemp = GetObjectByTag("sl_cont_temp");
    object oTestItem = CopyItem(oItem, oTemp, TRUE);
    SetIdentified(oTestItem, TRUE);

    UpgradeItemToMaxStage(oTestItem);
    int nItemPower = CalculateOverallGradeItem(oTestItem);                      //DBM("SLW", "RexFeronImboCheck", "nItemPower" + IToS(nItemPower));
    DestroyObject(oTestItem, 0.1);

    // Если вещь сильно имбовая, удаляем целое свойство, если не сильно, тогда делаем рандомное свойство слабей
    if((nItemPower > IMBO_LIMIT) && Random(100)) // маленький шанс пропустить имбу
    {
        if(nItemPower > IMBO_LIMIT*2)
            DeleteRandomProperty(oItem);
        else
            DecreaseRandomMaxStage(oItem);

        RexFeronImboCheck(oItem);
    }
}
//------------------------------------------------------------------------------
void PropsPostManage(object oItem)
{
    int nSLW_PropsDeleted = GetLocalInt(oItem, "SLW_PropsDeleted");
    DeleteLocalInt(oItem, "SLW_PropsDeleted"); // Скорей всего эта переменная больше не понадобится.

    // Определяем список свойств
    int i, nChangesCount = 2; // Количество рандомизаций(удалений, замен или добавлений свойств)
    int nRandom = Random(10);
    if(nRandom<3)
        nChangesCount = 1;
    else if(nRandom == 7) // 0 слишком часто выпадает
        nChangesCount = 3;
                                                                                //DBM("slw", "PropsPostManage", "Количество рандомизаций" + IToS(nChangesCount));
    for(i=0; i<nChangesCount; i++)
    {                                                                           //DBM("slw", "PropsPostManage", "Номер ранодмизации" + IToS(i));
        nRandom = Random(3)+nSLW_PropsDeleted; // 0 - удаляем, 1 - заменяем, 2 - добавляем 1 свойство.
                                                                                //DBM("slw", "PropsPostManage", "Выпал рэндом" + IToS(nRandom));
        if(nRandom<=1) // Если 0 или 1, удаляем 1 свойство
        {                                                                       //DBM("slw", "PropsPostManage", "Удаляем");
            DeleteRandomProperty(oItem);
            nSLW_PropsDeleted++;
        }
        if(nRandom>=1) // если 1 или больше - 1 свойство добавляем
        {                                                                       //DBM("slw", "PropsPostManage", "Добавляем");
            AddRandomProperty(oItem);
            nSLW_PropsDeleted--;
        }
    }

    // Если у вещи 1-2 свойства, может так случиться что она останется совсем без свойств. Надо это исправить
    if(GetLocalInt(oItem, "PropsCount")<=0)
    {
        nRandom = 1+Random(2);                                                  //DBM("slw", "PropsPostManage", "Аварийное добавление свейств" + IToS(nRandom));
        for(i=0; i<nRandom; i++)
            AddRandomProperty(oItem);
    }
                                                                                //DBM("slw", "PropsPostManage", "Свойств после рандомизации" + IToS(GetLocalInt(oItem, "PropsCount")));

    // Определяем максимумы // Проверяем количество свойств // Добавляем имбу
    SetPropsMaxStages(oItem);

    RexFeronImboCheck(oItem);
}
//------------------------------------------------------------------------------
object CreateLevelingUpItem_New(object oItem1, object oLoot, int bTest = FALSE)
{
    if(!GetLocalInt(GetModule(), "SLW_ON") || (GetTag(oItem1) == "sl_it_slw_tag") || !GetIsPotentialUpgradingItem(oItem1))
        return oItem1;

    object oPC = GetNearestCreature(CREATURE_TYPE_PLAYER_CHAR, PLAYER_CHAR_IS_PC, oLoot);
    if(!bTest && !GetLocalInt(oPC, "SLW_Test") && Random(40)!=17)// 0 слишком часто выпадает, поэтому например 17
        return oItem1;
    DeleteLocalInt(oPC, "SLW_Test"); // For tests


    //Recreation for new tag
    object oItem = CopyObject(oItem1, GetLocation(oLoot), oLoot, "sl_it_slw_tag");   //DBM("sl_s_slw_inc", "CreateLevelingUpItem_New", "oItem copy" + OToS(oItem));
    WriteTimestampedLogEntry("[SLW] Item Created in area: " + GetName(GetArea(oLoot)));

    if(GetTag(oItem1) == "symbfaith001")//For cleric swords
        SetLocalInt(oItem, "symbfaith001", TRUE);

    DestroyObject(oItem1, 0.1);
    //End rec

    //Get grade of Item
    int nIPGrade;
    int nItemRestrictLevel = getItemLevel_New(oItem);                           //DBM("sl_s_slw_inc", "CreateLevelingUpItem_New", "nItemRestrictLevel" + IToS(nItemRestrictLevel));

    if(nItemRestrictLevel<=6)
        nIPGrade = 1;
    else if((nItemRestrictLevel>6) && (nItemRestrictLevel<=17))
        nIPGrade = 2;
    else if(nItemRestrictLevel>17)
        nIPGrade = 3;
    SetLocalInt(oItem, "nItemGrade", nIPGrade);                                 //DBM("slw", "SLW_CreateSLWItem", "изначальный ГРЭЙД" + IToS(nIPGrade));


    // Обработка свойств
    ManageAllItemProps(oItem);

    // Постобработка
    PropsPostManage(oItem);


    SetMainVariables(oItem, nIPGrade);

                                                                                //DBM("slw", "SLW_CreateSLWItem", "PropsCount FINAL" + IToS(GetLocalInt(oItem, "PropsCount")));
return oItem;
}
//------------------------------------------------------------------------------









// TEST AND DEBUG PART
//------------------------------------------------------------------------------
int GetItemsSlot(object oPC, object oItem)
{
    int n, nSlot = -1;
    while((n<=10) && (nSlot==-1))
    {
        if(GetItemInSlot(n, oPC) == oItem)
            nSlot = n;
        n++;
    }
return nSlot;
}
//------------------------------------------------------------------------------
void SLW_ShowPropsFormVars(object oDM, object oItem)
{
    SendMessageToPC(oDM, "FROM PROPS");
    int i;
    string sProperty;
    itemproperty ip = GetFirstItemProperty(oItem);
    while(GetIsItemPropertyValid(ip))
    {
        sProperty = "T:" + IntToString(GetItemPropertyType(ip)) + "||S:" + IntToString(GetItemPropertySubType(ip)) + "||V:" + IntToString(GetItemPropertyCostTableValue(ip)) + "||P1:" + IntToString(GetItemPropertyParam1Value(ip));
        i++;
        SendMessageToPC(oDM, IntToString(i) + ": " + sProperty);

        ip = GetNextItemProperty(oItem);
    }


    SendMessageToPC(oDM, "FROM VARS");
    int nMax = GetLocalInt(oItem, "PropsCount");
    string sID;
    for(i=1; i<=nMax; i++)
    {
        sID = IntToString(i);
        sProperty = "T:" + IntToString(GetLocalInt(oItem, "Prop_"+sID)) + "||S:" + IntToString(GetLocalInt(oItem, "SubType_Prop_"+sID)) + "||V:" + IntToString(GetLocalInt(oItem, "Value_Prop_"+sID)) + "||P1:" + IntToString(GetLocalInt(oItem, "Param1_Prop_"+sID)) + "||ST:" + IntToString(GetLocalInt(oItem, "Stage_Prop_"+sID)) + "||MS:" + IntToString(GetLocalInt(oItem, "MaxStage_Prop_"+sID));
        SendMessageToPC(oDM, sID + ": " + sProperty);
    }
}
//------------------------------------------------------------------------------
object SLW_RecreateItem(object oPC, object oItem, object oDM = OBJECT_INVALID, int nSlot = -1)
{
    if(nSlot==-1)
        nSlot = GetItemsSlot(oPC, oItem);
    int nExp = GetItemExp(oItem);
    string sResRef = GetResRef(oItem);
    if(GetIsObjectValid(oDM))
    {
        CopyItem(oItem, oDM, TRUE);
        CreateItemOnObject(sResRef, oDM);
    }
    DestroyObject(oItem);

    object oNew = CreateItemOnObject(sResRef, GetObjectByTag("sl_cont_temp"));
    oNew = CreateLevelingUpItem_New(oNew, oPC, TRUE);
    SetIdentified(oNew, TRUE);
    SetItemExp(oNew, nExp);

    if(nSlot>-1)
        AssignCommand(oPC, ActionEquipItem(oNew, nSlot));

    LevelUpItemIfNecessary(oNew);
return oNew;
}
//------------------------------------------------------------------------------

void SLW_RecreateItemOnEnter(object oPC, object oItem, int nSlot = -1);
void SLW_RecreateItemOnEnter(object oPC, object oItem, int nSlot = -1)
{
    if(GetLocalInt(oItem, "SLW_NewItem") || !GetIsObjectValid(oItem))
        return;

    object oNew = SLW_RecreateItem(oPC, oItem, OBJECT_INVALID, nSlot);
    SetLocalInt(oNew, "SLW_NewItem", 1);
}
//------------------------------------------------------------------------------
