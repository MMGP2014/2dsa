//define     
/********************************************/
/*　     stage > floor > block > pixel      */
/* Dxlibの座標表記に合わせてblock,floorも   */
/* 左上が(0,0)or(1,1)で行こうと思います。   */
/********************************************/
#define SCREEN_WIDTH 640
#define SCREEN_HIGHT 480
#define BLOCK_SIZE 32 //なんとかSIZEの単位はpixelだよ
#define BLOCK_NUM_W ( SCREEN_WIDTH / BLOCK_SIZE ) 
#define BLOCK_NUM_H ( SCREEN_HIGHT / BLOCK_SIZE ) 
#define MAIN_PIC "tarou2.png"
#define OB_PIC_SIZE 100
#define FLOOR_NUM 20
#define LR_SPEED 4
#define EXTRATE ((double)BLOCK_SIZE / (double)OB_PIC_SIZE)
#define PI 3.1415926

  //BULLET 情報
#define BULLET_NUM 2

#define BULLET0_SPEED_X 5
#define BULLET0_SPEED_Y 0
#define BULLET0_ACCEL_X 0
#define BULLET0_ACCEL_Y 0
#define BULLET0_ACCEL_FREQUENCY 1
#define BULLET0_DAMAGE 6
#define BULLET0_SIZE 10
#define BULLET1_SPEED_X 7
#define BULLET1_SPEED_Y -10
#define BULLET1_ACCEL_X 0
#define BULLET1_ACCEL_Y 1
#define BULLET1_ACCEL_FREQUENCY 2
#define BULLET1_DAMAGE 10
#define BULLET1_SIZE 15

 //JUMP
#define JUMP_NUM 1
#define JUMP_G 8
#define JUMP1HIGH -50
#define JUMP2HIGH -50

  //enemy
#define ENEMY_MAX 10
#define ENEMY_TYPE_NUM 1
#define ENE0_MOVE_RANGE 70
#define ENE0_ROT_SPEED 1.5
#define ENE1_FALL_SPEED 13
//struct
typedef struct tble1{
	int x;
	int y;
}COORD2;

typedef struct tble2{
	int x;
	int y;
}SPEED;

typedef struct tble3{
	int type;
	int handle;
	int turnflag;
	COORD2 crd;
	COORD2 crd_s;
	SPEED speed;
	int cnt;
	int HP;
	COORD2 size;
}ENEMY;

typedef struct tble4{
	int handle;
	int toge;
	int block[ BLOCK_NUM_W ][ BLOCK_NUM_H ];
	int enemy_num;
	ENEMY enemy[ENEMY_MAX];
}FLOOR;

typedef struct tble5{
	int type;
	int handle;
	int turnflag;
	int damage;
	int size;
	COORD2 crd;
	SPEED speed;
	SPEED accel;
	int freq;
	int freq_cnt;
	struct tble5 *next;
	struct tble5 *pre;
}BULLET;


//prot
//first_stg.cpp

void input_floor_csv(FLOOR *,char *);

COORD2 check_contact(COORD2 *,SPEED *,FLOOR *,COORD2 *);
int get_key_action(SPEED *,int *,FLOOR,COORD2,BULLET *,int *,int *,int *,int &,COORD2 *);
int key2int();
int first_stg(void);
int jump_before(COORD2,FLOOR, COORD2 *);

//fuction.cpp
void print_char(char *);
void print_int(int );
void print_double(double );
//list.cpp
void add_bullet(BULLET *);
void delete_bullet(BULLET *);
void action_bullet(BULLET *,FLOOR *);
//enemy.cpp
void input_floor_enemy(FLOOR *,char *,ENEMY *);
void file_in(ENEMY *,char *);
void behaive_enemy(FLOOR *,ENEMY *);
