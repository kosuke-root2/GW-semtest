#include <thread>
#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>
#include <string>

#define SEM_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)

void CreateSem(sem_t **ct, std::string name);
void DeleteSem(sem_t **ct, std::string name);

int main(){
	/* setting parameters */
	sem_t **ppct;
	sem_t *pct;
	sem_t ct = {0};

	sem_t **ppct2;
	sem_t *pct2;
	sem_t ct2 = {0};

	sem_t **ppct3;
	sem_t *pct3;
	sem_t ct3 = {0};

	pct = &ct;
	ppct = &pct;

	pct2 = &ct2;
	ppct2 = &pct2;

	pct3 = &ct3;
	ppct3 = &pct3;

	int *semvalue;
	int tmp = 0;
	semvalue = &tmp;
	std::string semname1 = "/SEMNAME1";
	std::string semname2 = "/SEMNAME2";

	printf("TEST:Hello world!\n");
	printf("TEST:pp is %p\n", ppct);
	printf("TEST:p  is %p\n", *ppct);
	printf("TEST:numis %d\n", **ppct);

	/* get semaphore1 */ 
	CreateSem(ppct, semname1);
	printf("main:ctp is %p\n",*ppct);
#if 1
	if(sem_getvalue(*ppct, semvalue) < 0){
		printf("main:getvalue ERROR !\n");
	}else{
		printf("main:semvalue2 is %d\n", *semvalue);
	}
#endif

#if 1
	/* get semaphore2 */ 
	CreateSem(ppct2, semname1);
	printf("main:ctp2 is %p\n",*ppct2);
	if(sem_getvalue(*ppct2, semvalue) < 0){
		printf("main:getvalue ERROR !\n");
	}else{
		printf("main:semvalue2 is %d\n", *semvalue);
	}

#endif
	DeleteSem(ppct, semname1);

	CreateSem(ppct3, semname1);

	DeleteSem(ppct2, semname1);
	DeleteSem(ppct3, semname1);

	return 0;
}

void CreateSem(sem_t **ct, std::string name){
	int *semvalue;
	int tmp = 0;
	semvalue = &tmp;

	*ct = sem_open(name.c_str(), O_CREAT, SEM_PERMS, 10);
	if(*ct == SEM_FAILED){
		printf("crt:sem_open ERROR !\n");
	}else{
		printf("crt:sem_open finish !\n");
	}

	printf("crt:%p\n", *ct);
#if 1
	if(sem_getvalue(*ct, semvalue) < 0){
		printf("crt:sem_getvalue1 ERROR !\n");
	}else{
		printf("crt:semvalue is %d\n", *semvalue);
	}
#endif
	if(sem_wait(*ct) < 0){
		printf("crt:sem_wait ERROR !\n");
	}else{
		printf("crt:semwait finish !\n");
	}

	if(sem_getvalue(*ct, semvalue) < 0){
		printf("crt:getvalue2 ERROR !\n");
	}else{
		printf("crt:semvalue2 is %d\n", *semvalue);
		printf("crt:*ct is %p\n", *ct);
	}
	if(sem_getvalue(*ct, semvalue) < 0){
		printf("crt:getvalue2 ERROR !\n");
	}else{
		printf("crt:semvalue2 is %d\n", *semvalue);
		printf("crt:*ct is %p\n", *ct);
	}
}

void DeleteSem(sem_t **ct, std::string name){

	int *semvalue;
	int tmp = 0;
	semvalue = &tmp;

	if(sem_post(*ct) < 0){
		printf("del:sem_post ERROR !\n");
	}else{
		printf("del:sem_post finish !\n");
	}

	printf("del:*ct is %p\n", *ct);	

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
	/* after sem_close, if no one use semaphore, segmentation fault occers. */
#if 0	
	if(sem_getvalue(*ct, semvalue) < 0){
		printf("del:sem_getvalue4 ERROR !\n");
	}else{
		printf("del:semvalue4 is %d\n", *semvalue);
	}
#endif
#if 1 	
	if(sem_unlink(name.c_str()) < 0){
		printf("del:sem_unlink ERROR ! \n");
	}else{
		printf("del:sem_unlink finish !\n");
	}
#endif
}
