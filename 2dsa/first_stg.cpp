#include "DxLib.h"
#include "prot.h"
#include "mypath.h"
#include <stdio.h>
#include <string.h>



int first_stg(void){
	int i,j,a;
	int turnflag=0;
	int cr=GetColor(100,100,100);
	int col0=GetColor(255,0,0);
	int col1=GetColor(0,255,0);
	int jmp_times =0;
	FLOOR floor[ FLOOR_NUM ][ FLOOR_NUM ];
	FLOOR *flr;
	char flr_name[1000];
	char flr_enemy_name[1000];
	char tmp_char[1000];
	char stage[]="STAGE1";
	char chitoge[]="toge1.png";
	ENEMY ene[100];
	char enetype_file[]=DATA "ENEMY\\enemy_type.csv";
	char main_name[]=PIC MAIN_PIC;
	int main_handle = LoadGraph(main_name);
	char bullet_name[BULLET_NUM][1000];
	sprintf_s(bullet_name[0],"%s%s",PIC,"bullet01.png");
	sprintf_s(bullet_name[1],"%s%s",PIC,"bullet02.png");
	int bullet_handle[BULLET_NUM];
	bullet_handle[0] = LoadGraph(bullet_name[0]);
	bullet_handle[1] = LoadGraph(bullet_name[1]);
	BULLET bullet_first,bullet_last;
	bullet_first.next = &bullet_last;
	bullet_first.pre = NULL;
	bullet_last.next = NULL;
	bullet_last.pre = &bullet_first;
	int bullet_flag[BULLET_NUM];
	int jump_flag[JUMP_NUM];
	int death;
	char music_name[]=MUSIC "boss_music.mp3";
	PlaySoundFile(music_name,DX_PLAYTYPE_LOOP);
	for(i=0;i < BULLET_NUM; i++){
		bullet_flag[i] = 0;
	}
	SPEED speed={0,0};
	COORD2 size={BLOCK_SIZE,BLOCK_SIZE};
	COORD2 crd={100,100};
	COORD2 flr_crd_mv={10,10};
	COORD2 flr_crd={0,0};//初期フロア10,10
	for(a=0;a<JUMP_NUM;a++){
		jump_flag[a] = 0;
	}
	
	
	file_in(ene,enetype_file);
	/*ClearDrawScreen();
	print_char(enetype_file);
	ScreenFlip();*/
	
	
	
	
	for(i=0;i<FLOOR_NUM;i++){
		for(j=0;j<FLOOR_NUM;j++){
			if(((i == 10) && (j == 10)) ||((i == 11) && (j == 10))){
				sprintf_s(flr_name,"%s%s\\floor_%d_%d",DATA,stage,i,j);
				sprintf_s(flr_name,"%s%s\\floor_%d_%d",DATA,stage,i,j);
				sprintf_s(tmp_char,"%s.png",flr_name);
				floor[i][j].handle = LoadGraph(tmp_char);
				floor[i][j].toge = LoadGraph(PIC "chitoge");
				sprintf_s(tmp_char,"%s.csv",flr_name);
				input_floor_csv(&floor[i][j],tmp_char);
			}
		}
	}
	death=0;
	while( ProcessMessage() == 0){
		ScreenFlip();
		ClearDrawScreen();
		if(flr_crd_mv.x != 0 || flr_crd_mv.y != 0){
			flr_crd.x += flr_crd_mv.x;
			flr_crd.y += flr_crd_mv.y;
			if( flr_crd_mv.x < 0){
				crd.x = SCREEN_WIDTH - size.x/2-1;
				//-1は適当まじめにやらないと切り替え後
				//2マス目が壁のときバグる恐れ
			}else if(flr_crd_mv.x > 0){
				crd.x = size.x/2+1;
			}
			if( flr_crd_mv.y < 0){
				crd.y = SCREEN_HIGHT - size.y/2-1;
			}else if(flr_crd_mv.y > 0){
				crd.y = size.y/2+1;
			}

			//bulletのデリートが必要
			flr_crd_mv.x = 0;
			flr_crd_mv.y = 0;

			flr = &floor[flr_crd.x][flr_crd.y];
		DrawGraph(0,0,flr->handle,0);DrawGraph(0,0,flr->toge,0);
		DrawString(540,0,"END:[ENTER]",cr);
			sprintf_s(flr_enemy_name,"%s%s\\enemy_%d_%d.csv",DATA,stage,flr_crd.x,flr_crd.y);
			input_floor_enemy(flr,flr_enemy_name,ene);
		}
		DrawGraph(0,0,flr->handle,0);
		DrawString(540,0,"END:[ENTER]",cr);
		if(get_key_action(&speed,&turnflag,*flr,crd,&bullet_last,bullet_handle,bullet_flag,jump_flag,jmp_times,&size)==1) break; 
		flr_crd_mv=check_contact(&crd,&speed,flr,&size); //main - wall contact
		crd.y +=  speed.y;
		crd.x +=  speed.x;//main move
		for(i=0;i<flr->enemy_num;i++){ 
			if(flr->enemy[i].HP <= 0) continue;
			behaive_enemy(flr,&flr->enemy[i]); //ene move
		}
		action_bullet(&bullet_first,flr); //bullet move (ene - bullet contact)
		for(i=0;i<flr->enemy_num;i++){
			if(flr->enemy[i].HP <= 0) continue;
			DrawRotaGraph(flr->enemy[i].crd.x,flr->enemy[i].crd.y,1.0,0.0,flr->enemy[i].handle,0,0);	
			if((abs(flr->enemy[i].crd.x - crd.x) <= flr->enemy[i].size.x/2 + size.x/2) && (abs(flr->enemy[i].crd.y - crd.y) <= flr->enemy[i].size.y/2 + size.y/2 )){
				death=1;
			}

		}
		DrawRotaGraph(crd.x,crd.y,EXTRATE,0.0,main_handle,1,turnflag);
		if(death == 1){
			print_char("death");
			ScreenFlip();
			WaitKey();
		       	return 1;
		}

	}
	return 0;
}

