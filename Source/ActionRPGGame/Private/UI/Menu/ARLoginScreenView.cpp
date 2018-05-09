// Fill out your copyright notice in the Description page of Project Settings.

#include "ARLoginScreenView.h"
#include "ARGameInstance.h"



void UARLoginScreenView::NativeConstruct()
{
	Super::NativeConstruct();

	LoginButton->OnClicked.AddDynamic(this, &UARLoginScreenView::OnLoginClicked);
}

void UARLoginScreenView::OnLoginClicked()
{
	if (UserNameBox->GetText().IsEmpty())
	{
		WarrningText->SetText(FText::FromString("Enter User Name"));
		return;
	}
	if (PasswordBox->GetText().IsEmpty())
	{
		WarrningText->SetText(FText::FromString("Enter User Name"));
		return;
	}
	
	if (UARGameInstance* GI = Cast<UARGameInstance>(GetOwningPlayer()->GetGameInstance()))
	{
		GI->OnLoginSuccess.AddDynamic(this, &UARLoginScreenView::OnLoginSuccess);
		GI->OnLoginFailed.AddDynamic(this, &UARLoginScreenView::OnLoginFailed);
		GI->AttemptLogin(UserNameBox->GetText().ToString(), PasswordBox->GetText().ToString());
	}
}

void UARLoginScreenView::OnLoginSuccess()
{
	if (UARGameInstance* GI = Cast<UARGameInstance>(GetOwningPlayer()->GetGameInstance()))
	{
		WarrningText->SetText(FText::FromString("Login Success"));
		GI->OnLoginSuccess.RemoveDynamic(this, &UARLoginScreenView::OnLoginSuccess);
		GI->OnLoginFailed.RemoveDynamic(this, &UARLoginScreenView::OnLoginFailed);
	}
}


void UARLoginScreenView::OnLoginFailed()
{

}