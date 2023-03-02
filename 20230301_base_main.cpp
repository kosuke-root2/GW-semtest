#include <thread>
#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>

#define SEM_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)
#define SEMNAME "/sem4"

void CreateSem(sem_t **ct);
void DeleteSem(sem_t **ct);

int main(){
	sem_t **ppct;
	sem_t *pct;
	sem_t ct = (sem_t)1;
	pct = &ct;
	ppct = &pct;

	int *semvalue;
	//string semname = "

	printf("TEST:Hello world!\n");
	printf("TEST:pp is %p\n", ppct);
	printf("TEST:p  is %p\n", *ppct);
	printf("TEST:numis %d\n", **ppct);

	CreateSem(ppct);
	sem_getvalue(*ppct, semvalue);
	printf("main:semvalue2 is %d\n", *semvalue);

	printf("main:ctp is %p\n",*ppct);

	DeleteSem(ppct);
	
	return 0;
}

void CreateSem(sem_t **ct){
	int *semvalue;

	*ct = sem_open(SEMNAME, O_CREAT, SEM_PERMS, 2);
	if(*ct == SEM_FAILED){
		printf("crt:sem_open ERROR !\n");
	}else{
		printf("crt:sem_open finish !\n");
	}

	printf("crt:%p\n", *ct);

	if(sem_getvalue(*ct, semvalue) < 0){
		printf("crt:sem_getvalue1 ERROR !\n");
	}else{
		printf("crt:semvalue is %d\n", *semvalue);
	}
	if(sem_wait(*ct) < 0){
		printf("crt:sem_wait ERROR !\n");
	}else{
		printf("crt:semwait finish !\n");
	}
}

void DeleteSem(sem_t **ct){

	int *semvalue;

	if(sem_post(*ct) < 0){
		printf("del:sem_post ERROR !\n");
	}else{
		printf("del:sem_post finish !\n");
	}

	if(sem_getvalue(*ct, semvalue) < 0){
		printf("del:sem_getvalue3 ERROR !\n");
	}else{
		printf("del:semvalue3 is %d\n", *semvalue);
	}

	if(sem_close(*ct) < 0){
		printf("del:sem_close ERROR !\n");
	}else{
		printf("del:sem_close finish !\n");
	}

	if(sem_getvalue(*ct, semvalue) < 0){
		printf("del:sem_getvalue4 ERROR !\n");
	}else{
		printf("del:semvalue4 is %d\n", *semvalue);
	}

	if(sem_unlink(SEMNAME) < 0){
		printf("del:sem_unlink ERROR ! \n");
	}else{
		printf("del:sem_unlink finish !\n");
	}
}
