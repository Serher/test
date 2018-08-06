//#include "sl_s_dbsys_inc"
//bZ 09.2014
#include "sl_s_op_cat_inc"
//#include "alx_timecheck"
#include "tob_color"
#include "epqst_inc"


void ClearInv(object oMob, int nDestroy = FALSE);

void DestroyTemplates(int nFaction);

void ArenaDebug(string sMessage);

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////     MISC    /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void ArenaDebug(string sMessage)
{
    object oArea = GetObjectByTag("glad_arena");
    string sPlayers = "[GLAD DEBUG]";
    object oPC = GetFirstPC();
    while(GetIsObjectValid(oPC))
    {
        if(GetArea(oPC) == oArea)
            sPlayers += " || " + GetDeity(oPC);
        oPC = GetNextPC();
    }
    WriteTimestampedLogEntry(sPlayers);

    sMessage+= " || Stage=" + IntToString(GetLocalInt(oArea, "ContestStage"));
    sMessage+= " || PCs1=" + IntToString(GetLocalInt(oArea, "1"));
    sMessage+= " || PCs2=" + IntToString(GetLocalInt(oArea, "2"));
    sMessage+= " || Mobs1=" + IntToString(GetLocalInt(oArea, "Mobs1"));
    sMessage+= " || Mobs2=" + IntToString(GetLocalInt(oArea, "Mobs2"));

    object oTop = GetObjectByTag("glad_top1");
    if(GetIsObjectValid(oTop))
        sMessage+= " || Time1=" + IntToString(GetLocalInt(oTop, "TimePassed"));
    else
        sMessage+= " || Top1 not valid";

    oTop = GetObjectByTag("glad_top2");
    if(GetIsObjectValid(oTop))
        sMessage+= " || Time2=" + IntToString(GetLocalInt(oTop, "TimePassed"));
    else
        sMessage+= " || Top2 not valid";

    sMessage+= " || Templates1=" + IntToString(GetLocalInt(oArea, "Templates1"));
    sMessage+= " || Templates2=" + IntToString(GetLocalInt(oArea, "Templates2"));

    sMessage+= " || Template1=" + GetLocalString(oArea, "GladTemplate1");
    sMessage+= " || Template2=" + GetLocalString(oArea, "GladTemplate2");
    sMessage+= " || Template3=" + GetLocalString(oArea, "GladTemplate3");
    sMessage+= " || Template4=" + GetLocalString(oArea, "GladTemplate4");
    sMessage+= " || Template5=" + GetLocalString(oArea, "GladTemplate5");
    sMessage+= " || Template6=" + GetLocalString(oArea, "GladTemplate6");

    WriteTimestampedLogEntry(sMessage);
}
//------------------------------------------------------------------------------
string GladDoorAction(int nStage, int nFaction, int nOpen = FALSE)
{
    int nDoorMod, nDoorCount = 4;
    string sDoorPrefix;
    if(!(nStage%4))//if boss stage, open big doors
    {
        sDoorPrefix = "glad_bigdoor_";
        nDoorCount = 2;
    }
    else //open small doors
        sDoorPrefix = "glad_door_";

    nDoorMod = (nFaction-1)*nDoorCount;

    int i;
    object oDoor;
    for(i = 1; i<=nDoorCount; i++)
    {
        oDoor = GetObjectByTag(sDoorPrefix+IntToString(i+nDoorMod));
        if(nOpen)
            AssignCommand(oDoor, ActionOpenDoor(oDoor));
        else
            AssignCommand(oDoor, ActionCloseDoor(oDoor));
    }
return sDoorPrefix;
}
//------------------------------------------------------------------------------
void SendMessageToGladiators(string sMessage, int nFaction)
{
    object oPC = GetFirstPC();
    while(GetIsObjectValid(oPC))
    {
        if((GetTag(GetArea(oPC)) == "glad_arena") && !GetIsDM(oPC))
        {
            if(GetIdFaction(oPC) == nFaction)
                FloatingTextStringOnCreature(sMessage, oPC);
        }
        oPC = GetNextPC();
    }
}
//------------------------------------------------------------------------------
void DestroyGroundLoot(location lLoc)
{
    int nType;
    object oLoot = GetFirstObjectInShape(SHAPE_SPHERE, 3.0, lLoc, FALSE, OBJECT_TYPE_PLACEABLE | OBJECT_TYPE_ITEM);
    while(GetIsObjectValid(oLoot))
    {
        nType = GetObjectType(oLoot);
        if(nType == OBJECT_TYPE_ITEM)
        {
            SetPlotFlag(oLoot, FALSE);
            DestroyObject(oLoot, 0.1);
        }
        else //Placeable
        {
            if(GetHasInventory(oLoot))
            {
                ClearInv(oLoot, TRUE);
                SetPlotFlag(oLoot, FALSE);
                DestroyObject(oLoot, 0.1);
            }
        }
        oLoot = GetNextObjectInShape(SHAPE_SPHERE, 3.0, lLoc, FALSE, OBJECT_TYPE_PLACEABLE | OBJECT_TYPE_ITEM);
    }
}
//------------------------------------------------------------------------------
int GetRewardCount(int nStage)
{
    int nReward;
    object oArea = GetObjectByTag("glad_arena");
    int nArenaForNubs = GetLocalInt(oArea, "NubsArena");

    if(nArenaForNubs)
    {
        if(nStage == 4)
            nReward = 2500;
        else if(nStage == 8)
            nReward = 5000;
        else if(nStage == 12)
            nReward = 10000;
        else
            nReward = nStage*15;
    }
    else
    {
        if(nStage == 4)
            nReward = 5000;
        else if(nStage == 8)
            nReward = 10000;
        else if(nStage == 12)
            nReward = 15000;
        else
            nReward = nStage*50;
    }
return nReward;
}
//------------------------------------------------------------------------------
void GiveRewardToFaction(int nStage, int nFaction)
{
    int nReward = GetRewardCount(nStage);

    object oArea = GetObjectByTag("glad_arena");
    int nPCs = GetLocalInt(oArea, IntToString(nFaction));
    if(nPCs>1)
        nReward = FloatToInt(nReward * 2.0 / nPCs);

    object oPC = GetFirstPC();
    while(GetIsObjectValid(oPC))
    {
        if(!GetIsDM(oPC))
        {
            if(GetArea(oPC) == oArea)
            {
                if(GetIdFaction(oPC) == nFaction)
                    GiveGoldToCreature(oPC, nReward);
            }
        }
        oPC = GetNextPC();
    }
}
//------------------------------------------------------------------------------



////////////////////////////////////////////////////////////////////////////////
//////////////////////////////    SPAWN    /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

