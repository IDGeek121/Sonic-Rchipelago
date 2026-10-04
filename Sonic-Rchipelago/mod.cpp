#include <IniFile.hpp>

#include <d3d9.h>

#include "apworld.h"
#include "mod.h"
#include "config.h"

extern "C" bool internal_hud_draw_sonic_tokens_by_challenge_race_win(Courses course) {
  return ap::sent_challenge_race_win(course);
}

void __declspec(naked) hud_draw_sonic_tokens_by_challenge_race_win() {
  __asm(
      "push %eax\n\t"
      "call _internal_hud_draw_sonic_tokens_by_challenge_race_win\n\t"
      "add $0x4, %esp\n\t"
      "cmpl $0x1, %eax\n\t"
      "push $0x43e77f\n\t"
      "ret"
  );
}

extern "C" bool internal_css_block_locked_character(int player) {
  const int* unlocked_characters = &CurrentFileData.SonicUnlocked;

  if (unlocked_characters[Players[player].Character] != 2) {
    return false;
  }

  return true;
}

void __declspec(naked) css_block_locked_character() {
  __asm (
    "push %ecx\n\t"

    "push %ebp\n\t"
    "call _internal_css_block_locked_character\n\t"
    "add $0x4, %esp\n\t"

    "pop %ecx\n\t"
    "test %eax, %eax\n\t"
    "jnz .+0x8\n\t"
    // If locked, skip
    "push $0x430082\n\t"
    "ret\n\t"
    // If unlocked, business as usual
    "movl 0x10(%esp), %edx\n\t"
    "movw (%edx), %ax\n\t"
    "push $0x42ffe2\n\t"
    "ret\n\t"
  );
}

extern "C" void internal_css_init_character_selection(int player) {
  const int* unlocked_characters = &CurrentFileData.SonicUnlocked;
  for (int i = 0; i <= Characters_EggRobo; ++i) {
    const Characters character_to_select = static_cast<Characters>(i);

    if (unlocked_characters[character_to_select] == 2) {
      CharacterSelectScreen_PreviousCharacterSelection[player] = character_to_select;
      PreviousCharacterSelection[player] = character_to_select;
      return;
    }
  }

  CharacterSelectScreen_PreviousCharacterSelection[player] = Characters_Sonic;
  PreviousCharacterSelection[player] = Characters_Sonic;
}

void __declspec(naked) css_init_character_selection() {
  __asm (
    "push %eax\n\t"
    "push %ecx\n\t"
    "push %edx\n\t"

    "push %eax\n\t"
    "call _internal_css_init_character_selection\n\t"
    "add $0x4, %esp\n\t"

    "pop %edx\n\t"
    "pop %ecx\n\t"
    "pop %eax\n\t"
    "push $0x42fde0\n\t"
    "ret\n\t"
  );
}

void css_draw_sonic_portrait() {
  const int portrait_xpos = CharacterSelectScreen_CursorPositionTable[Characters_Sonic] * 2;
  const int portrait_ypos = 360;
  const int portrait_width = 56;
  const int portrait_height = 80;
  const int tex_page = WallpaperTPage + 1;
  const int portrait_tex_width = 28;
  const int portrait_tex_height = 40;
  const int tex_x_off = 172;
  const int tex_y_off = *(int *)0x752830;
  const int tint = 0xffe0e0e0;

  D3D_Render2DObject(
      portrait_xpos,
      portrait_ypos,
      200.f,
      portrait_width,
      portrait_height,
      tex_page,
      tex_x_off,
      tex_y_off,
      portrait_tex_width,
      portrait_tex_height,
      tint);
  if (CurrentFileData.SonicUnlocked != 2) {
    D3D_Render2DObject(
        portrait_xpos,
        portrait_ypos,
        190.f,
        portrait_width,
        portrait_height,
        tex_page,
        228,
        200,
        portrait_tex_width,
        portrait_tex_height,
        tint);
  }
}

void __declspec(naked) css_left_bound_fix_1() {
  __asm (
    "movl %eax, 0x752918\n\t"
    "dec %eax\n\t"
    "test %eax, %eax\n\t"
    "jl .+0x8\n\t"
    "push $0x430331\n\t"
    "ret\n\t"
    "push $0x43034a\n\t"
    "ret\n\t"
  );
}

