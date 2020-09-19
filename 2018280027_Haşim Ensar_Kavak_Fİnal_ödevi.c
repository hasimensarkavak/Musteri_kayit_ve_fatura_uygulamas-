#include<stdio.h>
#include <stdlib.h>
#include<locale.h>
#include <string.h> 

//Ha�im Ensar KAVAK 2018280027

typedef struct //m��teriler i�in struct
{
	int hspno;
	char ad[20];
	char soyad[20];
	char tel[11];
	char adres[100];
	int bakiye;
}musteriler;


typedef struct //�r�nler i�in struct
{
	int urunkod;
	char urunad[20];
	int fiyat;
	int stok;
}urunler;

// �r�nler men�s� i�in olan fonksiyonlar
void urundosya() //Kay�tlar� s�f�rlama ve olu�turmak i�in.
{
	FILE *dosya;
	if((dosya=fopen("�r�nler.dat","w"))==NULL)
	{
		printf("Dosya a��lamad�!\n");
	}
	fclose(dosya);
}

void urunekleme() //�r�n ekleme fonksiyonu.
{
	urunler urun; //struct bir de�i�kene girdi al�p bunu dosyaya at�yoruz.
	FILE *dosya;
	if((dosya=fopen("�r�nler.dat","a"))==NULL)
	{
		printf("Dosya a��lamad�!\n");
	}
	int secim=1;
	while(secim==1)  
	{
		fflush(stdin);
		printf("\n�r�n kodunu giriniz. (1-1000 aras�)\n"); 
		scanf("%d",&urun.urunkod);
		fflush(stdin);
		printf("�r�n�n ad�n� giriniz. (max 20 karakter)\n");
		scanf("%s",&urun.urunad);
		fflush(stdin);
		printf("�r�n�n fiyat�n� giriniz.\n");
		scanf("%d",&urun.fiyat);
		fflush(stdin);
		printf("�r�n�n stok miktar�n� giriniz.\n");
		scanf("%d",&urun.stok);
		fflush(stdin);
		
		fwrite(&urun,sizeof(urun),1,dosya);
	
		printf("�r�n kay�tlar�na devam etmek i�in => 1\n");
		printf("Ana men�ye d�nmek i�in => 0\n\n");
		scanf("%d",&secim);
		fflush(stdin);
		if(secim==0)
		{
			break;
		}
	}
	fclose(dosya);
}


void tumurunler() // t�m �r�nleri ekrana yazd�rmak i�in olan fonksiyon.
{
	urunler urun; // yine struct bir de�i�kenle yap�yoruz.
	FILE *dosya;
	if((dosya=fopen("�r�nler.dat","r"))==NULL)
	{
		printf("Dosya a��lamad�!\n");
	}
	int sayac=0;
	while(fread(&urun,sizeof(urun),1,dosya)==1) // her dosyadan okudu�umuzda ekrana yazd�r�yoruz.
	{
		sayac++;
		printf("%d -)\n",sayac);
		printf("�r�n Kodu : %d\n",urun.urunkod);
		printf("�r�n Ad� : %s\n",urun.urunad);
		printf("�r�n Fiyat� : %d\n",urun.fiyat);
		printf("�r�n Stok Miktar� : %d\n\n",urun.stok);
	}
	fflush(stdin); 
	fclose(dosya);
}