string SelectResRefForNubsArena(int nStage)
{
    string sResRef;
    int nRandom;

    if(nStage == 1)
    {
        nRandom = Random(6);
        switch(nRandom)
        {
            case 0: sResRef = "badger001";      break; //Барсук CR:        4.00000000
            case 1: sResRef = "bat001";         break; //Летучая мышьCR:        3.00000000
            case 2: sResRef = "btlfire001";     break; //Огненный жукCR:        5.00000000
            case 3: sResRef = "sl_cr_en_001";   break; //КомарCR:        3.00000000
            case 4: sResRef = "rat002";         break; //Крыса CR:        3.00000000
            case 5: sResRef = "sl_cr_en_018";   break; //Травяной жительCR:        4.00000000
        }
    }
    else if(nStage == 2)
    {
        nRandom = Random(10);
        switch(nRandom)
        {
            case 0: sResRef = "btlstink001";        break; //Жук-вонючка CR:        8.00000000
            case 1: sResRef = "spidgiant001";       break; //Огромный паукCR:        5.00000000
            case 2: sResRef = "raptor002";          break; //Сокол CR:        4.00000000
            case 3: sResRef = "sl_cr_en_002";       break; //Зеленый комарCR:        4.00000000
            case 4: sResRef = "vito_direbadger";    break; //БарсучищеCR:        6.00000000
            case 5: sResRef = "sl_cr_wwolfyoung";   break; //Молодой белый волкCR:        7.00000000
            case 6: sResRef = "ya_cr068";           break; //Гигантский кабанCR:        7.00000000
            case 7: sResRef = "raven002";           break; //Ворон CR:        4.00000000
            case 8: sResRef = "young_wolf";         break; //ВолчонокCR:        4.00000000
            case 9: sResRef = "btlbomb001";         break; //Жук бомбардирCR:        8.00000000
        }
    }
    else if(nStage == 3)
    {
        nRandom = Random(10);
        switch(nRandom)
        {
            case 0: sResRef = "spidswrd001";    break; //Паук-мечникCR:        8.00000000
            case 1: sResRef = "skeleton001";    break; //Скелет CR:        6.00000000
            case 2: sResRef = "ya_creat002a";   break; //Зеленый Эттаркап CR:        8.00000000
            case 3: sResRef = "zombie002";      break; //Зомби CR:        4.00000000
            case 4: sResRef = "spidwra001";     break; //Паук-духCR:        7.00000000
            case 5: sResRef = "zombie003";      break; //Зомби CR:        4.00000000
            case 6: sResRef = "kobold008";      break; //Кобольд Шаман CR:        4.00000000
            case 7: sResRef = "sl_cr_en_010";   break; //Пятно слизиCR:        8.00000000
            case 8: sResRef = "kobold007";      break; //Кобольд Целитель CR:        4.00000000
            case 9: sResRef = "wolf001";        break; //ВолчараCR:        4.00000000
        }
    }
    else if(nStage == 4)
    {
        nRandom = Random(5);
        switch(nRandom)
        {
            case 0: sResRef = "sl_cr_en_008";   break; //Слизистый кубCR:       10.00000000
            case 1: sResRef = "allip002";       break; //Аллип CR:       10.00000000
            case 2: sResRef = "golclay001";     break; //Глиняный голем CR:       15.00000000
            case 3: sResRef = "beetleboss001";  break; //МаткаCR:       15.00000000
            case 4: sResRef = "bodak003";       break; //БодакCR:       12.00000000
        }
    }
    else if(nStage == 5)
    {
        nRandom = Random(9);
        switch(nRandom)
        {
            case 0: sResRef = "ghast002";           break; //Кошмар CR:        5.00000000
            case 1: sResRef = "shadow001";          break; //Тень CR:        5.00000000
            case 2: sResRef = "veter_cr080";        break; //Гниющий зомбиCR:        7.00000000
            case 3: sResRef = "btlstag001";         break; //Жук-олений рогCR:       10.00000000
            case 4: sResRef = "yuan_ti002";         break; //ГадюкаCR:       10.00000000
            case 5: sResRef = "ghoul001";           break; //ВурдалакCR:        4.00000000
            case 6: sResRef = "ya_creat001a";       break; //Зеленый Эттаркап ВожакCR:       14.00000000
            case 7: sResRef = "sl_cr_whitewolf";    break; //Белый волкCR:       11.00000000
            case 8: sResRef = "sl_cr_en_016";       break; //Жертва пытокCR:        7.00000000
        }
    }
    else if(nStage == 6)
    {
        nRandom = Random(10);
        switch(nRandom)
        {
            case 0: sResRef = "spiddire001";    break; //Жуткий паукCR:       10.00000000
            case 1: sResRef = "veter_cr075";    break; //Скелет-воин CR:       11.00000000
            case 2: sResRef = "zombwarr003";    break; //Зомби-воин CR:       11.00000000
            case 3: sResRef = "vampire002";     break; //Вампир CR:        8.00000000
            case 4: sResRef = "adult_wolf";     break; //ВолкCR:        8.00000000
            case 5: sResRef = "skelmage002";    break; //Скелет ученика магаCR:        6.00000000
            case 6: sResRef = "yuan_ti004";     break; //ГюрзаCR:        8.00000000
            case 7: sResRef = "ghoullord001";   break; //Лорд ВурдалакCR:       11.00000000
            case 8: sResRef = "skelpriest003";  break; //Скелет-жрец CR:        6.00000000
            case 9: sResRef = "wolfess";        break; //ВолчицаCR:        6.00000000
        }
    }
    else if(nStage == 7)
    {
        nRandom = Random(9);
        switch(nRandom)
        {
            case 0: sResRef = "goblina002";       break; //ЛесовикCR:        7.00000000
            case 1: sResRef = "goblina001";       break; //ЛесовикCR:        8.00000000
            case 2: sResRef = "mumcleric001";     break; //Великая мумияCR:        7.00000000
            case 3: sResRef = "yuan_ti003";       break; //КобраCR:        8.00000000
            case 4: sResRef = "zombieboss001";    break; //Зомби ЛордCR:       14.00000000
            case 5: sResRef = "wererat001";       break; //Крыс-оборотеньCR:       12.00000000
            case 6: sResRef = "goblina004";       break; //ЛесовикCR:        8.00000000
            case 7: sResRef = "zombtyrant001";    break; //Зомби-тиранCR:        9.00000000
            case 8: sResRef = "rand_crea011";     break; //Доберман Черных ястребовCR:       12.00000000
        }
    }
    else if(nStage == 8)
    {
        nRandom = Random(7);
        switch(nRandom)
        {
            case 0: sResRef = "bathorror002";     break; //Ужас битвыCR:       21.00000000
            case 1: sResRef = "allip001";         break; //Призрак БылогоCR:       19.00000000
            case 2: sResRef = "spectre003";       break; //Страж мертвого городаCR:       26.00000000
            case 3: sResRef = "beholder003";      break; //Молодой свенCR:       20.00000000
            case 4: sResRef = "kokodemon002";     break; //Младший КокадемонCR:       20.00000000
            case 5: sResRef = "mindflayer003";    break; //ИлисидCR:       30.00000000
            case 6: sResRef = "minogon001";       break; //МиногонCR:       20.00000000
        }
    }
    else if(nStage == 9)
    {
        nRandom = Random(7);
        switch(nRandom)
        {
            case 0: sResRef = "wight001";         break; //Умертвие CR:       13.00000000
            case 1: sResRef = "basilisk002";      break; //Болотный аллигаторCR:       12.00000000
            case 2: sResRef = "doomkght001";      break; //Рыцарь рокаCR:       14.00000000
            case 3: sResRef = "rand_crea016";     break; //Костяная ГончаяCR:       12.00000000
            case 4: sResRef = "veter_cr073";      break; //Скелет-лучникCR:       10.00000000
            case 5: sResRef = "gobchiefa006";     break; //Герой лесовиков      13.00000000
            case 6: sResRef = "gobchiefb007";     break; //Герой лесовиков(лучник)      13.00000000
        }
    }
    else if(nStage == 10)
    {
        nRandom = Random(6);
        switch(nRandom)
        {
            case 0: sResRef = "firegreat001";     break; //Большой дух огняCR:       16.00000000
            case 1: sResRef = "rand_crea006";     break; //Железный виверн воинCR:       19.00000000
            case 2: sResRef = "sl_cr_winterwolf"; break; //Зимний волкCR:       12.00000000
            case 3: sResRef = "rand_crea007";     break; //Железная деваCR:       21.00000000
            case 4: sResRef = "horror001";        break; //Крючковатый ужасCR:       16.00000000
            case 5: sResRef = "doomkghtboss002";  break; //Рыцарь рока, командир CR:       17.00000000
        }
    }
    else if(nStage == 11)
    {
        nRandom = Random(7);
        switch(nRandom)
        {
            case 0: sResRef = "umberhulk001";         break; //Коричневый увалень CR:       16.00000000
            case 1: sResRef = "werewolf002";          break; //Волк-оборотень CR:       18.00000000
            case 2: sResRef = "sl_cr_hwarr01";        break; //Молодой Х'варрCR:       22.00000000
            case 3: sResRef = "golstone001";          break; //Каменный голем CR:       18.00000000
            case 4: sResRef = "vito_irilla";          break; //ИриллаCR:       20.00000000
            case 5: sResRef = "vito_smeh";            break; //НечтоCR:       18.00000000
            case 6: sResRef = "sl_cr_elem_ca_01";     break; //Дух пещерCR:       14.00000000
        }
    }
    else if(nStage == 12)
    {
        nRandom = Random(4);
        switch(nRandom)
        {
            case 0: sResRef = "heartetmage";      break; //Пожирательница сердец - магCR:       35.00000000
            case 1: sResRef = "sl_cr_alchemist";  break; //АлхимикCR:       19.00000000
            case 2: sResRef = "kokodemon";        break; //Древний кокадемонCR:       37.00000000
            case 3: sResRef = "lich005";          break; //Древний лич CR:       38.00000000
        }
    }                                                                          //DBM("glad_start", "SelectResRefForNubsArena", "sResRef: " + sResRef);
return sResRef;
}
//------------------------------------------------------------------------------
string SelectResRefForHighArena(int nStage)
{
    string sResRef;
    int nRandom;
    if(nStage == 1)
    {
        nRandom = Random(7);
        switch(nRandom)
        {
            case 0: sResRef = "basilisk002";          break; //Болотный аллигаторCR:       12.00000000
            case 1: sResRef = "firegreat001";         break; //Большой дух огняCR:       16.00000000
            case 2: sResRef = "rand_crea006";         break; //Железный виверн воинCR:       19.00000000
            case 3: sResRef = "sl_cr_winterwolf";     break; //Зимний волкCR:       12.00000000
            case 4: sResRef = "rand_crea007";         break; //Железная деваCR:       21.00000000
            case 5: sResRef = "horror001";            break; //Крючковатый ужасCR:       16.00000000
            case 6: sResRef = "doomkghtboss002";      break; //Рыцарь рока, командир CR:       17.00000000
        }
    }
    else if(nStage == 2)
    {
        nRandom = Random(9);
        switch(nRandom)
        {
            case 0: sResRef = "firehuge002";          break; //Огромный дух огняCR:       25.00000000
            case 1: sResRef = "umberhulk001";         break; //Коричневый увалень CR:       16.00000000
            case 2: sResRef = "werewolf002";          break; //Волк-оборотень CR:       18.00000000
            case 3: sResRef = "sl_cr_hwarr01";        break; //Молодой Х'варрCR:       22.00000000
            case 4: sResRef = "sl_cr_alchemist";      break; //АлхимикCR:       19.00000000
            case 5: sResRef = "golstone001";          break; //Каменный голем CR:       18.00000000
            case 6: sResRef = "vito_irilla";          break; //ИриллаCR:       20.00000000
            case 7: sResRef = "vito_smeh";            break; //НечтоCR:       18.00000000
            case 8: sResRef = "sl_cr_elem_ca_01";     break; //Дух пещерCR:       14.00000000
        }
    }
    else if(nStage == 3)
    {
        nRandom = Random(7);
        switch(nRandom)
        {
            case 0: sResRef = "bathorror002";         break; //Ужас битвыCR:       21.00000000
            case 1: sResRef = "allip001";             break; //Призрак БылогоCR:       19.00000000
            case 2: sResRef = "spectre003";           break; //Страж мертвого городаCR:       26.00000000
            case 3: sResRef = "beholder003";          break; //Молодой свенCR:       20.00000000
            case 4: sResRef = "kokodemon002";         break; //Младший КокадемонCR:       20.00000000
            case 5: sResRef = "mindflayer003";        break; //ИлисидCR:       30.00000000
            case 6: sResRef = "minogon001";           break; //МиногонCR:       20.00000000
        }
    }
    else if(nStage == 4)
    {
        nRandom = Random(3);
        switch(nRandom)
        {
            case 0: sResRef = "sl_cr_en_015";         break; //Кровавый големCR:       20.00000000
            case 1: sResRef = "kokodemon";            break; //Древний кокадемонCR:       37.00000000
            case 2: sResRef = "lich005";              break; //Древний лич CR:       38.00000000
        }
    }
    else if(nStage == 5)
    {
        nRandom = Random(5);
        switch(nRandom)
        {
            case 0: sResRef = "ya_cr241";             break; //Масай - воинCR:       33.00000000
            case 1: sResRef = "sl_cr_n_viper001";     break; //Песчаный гадCR:       18.00000000
            case 2: sResRef = "proraider001";         break; //Продавшийся - рейдерCR:       25.00000000
            case 3: sResRef = "ya_crn013";            break; //Воинствующий илисид CR:       37.00000000
            case 4: sResRef = "yrl_crn001";           break; //Пещерный гоблин CR:       32.00000000
        }
    }
    else if(nStage == 6)
    {
        nRandom = Random(8);
        switch(nRandom)
        {
            case 0: sResRef = "ya_cr231";             break; //Мумия воинаCR:       29.00000000
            case 1: sResRef = "kokodemon";            break; //Древний кокадемонCR:       37.00000000
            case 2: sResRef = "oldchiefb001";         break; //Охотник людей-ящериц CR:       29.00000000
            case 3: sResRef = "earthhuge001";         break; //Огромный дух землиCR:       19.00000000
            case 4: sResRef = "dmvrock002";           break; //Врок CR:       28.00000000
            case 5: sResRef = "waterhuge001";         break; //Огромный дух водыCR:       19.00000000
            case 6: sResRef = "ya_cr256";             break; //Жертва пожирательницCR:       35.00000000
            case 7: sResRef = "oldwarra001";          break; //Воин людей-ящериц CR:       24.00000000
        }
    }
    else if(nStage == 7)
    {
        nRandom = Random(4);
        switch(nRandom)
        {
            case 0: sResRef = "oldchiefa001";         break; //Вождь людей-ящериц CR:       32.00000000
            case 1: sResRef = "ya_cr233";             break; //Мумия князяCR:       41.00000000
            case 2: sResRef = "heartetmage";          break; //Пожирательница сердец - магCR:       35.00000000
            case 3: sResRef = "drider002";            break; //Вармонгер - стрелокCR:       33.00000000
        }
    }
    else if(nStage == 8)
    {
        nRandom = Random(3);
        switch(nRandom)
        {
            case 0: sResRef = "bes_trial_061";        break; //Хозяйка ЖизниCR:       61.00000000
            case 1: sResRef = "heartetmage001";       break; //ХозяйкаCR:       44.00000000
            case 2: sResRef = "golem003";             break; //Алмазный Голем CR:       49.00000000
        }
    }
    else if(nStage == 9)
    {
        nRandom = Random(6);
        switch(nRandom)
        {
            case 0: sResRef = "drider051";            break; //Вармонгер - воинCR:       31.00000000
            case 1: sResRef = "belf001";              break; //БельфигорCR:       39.00000000
            case 2: sResRef = "ya_cr257";             break; //Пожирательница сердецCR:       34.00000000
            case 3: sResRef = "ya_sult001";           break; //Пахлеван СултанатаCR:       40.00000000
            case 4: sResRef = "ya_crn163";            break; //Проклятый мечникCR:       32.00000000
            case 5: sResRef = "mumy002";              break; //Мумия шаманаCR:       32.00000000
        }
    }
    else if(nStage == 10)
    {
        nRandom = Random(5);
        switch(nRandom)
        {
            case 0: sResRef = "ya_cr_mrl_002";        break; //Мурлок - стрелокCR:       37.00000000
            case 1: sResRef = "sl_cr_hwarr02";        break; //Х'варрCR:       37.00000000
            case 2: sResRef = "ya_cr_mrl_003";        break; //Мурлок - колдунCR:       36.00000000
            case 3: sResRef = "ya_crn164";            break; //Великий проклятый мечникCR:       40.00000000
            case 4: sResRef = "driderw002";           break; //Варморген - колдунCR:       32.00000000
        }
    }
    else if(nStage == 11)
    {
        nRandom = Random(7);
        switch(nRandom)
        {
            case 0: sResRef = "ya_cr_mrl_001";        break; //Мурлок - воинCR:       31.00000000
            case 1: sResRef = "mumy001";              break; //Мумия колдунаCR:       37.00000000
            case 2: sResRef = "sl_cr_en_020";         break; //Порождение тьмыCR:       38.00000000
            case 3: sResRef = "ya_cr236";             break; //Заколдованый скелет - поджигательCR:       34.00000000
            case 4: sResRef = "ya_cr234";             break; //Заколдованый скелет - потрошительCR:       34.00000000
            case 5: sResRef = "bes_trial_065";        break; //Страж СтворокCR:       39.00000000
            case 6: sResRef = "scel_001";             break; //Заколдованый скелет - магCR:       37.00000000
        }
    }
    else if(nStage == 12)
    {
        nRandom = Random(3);
        switch(nRandom)
        {
            case 0: sResRef = "sl_cr_theend";         break; //Демон Храд СпайнаCR:      279.00000000
            case 1: sResRef = "ya_cr039";             break; //Х'сан'корCR:       57.00000000
            case 2: sResRef = "bonedrak";             break; //Костяной драконCR:      245.00000000
        }
    }                                                                          //DBM("glad_start", "SelectResRefForHighArena", "sResRef: " + sResRef);
return sResRef;
}
//------------------------------------------------------------------------------
string SelectResRef(int nStage)
{
    if(GetLocalInt(OBJECT_SELF, "NubsArena"))
        return SelectResRefForNubsArena(nStage);
    else
        return SelectResRefForHighArena(nStage);
}
//------------------------------------------------------------------------------
void SetMobApp(object oMob, object oArea, int nTemplateID)
{                                                                              //DBM("glad_start", "SetMobApp", "Start with oMob" + OToS(oMob));
                                                                               //DBM("glad_start", "SetMobApp", "Start with oArea" + OToS(oArea));
                                                                               //DBM("glad_start", "SetMobApp", "Start with nTemplateID" + IToS(nTemplateID));
    int nApp = GetLocalInt(oArea, "GladTemplateApp"+IntToString(nTemplateID)); //DBM("glad_start", "SetMobApp", "nApp" + IToS(nApp));
    if(nApp>6)
        SetCreatureAppearanceType(oMob, nApp);
}
//------------------------------------------------------------------------------
void ClearInv(object oMob, int nDestroy = FALSE)
{
    object oItem = GetFirstItemInInventory(oMob);
    while(GetIsObjectValid(oItem))
    {
        if(nDestroy)
        {
            SetPlotFlag(oItem, FALSE);
            DestroyObject(oItem, 0.01);
        }
        else
            SetDroppableFlag(oItem, FALSE);
        oItem = GetNextItemInInventory(oMob);
    }
}
//------------------------------------------------------------------------------
int SelectMobAppearance(string sRandomResRef)
{                                                                              //DBM("glad_start", "SelectMobAppearance", "START with sRandomResRef: " + sRandomResRef);
    location lLoc = GetLocation(GetObjectByTag("glad_spwn_zone1"));            //DBM("glad_start", "SelectMobAppearance", "lLoc" + OToS(GetAreaFromLocation(lLoc)));
    object oTemp = CreateObject(OBJECT_TYPE_CREATURE, sRandomResRef, lLoc);    //DBM("glad_start", "SelectMobAppearance", "oTemp" + OToS(oTemp));
    int nApp = GetAppearanceType(oTemp);                                       //DBM("glad_start", "SelectMobAppearance", "nApp" + IToS(nApp));
    DestroyObject(oTemp, 0.01);
return nApp;
}
//------------------------------------------------------------------------------
void ManageMobTemplates(int nStage, int nCount, int nFaction)
{                                                                              //DBM("glad_start", "ManageMobTemplates", "Start with nStage" + IToS(nStage));
                                                                               //DBM("glad_start", "ManageMobTemplates", "Start with nCount" + IToS(nCount));
                                                                               //DBM("glad_start", "ManageMobTemplates", "Start with nFaction" + IToS(nFaction));
    int n=1;
    int nFactionNumbers = (nFaction-1)*3;                                      //DBM("glad_start", "ManageMobTemplates", "nFactionNumbers" + IToS(nFactionNumbers));
    while(n<=nCount)
    {
        SetLocalString(OBJECT_SELF, "GladTemplate"+IntToString(nFactionNumbers + n), SelectResRef(nStage));
        SetLocalInt(OBJECT_SELF, "GladTemplateApp"+IntToString(nFactionNumbers + n), SelectMobAppearance(SelectResRef(nStage))); //DBM("glad_start", "ManageMobTemplates", "'GladTemplateApp'+IntToString(nFactionNumbers + n): " + "GladTemplateApp"+IntToString(nFactionNumbers + n));
        n++;
    }
}
//------------------------------------------------------------------------------
void SetRandomTempHP(object oMob)
{
    int nRandom = d20();
    if(nRandom>10)
        ApplyEffectToObject(DURATION_TYPE_PERMANENT, EffectTemporaryHitpoints(FloatToInt(GetMaxHitPoints(oMob)/100.0*nRandom)), oMob);
}
//------------------------------------------------------------------------------
void SetRandomSR(object oMob)
{
    int nRandom = Random(4);//0 - both, 1 - only SR, 2 - only immun, 3 - no effect

    effect eSR = EffectSpellResistanceIncrease(50);
    effect eImmun = EffectSpellLevelAbsorption(4);
    effect eDouble = EffectLinkEffects(eSR, eImmun);
    if(!nRandom)
        ApplyEffectToObject(DURATION_TYPE_PERMANENT, eDouble, oMob);
    else if(nRandom == 1)
        ApplyEffectToObject(DURATION_TYPE_PERMANENT, eSR, oMob);
    else if(nRandom == 2)
        ApplyEffectToObject(DURATION_TYPE_PERMANENT, eImmun, oMob);
}
//------------------------------------------------------------------------------
void GladSpawnMob(int nStage, int nFaction, string sDoorPrefix = "glad_door_", object oArea = OBJECT_SELF)
{                                                                               //DBM("sl_s_glad_start", "GladSpawnMob", "Start with nStage" + IToS(nStage));
                                                                                //DBM("sl_s_glad_start", "GladSpawnMob", "Start with nFaction" + IToS(nFaction));
                                                                                //DBM("sl_s_glad_start", "GladSpawnMob", "Start with sDoorPrefix: " + sDoorPrefix);
                                                                                //DBM("sl_s_glad_start", "GladSpawnMob", "Start with oArea" + OToS(oArea));
    object oTop = GetObjectByTag("glad_top"+IntToString(nFaction));
    int nTimePassed = GetLocalInt(oTop, "TimePassed");
    int nMobCount;

    if((nTimePassed>=150) || (!(nStage%4) && (nTimePassed>5)))
    {                                                                           //ArenaDebug("CloseDoors; nTimePassed>=150; Faction: "+IntToString(nFaction));
        //CloseDoors
        GladDoorAction(nStage, nFaction);
        //Kill Templates
        DestroyTemplates(nFaction);

        //SendMessageToGladiators("Добейте оставшихся тварей до конца раунда, или вы проиграете!", nFaction);
    }
    else
    {
        //Select door
        int nDoorNumber;
        if(sDoorPrefix == "glad_door_")
            nDoorNumber = (nFaction-1)*4 + (1+Random(4));
        else if(sDoorPrefix == "glad_bigdoor_")
            nDoorNumber = (nFaction-1)*2 + (1+Random(2));                       //DBM("sl_s_glad_start", "GladSpawnMob", "nDoorNumber" + IToS(nDoorNumber));
        object oDoor = GetObjectByTag(sDoorPrefix+IntToString(nDoorNumber));    //DBM("sl_s_glad_start", "GladSpawnMob", "oDoor" + OToS(oDoor));

        //Select template
        int nTemplatesNumber = GetLocalInt(oArea, "Templates"+IntToString(nFaction));           //DBM("sl_s_glad_start", "GladSpawnMob", "nTemplatesNumber" + IToS(nTemplatesNumber));
        int nTemplateID = (nFaction-1)*3 + (1+Random(nTemplatesNumber));                        //DBM("sl_s_glad_start", "GladSpawnMob", "nTemplateID" + IToS(nTemplateID));
        string sTemplateResRef = GetLocalString(oArea, "GladTemplate" + IntToString(nTemplateID));

        //Create mob
        object oMob = CreateObject(OBJECT_TYPE_CREATURE, sTemplateResRef, GetLocation(GetNearestObjectByTag("glad_mob_exit_WP", oDoor)));
        SetPlotFlag(oMob, TRUE);
        ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectVisualEffect(VFX_DUR_CUTSCENE_INVISIBILITY), oMob, 1.0);
        //Change App
        SetMobApp(oMob, oArea, nTemplateID);
        //Change Name
        if(!(nStage%4))
        {
            if(GetLocalInt(GetObjectByTag("glad_arena"), "NubsArena"))
                ApplyEffectToObject(DURATION_TYPE_PERMANENT, EffectTemporaryHitpoints(80), oMob);
            else
                ApplyEffectToObject(DURATION_TYPE_PERMANENT, EffectTemporaryHitpoints(600), oMob);
            SetName(oMob, "Свирепая тварь уровня "+IntToString(nStage));
        }
        else
        {
            SetName(oMob, "Тварь уровня "+IntToString(nStage));
            SetRandomTempHP(oMob);
            SetRandomSR(oMob);
        }
        //Change Portrait
        SetPortraitResRef(oMob, "po_clspalemast_");
        //Set vars here, because CopyObject do not take vars from oSource
        SetLocalInt(oMob, "NO_EXP", TRUE);//NoExp
        SetLocalString(oMob, "SL_AI_DEATH", "sl_s_glad_start");//Set OnDeath script (Give money+spawn new mob)
        //Clear Mob Inventory
        ClearInv(oMob);


        //Give see effects
        int nSee = Random(3);                                                   //DBM("sl_s_glad_start", "GladSpawnMob", "nSee" + IToS(nSee));
        if(nSee == 1)
            ApplyEffectToObject(DURATION_TYPE_PERMANENT, EffectSeeInvisible(), oMob);
        else if(nSee == 2)
            ApplyEffectToObject(DURATION_TYPE_PERMANENT, EffectTrueSeeing(), oMob);

        nMobCount = GetLocalInt(oArea, "Mobs"+IntToString(nFaction));           //DBM("sl_s_glad_start", "GladSpawnMob", "nMobCount" + IToS(nMobCount));
        nMobCount++;                                                            //DBM("sl_s_glad_start", "GladSpawnMob", "nMobCount++" + IToS(nMobCount));
        SetLocalInt(oArea, "Mobs"+IntToString(nFaction), nMobCount);
        DelayCommand(0.5, SetPlotFlag(oMob, FALSE));
    }
}
//------------------------------------------------------------------------------
void GladSpawnMobs(int nStage, int nFaction)
{                                                                               //ArenaDebug("OpenDoors; Faction: "+IntToString(nFaction));
    string sDoorPrefix = GladDoorAction(nStage, nFaction, TRUE);
    int nPCs = GetLocalInt(OBJECT_SELF, IntToString(nFaction));
    int i, nTemp=0;

    if(!(nStage%4))//boss every 4th level
    {
        SetLocalInt(OBJECT_SELF, "Free", TRUE);
        SendMessageToGladiators("Отдых разрешен!", nFaction);

        nTemp = 2+Random(2);
        if(nTemp<nPCs)
            nPCs = nTemp;
        nPCs--;//to spawn correct number of bosses
    }
    else
        DeleteLocalInt(OBJECT_SELF, "Free");//Disable rest

    do{
        GladSpawnMob(nStage, nFaction, sDoorPrefix);
        i++;
    }while(i<=nPCs);


    if(nTemp)//for boss levels
    {                                                                           //ArenaDebug("CloseBossDoors; Faction: "+IntToString(nFaction));
        GladDoorAction(nStage, nFaction);
    }
}
//------------------------------------------------------------------------------






