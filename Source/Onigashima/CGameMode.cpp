#include "CGameMode.h"

ACGameMode::ACGameMode()
{
	ConstructorHelpers::FClassFinder<APawn> pawn(TEXT("/Script/Engine.Blueprint'/Game/ODH/Blueprint/BP_VRPlayer.BP_VRPlayer_C'"));
	if (pawn.Succeeded())
		DefaultPawnClass = pawn.Class;

}