void urunarama() //�r�n arama fonksiyonu.
{
	urunler urun;
	FILE *dosya;
	if((dosya=fopen("�r�nler.dat","r"))==NULL)
	{
		printf("Dosya a��lamad�!\n");
	}
	int secim;
	do
	{
	printf("�r�n koduna g�re arama yapmak i�in => 1\n");
	printf("�sime g�re arama yapmak i�in => 2\n");
	scanf("%d",&secim);
	fflush(stdin); 
	if(secim==1)
	{
		int aranan;  //Arad���m�z �r�n kodunu tutan de�i�ken.
		printf("G�r�nt�lemek istedi�iniz �r�n�n �r�n kodunu giriniz.\n");
		scanf("%d",&aranan);
		fflush(stdin); 
		while(fread(&urun,sizeof(urun),1,dosya)==1)
		{
			if(aranan==urun.urunkod)
			{
				printf("�r�n Kodu : %d\n",urun.urunkod);
				printf("�r�n Ad� : %s\n",urun.urunad);
				printf("�r�n Fiyat� : %d\n",urun.fiyat);
				printf("Stok Miktar� : %d\n\n",urun.stok);
				break;
			}
		}
		if(aranan!=urun.urunkod) //hata mesaj�.
		{
			printf("Arad���n�z �r�n kodunda �r�n bulunamad�!!!\n");
		}
	}
	if(secim==2)
	{
		char ara[]="";   //Arad���m�z harf hece veya ismi tutan de�i�ken.
		printf("G�r�nt�lemek istedi�iniz �r�n�n ismini giriniz.(�sminin i�inde ge�en harf  veya heceye g�re de aran�r.)\n");
		scanf("%s",&ara);
		fflush(stdin); 
		while(fread(&urun,sizeof(urun),1,dosya)==1)
		{
			
			if(strstr(urun.urunad,ara)!=NULL)
			{
				printf("�r�n Kodu : %d\n",urun.urunkod);
				printf("�r�n Ad� : %s\n",urun.urunad);
				printf("�r�n Fiyat� : %d\n",urun.fiyat);
				printf("Stok Miktar� : %d\n\n",urun.stok);
			}
		}
	}
	printf("\nKay�t g�r�nt�lemeye devam etmek i�in => 1\n");
	printf("Ana men�ye d�nmek i�in => 0\n\n");
	scanf("%d",&secim);
	fflush(stdin); 
	}while(secim==1);
	
	fclose(dosya);
}


void urunguncelleme() //�r�n g�ncelleme fonksiyonu.
{
	urunler *urun=(urunler*)malloc(1*sizeof(urunler)); //�r�nler i�in dizi tan�mlad�m.
	fflush(stdin);
	FILE *dosya;
	if((dosya=fopen("�r�nler.dat","r"))==NULL)
	{
		printf("Dosya a��lamad�!\n");
	}
	int i=0;
	while(fread(&urun[i],sizeof(urunler),1,dosya)==1) //�r�n g�ncellemesi yapmak i�in t�m  �r�nleri diziye al�yorum.
	{
		i++;
		urun=(urunler *)realloc(urun,(i+1)*sizeof(urunler)); //Her �r�n ald���mda dizi boyutunu artt�r�yorum.	
	}
	fclose(dosya);
	int secim=2,aranan,j;
	while(1)
	{
		go:
		printf("G�ncellemek istedi�in �r�n�n �r�n kodunu giriniz. (�r�n kodunu bilmiyorsan�z Ana Men�ye gidip �r�n G�r�nt�leme ekran�ndan ��reniniz!!!\nAna men� i�in => 0)\n");
		scanf("%d",&aranan);
		fflush(stdin);
		if(aranan==0)
		{
			break;
		}
		for(j=0;j<=i;j++)
		{
			if(urun[j].urunkod==aranan)
			{
				secim=j;
				break;
			}		
		}
		if(aranan!=urun[j].urunkod)
		{
			printf("Bu �r�n kodunda kay�t bulunamad�!!!\n\n");
			printf("Ba�ka �r�n kodu girmek i�in => 1\n");
			printf("Ana men�ye d�nmek i�in => 0\n");
			scanf("%d",&secim);
			fflush(stdin); 
			if(secim==0)
			{
				break;
			}
			if(secim==1)
			{
				goto go;
			}
		}
		printf("�r�n�n fiyat�n� g�ncellemek i�in => 1\n");
		printf("�r�n�n stok miktar�n� g�ncellemek i�in => 2\n");
		printf("Bir �nceki men�ye d�nmek i�in => 0\n");
		scanf("%d",&secim);
		fflush(stdin);
		switch(secim)
		{
			case 0:
				goto go;
				break;
			case 1:
				printf("Yeni �r�n fiyat�n� giriniz.\n");
				scanf("%d",&urun[j].fiyat);				// �r�n de�i�ikli�ini dizi �zerinde yap�yorum.
				fflush(stdin);
				break;
			case 2:
				printf("Yeni �r�n stok miktar�n� giriniz.\n");
				scanf("%d",&urun[j].stok);
				fflush(stdin);
				break;
		}
		printf("Ba�ka bir �r�n� g�ncellemek i�in => 1\n");
		printf("Ana men�ye d�nmek i�in => 0\n");
		scanf("%d",&secim);
		fflush(stdin); 
		if(secim==0)
		{
			break;
		}
		if(secim==1)
		{
			goto go;
		}
	}
	if((dosya=fopen("�r�nler.dat","w"))==NULL)  //Diziyi tekrar dosyaya yazd�r�yorum. De�i�mi� verilerde b�ylece yaz�lm�� oluyor.
	{
		printf("Dosya a��lamad�!\n");
	}
	for(j=0;j<i;j++)
	{
		fwrite(&urun[j],sizeof(urunler),1,dosya);
	}
	fclose(dosya);
	fflush(stdin);
}