int get_key_action(SPEED *speed,int *turnflag,FLOOR floor,COORD2 crd,BULLET *bullet_last,int bullet_handle[],int *bullet_flag,int *jump_flag,int &jmp_times,COORD2 *size){
	/************************************************* 
	/キー入力を読み取り、上下左右のスピードを計算する
	/また移動方向によりキャラの向きも算出する
	/終了のキーを受けたら1を返す
	 *************************************************/
	char key[256];	
	GetHitKeyStateAll( key ) ;



	//エンターのキー入力(exit)
        if(key[KEY_INPUT_RETURN] >= 1) return 1; 

	//左右のキー入力
	if(key[KEY_INPUT_LEFT] >= 1){
	       	speed->x = -1 * LR_SPEED;
	}else if(key[KEY_INPUT_RIGHT] >= 1){ 
		speed->x = LR_SPEED;
	}else{ 
		speed->x=0;
       	}

	//上下のキー入力
	if(speed->y < JUMP_G) speed->y+=JUMP_G;

	/*while(ProcessMessage() == 0&&jump_before(crd,floor,size)==0&&key[KEY_INPUT_UP] == 1 && jmp_times==1){
		print_int(jmp_times);
		speed ->y = -30;
	}*/	
	if(key[KEY_INPUT_DOWN] >= 1){
		speed->y += 1;
		
	}else if((key[KEY_INPUT_UP] >=1 || key[KEY_INPUT_SPACE] == 1)&& jump_before(crd,floor,size)==1){
		speed ->y=JUMP1HIGH;
		
	}		
	if(jump_before(crd,floor,size)==0&&(key[KEY_INPUT_UP]==1 || key[KEY_INPUT_SPACE] >= 1) && jmp_times<=0&&jump_flag[0]==0){
		speed->y = JUMP2HIGH;
		jmp_times++;
	}if((key[KEY_INPUT_UP]==1 || key[KEY_INPUT_SPACE] >= 1)){
		jump_flag[0]=1;
		}
	else{
		jump_flag[0] =0;
	}
		if(jump_before(crd,floor,size)==1){
		jmp_times = 0;
		
		}

	/*else if(key[KEY_INPUT_UP] >= 1 &&key[KEY_INPUT_SPACE]&& jump_before(crd,floor,size)==0){
		jmp_times++;
		while(jmp_times <= 1){
			speed ->y = -20;
		break;
		}
		return 0;
	}*/


	
	//キャラクターの向き
	if(speed->x < 0){
		*turnflag = 1;
	} else if(speed->x > 0){
      		*turnflag = 0;
	}

	//攻撃タイプ0
	if(key[KEY_INPUT_Z] >= 1){
		if(bullet_flag[0] == 0){

			add_bullet(bullet_last);
			bullet_last->pre->type = 0;
			bullet_last->pre->handle = bullet_handle[0];
			bullet_last->pre->turnflag = *turnflag ;
			bullet_last->pre->crd = crd;
			bullet_last->pre->crd.x += (1 + (1 + (-2) * *turnflag ) * (BLOCK_SIZE+1))/2;
			bullet_last->pre->speed.x = (1 + (-2) * *turnflag ) * BULLET0_SPEED_X;
			bullet_last->pre->speed.y = BULLET0_SPEED_Y;
			bullet_last->pre->accel.x = (1 + (-2) * *turnflag) * BULLET0_ACCEL_X;
			bullet_last->pre->accel.y = BULLET0_ACCEL_Y;
			bullet_last->pre->freq = BULLET0_ACCEL_FREQUENCY;
			bullet_last->pre->damage = BULLET0_DAMAGE;
			bullet_last->pre->size = BULLET0_SIZE;
			bullet_last->pre->freq_cnt = 0;
			bullet_flag[0]++;
		}
	}else bullet_flag[0]=0;
	
		
	if(key[KEY_INPUT_X] >= 1){
		if(bullet_flag[1] == 0){
			add_bullet(bullet_last);
			bullet_last->pre->type = 1;
			bullet_last->pre->handle = bullet_handle[1];
			bullet_last->pre->turnflag = *turnflag ;
			bullet_last->pre->crd = crd;
			bullet_last->pre->crd.x += (1 + (1 + (-2) * *turnflag ) * (BLOCK_SIZE+1))/2;
			bullet_last->pre->speed.x = (1 + (-2) * *turnflag ) * BULLET1_SPEED_X;
			bullet_last->pre->speed.y = BULLET1_SPEED_Y;
			bullet_last->pre->accel.x = (1 + (-2) * *turnflag) * BULLET1_ACCEL_X;
			bullet_last->pre->accel.y = BULLET1_ACCEL_Y;
			bullet_last->pre->freq = BULLET1_ACCEL_FREQUENCY;
			bullet_last->pre->damage = BULLET1_DAMAGE;
			bullet_last->pre->size = BULLET1_SIZE;
			bullet_last->pre->freq_cnt = 0;
			bullet_flag[1]++;
		}
	}else bullet_flag[1] = 0;
	return 0;
}