void __declspec(naked) css_left_bound_fix_2() {
  __asm (
    "movl (0x752918), %ecx\n\t"
    "movl (%ebp), %edx\n\t"
    "cmp %ecx, %edx\n\t"
    "jnz .+0x8\n\t"
    "push $0x430395\n\t"
    "ret\n\t"
    "movw %ax, (%esi)\n\t"
    "cmpw $0x0, (%esi)\n\t"
    "push $0x430351\n\t"
    "ret\n\t"
  );
}

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

bool check_if_challenge_race_won(Courses course) {
  return (ChallengeRaceBitmask >> course) & 1;
}

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

  // Don't set Chaos Emerald or Sonic Token visibility based on file status. We will set this based on location sent status.
  WriteJump((void *)0x4279a1, (void *)0x427aa3);

  // Hook for rendering text before D3D_ScreenSwap
  WriteCall((void *)D3D_ScreenSwap, (void *)&handle_messages);
  //WriteCall((void *)D3D_ScreenSwap, (void *)&temp);

  // Hook for fixing left bounds on the Character Select Screen
  WriteJump((void *)0x43032c, (void *)&css_left_bound_fix_1);
  WriteJump((void *)0x43034a, (void *)&css_left_bound_fix_2);

  // Hook for rendering Sonic's Character Select Screen portrait
  WriteCall((void *)0x430699, (void *)&css_draw_sonic_portrait);

  // Hook for determining character selection if the previously selected
  // character is locked, i.e. if Sonic is locked at the start.
  WriteJump((void *)0x42fdd2, (void *)&css_init_character_selection);

  // Do not allow a character to be selected if they are locked.
  WriteJump((void *)0x42ffdb, (void *)&css_block_locked_character);

  // Display Sonic Token HUD based on challenge race wins, not character unlocks.
  WriteJump((void *)0x43e777, (void *)&hud_draw_sonic_tokens_by_challenge_race_win);
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
  // Syncing state for what we've received
  int* const file_grand_prix_win_array = &CurrentFileData.ResortIslandWon;
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

  int* const file_character_array = &CurrentFileData.SonicUnlocked;
  for (int i = 0; i <= Characters_EggRobo; ++i) {
    const Characters character = static_cast<Characters>(i);
    if (ap::received_character(character)) {
      file_character_array[i] = 2;
    } else {
      file_character_array[i] = 1;
    }
  }

  int* const file_chaos_emerald_array = &CurrentFileData.BlueEmeraldCollected;
  bool unlock_super_sonic = true;
  for (int i = 0; i < 7; ++i) {
    const int has_emerald = ap::received_chaos_emerald_to_file(i);
    file_chaos_emerald_array[i] = has_emerald;
    ChaosEmeraldsCurrentlyCollected[i] = has_emerald;
    if (has_emerald != 2) {
      unlock_super_sonic = false;
    }
  }

  if (unlock_super_sonic) {
    file_character_array[Characters_SuperSonic] = 2;
  } else {
    file_character_array[Characters_SuperSonic] = 1;
  }

  /* If we're in a demo, we aren't in game, so don't collect items. */
  if (InDemo == 1) {
    in_game = 0;
  }
  if (!in_game) {
    return;
  }

  switch (GameMode) {
  case GameMode_GrandPrix: /* SonicTokens and ChaosEmeralds */
    if (CurrentCourse == Courses_RadiantEmerald) {
      break;
    }
    if (ap::sent_challenge_race_win(static_cast<Courses>(CurrentCourse))) {
      CurrentSonicTokenOrTagCount = 0;
    } else {
      CurrentSonicTokenOrTagCount = ap::received_sonic_tokens(static_cast<Courses>(CurrentCourse));
    }

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
  case GameMode_ChallengeRace:
    if (!ap::sent_challenge_race_win(static_cast<Courses>(CurrentCourse)) && check_if_challenge_race_won(static_cast<Courses>(CurrentCourse))) {
      ap::send_item_challenge_race_win(static_cast<Courses>(CurrentCourse));
    };
  default:
    break;
  }
}

__declspec(dllexport) ModInfo SonicRModInfo = { ModLoaderVer };
}