//M��teriler men�s� i�in olan fonksiyonlar.

void kytdosya() //M��teri dosyas�n� s�f�rlamak ve olu�turmak i�in.
{
	FILE *dosya;
	if((dosya=fopen("m��teriler.dat","w"))==NULL)
	{
		printf("Dosya a��lamad�!\n");
	}
	fclose(dosya);
}


void kytekleme() //M��teri ekleme fonksiyonu.
{
	musteriler musteri;
	FILE *dosya;
	if((dosya=fopen("m��teriler.dat","a"))==NULL)
	{
		printf("Dosya a��lamad�!\n");
	}
	int secim=1;
	while(secim==1)  
	{
		fflush(stdin);
		printf("\nM��terinin hesap numaras�n� giriniz. (1-1000 aras�)\n"); // belli bir s�n�r olmas�n� istedi�im i�in . int aral���ndan b�y�k say� girmesinler diye.
		scanf("%d",&musteri.hspno);
		fflush(stdin);
		printf("M��terinin ad�n� giriniz. (max 20 karakter)\n");
		scanf("%s",&musteri.ad);
		fflush(stdin);
		printf("M��terinin soyad�n� giriniz. (max 20 karakter)\n");
		scanf("%s",&musteri.soyad);
		fflush(stdin);
		printf("M��terinin telefon numaras�n� giriniz. (ba��nda '0' olmadan)\n");
		scanf("%s",&musteri.tel);
		fflush(stdin);
		printf("M��terinin adres bilgisini giriniz. (max 100 karakter)\n");
		gets(musteri.adres); //Adresi gets ile ald�m ��nk� scnaf ile bo�luktan sonra yaz�lanlar� alam�yoruz.
		fflush(stdin);
		printf("M��terinin bakiyesini giriniz.\n");
		scanf("%d",&musteri.bakiye);
		fflush(stdin);
		
		fwrite(&musteri,sizeof(musteri),1,dosya);
	
		printf("M��teri kay�tlar�na devam etmek i�in => 1\n");
		printf("Ana men�ye d�nmek i�in => 0\n\n");
		scanf("%d",&secim);
		fflush(stdin);
		if(secim==0)
		{
			break;
		}
	}
	fclose(dosya);
}


void tummusteriler() //T�m m��terileri ekrana yazd�rma fonksiyonu.
{
	musteriler musteri;
	FILE *dosya;
	if((dosya=fopen("m��teriler.dat","r"))==NULL)
	{
		printf("Dosya a��lamad�!\n");
	}
	int sayac=0;
	while(fread(&musteri,sizeof(musteriler),1,dosya)==1)
	{
		sayac++;
		printf("%d -)  M��terinin:\n",sayac);
		printf("Hesap No : %d\n",musteri.hspno);
		printf("Ad� : %s\n",musteri.ad);
		printf("Soyad� : %s\n",musteri.soyad);
		printf("Telefon No : %s\n",musteri.tel);
		printf("Adres : ");
		puts(musteri.adres); 
		printf("Bakiye : %d\n\n",musteri.bakiye);
	}
	fflush(stdin); 
	fclose(dosya);
}


