#include "PJS/CGameMode_PJS.h"

ACGameMode_PJS::ACGameMode_PJS()
{
	ConstructorHelpers::FClassFinder<APawn> pawn(L"/Script/Engine.Blueprint'/Game/PJS/Characters/BP_CCharacter_PJS.BP_CCharacter_PJS_C'");
	if (pawn.Succeeded())
		DefaultPawnClass = pawn.Class;

}
