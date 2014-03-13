#include "DxLib.h"
#include "prot.h"
#include "mypath.h"
#include <stdio.h>
#include <string.h>

BULLET *add_bullet(BULLET *first){
	BULLET *newb;
	newb = (BULLET *)malloc(sizeof(BULLET));
	newb->next = first;
	newb->pre = NULL;
	return newb;
}

void delete_bullet(BULLET *corrent){
	if(corrent->pre != NULL) corrent->pre->next=corrent->next;
	if(corrent->next != NULL) corrent->next->pre=corrent->pre;
	free(corrent);
}

void action_bullet(BULLET *corrent){
	BULLET *p = corrent;
	BULLET *pp  ;
		//print_int(30);
	while(p != NULL){
		//print_int(2);
		p->speed.x += p->accel.x;
		p->speed.y += p->accel.y;
		p->crd.x += p->speed.x;
		//print_int(p->crd.x);
		p->crd.y += p->speed.y;
		DrawRotaGraph(p->crd.x,p->crd.y,1.0,0.0,p->handle,1,p->turnflag);
		pp = p;
		p = p->next;
		if(pp->crd.x > SCREEN_WIDTH || pp->crd.x <= 0 || pp->crd.y > SCREEN_HIGHT){ delete_bullet(pp);
		}
	}
}
