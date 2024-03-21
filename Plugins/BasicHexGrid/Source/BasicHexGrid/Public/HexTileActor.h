#pragma once

#include <CoreMinimal.h>
#include <GameFramework/Actor.h>

#include "HexCommon.h"
#include "HexTileActor.generated.h"

class UInstancedStaticMesh;

/*
* Visual representation of hex tile.
* Implementation is inspired by https://www.redblobgames.com/grids/hexagons/
* 
* Currently it's a signle UInstancedStaticMeshComponent which is fed and initialized by the grid actor
*/

UCLASS()
class BASICHEXGRID_API AHexTileActor : public AActor
{
	GENERATED_BODY()
public:
	AHexTileActor();

	UFUNCTION(BlueprintCallable, Category = "BasicHexGrid|HexTile")
	void ClearTileInstances();

	UFUNCTION(BlueprintCallable, Category = "BasicHexGrid|HexTile")
	void AddTileInstancesWorldSpace(TArray<FTransform> Instances);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInstancedStaticMeshComponent* HexTileInstancedMesh = nullptr;
};

