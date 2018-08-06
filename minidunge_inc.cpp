//bZ 07.2015

#include "sl_s_inc2"
#include "x2_inc_toollib"
#include "epqst_inc"

/*
const string CRED = "<cя  >";
const string CYELLOW = "<cяя >";
const string CWHITE = "<cяяя>";
const string CMAGENTA = "<cя я>";
const string CCYAN = "<c яя>";
const string CGREEN = "<c я >";
const string CBLUE = "<c  я>";
*/

const int MAX_PC_LEVEL = 20;
const int MIN_PC_LEVEL = 10;

//VSHW----
const int CODE_LEN = 8;


//WRM----
const string WRM_ROOM_1 = "51_50_60_70_71_61_";
const string WRM_ROOM_2 = "62 72 73_";
const string WRM_ROOM_3 = "23 33 43 53 63_";
const string WRM_ROOM_4 = "10 11 12 13_";
const string WRM_ROOM_5 = "00 01 02 03 04_";
const string WRM_ROOM_6 = "14 24 34 44 54 64_";
const string WRM_ROOM_7 = "74 75 65 55 45 35_";
const string WRM_ROOM_8 = "25 26 16 15 05 06 07_";
const string WRM_ROOM_9 = "17 27 28 18 08 09 19_";
const string WRM_ROOM_10 = "29 39 38 37 36_";
const string WRM_ROOM_11 = "46 56 66 76 77 78_";


const string WRM_EXIT_POINT = "WP_wrm_dunge_exit";
const string WRM_WYRMLING = "wrm_wyrmling";




int GetAllThePCsInAreaPassedTheTrigger(object oDoor);

object GetDoor(int nNumber = 0);

object CreateInvisiblePlaceable(location lLoc);

void GarantyDestroyObject(object oToDestroy, float fDelay = 0.0);

//ACHTUNG! Because of a mistake in Bioware functions, this function can be used only when OBJECT_SELF is an Area
//Otherwise you should use your own function with necessary corrections instead of Bioware
void FillTheArea(int nEffect, float fZOffset, float fZOffsetMax = 8.0, float fStep = 0.5, float fDelay = 2.0, object oArea = OBJECT_SELF);

void ApplyBeamToLocation(int nBeam, location lTarget, object oEffector, float fTime = 1.0);

void MassScreenShake(object oArea, int nEffect = VFX_FNF_SCREEN_SHAKE);

void MassBlackScreen(object oArea, float fDuration);

int GetToolsetMapRow(location lLoc);

int GetToolsetMapColumn(location lLoc);

void FillAreaBlock(object oArea, int nRow, int nColumn, float fZOffset, int nGroundEffect);


// Create an object of the specified type at lLocation.
// - nObjectType: OBJECT_TYPE_ITEM, OBJECT_TYPE_CREATURE, OBJECT_TYPE_PLACEABLE,
//   OBJECT_TYPE_STORE, OBJECT_TYPE_WAYPOINT
// - sTemplate
// - lLocation
// - bUseAppearAnimation
// - sNewTag - if this string is not empty, it will replace the default tag from the template
void CreateObjectVoid(int nObjectType, string sTemplate, location lLocation, int bUseAppearAnimation=FALSE, string sNewTag="");


void MiniDunge_ClearInventory(object oObject);

// Function may be not finished! Should be checked before usage.
// Returns: 0 if the saving throw roll failed
// Returns: 1 if the saving throw roll succeeded
// - nType: SAVING_THROW_FORT, SAVING_THROW_REFLEX, SAVING_THROW_WILL
int DoFakeSavingThrow(object oCreature, int nType, int nDC, object oSaveVersus = OBJECT_SELF);


void HidePlaceable(object oPlaceable, float fSeconds = 0.0);

void UnhidePlaceable(object oPlaceable);

void LitAreaBlock(object oArea, int nX, int nY, int nMainColor = TILE_MAIN_LIGHT_COLOR_PALE_YELLOW, int nSourceColor = TILE_SOURCE_LIGHT_COLOR_PALE_YELLOW);

// LIT FUNCTIONS DO NOT WORK!
void LitTheArea(object oArea, int nMainColor = TILE_MAIN_LIGHT_COLOR_PALE_YELLOW, int nSourceColor = TILE_SOURCE_LIGHT_COLOR_PALE_YELLOW);


////////////////////////////////////////////////////////////////////////////////
//-UNIVERSAL--------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////


//A correct variant of the Bioware function
void TLResetAreaGroundTilesEx_Corr(object oArea)
{
    TLResetAreaGroundTiles(oArea, GetAreaSize(AREA_WIDTH, oArea), GetAreaSize(AREA_HEIGHT, oArea));
}
//------------------------------------------------------------------------------
//A correct variant of the Bioware function
void TLChangeAreaGroundTilesEx_Corr(object oArea, int nGroundTileConst, float fZOffset = -0.4f )
{
    TLChangeAreaGroundTiles(oArea, nGroundTileConst, GetAreaSize(AREA_WIDTH, oArea), GetAreaSize(AREA_HEIGHT, oArea), fZOffset );
}
//------------------------------------------------------------------------------
int GetAllThePCsInAreaPassedTheTrigger(object oDoor)
{
    int nStop;
    object oWP = GetNearestObject(OBJECT_TYPE_WAYPOINT, oDoor);
    object oArea = GetArea(OBJECT_SELF);

    object oPC = GetFirstPC();
    while(GetIsObjectValid(oPC) && !nStop)
    {
        if((GetArea(oPC) == oArea) && !GetIsDM(oPC))
        {
            if(GetDistanceBetween(oPC, oDoor)<GetDistanceBetween(oPC, oWP))
                nStop = TRUE;
        }
        oPC = GetNextPC();
    }
return !nStop;
}
//------------------------------------------------------------------------------
object GetDoor(int nNumber = 0)
{
    string sVarName = "DoorTag";
    if(nNumber>1)
        sVarName += IntToString(nNumber);

return GetObjectByTag(GetLocalString(OBJECT_SELF, sVarName));
}
//------------------------------------------------------------------------------
object CreateInvisiblePlaceable(location lLoc)
{                                                                               //DBM("minidunge_inc", "CreateInvisiblePlaceable", "Start with" + OToS(GetAreaFromLocation(lLoc)));
    object oInv = CreateObject(OBJECT_TYPE_PLACEABLE, "sl_pl_dialoguer", lLoc); //DBM("minidunge_inc", "CreateInvisiblePlaceable", "oInv" + OToS(oInv));
    return oInv;
}
//------------------------------------------------------------------------------
void GarantyDestroyObject(object oToDestroy, float fDelay = 0.0)
{
    SetPlotFlag(oToDestroy, FALSE);
    SetImmortal(oToDestroy, FALSE);
    AssignCommand(oToDestroy, SetIsDestroyable(TRUE));

    DestroyObject(oToDestroy, fDelay);
}
//------------------------------------------------------------------------------
void FillTheArea(int nEffect, float fZOffset, float fZOffsetMax = 8.0, float fStep = 0.5, float fDelay = 2.0, object oArea = OBJECT_SELF)
{
    TLResetAreaGroundTilesEx_Corr(oArea);
    TLChangeAreaGroundTilesEx_Corr(oArea, nEffect, fZOffset);
    SetLocalFloat(oArea, "FillLevel", fZOffset);                               //DBM("minidunge_inc", "FillTheArea", "fZOffset" + FToS(fZOffset));

    fZOffset+=fStep;
    if( ((fZOffset<=fZOffsetMax) && (fStep>=0.0))  ||
        ((fZOffset>=fZOffsetMax) && (fStep<0.0))    )
        DelayCommand(fDelay, FillTheArea(nEffect, fZOffset, fZOffsetMax, fStep, fDelay, oArea));
}
//------------------------------------------------------------------------------
void ApplyBeamToLocation(int nBeam, location lTarget, object oEffector, float fTime = 1.0)
{                                                                               //DBM("minidunge_inc", "ApplyBeamToLocation", "Start With nBeam" + IToS(nBeam));
                                                                                //DBM("minidunge_inc", "ApplyBeamToLocation", "Start With lTarget area" + OToS(GetAreaFromLocation(lTarget)));
                                                                                //DBM("minidunge_inc", "ApplyBeamToLocation", "Start With oEffector" + OToS(oEffector));
    object oTarget = CreateInvisiblePlaceable(lTarget);                         //DBM("minidunge_inc", "ApplyBeamToLocation", "Invisible oTarget" + OToS(oTarget));
    ApplyEffectToObject(DURATION_TYPE_PERMANENT, EffectBeam(nBeam, oEffector, BODY_NODE_CHEST), oTarget);
    GarantyDestroyObject(oTarget, fTime);
}
//------------------------------------------------------------------------------
void MassScreenShake(object oArea, int nEffect = VFX_FNF_SCREEN_SHAKE)
{
    object oPC = GetFirstPC();
    while(GetIsObjectValid(oPC))
    {
        if(GetArea(oPC) == oArea)
            ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectVisualEffect(nEffect), oPC, 5.0);

        oPC = GetNextPC();
    }
return;
}
//------------------------------------------------------------------------------
void MassBlackScreen(object oArea, float fDuration)
{
    object oPC = GetFirstPC();
    while(GetIsObjectValid(oPC))
    {
        if(GetArea(oPC) == oArea)
        {
            AssignCommand(oPC, ClearAllActions());
            BlackScreen(oPC);
            DelayCommand(fDuration, StopFade(oPC));
        }
        oPC = GetNextPC();
    }
}
//------------------------------------------------------------------------------
int GetToolsetMapRow(location lLoc)
{
    vector vPos = GetPositionFromLocation(lLoc);
    return FloatToInt(vPos.y / 10);
}
//------------------------------------------------------------------------------
int GetToolsetMapColumn(location lLoc)
{
    vector vPos = GetPositionFromLocation(lLoc);
    return FloatToInt(vPos.x / 10);
}
//------------------------------------------------------------------------------
void FillAreaBlock(object oArea, int nRow, int nColumn, float fZOffset, int nGroundEffect)
{
    vector vPos;
    vPos.x = 5.0 + 10*nColumn;
    vPos.y = 5.0 + 10*nRow;
    vPos.z = fZOffset;
    location lLoc = Location(oArea, vPos, 0.0);

    object oTile = CreateObject(OBJECT_TYPE_PLACEABLE, "plc_invisobj", lLoc,FALSE, "tmp_tile_"+GetResRef(oArea)+ "_" +IntToString(nColumn)+IntToString(nRow));
    SetPlotFlag(oTile,TRUE);
    ApplyEffectToObject(DURATION_TYPE_PERMANENT, EffectVisualEffect(nGroundEffect), oTile);
}
//------------------------------------------------------------------------------
void ResetAreaBlock(object oArea, string sColumnRow)
{
    string sTag = "tmp_tile_"+GetResRef(oArea)+ "_" +sColumnRow;
    object oTile = GetObjectByTag(sTag);
    SetPlotFlag(oTile,FALSE);
    DestroyObject(oTile, 0.1);
}
//------------------------------------------------------------------------------
void CreateObjectVoid(int nObjectType, string sTemplate, location lLocation, int bUseAppearAnimation=FALSE, string sNewTag="")
{
    if(sNewTag != "")
        CreateObject(nObjectType, sTemplate, lLocation, bUseAppearAnimation, sNewTag);
    else
        CreateObject(nObjectType, sTemplate, lLocation, bUseAppearAnimation);
}
//------------------------------------------------------------------------------
void MiniDunge_ClearInventory(object oObject)
{
    object oItem = GetFirstItemInInventory(oObject);
    while(GetIsObjectValid(oItem))
    {
        GarantyDestroyObject(oItem, 0.1);
        oItem = GetNextItemInInventory(oObject);
    }
}
//------------------------------------------------------------------------------
/*
int DoFakeSavingThrow(object oCreature, int nType, int nDC, object oSaveVersus = OBJECT_SELF)
{
    int nSave, nSaveRoll, nResult;
    string sMessage, sType, sResult = "*успех*";
    effect eVis = EffectVisualEffect(VFX_IMP_FORTITUDE_SAVING_THROW_USE);

    switch(nType)
    {
        case SAVING_THROW_FORT:
            nSave = GetFortitudeSavingThrow(oCreature);
            sType = "Стойкости : ";
            break;
        case SAVING_THROW_REFLEX:
            nSave = GetReflexSavingThrow(oCreature);
            sType = "Рефлексам : ";
            break;
        case SAVING_THROW_WILL:
            nSave = GetWillSavingThrow(oCreature);
            sType = "Воле : ";
            break;
    }
    nSaveRoll = d20();
    if ((nSave+nSaveRoll) < nDC)
        sResult = "*неудача*";
    else
        nResult = 1;

    sMessage = (CMAGENTA + GetDeity(oCreature) + " : " + CCYAN + "Спасение по "+ sType + sResult + " : (" + IntToString(nSaveRoll) + " + " + IntToString(nSave) + " = " + IntToString(nSave + nSaveRoll) + " против Класса Сложности: " + IntToString(nDC) + ")");
    SendMessageToPC(oCreature, sMessage);
    SendMessageToPC(oSaveVersus, sMessage);

return nResult;
}*/
//------------------------------------------------------------------------------
void HidePlaceable(object oPlaceable, float fSeconds = 0.0)
{
    if(fSeconds == 0.0)
    {
        ApplyEffectToObject(DURATION_TYPE_PERMANENT, EffectVisualEffect(VFX_DUR_CUTSCENE_INVISIBILITY), oPlaceable);
        ApplyEffectToObject(DURATION_TYPE_PERMANENT, EffectCutsceneGhost(), oPlaceable);
    }
    else
    {
        ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectVisualEffect(VFX_DUR_CUTSCENE_INVISIBILITY), oPlaceable, fSeconds);
        ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectCutsceneGhost(), oPlaceable, fSeconds);
    }
}
//------------------------------------------------------------------------------
void UnhidePlaceable(object oPlaceable)
{
    effect eEff = GetFirstEffect(oPlaceable);
    while(GetIsEffectValid(eEff))
    {                                                                           DBM("mini", "UnhidePlaceable", "eEff" + IToS(GetEffectType(eEff)));
        if(GetEffectType(eEff) == EFFECT_TYPE_VISUALEFFECT || GetEffectType(eEff) == EFFECT_TYPE_CUTSCENEGHOST)
            RemoveEffect(oPlaceable, eEff);
        eEff = GetNextEffect(oPlaceable);
    }
}
//------------------------------------------------------------------------------
void LitAreaBlock(object oArea, int nX, int nY, int nMainColor = TILE_MAIN_LIGHT_COLOR_PALE_YELLOW, int nSourceColor = TILE_SOURCE_LIGHT_COLOR_PALE_YELLOW)
{
    vector vPos;
    vPos.x = 5.0 + 10.0*nX;
    vPos.y = 5.0 + 10.0*nY;
    vPos.z = 0.0;
    location lBlockLoc = Location(oArea, vPos, 0.0);
    AssignCommand(oArea, SetTileMainLightColor(lBlockLoc, nMainColor, nMainColor));
    AssignCommand(oArea, SetTileSourceLightColor(lBlockLoc, nSourceColor, nSourceColor));
}
//------------------------------------------------------------------------------
void LitTheArea(object oArea, int nMainColor = TILE_MAIN_LIGHT_COLOR_PALE_YELLOW, int nSourceColor = TILE_SOURCE_LIGHT_COLOR_PALE_YELLOW)
{
    int i, nX = GetAreaSize(AREA_WIDTH, oArea);
    int j, nY = GetAreaSize(AREA_HEIGHT, oArea);

    for(i = 0; i<nX; i++)
        for(j = 0; j<nY; j++)
            LitAreaBlock(oArea, i, j, nMainColor, nSourceColor);

    DelayCommand(5.0, RecomputeStaticLighting(oArea));
}






