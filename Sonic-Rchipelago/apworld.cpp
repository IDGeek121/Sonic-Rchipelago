#include <sstream>

#include "apworld.h"

namespace {
  struct Game_state {
    struct ap::message message;

    std::string slot;

    // Items received
    int received_sonic_tokens[4]; // Only the count of tokens matters
    int received_chaos_emeralds[7];
    bool received_characters[9];
    bool received_courses[4];

    // Items sent
    bool sent_sonic_tokens[4][5]; // Each individual token matters
    unsigned char sent_chaos_emeralds[4]; // 1 = Chaos Emerald 1, 2 = Chaos Emerald 2. Logical OR
    bool sent_grand_prix_wins[5];
    bool sent_challenge_race_wins[4];
  };

  std::string get_message_item_recv(AP_ItemRecvMessage* message);
  std::string get_message_item_send(AP_ItemSendMessage* message);
  void item_clear();
  void item_recv(int id, bool notify);
  void item_recv_chaos_emerald(int id);
  void item_recv_character(int id);
  void item_recv_ring(int id);
  void item_recv_sonic_token(int id);
  void location_checked(int id);
  void location_checked_challenge_race_win(int id);
  void location_checked_chaos_emerald(int id);
  void location_checked_grand_prix_win(int id);
  void location_checked_sonic_token(int id);

  struct Game_state game_state;

  std::string get_message_item_recv(AP_ItemRecvMessage* message) {
    std::stringstream stream;

    if (game_state.slot == message->sendPlayer) {
      stream << "Found " << message->item;
    } else {
      stream << "Received " << message->item << " from " << message->sendPlayer;
    }

    return stream.str();
  }

  std::string get_message_item_send(AP_ItemSendMessage* message) {
    std::stringstream stream;
    stream << "Sent " << message->item << " to " << message->recvPlayer;
    return stream.str();
  }

  void item_clear() {
    PrintDebug("item_clear()\n");

    for (int i = 0; i < 4; ++i) {
      game_state.received_sonic_tokens[i] = 0;
    }
    for (int i = 0; i < 7; ++i) {
      game_state.received_chaos_emeralds[i] = 0;
    }
    for (int i = 0; i <= Characters_EggRobo; ++i) {
      game_state.received_characters[i] = 0;
    }
    for (int i = 0; i < 5; ++i) {
      game_state.sent_grand_prix_wins[i] = 0;
    }
    for (int i = 0; i < 4; ++i) {
      game_state.sent_challenge_race_wins[i] = 0;
    }
  }

  void item_recv(int id, bool notify) {
    PrintDebug("item_recv(%d, %d)\n", id, notify);
    
    switch (id) {
    case ap::item::ProgressiveResortIslandSonicToken:
    case ap::item::ProgressiveRadicalCitySonicToken:
    case ap::item::ProgressiveRegalRuinSonicToken:
    case ap::item::ProgressiveReactiveFactorySonicToken:
      item_recv_sonic_token(id);
      break;
    case ap::item::BlueChaosEmerald:
    case ap::item::GreenChaosEmerald:
    case ap::item::PurpleChaosEmerald:
    case ap::item::YellowChaosEmerald:
    case ap::item::OrangeChaosEmerald:
    case ap::item::RedChaosEmerald:
    case ap::item::WhiteChaosEmerald:
      item_recv_chaos_emerald(id);
      break;
    case ap::item::Sonic:
    case ap::item::Tails:
    case ap::item::Knuckles:
    case ap::item::Amy:
    case ap::item::Robotnik:
    case ap::item::MetalSonic:
    case ap::item::TailsDoll:
    case ap::item::MetalKnuckles:
    case ap::item::EggRobo:
      item_recv_character(id);
      break;
    case ap::item::Ring:
      item_recv_ring(50);
      break;
    default:
      PrintDebug("item_recv: Item ID %d not implemented.\n", id);
    }
  }

  void item_recv_chaos_emerald(int id) {
    PrintDebug("item_recv_chaos_emerald(%d)\n", id);

    int *ChaosEmerald = &game_state.received_chaos_emeralds[id - ap::item::BlueChaosEmerald];
    *ChaosEmerald = 2;
  }

  void item_recv_character(int id) {
    PrintDebug("item_recv_character(%d)\n", id);

    game_state.received_characters[id - ap::item::Sonic] = true;
  }

  void item_recv_ring(int count) {
    PrintDebug("item_recv_ring(%d)\n", count);

    Players[0].RingCount += count;
  }

  void item_recv_sonic_token(int id) {
    PrintDebug("item_recv_sonic_token(%d)\n", id);

    int *SonicToken = &game_state.received_sonic_tokens[id - ap::item::ProgressiveResortIslandSonicToken];
    ++(*SonicToken);
    if (*SonicToken > 5) {
      *SonicToken = 5;
    }
  }

  void location_checked(int id) {
    PrintDebug("location_checked(%d)\n", id);

    if (id >= ap::location::ResortIslandSonicToken1 && id <= ap::location::RegalRuinSonicToken5) {
      location_checked_sonic_token(id);
    } else if (id >= ap::location::ResortIslandChaosEmerald && id <= ap::location::RegalRuinChaosEmerald2) {
      location_checked_chaos_emerald(id);
    } else if (id >= ap::location::ResortIslandGrandPrixWin && id <= ap::location::RadiantEmeraldGrandPrixWin) {
      location_checked_grand_prix_win(id);
    } else if (id >= ap::location::ResortIslandChallengeRaceWin && id <= ap::location::RegalRuinChallengeRaceWin) {
      location_checked_challenge_race_win(id);
    } else {
      PrintDebug("location_checked: Location ID %d not implemented.\n", id);
    }
  }

