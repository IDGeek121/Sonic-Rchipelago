#ifndef MOD_H
#define MOD_H

#include <SonicRModLoader.h>
#include <d3d9.h>
#include <array>

enum SpecialItems {
  SpecialItem_ItemPanel=2,
  SpecialItem_SonicToken=5,
  SpecialItem_ChaosEmerald1=6,
  SpecialItem_Balloon=7,
  SpecialItem_ChaosEmerald2=8
};

struct SpecialItemTableEntry {
  int TrackArrayIndex;
  unsigned int BoundingBox;
  int IgnoreYPos;
  enum SpecialItems ItemType;
};

struct TrackArrayEntry {
  SpecialItems ItemType;
  int field1_0x4;
  int field2_0x8;
  int field3_0xc;
  int field4_0x10;
  int field5_0x14;
  int field6_0x18;
  int field7_0x1c;
  int XPosition;
  int YPosition;
  int ZPosition;
  short Visible;
  short field12_0x2e;
  int field13_0x30;
  int field14_0x34;
  int field15_0x38;
  int field16_0x3c;
  int field17_0x40;
};

struct RecordTable {
  int GrandPrixCourseRecord[5];
  int GrandPrixLapRecord[5];
  int TimeAttackNormalCourseRecord[5];
  int TimeAttackReverseCourseRecord[5];
  int TimeAttackNormalLapRecord[5];
  int TimeAttackReverseLapRecord[5];
  int TimeAttackBalloonCourseRecord[5];
  int TimeAttackTagCourseRecord[5];
};

struct CharacterRecordTable {
  struct RecordTable RecordTable;
  int NumMultiplayerWins;
};

struct FileData {
  int field0_0x0;
  int ResortIslandWon;
  int RadicalCityWon;
  int RegalRuinWon;
  int ReactiveFactoryWon;
  int RadiantEmeraldWon;
  int SonicUnlocked; /* crashes at css if 0 */
  int TailsUnlocked;
  int KnucklesUnlocked;
  int AmyUnlocked;
  int RobotnikUnlocked;
  int MetalSonicUnlocked;
  int TailsDollUnlocked;
  int MetalKnucklesUnlocked;
  int EggRoboUnlocked;
  int SuperSonicUnlocked;
  int BlueEmeraldCollected;
  int GreenEmeraldCollected;
  int PurpleEmeraldCollected;
  int YellowEmeraldCollected;
  int OrangeEmeraldCollected;
  int RedEmeraldCollected;
  int WhiteEmeraldCollected;
  struct RecordTable CourseRecords;
  unsigned char field24_0xfc;
  unsigned char field25_0xfd;
  unsigned char field26_0xfe;
  unsigned char field27_0xff;
  unsigned char field28_0x100;
  unsigned char field29_0x101;
  unsigned char field30_0x102;
  unsigned char field31_0x103;
  unsigned char field32_0x104;
  unsigned char field33_0x105;
  unsigned char field34_0x106;
  unsigned char field35_0x107;
  unsigned char field36_0x108;
  unsigned char field37_0x109;
  unsigned char field38_0x10a;
  unsigned char field39_0x10b;
  unsigned char field40_0x10c;
  unsigned char field41_0x10d;
  unsigned char field42_0x10e;
  unsigned char field43_0x10f;
  unsigned char field44_0x110;
  unsigned char field45_0x111;
  unsigned char field46_0x112;
  unsigned char field47_0x113;
  unsigned char field48_0x114;
  unsigned char field49_0x115;
  unsigned char field50_0x116;
  unsigned char field51_0x117;
  unsigned char field52_0x118;
  unsigned char field53_0x119;
  unsigned char field54_0x11a;
  unsigned char field55_0x11b;
  unsigned char field56_0x11c;
  unsigned char field57_0x11d;
  unsigned char field58_0x11e;
  unsigned char field59_0x11f;
  unsigned char field60_0x120;
  unsigned char field61_0x121;
  unsigned char field62_0x122;
  unsigned char field63_0x123;
  unsigned char field64_0x124;
  unsigned char field65_0x125;
  unsigned char field66_0x126;
  unsigned char field67_0x127;
  unsigned char field68_0x128;
  unsigned char field69_0x129;
  unsigned char field70_0x12a;
  unsigned char field71_0x12b;
  unsigned char field72_0x12c;
  unsigned char field73_0x12d;
  unsigned char field74_0x12e;
  unsigned char field75_0x12f;
  unsigned char field76_0x130;
  unsigned char field77_0x131;
  unsigned char field78_0x132;
  unsigned char field79_0x133;
  unsigned char field80_0x134;
  unsigned char field81_0x135;
  unsigned char field82_0x136;
  unsigned char field83_0x137;
  unsigned char field84_0x138;
  unsigned char field85_0x139;
  unsigned char field86_0x13a;
  unsigned char field87_0x13b;
  int NumMultiplayerRacesPlayed[4]; /* Counts per player. Caps at 99 */
  int CoursesFirstWonByCharacters[10][5]; /* Tracks which character cleared a course first in Grand Prix */
  int NumberOfFirstCourseClearsByCharacter[10];
  struct CharacterRecordTable CourseRecordsByCharacter[10];
  int NumRaces;
};

