#include "HexGridActor.h"
#include "HexTileActor.h"

AHexGridActor::AHexGridActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AHexGridActor::InitializeHexGrid(TArray<FHexRow> GridMap)
{
	CleanupHexGrid();

	AHexTileActor* HexActor = GetWorld()->SpawnActor<AHexTileActor>(HexTileTemplate);
	// check(HexActor);
	HexActor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	
	TArray<FTransform> InstanceTransforms;
	for (FHexRow Row : GridMap)
	{
		for (FHex Hex : Row.GetArr())
		{
			InstanceTransforms.Add(FTransform(GetHexTilePositionWorldSpace(Hex)));
		}
	}

	HexActor->AddTileInstancesWorldSpace(InstanceTransforms);
	HexGridMap.Append(GridMap);
}

void AHexGridActor::CleanupHexGrid()
{
	HexGridMap.Empty();

	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);
	for (AActor* Attached : AttachedActors)
	{
		if (AHexTileActor* AsHexTile = Cast<AHexTileActor>(Attached)) Attached->Destroy();
	}
}