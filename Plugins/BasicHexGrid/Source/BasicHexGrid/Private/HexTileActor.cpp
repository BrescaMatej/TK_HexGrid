#include "HexTileActor.h"
#include <Components/InstancedStaticMeshComponent.h>

AHexTileActor::AHexTileActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	HexTileInstancedMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Hex Tile Mesh"));
	SetRootComponent(HexTileInstancedMesh);
	// check(HexTileInstancedMesh); // Must be valid
}

void AHexTileActor::ClearTileInstances()
{
	HexTileInstancedMesh->ClearInstances();
}

void AHexTileActor::AddTileInstancesWorldSpace(TArray<FTransform> Instances)
{
	FTransformArrayA2 TfArr;
	TfArr.Empty();
	TfArr.Append(Instances);
	
	HexTileInstancedMesh->AddInstances(TfArr, false, true);
}