////////////////////////////////////////////////////////////////////////////////
//-VISHKI-----------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
object GetStatue(object oTrigger = OBJECT_SELF)
{
    return GetObjectByTag(GetLocalString(oTrigger, "Statue"));
}
//------------------------------------------------------------------------------
void StatueShoot(object oPC, object oStatue = OBJECT_SELF)
{
    int nBeam = GetLocalInt(oStatue, "Beam");
    int nDamType = GetLocalInt(oStatue, "Type");
    int nAmount = GetLocalInt(oStatue, "Amount");
    if(!nAmount)
        nAmount = d6(3);

    ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectBeam(nBeam, oStatue, BODY_NODE_CHEST), oPC, 1.0);
    ApplyEffectToObject(DURATION_TYPE_INSTANT, EffectDamage(nAmount, nDamType), oPC);
}
//------------------------------------------------------------------------------
object GetNearestPCToStatue(object oStatue)
{
    int nPCs = GetNumberOfObjectsInArray(oStatue, "Players");
    if(!nPCs)
        return OBJECT_INVALID;

    if(nPCs == 1)
        return GetObejctFromArrayByPosition(oStatue, "Players", 1);

    object oPC, oNearestPC;
    float fDist, fLowDist;
    int n;
    for(n=1; n<=nPCs; n++)
    {
        oPC = GetObejctFromArrayByPosition(oStatue, "Players", n);
        fDist = GetDistanceBetween(oStatue, oPC);
        if((fLowDist == 0.0) || (fDist<fLowDist))
        {
            fLowDist = fDist;
            oNearestPC = oPC;
        }
    }
return oNearestPC;
}
//------------------------------------------------------------------------------
void FireCheck(object oStatue)
{
    object oPC = GetNearestPCToStatue(oStatue);
    if(GetIsObjectValid(oPC))
    {
        AssignCommand(oStatue, StatueShoot(oPC));
        DelayCommand(2.0, FireCheck(oStatue));
    }
}
//------------------------------------------------------------------------------
void CreateMobs()
{                                                                               //DBM("minidunge_inc", "CreateMobs", "OBJECT_SELF" + OToS(OBJECT_SELF));
    location lLoc1 = GetLocation(GetObjectByTag("WP_vshw_cr_fl2_5"));
    location lLoc2 = GetLocation(GetObjectByTag("WP_vshw_cr_fl2_6"));

    ApplyEffectAtLocation(DURATION_TYPE_INSTANT, EffectVisualEffect(VFX_FNF_SUMMON_MONSTER_1), lLoc1);
    ApplyEffectAtLocation(DURATION_TYPE_INSTANT, EffectVisualEffect(VFX_FNF_SUMMON_MONSTER_1), lLoc2);

    object oMob1 = CreateObject(OBJECT_TYPE_CREATURE, "vshw_cr_fl2_5", lLoc1);  //DBM("minidunge_inc", "CreateMobs", "oMob1" + OToS(oMob1));
    object oMob2 = CreateObject(OBJECT_TYPE_CREATURE, "vshw_cr_fl2_6", lLoc2);  //DBM("minidunge_inc", "CreateMobs", "oMob2" + OToS(oMob2));
    ApplyEffectToObject(DURATION_TYPE_PERMANENT, SupernaturalEffect(EffectSeeInvisible()), oMob1);
    ApplyEffectToObject(DURATION_TYPE_PERMANENT, SupernaturalEffect(EffectSeeInvisible()), oMob2);

    SetLocalObject(OBJECT_SELF, "Mob1", oMob1);
    SetLocalObject(OBJECT_SELF, "Mob2", oMob2);

    object oCenter = GetLocalObject(OBJECT_SELF, "Center");                     //DBM("minidunge_inc", "CreateMobs", "oCenter" + OToS(oCenter));
    ApplyEffectToObject(DURATION_TYPE_PERMANENT, EffectBeam(VFX_BEAM_SILENT_LIGHTNING, oCenter, BODY_NODE_CHEST), oMob1);
    ApplyEffectToObject(DURATION_TYPE_PERMANENT, EffectBeam(VFX_BEAM_SILENT_LIGHTNING, oCenter, BODY_NODE_CHEST), oMob2);
}
//------------------------------------------------------------------------------
void CountPlayers()
{
    object oArea = GetArea(OBJECT_SELF);
    object oPC = GetFirstPC();
    while(GetIsObjectValid(oPC))
    {
        if((GetArea(oPC) == oArea) && !GetIsDM(oPC))
        {
            if(GetDistanceBetween(OBJECT_SELF, oPC)<40.0)
                AddObjectToArray(oPC, OBJECT_SELF, "Players");
        }
        oPC = GetNextPC();
    }
}
//------------------------------------------------------------------------------
object SelectPlayer()
{
    object oPC;
    int nNumberInBase = GetNumberOfObjectsInArray(OBJECT_SELF, "Players");
    if(nNumberInBase)
    {
        int nRandom = Random(nNumberInBase)+1;
        oPC = GetObejctFromArrayByPosition(OBJECT_SELF, "Players", nRandom);
        if(!GetIsObjectValid(oPC) || GetIsDead(oPC) || (GetArea(OBJECT_SELF) != GetArea(oPC)))
        {
            RemoveObjectFromArray(oPC, OBJECT_SELF, "Players");
            oPC = SelectPlayer();
        }
    }
return oPC;
}
//------------------------------------------------------------------------------
void DamageFromBeamExplosion(location lLoc)
{
    object oPC = GetFirstObjectInShape(SHAPE_SPHERE, 1.0, lLoc);
    while(GetIsObjectValid(oPC))
    {
        if(GetIsPC(oPC) && !GetIsDM(oPC))
            ApplyEffectToObject(DURATION_TYPE_INSTANT, EffectDamage(d6(10), DAMAGE_TYPE_ELECTRICAL), oPC);
        oPC = GetNextObjectInShape(SHAPE_SPHERE, 1.0, lLoc);
    }
}
//------------------------------------------------------------------------------
void ElectricBeam(object oPC)
{                                                                               //DBM("minidunge_inc", "ElectricBeam", "Start with oPC" + OToS(oPC));
    location lLoc = GetLocation(oPC);
    location lLocUp = UpLocation(lLoc, 5.0);

    object oCenter = GetLocalObject(OBJECT_SELF, "Center");                     //DBM("minidunge_inc", "ElectricBeam", "oCenter" + OToS(oCenter));
    object oInv1 = CreateInvisiblePlaceable(lLocUp);                            //DBM("minidunge_inc", "ElectricBeam", "oInv1" + OToS(oInv1));
    object oInv2 = CreateInvisiblePlaceable(lLoc);                              //DBM("minidunge_inc", "ElectricBeam", "oInv2" + OToS(oInv2));
    ApplyEffectToObject(DURATION_TYPE_PERMANENT, EffectBeam(VFX_BEAM_LIGHTNING, oCenter, BODY_NODE_CHEST), oInv1);

    DelayCommand(2.0, ApplyEffectToObject(DURATION_TYPE_PERMANENT, EffectBeam(VFX_BEAM_LIGHTNING, oInv1, BODY_NODE_CHEST), oInv2));
    DelayCommand(2.1, ApplyEffectAtLocation(DURATION_TYPE_INSTANT, EffectVisualEffect(VFX_FNF_GAS_EXPLOSION_MIND), lLoc));
    DelayCommand(2.1, DamageFromBeamExplosion(lLoc));
    GarantyDestroyObject(oInv1, 2.4);
    GarantyDestroyObject(oInv2, 2.4);
}
//------------------------------------------------------------------------------
void PowerWave()
{
    ApplyEffectToObject(DURATION_TYPE_INSTANT, EffectVisualEffect(VFX_FNF_HOWL_WAR_CRY), OBJECT_SELF);
    location lLoc = GetLocation(OBJECT_SELF);
    object oMaster, oSummon = GetFirstObjectInShape(SHAPE_SPHERE, 40.0, lLoc);
    while(GetIsObjectValid(oSummon))
    {
        oMaster = GetMaster(oSummon);
        if(GetIsObjectValid(oMaster) && GetIsPC(oMaster))
            DelayCommand(GetDistanceToObject(oSummon)/10.0, ApplyEffectToObject(DURATION_TYPE_INSTANT, EffectDamage(GetCurrentHitPoints(oSummon)+10, DAMAGE_TYPE_ELECTRICAL), oSummon));

        oSummon = GetNextObjectInShape(SHAPE_SPHERE, 40.0, lLoc);
    }
}
//------------------------------------------------------------------------------
void CreateLights(object oObel)
{
    location lLocStart = GetLocation(oObel);
    location lLoc = DistantLocation(1.0, 45.0, lLocStart);
    SetLocalObject(oObel, "Light1", CreateObject(OBJECT_TYPE_PLACEABLE, "pl_vshw_light", lLoc));

    lLoc = DistantLocation(1.0, 135.0, lLocStart);
    SetLocalObject(oObel, "Light2", CreateObject(OBJECT_TYPE_PLACEABLE, "pl_vshw_light", lLoc));

    lLoc = DistantLocation(1.0, 225.0, lLocStart);
    SetLocalObject(oObel, "Light3", CreateObject(OBJECT_TYPE_PLACEABLE, "pl_vshw_light", lLoc));

    lLoc = DistantLocation(1.0, 315.0, lLocStart);
    SetLocalObject(oObel, "Light4", CreateObject(OBJECT_TYPE_PLACEABLE, "pl_vshw_light", lLoc));
}
//------------------------------------------------------------------------------
void DestroyLights(object oObel)
{
    object oLight;
    int n;
    for(n=1; n<=4; n++)
    {
        oLight = GetLocalObject(oObel, "Light"+IntToString(n));
        GarantyDestroyObject(oLight);
    }
}
//------------------------------------------------------------------------------
void GenerateCode()
{
    string sCode;
    int n, nNumber;
    for(n=1; n<=CODE_LEN; n++)
    {
        nNumber = Random(4);
        sCode += IntToString(nNumber);
    }
    SetLocalString(GetArea(OBJECT_SELF), "Code", sCode);
}
//------------------------------------------------------------------------------
int CheckInput()
{
    object oArea = GetArea(OBJECT_SELF);
    string sCode = GetLocalString(oArea, "Code");
    string sInput = GetLocalString(oArea, "Input");
    int nLen = GetStringLength(sInput);

    if(GetStringLeft(sCode, nLen) == sInput)
        return TRUE;
return FALSE;
}
//------------------------------------------------------------------------------
void DisableLevelers()
{
    object oLev = GetObjectByTag("vshw_coder0");
    SetUseableFlag(oLev, FALSE);
    oLev = GetObjectByTag("vshw_coder1");
    SetUseableFlag(oLev, FALSE);
    oLev = GetObjectByTag("vshw_coder2");
    SetUseableFlag(oLev, FALSE);
    oLev = GetObjectByTag("vshw_coder3");
    SetUseableFlag(oLev, FALSE);
}
//------------------------------------------------------------------------------
void InitObelisk(object oObel)
{
    location lLoc = UpLocation(GetLocation(oObel), 8.3);
    SetLocalObject(oObel, "Center", CreateInvisiblePlaceable(lLoc));
    CreateLights(oObel);
}
//------------------------------------------------------------------------------
void RemoveBeam(object oToRemoveFrom = OBJECT_SELF)
{
    effect eEff = GetFirstEffect(oToRemoveFrom);
    while(GetIsEffectValid(eEff))
    {
        if(GetEffectType(eEff) == EFFECT_TYPE_BEAM)
            RemoveEffect(oToRemoveFrom, eEff);
        eEff = GetNextEffect(oToRemoveFrom);
    }
}
//------------------------------------------------------------------------------
void ChaoticBeams(object oObel, int nIterations = 10)
{
    object oCenter = GetLocalObject(oObel, "Center");
    location lLocStart = GetLocation(oObel);

    int nRandomDirection = Random(180);
    int nRandomZ = Random(6);
    location lLoc = DistantLocation(IntToFloat(Random(4)+6), IntToFloat(nRandomDirection), lLocStart);
    if(nRandomZ)
        lLoc = UpLocation(lLoc, IntToFloat(nRandomZ));
    ApplyBeamToLocation(VFX_BEAM_LIGHTNING, lLoc, oCenter, 0.5);
    ApplyEffectAtLocation(DURATION_TYPE_INSTANT, EffectVisualEffect(VFX_FNF_FIREBALL), lLoc);

    nRandomDirection +=180;
    nRandomZ = Random(4)+9;
    lLoc = UpLocation(DistantLocation(IntToFloat(Random(4)+6), IntToFloat(nRandomDirection), lLocStart), IntToFloat(nRandomZ));

    DelayCommand(0.5, ApplyBeamToLocation(VFX_BEAM_LIGHTNING, lLoc, oCenter, 0.5));
    DelayCommand(0.5, ApplyEffectAtLocation(DURATION_TYPE_INSTANT, EffectVisualEffect(VFX_FNF_FIREBALL), lLoc));

    int nCounter = GetLocalInt(oObel, "Iterations")+1;
    if(nCounter<nIterations)
    {
        SetLocalInt(oObel, "Iterations", nCounter);
        DelayCommand(1.0, ChaoticBeams(oObel, nIterations));
    }
    else
    {
        ApplyEffectAtLocation(DURATION_TYPE_INSTANT, EffectVisualEffect(464), GetLocation(oObel));
        GarantyDestroyObject(oObel, 2.0);
    }
}
//------------------------------------------------------------------------------
string SelectSwimMessage()
{
    string sResult;
    int nRandom = Random(4);
    switch(nRandom)
    {
        case 0: sResult = "Пора убираться отсюда!"; break;
        case 1: sResult = "Я не умею плавать!"; break;
        case 2: sResult = "Бежим!"; break;
        case 3: sResult = "Здесь скоро все будет затоплено!"; break;
    }
return sResult;
}
//------------------------------------------------------------------------------
void SwimMessage(object oArea = OBJECT_SELF)
{
    string sMessage;
    object oPC = GetFirstPC();
    while(GetIsObjectValid(oPC))
    {
        if((GetArea(oPC) == oArea) && !GetIsDM(oPC))
        {
            sMessage = SelectSwimMessage();
            DelayCommand(IntToFloat(Random(5)), AssignCommand(oPC, SpeakString(sMessage)));
        }
        oPC = GetNextPC();
    }
}
//------------------------------------------------------------------------------
int GetDrownLevel(object oPC)
{
    object oArea = GetArea(oPC);
    float fAreaCorrection = GetLocalFloat(oArea, "FillLevelCorrection");
    if(fAreaCorrection == 0.0)
        fAreaCorrection = 0.9;                                                 //DBM("minidunge_inc", "GetDrownLevel", "fAreaCorrection" + FToS(fAreaCorrection));

    float fLevel = GetLocalFloat(oArea, "FillLevel");                          //DBM("minidunge_inc", "GetDrownLevel", "fLevel" + FToS(fLevel));
    vector vPos = GetPosition(oPC);                                            //DBM("minidunge_inc", "GetDrownLevel", "vPos.z" + FToS(vPos.z));
    float fDiff = fLevel - fAreaCorrection - vPos.z;                           //DBM("minidunge_inc", "GetDrownLevel", "fDiff" + FToS(fDiff));
    if(fDiff>=2.0)
        return 4;
    if(fDiff>=1.5)
        return 3;
    if(fDiff>=1.0)
        return 2;
    if(fDiff>=0.5)
        return 1;
return 0;
}
//------------------------------------------------------------------------------
void ManageDrown(object oPC)
{
    int nDrownLevel = GetDrownLevel(oPC);
    switch(nDrownLevel)
    {
        case 1:
            ApplyEffectToObject(DURATION_TYPE_INSTANT, EffectDamage(5, DAMAGE_TYPE_COLD), oPC);
            break;
        case 2:
            ApplyEffectToObject(DURATION_TYPE_INSTANT, EffectDamage(10, DAMAGE_TYPE_COLD), oPC);
            break;
        case 3:
            ApplyEffectToObject(DURATION_TYPE_INSTANT, EffectDamage(15, DAMAGE_TYPE_COLD), oPC);
            break;
        case 4:
            SendMessageToPC(oPC, "Вы утонули!");
            ApplyEffectToObject(DURATION_TYPE_INSTANT, EffectDamage(50, DAMAGE_TYPE_MAGICAL), oPC);
            break;
    }
}
//------------------------------------------------------------------------------
void CheckWaterLevel(object oArea, float fCheckInterval = 2.0)
{                                                                              //DBM("minidunge_inc", "CheckWaterLevel", "START with oArea" + OToS(oArea));
    int nOnceMore;
    object oPC;
    int nNumber = GetNumberOfObjectsInArray(oArea, "PlayersIn");               //DBM("minidunge_inc", "CheckWaterLevel", "nNumber" + IToS(nNumber));
    if(!nNumber)
    {
        oPC = GetFirstPC();
        while(GetIsObjectValid(oPC))
        {
            if(!GetIsDM(oPC) && (GetArea(oPC) == oArea))
            {
                AddObjectToArray(oPC, oArea, "PlayersIn");
                ManageDrown(oPC);
                nOnceMore = TRUE;
            }
            oPC = GetNextPC();
        }
    }
    else
    {
        int n;
        for(n=1; n<=nNumber; n++)
        {
            oPC = GetObejctFromArrayByPosition(oArea, "PlayersIn", n);
            if(GetArea(oPC) == oArea)
            {
                ManageDrown(oPC);
                nOnceMore = TRUE;
            }
            else
                DelayCommand(0.5, RemoveObjectFromArray(oPC, oArea, "PlayersIn"));
        }
    }

    if(nOnceMore)
        DelayCommand(fCheckInterval, CheckWaterLevel(oArea));
}
//------------------------------------------------------------------------------







