// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

USTRUCT()
struct FSpawnPosition
{
	GENERATED_USTRUCT_BODY()

	FVector Location;
	float Rotation;
	float Scale;
};

class UActorPool;

UCLASS()
class TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Settings")
		void PlaceActors(
			TSubclassOf<AActor> ToSpawn,
			int MinSpawn = 1,
			int MaxSpawn = 1,
			float Radius = 500,
			float MinScale = 1,
			float MaxScale = 1);


	UFUNCTION(BlueprintCallable, Category = "Settings")
		void PlaceAIPawns(
			TSubclassOf<APawn> ToSpawn,
			int MinSpawn = 1,
			int MaxSpawn = 1,
			float Radius = 500);

		
	UFUNCTION(BlueprintCallable, Category = "Pool")
		void SetPool(UActorPool* InPool);

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, Category = "Navigation")
		FVector NavigationBoundsOffset;
	
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
		FVector MinExtent;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
		FVector MaxExtent;

private:
	bool FindEmptyLocation(FVector& OutLocation, float Radius);

	template<class T>
	void RandomlyPlaceActors(TSubclassOf<T> ToSpawn, int MinSpawn = 1, int MaxSpawn = 1, float Radius = 500, float MinScale = 1, float MaxScale = 1);

	void PlaceActor(TSubclassOf<AActor> ToSpawn, FSpawnPosition SpawnPosition);

	void PlaceActor(TSubclassOf<APawn> ToSpawn, FSpawnPosition SpawnPosition);
	
	bool CanSpawnAtLocation(FVector Location, float Radius);

	void PositionNavMeshBoundsVolume();

	TArray<FSpawnPosition> RandomSpawnPositions(int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale);

	UActorPool* Pool;
	
	AActor* NavMeshBoundsVolume;
};

//template<class T>
//inline void ATile::RandomlyPlaceActors(TSubclassOf<T> ToSpawn, int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale)
//{
//}
