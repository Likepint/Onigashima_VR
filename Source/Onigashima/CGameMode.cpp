#include "CGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

ACGameMode::ACGameMode()
{
	ConstructorHelpers::FClassFinder<APawn> pawn(TEXT("/Script/Engine.Blueprint'/Game/ODH/Blueprint/BP_VRPlayer.BP_VRPlayer_C'"));
	if (pawn.Succeeded())
		DefaultPawnClass = pawn.Class;



	// 배경음악
	ConstructorHelpers::FObjectFinder<USoundBase> tmpSound_1(TEXT("/Script/Engine.SoundWave'/Game/KJY/Peaceful_Moments.Peaceful_Moments'"));
	if (tmpSound_1.Succeeded()) { GameSound = tmpSound_1.Object; }


	// 용과의 전투 시작 음악
	ConstructorHelpers::FObjectFinder<USoundBase> tmpSound_2(TEXT("/Script/Engine.SoundWave'/Game/KJY/ARK_Manticore.ARK_Manticore'"));
	if (tmpSound_2.Succeeded()) { CombatSound = tmpSound_2.Object; }


}

//BeginPlay는 사운드 추가용으로 만들었습니다.
void ACGameMode::BeginPlay()
{
	//사운드 플레이 추가
	if (GameSound && GetWorld()) { 
		CurrentAudioComponent = UGameplayStatics::SpawnSound2D(GetWorld(), GameSound);}


	//UGameplayStatics::PlaySound2D(GetWorld(), GameSound);
}


void ACGameMode::ChangeBackgroundMusic(USoundBase* NewSound)
{
	if (NewSound && GetWorld())
	{
		// 현재 재생 중인 사운드가 있으면 중지
		if (CurrentAudioComponent && CurrentAudioComponent->IsPlaying())
		{
			CurrentAudioComponent->Stop();
		}

		CurrentAudioComponent = UGameplayStatics::SpawnSound2D(GetWorld(), NewSound);
	}
}