  void location_checked_challenge_race_win(int id) {
    PrintDebug("location_checked_challenge_race_win(%d)\n", id);

    Courses course = (Courses)(1 + (id - ap::location::ResortIslandChallengeRaceWin));

    game_state.sent_challenge_race_wins[course - Courses_ResortIsland] = 1;
  }

  void location_checked_chaos_emerald(int id) {
    PrintDebug("location_checked_chaos_emerald(%d)\n", id);

    Courses course = (Courses)(1 + ((id - ap::location::ResortIslandChaosEmerald) / 2));
    int i = ((id - ap::location::ResortIslandChaosEmerald) % 2);

    game_state.sent_chaos_emeralds[course - Courses_ResortIsland] |= (1 << i);
  }

  void location_checked_grand_prix_win(int id) {
    PrintDebug("location_checked_grand_prix_win(%d)\n", id);

    Courses course = (Courses)(1 + (id - ap::location::ResortIslandGrandPrixWin));

    game_state.sent_grand_prix_wins[course - Courses_ResortIsland] = 1;
  }

  void location_checked_sonic_token(int id) {
    PrintDebug("location_checked_sonic_token(%d)\n", id);

    Courses course = (Courses)(1 + ((id - ap::location::ResortIslandSonicToken1) / 5));
    int i = ((id - ap::location::ResortIslandSonicToken1) % 5);

    game_state.sent_sonic_tokens[course - Courses_ResortIsland][i] = 1;
  }
}

namespace ap {
  const struct message* get_message() {
    if (game_state.message.time > 0) {
      game_state.message.time--;
    }
    if (game_state.message.time == 0 && AP_IsMessagePending()) {
      struct AP_Message* message = AP_GetLatestMessage();

      switch (message->type) {
      case AP_MessageType::ItemSend:
        game_state.message.text = get_message_item_send(dynamic_cast<AP_ItemSendMessage*>(message));
        break;
      case AP_MessageType::ItemRecv:
        game_state.message.text = get_message_item_recv(dynamic_cast<AP_ItemRecvMessage*>(message));
        break;
      default:
        game_state.message.text = message->text;
        break;
      }
      game_state.message.time = 90;
      AP_ClearLatestMessage();
    }
    return &game_state.message;
  }

  void init(const char *host, const char *slot, const char *password) {
    AP_Init(host, "Sonic R", slot, password);

    AP_SetItemClearCallback(&item_clear);
    AP_SetItemRecvCallback(&item_recv);
    AP_SetLocationCheckedCallback(&location_checked);

    game_state.slot = slot;

    AP_Start();
  }

  void send_item_challenge_race_win(Courses course) {
    PrintDebug("send_item_challenge_race_win(%d)\n", course);

    AP_SendItem(ap::location::ResortIslandChallengeRaceWin + (course - Courses_ResortIsland));
  }

  void send_item_chaos_emerald(Courses course, int i) {
    PrintDebug("send_item_chaos_emerald(%d, %d)\n", course, i);

    AP_SendItem(ap::location::ResortIslandChaosEmerald + ((course - Courses_ResortIsland) * 2) + i);
  }

  void send_item_grand_prix_win(Courses course) {
    PrintDebug("send_item_grand_prix_win(%d)\n", course);

    AP_SendItem(ap::location::ResortIslandGrandPrixWin + (course - Courses_ResortIsland));
  }

  void send_item_sonic_token(Courses course, int i) {
    PrintDebug("send_item_sonic_token(%d, %d)\n", course, i);

    AP_SendItem(ap::location::ResortIslandSonicToken1 + ((course - Courses_ResortIsland) * 5) + i);
  }

  // Return 2 if the file should have the Chaos Emerald at index i [0, 6).
  int received_chaos_emerald_to_file(int i) {
    return game_state.received_chaos_emeralds[i];
  }

  bool received_character(Characters i) {
    return game_state.received_characters[i];
  }

  // Return number of Sonic Tokens that have been received for a given course.
  int received_sonic_tokens(Courses course) {
    return game_state.received_sonic_tokens[course - Courses_ResortIsland];
  }

  // Return true if the challenge race for a course has been beaten already. False otherwise.
  bool sent_challenge_race_win(Courses course) {
    return game_state.sent_challenge_race_wins[course - Courses_ResortIsland];
  }

  // Return true if Chaos Emerald #i on course has been sent already. False otherwise.
  bool sent_chaos_emerald(Courses course, int i) {
    return (game_state.sent_chaos_emeralds[course - Courses_ResortIsland] >> i) & 1;
  }

  bool sent_grand_prix_win(Courses course) {
    return game_state.sent_grand_prix_wins[course - Courses_ResortIsland];
  }

  // Return true if token #i on course has been sent already. False otherwise.
  bool sent_sonic_token(Courses course, int i) {
    return game_state.sent_sonic_tokens[course - Courses_ResortIsland][i];
  }
}
