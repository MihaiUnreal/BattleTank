// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerUI.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include <assert.h>


UPlayerUI::UPlayerUI(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//// .cpp constructor
	//ConstructorHelpers::FClassFinder<UUserWidget> PlayerUIClassFinder(TEXT("/Game/GUI/PlayerUI_BP"));

	//if (PlayerUIClassFinder.Succeeded())
	//{
	//	PlayerUIClass = PlayerUIClassFinder.Class;
	//}
}

bool UPlayerUI::Initialize()
{
	Super::Initialize();

	//// beginplay

	//if (PlayerUIWidget)
	//{
		// setup main widget
		//this->AddToViewport();

		//m_CrosshairWidget = PlayerUIWidget->GetWidgetFromName("AimPoint");

		//UE_LOG(LogTemp, Warning, TEXT("PlayerUI crosshair %s"), *(m_CrosshairWidget->GetName()));

		//UE_LOG(LogTemp, Warning, TEXT("PlayerUIWidget has been created!"));
	//}

	return true;
}


void UPlayerUI::PostLoad()
{
	//assert(GetWorld() != nullptr);
	//assert(World->GetGameInstance() != nullptr);

	//UWorld* World = GetWorld();
	//UGameInstance* GameInstance = World->GetGameInstance();

	// create the widget
	//PlayerUIWidget = CreateWidget<UPlayerUI>(GetWorld()->GetFirstPlayerController(), PlayerUIClass);
}