#ifndef APWORLD_H
#define APWORLD_H

#include <SonicRModLoader.h>
#include <Archipelago.h>

namespace ap {
  struct message {
    std::string text;
    int time;
  };

  enum item {
    ProgressiveResortIslandSonicToken = 1,
    ProgressiveRadicalCitySonicToken,
    ProgressiveReactiveFactorySonicToken,
    ProgressiveRegalRuinSonicToken,
    BlueChaosEmerald,
    GreenChaosEmerald,
    PurpleChaosEmerald,
    YellowChaosEmerald,
    OrangeChaosEmerald,
    RedChaosEmerald,
    WhiteChaosEmerald,
    Ring,
    Sonic,
    Tails,
    Knuckles,
    Amy,
    Robotnik,
    MetalSonic,
    TailsDoll,
    MetalKnuckles,
    EggRobo,
  };

  enum location {
    ResortIslandSonicToken1 = 1,
    ResortIslandSonicToken2,
    ResortIslandSonicToken3,
    ResortIslandSonicToken4,
    ResortIslandSonicToken5,
    RadicalCitySonicToken1,
    RadicalCitySonicToken2,
    RadicalCitySonicToken3,
    RadicalCitySonicToken4,
    RadicalCitySonicToken5,
    ReactiveFactorySonicToken1,
    ReactiveFactorySonicToken2,
    ReactiveFactorySonicToken3,
    ReactiveFactorySonicToken4,
    ReactiveFactorySonicToken5,
    RegalRuinSonicToken1,
    RegalRuinSonicToken2,
    RegalRuinSonicToken3,
    RegalRuinSonicToken4,
    RegalRuinSonicToken5,
    ResortIslandChaosEmerald,
    RadicalCityChaosEmerald1 = 23,
    RadicalCityChaosEmerald2,
    ReactiveFactoryChaosEmerald1,
    ReactiveFactoryChaosEmerald2,
    RegalRuinChaosEmerald1,
    RegalRuinChaosEmerald2,
    ResortIslandGrandPrixWin,
    RadicalCityGrandPrixWin,
    ReactiveFactoryGrandPrixWin,
    RegalRuinGrandPrixWin,
    RadiantEmeraldGrandPrixWin,
    ResortIslandChallengeRaceWin,
    RadicalCityChallengeRaceWin,
    ReactiveFactoryChallengeRaceWin,
    RegalRuinChallengeRaceWin,
  };

  void init(const char*, const char*, const char*);
  const struct message* get_message();
  int received_chaos_emerald_to_file(int i);
  bool received_character(Characters i);
  int received_sonic_tokens(Courses course);
  void send_item_challenge_race_win(Courses course);
  void send_item_chaos_emerald(Courses course, int i);
  void send_item_grand_prix_win(Courses course);
  void send_item_sonic_token(Courses course, int i);
  bool sent_challenge_race_win(Courses course);
  bool sent_chaos_emerald(Courses course, int i);
  bool sent_grand_prix_win(Courses course);
  bool sent_sonic_token(Courses course, int i);
}

#endif
