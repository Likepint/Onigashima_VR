#include "CGameMode.h"

ACGameMode::ACGameMode()
{
	ConstructorHelpers::FClassFinder<APawn> pawn(L"/Script/Engine.Blueprint'/Game/PJS/Characters/BP_CCharacter_PJS.BP_CCharacter_PJS_C'");
	if (pawn.Succeeded())
		DefaultPawnClass = pawn.Class;

}
