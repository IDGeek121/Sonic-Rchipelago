#include <IniFile.hpp>

#include <d3d9.h>

#include "apworld.h"
#include "mod.h"
#include "config.h"


extern "C" void internal_goal() {
  if (Players[0].Character == Characters_SuperSonic) {
    AP_StoryComplete();
  }
}

void __declspec(naked) goal() {
  asm (
    "pushfl\n\t"
    "pushal\n\t"
    "call _internal_goal\n\t"
    "popal\n\t"
    "popfl\n\t;"
    "movl $0x75349c, %eax\n\t"
    "ret\n\t"
  );
}

int in_game = 0;

extern "C" void internal_set_in_game() {
  in_game = 1;
}

void __declspec(naked) set_in_game() {
  asm (
    "pushfl\n\t"
    "pushal\n\t"
    "call _internal_set_in_game\n\t"
    "popal\n\t"
    "popfl\n\t;"
    "movl 0x72e01c, %ecx\n\t"
    "ret\n\t"
  );
}

extern "C" void internal_set_not_in_game() {
  in_game = 0;
}

void __declspec(naked) set_not_in_game() {
  asm (
    "pushfl\n\t"
    "pushal\n\t"
    "call _internal_set_not_in_game\n\t"
    "popal\n\t"
    "popfl\n\t;"
    "xor %edi, %edi\n\t"
    "movl 0x4b53cc, %edi\n\t"
    "ret\n\t"
  );
}

namespace {
  struct SonicRAPMessage {
    std::string text;
    int time;
  };

  struct SonicRAPData {
    // Pointers to objects in the TrackArray. Used to visually show/hide them in-game.
    TrackArrayEntry *SonicTokenObjects[4][5];
    TrackArrayEntry *ChaosEmeraldObjects[4][2];
  };
}

struct SonicRAPData g_SonicRAPData = { 
    .SonicTokenObjects = { 0 },
    .ChaosEmeraldObjects = { 0 },
};

void ParseCourseSpecialItemTable(Courses course) {
  PrintDebug("ParseCourseSpecialItemTable(%d)\n", course);

  int CurToken = 0;
  g_SonicRAPData.ChaosEmeraldObjects[course - 1][1] = nullptr;

  const SpecialItemTableEntry *cur = CourseSpecialItemTable[course];
  while (cur->TrackArrayIndex != -1) {
    switch (cur->ItemType) {
    case SpecialItem_SonicToken:
      PrintDebug("ParseCourseSpecialItemTable(%d): Found Sonic Token %d at %p.\n", course, CurToken, &TrackArray[cur->TrackArrayIndex]);
      g_SonicRAPData.SonicTokenObjects[course - 1][CurToken++] = &TrackArray[cur->TrackArrayIndex];
      break;
    case SpecialItem_ChaosEmerald1:
      PrintDebug("ParseCourseSpecialItemTable(%d): Found Chaos Emerald 1.\n", course);
      g_SonicRAPData.ChaosEmeraldObjects[course - 1][0] = &TrackArray[cur->TrackArrayIndex];
      break;
    case SpecialItem_ChaosEmerald2:
      PrintDebug("ParseCourseSpecialItemTable(%d): Found Chaos Emerald 2.\n", course);
      g_SonicRAPData.ChaosEmeraldObjects[course - 1][1] = &TrackArray[cur->TrackArrayIndex];
      break;
    default:
      PrintDebug("ParseCourseSpecialItemTable(%d): Skipping item with ItemType %d.\n", course, cur->ItemType);
      break;
    }
    ++cur;
  }
}

void InitObjectPointers() {
  PrintDebug("InitObjectPointers()\n");
  
  for (int i = Courses_ResortIsland; i <= Courses_RadiantEmerald; ++i) {
    ParseCourseSpecialItemTable((Courses)i);
  }
}

void draw_text(const char *buf, int len, int xpos, int ypos, int scale) {
  DWORD prev_colorop;

  D3DDevice->GetTextureStageState(0, D3DTSS_COLOROP, &prev_colorop);
  D3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_ADDSIGNED);
  D3D_BeginScene();
  D3D_SetSamplerState(0);
  D3D_SetBlendMode(1);

  if (TPageBuffers[TPageBufferIndex_TextAtlas] != nullptr) {
    for (int i = 0; i < len; ++i) {
      uint8_t j = buf[i];
      if (j == ' ') {
        xpos += 5 * scale;
      } else if ((j >= '0' && j <= '9') ||
                 (j >= 'A' && j <= 'Z') ||
                 (j >= 'a' && j <= 'z')) {
        if (j >= 'a' && j <= 'z') {
          j -= 87; // Should map to 10
        } else if (j >= 'A' && j <= 'Z') {
          j -= 55; // Should map to 10
        } else if (j >= '0' && j <= '9') {
          j -= 48; // Should map to 0
        }
        D3D_Render2DObject(xpos, ypos, 1.f, text_atlas[j].w * scale, text_atlas[j].h * scale, TPageBufferIndex_TextAtlas, text_atlas[j].x, text_atlas[j].y, text_atlas[j].w, text_atlas[j].h, 0xFFE0E0E0);
        xpos += text_atlas[j].w * scale;
      }
    }
  }

  D3D_EndScene();
  D3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, prev_colorop);
}

void *handle_messages() {
  const struct ap::message *message = ap::get_message();

  if (message->time > 0) {
    draw_text(message->text.c_str(), message->text.length(), 16, 64, 1);
  }

  return D3DDevice;
}