////////////////////////////////////////////////////////////////////////////////
//----WRM-----------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
void CheckForDamage(location lLoc)
{                                                                              //DBM("minidunge_inc", "CheckForDamage", "START");
    float fFacing = GetFacingFromLocation(lLoc);
    lLoc = DistantLocation(5.0, fFacing, lLoc);                                 //ApplyEffectAtLocation(DURATION_TYPE_INSTANT, EffectVisualEffect(VFX_IMP_HARM), lLoc);

    object oPC = GetFirstObjectInShape(SHAPE_SPHERE, 4.0, lLoc);               //DBM("minidunge_inc", "CheckForDamage", "First PC" + OToS(oPC));
    while(GetIsObjectValid(oPC))
    {
        if(GetIsPC(oPC) || GetIsPC(GetMaster(oPC)))
        {                                                                      //DBM("minidunge_inc", "CheckForDamage", "IN!!!");
            ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectKnockdown(), oPC, 3.0);
            ApplyEffectToObject(DURATION_TYPE_INSTANT, EffectDamage(FloatToInt(GetMaxHitPoints(oPC)/4.0), DAMAGE_TYPE_BLUDGEONING), oPC);
            ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectSlow(), oPC, 12.0);
        }
        oPC = GetNextObjectInShape(SHAPE_SPHERE, 4.0, lLoc);                   //DBM("minidunge_inc", "CheckForDamage", "Next PC" + OToS(oPC));
    }
}
//------------------------------------------------------------------------------
void CreateTongue(int nNeedEffect = TRUE)
{
    float fDistance = 6.0;
    int i;
    object oPart;
    location lLoc = GetLocation(GetObjectByTag("wrm_tongue_WP"));

    for(i=1; i<=5; i++)
    {
        oPart = CreateObject(OBJECT_TYPE_PLACEABLE, "tongue_part", lLoc, FALSE, "wrm_tongue_part"+IntToString(i));
        ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectVisualEffect(VFX_DUR_CUTSCENE_INVISIBILITY), oPart, 1.0);
        DelayCommand(1.0, AssignCommand(GetObjectByTag("wrm_tongue_part1"), CheckForDamage(lLoc)));

        if(i == 1)
            SetUseableFlag(oPart, TRUE);
        if(i<5)
            lLoc = DistantLocation(fDistance, 90.0, lLoc);
    }

    if(nNeedEffect)
    {
        DelayCommand(1.0, MassScreenShake(GetAreaFromLocation(lLoc), VFX_FNF_SCREEN_BUMP));
        DelayCommand(1.0, ApplyEffectAtLocation(DURATION_TYPE_INSTANT, EffectVisualEffect(VFX_FNF_FIREBALL), lLoc));
    }
}
//------------------------------------------------------------------------------
void DestroyTongue()
{
    object oPart;
    int i;
    for(i = 1; i<=5; i++)
    {
        oPart = GetObjectByTag("wrm_tongue_part" + IntToString(i));
        ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectVisualEffect(VFX_DUR_CUTSCENE_INVISIBILITY), oPart, 1.0);
        GarantyDestroyObject(oPart, 0.1);
    }
}
//------------------------------------------------------------------------------
void PutTongueLeft()
{
    location lLoc = GetLocation(GetObjectByTag("wrm_tongue_WP"));
    lLoc = DistantLocation(1.0, 270.0, lLoc, 135.0);
    object oPart = CreateObject(OBJECT_TYPE_PLACEABLE, "tongue_part", lLoc, FALSE, "wrm_tongue_part1");
    SetUseableFlag(oPart, TRUE);
    ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectVisualEffect(VFX_DUR_CUTSCENE_INVISIBILITY), oPart, 1.0);
    DelayCommand(1.0, AssignCommand(GetObjectByTag("wrm_tongue_part1"), CheckForDamage(lLoc)));

    lLoc = DistantLocation(6.0, 135.0, lLoc, 110.0);
    oPart = CreateObject(OBJECT_TYPE_PLACEABLE, "tongue_part", lLoc, FALSE, "wrm_tongue_part2");
    ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectVisualEffect(VFX_DUR_CUTSCENE_INVISIBILITY), oPart, 1.0);
    DelayCommand(1.0, AssignCommand(GetObjectByTag("wrm_tongue_part1"), CheckForDamage(lLoc)));

    lLoc = DistantLocation(6.0, 110.0, lLoc, 90.0);
    oPart = CreateObject(OBJECT_TYPE_PLACEABLE, "tongue_part", lLoc, FALSE, "wrm_tongue_part3");
    ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectVisualEffect(VFX_DUR_CUTSCENE_INVISIBILITY), oPart, 1.0);
    DelayCommand(1.0, AssignCommand(GetObjectByTag("wrm_tongue_part1"), CheckForDamage(lLoc)));

    lLoc = DistantLocation(6.0, 90.0, lLoc);
    oPart = CreateObject(OBJECT_TYPE_PLACEABLE, "tongue_part", lLoc, FALSE, "wrm_tongue_part4");
    ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectVisualEffect(VFX_DUR_CUTSCENE_INVISIBILITY), oPart, 1.0);
    DelayCommand(1.0, AssignCommand(GetObjectByTag("wrm_tongue_part1"), CheckForDamage(lLoc)));

    lLoc = DistantLocation(6.0, 90.0, lLoc);
    oPart = CreateObject(OBJECT_TYPE_PLACEABLE, "tongue_part", lLoc, FALSE, "wrm_tongue_part5");
    ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectVisualEffect(VFX_DUR_CUTSCENE_INVISIBILITY), oPart, 1.0);
    DelayCommand(1.0, AssignCommand(GetObjectByTag("wrm_tongue_part1"), CheckForDamage(lLoc)));

    DelayCommand(1.0, MassScreenShake(GetAreaFromLocation(lLoc), VFX_FNF_SCREEN_BUMP));
    DelayCommand(1.0, ApplyEffectAtLocation(DURATION_TYPE_INSTANT, EffectVisualEffect(VFX_FNF_FIREBALL), lLoc));
}
//------------------------------------------------------------------------------
void PutTongueRight()
{
    location lLoc = GetLocation(GetObjectByTag("wrm_tongue_WP"));
    lLoc = DistantLocation(1.0, 270.0, lLoc, 45.0);
    object oPart = CreateObject(OBJECT_TYPE_PLACEABLE, "tongue_part", lLoc, FALSE, "wrm_tongue_part1");
    SetUseableFlag(oPart, TRUE);
    ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectVisualEffect(VFX_DUR_CUTSCENE_INVISIBILITY), oPart, 1.0);
    DelayCommand(1.0, AssignCommand(GetObjectByTag("wrm_tongue_part1"), CheckForDamage(lLoc)));

    lLoc = DistantLocation(6.0, 45.0, lLoc, 70.0);
    oPart = CreateObject(OBJECT_TYPE_PLACEABLE, "tongue_part", lLoc, FALSE, "wrm_tongue_part2");
    ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectVisualEffect(VFX_DUR_CUTSCENE_INVISIBILITY), oPart, 1.0);
    DelayCommand(1.0, AssignCommand(GetObjectByTag("wrm_tongue_part1"), CheckForDamage(lLoc)));

    lLoc = DistantLocation(6.0, 70.0, lLoc, 90.0);
    oPart = CreateObject(OBJECT_TYPE_PLACEABLE, "tongue_part", lLoc, FALSE, "wrm_tongue_part3");
    ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectVisualEffect(VFX_DUR_CUTSCENE_INVISIBILITY), oPart, 1.0);
    DelayCommand(1.0, AssignCommand(GetObjectByTag("wrm_tongue_part1"), CheckForDamage(lLoc)));

    lLoc = DistantLocation(6.0, 90.0, lLoc);
    oPart = CreateObject(OBJECT_TYPE_PLACEABLE, "tongue_part", lLoc, FALSE, "wrm_tongue_part4");
    ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectVisualEffect(VFX_DUR_CUTSCENE_INVISIBILITY), oPart, 1.0);
    DelayCommand(1.0, AssignCommand(GetObjectByTag("wrm_tongue_part1"), CheckForDamage(lLoc)));

    lLoc = DistantLocation(6.0, 90.0, lLoc);
    oPart = CreateObject(OBJECT_TYPE_PLACEABLE, "tongue_part", lLoc, FALSE, "wrm_tongue_part5");
    ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectVisualEffect(VFX_DUR_CUTSCENE_INVISIBILITY), oPart, 1.0);
    DelayCommand(1.0, AssignCommand(GetObjectByTag("wrm_tongue_part1"), CheckForDamage(lLoc)));

    DelayCommand(1.0, MassScreenShake(GetAreaFromLocation(lLoc), VFX_FNF_SCREEN_BUMP));
    DelayCommand(1.0, ApplyEffectAtLocation(DURATION_TYPE_INSTANT, EffectVisualEffect(VFX_FNF_FIREBALL), lLoc));
}
//------------------------------------------------------------------------------
void MoveTongue()
{
    MassScreenShake(OBJECT_SELF);
    DelayCommand(1.5, DestroyTongue());

    int nRandom = Random(3);
    if(!nRandom)
        DelayCommand(4.0, CreateTongue());
    else if(nRandom == 1)
        DelayCommand(4.0, PutTongueLeft());
    else
        DelayCommand(4.0, PutTongueRight());
}
//------------------------------------------------------------------------------