void arama() //M��teri arama fonksiyonu.
{
	musteriler musteri;
	FILE *dosya;
	if((dosya=fopen("m��teriler.dat","r"))==NULL)
	{
		printf("Dosya a��lamad�!\n");
	}
	int secim;
	do
	{
	printf("M��teri hesap numaras�na g�re arama yapmak i�in => 1\n");
	printf("�sime g�re arama yapmak i�in => 2\n");
	scanf("%d",&secim);
	fflush(stdin); 
	if(secim==1)
	{
		int aranan;
		printf("G�r�nt�lemek istedi�iniz m��terinin hesap numaras�n� giriniz.\n");
		scanf("%d",&aranan);
		fflush(stdin); 
		while(fread(&musteri,sizeof(musteri),1,dosya)==1)
		{
			if(aranan==musteri.hspno)
			{
				printf("Hesap No : %d\n",musteri.hspno);
				printf("Ad� : %s\n",musteri.ad);
				printf("Soyad� : %s\n",musteri.soyad);
				printf("Telefon No : %s\n",musteri.tel);
				printf("Adres : ");
				puts(musteri.adres);
				printf("Bakiye : %d\n\n",musteri.bakiye);
				break;
			}
		}
		if(aranan!=musteri.hspno)
		{
			printf("Arad���n�z hesap numaras�nda m��teri bulunamad�!!!\n");
		}
	}
	if(secim==2)
	{
		char ara[]="";
		printf("G�r�nt�lemek istedi�iniz m��terinin ismini giriniz.(ad-soyad ikisinde de arama yap�l�r. �sminin i�inde ge�en harf  veya heceye g�re de aran�r.)\n");
		scanf("%s",&ara);
		fflush(stdin); 
		while(fread(&musteri,sizeof(musteri),1,dosya)==1)
		{
			
			if(strstr(musteri.ad,ara)!=NULL || strstr(musteri.soyad,ara)!=NULL)
			{
				printf("Hesap No : %d\n",musteri.hspno);
				printf("Ad� : %s\n",musteri.ad);
				printf("Soyad� : %s\n",musteri.soyad);
				printf("Telefon No : %s\n",musteri.tel);
				printf("Adres : ");
				puts(musteri.adres);
				printf("Bakiye : %d\n\n",musteri.bakiye);
			}
		}
	}
	printf("\nKay�t g�r�nt�lemeye devam etmek i�in => 1\n");
	printf("Ana men�ye d�nmek i�in => 0\n\n");
	scanf("%d",&secim);
	fflush(stdin); 
	}while(secim==1);
	
	fclose(dosya);
}