////////////////////////////////////////////////////////////////////////////////
//////////////////////////////    CLOCK    /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void NullifyClock(object oTimer, object oTop)
{                                                                               //ShowPosition(oTop, "NullifyClock, oTop");
    if(GetDistanceBetween(oTimer, oTop)>10.0)
    {                                                                           //ShowPosition(oTimer, "NullifyClock, oTimer");
        location lLoc = DistantLocation(0.2, 270.0, GetLocation(oTop), 90.0);
        object oNewTimer = CreateObject(OBJECT_TYPE_PLACEABLE, "sl_pl_dialoguer", lLoc); //ShowPosition(oNewTimer, "NullifyClock, oNewTimer");
        SetLocalObject(oTop, "Timer", oNewTimer);
        SetPlotFlag(oTimer, FALSE);
        DestroyObject(oTimer, 0.01);
    }
}
//------------------------------------------------------------------------------
void ApplyBeams(object oTimer, object oTop, object oBottom, int nTimePassed=0)
{
    ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectBeam(VFX_BEAM_BLACK, oTop, BODY_NODE_CHEST), oTimer, 5.0);
    if(nTimePassed<150)
        ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectBeam(VFX_BEAM_HOLY, oBottom, BODY_NODE_CHEST), oTimer, 5.0);
    else
        ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectBeam(VFX_BEAM_EVIL, oBottom, BODY_NODE_CHEST), oTimer, 5.0);
}
//------------------------------------------------------------------------------
object MoveTimer(object oTimer)
{
    location lTimerLoc = DistantLocation(0.266, 270.0, GetLocation(oTimer), 90.0);
    object oNewTimer = CreateObject(OBJECT_TYPE_PLACEABLE, "sl_pl_dialoguer", lTimerLoc);  //ShowPosition(oNewTimer, "MoveTimer, oNewTimer");
    SetPlotFlag(oTimer, FALSE);
    DestroyObject(oTimer, 0.01);
return oNewTimer;
}
//------------------------------------------------------------------------------
void StartClock(int nFaction)
{                                                                               //ArenaDebug("StartClock of faction: "+IntToString(nFaction));
    object oArea = GetObjectByTag("glad_arena");
    string sID = IntToString(nFaction);
    object oTop = GetLocalObject(oArea, "Top"+ sID);  //ShowPosition(oTop, "StartClock, oTop");

    object oTimer = GetLocalObject(oTop, "Timer");    //ShowPosition(oTimer, "StartClock, oTimer");
    object oBottom = GetLocalObject(oTop, "Bottom");  //ShowPosition(oBottom, "StartClock, oBottom");

    //Put Timer to init position
    NullifyClock(oTimer, oTop);
    //Beams
    ApplyBeams(oTimer, oTop, oBottom);
    //start timer movement
    ExecuteScript("sl_s_glad_start", oTop);//Start timer move
}