//AREA 3
//------------------------------------------------------------------------------
int GetRoomID(string sRoom);
int GetRoomID(string sRoom)
{
    if(sRoom == WRM_ROOM_1)
        return 1;
    if (sRoom == WRM_ROOM_2)
        return 2;
    if (sRoom == WRM_ROOM_3)
        return 3;
    if (sRoom == WRM_ROOM_4)
        return 4;
    if (sRoom == WRM_ROOM_5)
        return 5;
    if (sRoom == WRM_ROOM_6)
        return 6;
    if (sRoom == WRM_ROOM_7)
        return 7;
    if (sRoom == WRM_ROOM_8)
        return 8;
    if (sRoom == WRM_ROOM_9)
        return 9;
    if (sRoom == WRM_ROOM_10)
        return 10;
    if (sRoom == WRM_ROOM_11)
        return 11;
return 0;
}
//------------------------------------------------------------------------------
string GetRoomByID(int nRoomID);
string GetRoomByID(int nRoomID)
{
    string sRoom;
    switch(nRoomID)
    {
        case 1: sRoom = WRM_ROOM_1; break;
        case 2: sRoom = WRM_ROOM_2; break;
        case 3: sRoom = WRM_ROOM_3; break;
        case 4: sRoom = WRM_ROOM_4; break;
        case 5: sRoom = WRM_ROOM_5; break;
        case 6: sRoom = WRM_ROOM_6; break;
        case 7: sRoom = WRM_ROOM_7; break;
        case 8: sRoom = WRM_ROOM_8; break;
        case 9: sRoom = WRM_ROOM_9; break;
        case 10: sRoom = WRM_ROOM_10; break;
        case 11: sRoom = WRM_ROOM_11; break;
    }
return sRoom;
}
//------------------------------------------------------------------------------
string GetRoomFromBlock(string sBlock);
string GetRoomFromBlock(string sBlock)
{
    if(FindSubString(WRM_ROOM_1, sBlock)> -1)
        return WRM_ROOM_1;
    else if(FindSubString(WRM_ROOM_2, sBlock)> -1)
        return WRM_ROOM_2;
    else if(FindSubString(WRM_ROOM_3, sBlock)> -1)
        return WRM_ROOM_3;
    else if(FindSubString(WRM_ROOM_4, sBlock)> -1)
        return WRM_ROOM_4;
    else if(FindSubString(WRM_ROOM_5, sBlock)> -1)
        return WRM_ROOM_5;
    else if(FindSubString(WRM_ROOM_6, sBlock)> -1)
        return WRM_ROOM_6;
    else if(FindSubString(WRM_ROOM_7, sBlock)> -1)
        return WRM_ROOM_7;
    else if(FindSubString(WRM_ROOM_8, sBlock)> -1)
        return WRM_ROOM_8;
    else if(FindSubString(WRM_ROOM_9, sBlock)> -1)
        return WRM_ROOM_9;
    else if(FindSubString(WRM_ROOM_10, sBlock)> -1)
        return WRM_ROOM_10;
    else if(FindSubString(WRM_ROOM_11, sBlock)> -1)
        return WRM_ROOM_11;
return "";
}
//------------------------------------------------------------------------------
string GetPCsRoom(object oPC);
string GetPCsRoom(object oPC)
{
    location lLoc = GetLocation(oPC);
    int nRow = GetToolsetMapRow(lLoc);
    int nColumn = GetToolsetMapColumn(lLoc);
    string sBlock = IntToString(nColumn) + IntToString(nRow);

return GetRoomFromBlock(sBlock);
}
//------------------------------------------------------------------------------
void WRM_OpenDoors(object oArea = OBJECT_SELF)
{
    int i;
    object oDoor, oRoomWP, oPC;
    for(i = 12; i>=1; i--)// i-- need for function RemoveObjectFromArray
    {
        //Open door
        oDoor = GetObjectByTag("wrm_a3_door"+IntToString(i));
        SetLocked(oDoor, FALSE);
        AssignCommand(oDoor, ActionOpenDoor(oDoor));

        //Clear vars from room main WP
        oRoomWP = GetObjectByTag("wrm_spWP_r" + IntToString(i) + "_1"); //wrm_spWP_r3_1
        DeleteLocalInt(oRoomWP, "Trap");

        //Clear drowning base
        oPC = GetObejctFromArrayByPosition(oArea, "Drowning", i);
        if(GetIsObjectValid(oPC))
            RemoveObjectFromArray(oPC, oArea, "Drowning");
    }
}
//------------------------------------------------------------------------------
void WRM_CloseDoors()
{
    int i;
    object oDoor;
    for(i = 1; i<=12; i++)
    {
        oDoor = GetObjectByTag("wrm_a3_door"+IntToString(i));
        AssignCommand(oDoor, ActionCloseDoor(oDoor));
        SetLocked(oDoor, TRUE);
    }
}
//------------------------------------------------------------------------------
void FillRoomLevel(string sRoom, float fZOffset, int nGroundEffect);
void FillRoomLevel(string sRoom, float fZOffset, int nGroundEffect)
{                                                                              //DBM("minidunge_inc", "FillRoomLevel", "START with sRoom: " + sRoom);
                                                                               //DBM("minidunge_inc", "FillRoomLevel", "fZOffset" + FToS(fZOffset));
    string sBlock;
    while(sRoom!="")
    {
        sBlock = GetStringLeft(sRoom, 2);                                      //DBM("minidunge_inc", "FillRoomLevel", "sBlock: " + sBlock);
        FillAreaBlock(OBJECT_SELF, StringToInt(GetStringRight(sBlock, 1)), StringToInt(GetStringLeft(sBlock, 1)), fZOffset, nGroundEffect);

        sRoom = GetStringRight(sRoom, GetStringLength(sRoom)-3);               //DBM("minidunge_inc", "FillRoomLevel", "sRoom: " + sRoom);
    }
}
//------------------------------------------------------------------------------
void ResetRoomTiles(string sRoom);
void ResetRoomTiles(string sRoom)
{                                                                              //DBM("minidunge_inc", "ResetRoomTiles", "START with sRoom: " + sRoom);
    string sBlock;
    while(sRoom!="")
    {
        sBlock = GetStringLeft(sRoom, 2);                                      //DBM("minidunge_inc", "ResetRoomTiles", "sBlock: " + sBlock);
        ResetAreaBlock(OBJECT_SELF, sBlock);

        sRoom = GetStringRight(sRoom, GetStringLength(sRoom)-3);               //DBM("minidunge_inc", "ResetRoomTiles", "sRoom: " + sRoom);
    }
}
//------------------------------------------------------------------------------
void FillTheRoom(string sRoom, int nEffect, float fZOffset, float fZOffsetMax = 8.0, float fStep = 0.5, float fDelay = 2.0, object oArea = OBJECT_SELF);
void FillTheRoom(string sRoom, int nEffect, float fZOffset, float fZOffsetMax = 8.0, float fStep = 0.5, float fDelay = 2.0, object oArea = OBJECT_SELF)
{                                                                              //DBM("minidunge_inc", "FillTheRoom", "START with sRoom: " + sRoom);
    ResetRoomTiles(sRoom);
    FillRoomLevel(sRoom, fZOffset, nEffect);

    fZOffset+=fStep;
    if( ((fZOffset<=fZOffsetMax) && (fStep>=0.0))  ||
        ((fZOffset>=fZOffsetMax) && (fStep<0.0))    )
        DelayCommand(fDelay, FillTheRoom(sRoom, nEffect, fZOffset, fZOffsetMax, fStep, fDelay, oArea));
}
//------------------------------------------------------------------------------
void SpawnRandomMobInRoom(int nRoomID, int nSpWpID)
{
    object oWP = GetObjectByTag("wrm_spWP_r" + IntToString(nRoomID)+ "_" + IntToString(nSpWpID)); //wrm_spWP_r3_4
    if(!GetIsObjectValid(oWP))
        oWP = GetObjectByTag("wrm_spWP_r" + IntToString(nRoomID)+ "_1");

    string sTemplate = "wrm_a3_mob" + IntToString(1+Random(3));
    CreateObject(OBJECT_TYPE_CREATURE, sTemplate, GetLocation(oWP));
}
//------------------------------------------------------------------------------
void ManageRoomTraps(object oArea = OBJECT_SELF)
{
    string sRoom;
    int nRoomID;
    object oRoomWP;
    int nTrap;

    object oPC = GetFirstPC();
    while(GetIsObjectValid(oPC))
    {
        if(GetArea(oPC) == oArea)
        {
            sRoom = GetPCsRoom(oPC);
            nRoomID = GetRoomID(sRoom);
            if(nRoomID)
            {
                oRoomWP = GetObjectByTag("wrm_spWP_r" + IntToString(nRoomID) + "_1"); //wrm_spWP_r3_4
                nTrap = GetLocalInt(oRoomWP, "Trap");
                if(!nTrap)
                {
                    if(!Random(5))
                    {
                        nTrap = 100;
                        SetLocalInt(oRoomWP, "Trap", nTrap); //Water
                        FillTheRoom(sRoom, X2_TL_GROUNDTILE_SEWER_WATER, 1.5, 4.5, 0.3);
                        DelayCommand(24.0, FillTheRoom(sRoom, X2_TL_GROUNDTILE_SEWER_WATER, 4.5, 1.5, -0.3));
                    }
                    else
                    {
                        nTrap = 1;/*mobs */                                        //DBM("minidunge_inc", "ManageRoomTraps", "nTrap" + IToS(nTrap));
                        SpawnRandomMobInRoom(nRoomID, nTrap);//+1
                    }
                }

                if(nTrap<100)//if mobs
                {
                    SpawnRandomMobInRoom(nRoomID, nTrap);
                    SetLocalInt(oRoomWP, "Trap", ++nTrap);
                }
                else
                    AddObjectToArray(oPC, oArea, "Drowning");
            }
        }
        oPC = GetNextPC();
    }
}
//------------------------------------------------------------------------------
void CheckPCForDamageA3(int nRound, object oArea = OBJECT_SELF)
{
    object oPC;
    int i, nNumber = GetNumberOfObjectsInArray(oArea, "Drowning");
    for(i = 1; i<=nNumber; i++)
    {
        oPC = GetObejctFromArrayByPosition(oArea, "Drowning", i);
        if(GetIsObjectValid(oPC))
        {
            ApplyEffectAtLocation(DURATION_TYPE_INSTANT, EffectVisualEffect(VFX_FNF_GAS_EXPLOSION_ACID), GetLocation(oPC));
            if(nRound == 1 || nRound == 7)
            {
                ApplyEffectToObject(DURATION_TYPE_INSTANT, EffectDamage(d3(4), DAMAGE_TYPE_ACID), oPC);
                ApplyEffectToObject(DURATION_TYPE_INSTANT, EffectDamage(d3(4), DAMAGE_TYPE_NEGATIVE), oPC);
            }
            else if(nRound == 2 || nRound == 6)
            {
                ApplyEffectToObject(DURATION_TYPE_INSTANT, EffectDamage(d3(8), DAMAGE_TYPE_ACID), oPC);
                ApplyEffectToObject(DURATION_TYPE_INSTANT, EffectDamage(d3(8), DAMAGE_TYPE_NEGATIVE), oPC);
            }
            else if(nRound == 3 || nRound == 5)
            {
                ApplyEffectToObject(DURATION_TYPE_INSTANT, EffectDamage(d3(12), DAMAGE_TYPE_ACID), oPC);
                ApplyEffectToObject(DURATION_TYPE_INSTANT, EffectDamage(d3(12), DAMAGE_TYPE_NEGATIVE), oPC);
            }
            else
                ApplyEffectToObject(DURATION_TYPE_INSTANT, EffectDamage(d3(20), DAMAGE_TYPE_ACID), oPC);
                ApplyEffectToObject(DURATION_TYPE_INSTANT, EffectDamage(d3(20), DAMAGE_TYPE_NEGATIVE), oPC);
        }
    }
}
//------------------------------------------------------------------------------
void CheckPCForDamageA4(object oArea = OBJECT_SELF)
{
    float fLevel = GetLocalFloat(oArea, "FillLevel");
    object oPC = GetFirstPC();
    while(GetIsObjectValid(oPC))
    {
        if(GetArea(oPC) == oArea)
        {
            if(GetPosition(oPC).z+1.0 < fLevel)
            {                                                                  //DBM("minidunge_inc", "CheckPCForDamageA4", "oPC.z" + FToS(GetPosition(oPC).z));
                                                                               //DBM("minidunge_inc", "CheckPCForDamageA4", "fLevel" + FToS(fLevel));
                ApplyEffectToObject(DURATION_TYPE_INSTANT, EffectDamage(GetMaxHitPoints(oPC)/4, DAMAGE_TYPE_FIRE), oPC);
                ApplyEffectToObject(DURATION_TYPE_INSTANT, EffectDamage(GetMaxHitPoints(oPC)/4, DAMAGE_TYPE_ACID), oPC);
                ApplyEffectAtLocation(DURATION_TYPE_INSTANT, EffectVisualEffect(VFX_FNF_GAS_EXPLOSION_FIRE), GetLocation(oPC));
            }
        }
        oPC = GetNextPC();
    }
}
//------------------------------------------------------------------------------
void AppearEffects(object oPC)
{
    ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectVisualEffect(VFX_DUR_CUTSCENE_INVISIBILITY), oPC, 5.3);
    DelayCommand(5.0, ApplyEffectToObject(DURATION_TYPE_INSTANT, EffectVisualEffect(VFX_IMP_POLYMORPH), oPC));
}
//------------------------------------------------------------------------------
void CheckExitingPC()
{
    object oWyr = GetObjectByTag(WRM_WYRMLING);
    object oExitDestination = GetObjectByTag(WRM_EXIT_POINT);

    object oExit = GetObjectByTag("WRM_DungeExit");
    object oArea = GetArea(oExit);
    object oPC = GetFirstPC();
    while(GetIsObjectValid(oPC))
    {
        if(GetArea(oPC) == oArea)
        {
            if(GetDistanceBetween(oPC, oExit)<=5.0)
            {
                EPQST_Exit(oPC);
                ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectKnockdown(), oWyr, 0.05);
                AssignCommand(oWyr, ClearAllActions(TRUE));
                AppearEffects(oPC);
                AssignCommand(oPC, ClearAllActions());
                AssignCommand(oPC, JumpToObject(oExitDestination));
                DelayCommand(1.0, AssignCommand(oWyr, ActionCastFakeSpellAtLocation(SPELLABILITY_DRAGON_BREATH_FIRE, GetLocation(oExitDestination))));// SPELLABILITY_DRAGON_BREATH_FIRE -> 797?
            }
        }
        oPC = GetNextPC();
    }
}
//------------------------------------------------------------------------------
void WRM_CustomPhrases(object oArea = OBJECT_SELF)
{
    string sPhrase;
    object oPC = GetFirstPC();
    while(GetIsObjectValid(oPC))
    {
        if(GetArea(oPC) == oArea)
        {
            switch(Random(5))
            {
                case 0: sPhrase = "Надо убираться отсюда! Его сейчас стошнит!";                     break;
                case 1: sPhrase = "Наверх! Вижу там луч света!";                                    break;
                case 2: sPhrase = "Кажется вирмлингу совсем нездоровится, пора уходить!";           break;
                case 3: sPhrase = "Чертова животина сейчас изрыгнет нас вместе с остатками ужина!"; break;
                case 4: sPhrase = "Похоже сейчас его вырвет, это шанс выбраться отсюда!";           break;
            }
            DelayCommand(IntToFloat(Random(5)), AssignCommand(oPC, SpeakString(sPhrase)));
        }
        oPC = GetNextPC();
    }
}
//------------------------------------------------------------------------------















