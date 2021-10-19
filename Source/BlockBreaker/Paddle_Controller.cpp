// Fill out your copyright notice in the Description page of Project Settings.


#include "Paddle_Controller.h"

#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"

#include "Paddle.h"
#include "Ball.h"

APaddle_Controller::APaddle_Controller()
{

}

void APaddle_Controller::BeginPlay()
{
	TArray<AActor*> CameraActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), CameraActors);

	FViewTargetTransitionParams Params;
	SetViewTarget(CameraActors[0], Params);

	SpawnNewBall();
}

void APaddle_Controller::SetupInputComponent()
{
	Super::SetupInputComponent();

	EnableInput(this);

	InputComponent->BindAction("Launch", IE_Pressed, this, &APaddle_Controller::Launch);
}

void APaddle_Controller::Launch()
{
	MyBall->Launch();
}

void APaddle_Controller::SpawnNewBall()
{
	if (!MyBall) {
		MyBall = nullptr;
	}

	if (Ballobj) {
		MyBall = GetWorld()->SpawnActor<ABall>(Ballobj, SpawnLocation, SpawnRotation, SpawnInfo);
	}
}