/*
void* temp() {
  const int w = 256;
  const int h = 256;

  DWORD prev_colorop;

  D3DDevice->GetTextureStageState(0, D3DTSS_COLOROP, &prev_colorop);
  D3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_ADDSIGNED);
  D3D_BeginScene();
  D3D_SetSamplerState(0);
  D3D_SetBlendMode(1);

  D3D_Render2DObject(0, 0, 1.f, w, h, TPageBufferIndex_TextAtlas, 0, 0, w, h, 0xFFE0E0E0);
  
  D3D_EndScene();
  D3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, prev_colorop);
  return D3DDevice;
}
*/

void CreateTrampolines() {
  const uint8_t InitSonicR_B_bytes[4] = { 0x5f, 0x5e, 0x5b, 0xc3 }; 

  // Set in_game flag after loading the track array.
  WriteCall((void *)0x4203e9, (void *)&set_in_game);
  WriteData((uint8_t *)0x4203ee, (uint8_t)0x90);

  // Set in_game flag before returning to mode select.
  WriteCall((void *)0x43ac41, (void *)&set_not_in_game);
  WriteData<3>((uint8_t *)0x43ac46, (uint8_t)0x90);

  WriteCall((void *)0x43a914, (void *)&InitObjectPointers);
  WriteData((void *)0x43a919, InitSonicR_B_bytes, 4);

  WriteCall((void *)0x444596, (void *)&goal);

  // Don't set Chaos Emerald visibility based on file status. We will set this based on location sent status.
  WriteJump((void *)0x4279fe, (void *)0x427aa3);

  // Hook for rendering text before D3D_ScreenSwap
  WriteCall((void *)D3D_ScreenSwap, (void *)&handle_messages);
  //WriteCall((void *)D3D_ScreenSwap, (void *)&temp);
}

extern "C" {
__declspec(dllexport) void Init() {
  bool should_init = 1;

  struct config::Config config;
  config::read_config(&config);

  if (config.host.empty()) {
    PrintDebug("Sonic Rchipelago ERROR: host not defined.\n");
    should_init = 0;
  }
  if (config.slot.empty()) {
    PrintDebug("Sonic Rchipelago ERROR: slot not defined.\n");
    should_init = 0;
  }
  if (!should_init) {
    PrintDebug("Sonic Rchipelago will not load. Please correct the above errors.\n");
    return;
  }
  PrintDebug("Sonic Rchipelago INFO: Connecting to %s as %s.\n", config.host.c_str(), config.slot.c_str());
  ap::init(config.host.c_str(), config.slot.c_str(), config.password.c_str());
  CreateTrampolines();
}

__declspec(dllexport) void OnFrame() {
  /* Check if we've won a race. If so, send. Otherwise, keep them in sync. */
  int *file_grand_prix_win_array = &CurrentFileData.ResortIslandWon;
  bool unlock_radiant_emerald = true;
  for (int i = 0; i < 5; ++i) {
    if (ap::sent_grand_prix_win(static_cast<Courses>(i + 1))) {
      file_grand_prix_win_array[i] = 2;
    } else if (file_grand_prix_win_array[i] == 2) {
      ap::send_item_grand_prix_win(static_cast<Courses>(i + 1));
    } else if (i != 4) {
      unlock_radiant_emerald = false;
    }
  }
  if (!ap::sent_grand_prix_win(static_cast<Courses>(Courses_RadiantEmerald)) && unlock_radiant_emerald) {
    file_grand_prix_win_array[4] = 1;
  }

  // Syncing state for what we've received
  int *file_chaos_emerald_array = &CurrentFileData.BlueEmeraldCollected;
  for (int i = 0; i < 7; ++i) {
    file_chaos_emerald_array[i] = ap::received_chaos_emerald_to_file(i);
    ChaosEmeraldsCurrentlyCollected[i] = file_chaos_emerald_array[i];
  }
  CheckSuperSonicUnlockCondition = 1; /* This check only happens at the end of a race. TODO: Find/make a better way to enable Super Sonic. */

  /* If we're in a demo, we aren't in game, so don't collect items. */
  if (InDemo == 1) {
    in_game = 0;
  }
  if (!(in_game &&
        CurrentCourse >= Courses_ResortIsland &&
        CurrentCourse <= Courses_RegalRuin)) {
    return;
  }

  switch (GameMode) {
  case GameMode_GrandPrix: /* SonicTokens and ChaosEmeralds */
    CurrentSonicTokenOrTagCount = ap::received_sonic_tokens(static_cast<Courses>(CurrentCourse));

    /* Loop over objects in the current course. If we've sent the item, make the
       object invisible. If we haven't sent the item and the object is invisible,
       assume we just collected it and send the item. */
    for (int i = 0; i < 5; ++i) {
      TrackArrayEntry *token = g_SonicRAPData.SonicTokenObjects[CurrentCourse - 1][i];
      bool token_sent = ap::sent_sonic_token(static_cast<Courses>(CurrentCourse), i);

      if (token) {
        if (token_sent) {
          token->Visible = -1;
        } else if (token->Visible == -1) {
          ap::send_item_sonic_token(static_cast<Courses>(CurrentCourse), i);
        }
      }
    }
    for (int i = 0; i < 2; ++i) {
      TrackArrayEntry *emerald = g_SonicRAPData.ChaosEmeraldObjects[CurrentCourse - 1][i];
      bool emerald_sent = ap::sent_chaos_emerald(static_cast<Courses>(CurrentCourse), i);
      if (emerald) {
        if (emerald_sent) {
          emerald->Visible = -1;
        } else if (emerald->Visible == -1) {
          ap::send_item_chaos_emerald(static_cast<Courses>(CurrentCourse), i);
        }
      }
    }
    break;
  case GameMode_TimeAttack: /* Lots of other objects */
  case GameMode_RaceNoResultsScreen: /* Challenge Races? */
  default:
    break;
  }
}

__declspec(dllexport) ModInfo SonicRModInfo = { ModLoaderVer };
}
