#pragma once

#include <CoreMinimal.h>
#include <GameFramework/Actor.h>
#include "HexTileActor.generated.h"

USTRUCT(BlueprintType)
struct FCubeHex
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int q;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int r;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int s;
	
	FCubeHex(int _q = 0, int _r = 0) : q(_q), r(_r), s(-_q - _r)
	{
		check(q + r + s == 0); // Valid cube coords must sum back to 0
	}
};

USTRUCT(BlueprintType)
struct FHexRow
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCubeHex> HexArr{};
	
	FHexRow(){}
	FHexRow(TArray<FCubeHex> InArr) : HexArr(InArr){}
};

//FORCEINLINE bool operator == (const FCubeHex& a, const FCubeHex& b)
//{
//	return a.q == b.q && a.r == b.r && a.s == b.s;
//}
//
//FORCEINLINE bool operator!= (const FCubeHex& a, const FCubeHex& b)
//{
//	return !(a == b);
//}
//
//FORCEINLINE FCubeHex operator+= (const FCubeHex& a, const FCubeHex& b)
//{
//	return FCubeHex(a.q + b.q, a.r + b.r);
//}
//
//FORCEINLINE FCubeHex operator-= (const FCubeHex& a, const FCubeHex& b)
//{
//	return FCubeHex(a.q - b.q, a.r - b.r);
//}
//
//FORCEINLINE FCubeHex operator*= (const FCubeHex& a, const FCubeHex& b)
//{
//	return FCubeHex(a.q * b.q, a.r * b.r);
//}


class UInstancedStaticMesh;

UCLASS()
class BASICHEXGRID_API AHexTileActor : public AActor
{
	GENERATED_BODY()
public:
	AHexTileActor();


	UFUNCTION(BlueprintCallable, BlueprintPure)
	FVector GetHexTilePositionWorldSpace(FCubeHex& Hex, float HexRadius = 50.0f, float ZOffset = 0.0f)
	{
		float PosX = HexRadius * (FMath::Sqrt(3.0f) * Hex.q + FMath::Sqrt(3.0) / 2 * Hex.r);
		float PosY = HexRadius * 3.0 / 2 * Hex.r;
		return FVector(PosX, PosY, ZOffset);
	}

	UFUNCTION(BlueprintCallable)
	void ClearTileInstances();

	UFUNCTION()
	void AddTileInstancesWorldSpace(TArray<FTransform> Instances);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInstancedStaticMeshComponent* HexTileInstancedMesh = nullptr;
};

