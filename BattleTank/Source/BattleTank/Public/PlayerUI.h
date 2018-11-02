// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerUI.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API UPlayerUI : public UUserWidget
{
	GENERATED_BODY()

public:
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
//	TSubclassOf<class UUserWidget> PlayerUIClass;

//	UPROPERTY(VisibleAnywhere)
//	class UUserWidget* PlayerUIWidget;

//	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
//	class UImage* AimPoint;

	UPlayerUI(const FObjectInitializer& ObjectInitializer);

private:
	// replacement for BeginPlay() as widgets don't have any
	virtual bool Initialize() override;

	virtual void PostLoad() override;

};