//------------------------------------------------------------------------------
void DestroyClock(string sFaction)
{                                                                               //ArenaDebug("DestroyClock of faction: "+sFaction);
    object oArea = GetObjectByTag("glad_arena");
    object oTop = GetLocalObject(oArea, "Top"+ sFaction);
    object oTimer = GetLocalObject(oTop, "Timer");
    object oBottom = GetLocalObject(oTop, "Bottom");

    SetPlotFlag(oTimer, FALSE);
    DestroyObject(oTimer, 0.1);
    SetPlotFlag(oBottom, FALSE);
    DestroyObject(oBottom, 0.1);
    SetPlotFlag(oTop, FALSE);
    DestroyObject(oTop, 0.1);
}
//------------------------------------------------------------------------------
void CreateClock(int nFaction)
{                                                                               //ArenaDebug("CreateClock of faction: "+IntToString(nFaction));
    object oBottom, oTop, oTimer, oArea = GetObjectByTag("glad_arena"); //OBJECT_SELF;
    string sID = IntToString(nFaction);
    object oWP = GetObjectByTag("wp_glad_clock"+sID);
    location lLoc;

    //bottom
    lLoc = DistantLocation(12.0, 270.0, GetLocation(oWP));
    oBottom = CreateObject(OBJECT_TYPE_PLACEABLE, "sl_pl_dialoguer", lLoc);     //ShowPosition(oBottom, "CreateClock, oBottom");
    //ApplyEffectToObject(DURATION_TYPE_PERMANENT, EffectCutsceneGhost(), oBottom);
    SetPlotFlag(oBottom, TRUE);

    //top
    lLoc = DistantLocation(12.0, 90.0, GetLocation(oWP));
    oTop = CreateObject(OBJECT_TYPE_PLACEABLE, "sl_pl_dialoguer", lLoc, FALSE, "glad_top"+sID);   //ShowPosition(oTop, "CreateClock, oTop");
    //ApplyEffectToObject(DURATION_TYPE_PERMANENT, EffectCutsceneGhost(), oTop);
    SetPlotFlag(oTop, TRUE);

    //timer
    lLoc = DistantLocation(11.8, 90.0, GetLocation(oWP), 90.0);
    oTimer = CreateObject(OBJECT_TYPE_PLACEABLE, "sl_pl_dialoguer", lLoc);//the only invisible creature in pallet
                                                                                //ShowPosition(oTimer, "CreateClock, oTimer");
    //misc
    SetLocalObject(oArea, "Top"+ sID, oTop);
    SetLocalObject(oTop, "Bottom", oBottom);
    SetLocalObject(oTop, "Timer", oTimer);

    //main func
    StartClock(nFaction);
}
//------------------------------------------------------------------------------



