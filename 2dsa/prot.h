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

  //BULLET 情報
#define BULLET_NUM 2

#define BULLET0_SPEED_X 5
#define BULLET0_SPEED_Y 0
#define BULLET0_ACCEL_X 0
#define BULLET0_ACCEL_Y 0
#define BULLET0_ACCEL_FREQUENCY 1
#define BULLET1_SPEED_X 7
#define BULLET1_SPEED_Y -10
#define BULLET1_ACCEL_X 0
#define BULLET1_ACCEL_Y 1
#define BULLET1_ACCEL_FREQUENCY 2

  //enemy
#define ENEMY_MAX 10
#define ENEMY_TYPE_NUM 1
//struct
typedef struct tble1{
	int x;
	int y;
}COORD2;

typedef struct tble5{
	int type;
	int handle;
	int turnflag;
	COORD2 crd;
	int freq;
	int HP;
	int exist;
	COORD2 size;
}ENEMY;

typedef struct tble2{
	int handle;
	int block[ BLOCK_NUM_W ][ BLOCK_NUM_H ];
	int enemy_num;
	ENEMY enemy[ENEMY_MAX];
}FLOOR;

typedef struct tble3{
	int x;
	int y;
}SPEED;

typedef struct tble4{
	int type;
	int handle;
	int turnflag;
	COORD2 crd;
	COORD2 size;
	SPEED speed;
	SPEED accel;
	int freq;
	int freq_cnt;
	struct tble4 *next;
	struct tble4 *pre;
}BULLET;


//prot
//first_stg.cpp

void move_obj(int ,COORD2 *,SPEED *,int );
void input_floor_csv(FLOOR *,char *);

void check_contact(COORD2 *,SPEED *,FLOOR *);
int get_key_action(SPEED *,int *,FLOOR,COORD2,BULLET *,int *,int *);
int key2int();
int first_stg(void);
int jump_before(COORD2,FLOOR);

//fuction.cpp
void print_char(char *);
void print_int(int );
void print_double(double );
//list.cpp
void add_bullet(BULLET *);
void delete_bullet(BULLET *);
void action_bullet(BULLET *);

//enemy.cpp
void file_in(ENEMY *,char *);