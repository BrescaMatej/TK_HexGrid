// Fill out your copyright notice in the Description page of Project Settings.
#include "HexGridActor.h"


// Sets default values
AHexGridActor::AHexGridActor()
{
	PrimaryActorTick.bCanEverTick = false;
	//InitializeHexGrid(HexagonMap);
}

void AHexGridActor::InitializeHexGrid(TArray<FHexRow> GridMap)
{
	for (FHexRow Row : GridMap)
	{
		for (FCubeHex Hex : Row.HexArr)
		{
			if (AHexTileActor* HexActor = GetWorld()->SpawnActor<AHexTileActor>(HexTileTemplate))
			{
				HexActor->SetActorLocation(HexActor->GetHexTilePosition(Hex));
				
				HexActor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
			}
		}
	}
}

void AHexGridActor::CleanupHexGrid()
{
	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);
	for (AActor* Attached : AttachedActors)
	{
		Attached->MarkAsGarbage();
	}
}
