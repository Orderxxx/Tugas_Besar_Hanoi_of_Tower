#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NAMA_FILE "testajaa.dat"

typedef struct{
	char nama[50];
	int menit;
	int detik; 
	int sisaLangkah;
}player;

void inputData(char nama[], int detik, int langkah);
void tampilData();
void urutkan(player a[], int n, int choice);

int main(){
	char nama[50];
	int jam, menit, detik, sisaLangkah, choice;
	do{
		printf("1. Input Data\n");
		printf("2. Tampilkan Leaderboard\n");
		printf("3. Keluar\n");
		printf("   Masukkan Pilihan : ");
		scanf("%d",&choice);
		getchar();
		
		switch (choice) {
            case 1:
            	system("cls");
                printf("Masukkan Nama : ");
				fgets(nama, 50,stdin);
				nama[strcspn(nama, "\n")] = '\0';
				printf("Masukkan detik : ");
				scanf("%d",&detik);
				printf("Masukkan sisa langkah : ");
				scanf("%d",&sisaLangkah);
                inputData(nama,detik,sisaLangkah);
                break;
            case 2:
            	system("cls");
            	printf("1. Urut berdasarkan waktu\n");
            	printf("2. Urut berdasarkan langkah\n");
            	printf("   Masukkan pilihan : ");
            	scanf("%d",&choice);
                tampilData(choice);
                break;
            case 3:
            	system("cls");
                printf("Tekan tombol apapun untuk keluar\n");
                break;
            default:
            	system("cls");
                printf("Input tidak sesuai. Mohon masukkan ulang\n");
        }
    } while (choice != 3);
    
	return 0;
}

void inputData(char nama[], int detik, int langkah){
	player x;
	player y[50];
	strcpy(x.nama,nama);
	if(detik % 60 == 0){
		x.menit = detik / 60;
		x.detik = 0;
	}
	else if(detik > 60){
		x.menit = detik / 60; 
		x.detik = detik - (x.menit * 60 );
	}else{
		x.menit = 0;
		x.detik = detik;
	}
	x.sisaLangkah = langkah;
	int i, target = 0 ,n = 0;

	FILE *file = fopen(NAMA_FILE,"rb");
	if (file == NULL) {
      printf("File baru saja dibuat. Silakan input ulang.\n");
      file = fopen(NAMA_FILE,"wb");
	  return;   
    }
    while (fread(&y[n], sizeof(player), 1, file)) {
        n++;
    }
    fclose(file);
    
    printf("%s",x.nama);
    
    for(i = 0; i < n; i++){
    	if(strcmp(y[i].nama, x.nama) == 0){
    		target += 1;
    		break;
		}
	}
	if(target == 1){
    	y[i].menit = x.menit;
    	y[i].detik = x.detik;
    	y[i].sisaLangkah = x.sisaLangkah;
	}else{
    	y[n] = x;
    	n++;
	}
	
	file = fopen(NAMA_FILE,"wb");
	if (file == NULL) {
      printf("File tidak ditemukan.\n");
	  return;   
    }
    for(i = 0; i < n; i++){
    	fwrite(&y[i],sizeof(player),1,file);
	}
    fclose(file);
    
    printf("Data leaderboard berhasil disimpan!\n");
    sleep(1);
    system("cls");
}
	
	
void tampilData(int choice){
	player y[50];
	int i,j,n = 0;
	
	FILE *file = fopen(NAMA_FILE, "rb");

    if (file == NULL) {
        printf("File baru saja dibuat. Silakan input ulang.\n");
      	file = fopen(NAMA_FILE,"wb");  	
        return;
    }

    while (fread(&y[n], sizeof(player), 1, file)) {
        n++;
    }
    fclose(file);
    
    urutkan(y, n, choice);
    
	printf("\n=== Leaderboard ===\n");
	printf("==================================================\n");
	printf("| No | Nama            | Waktu | Langkah |\n");
	printf("==================================================\n");
	for (i = 0; i < n; i++) {
	    if(y[i].detik < 10){
			printf("| %-2d | %-15s | %d:0%d  | %d      |\n",
	        i + 1, y[i].nama,y[i].menit, y[i].detik, y[i].sisaLangkah);
	    }else{
	    	printf("| %-2d | %-15s | %d:%d  | %d       |\n",
	        i + 1, y[i].nama,y[i].menit, y[i].detik, y[i].sisaLangkah);
		}
	    printf("==================================================\n");
	}
	
}

void urutkan(player a[], int n, int choice) {
    int i, j;
    player temp;
	
	switch(choice){
	
	case 1:
	    for (i = 0; i < n - 1; i++) {
	        for (j = 0; j < n - i - 1; j++) {
	            int totalWaktu1 = a[j].menit * 60 + a[j].detik;
	            int totalWaktu2 = a[j + 1].menit * 60 + a[j + 1].detik;
	
	            if (totalWaktu1 > totalWaktu2) {
	                temp = a[j];
	                a[j] = a[j + 1];
	                a[j + 1] = temp;
	            }
	        }
	    }
	    break;
	case 2:
		for (i = 0; i < n - 1; i++) {
	        for (j = 0; j < n - i - 1; j++) {
	        	
	            if ( a[j].sisaLangkah > a[j+1].sisaLangkah) {
	                temp = a[j];
	                a[j] = a[j + 1];
	                a[j + 1] = temp;
	            }
	        }
	    }
	    break;
	}
}
