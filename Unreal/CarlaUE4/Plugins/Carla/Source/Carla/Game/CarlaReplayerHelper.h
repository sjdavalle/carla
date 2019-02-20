// Copyright (c) 2017 Computer Vision Center (CVC) at the Universitat Autonoma
// de Barcelona (UAB).
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#pragma once

class UCarlaEpisode;
class FActorView;
struct FActorDescription;

class CarlaReplayerHelper
{

public:

  // set the episode to use
  void SetEpisode(UCarlaEpisode *ThisEpisode)
  {
    Episode = ThisEpisode;
  }

  // replay event for creating actor
  std::pair<int, uint32_t> ProcessReplayerEventAdd(
      FVector Location,
      FVector Rotation,
      CarlaRecorderActorDescription Description,
      uint32_t DesiredId);

  // replay event for removing actor
  bool ProcessReplayerEventDel(uint32_t DatabaseId);

  // replay event for parenting actors
  bool ProcessReplayerEventParent(uint32_t ChildId, uint32_t ParentId);

  // reposition actors
  bool ProcessReplayerPosition(CarlaRecorderPosition Pos1, CarlaRecorderPosition Pos2, double Per);

  // replay event for traffic light state
  bool ProcessReplayerStateTrafficLight(CarlaRecorderStateTrafficLight State);

  // replay finish
  bool ProcessReplayerFinish(bool bApplyAutopilot);

  // set the camera position to follow an actor
  bool SetCameraPosition(uint32_t Id, FVector Offset, FQuat Rotation);

private:

  UCarlaEpisode *Episode {nullptr};

  std::pair<int, FActorView &>TryToCreateReplayerActor(
    FVector &Location,
    FVector &Rotation,
    FActorDescription &ActorDesc,
    uint32_t DesiredId);

  AActor *FindTrafficLightAt(FVector Location);

  // enable / disable physics for an actor
  bool SetActorSimulatePhysics(FActorView &ActorView, bool bEnabled);
  // enable / disable autopilot for an actor
  bool SetActorAutopilot(FActorView &ActorView, bool bEnabled);

};