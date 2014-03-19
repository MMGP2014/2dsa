#include "DxLib.h"
#include "prot.h"
#include "mypath.h"
#include <stdio.h>
#include <string.h>

void add_bullet(BULLET *last){
	BULLET *newb;
	newb = (BULLET *)malloc(sizeof(BULLET));
	last->pre->next = newb;
	newb->pre = last->pre;
	newb->next = last;
	last->pre = newb;
}

void delete_bullet(BULLET *corrent){
	corrent->pre->next=corrent->next;
	corrent->next->pre = corrent->pre;
	free(corrent);
}

void action_bullet(BULLET *first,FLOOR *flr){
	BULLET *p = first->next;
	BULLET *pp;
	int i,flag; //flag=1‚Íbullet‚ÌÁ–Å‚ğ•\‚·
	COORD2 crdt;
	ENEMY *ene;
	while(p->next != NULL){
		if(p->freq_cnt++ % p->freq == 0){
			p->speed.x += p->accel.x;
			p->speed.y += p->accel.y;
		}
		p->crd.x += p->speed.x;
		p->crd.y += p->speed.y;
		//enemy loop ‚ÅÕ“Ëˆ—
		flag=0;
		for(i=0; i < flr->enemy_num;i++){
			ene=&flr->enemy[i];
			if(ene->HP <= 0) continue;
			if(ene->crd.x - ene->size.x/2 <= p->crd.x && p->crd.x <= ene->crd.x + ene->size.x/2){
			       	crdt.x = 0;
			}else if(ene->crd.x - ene->size.x/2  > p->crd.x){
				crdt.x = ene->crd.x - ene->size.x/2 - p->crd.x;
			}else{
				crdt.x = ene->crd.x + ene->size.x/2 - p->crd.x;
			}

			if(ene->crd.y - ene->size.y/2 <= p->crd.y && p->crd.y <= ene->crd.y + ene->size.y/2){
			       	crdt.y = 0;
			}else if(ene->crd.y - ene->size.y/2  > p->crd.y){
				crdt.y = ene->crd.y - ene->size.y/2 - p->crd.y;
			}else{
				crdt.y = ene->crd.y + ene->size.y/2 - p->crd.y;
			}
			if(p->size/2 * p->size/2 >= crdt.x * crdt.x + crdt.y * crdt.y){
				ene->HP -= p->damage;
				flag=1;
				break;
			}




		}
		if(flag==0){	
			DrawRotaGraph(p->crd.x,p->crd.y,1.0,(-2*p->turnflag+1)*p->freq_cnt*0.2*p->type,p->handle,1,p->turnflag);
		}
		pp = p;
		p = p->next;
		if(pp->crd.x > SCREEN_WIDTH || pp->crd.x <= 0 || pp->crd.y > SCREEN_HIGHT || flag == 1) delete_bullet(pp);
	}
}