//LABIRINT
//------------------------------------------------------------------------------
void CreateCraneEyes(object oCrane)
{
    location lLoc = GetLocation(oCrane);
    object oFire1 = CreateInvisiblePlaceable(DistantLocation(6.0, GetFacing(oCrane)-180.0+25.0, UpLocation(lLoc, 0.7)));
    object oFire2 = CreateInvisiblePlaceable(DistantLocation(6.0, GetFacing(oCrane)+180.0-25.0, UpLocation(lLoc, 0.7)));
    ApplyEffectToObject(DURATION_TYPE_PERMANENT, EffectVisualEffect(VFX_DUR_INFERNO), oFire1);
    ApplyEffectToObject(DURATION_TYPE_PERMANENT, EffectVisualEffect(VFX_DUR_INFERNO), oFire2);


    DestroyObject(oFire1, 15.0);
    DestroyObject(oFire2, 15.0);

}
//------------------------------------------------------------------------------
void Lab_SpawnEnter(location lLoc)
{
    MassScreenShake(GetAreaFromLocation(lLoc));
    object oCrane = GetObjectByTag("lab_enter");
    if(GetIsObjectValid(oCrane))
    {
        lLoc = UpLocation(lLoc, 0.5);
        GarantyDestroyObject(oCrane, 0.05);
    }
    else
        lLoc = UpLocation(lLoc, -9.0);

    oCrane = CreateObject(OBJECT_TYPE_PLACEABLE, "lab_enter", lLoc);

    if(GetPositionFromLocation(lLoc).z <3.0)
        DelayCommand(1.0, Lab_SpawnEnter(lLoc));
    else
    {
        object oArea = GetAreaFromLocation(lLoc);
        int nKeyID = GetLocalInt(oArea, "KeyID");
        object oUser = GetLocalObject(oArea, "KeyUser");
        DeleteLocalInt(oArea, "KeyID");
        DeleteLocalObject(oArea, "KeyUser");

        EPQST_UnlockQuest(oCrane, IntToString(nKeyID));

        DelayCommand(3.0, SetUseableFlag(oCrane, TRUE));
        DelayCommand(3.0, CreateCraneEyes(oCrane));
        DelayCommand(3.0, FloatingTextStringOnCreature("Через 15 сек вход будет закрыт!", oUser));
        GarantyDestroyObject(oCrane, 23.0);
    }
}
//------------------------------------------------------------------------------
void Lab_HideMapForPlayersInArea(object oArea = OBJECT_SELF)
{
    object oPC = GetFirstPC();
    while(GetIsObjectValid(oPC))
    {
        if(GetArea(oPC) == oArea)
            ExploreAreaForPlayer(oArea, oPC, FALSE);

        oPC = GetNextPC();
    }
}
//------------------------------------------------------------------------------
void Lab_A1_SpawnRandomMob(object oPC)
{
    string sResRef = "lab_a1_mob" + IntToString(Random(2)+1);
    CreateObject(OBJECT_TYPE_CREATURE, sResRef, GetLocation(oPC), TRUE);
}
//------------------------------------------------------------------------------
void Lab_A1_TorchLightDebug(object oArea = OBJECT_SELF)
{
    if(GetLocalInt(oArea, "TorchDebug"))
        return;
    SetLocalInt(oArea, "TorchDebug", 1);
    DelayCommand(10.0, DeleteLocalInt(oArea, "TorchDebug"));

    object oTorch, oStone = GetObjectByTag("lab_a1_stone");
    int i;
    for(i = 1; i<=4; i++)
    {
        oTorch = GetNearestObjectByTag("lab_a1_torch", oStone, i);
        if(GetUseableFlag(oTorch))
        {
            SetPlaceableIllumination(oTorch, TRUE);
            SetPlaceableIllumination(oTorch, FALSE);
        }
    }
    DelayCommand(8.0, RecomputeStaticLighting(OBJECT_SELF));
}
//------------------------------------------------------------------------------
void Lab_A1_InitArea(object oArea = OBJECT_SELF)
{
    if(GetLocalInt(oArea, "Initialized"))
        return;
    SetLocalInt(oArea, "Initialized", TRUE);

    /* Disabled bZ 26.01.2018 // Not need
    //Destoy Portal
    object oPortal = GetObjectByTag("lab_a1_portal");
    if(GetIsObjectValid(oPortal))
        GarantyDestroyObject(oPortal, 0.1);

    //Stone useable
    object oStone = GetObjectByTag("lab_a1_stone");
    SetUseableFlag(oStone, TRUE);
    //Zero Var on Stone
    DeleteLocalInt(oStone, "Torches");
    */

    //Torches
    object oTorch, oChest = GetObjectByTag("lab_a1_torch_chest");
    //object oStone = GetObjectByTag("lab_a1_stone");
    MiniDunge_ClearInventory(oChest);
    int i;
    for(i = 1; i<=4; i++)//1 loop for 2 features - torches-items in chest near the enter, and torches-placeables near the stone
    {
        oTorch = CreateItemOnObject("it_torch004", oChest, 1, "lab_item");
        SetName(oTorch, "Яркий Факел");
        SetLocalInt(oTorch, "symbfaith001", TRUE); // чтоб клеры могли кастовать

        //oTorch = GetNearestObjectByTag("lab_a1_torch", oStone, i);
        //SetLocalInt(oTorch,"NW_L_AMION",1);
        //ExecuteScript("nw_02_onoff", oTorch);

    }
}
//------------------------------------------------------------------------------
void Lab_A1_RemoveBlindness(object oPC)
{
    effect eEffect = GetFirstEffect(oPC);
    while(GetIsEffectValid(eEffect))
    {
        if(GetEffectType(eEffect) == EFFECT_TYPE_BLINDNESS && GetEffectDurationType(eEffect) == DURATION_TYPE_PERMANENT)
            RemoveEffect(oPC, eEffect);
        eEffect = GetNextEffect(oPC);
    }
}
//------------------------------------------------------------------------------
void Lab_A1_ManageBlindness(object oPC)
{
    if(GetLocalInt(oPC, "InLightZone") || GetTag(GetArea(oPC)) != "lab_area_1")
    {
        Lab_A1_RemoveBlindness(oPC);
        return;
    }
    /*
    object oItem = GetItemInSlot(INVENTORY_SLOT_LEFTHAND, oPC);
    if(GetResRef(oItem) == "it_torch004" && GetTag(oItem) == "lab_item")
        Lab_A1_RemoveBlindness(oPC);
    */

    int nLightCount = GetLocalInt(oPC, "InTorchLight");
    if(nLightCount<1)
    {
        ApplyEffectToObject(DURATION_TYPE_PERMANENT, ExtraordinaryEffect(EffectBlindness()), oPC);
        SendMessageToPC(oPC, "В этой густой тьме вы ничего не видите");
    }
    else
        Lab_A1_RemoveBlindness(oPC);


    /*
    else
    {
        int nLightCount = GetLocalInt(oPC, "InTorchLight");
        if(nLightCount<1)
        {
            ApplyEffectToObject(DURATION_TYPE_PERMANENT, ExtraordinaryEffect(EffectBlindness()), oPC);
            SendMessageToPC(oPC, "В этой густой тьме вы ничего не видите");
        }
    }*/
}
//------------------------------------------------------------------------------
void Lab_A1_SpeakPhrase(object oPC)
{
    AssignCommand(oPC, ActionPlayAnimation(ANIMATION_FIREFORGET_VICTORY1));
    DelayCommand(1.0, AssignCommand(oPC, SpeakString("Фла-зоц-лет-ушг-саовс!")));
}
//------------------------------------------------------------------------------
void Lab_A1_Final()
{
    //OBJECT_SELF - это камень

    // Удаляем портал
    object oPortal = GetObjectByTag("lab_a1_portal");
    location lLoc = GetLocation(oPortal);
    SetPlotFlag(oPortal, FALSE);
    DestroyObject(oPortal, 2.0);

    MassScreenShake(GetArea(OBJECT_SELF));
    float fDelay;
    DelayCommand(fDelay+=2.0, ApplyEffectAtLocation(DURATION_TYPE_INSTANT, EffectVisualEffect(2116), lLoc));
    DelayCommand(fDelay+=1.0, CreateObjectVoid(OBJECT_TYPE_CREATURE, "lab_a1_boss", lLoc));


    //fDelay = 60.0;
    //DelayCommand(fDelay, ApplyEffectAtLocation(DURATION_TYPE_INSTANT, EffectVisualEffect(VFX_IMP_LIGHTNING_M), lLoc));
    //DelayCommand(fDelay+0.5, CreateObjectVoid(OBJECT_TYPE_PLACEABLE, "universal_portal", lLoc, FALSE, "lab_a1_portal"));
    //DelayCommand(fDelay+0.6, Lab_A1_ManagePortal());

}
//------------------------------------------------------------------------------



