void guncelleme() //M��teri verisi g�ncelleme fonksiyonu.
{
	musteriler *dizi=(musteriler*)malloc(1*sizeof(musteriler)); //m��teriler i�in dizi tan�mlad�m. Dizi boyutunu m��terilere g�re ayarlamak i�in 
	fflush(stdin);
	FILE *dosya;
	if((dosya=fopen("m��teriler.dat","r"))==NULL) //Burda da �r�nler de oldu�u gibi dizi ile yapt�m i�lemleri.
	{
		printf("Dosya a��lamad�!\n");
	}
	int i=0,a=1;
	while(fread(&dizi[i],sizeof(musteriler),1,dosya)==1)
	{
		i++;
		dizi=(musteriler *)realloc(dizi,(i+1)*sizeof(musteriler));// Dizi boyutunu m��terilere g�re ayarlamak i�in realloc kulland�m.
	}
	fclose(dosya);
	int secim=2,aranan,j;
	while(1)
	{
		go:
		printf("G�ncellemek istedi�in m��terinin hesap numaras�n� giriniz. (Hesap numaras�n� bilmiyorsan�z Ana Men�ye gidip M��teri G�r�nt�leme ekran�ndan ��reniniz!!!=> 0)\n");
		scanf("%d",&aranan);
		if(aranan==0)
		{
			break;
		}
		fflush(stdin);
		for(j=0;j<=i;j++)
		{
			if(dizi[j].hspno==aranan)
			{
				break;
			}		
		}
		if(aranan!=dizi[j].hspno)
		{
			printf("Bu hesap numaras�nda kay�t bulunamad�!!!\n\n");
			printf("Ba�ka hesap numaras� girmek i�in => 1\n");
			printf("Ana men�ye d�nmek i�in => 0\n");
			scanf("%d",&secim);
			fflush(stdin); 
			if(secim==0)
			{
				break;
			}
			if(secim==1)
			{
				goto go;
			}
		}
		printf("M��terinin telefon numaras�n� g�ncellemek i�in => 1\n");
		printf("M��terinin adresini g�ncellemek i�in => 2\n");
		printf("M��terinin bakiyesini g�ncellemek i�in => 3 (Bakiyeyi istedi�iniz gibi de�i�tirebilirsiniz)\n");
		printf("M��terinin bakiyesine ekleme yapmak i�in => 4 (Bakiyeye sadece ekleme yapabilirsiniz)\n");
		printf("Bir �nceki men�ye d�nmek i�in => 0\n");
		scanf("%d",&secim);
		fflush(stdin);
		switch(secim)
		{
			case 0:
				goto go;
				break;
			case 1:
				printf("Yeni telefon numaras�n� giriniz.\n");
				scanf("%s",&dizi[j].tel);
				fflush(stdin);
				break;
			case 2:
				printf("Yeni adresi giriniz.\n");
				gets(dizi[j].adres);
				fflush(stdin);
				break;
			case 3:
				printf("Yeni bakiyeyi giriniz.\n");
				scanf("%d",&dizi[j].bakiye);	
				fflush(stdin);
				break;
			case 4:
				printf("Eklemek istedi�iniz miktar� yaz�n�z.\n");
				scanf("%d",&aranan);  // Yeni bir de�i�ken olu�turmak istemedi�imden bunu kulland�m.
				fflush(stdin);  
				dizi[j].bakiye=dizi[j].bakiye+aranan;
				break;
		}
		printf("Ba�ka bir m��teriyi g�ncellemek i�in => 1\n");
		printf("Ana men�ye d�nmek i�in => 0\n");
		scanf("%d",&secim);
		fflush(stdin);
		if(secim==0)
		{
			break;
		}
		if(secim==1)
		{
			goto go;
		}
	}
	if((dosya=fopen("m��teriler.dat","w"))==NULL) // Dosyay� w ile a�t���m i�in de�i�memi� ve de�i�mi� veriler 2. kez yaz�lmad�.
	{
		printf("Dosya a��lamad�!\n");
	}
	for(j=0;j<i;j++)
	{
		fwrite(&dizi[j],sizeof(musteriler),1,dosya); //De�i�mi� verilerle birlikte dosyay� yeniden yaz�yoruz.
	}
	fclose(dosya);
	fflush(stdin); 
}

// Sat�� fonksiyonu.

