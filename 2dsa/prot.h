//define     
/********************************************/
/*　         stage > floor > block          */
/* Dxlibの座標表記に合わせてblock,floorも   */
/* 左上が(0,0)で行こうと思います。          */
/********************************************/
#define SCREEN_WIDTH 640
#define SCREEN_HIGHT 480
#define BLOCK_SIZE 32 //なんとかSIZEの単位はpixelだよ
#define BLOCK_NUM_W ( SCREEN_WIDTH / BLOCK_SIZE ) 
#define BLOCK_NUM_H ( SCREEN_HIGHT / BLOCK_SIZE ) 
#define OB_PIC_SIZE 32
#define FLOOR_NUM 20
#define LR_SPEED 4
#define EXTRATE ((double)BLOCK_SIZE / (double)OB_PIC_SIZE)

//struct
typedef struct tble1{
	int x;
	int y;
}COORD2;

typedef struct tble2{
	int handle;
	int block[ BLOCK_NUM_W ][ BLOCK_NUM_H ];
}FLOOR;

typedef struct tble3{
	int x;
	int y;
}SPEED;


//prot
//first_stg.cpp
void move_obj(int ,COORD2 *,SPEED *,int ,FLOOR *);
void input_csv(FLOOR *,char *);
void check_contact(COORD2 *,SPEED *,FLOOR *);
int get_key_action(SPEED *,int *,FLOOR,COORD2);
int key2int();
int first_stg(void);
int jump_before(COORD2,FLOOR);
//fuction.cpp
void print_char(char *);
void print_int(int );
void print_double(double );