//------------------------------------------------------------------------------
void Lab_A2_PlaceArrows(object oWP)
{
    location lWPLoc = GetLocation(oWP);
    location lLoc = DistantLocation(4.0, 0.0, lWPLoc, 0.0);
    object oArrow = CreateObject(OBJECT_TYPE_PLACEABLE, "lab_arrow", lLoc);

    lLoc = DistantLocation(4.0, 90.0, lWPLoc, 90.0);
    oArrow = CreateObject(OBJECT_TYPE_PLACEABLE, "lab_arrow", lLoc);

    lLoc = DistantLocation(4.0, 180.0, lWPLoc, 180.0);
    oArrow = CreateObject(OBJECT_TYPE_PLACEABLE, "lab_arrow", lLoc);

    lLoc = DistantLocation(4.0, 270.0, lWPLoc, 270.0);
    oArrow = CreateObject(OBJECT_TYPE_PLACEABLE, "lab_arrow", lLoc);
}
//------------------------------------------------------------------------------
void Lab_A2_InitArea(object oArea = OBJECT_SELF)
{
    if(GetLocalInt(oArea, "Initialized"))
        return;
    SetLocalInt(oArea, "Initialized", TRUE);

    object oEnterWP = GetObjectByTag("WP_lab_a2_enter");
    //Lab_A2_PlaceArrows(oEnterWP);

    int nNth = 1;
    object oWP = GetNearestObjectByTag("WP_lab_a2_block", oEnterWP, nNth);
    while(GetIsObjectValid(oWP))
    {
        Lab_A2_PlaceArrows(oWP);
        oWP = GetNearestObjectByTag("WP_lab_a2_block", oEnterWP, ++nNth);
    }
}
//------------------------------------------------------------------------------
void Lab_A2_DestroyTorchesFromA1(object oEnter)
{
    object oItem = GetFirstItemInInventory(oEnter);
    while(GetIsObjectValid(oItem))
    {
        if(GetBaseItemType(oItem) == BASE_ITEM_TORCH && GetTag(oItem) == "lab_item")
            GarantyDestroyObject(oItem, 0.1);

        oItem = GetNextItemInInventory(oEnter);
    }
}










//------------------------------------------------------------------------------
void Lab_A3_CreateReturnPortal(object oWP)
{
    location lLoc = GetLocation(oWP);
    string sDest = GetLocalString(oWP, "Dest");
    object oPortal = CreateObject(OBJECT_TYPE_PLACEABLE, "universal_portal", lLoc);
    SetLocalString(oPortal, "DestinationTag", sDest);
    SetName(oPortal, "Портал возвращения");
}
//------------------------------------------------------------------------------
void Lab_A3_CloseTrapDoor(object oCenter = OBJECT_SELF, string sTag = "lab_a3_trap_door")
{
    object oDoor = GetNearestObjectByTag(sTag, oCenter);
    AssignCommand(oDoor, ActionCloseDoor(oDoor));
    SetLocked(oDoor, TRUE);
    DelayCommand(59.0, SetLocked(oDoor, FALSE));
    DelayCommand(60.0, AssignCommand(oDoor, ActionOpenDoor(oDoor)));

    //DelayCommand(65.0, UnhidePlaceable(GetNearestObjectByTag("lab_a3_return_portal", oCenter)));
    //DelayCommand(65.0, AssignCommand(GetNearestObjectByTag("lab_a3_return_portal", oCenter), PlayAnimation(ANIMATION_PLACEABLE_ACTIVATE)));
    DelayCommand(65.0, Lab_A3_CreateReturnPortal(GetNearestObjectByTag("WP_lab_a3_return_portal")));
}
//------------------------------------------------------------------------------
void Lab_A3_ManageInterier(int nVariant = 1)
{
    // DESTROY
    int i=1;
    object oPlace = GetObjectByTag("lab_a3_plc_"+ IntToString(i));
    while(GetIsObjectValid(oPlace))
    {
        GarantyDestroyObject(oPlace, 0.01);
        oPlace = GetObjectByTag("lab_a3_plc_"+ IntToString(++i));
    }

    // CREATE
    location lLoc, lMainLoc = GetLocation(GetObjectByTag("WP_lab_a3_int_1_" + IntToString(nVariant)));
    float fFacing = GetFacingFromLocation(lMainLoc);

    // Книга
    lLoc = DistantLocation(-2.0, fFacing, lMainLoc, fFacing+180.0);
    oPlace = CreateObject(OBJECT_TYPE_PLACEABLE, "sl_it_re_book1", lLoc, FALSE, "lab_a3_plc_1");
    SetPlotFlag(oPlace, TRUE);
    SetDescription(oPlace, "Северный портал, Восточный, Южный, Западный портал. Не перепутай порядок, иначе тебе никогда не найти выход!");

    // Кости
    lLoc = GetLocation(GetObjectByTag("WP_lab_a3_int_2_" + IntToString(nVariant)));
    oPlace = CreateObject(OBJECT_TYPE_PLACEABLE, "sl_pl_bg_bon", lLoc, FALSE, "lab_a3_plc_2");
    SetPlotFlag(oPlace, TRUE);
    SetUseableFlag(oPlace, FALSE);

    // Крест
    int nTemp = nVariant+2;
    if(nTemp>4)
        nTemp-=4;
    lLoc = GetLocation(GetObjectByTag("WP_lab_a3_int_1_" + IntToString(nTemp)));
    lLoc = Location(GetAreaFromLocation(lLoc), GetPositionFromLocation(lLoc), GetFacingFromLocation(lLoc)+90.0);
    oPlace = CreateObject(OBJECT_TYPE_PLACEABLE, "sl_it_re_ankh2", lLoc, FALSE, "lab_a3_plc_3");
    SetPlotFlag(oPlace, TRUE);
    SetUseableFlag(oPlace, FALSE);

    // Камень 1
    lLoc = DistantLocation(7.5, fFacing-115.0, lMainLoc);
    oPlace = CreateObject(OBJECT_TYPE_PLACEABLE, "rector_q_boulder", lLoc, FALSE, "lab_a3_plc_4");
    SetPlotFlag(oPlace, TRUE);
    SetUseableFlag(oPlace, FALSE);

    // Камень 2
    lLoc = DistantLocation(8.0, fFacing+125.0, lMainLoc, fFacing-90.0);
    oPlace = CreateObject(OBJECT_TYPE_PLACEABLE, "sl_plc_stone_1", lLoc, FALSE, "lab_a3_plc_5");
    SetPlotFlag(oPlace, TRUE);
    SetUseableFlag(oPlace, FALSE);

    // Песок
    lLoc = GetLocation(GetObjectByTag("WP_lab_a3_int_1_" + IntToString(nTemp))); // Variant +2
    lLoc = DistantLocation(6.0, fFacing-75.0, lLoc, fFacing+90.0);
    oPlace = CreateObject(OBJECT_TYPE_PLACEABLE, "sl_pl_trap2", lLoc, FALSE, "lab_a3_plc_6");
    SetPlotFlag(oPlace, TRUE);
    SetUseableFlag(oPlace, FALSE);
}
//------------------------------------------------------------------------------
void Lab_A3_ManageArrow(int nVariant = 1)
{
    object oArrow = GetObjectByTag("lab_a3_arrow");
    if(GetIsObjectValid(oArrow))
        GarantyDestroyObject(oArrow, 0.01);

    location lLoc = GetLocation(GetObjectByTag("WP_lab_a3_enter"));
    float fDirection = 90.0*nVariant;
    lLoc = Location(GetAreaFromLocation(lLoc), GetPositionFromLocation(lLoc), fDirection);
    oArrow = CreateObject(OBJECT_TYPE_PLACEABLE, "lab_arrow", lLoc, FALSE, "lab_a3_arrow");
    SetUseableFlag(oArrow, FALSE);
}
//------------------------------------------------------------------------------
/*void Lab_A3_UnhidePortalsInstances(int nInst = 1)
{                                                                               DBM("mini", "Lab_A3_UnhidePortalsInstances", "nInst" + IToS(nInst));
    object oPortal;
    string sInst = IntToString(nInst);
    int nPortNum;
    for(nPortNum = 1; nPortNum<=4; nPortNum++)
    {
        oPortal = GetObjectByTag("lab_a3_portal_" + IntToString(nPortNum) + "_" + sInst); DBM("mini", "Lab_A3_UnhidePortalsInstances", "oPortal" + OToS(oPortal));
        UnhidePlaceable(oPortal);
    }
}
//------------------------------------------------------------------------------
void Lab_A3_HideAllPortals()
{
    object oPortal;
    int nPortNum, nInstNum;
    for(nPortNum = 1; nPortNum<=4; nPortNum++)
    {
        for(nInstNum = 1; nInstNum<=4; nInstNum++)
        {
            oPortal = GetObjectByTag("lab_a3_portal_" + IntToString(nPortNum) + "_" + IntToString(nInstNum));
            DeleteLocalString(oPortal, "DestinationTag");
            HidePlaceable(oPortal);
        }
    }

    nPortNum = 0;
    oPortal = GetObjectByTag("lab_a3_return_portal");
    while(GetIsObjectValid(oPortal))
    {
        HidePlaceable(oPortal);
        oPortal = GetObjectByTag("lab_a3_return_portal", ++nPortNum);
    }
}*/
//------------------------------------------------------------------------------
void Lab_A3_RotatePortals(int nVariant = 1)
{
    object oWP, oPortal;
    int i, nPortalType;
    for(i = 1; i<=4; i++)
    {
        oWP = GetObjectByTag("WP_lab_a3_portal_" + IntToString(i));
        GarantyDestroyObject(GetLocalObject(oWP, "Portal"), 0.1);
        nPortalType = i + nVariant - 1;
        if(nPortalType>4)
            nPortalType -= 4;
        oPortal = CreateObject(OBJECT_TYPE_PLACEABLE, "lab_a3_portal_" + IntToString(nPortalType), GetLocation(oWP));
        SetLocalObject(oWP, "Portal", oPortal);
        SetLocalObject(oPortal, "WPOwner", oWP);
    }
}
//------------------------------------------------------------------------------
void Lab_A3_ArrangePlaceables(int nVariant = 1)
{
    //Lab_A3_HideAllPortals();
    //Lab_A3_UnhidePortalsInstances(nVariant);
    Lab_A3_RotatePortals(nVariant);
    Lab_A3_ManageArrow(nVariant);
    Lab_A3_ManageInterier(nVariant);
}
//------------------------------------------------------------------------------
void Lab_A3_RotateRoom()
{
    object oArea = GetObjectByTag("lab_area_3");
    if(!GetLocalInt(oArea, "RotationStarted"))
    {
        //MassBlackScreen(oArea, 2.0);

        SetLocalInt(oArea, "RotationStarted", TRUE);
        DelayCommand(5.0, DeleteLocalInt(oArea, "RotationStarted"));

        int nVariant = GetLocalInt(oArea, "Variant")+1;
        if(nVariant>4)
            nVariant = 1;
        SetLocalInt(oArea, "Variant", nVariant);
        Lab_A3_ArrangePlaceables(nVariant);
    }
}
//------------------------------------------------------------------------------
void Lab_A3_CheckPCsAndRotateRoom()
{
    location lLoc = GetLocation(GetObjectByTag("WP_lab_a3_enter"));
    object oPC = GetFirstObjectInShape(SHAPE_SPHERE, 15.0, lLoc);
    while(GetIsObjectValid(oPC))
    {
        if(GetIsPC(oPC) && !GetIsDM(oPC))
            return;
    }
    // Если нет игроков в радиусе
    Lab_A3_RotateRoom();
}
//------------------------------------------------------------------------------
void Lab_A3_PrepareChests2()
{
    int nNth;
    object oChest = GetObjectByTag("lab_a3_chest2");
    while(GetIsObjectValid(oChest))
    {
        CreateItemOnObject("nw_it_gold001", oChest, 1000);
        oChest = GetObjectByTag("lab_a3_chest2", ++nNth);
    }

    // Вибираем фэйковый сундук
    oChest = GetObjectByTag("lab_a3_chest2", Random(5));
    SetItemStackSize(GetFirstItemInInventory(oChest), 1);
    SetLocalInt(oChest, "Fake", TRUE);
}
//------------------------------------------------------------------------------
void Lab_A3_HideAllChestsWithNumber(int nNumber)
{
    string sNumber = IntToString(nNumber);
    int nNth;
    object oChest = GetObjectByTag("lab_a3_chest"+sNumber, nNth);
    while(GetIsObjectValid(oChest))
    {
        HidePlaceable(oChest);
        oChest = GetObjectByTag("lab_a3_chest"+sNumber, ++nNth);
    }
}
//------------------------------------------------------------------------------
void Lab_A3_UnhideAllChestsWithNumber(int nNumber)
{
    string sNumber = IntToString(nNumber);
    int nNth;
    object oChest = GetObjectByTag("lab_a3_chest"+sNumber, nNth);
    while(GetIsObjectValid(oChest))
    {
        UnhidePlaceable(oChest);
        oChest = GetObjectByTag("lab_a3_chest"+sNumber, ++nNth);
    }
}
//------------------------------------------------------------------------------
void Lab_A3_PrepareChests4()
{
    //UnhidePlaceable(GetObjectByTag("lab_a3_stone"));
    //Lab_A3_UnhideAllChestsWithNumber(4);
    int nDeath = Random(5);
    object oChest = GetObjectByTag("lab_a3_chest4", nDeath);
    SetLocalInt(oChest, "Special", 1);

    int nGift = Random(5);
    if(nGift == nDeath)
        nGift += 1+Random(4);
    if(nGift>5)
        nGift -=5;

    oChest = GetObjectByTag("lab_a3_chest4", nGift);
    SetLocalInt(oChest, "Special", 2);
}
//------------------------------------------------------------------------------
void Lab_A3_InitArea(object oArea = OBJECT_SELF)
{
    if(GetLocalInt(oArea, "Initialized"))
        return;

    SetLocalInt(oArea, "Initialized", TRUE);


    // Initial room
    //Lab_A3_HideAllPortals();
    //Lab_A3_ArrangePlaceables();
    Lab_A3_RotateRoom();


    // Hide secret doors
    //HidePlaceable(GetObjectByTag("lab_a3_exitdoor1"));
    //HidePlaceable(GetObjectByTag("lab_a3_exitdoor2"));

    // Make trap-triggers active
    //DeleteLocalInt(GetObjectByTag("lab_a3_trap1"), "Activated");
    //DeleteLocalInt(GetObjectByTag("lab_a3_trap2"), "Activated");
    //DeleteLocalInt(GetObjectByTag("lab_a3_trap3"), "Activated");
    //DeleteLocalInt(GetObjectByTag("lab_a3_trap4"), "Activated");
    //DeleteLocalInt(GetObjectByTag("lab_a3_trg_showdoor"), "Activated");
    //DeleteLocalInt(GetObjectByTag("lab_a3_show_ch4"), "Activated");


    //Unhide chests 1
    //Lab_A3_UnhideAllChestsWithNumber(1);

    //Hide chests 4
    //Lab_A3_HideAllChestsWithNumber(4);

    //Create gold
    Lab_A3_PrepareChests2();
}
//------------------------------------------------------------------------------
/*void Lab_A3_SetDestinationTag(object oPortal, string sDestTag)
{
    string sTagPart = GetStringLeft(GetTag(oPortal), 16);
    int i;
    for(i = 1; i<=4; i++)
    {
        oPortal = GetObjectByTag(sTagPart + IntToString(i));
        SetLocalString(oPortal, "DestinationTag", sDestTag);
    }
}*/
//------------------------------------------------------------------------------
void Lab_A3_SpawnMimics(object oPC)
{
    location lLoc;
    int nNth;
    object oChest = GetObjectByTag("lab_a3_chest1", nNth);
    while(GetIsObjectValid(oChest))
    {
        lLoc = GetLocation(oChest);
        HidePlaceable(oChest);
        GarantyDestroyObject(oChest, 0.1);
        CreateObject(OBJECT_TYPE_CREATURE, "lab_a3_mob3", lLoc);

        oChest = GetObjectByTag("lab_a3_chest1", ++nNth);
    }
}
//------------------------------------------------------------------------------
void DestroyFlames()
{
    object oFlame = GetObjectByTag("lab_a3_mob4", 0);
    object oFlame2 = GetObjectByTag("lab_a3_mob4", 1);
    object oFlame3 = GetObjectByTag("lab_a3_mob4", 2);

    GarantyDestroyObject(oFlame, 0.1);
    GarantyDestroyObject(oFlame2, 0.1);
    GarantyDestroyObject(oFlame3, 0.1);
}
//------------------------------------------------------------------------------
void Lab_A3_SpawnFlames()
{
    int nNth;
    object oChest = GetObjectByTag("lab_a3_chest2", nNth);
    while(GetIsObjectValid(oChest))
    {
        //HidePlaceable(oChest);
        GarantyDestroyObject(oChest, 0.1);
        oChest = GetObjectByTag("lab_a3_chest2", ++nNth);
    }

    location lLoc = GetLocation(GetObjectByTag("WP_lab_a3_flame1"));
    ApplyEffectAtLocation(DURATION_TYPE_INSTANT, EffectVisualEffect(VFX_IMP_LIGHTNING_M), lLoc);
    CreateObject(OBJECT_TYPE_CREATURE, "lab_a3_mob4", lLoc);

    lLoc = GetLocation(GetObjectByTag("WP_lab_a3_flame2"));
    DelayCommand(20.0, ApplyEffectAtLocation(DURATION_TYPE_INSTANT, EffectVisualEffect(VFX_IMP_LIGHTNING_M), lLoc));
    DelayCommand(20.0, CreateObjectVoid(OBJECT_TYPE_CREATURE, "lab_a3_mob4", lLoc));

    lLoc = GetLocation(GetObjectByTag("WP_lab_a3_flame3"));
    DelayCommand(40.0, ApplyEffectAtLocation(DURATION_TYPE_INSTANT, EffectVisualEffect(VFX_IMP_LIGHTNING_M), lLoc));
    DelayCommand(40.0, CreateObjectVoid(OBJECT_TYPE_CREATURE, "lab_a3_mob4", lLoc));

    DelayCommand(60.0, DestroyFlames());
}
//------------------------------------------------------------------------------
/*object Lab_A3_SelectPoint(object oSelf, object oPC)
{
    int nNth;
    float fDiff, fBiggestDiff = -100.0;
    object oResult, oWP = GetObjectByTag("WP_lab_a3_escape", nNth);
    while(GetIsObjectValid(oWP))
    {
        fDiff = GetDistanceBetween(oSelf, oWP) - GetDistanceBetween(oPC, oWP);
        if(fDiff>fBiggestDiff)
        {
            fBiggestDiff = fDiff;
            oResult = oWP;
        }
        oWP = GetObjectByTag("WP_lab_a3_escape", ++nNth);
    }
return oResult;
}*/
//------------------------------------------------------------------------------
void Lab_A3_RunToPoint(object oSelf, object oPC)
{
    if(GetLocalInt(oSelf, "IsRunning"))
        return;
    SetLocalInt(oSelf, "IsRunning", TRUE);
    DelayCommand(3.0, DeleteLocalInt(oSelf, "IsRunning"));

    int nNth = 3+Random(3);
    object oWP = GetNearestObjectByTag("WP_lab_a3_escape", oSelf, nNth);
    // Рандомим расстояние, которое должно остаться между боссом и точкой
    float fDist = GetDistanceBetween(oSelf, oWP);
    fDist = IntToFloat(Random(FloatToInt(fDist)));
    if(fDist>20.0)
        fDist/=2;

    AssignCommand(oSelf, ClearAllActions(TRUE));
    DelayCommand(0.1, AssignCommand(oSelf, ActionMoveToObject(oWP, TRUE, fDist)));
}
//------------------------------------------------------------------------------
void Lab_A3_RunAway(object oSelf, object oPC)
{
    AssignCommand(oSelf, ActionMoveAwayFromObject(oPC, TRUE));
    DelayCommand(2.0, Lab_A3_RunToPoint(oSelf, oPC));
}
//------------------------------------------------------------------------------







