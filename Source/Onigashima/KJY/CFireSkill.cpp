// 현재로선 깡통입니다. 2종의 파이어볼이 같이 상속받는 클래스가 있으면 관리에 용이해보여 상속용 순수가상함수로 만듬.


#include "KJY/CFireSkill.h"

// Sets default values
ACFireSkill::ACFireSkill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACFireSkill::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACFireSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