void input_floor_csv(FLOOR *floor,char *fname){
	int x,y;
	char buf[256];
	FILE *fp;
	if((fopen_s(&fp,fname,"r")) != 0) exit(EXIT_FAILURE);
	for(y=0; y < BLOCK_NUM_H ;y++){
		if( fgets(buf,256,fp) == NULL) exit(EXIT_FAILURE);
		for(x=0; x < BLOCK_NUM_W ;x++){
			floor->block[x][y] = atoi(&buf[2*x]);
		}
	}
	fclose(fp);
}

COORD2 check_contact(COORD2 *crd,SPEED *speed,FLOOR *floor,COORD2 *size){
	int block_pxl;
	int block_pxr;
	int block_pyu;
	int block_pyd;

	int i,flag;
	COORD2 flr_p={0,0};

	block_pyd = (crd->y + (size->y / 2)  - 1) / BLOCK_SIZE;
	block_pyu = (crd->y - (size->y / 2)) / BLOCK_SIZE;
	
	
	if(floor->block[block_pyd][block_pyu] == 2){
	  LoadGraphScreen( 0 , 0 , PIC "man.png" , TRUE ) ;
	}
	
	
	while(speed->x > 0){
		block_pxr = (crd->x + (size->x / 2) + speed->x - 1) / BLOCK_SIZE;
		if(block_pxr >= BLOCK_NUM_W){
			flr_p.x=1;
			flr_p.y=0;
			break;
		}
		flag=0;
		for(i = block_pyu; i <= block_pyd ;i++){
			if(floor->block[block_pxr][i] == 1) flag=1;
		}
		if(flag == 0) break;
		speed->x--;
	}
	while(speed->x < 0){
		block_pxl = (crd->x - (size->x / 2) + speed->x ) / BLOCK_SIZE;
		if(block_pxl < 0){
			flr_p.x=-1;
			flr_p.y=0;
			break;
		}
		flag=0;
		for(i = block_pyu; i <= block_pyd ;i++){
			if(floor->block[block_pxl][i] == 1) flag=1;
		}
		if(flag == 0) break;
		speed->x++;
	}

	block_pxr = (crd->x + (size->x / 2) + speed->x - 1) / BLOCK_SIZE;
	block_pxl = (crd->x - (size->x / 2) + speed->x ) / BLOCK_SIZE;
	while(speed->y > 0){
		block_pyd = (crd->y + (size->y / 2) + speed->y - 1 ) / BLOCK_SIZE;
		if(block_pyd >= BLOCK_NUM_H){
			flr_p.x=0;
			flr_p.y=1;
			break;
		}
		flag=0;
		for(i = block_pxl; i <= block_pxr ;i++){
			if(floor->block[i][block_pyd] == 1) flag=1;
		}
		if(flag == 0) break;
		speed->y--;
	}
	while(speed->y < 0){
		block_pyu = (crd->y - (size->y / 2) + speed->y ) / BLOCK_SIZE;
		if(block_pyu < 0){
			flr_p.x=0;
			flr_p.y=-1;
			break;
		}
		flag=0;
		for(i = block_pxl; i <= block_pxr ;i++){
			if(floor->block[i][block_pyu] == 1) flag=1;
		}
		if(flag == 0) break;
		speed->y++;
	}
	return flr_p;
}


int jump_before(COORD2 crd,FLOOR floor,COORD2 *size){


	int block_pyd;
	int block_pxr;
	int block_pxl;
	int i;

	block_pyd = (crd.y + (size->y / 2) ) / BLOCK_SIZE;
	block_pxr = (crd.x + (size->x / 2)  -1) / BLOCK_SIZE;
	block_pxl = (crd.x - (size->x / 2)  ) / BLOCK_SIZE;
 	
	for(i = block_pxl ; i <= block_pxr;i++){
		if(floor.block[i][block_pyd]==1) return 1;
	}
	return 0;
}

