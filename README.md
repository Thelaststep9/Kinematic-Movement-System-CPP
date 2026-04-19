# Unreal Engine C++ | Kinematic Actor Movement System

A high-performance, frame-rate independent system for controlling 3D actor movement and rotation. Designed for precision-based gameplay where predictable motion is critical.

## 📺 Technical Showcase
[![Watch the Showcase](https://img.youtube.com/vi/YOUR_VIDEO_ID/maxresdefault.jpg)](https://www.youtube.com/watch?v=t6Du1QYcxtQ)


---

## 🛠️ Project Overview
This project features a custom `AMovingPlatform` class written with C++ in Unreal Engine. Unlike standard physics-based actors, this system utilizes a manual kinematic update loop to ensure 100% predictable movement, a necessity for the timed obstacle course game this system was built for.

### Key Technical Features:
* **Linear Kinematics:** Position updates calculated via velocity vectors.
* **Frame-Rate Independence:** All movement and rotation are scaled by `DeltaTime`, ensuring consistent speeds across different hardware.
* **Overshoot & Drift Correction:** Implemented logic to calculate exact "snap" points when a distance threshold is reached. This prevents the "floating point creep" that often causes moving platforms to slowly drift out of sync over time.
* **Angular Motion:** Utilizes local-space rotation logic to allow actors to spin smoothly on their own axes.

---

## 🔍 Code Highlight: Precision Reset Logic
The most important part of this implementation is ensuring the platform never loses its place. Instead of a simple velocity reversal, the system manually re-aligns the actor to the intended target location:

```cpp
if (DistanceMoved >= MoveDistance)
{
    // Calculate the exact intended stop point to prevent drifting
    FVector MoveDirection = PlatformVelocity.GetSafeNormal();
    FVector NewStartLocation = StartLocation + MoveDirection * MoveDistance;

    // Snap to the exact location and reset for return journey
    SetActorLocation(NewStartLocation);
    StartLocation = NewStartLocation;
    PlatformVelocity = -PlatformVelocity;
}