//------------------------------------------------------------------------------
/*
void Lab_A4_InitArea(object oArea = OBJECT_SELF)
{
    if(GetLocalInt(oArea, "Initialized"))
        return;

    SetLocalInt(oArea, "Initialized", TRUE);
    SendMessageToAllDMs("Initialization");

    object oPlace = GetFirstObjectInArea(oArea);
    while(GetIsObjectValid(oPlace))
    {
        if(GetObjectType(oPlace) == OBJECT_TYPE_PLACEABLE)
        {
            if(GetStringLeft(GetTag(oPlace), 11) == "lab_a4_plc_" && !GetLocalInt(oPlace, "Put"))
            {
                ApplyEffectToObject(DURATION_TYPE_PERMANENT, EffectCutsceneGhost(), oPlace);
                SendMessageToAllDMs("oPlace: " + GetTag(oPlace));
            }
        }
        oPlace = GetNextObjectInArea(oArea);
    }
}*/
//------------------------------------------------------------------------------
object Lab_A4_GetConstructWP(object oColumn)
{
    return GetNearestObjectByTag("WP_lab_construct", oColumn);
}
//------------------------------------------------------------------------------
string Lab_A4_GetNextPartResRef(object oOldPart, object oNewPart)
{
    string sOldPart = GetTag(oOldPart);
    string sNewPart = GetTag(oNewPart);

    string sNextPart;
    if(sNewPart == "lab_a4_plc_1")
        sNextPart = "lab_a4_it_2";
    else if(sNewPart == "lab_a4_plc_2")
    {
        if(sOldPart == "lab_a4_plc_2")
            sNextPart = "lab_a4_it_3";
        else
            sNextPart = "lab_a4_it_2";
    }
    else if(sNewPart == "lab_a4_plc_4")
    {
        object oConstWP = Lab_A4_GetConstructWP(oNewPart);
        int nCount = GetLocalInt(oConstWP, "Count");
        SetLocalInt(oConstWP, "Count", ++nCount);
        if(nCount<GetLocalInt(oConstWP, "Columns"))
            sNextPart = "lab_a4_it_1";
        else
            sNextPart = GetLocalString(oConstWP, "Top");
    }
return sNextPart;
}
//------------------------------------------------------------------------------
float Lab_A4_GetHeight(string sResRef, string sTargetTag)
{
    float fHeight;
    if(sResRef == "lab_a4_it_1")//Нижняя часть
        fHeight = 3.20;
    else if(sResRef == "lab_a4_it_2")//Средняя часть
    {
        if(sTargetTag == "lab_a4_plc_1")
            fHeight = 0.55;
        else
            fHeight = 0.75;
    }
    else if(sResRef == "lab_a4_it_5")//Прозрачный камень
        fHeight = 0.45;
    else if(sResRef == "lab_a4_it_6")//Концентратор
        fHeight = 2.25;
    else if(sResRef == "lab_a4_it_7")//Накопитель
        fHeight = 3.2;
    else if(sResRef == "lab_a4_it_8")//Кристалл
        fHeight = 3.4;

return fHeight;
}
//------------------------------------------------------------------------------
object Lab_A4_CreateColumn(location lLoc)
{
    location lNew;
    string sTag;

