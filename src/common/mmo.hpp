/// Global structures and defines
#ifndef MMO_HPP
#define MMO_HPP

# include "sanity.hpp"
# include "timer.t.hpp"
# include "utils.hpp"

constexpr int FIFOSIZE_SERVERLINK = 256 * 1024;

constexpr int MAX_MAP_PER_SERVER = 512;
constexpr int MAX_INVENTORY = 100;
constexpr int MAX_AMOUNT = 30000;
constexpr int MAX_ZENY = 1000000000;     // 1G zeny
constexpr int MAX_CART = 100;

enum class SkillID : uint16_t;
constexpr SkillID MAX_SKILL = SkillID(474); // not 450
constexpr SkillID get_enum_min_value(SkillID) { return SkillID(); }
constexpr SkillID get_enum_max_value(SkillID) { return MAX_SKILL; }

constexpr int GLOBAL_REG_NUM = 96;
constexpr int ACCOUNT_REG_NUM = 16;
constexpr int ACCOUNT_REG2_NUM = 16;
constexpr interval_t DEFAULT_WALK_SPEED = std::chrono::milliseconds(150);
constexpr interval_t MIN_WALK_SPEED = interval_t::zero();
constexpr interval_t MAX_WALK_SPEED = std::chrono::seconds(1);
constexpr int MAX_STORAGE = 300;
constexpr int MAX_PARTY = 12;

# define MIN_HAIR_STYLE battle_config.min_hair_style
# define MAX_HAIR_STYLE battle_config.max_hair_style
# define MIN_HAIR_COLOR battle_config.min_hair_color
# define MAX_HAIR_COLOR battle_config.max_hair_color
# define MIN_CLOTH_COLOR battle_config.min_cloth_color
# define MAX_CLOTH_COLOR battle_config.max_cloth_color

# define CHAR_CONF_NAME  "conf/char_athena.conf"

namespace e
{
enum class EPOS : uint16_t
{
    ZERO    = 0x0000,

    LEGS    = 0x0001,
    WEAPON  = 0x0002,
    GLOVES  = 0x0004,
    CAPE    = 0x0008,
    MISC1   = 0x0010,
    SHIELD  = 0x0020,
    SHOES   = 0x0040,
    MISC2   = 0x0080,
    HAT     = 0x0100,
    TORSO   = 0x0200,

    ARROW   = 0x8000,
};
ENUM_BITWISE_OPERATORS(EPOS)

constexpr EPOS get_enum_min_value(EPOS) { return EPOS(0x0000); }
constexpr EPOS get_enum_max_value(EPOS) { return EPOS(0xffff); }
}
using e::EPOS;

struct item
{
    int id;
    short nameid;
    short amount;
    EPOS equip;
    uint8_t identify;
    uint8_t refine;
    uint8_t attribute;
    short card[4];
    short broken;
};

struct point
{
    char map[24];
    short x, y;
};

namespace e
{
enum class SkillFlags : uint16_t;
}
using e::SkillFlags;

struct skill_value
{
    unsigned short lv;
    SkillFlags flags;
};

struct global_reg
{
    char str[32];
    int value;
};

// Option and Opt1..3 in map.hpp
namespace e
{
enum class Option : uint16_t;
constexpr Option get_enum_min_value(Option) { return Option(0x0000); }
constexpr Option get_enum_max_value(Option) { return Option(0xffff); }
}
using e::Option;

enum class ATTR
{
    STR = 0,
    AGI = 1,
    VIT = 2,
    INT = 3,
    DEX = 4,
    LUK = 5,

    COUNT = 6,
};

constexpr ATTR ATTRs[6] =
{
    ATTR::STR,
    ATTR::AGI,
    ATTR::VIT,
    ATTR::INT,
    ATTR::DEX,
    ATTR::LUK,
};

enum class ItemLook : uint16_t
{
    NONE = 0,
    BLADE = 1, // or some other common weapons
    _2,
    SETZER_AND_SCYTHE = 3,
    _6,
    STAFF = 10,
    BOW = 11,
    _13 = 13,
    _14 = 14,
    _16 = 16,
    SINGLE_HANDED_COUNT = 17,

    DUAL_BLADE = 0x11,
    DUAL_2 = 0x12,
    DUAL_6 = 0x13,
    DUAL_12 = 0x14,
    DUAL_16 = 0x15,
    DUAL_26 = 0x16,
};

struct mmo_charstatus
{
    int char_id;
    int account_id;
    int partner_id;

    int base_exp, job_exp, zeny;

    short species;
    short status_point, skill_point;
    int hp, max_hp, sp, max_sp;
    Option option;
    short karma, manner;
    short hair, hair_color, clothes_color;
    int party_id;

    ItemLook weapon;
    short shield;
    short head_top, head_mid, head_bottom;

    char name[24];
    unsigned char base_level, job_level;
    earray<short, ATTR, ATTR::COUNT> attrs;
    unsigned char char_num, sex;

    unsigned long mapip;
    unsigned int mapport;

    struct point last_point, save_point, memo_point[10];
    struct item inventory[MAX_INVENTORY], cart[MAX_CART];
    earray<skill_value, SkillID, MAX_SKILL> skill;
    int global_reg_num;
    struct global_reg global_reg[GLOBAL_REG_NUM];
    int account_reg_num;
    struct global_reg account_reg[ACCOUNT_REG_NUM];
    int account_reg2_num;
    struct global_reg account_reg2[ACCOUNT_REG2_NUM];
};

struct storage
{
    int dirty;
    int account_id;
    short storage_status;
    short storage_amount;
    struct item storage_[MAX_STORAGE];
};

struct map_session_data;

struct GM_Account
{
    int account_id;
    uint8_t level;
};

struct party_member
{
    int account_id;
    char name[24], map[24];
    int leader, online, lv;
    struct map_session_data *sd;
};

struct party
{
    int party_id;
    char name[24];
    int exp;
    int item;
    struct party_member member[MAX_PARTY];
};

struct square
{
    int val1[5];
    int val2[5];
};

#endif // MMO_HPP
