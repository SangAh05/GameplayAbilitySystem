// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerState.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

AAuraPlayerState::AAuraPlayerState()
{
    AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
    AbilitySystemComponent->SetIsReplicated(true); // 복제에 관한일을 할 것이다.

    
    AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
    
    NetUpdateFrequency = 100.0f; // 서버 클라이언트 업데이트 주기 서버 버전과 동기화하는 빈도
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}
