#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define N 50
struct HANDAN{
  char handan_name[N];
  int kaisuu;
  long time;
  bool count;
};

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

  if(sec>=60){
    sec = sec-60;
    min = min+1;
  }
  if(min>=60){
    sec = min-60;
    hour = hour+1;
  }
  //printf("%ld年%ld月%ld日%ld時%ld分です\n",year,month,day,hour,min);
  //printf("kikan is %ld\n",kikan);
  
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
  struct HANDAN han[N];
  struct LOG log[N]; 
  char s[N][N],*cp;
  char name[4][15]={"10.20.30.1/16","10.20.30.2/16","192.168.1.1/24","192.168.1.2/24"};
  const char *sikiri=",";
  long handan_time=0,kikan;
  int i = 0,j = 0,h=0;
  int kaisuu[4] = {};
  bool count[N]={};//countによって故障したかどうか判断
  
  fp = fopen("server.txt","r");
  
  while(fgets(s[i],N,fp)!=NULL){
    cp = strtok(s[i],sikiri);
    log[i].time=atol(cp);//ここで時間を挿入、文字列から数に変換
    int c=0;
    while(cp!=NULL){
      cp = strtok(NULL,sikiri);
      if(cp!=NULL&&c==0){
	strcpy(log[i].server_name,cp);	//ここでサーバーの名前を挿入
	c++;
	
	for(h=0;h<=j;h++){
	  if(han[h].count==true){ //if(故障していたら)故障状況をプリント
	    if(strcmp(han[h].handan_name,log[i].server_name)==0){	      
	      kikan=log[i].time-han[h].time;
	      printf("サーバー%sが故障状態です\n",han[h].handan_name);
	      //printf("log.time is %ld\nhandan is %ld\n",log[i].time,han[h].time);
	      printTime(kikan);
	      han[h].count = false;
	      
	    }
	  }
	  
	}
	
      }
      
      if(cp!=NULL&&c==1){
	strcpy(log[i].result,cp);//ここで結果を挿入
	if(strncmp(log[i].result,"-",1)==0){                      //1."-"かどうか
	  for(h=0;h<4;h++){//回数計算
	    if(strcmp(log[i].server_name,name[h])==0){           //入力された値がどれかと一緒ならkaisuuを+1する 
	      if(kaisuu[h]==0){                                   //2.一回目か
		strcpy(han[j].handan_name,log[i].server_name);
		han[j].time = log[i].time;
	      }
	      kaisuu[h]++;
	    }
	  }
	  //printf("%d %d %d %d\n",kaisuu[0],kaisuu[1],kaisuu[2],kaisuu[3]);
	}else{
	  for(h=0;h<=j;h++){
	    if(strcmp(han[h].handan_name,log[i].server_name)==0){//名前が以前に出てきていないか確認
	      han[h].count=true;
	    }
	  }
	}
      }
      j++;
    }
    
    i++;
  }
  
  fclose(fp);
  return 0;
}
