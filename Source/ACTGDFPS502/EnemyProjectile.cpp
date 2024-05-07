// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyProjectile.h"
#include "Components/SphereComponent.h"

AEnemyProjectile::AEnemyProjectile()
{
	CollisionComp->BodyInstance.SetCollisionProfileName("EnemyProjectile");
}