DataPointer(struct FileData, CurrentFileData, 0x752BC8);
DataPointer(int, CurrentSonicTokenOrTagCount, 0x75356C);
DataArray(int, ChaosEmeraldsCurrentlyCollected, 0x5018C4, 7); /* Used for determining if Super Sonic is unlocked. */
DataPointer(int, CheckSuperSonicUnlockCondition, 0x50215C);

const SpecialItemTableEntry* const CourseSpecialItemTable[6] = {
  (SpecialItemTableEntry*)nullptr,
  (SpecialItemTableEntry*)0x45D1C0,
  (SpecialItemTableEntry*)0x45CD1C,
  (SpecialItemTableEntry*)0x45CB20,
  (SpecialItemTableEntry*)0x45C9A0,
  (SpecialItemTableEntry*)0x45C8D8,
};

enum GameMode {
  GameMode_GrandPrix,
  GameMode_MultiPlayer,
  GameMode_TimeAttack,
  GameMode_ChallengeRaceIntro,
  GameMode_ChallengeRace,
};

enum GameModeSubmode {
  GameModeSubmode_RaceNormal,
  GameModeSubmode_RaceReverse,
  GameModeSubmode_Tag,
  GameModeSubmode_Balloon,
};

const unsigned int TrackArrayLength = 1024;
DataPointer(TrackArrayEntry*, TrackArray, 0x5F3870);
DataPointer(int, InDemo, 0x73604C);
DataArray(int, CharacterSelectScreen_CursorPositionTable, 0x45F098, 8);
DataPointer(enum GameMode, GameMode, 0x769F24);
DataPointer(enum GameModeSubmode, GameModeSubmode, 0x7BCB80);
DataPointer(int, SceneFrameCount, 0x7AF154);
DataPointer(int, TPageBufferIndex_TextAtlas, 0x754650);
FunctionPointer(void, D3D_SetSamplerState, (unsigned int val), 0x441D00);
FunctionPointer(void, D3D_SetBlendMode, (int val), 0x441D60);
FunctionPointer(void, D3D_SetDepthBuffering, (int val), 0x441DE0);
FunctionPointer(void, D3D_ScreenSwap, (), 0x441EF0);
FunctionPointer(void, D3D_BeginScene, (), 0x4424D0);
FunctionPointer(void, D3D_EndScene, (), 0x4425F0);
FunctionPointer(void, D3D_ClearViewport, (int color), 0x442650);
FunctionPointer(void, D3D_Flush, (int val), 0x442680);
DataPointer(IDirect3DDevice9*, D3DDevice, 0x5EDD14);
DataPointer(uint8_t, ChallengeRaceBitmask, 0x7AF0C9);

FunctionPointer(void, DrawHUD, (int Player), 0x43DE30);
FunctionPointer(void, FUN_00412e30, (int player), 0x412e30);

struct text_char {
  uint16_t x;
  uint16_t y;
  uint16_t w;
  uint16_t h;
};

constexpr unsigned int TEXT_NUMS_Y = 167;
constexpr unsigned int TEXT_NUMS_H = 10;
constexpr unsigned int TEXT_CAPS_Y = 178;
constexpr unsigned int TEXT_CAPS_H = 10;

//#define SCALE 3
#ifdef SCALE
#define TEXT_OFFSET 1
#else
#define TEXT_OFFSET 0
#endif

