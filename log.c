#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 50

struct LOG{
  long time;
  char server_name[N];
  char result[N];
};

void printTime(long kikan){
  char kikan2[14];
  sprintf(kikan2,"%ld",kikan);
  int len = strlen(kikan2);
  long sec,min,hour,day,month,year;
  year = kikan/10000000000;
  month = (kikan/1000000)%100;
  day = (kikan/10000)%100;
  hour = (kikan/100)%100;
  min = kikan/100;
  sec = kikan%100;

  //printf("%ld年%ld月%ld日%ld時%ld分です\n",year,month,day,hour,min);

  
  if(len<=2){
    printf("故障期間は%ld秒です\n",sec);
  }else if(len<=4){
    printf("故障期間は%ld分%ld秒です\n",min,sec);
  }else if(len<=6){
    printf("故障期間は%ld時%ld分%ld秒です\n",hour,min,sec);
  }else if(len<=8){
    printf("故障期間は%ld日%ld時%ld分%ld秒です\n",day,hour,min,sec);
  }else if(len<=10){
    printf("故障期間は%ld月%ld日%ld時%ld分%ld秒です\n",month,day,hour,min,sec);
  }else if(len<=14){
    printf("故障期間は%ld年%ld月%ld日%ld時%ld分%ld秒です\n",year,month,day,hour,min,sec);
  }
}
  
  
  
int main(){
  FILE *fp;
  struct LOG log[10];
  
  char s[N][N],*cp,handan_name[N];
  const char *sikiri=",";
  long handan_time=0,kikan;
  int i = 0,j = 0,len=0,ct=0; //ctによって一度のエラーにつき一回のみと判断
  
  //printTime(20201111111010);
  
  fp = fopen("server.txt","r");
  
  while(fgets(s[i],N,fp)!=NULL){
    cp = strtok(s[i],sikiri);
    log[i].time=atol(cp);//ここで時間を挿入、文字列から数に変換
    //printf("%ld %s\n", log[i].time,cp);
    int c=0;
    while(cp!=NULL){
      cp = strtok(NULL,sikiri);
      //printf("unko\n");
      if(cp!=NULL&&c==0){
	strcpy(log[i].server_name,cp);	//ここでサーバーの名前を挿入
	c++;
	//printf("ok %d\n",i);
	
	if(strcmp(&handan_name[len-1],"1")&&
	   strncmp(handan_name,log[i].server_name,8)==0&&ct==1){ //if(故障していたら)ここでサーバーの名前がかぶってないか判断
	  kikan=log[i].time-handan_time;

	  printTime(kikan);
	  ct--;
	}else if(strcmp(&handan_name[len-1],"2")&&
		 strncmp(handan_name,log[i].server_name,9)==0&&ct==1){
	  kikan=log[i].time-handan_time;
	  printTime(kikan);
	  ct--;
	}
      }
      
      if(cp!=NULL&&c==1){
	strcpy(log[i].result,cp);//ここで結果を挿入
	if(strncmp(log[i].result,"-",1)==0&&ct==0){
	  printf("サーバー%sが故障状態です\n",log[i].server_name);//サーバーが故障しているか判断
	  len=strlen(log[i].server_name);
	  handan_time = log[i].time;
	  strcpy(handan_name,log[i].server_name);
	  ct++;
	  //printf("len is %d\n",len);
	}
      }
    }
    i++;
  }
  
  /*for(j=0;j<10;j++){
    printf("time is %d\n",log[j].time);
    printf("server_name is %s\n",log[j].server_name);
    printf("result is %s\n",log[j].result);
   
    }*/ //確認用
  
  
  fclose(fp);
  free()
  return 0;
}