////////////////////////////////////////////////////////////////////////////////
//////////////////////////////    SYSTEM   /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void CheckPlayersOnArena()
{
    int nBLUE, nRED;
    object oPC = GetFirstObjectInArea(OBJECT_SELF);
    while(GetIsObjectValid(oPC))
    {
        if(GetIsPC(oPC) && !GetIsDM(oPC))
        {
            if(GetIdFaction(oPC) == 1)
                nBLUE++;
            else if(GetIdFaction(oPC) == 2)
                nRED++;
        }
        oPC = GetNextObjectInArea(OBJECT_SELF);
    }
    SetLocalInt(OBJECT_SELF, "1", nBLUE);
    SetLocalInt(OBJECT_SELF, "2", nRED);
}
//------------------------------------------------------------------------------
void DestroyTemplates(int nFaction)
{                                                                               //DBM("sl_s_glad_start", "DestroyTemplates", "START with nFaction" + IToS(nFaction));
    object oArea = GetObjectByTag("glad_arena");                                //DBM("sl_s_glad_start", "DestroyTemplates", "oArea" + OToS(oArea));
    //object oTemplate;
    int i, nID = 1 + (nFaction-1)*3;                                            //DBM("sl_s_glad_start", "DestroyTemplates", "nID" + IToS(nID));
    for(i = nID; i<= (nID+2); i++)
    {                                                                           //DBM("sl_s_glad_start", "DestroyTemplates", "i in loop" + IToS(i));
        DeleteLocalString(oArea, "GladTemplate"+IntToString(i));
        DeleteLocalInt(oArea, "GladTemplateApp"+IntToString(i));
    }
}
//------------------------------------------------------------------------------
void StartStageForFaction(int nStage, int nFaction)
{                                                                               //ArenaDebug("StartStage: " + IntToString(nStage) + " ForFaction: " + IntToString(nFaction));
    object oArea = OBJECT_SELF;
    int nPCs, nMobCount, nMobResRefs = Random(3)+1;
    SetLocalInt(oArea, "Templates"+IntToString(nFaction), nMobResRefs);

    //Create templates
    ManageMobTemplates(nStage, nMobResRefs, nFaction);

    //Spawn mobs
    GladSpawnMobs(nStage, nFaction);
}
//------------------------------------------------------------------------------
void FinishContestForFaction(int nFaction)
{                                                                               //ArenaDebug("FinishContestForFaction: " + IntToString(nFaction));
    object oArea = GetObjectByTag("glad_arena");
    int nPCFaction;
    object oPC = GetFirstPC();
    while(GetIsObjectValid(oPC))
    {
        if(!GetIsDM(oPC))
        {
            if(GetArea(oPC) == oArea)
            {
                nPCFaction = GetIdFaction(oPC);
                if(nPCFaction == nFaction)
                {
                    SendMessageToPC(oPC, "Вы не успели добить всех тварей на арене, поэтому проиграли!");
                    ApplyEffectToObject(DURATION_TYPE_INSTANT, EffectDamage(10000, DAMAGE_TYPE_MAGICAL), oPC);
                }
            }
        }
        oPC = GetNextPC();
    }

    string sID = IntToString(nFaction);
    DeleteLocalInt(oArea, "Templates"+sID);
    DeleteLocalInt(oArea, "Mobs"+sID);

    //Kill mobs on arena
    object oWP = (nFaction==1) ? GetObjectByTag("glad_arena_enter_WP") : GetObjectByTag("glad_arena_enter_WP2");
    location lLoc = GetLocation(oWP);
    object oMob = GetFirstObjectInShape(SHAPE_SPHERE, 35.0, lLoc);
    while(GetIsObjectValid(oMob))
    {
        if(GetLocalString(oMob, "SL_AI_DEATH") != "")
            DestroyObject(oMob, 5.0);

        oMob = GetNextObjectInShape(SHAPE_SPHERE, 35.0, lLoc);
    }

    //CloseDoors
    int nStage = GetLocalInt(oArea, "ContestStage");                            //ArenaDebug("CloseDoors in FinishContestForFaction: " + IntToString(nFaction));
    GladDoorAction(nStage, nFaction);
    //Kill Templates
    DestroyTemplates(nFaction);

    //Destroy Clock
    DestroyClock(sID);
}
//------------------------------------------------------------------------------
void ResetArena(int nStage, object oArea = OBJECT_SELF)
{                                                                               //ArenaDebug("Reset!");
    object oMod = GetModule();

    FinishContestForFaction(1);
    FinishContestForFaction(2);

    float fDelay = (12 - nStage)>0 ? (12 - nStage)*120.0 : 0.0;//3min = 180, but 120 is set for more safetiness
    DelayCommand(fDelay, DeleteLocalInt(oMod, "GladArenaStarted"));

    DeleteLocalInt(oArea, "ContestStage");

    DeleteLocalInt(oArea, "1");//Players of faction Valiostr
    DeleteLocalInt(oArea, "2");//     - || -        Insanna

    if(GetLocalInt(oArea, "NubsArena"))
        DeleteLocalInt(oArea, "NubsArena");
    else
        SetLocalInt(oArea, "NubsArena", TRUE);

}
//------------------------------------------------------------------------------


