const std::array<struct text_char, 36> text_atlas = {{
  { 64, TEXT_NUMS_Y, TEXT_OFFSET, TEXT_NUMS_H }, // 0
  { 70, TEXT_NUMS_Y, 5 - TEXT_OFFSET, TEXT_NUMS_H }, // 1
  { 75, TEXT_NUMS_Y, 6 - TEXT_OFFSET, TEXT_NUMS_H }, // 2
  { 81, TEXT_NUMS_Y, 6 - TEXT_OFFSET, TEXT_NUMS_H }, // 3
  { 87, TEXT_NUMS_Y, 6 - TEXT_OFFSET, TEXT_NUMS_H }, // 4
  { 93, TEXT_NUMS_Y, 6 - TEXT_OFFSET, TEXT_NUMS_H }, // 5
  { 99, TEXT_NUMS_Y, 6 - TEXT_OFFSET, TEXT_NUMS_H }, // 6
  { 105, TEXT_NUMS_Y, 6 - TEXT_OFFSET, TEXT_NUMS_H }, // 7
  { 111, TEXT_NUMS_Y, 6 - TEXT_OFFSET, TEXT_NUMS_H }, // 8
  { 117, TEXT_NUMS_Y, 6 - TEXT_OFFSET, TEXT_NUMS_H }, // 9
  { 64, TEXT_CAPS_Y, 6 - TEXT_OFFSET, TEXT_CAPS_H }, // A
  { 70, TEXT_CAPS_Y, 6 - TEXT_OFFSET, TEXT_CAPS_H }, // B
  { 76, TEXT_CAPS_Y, 5 - TEXT_OFFSET, TEXT_CAPS_H }, // C
  { 81, TEXT_CAPS_Y, 6 - TEXT_OFFSET, TEXT_CAPS_H }, // D
  { 87, TEXT_CAPS_Y, 6 - TEXT_OFFSET, TEXT_CAPS_H }, // E
  { 93, TEXT_CAPS_Y, 6 - TEXT_OFFSET, TEXT_CAPS_H }, // F
  { 99, TEXT_CAPS_Y, 6 - TEXT_OFFSET, TEXT_CAPS_H }, // G
  { 105, TEXT_CAPS_Y, 6 - TEXT_OFFSET, TEXT_CAPS_H }, // H
  { 111, TEXT_CAPS_Y, 5 - TEXT_OFFSET, TEXT_CAPS_H }, // I
  { 116, TEXT_CAPS_Y, 5 - TEXT_OFFSET, TEXT_CAPS_H }, // J
  { 121, TEXT_CAPS_Y, 6 - TEXT_OFFSET, TEXT_CAPS_H }, // K
  { 127, TEXT_CAPS_Y, 5 - TEXT_OFFSET, TEXT_CAPS_H }, // L
  { 132, TEXT_CAPS_Y, 9 - TEXT_OFFSET, TEXT_CAPS_H }, // M
  { 141, TEXT_CAPS_Y, 7 - TEXT_OFFSET, TEXT_CAPS_H }, // N
  { 148, TEXT_CAPS_Y, 6 - TEXT_OFFSET, TEXT_CAPS_H }, // O
  { 154, TEXT_CAPS_Y, 6 - TEXT_OFFSET, TEXT_CAPS_H }, // P
  { 160, TEXT_CAPS_Y, 6 - TEXT_OFFSET, TEXT_CAPS_H }, // Q
  { 166, TEXT_CAPS_Y, 6 - TEXT_OFFSET, TEXT_CAPS_H }, // R
  { 172, TEXT_CAPS_Y, 6 - TEXT_OFFSET, TEXT_CAPS_H }, // S
  { 178, TEXT_CAPS_Y, 7 - TEXT_OFFSET, TEXT_CAPS_H }, // T
  { 185, TEXT_CAPS_Y, 6 - TEXT_OFFSET, TEXT_CAPS_H }, // U
  { 191, TEXT_CAPS_Y, 6 - TEXT_OFFSET, TEXT_CAPS_H }, // V
  { 197, TEXT_CAPS_Y, 9 - TEXT_OFFSET, TEXT_CAPS_H }, // W
  { 206, TEXT_CAPS_Y, 6 - TEXT_OFFSET, TEXT_CAPS_H }, // X
  { 212, TEXT_CAPS_Y, 6 - TEXT_OFFSET, TEXT_CAPS_H }, // Y
  { 218, TEXT_CAPS_Y, 6 - TEXT_OFFSET, TEXT_CAPS_H }, // Z
}};

#endif