void satis(musteriler *musteri,urunler *urun,int meleman,int ueleman) //Dizileri satismenu fonksiyonu i�inde doldurdum. dizilerin eleman say�s�n� da ald�m.
{
	int alici,j,secim,y,z,ukod,adet,toplam=0;
	char da[]=""; 
	fflush(stdin);
	FILE *fp;
	while(1)
	{
		basla:
		fflush(stdin);
		printf("Al�c�n�n hesap numaras�n� giriniz.\n");
		printf("Ana Men�ye d�nmek i�in => 0\n");
		scanf("%d",&alici);
		fflush(stdin);
		if(alici==0)
		{
			break;
		}
		for(j=0;j<=meleman;j++)
		{
			fflush(stdin);
			if(alici==musteri[j].hspno) //istenen m��teriyi hesap numaras�n� kar��la�t�rarak dizide ar�yoruz.
			{
				printf("M��teri bulundu.\n");
				fflush(stdin);
				y=j;
				break;
			}
		}
		fflush(stdin);
		if(alici!=musteri[j].hspno) //bulunamazsa �al��an if.
		{
			printf("M��teri bulunamad�!!!\n");
			printf("Ba�ka hesap numaras� girmek i�in => 1\n");
			printf("Ana men�ye d�nmek i�in => 0\n");
			scanf("%d",&secim);
			fflush(stdin);
			if(secim==0)
			{
				break;
			}
			if(secim==1)
			{
				goto basla;
			}
		}
		strcpy(da,musteri[y].ad);
		strcat(da,"_");
		strcat(da,musteri[y].soyad);
		strcat(da,".txt");
		if((fp=fopen(da,"w"))==NULL) //faturaya m��teri bilgilerini yazd�r�yoruz.
		{
			printf("Dosya a��lamad�!\n");
		}
		fprintf(fp,"**********Fatura***********\n");
		fprintf(fp,"M��terinin Hesap No: %d\n",musteri[y].hspno);
		fprintf(fp,"M��terinin Ad�: %s\n",musteri[y].ad);
		fprintf(fp,"M��terinin Soyad�: %s\n",musteri[y].soyad);
		fprintf(fp,"M��terinin Telefon No: %s\n",musteri[y].tel);
		fprintf(fp,"M��terinin Adresi: %s\n",musteri[y].adres);
		fprintf(fp,"**************************\n");
		fprintf(fp,"********Al�nan �r�nler*******\n\n");
		fprintf(fp,"�r�n Kodu		Ad�	Adet	Birim Fiyat�\n");
		fflush(stdin);
		tumu:
		system("cls");
		system("color a");
		tumurunler();// T�m �r�nleri listeliyoruz ki hangi �r�n�n al�nd���n� daha kolay bulsun.
		tekrar:
		printf("Sat�n al�nan �r�n�n �r�n kodunu giriniz. (Her seferinde 1 �r�n kodu giriniz. Al��veri�i tamamlamak i�in => 0)\n");
		scanf("%d",&ukod);
		fflush(stdin);
		if(ukod==0)
		{
			goto fatura;
		}
		for(j=0;j<ueleman;j++)
		{
			fflush(stdin);
			if(ukod==urun[j].urunkod) //�r�n dizisinde ar�yoruz.
			{
				z=j;
				fflush(stdin);
				break;
			}
		}
		fflush(stdin);
		if(ukod!=urun[z].urunkod) //�r�n kodu yanl�� girilirse.
		{
			printf("�r�n bulunamad�!!!\n");
			printf("Ba�ka �r�n kodu girmek i�in => 1\n");
			printf("T�m �r�nleri tekrar g�rmek i�in => 2\n");
			printf("Men�ye d�nmek i�in => 0\n");
			scanf("%d",&secim);
			fflush(stdin);
			switch(secim)
			{
				case 0:
					goto basla;
					break;
				case 1:
					goto tekrar;
					break;
				case 2:
					goto tumu;
					break;
			}
		}
		adet:
		printf("Adet giriniz.\n");
		scanf("%d",&adet);
		fflush(stdin);
		if(urun[z].stok<adet) //Yeterli stok olup olmad���n� kontrol ediyoruz.
		{
			printf("Stok miktar�ndan fazla giri� yapt�n�z l�tfen tekrar giriniz.\n");
			goto adet;
		}
		if(adet<=0)
		{
			printf("0 veya daha k���k bir de�er girdiniz l�tfen tekrar giriniz.\n");
			goto adet;
		}
		urun[z].stok=urun[z].stok-adet; // stoktan d���yoruz.
		toplam=toplam+(urun[z].fiyat*adet); //toplam �denecek tutar� tutuyoruz.
		fflush(stdin);
		fprintf(fp,"%d		%s	X %d	%dTL\n",urun[z].urunkod,urun[z].urunad,adet,urun[z].fiyat); //al�nan her �r�n i�in faturada bilgilendirme.
		fflush(stdin);
		goto tekrar; // kullan�c� 0 girene kadar �r�n al�m�na devam edebilmesi i�in.
		fatura:
		if(musteri[y].bakiye<toplam) //Bakiye yeterlimi diye kontrol.
		{
			FILE *f;
			if((f=fopen("�r�nler.dat","r"))==NULL)
			{
				printf("Dosya a��lamad�!\n");
			}
			int x=0;
			while(fread(&urun[x],sizeof(urunler),1,f)==1) //Bakiye yetersizse �r�nlerin stoklar�nda yapt���m�z de�i�ikli�i geri almak i�in tekrar okuduk.
			{
				x++;
				fflush(stdin);
			}
			fclose(f);
			printf("YETERS�Z BAK�YE!!!\n");
			printf("Yeniden denemek i�in => 1\n");
			printf("�ptal etmek i�in => 0\n");
			scanf("%d",&secim);
			fflush(stdin);
			switch(secim)
			{
				case 0:
					fprintf(fp,"\n!!!��LEM �PTAL ED�LM��T�R DOSYAYI S�LEB�L�RS�N�Z!!!!\n");//remove fonksiyonu �al��mad� nedeni ni bulamad�m o y�zden b�yle yapt�m.
					fclose(fp);
					printf("��lem iptal edilmi�tir...\nFatura dosyas�n� silebilirsiniz.\n");
					break;
				case 1:
					fclose(fp);
					toplam=0; //�r�nleri ba�tan se�ecekse toplam de�erini s�f�rl�yoruz.
					goto basla;
					break;
			}
		}
		if(musteri[y].bakiye>toplam) //bakiye yeterliyse.
		{
			fflush(stdin);
			musteri[y].bakiye=musteri[y].bakiye-toplam; //m��terinin bakiyesinden d���yoruz.
			fprintf(fp,"Toplam Tutar = %dTL\n\n",toplam);
			fprintf(fp,"Yeni M��teri Bakiyesi = %dTL",musteri[y].bakiye);
			fclose(fp);						 // fatura dosyas� haz�r.
			printf("Al��veri� Tamamland�.\n");
			printf("Faturan�z haz�r...\n");
			printf("Yeni al��veri� i�in => 1\n");
			printf("Ana men�ye d�nmek i�in => 0\n");
			scanf("%d",&secim);
			fflush(stdin);
			if(secim==0)
			{
				break;
			}
			if(secim==1)
			{
				goto basla;
			}
		}
	}
}