void main()
{
    object oArea, oPC;
    int nStage;
    int nFaction;
    string sSelfTag = GetTag(OBJECT_SELF);                                      //DBM("sl_s_glad_start", "", "sSelfTag: " + sSelfTag);

//--Give-arrows-to-arcans-------------------------------------------------------
    if(sSelfTag == "for_arcans")
    {                                                                           //DBM("sl_s_glad_start", "for_arcans", "");
        oPC = GetLastUsedBy();
        int nLevel = GetLevelByClass(CLASS_TYPE_ARCANE_ARCHER, oPC);            //DBM("sl_s_glad_start", "for_arcans", "nLevel"+ IToS(nLevel));
        if(nLevel>=5)
        {
            if(nLevel>=20)
            {
                CreateItemOnObject("arc_arr_21_1", oPC, 25, "arena_arrows");
                CreateItemOnObject("arc_arr_21_2", oPC, 25, "arena_arrows");
                CreateItemOnObject("arc_arr_21_3", oPC, 25, "arena_arrows");
                CreateItemOnObject("arc_arr_21_4", oPC, 25, "arena_arrows");
            }
            else if(nLevel>=15)
                CreateItemOnObject("arc_arr_16", oPC, 99, "arena_arrows");
            else  //nLevel>=5
                CreateItemOnObject("arc_arr_10", oPC, 99, "arena_arrows");

            FloatingTextStringOnCreature("Вы наполнили колчан стрелами!", oPC);
            SetUseableFlag(OBJECT_SELF, FALSE);
            DelayCommand(180.0, SetUseableFlag(OBJECT_SELF, TRUE));
        }
    return;
    }
//--Glad_watchers---------------------------------------------------------------
    if(sSelfTag == "glad_watcher")
    {
        object oWatcher = OBJECT_SELF;
        if(GetLocalInt(GetModule(), "GladArenaStarted"))
        {
            string sFaction = GetLocalString(oWatcher, "Faction");
            if(sFaction == "")//Faction count part
            {
                object oWP1 = GetObjectByTag("glad_arena_enter_WP");
                object oWP2 = GetObjectByTag("glad_arena_enter_WP2");
                if(GetDistanceBetween(oWP1, oWatcher)<GetDistanceBetween(oWP2, oWatcher))
                {
                    sFaction = "1";
                    SetLocalString(oWatcher, "Faction", "1");
                }
                else
                {
                    sFaction = "2";
                    SetLocalString(oWatcher, "Faction", "2");
                }
            }//Faction count part

            oArea = GetObjectByTag("glad_arena");
            if(GetLocalInt(oArea, sFaction))//Animation part
            {
                if(GetLocalInt(oArea, "Mobs"+sFaction))
                {
                    if(!Random(3))
                        PlayVoiceChat(Random(4), OBJECT_SELF);//VOICE_CHAT_ATTACK + VOICE_CHAT_BATTLECRY1 - 3
                }
                PlayAnimation(Random(3)+109); //ANIMATION_FIREFORGET_VICTORY1 - 3
            }
        }
        DelayCommand(IntToFloat(20+Random(20)), ExecuteScript("sl_s_glad_start", oWatcher));
    return;
    }
//--Give Ticket Script----------------------------------------------------------
    if(sSelfTag == "glad_manager")
    {
        oPC = GetPCSpeaker();
        if(GetLocalInt(oPC, "GladQuest"))
        {
            object oBook = GetItemPossessedBy(oPC, "sl_it_ass_book");
            if(GetIsObjectValid(oBook))
            {
                SetPlotFlag(oBook, FALSE);
                DestroyObject(oBook, 0.1);
                CreateItemOnObject("sl_it_glad_doc", oPC);
                DeleteLocalInt(oPC, "GladQuest");
                return;
            }
            else
                FloatingTextStringOnCreature("У вас нет нужного предмета!", oPC);

        }
        if(GetGold(oPC)>= 10000)
        {
            TakeGoldFromCreature(10000, oPC, TRUE);
            CreateItemOnObject("sl_it_glad_doc", oPC);
        }
        else
            FloatingTextStringOnCreature("У вас нет нужной суммы!", oPC);

    return;
    }

//--Timer movement--------------------------------------------------------------
    if(GetResRef(OBJECT_SELF) == "sl_pl_dialoguer")//this should be the separate script, but we are limited in resources
    {                                                                           //ArenaDebug("Timer movement, tag: " + GetTag(OBJECT_SELF));
        object oTop = OBJECT_SELF;                                              //ShowPosition(oTop, "MAIN, oTop");
        object oTimer = GetLocalObject(oTop, "Timer");                          //ShowPosition(oTimer, "MAIN, oTimer");
        object oBottom = GetLocalObject(oTop, "Bottom");                        //ShowPosition(oBottom, "MAIN, oBottom");

        object oMovedTimer = MoveTimer(oTimer);                                 //ShowPosition(oMovedTimer, "MAIN, oMovedTimer");
        SetLocalObject(oTop, "Timer", oMovedTimer);

        int nTimePassed = GetLocalInt(oTop, "TimePassed");
        nTimePassed +=2;
        if(nTimePassed >= 180)
            DeleteLocalInt(oTop, "TimePassed");
        else
        {
            ApplyBeams(oMovedTimer, oTop, oBottom, nTimePassed);
            SetLocalInt(oTop, "TimePassed", nTimePassed);
            DelayCommand(2.0, ExecuteScript("sl_s_glad_start", oTop));
        }
        return;
    }
//--Mob Custom DeathScript------------------------------------------------------
    if(GetObjectType(OBJECT_SELF) == OBJECT_TYPE_CREATURE)//this should be the separate script, but we are limited in resources
    {
        //SendMessageToAllDMs("Custom DeathScript Enter");
        //on mob death
        nFaction = GetIdFaction(GetNearestPCnotDM(OBJECT_SELF));  //SendMessageToAllDMs("nFaction: " + IntToString(nFaction));
        oArea = GetObjectByTag("glad_arena");
        nStage = GetLocalInt(oArea, "ContestStage");    //SendMessageToAllDMs("nStage: " + IntToString(nStage));

        //Destroy ground loot
        DestroyGroundLoot(GetLocation(OBJECT_SELF));

        //give money
        GiveRewardToFaction(nStage, nFaction);

        //Minus mob
        string sFaction = IntToString(nFaction);
        SetLocalInt(oArea, "Mobs"+sFaction, GetLocalInt(oArea, "Mobs"+sFaction)-1); //DBM("sl_s_glad_start", "", "Mobs"+sFaction + IToS(GetLocalInt(oArea, "Mobs"+sFaction)));

        //run next mob
        DelayCommand(0.5, GladSpawnMob(nStage, nFaction, "glad_door_", oArea));
        return;
    }
//--Trigger script. Do not allow players to exit the boss_doors ----------------
    if(GetObjectType(OBJECT_SELF) == OBJECT_TYPE_TRIGGER)//this should be the separate script, but we are limited in resources
    {
        oPC = GetEnteringObject();
        if(GetIsPC(oPC))
        {
            string sCenterWP = "glad_arena_enter_WP";
            if(GetIdFaction(oPC) == 2)
                sCenterWP = "glad_arena_enter_WP2";

            SetCutsceneMode(oPC);
            DelayCommand(0.1, AssignCommand(oPC, ClearAllActions(TRUE)));
            DelayCommand(0.2, AssignCommand(oPC, JumpToObject(GetObjectByTag(sCenterWP))));
            DelayCommand(0.4, SetCutsceneMode(oPC, FALSE));
        }
        return;
    }
//--Arena Exit through Big door-------------------------------------------------
    if(GetStringLeft(GetTag(OBJECT_SELF), 12) == "glad_bigdoor")
    {
        oPC = GetClickingObject();
        if(!GetLocalInt(GetModule(), "GladArenaStarted"))
        {
            int nPCFaction = GetIdFaction(oPC);
            if(nPCFaction == 1)
                AssignCommand(oPC, JumpToObject(GetObjectByTag("TEMLE_1")));
            else if(nPCFaction == 2)
                AssignCommand(oPC, JumpToObject(GetObjectByTag("OUTLAW_WP")));

            DelayCommand(3.0, MakeWeaponDropable(oPC));
        }
    return;
    }
//------------------------------------------------------------------------------




    oArea = OBJECT_SELF;
//--Arena Messages Part---------------------------------------------------------
    int nMessage = GetLocalInt(oArea, "Message");//Number of message about GladArena
                                                                                //DBM("sl_s_glad_start", "string 1131", "nMessage"+IToS(nMessage));
    if(nMessage)//This part shows arena messages
    {
        object oMod = GetModule();
        int nArenaForNubs = GetLocalInt(oArea, "NubsArena");

        if(nMessage == 1)
        {
            if(nArenaForNubs)
                SendMessageToAllPC("Арена для НАЧИНАЮЩИХ гладиаторов откроется через 10 минут!", TRUE);
            else
                SendMessageToAllPC("Арена гладиаторов откроется через 10 минут!", TRUE);

            SetLocalInt(oArea, "Message", 2);//Switch to next message
            DelayCommand(300.0, ExecuteScript("sl_s_glad_start", oArea));
            return;
        }
        if(nMessage == 2)
        {
            if(nArenaForNubs)
                SendMessageToAllPC("Арена для НАЧИНАЮЩИХ гладиаторов откроется через 5 минуты!", TRUE);
            else
                SendMessageToAllPC("Арена гладиаторов откроется через 5 минуты!", TRUE);

            SetLocalInt(oArea, "Message", 3);//Switch to next message
            DelayCommand(300.0, ExecuteScript("sl_s_glad_start", oArea));
            return;
        }
        if(nMessage == 3)
        {
            SetLocalInt(oMod, "GladArenaStarted", TRUE);
            if(nArenaForNubs)
                SendMessageToAllPC("Арена для НАЧИНАЮЩИХ гладиаторов ОТКРЫТА! Бои начнутся через 2 минуты!", TRUE);
            else
                SendMessageToAllPC("Арена гладиаторов ОТКРЫТА! Бои начнутся через 2 минуты!", TRUE);

            SetLocalInt(oArea, "Free", TRUE);
            DeleteLocalInt(oArea, "Message");
            DeleteLocalInt(oArea, "1");//Players of faction Valiostr
            DeleteLocalInt(oArea, "2");//     - || -        Insanna

            float fEnterAllowedDelay = 120.0;
            SetLocalInt(oArea, "EnterAllowed", TRUE);
            DelayCommand(fEnterAllowedDelay-5.0, DeleteLocalInt(oArea, "EnterAllowed"));
            DelayCommand(fEnterAllowedDelay-5.0, SendMessageToAllPC("Вход на Арену гладиаторов закрыт.", TRUE));

            DelayCommand(fEnterAllowedDelay, SendMessageToAllPC("Гладиаторские бои начались!", TRUE));
            DelayCommand(fEnterAllowedDelay, ExecuteScript("sl_s_glad_start", oArea));//Already spawn first part of mobs
        }
    return;
    }
//------------------------------------------------------------------------------








    //MAIN SCRIPT
    DeleteLocalInt(OBJECT_SELF, "BG");//enable Time Stop for mobs

    int nFinish1, nFinish2;
    nStage = GetLocalInt(oArea, "ContestStage");

    if(GetLocalInt(oArea, "Mobs1") || (nStage>=12))//some mobs rest on arena or last(12) stage had passed
    {                                                                           //ArenaDebug("[Mobs1>0||nStage>=12]");
        nFinish1 = TRUE;
        FinishContestForFaction(1); //finish contest for Valiostr // TEMLE_1
    }
    if(GetLocalInt(oArea, "Mobs2") || (nStage>=12))//some mobs rest on arena or last(12) stage had passed
    {                                                                           //ArenaDebug("[Mobs2>0||nStage>=12]");
        nFinish2 = TRUE;
        FinishContestForFaction(2); //finish contest for Insanna // OUTLAW_WP
    }

    CheckPlayersOnArena();//Set vars "1"(BLUE) and "2"(RED)
    nStage++;

    if(GetLocalInt(oArea, "1") && !nFinish1)
    {                                                                           //ArenaDebug("[1&&nFinish1]");
        if(nStage == 1)
            CreateClock(1);
        else
            StartClock(1);

        DelayCommand(0.5, StartStageForFaction(nStage, 1));
    }
    else
        nFinish1 = TRUE;

    if(GetLocalInt(oArea, "2") && !nFinish2)
    {                                                                           //ArenaDebug("[2&&!nFinish2]");
        if(nStage == 1)
            CreateClock(2);
        else
            StartClock(2);

        DelayCommand(0.5, StartStageForFaction(nStage, 2));
    }
    else
        nFinish2 = TRUE;

    if(nFinish1 && nFinish2)//Finish contest
    {
        ResetArena(nStage);
        return;
    }

    SetLocalInt(oArea, "ContestStage", nStage);                                 //ArenaDebug("Stage began|| ");
    //DelayCommand(180.0, /*Сообщение "До конца раунда осталась 1 минута!"*/);


    DelayCommand(150.0, SendMessageToGladiators("Добейте оставшихся тварей до конца раунда, или вы проиграете!", 1));
    DelayCommand(150.0, SendMessageToGladiators("Добейте оставшихся тварей до конца раунда, или вы проиграете!", 2));
    DelayCommand(150.0, SetLocalInt(OBJECT_SELF, "BG", 1)); //disable Time Stop for last 30 sec of round
    DelayCommand(185.0, ExecuteScript("sl_s_glad_start", OBJECT_SELF));
}
