// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AuraEffectActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "../../../../Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "../../../../Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "../../../../Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayEffectTypes.h"

// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot")));

	/*Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere"); 

	Sphere->SetupAttachment(GetRootComponent());*/ // 블프로 하기 위해서 영상에서는 지움 
}

/*void AAuraEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 인터페이스를 캐스팅하도록하겠다.플레이어에 있던 인터페이스를 캐스팅할 것이다.

	// TODO : Change this to apply a Gameplay Effect. For now, using const_cast a hack!
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		// 어트리뷰트 세트가 있는 경우 세팅하는 것 우리가 만든 것으로 세팅하도록하겠다. 
		
		//우리가 만든것을 가지고 오기 때문에 앞에 const를 붙여주어야한다 그렇지 않으면 오류가 생긴다.
		const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass()));
		
		// const_cast를 통해서 속성을 바꾸는 작업 
		UAuraAttributeSet* MutableAuraAttributeSet = const_cast<UAuraAttributeSet*>(AuraAttributeSet); // 가변 오라 속성세트
		MutableAuraAttributeSet->SetHealth(AuraAttributeSet->GetHealth() + 25.0f); // const이기 떄문에 오류가 생길 것인데 이것은 하면 안되는 행동이지만 배우기 위해 잠시 할 거라고한다. 가변 속성세트를 만들어서 하도록한다.
		MutableAuraAttributeSet->SetMana(AuraAttributeSet->GetMana() - 25.0f);
		
		Destroy(); // 오버랩이 되었으니까 해당 메쉬를 지워주겠다. 
	}
}

void AAuraEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}*/

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

	/*Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AAuraEffectActor::EndOverlap);*/
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC == nullptr) return;

	check(GameplayEffectClass);
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();// 이펙트 컨텍스트 게임플레이 컨텍스트를 반환한다.  
	EffectContextHandle.AddSourceObject(this); // 소스 객체를 저장하고 추가하면 된다. 효과에 대한 것을 저장할 수 있다. 
	FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1.0f, EffectContextHandle);
	TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}