void musterimenu()
{
	int secim;
		while(1) //m��teri men�s�.
			{
				system("cls");
				system("color f");
				printf("M��teri kay�t dosyas�n� s�f�rlamak i�in yada dosya yoksa olu�turmak i�in => 1 (NOT:Eski kay�t silinir)\n");
				printf("Yeni m��teri eklemek i�in => 2\n");
				printf("M��teri kayd� g�ncelleme i�in => 3\n");
				printf("M��teri kayd� g�r�nt�leme i�in => 4\n");
				printf("Ana men�ye d�nmek i�in => 0\n");
				scanf("%d",&secim);
				fflush(stdin); // Bellekte tampon g�revi g�ren bir fonksiyonmu�. Baz� problemlerin �n�ne ge�ti. (scanf vs.)
				if(secim==0)
				{
					break;
				}
				if(secim==1)
				{
					kytdosya();
				}
				if(secim==2)
				{
					kytekleme();
				}
				if(secim==3)
				{
					fflush(stdin); 
					guncelleme();
				}
				if(secim==4)
				{
					int x;
					printf("T�m m��terileri g�r�nt�lemek i�in => 1\n");
					printf("Arama yapmak i�in => 2\n");
					scanf("%d",&x);
					if(x==1)
					{
						tummusteriler();
						getch();
					}
						if(x==2)
					{
						arama();
						getch();
					}
				}
			}
}

