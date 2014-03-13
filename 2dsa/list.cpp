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
void action_bullet(BULLET *first){
	BULLET *p = first->next;
	BULLET *pp;
	while(p->next != NULL){
		if(p->freq_cnt++ % p->freq == 0){
			p->speed.x += p->accel.x;
			p->speed.y += p->accel.y;
		}
		p->crd.x += p->speed.x;
		p->crd.y += p->speed.y;
		DrawRotaGraph(p->crd.x,p->crd.y,1.0,0.0,p->handle,1,p->turnflag);
		pp = p;
		p = p->next;
		if(pp->crd.x > SCREEN_WIDTH || pp->crd.x <= 0 || pp->crd.y > SCREEN_HIGHT) delete_bullet(pp);
	}
}