    //Destroy parts
    object oPart = GetFirstObjectInShape(SHAPE_SPHERE, 2.0, lLoc, FALSE, OBJECT_TYPE_PLACEABLE);
    while(GetIsObjectValid(oPart))
    {
        sTag = GetTag(oPart);
        if(sTag == "lab_a4_plc_1")
        {
            lNew = GetLocation(oPart);
            if(!GetLocalInt(oPart, "Init"))
                GarantyDestroyObject(oPart, 0.1);
            else
                HidePlaceable(oPart);
        }
        else if(sTag == "lab_a4_plc_2")
        {
            if(!GetLocalInt(oPart, "Init"))
                GarantyDestroyObject(oPart, 0.1);
            else
                HidePlaceable(oPart);
        }
        oPart = GetNextObjectInShape(SHAPE_SPHERE, 2.0, lLoc, FALSE, OBJECT_TYPE_PLACEABLE);
    }
    //End destruction
    object oColumn = CreateObject(OBJECT_TYPE_PLACEABLE, "lab_a4_plc_4", lNew);

return oColumn;
}
//------------------------------------------------------------------------------
void Lab_A4_CreateConstructionPart(object oItem, object oTarget)
{
    SetUseableFlag(oTarget, FALSE);
    object oNew;
    string sResRef;
    string sItemRR = GetResRef(oItem);
    string sTargetTag = GetTag(oTarget);

    if(sItemRR == "lab_a4_it_3")
        oNew = Lab_A4_CreateColumn(GetLocation(oTarget));
    else
    {
        string sID = GetStringRight(GetResRef(oItem), 1);
        string sResRef = "lab_a4_plc_" + sID;
        string sNewTag;
        if(sResRef == "lab_a4_plc_6")
            sNewTag = "lab_a4_powerstone_l";
        else if(sResRef == "lab_a4_plc_7")
            sNewTag = "lab_a4_conc_r";

        oNew = CreateObject(OBJECT_TYPE_PLACEABLE, sResRef, UpLocation(GetLocation(oTarget), Lab_A4_GetHeight(sItemRR, sTargetTag)), FALSE, sNewTag);

        if(StringToInt(sID)>4)
        {
            object oCounter = GetObjectByTag("lab_a4_plc_build_counter");
            SetLocalInt(oCounter, "BuildCount", GetLocalInt(oCounter, "BuildCount")+1);
        }


        if(StringToInt(GetStringRight(sItemRR, 1)) <= 5)
            SetUseableFlag(oNew, TRUE);
        else
            SetUseableFlag(oNew, FALSE);
    }

    SetLocalInt(oNew, "Put", TRUE);
    SetLocalString(oNew, "NextPart", Lab_A4_GetNextPartResRef(oTarget, oNew));
    GarantyDestroyObject(oItem, 0.1);
}
//------------------------------------------------------------------------------
void Lab_A4_LightDamage(location lLoc)
{
    object oBoss = GetObjectByTag("lab_a4_boss");
    location lBoss = GetLocation(oBoss);
    float fDist = GetDistanceBetweenLocations(lLoc, lBoss);
    if(fDist<4.0) //(fDist<=1.5)
    {
        AssignCommand(oBoss, ClearAllActions(TRUE));
        ApplyEffectAtLocation(DURATION_TYPE_INSTANT, EffectVisualEffect(VFX_FNF_WAIL_O_BANSHEES), lBoss);
        // Kill boss
        SetPlotFlag(oBoss, FALSE);
        SetImmortal(oBoss, FALSE);
        AssignCommand(oBoss, SetIsDestroyable(TRUE));
        ApplyEffectToObject(DURATION_TYPE_INSTANT, EffectDamage(10000), oBoss);

        LitTheArea(GetAreaFromLocation(lLoc));
    }
    /*
    else if(fDist<4.0)
    {
        AssignCommand(oBoss, ClearAllActions(TRUE));
        AssignCommand(oBoss, JumpToObject(GetObjectByTag("WP_lab_a4_bossfall")));
        AssignCommand(oBoss, ActionPlayAnimation(ANIMATION_LOOPING_DEAD_BACK, 1.0, 2.0));
    }*/
}
//------------------------------------------------------------------------------
void Lab_A4_StartLightShootProcess(object oStone = OBJECT_SELF)
{
    object oMisalar_L = GetObjectByTag("lab_a4_misalar_l");
    object oMisalar_R = GetObjectByTag("lab_a4_misalar_r");
    object oPower_L = GetObjectByTag("lab_a4_powerstone_l");
    object oPower_R = GetObjectByTag("lab_a4_powerstone_r");
    object oConc_L = GetObjectByTag("lab_a4_conc_l");
    object oConc_R = GetObjectByTag("lab_a4_conc_r");
    object oCrystal = GetObjectByTag("lab_a4_crystal_put");
    location lLoc = GetLocation(GetObjectByTag("lab_a4_fireloc"));

    float fDelay = 0.0;
    //Activate stone
    AssignCommand(oStone, PlayAnimation(ANIMATION_PLACEABLE_ACTIVATE));

    //Beams to misalars
    DelayCommand(fDelay+=1.0, ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectBeam(VFX_BEAM_LIGHTNING, oStone, BODY_NODE_CHEST), oMisalar_L, 2.0));
    DelayCommand(fDelay, ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectBeam(VFX_BEAM_LIGHTNING, oStone, BODY_NODE_CHEST), oMisalar_R, 2.0));

    //Activate misalars
    DelayCommand(fDelay+=1.0, AssignCommand(oMisalar_L, PlayAnimation(ANIMATION_PLACEABLE_ACTIVATE)));
    DelayCommand(fDelay, AssignCommand(oMisalar_R, PlayAnimation(ANIMATION_PLACEABLE_ACTIVATE)));
    //Deactivate stone
    DelayCommand(fDelay, AssignCommand(oStone, PlayAnimation(ANIMATION_PLACEABLE_DEACTIVATE)));

    //Activate power stones
    DelayCommand(fDelay+=1.0, AssignCommand(oPower_L, PlayAnimation(ANIMATION_PLACEABLE_ACTIVATE)));
    DelayCommand(fDelay, AssignCommand(oPower_R, PlayAnimation(ANIMATION_PLACEABLE_ACTIVATE)));

    //Beams to concentrators
    DelayCommand(fDelay+=1.0, ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectBeam(VFX_BEAM_LIGHTNING, oPower_L, BODY_NODE_CHEST), oConc_L, 2.0));
    DelayCommand(fDelay, ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectBeam(VFX_BEAM_LIGHTNING, oPower_R, BODY_NODE_CHEST), oConc_R, 2.0));

    //Activate concentrators
    DelayCommand(fDelay+=1.0, AssignCommand(oConc_L, PlayAnimation(ANIMATION_PLACEABLE_ACTIVATE)));
    DelayCommand(fDelay, AssignCommand(oConc_R, PlayAnimation(ANIMATION_PLACEABLE_ACTIVATE)));
    //Deactivate misalars and power stones
    DelayCommand(fDelay, AssignCommand(oPower_L, PlayAnimation(ANIMATION_PLACEABLE_DEACTIVATE)));
    DelayCommand(fDelay, AssignCommand(oPower_R, PlayAnimation(ANIMATION_PLACEABLE_DEACTIVATE)));
    DelayCommand(fDelay, AssignCommand(oMisalar_L, PlayAnimation(ANIMATION_PLACEABLE_DEACTIVATE)));
    DelayCommand(fDelay, AssignCommand(oMisalar_R, PlayAnimation(ANIMATION_PLACEABLE_DEACTIVATE)));

    //Beams to crystal
    DelayCommand(fDelay+=2.0, ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectBeam(VFX_BEAM_HOLY, oConc_L, BODY_NODE_CHEST), oCrystal, 2.0));
    DelayCommand(fDelay, ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectBeam(VFX_BEAM_HOLY, oConc_R, BODY_NODE_CHEST), oCrystal, 2.0));

    //Fire
    DelayCommand(fDelay+=1.5, ApplyEffectAtLocation(DURATION_TYPE_INSTANT, EffectVisualEffect(VFX_FNF_SUNBEAM), lLoc));
    DelayCommand(fDelay, AssignCommand(oCrystal, Lab_A4_LightDamage(lLoc)));
    //Deactivate concentrators
    DelayCommand(fDelay, AssignCommand(oConc_L, PlayAnimation(ANIMATION_PLACEABLE_DEACTIVATE)));
    DelayCommand(fDelay, AssignCommand(oConc_R, PlayAnimation(ANIMATION_PLACEABLE_DEACTIVATE)));

}
//------------------------------------------------------------------------------
/*location CountPCsNewLocation(object oPC)
{
    vector vPos = GetPosition(oPC);
    vPos = Vector(137.0, vPos.y, vPos.z);
return Location(GetArea(oPC), vPos, 180.0);;
}
//------------------------------------------------------------------------------
void Lab_A4_ThroughPC(object oPC)
{
    SetCutsceneMode(oPC, TRUE);
    AssignCommand(oPC, ClearAllActions());

    //PC Jump
    location lLoc = CountPCsNewLocation(oPC);
    DelayCommand(0.1, AssignCommand(oPC, JumpToLocation(lLoc)));
    DelayCommand(0.1, ApplyEffectAtLocation(DURATION_TYPE_INSTANT, EffectVisualEffect(VFX_COM_CHUNK_STONE_SMALL), lLoc));
    DelayCommand(0.3, SetCutsceneMode(oPC, FALSE));
}
//------------------------------------------------------------------------------
void Lab_A4_BossBeams(object oBoss, object oTrigger)
{
    object oPC;
    int i, nMax = GetNumberOfObjectsInArray(oTrigger, "PCs");
    for(i = 1; i<=nMax; i++)
    {
        ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectBeam(VFX_BEAM_ODD, oBoss, BODY_NODE_CHEST), oPC, 2.0);
        DelayCommand(2.0, Lab_A4_ThroughPC(oPC));
        DelayCommand(2.5, ApplyEffectToObject(DURATION_TYPE_INSTANT, EffectDamage(d20(10), DAMAGE_TYPE_BLUDGEONING), oPC));
        DelayCommand(2.5, ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectKnockdown(), oPC, 3.0));
    }
}
//------------------------------------------------------------------------------
void Lab_A4_TreasureProtection(object oTrigger = OBJECT_SELF)
{
    object oBoss = GetObjectByTag("lab_a4_boss");
    if(!GetIsObjectValid(oBoss))
        return;

    object oWP = GetObjectByTag("WP_lab_a4_bossjump");
    if(GetDistanceBetween(oBoss, oWP)>10.0)
    {
        AssignCommand(oBoss, ClearAllActions());
        ApplyEffectToObject(DURATION_TYPE_TEMPORARY, EffectDisappearAppear(GetLocation(oWP)), oBoss, 2.0);
        DelayCommand(2.0, AssignCommand(oBoss, Lab_A4_BossBeams(oBoss, oTrigger)));
    }
}*/
//------------------------------------------------------------------------------





const int LAB_A5_SPHERE_COUNT = 20;
const int LAB_A5_HELP_COST = 200000;
//------------------------------------------------------------------------------
void Lab_A5_InitArea()
{
    object oArea = OBJECT_SELF;
    if(GetLocalInt(oArea, "Initialized"))
        return;

    SetLocalInt(oArea, "Initialized", TRUE);

    // Выбираем правильную сферу
    object oWP = GetObjectByTag("WP_lab_a5_exit");
    int nRandom = 1+Random(LAB_A5_SPHERE_COUNT);
    object oCorrectSphere = GetNearestObjectByTag("lab_a5_plc_1", oWP, nRandom);
    SetLocalInt(oCorrectSphere, "Correct", TRUE);
    SetLocalInt(oArea, "SphereCount", LAB_A5_SPHERE_COUNT);
}
//------------------------------------------------------------------------------
void Lab_A5_DestroyAllSpheres()
{
    int nNth = 1;
    float fDelay;
    object oWP = GetObjectByTag("WP_lab_a5_exit");
    object oSphere = GetNearestObjectByTag("lab_a5_plc_1", oWP, nNth);
    while(GetIsObjectValid(oSphere))
    {
        DelayCommand(fDelay+=0.3, ApplyEffectToObject(DURATION_TYPE_INSTANT, EffectVisualEffect(VFX_FNF_ELECTRIC_EXPLOSION), oSphere));
        SetPlotFlag(oSphere, FALSE);
        DestroyObject(oSphere, fDelay+0.1);

        oSphere = GetNearestObjectByTag("lab_a5_plc_1", oWP, ++nNth);
    }
}
//------------------------------------------------------------------------------
void Lab_A5_SpawnBoss()
{
    location lLoc = GetLocation(GetObjectByTag("WP_lab_a5_exit"));
    ApplyEffectAtLocation(DURATION_TYPE_INSTANT, EffectVisualEffect(VFX_IMP_DIVINE_STRIKE_HOLY), lLoc);
    CreateObject(OBJECT_TYPE_CREATURE, "lab_a5_boss", lLoc, TRUE);
}
//------------------------------------------------------------------------------
void Lab_A5_Final()
{
    Lab_A5_DestroyAllSpheres();
    DelayCommand(3.0, Lab_A5_SpawnBoss());
}
//------------------------------------------------------------------------------
object Lab_A5_SelectSphereToDestroy(int nCount)
{
    object oSphere = GetObjectByTag("lab_a5_plc_1", Random(nCount));
    if(GetLocalInt(oSphere, "Correct") || !GetPlotFlag(oSphere))// Если сфера уже выбрана для уничтожения
        oSphere = Lab_A5_SelectSphereToDestroy(nCount);
return oSphere;
}
//------------------------------------------------------------------------------
void Lab_A5_Help()
{
    object oAltar = OBJECT_SELF;
    object oArea = GetArea(oAltar);
    int nSphereCount = GetLocalInt(oArea, "SphereCount");
    if(nSphereCount <= 2)
        SpeakString("Хозяева этого места благодарят тебя за пожертвование");
    else
    {
        int nSpheresToDestroy = 3;
        if(nSphereCount-nSpheresToDestroy < 2) // Перестраховка
            nSpheresToDestroy = nSphereCount-2;

        object oSphereToDestroy;
        int i;
        for(i = 0; i<nSpheresToDestroy; i++)
        {
            oSphereToDestroy = Lab_A5_SelectSphereToDestroy(nSphereCount-i);
            ApplyEffectToObject(DURATION_TYPE_INSTANT, EffectVisualEffect(VFX_FNF_ELECTRIC_EXPLOSION), oSphereToDestroy);
            SetPlotFlag(oSphereToDestroy, FALSE);
            DestroyObject(oSphereToDestroy, 0.3);
        }
        SetLocalInt(oArea, "SphereCount", nSphereCount-nSpheresToDestroy);
    }
}
