#pragma once

namespace Settings
{
	// Aimbot
	bool Aimbot = false;
	bool Crosshair = false;
	bool AimPrediction = false;
	bool TargetLine = false;
	bool TriggerBot = false;
	bool OnlyShotgun = false;
	bool VisibleOnly = false;
	bool FOVCircle = false;
	bool IgnoreBots = false;
	bool BerziersCurve = false;
	int Bone = 0;
	int Bind = 0;
	int Smooth = 0;
	double Smoothing = 10.0;
	double ShakeSpeed = 2.0;
	double FieldOfView = 80.0;
	double JitterAmount = 0.0;
	double AimbotDistance = 250.0;
	double WorldDistance = 250.0;

	// Visuals
	bool Visuals = true;
	bool Radar = false;
	bool Line = false;
	int Boxes = 2;
	bool Skeleton = false;
	bool HeadDot = false;
	bool Fill = false;
	bool Username = false;
	bool Distance = false;
	bool ActiveWeapon = false;
	
	// World
	bool WorldESP = false;
	bool PickupESP = false;
	bool ContainerESP = false;
	bool SupplyDropESP = false;
	bool LeProxy = false;
	bool VehcileESP = false;
	bool WeakspotAimbot = false;
	bool Building = false;
	bool VehicleESP = false;
	double PickupDistance = 20.0;

	//Exploits
	bool SilentAim = false;
	bool Chams = false;
	bool Wireframe = false;
	bool Wallhacks = false;
	bool KillAll = false;
	bool BulletTP = false;
	bool InstantSearch = false;
	bool NoSpread = false;
}