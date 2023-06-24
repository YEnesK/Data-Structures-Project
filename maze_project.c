#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAXC 100
#define MAXR (MAXC + 1) / 2

void dosyaOku(int* , int* , int* , int* , int* , int* , char dosyaAdi[]);
void baslatOyun(int n , int m , int i , int j , int cikis_i , int cikis_j);
void DFS(int n , int m , int i , int j , int cikis_i , int cikis_j , int *flag);
void mazeYazdir(int n, int m);
void delay(int milli_seconds);

char a[MAXR][MAXC+1] = {""}; 
int b[MAXR][MAXC+1];
int visited[MAXR][MAXC+1]={0};
int puan=5;

int main () {
	int n,m;
	int baslangic_i,baslangic_j,cikis_i,cikis_j;
	
	dosyaOku(&n,&m,&baslangic_i,&baslangic_j,&cikis_i,&cikis_j,"maze.txt");
	
	printf("\n\n");
	
	baslatOyun(n,m,baslangic_i,baslangic_j,cikis_i,cikis_j);
    

return 0;
}

void dosyaOku(int* n , int* m , int* i, int* j, int* cikis_i, int* cikis_j, char dosyaAdi[]){
	
	srand(time(NULL));
	
	int random;
    int row = 0, col = 0, nrow = 0, ncol = 0;
    int len;
	
	FILE *fp = fopen (dosyaAdi, "r");

    if (!fp) {
        printf("Dosya Acilamadi!!!\n\n");
        return ;
    }

    while (row < MAXR && fgets (a[row], MAXC, fp)) {
        len = strlen (a[row]);
        if (len && a[row][len-1] == '\n'){   
            a[row][--len] = 0;  
    	}
    	
        if (!row)       
            ncol = len;
            
        

        for (col = 0; col < len; col++){
        	//printf("%c",a[row][col]);
        	if(a[row][col]==' '){
        		b[row][col]=1;
			}else if(a[row][col]=='b'){
				b[row][col]=1;
				*i=row;
				*j=col;
			}else if(a[row][col]=='c'){
				b[row][col]=1;
				*cikis_i=row;
				*cikis_j=col;
			}else{
				b[row][col]=0;
			}
		}
        //printf("\n");

        row++;
    }

    
    fclose (fp);
    nrow = row;
    
    //printf("\nElma Koyulmus Hali\n\n");
    
    for (row = 0; row < nrow; row++) {
        for (col = 0; col < ncol; col++) {
            if (col  &&   a[row][col-1] == ' ' && a[row][col] == ' ' && a[row][col+1] == ' '){
				random=rand()%2;
				if(random)
					a[row][col] = 'o';
			}
                
				
            //printf("%c",a[row][col]);
        }
       // printf("\n");
    }
    
    *n=nrow;
    *m=ncol;
    
	
}

void baslatOyun(int n , int m , int i , int j , int cikis_i , int cikis_j){
	int flag = 0;
	int *flag_ptr = &flag;
	DFS(n,m,i,j,cikis_i,cikis_j,flag_ptr);
	
}

void DFS(int n , int m , int i , int j , int cikis_i , int cikis_j , int *flag){

	visited[i][j] = 1;
	
	if((i==cikis_i) && (j==cikis_j)){
		*flag=1;
		printf("\nbitti\n");
		//mazeYazdir(n,m);
	}
	
	if (*flag == 0) {                   //cikis bulunmadiysa
		
		if(a[i][j]=='o'){
			puan += 10;                     //elma goruldu
			printf("\nPuan=%d\n",puan);
		}
		
		if( (b[i+1][j]==0 && b[i-1][j]==0 && b[i][j-1]==0) || (b[i][j+1]==0 && b[i-1][j]==0 && b[i][j-1]==0) || (b[i][j+1]==0 && b[i+1][j]==0 && b[i][j-1]==0) || (b[i][j+1]==0 && b[i+1][j]==0 && b[i-1][j]==0)){
			puan -= 5;
			printf("\nPuan=%d\n",puan);          //cikmaz sokak
		}
		a[i][j]='*';
		mazeYazdir(n,m);
		delay(100);                                        //delay suresi ayarlama
	}
		

	if( b[i][j+1] == 1 && visited[i][j+1] == 0){
		DFS(n,m,i,j+1,cikis_i,cikis_j,flag);
	}
	if( b[i+1][j] == 1 && visited[i+1][j] == 0){
		DFS(n,m,i+1,j,cikis_i,cikis_j,flag);
	}
	
	if( b[i][j-1] == 1 && visited[i][j-1] == 0){
		DFS(n,m,i,j-1,cikis_i,cikis_j,flag);
	}
	if( b[i-1][j] == 1 && visited[i-1][j] == 0){
		DFS(n,m,i-1,j,cikis_i,cikis_j,flag);
	}

	return;
}

void mazeYazdir(int n, int m){
	int i,j;
	
	for (i= 0; i < n; i++) {
        for (j= 0; j < m; j++) {
        	printf("%c",a[i][j]);
		}
		printf("\n");
	}
	
}

void delay(int milli_seconds){
    
    clock_t start_time = clock();
  
    while (clock() < start_time + milli_seconds)
        ;
}
