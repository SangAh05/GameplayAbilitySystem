// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/AuraHUD.h"
#include "Blueprint/UserWidget.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCPParams)
{
	if (OverlayWidgetContoller == nullptr)
	{
		OverlayWidgetContoller = NewObject<UOverlayWidgetController>(this, OverlayWidgetContollerClass);
		OverlayWidgetContoller->SetWidgetControllerParams(WCPParams);

		return OverlayWidgetContoller;
	}

	return OverlayWidgetContoller;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	// 체크 
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_AuraHUD")); // 크러쉬를 확인하는
	checkf(OverlayWidgetContollerClass, TEXT("Overlay Widget Controller Class unintialized, please out BP_AuraHUD"));

	// 초기화 오버레이 위젯 컨트롤러 구성 위젯 구성 뷰포트에 추가 
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAuraUserWidget>(Widget);

	// 위젯컨트롤러 매개 변수를 만들겠다.
	const FWidgetControllerParams WdigetControllerParams(PC, PS, ASC, AS); // 4가지 주요 변수 넣기 
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WdigetControllerParams); 

	// 셋 함수를 호출하여 두가지를 함께 묶어두기
	OverlayWidget->SetWidgetController(WidgetController);

	Widget->AddToViewport();
}


