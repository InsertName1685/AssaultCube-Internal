#pragma once

#include<cstdint>
#include<vector>





namespace position
{
	// Assault cubes position order goes x,z,y
	struct vec3 { float x, z, y; };
	inline vec3 shuffle_vec(vec3 vec) {
		float buffer;
		buffer = vec.z;
		vec.z = vec.y;
		vec.y = buffer;
		return vec;
	}
	// Rotation order goes x,y,z
	struct rot3 { float x, y, z; };

	struct vec2 
	{ float x, y; 
		vec2(float x, float y) 
		{ 
			this->x = x; this->y = y; 
		}
	};

	struct vec4 { float x, y, z, w; };

	struct viewMatrix { float matrix[16]; };

	

}

using namespace position;

struct Entity
{
	uintptr_t vTable;
	vec3 head_position;
	vec3 velocity;
	vec3 __speed_difference;
	vec3 feet_position;
	rot3 camera_rotation;
	float recoil_velocity;
	float __max_speed; // (literally useless cuz if you go over 16 it crashes your game)
	float __time_in_air; // (in milliseconds)
	float hitbox_radius, __camera_height_from_feet, __max_camera_height_from_feet, __hitbox_height_from_camera;  // bounding box size
	bool __inwater;
	bool onfloor, __onladder, jump_next; // jump next means if i hold jump while in the air and i land again, i will jump immediately (basically jump queue)
	bool __jumpd;
	bool crouching, crouchedinair;
	bool __trycrouch; // literally the same as crouching
	bool cancollide;// NOCLIP
	bool not_moving;
	bool scoping_in;

	char pad_0067[1]; //0x0067
	int32_t __last_jump; //0x0068 time since last jump
	float __last_jump_height; //0x006C
	int32_t __last_in_water; //0x0070 time since last in teh water
	int8_t __moving_forward_backward; //0x0074 These are character data types in assault cube
	int8_t __strafing; //0x0075 this is also technically movement speed as it can be adjusted to chagne speed
	char pad_0076[10]; //0x0076
	bool input_left; //0x0080 dynent : physent
	bool input_right; //0x0081
	bool input_forward; //0x0082
	bool input_backward; //0x0083
	char pad_0084[80]; //0x0084
	int32_t __time_since_last_anim; //0x00D4
	char pad_00D8[4]; //0x00D8
	void* __player_model; //0x00DC
	void* gun_model; //0x00E0
	char pad_00E4[8]; //0x00E4
	int32_t health; //0x00EC Player state
	int32_t armor; //0x00F0
	int32_t primary_weapon_id; //0x00F4
	int32_t __next_primary_weapon_id; //0x00F8 when a weapon is chosen it will be given to the player after they die, this will be the next weapon the recieve
	int32_t __respawn_weapon; //0x00FC I think this is the weapon that will be what u equip when u respawn
	bool akimbo_pistol; //0x0100
	char pad_0101[3]; //0x0101
	int32_t gun_mag_ammo[9];
	int32_t gun_ammo[9];
	int32_t gun_delay[9];
	int32_t gun_shots_fired[9];
	char pad_0194[68]; //0x0194
	uint32_t deaths; //0x01D8
	uint32_t kills; //0x01DC
	char pad_01E0[36]; //0x01E0
	bool is_attacking; //0x0204
	char name[260]; //0x0205
	char pad_0309[3]; //0x0309
	int32_t team; //0x030C
	char pad_0310[44]; //0x0310
	uintptr_t weapon_list[9]; //0x033C
	void* __previous_weapon_selected; //0x0360
	void* weapon_selected; //0x0364
	void* __next_weapon_selected; //0x0368
	void* primary_weapon; //0x036C
	void* __next_primary_weapon; //0x0370
	void* __last_weapon_shot; //0x0374
	char pad_0378[608]; //0x0378

};



enum GUN_ID
{
	KNIFE,
	PISTOL,
	CARBINE,
	SHOTGUN,
	SUBMACHINE_GUN,
	SNIPER,
	ASSAULT_RIFLE,
	GRENADE,
	AKIMBO_PISTOL
};



namespace __temporary
{
	class entlist
	{
	private:
		int32_t __padding;
	public:
		
		Entity* ent[32];
	};
}