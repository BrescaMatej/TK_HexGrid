#include "HexGridActor.h"

AHexGridActor::AHexGridActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AHexGridActor::InitializeHexGrid(TArray<FHexRow> GridMap)
{
	CleanupHexGrid();

	AHexTileActor* HexActor = GetWorld()->SpawnActor<AHexTileActor>(HexTileTemplate);
	
	check(HexActor);
	HexActor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	
	TArray<FTransform> InstanceTransforms;
	for (FHexRow Row : GridMap)
	{
		for (FCubeHex Hex : Row.HexArr)
		{
			InstanceTransforms.Add(FTransform(HexActor->GetHexTilePositionWorldSpace(Hex)));
		}
	}

	HexActor->AddTileInstancesWorldSpace(InstanceTransforms);
}

void AHexGridActor::CleanupHexGrid()
{
	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);
	for (AActor* Attached : AttachedActors)
	{
		if (AHexTileActor* AsHexTile = Cast<AHexTileActor>(Attached)) Attached->Destroy();
	}
}