void urunmenu()
{
	int secim;
	while(1) //�r�n men�s�
			{
				system("cls");
				system("color c");
				printf("�r�n kay�t dosyas�n� s�f�rlamak i�in yada dosya yoksa olu�turmak i�in => 1 (NOT:Eski kay�t silinir)\n");
				printf("Yeni �r�n eklemek i�in => 2\n");
				printf("�r�n kayd� g�ncelleme i�in => 3\n");
				printf("�r�n kayd� g�r�nt�leme i�in => 4\n");
				printf("Ana men�ye d�nmek i�in => 0\n");
				scanf("%d",&secim);
				fflush(stdin); 
				if(secim==0)
				{
					break;
				}
				if(secim==1)
				{
					urundosya();
				}
				if(secim==2)
				{
					urunekleme();
				}
				if(secim==3)
				{
					fflush(stdin); 
					urunguncelleme();
				}
				if(secim==4)
				{
					int x;
					printf("T�m �r�nleri g�r�nt�lemek i�in => 1\n");
					printf("Arama yapmak i�in => 2\n");
					scanf("%d",&x);
					if(x==1)
					{
						tumurunler();
						getch();
					}
						if(x==2)
					{
						urunarama();
						getch();
					}
				}
			}
}

void satismenu()
{
	musteriler *dizi=(musteriler*)malloc(1*sizeof(musteriler)); //m��teriler ve �r�nler i�in dizi tan�mlad�m. 
	urunler *urun=(urunler*)malloc(1*sizeof(urunler)); //Her eleman ekledi�imde dizi artt�rmak i�in malloc realloc kulland�m.
	system("cls");
	system("color d");
	FILE *dosya;
	FILE *f;
	if((dosya=fopen("m��teriler.dat","r"))==NULL)
	{
		printf("Dosya a��lamad�!\n");
	}
	int i=0;
	while(fread(&dizi[i],sizeof(musteriler),1,dosya)==1) //Sat�� i�leminde kullanmak i�in diziye alma i�lemleri
	{
		i++;
		dizi=(musteriler *)realloc(dizi,(i+1)*sizeof(musteriler));
		fflush(stdin);
	}
	fclose(dosya);
	fflush(stdin);	
	
	if((f=fopen("�r�nler.dat","r"))==NULL)
	{
		printf("Dosya a��lamad�!\n");
	}
	int x=0;
	while(fread(&urun[x],sizeof(urunler),1,f)==1)
	{
		x++;
		urun=(urunler *)realloc(urun,(x+1)*sizeof(urunler));
		fflush(stdin);		
	}
	fclose(f);
	
	satis(dizi,urun,i,x); //sat�� fonksiyonu.
			
	int j;
	if((dosya=fopen("m��teriler.dat","w"))==NULL) //Sat�� i�leminden sonra dosyay yazma i�lemleri.
	{
		printf("Dosya a��lamad�!\n");
	}
	for(j=0;j<i;j++)
	{
		fwrite(&dizi[j],sizeof(musteriler),1,dosya);
		fflush(stdin);
	}
	fclose(dosya);
	fflush(stdin);
	
	if((f=fopen("�r�nler.dat","w"))==NULL)
	{
	printf("Dosya a��lamad�!\n");
	}
	for(j=0;j<x;j++)
	{
		fwrite(&urun[j],sizeof(urunler),1,f);
		fflush(stdin);
	}
	fclose(f);
	fflush(stdin);
}
int main()
{
	setlocale(LC_ALL, "Turkish"); 
	int secim;
	while(1) //men�.
	{	
		system("COLOR e"); // G�z yormamas� ve anla��l�rl��� artt�rmak i�in temizleme ve renk de�i�tirme kulland�m.
		system("cls");
		fflush(stdin);
		printf("*****ANA MEN�*****\n\n");
		printf("M��teri men�s� i�in => 1\n");
		printf("�r�n men�s� i�in => 2\n");
		printf("Al��veri� men�s� i�in =>3\n");
		printf("��kmak i�in => 0\n");
		scanf("%d",&secim);
		fflush(stdin);
		if(secim==0)
		{
			break;
		}
		if(secim==1)
		{
			musterimenu();
		}
		if(secim==2)
		{
			urunmenu();
		}
		if(secim==3) //sat�� men�s�.
		{
			satismenu();
		}
	}	
}
//kaynaklar
//https://www.yusufsezer.com.tr/c-dosya-islemleri/
//https://www.dijitalders.com/icerik/106/5468/c_programlamada_string_islemleri.html
//https://www.daniweb.com/programming/software-development/threads/100744/system
//http://sharpsharp.blogcu.com/c-dili-ve-scanf-sorunu/1967218
