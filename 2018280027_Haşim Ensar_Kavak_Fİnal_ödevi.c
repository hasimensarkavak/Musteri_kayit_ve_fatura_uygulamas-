#include<stdio.h>
#include <stdlib.h>
#include<locale.h>
#include <string.h> 

//Haþim Ensar KAVAK 2018280027

typedef struct //müþteriler için struct
{
	int hspno;
	char ad[20];
	char soyad[20];
	char tel[11];
	char adres[100];
	int bakiye;
}musteriler;


typedef struct //ürünler için struct
{
	int urunkod;
	char urunad[20];
	int fiyat;
	int stok;
}urunler;

// ürünler menüsü için olan fonksiyonlar
void urundosya() //Kayýtlarý sýfýrlama ve oluþturmak için.
{
	FILE *dosya;
	if((dosya=fopen("ürünler.dat","w"))==NULL)
	{
		printf("Dosya açýlamadý!\n");
	}
	fclose(dosya);
}

void urunekleme() //ürün ekleme fonksiyonu.
{
	urunler urun; //struct bir deðiþkene girdi alýp bunu dosyaya atýyoruz.
	FILE *dosya;
	if((dosya=fopen("ürünler.dat","a"))==NULL)
	{
		printf("Dosya açýlamadý!\n");
	}
	int secim=1;
	while(secim==1)  
	{
		fflush(stdin);
		printf("\nÜrün kodunu giriniz. (1-1000 arasý)\n"); 
		scanf("%d",&urun.urunkod);
		fflush(stdin);
		printf("Ürünün adýný giriniz. (max 20 karakter)\n");
		scanf("%s",&urun.urunad);
		fflush(stdin);
		printf("Ürünün fiyatýný giriniz.\n");
		scanf("%d",&urun.fiyat);
		fflush(stdin);
		printf("Ürünün stok miktarýný giriniz.\n");
		scanf("%d",&urun.stok);
		fflush(stdin);
		
		fwrite(&urun,sizeof(urun),1,dosya);
	
		printf("Ürün kayýtlarýna devam etmek için => 1\n");
		printf("Ana menüye dönmek için => 0\n\n");
		scanf("%d",&secim);
		fflush(stdin);
		if(secim==0)
		{
			break;
		}
	}
	fclose(dosya);
}


void tumurunler() // tüm ürünleri ekrana yazdýrmak için olan fonksiyon.
{
	urunler urun; // yine struct bir deðiþkenle yapýyoruz.
	FILE *dosya;
	if((dosya=fopen("ürünler.dat","r"))==NULL)
	{
		printf("Dosya açýlamadý!\n");
	}
	int sayac=0;
	while(fread(&urun,sizeof(urun),1,dosya)==1) // her dosyadan okuduðumuzda ekrana yazdýrýyoruz.
	{
		sayac++;
		printf("%d -)\n",sayac);
		printf("Ürün Kodu : %d\n",urun.urunkod);
		printf("Ürün Adý : %s\n",urun.urunad);
		printf("Ürün Fiyatý : %d\n",urun.fiyat);
		printf("Ürün Stok Miktarý : %d\n\n",urun.stok);
	}
	fflush(stdin); 
	fclose(dosya);
}


void urunarama() //ürün arama fonksiyonu.
{
	urunler urun;
	FILE *dosya;
	if((dosya=fopen("ürünler.dat","r"))==NULL)
	{
		printf("Dosya açýlamadý!\n");
	}
	int secim;
	do
	{
	printf("Ürün koduna göre arama yapmak için => 1\n");
	printf("Ýsime göre arama yapmak için => 2\n");
	scanf("%d",&secim);
	fflush(stdin); 
	if(secim==1)
	{
		int aranan;  //Aradýðýmýz ürün kodunu tutan deðiþken.
		printf("Görüntülemek istediðiniz ürünün ürün kodunu giriniz.\n");
		scanf("%d",&aranan);
		fflush(stdin); 
		while(fread(&urun,sizeof(urun),1,dosya)==1)
		{
			if(aranan==urun.urunkod)
			{
				printf("Ürün Kodu : %d\n",urun.urunkod);
				printf("Ürün Adý : %s\n",urun.urunad);
				printf("Ürün Fiyatý : %d\n",urun.fiyat);
				printf("Stok Miktarý : %d\n\n",urun.stok);
				break;
			}
		}
		if(aranan!=urun.urunkod) //hata mesajý.
		{
			printf("Aradýðýnýz ürün kodunda ürün bulunamadý!!!\n");
		}
	}
	if(secim==2)
	{
		char ara[]="";   //Aradýðýmýz harf hece veya ismi tutan deðiþken.
		printf("Görüntülemek istediðiniz ürünün ismini giriniz.(Ýsminin içinde geçen harf  veya heceye göre de aranýr.)\n");
		scanf("%s",&ara);
		fflush(stdin); 
		while(fread(&urun,sizeof(urun),1,dosya)==1)
		{
			
			if(strstr(urun.urunad,ara)!=NULL)
			{
				printf("Ürün Kodu : %d\n",urun.urunkod);
				printf("Ürün Adý : %s\n",urun.urunad);
				printf("Ürün Fiyatý : %d\n",urun.fiyat);
				printf("Stok Miktarý : %d\n\n",urun.stok);
			}
		}
	}
	printf("\nKayýt görüntülemeye devam etmek için => 1\n");
	printf("Ana menüye dönmek için => 0\n\n");
	scanf("%d",&secim);
	fflush(stdin); 
	}while(secim==1);
	
	fclose(dosya);
}


void urunguncelleme() //Ürün güncelleme fonksiyonu.
{
	urunler *urun=(urunler*)malloc(1*sizeof(urunler)); //ürünler için dizi tanýmladým.
	fflush(stdin);
	FILE *dosya;
	if((dosya=fopen("ürünler.dat","r"))==NULL)
	{
		printf("Dosya açýlamadý!\n");
	}
	int i=0;
	while(fread(&urun[i],sizeof(urunler),1,dosya)==1) //Ürün güncellemesi yapmak için tüm  ürünleri diziye alýyorum.
	{
		i++;
		urun=(urunler *)realloc(urun,(i+1)*sizeof(urunler)); //Her ürün aldýðýmda dizi boyutunu arttýrýyorum.	
	}
	fclose(dosya);
	int secim=2,aranan,j;
	while(1)
	{
		go:
		printf("Güncellemek istediðin ürünün ürün kodunu giriniz. (Ürün kodunu bilmiyorsanýz Ana Menüye gidip Ürün Görüntüleme ekranýndan öðreniniz!!!\nAna menü için => 0)\n");
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
			printf("Bu ürün kodunda kayýt bulunamadý!!!\n\n");
			printf("Baþka ürün kodu girmek için => 1\n");
			printf("Ana menüye dönmek için => 0\n");
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
		printf("Ürünün fiyatýný güncellemek için => 1\n");
		printf("Ürünün stok miktarýný güncellemek için => 2\n");
		printf("Bir önceki menüye dönmek için => 0\n");
		scanf("%d",&secim);
		fflush(stdin);
		switch(secim)
		{
			case 0:
				goto go;
				break;
			case 1:
				printf("Yeni ürün fiyatýný giriniz.\n");
				scanf("%d",&urun[j].fiyat);				// Ürün deðiþikliðini dizi üzerinde yapýyorum.
				fflush(stdin);
				break;
			case 2:
				printf("Yeni ürün stok miktarýný giriniz.\n");
				scanf("%d",&urun[j].stok);
				fflush(stdin);
				break;
		}
		printf("Baþka bir ürünü güncellemek için => 1\n");
		printf("Ana menüye dönmek için => 0\n");
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
	if((dosya=fopen("ürünler.dat","w"))==NULL)  //Diziyi tekrar dosyaya yazdýrýyorum. Deðiþmiþ verilerde böylece yazýlmýþ oluyor.
	{
		printf("Dosya açýlamadý!\n");
	}
	for(j=0;j<i;j++)
	{
		fwrite(&urun[j],sizeof(urunler),1,dosya);
	}
	fclose(dosya);
	fflush(stdin);
}

//Müþteriler menüsü için olan fonksiyonlar.

void kytdosya() //Müþteri dosyasýný sýfýrlamak ve oluþturmak için.
{
	FILE *dosya;
	if((dosya=fopen("müþteriler.dat","w"))==NULL)
	{
		printf("Dosya açýlamadý!\n");
	}
	fclose(dosya);
}


void kytekleme() //Müþteri ekleme fonksiyonu.
{
	musteriler musteri;
	FILE *dosya;
	if((dosya=fopen("müþteriler.dat","a"))==NULL)
	{
		printf("Dosya açýlamadý!\n");
	}
	int secim=1;
	while(secim==1)  
	{
		fflush(stdin);
		printf("\nMüþterinin hesap numarasýný giriniz. (1-1000 arasý)\n"); // belli bir sýnýr olmasýný istediðim için . int aralýðýndan büyük sayý girmesinler diye.
		scanf("%d",&musteri.hspno);
		fflush(stdin);
		printf("Müþterinin adýný giriniz. (max 20 karakter)\n");
		scanf("%s",&musteri.ad);
		fflush(stdin);
		printf("Müþterinin soyadýný giriniz. (max 20 karakter)\n");
		scanf("%s",&musteri.soyad);
		fflush(stdin);
		printf("Müþterinin telefon numarasýný giriniz. (baþýnda '0' olmadan)\n");
		scanf("%s",&musteri.tel);
		fflush(stdin);
		printf("Müþterinin adres bilgisini giriniz. (max 100 karakter)\n");
		gets(musteri.adres); //Adresi gets ile aldým çünkü scnaf ile boþluktan sonra yazýlanlarý alamýyoruz.
		fflush(stdin);
		printf("Müþterinin bakiyesini giriniz.\n");
		scanf("%d",&musteri.bakiye);
		fflush(stdin);
		
		fwrite(&musteri,sizeof(musteri),1,dosya);
	
		printf("Müþteri kayýtlarýna devam etmek için => 1\n");
		printf("Ana menüye dönmek için => 0\n\n");
		scanf("%d",&secim);
		fflush(stdin);
		if(secim==0)
		{
			break;
		}
	}
	fclose(dosya);
}


void tummusteriler() //Tüm müþterileri ekrana yazdýrma fonksiyonu.
{
	musteriler musteri;
	FILE *dosya;
	if((dosya=fopen("müþteriler.dat","r"))==NULL)
	{
		printf("Dosya açýlamadý!\n");
	}
	int sayac=0;
	while(fread(&musteri,sizeof(musteriler),1,dosya)==1)
	{
		sayac++;
		printf("%d -)  Müþterinin:\n",sayac);
		printf("Hesap No : %d\n",musteri.hspno);
		printf("Adý : %s\n",musteri.ad);
		printf("Soyadý : %s\n",musteri.soyad);
		printf("Telefon No : %s\n",musteri.tel);
		printf("Adres : ");
		puts(musteri.adres); 
		printf("Bakiye : %d\n\n",musteri.bakiye);
	}
	fflush(stdin); 
	fclose(dosya);
}


void arama() //Müþteri arama fonksiyonu.
{
	musteriler musteri;
	FILE *dosya;
	if((dosya=fopen("müþteriler.dat","r"))==NULL)
	{
		printf("Dosya açýlamadý!\n");
	}
	int secim;
	do
	{
	printf("Müþteri hesap numarasýna göre arama yapmak için => 1\n");
	printf("Ýsime göre arama yapmak için => 2\n");
	scanf("%d",&secim);
	fflush(stdin); 
	if(secim==1)
	{
		int aranan;
		printf("Görüntülemek istediðiniz müþterinin hesap numarasýný giriniz.\n");
		scanf("%d",&aranan);
		fflush(stdin); 
		while(fread(&musteri,sizeof(musteri),1,dosya)==1)
		{
			if(aranan==musteri.hspno)
			{
				printf("Hesap No : %d\n",musteri.hspno);
				printf("Adý : %s\n",musteri.ad);
				printf("Soyadý : %s\n",musteri.soyad);
				printf("Telefon No : %s\n",musteri.tel);
				printf("Adres : ");
				puts(musteri.adres);
				printf("Bakiye : %d\n\n",musteri.bakiye);
				break;
			}
		}
		if(aranan!=musteri.hspno)
		{
			printf("Aradýðýnýz hesap numarasýnda müþteri bulunamadý!!!\n");
		}
	}
	if(secim==2)
	{
		char ara[]="";
		printf("Görüntülemek istediðiniz müþterinin ismini giriniz.(ad-soyad ikisinde de arama yapýlýr. Ýsminin içinde geçen harf  veya heceye göre de aranýr.)\n");
		scanf("%s",&ara);
		fflush(stdin); 
		while(fread(&musteri,sizeof(musteri),1,dosya)==1)
		{
			
			if(strstr(musteri.ad,ara)!=NULL || strstr(musteri.soyad,ara)!=NULL)
			{
				printf("Hesap No : %d\n",musteri.hspno);
				printf("Adý : %s\n",musteri.ad);
				printf("Soyadý : %s\n",musteri.soyad);
				printf("Telefon No : %s\n",musteri.tel);
				printf("Adres : ");
				puts(musteri.adres);
				printf("Bakiye : %d\n\n",musteri.bakiye);
			}
		}
	}
	printf("\nKayýt görüntülemeye devam etmek için => 1\n");
	printf("Ana menüye dönmek için => 0\n\n");
	scanf("%d",&secim);
	fflush(stdin); 
	}while(secim==1);
	
	fclose(dosya);
}


void guncelleme() //Müþteri verisi güncelleme fonksiyonu.
{
	musteriler *dizi=(musteriler*)malloc(1*sizeof(musteriler)); //müþteriler için dizi tanýmladým. Dizi boyutunu müþterilere göre ayarlamak için 
	fflush(stdin);
	FILE *dosya;
	if((dosya=fopen("müþteriler.dat","r"))==NULL) //Burda da ürünler de olduðu gibi dizi ile yaptým iþlemleri.
	{
		printf("Dosya açýlamadý!\n");
	}
	int i=0,a=1;
	while(fread(&dizi[i],sizeof(musteriler),1,dosya)==1)
	{
		i++;
		dizi=(musteriler *)realloc(dizi,(i+1)*sizeof(musteriler));// Dizi boyutunu müþterilere göre ayarlamak için realloc kullandým.
	}
	fclose(dosya);
	int secim=2,aranan,j;
	while(1)
	{
		go:
		printf("Güncellemek istediðin müþterinin hesap numarasýný giriniz. (Hesap numarasýný bilmiyorsanýz Ana Menüye gidip Müþteri Görüntüleme ekranýndan öðreniniz!!!=> 0)\n");
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
			printf("Bu hesap numarasýnda kayýt bulunamadý!!!\n\n");
			printf("Baþka hesap numarasý girmek için => 1\n");
			printf("Ana menüye dönmek için => 0\n");
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
		printf("Müþterinin telefon numarasýný güncellemek için => 1\n");
		printf("Müþterinin adresini güncellemek için => 2\n");
		printf("Müþterinin bakiyesini güncellemek için => 3 (Bakiyeyi istediðiniz gibi deðiþtirebilirsiniz)\n");
		printf("Müþterinin bakiyesine ekleme yapmak için => 4 (Bakiyeye sadece ekleme yapabilirsiniz)\n");
		printf("Bir önceki menüye dönmek için => 0\n");
		scanf("%d",&secim);
		fflush(stdin);
		switch(secim)
		{
			case 0:
				goto go;
				break;
			case 1:
				printf("Yeni telefon numarasýný giriniz.\n");
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
				printf("Eklemek istediðiniz miktarý yazýnýz.\n");
				scanf("%d",&aranan);  // Yeni bir deðiþken oluþturmak istemediðimden bunu kullandým.
				fflush(stdin);  
				dizi[j].bakiye=dizi[j].bakiye+aranan;
				break;
		}
		printf("Baþka bir müþteriyi güncellemek için => 1\n");
		printf("Ana menüye dönmek için => 0\n");
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
	if((dosya=fopen("müþteriler.dat","w"))==NULL) // Dosyayý w ile açtýðým için deðiþmemiþ ve deðiþmiþ veriler 2. kez yazýlmadý.
	{
		printf("Dosya açýlamadý!\n");
	}
	for(j=0;j<i;j++)
	{
		fwrite(&dizi[j],sizeof(musteriler),1,dosya); //Deðiþmiþ verilerle birlikte dosyayý yeniden yazýyoruz.
	}
	fclose(dosya);
	fflush(stdin); 
}

// Satýþ fonksiyonu.

void satis(musteriler *musteri,urunler *urun,int meleman,int ueleman) //Dizileri satismenu fonksiyonu içinde doldurdum. dizilerin eleman sayýsýný da aldým.
{
	int alici,j,secim,y,z,ukod,adet,toplam=0;
	char da[]=""; 
	fflush(stdin);
	FILE *fp;
	while(1)
	{
		basla:
		fflush(stdin);
		printf("Alýcýnýn hesap numarasýný giriniz.\n");
		printf("Ana Menüye dönmek için => 0\n");
		scanf("%d",&alici);
		fflush(stdin);
		if(alici==0)
		{
			break;
		}
		for(j=0;j<=meleman;j++)
		{
			fflush(stdin);
			if(alici==musteri[j].hspno) //istenen müþteriyi hesap numarasýný karþýlaþtýrarak dizide arýyoruz.
			{
				printf("Müþteri bulundu.\n");
				fflush(stdin);
				y=j;
				break;
			}
		}
		fflush(stdin);
		if(alici!=musteri[j].hspno) //bulunamazsa çalýþan if.
		{
			printf("Müþteri bulunamadý!!!\n");
			printf("Baþka hesap numarasý girmek için => 1\n");
			printf("Ana menüye dönmek için => 0\n");
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
		if((fp=fopen(da,"w"))==NULL) //faturaya müþteri bilgilerini yazdýrýyoruz.
		{
			printf("Dosya açýlamadý!\n");
		}
		fprintf(fp,"**********Fatura***********\n");
		fprintf(fp,"Müþterinin Hesap No: %d\n",musteri[y].hspno);
		fprintf(fp,"Müþterinin Adý: %s\n",musteri[y].ad);
		fprintf(fp,"Müþterinin Soyadý: %s\n",musteri[y].soyad);
		fprintf(fp,"Müþterinin Telefon No: %s\n",musteri[y].tel);
		fprintf(fp,"Müþterinin Adresi: %s\n",musteri[y].adres);
		fprintf(fp,"**************************\n");
		fprintf(fp,"********Alýnan Ürünler*******\n\n");
		fprintf(fp,"Ürün Kodu		Adý	Adet	Birim Fiyatý\n");
		fflush(stdin);
		tumu:
		system("cls");
		system("color a");
		tumurunler();// Tüm ürünleri listeliyoruz ki hangi ürünün alýndýðýný daha kolay bulsun.
		tekrar:
		printf("Satýn alýnan ürünün ürün kodunu giriniz. (Her seferinde 1 ürün kodu giriniz. Alýþveriþi tamamlamak için => 0)\n");
		scanf("%d",&ukod);
		fflush(stdin);
		if(ukod==0)
		{
			goto fatura;
		}
		for(j=0;j<ueleman;j++)
		{
			fflush(stdin);
			if(ukod==urun[j].urunkod) //ürün dizisinde arýyoruz.
			{
				z=j;
				fflush(stdin);
				break;
			}
		}
		fflush(stdin);
		if(ukod!=urun[z].urunkod) //ürün kodu yanlýþ girilirse.
		{
			printf("Ürün bulunamadý!!!\n");
			printf("Baþka ürün kodu girmek için => 1\n");
			printf("Tüm ürünleri tekrar görmek için => 2\n");
			printf("Menüye dönmek için => 0\n");
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
		if(urun[z].stok<adet) //Yeterli stok olup olmadýðýný kontrol ediyoruz.
		{
			printf("Stok miktarýndan fazla giriþ yaptýnýz lütfen tekrar giriniz.\n");
			goto adet;
		}
		if(adet<=0)
		{
			printf("0 veya daha küçük bir deðer girdiniz lütfen tekrar giriniz.\n");
			goto adet;
		}
		urun[z].stok=urun[z].stok-adet; // stoktan düþüyoruz.
		toplam=toplam+(urun[z].fiyat*adet); //toplam ödenecek tutarý tutuyoruz.
		fflush(stdin);
		fprintf(fp,"%d		%s	X %d	%dTL\n",urun[z].urunkod,urun[z].urunad,adet,urun[z].fiyat); //alýnan her ürün için faturada bilgilendirme.
		fflush(stdin);
		goto tekrar; // kullanýcý 0 girene kadar ürün alýmýna devam edebilmesi için.
		fatura:
		if(musteri[y].bakiye<toplam) //Bakiye yeterlimi diye kontrol.
		{
			FILE *f;
			if((f=fopen("ürünler.dat","r"))==NULL)
			{
				printf("Dosya açýlamadý!\n");
			}
			int x=0;
			while(fread(&urun[x],sizeof(urunler),1,f)==1) //Bakiye yetersizse ürünlerin stoklarýnda yaptýðýmýz deðiþikliði geri almak için tekrar okuduk.
			{
				x++;
				fflush(stdin);
			}
			fclose(f);
			printf("YETERSÝZ BAKÝYE!!!\n");
			printf("Yeniden denemek için => 1\n");
			printf("Ýptal etmek için => 0\n");
			scanf("%d",&secim);
			fflush(stdin);
			switch(secim)
			{
				case 0:
					fprintf(fp,"\n!!!ÝÞLEM ÝPTAL EDÝLMÝÞTÝR DOSYAYI SÝLEBÝLÝRSÝNÝZ!!!!\n");//remove fonksiyonu çalýþmadý nedeni ni bulamadým o yüzden böyle yaptým.
					fclose(fp);
					printf("Ýþlem iptal edilmiþtir...\nFatura dosyasýný silebilirsiniz.\n");
					break;
				case 1:
					fclose(fp);
					toplam=0; //ürünleri baþtan seçecekse toplam deðerini sýfýrlýyoruz.
					goto basla;
					break;
			}
		}
		if(musteri[y].bakiye>toplam) //bakiye yeterliyse.
		{
			fflush(stdin);
			musteri[y].bakiye=musteri[y].bakiye-toplam; //müþterinin bakiyesinden düþüyoruz.
			fprintf(fp,"Toplam Tutar = %dTL\n\n",toplam);
			fprintf(fp,"Yeni Müþteri Bakiyesi = %dTL",musteri[y].bakiye);
			fclose(fp);						 // fatura dosyasý hazýr.
			printf("Alýþveriþ Tamamlandý.\n");
			printf("Faturanýz hazýr...\n");
			printf("Yeni alýþveriþ için => 1\n");
			printf("Ana menüye dönmek için => 0\n");
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
		while(1) //müþteri menüsü.
			{
				system("cls");
				system("color f");
				printf("Müþteri kayýt dosyasýný sýfýrlamak için yada dosya yoksa oluþturmak için => 1 (NOT:Eski kayýt silinir)\n");
				printf("Yeni müþteri eklemek için => 2\n");
				printf("Müþteri kaydý güncelleme için => 3\n");
				printf("Müþteri kaydý görüntüleme için => 4\n");
				printf("Ana menüye dönmek için => 0\n");
				scanf("%d",&secim);
				fflush(stdin); // Bellekte tampon görevi gören bir fonksiyonmuþ. Bazý problemlerin önüne geçti. (scanf vs.)
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
					printf("Tüm müþterileri görüntülemek için => 1\n");
					printf("Arama yapmak için => 2\n");
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
	while(1) //ürün menüsü
			{
				system("cls");
				system("color c");
				printf("Ürün kayýt dosyasýný sýfýrlamak için yada dosya yoksa oluþturmak için => 1 (NOT:Eski kayýt silinir)\n");
				printf("Yeni ürün eklemek için => 2\n");
				printf("Ürün kaydý güncelleme için => 3\n");
				printf("Ürün kaydý görüntüleme için => 4\n");
				printf("Ana menüye dönmek için => 0\n");
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
					printf("Tüm ürünleri görüntülemek için => 1\n");
					printf("Arama yapmak için => 2\n");
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
	musteriler *dizi=(musteriler*)malloc(1*sizeof(musteriler)); //müþteriler ve ürünler için dizi tanýmladým. 
	urunler *urun=(urunler*)malloc(1*sizeof(urunler)); //Her eleman eklediðimde dizi arttýrmak için malloc realloc kullandým.
	system("cls");
	system("color d");
	FILE *dosya;
	FILE *f;
	if((dosya=fopen("müþteriler.dat","r"))==NULL)
	{
		printf("Dosya açýlamadý!\n");
	}
	int i=0;
	while(fread(&dizi[i],sizeof(musteriler),1,dosya)==1) //Satýþ iþleminde kullanmak için diziye alma iþlemleri
	{
		i++;
		dizi=(musteriler *)realloc(dizi,(i+1)*sizeof(musteriler));
		fflush(stdin);
	}
	fclose(dosya);
	fflush(stdin);	
	
	if((f=fopen("ürünler.dat","r"))==NULL)
	{
		printf("Dosya açýlamadý!\n");
	}
	int x=0;
	while(fread(&urun[x],sizeof(urunler),1,f)==1)
	{
		x++;
		urun=(urunler *)realloc(urun,(x+1)*sizeof(urunler));
		fflush(stdin);		
	}
	fclose(f);
	
	satis(dizi,urun,i,x); //satýþ fonksiyonu.
			
	int j;
	if((dosya=fopen("müþteriler.dat","w"))==NULL) //Satýþ iþleminden sonra dosyay yazma iþlemleri.
	{
		printf("Dosya açýlamadý!\n");
	}
	for(j=0;j<i;j++)
	{
		fwrite(&dizi[j],sizeof(musteriler),1,dosya);
		fflush(stdin);
	}
	fclose(dosya);
	fflush(stdin);
	
	if((f=fopen("ürünler.dat","w"))==NULL)
	{
	printf("Dosya açýlamadý!\n");
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
	while(1) //menü.
	{	
		system("COLOR e"); // Göz yormamasý ve anlaþýlýrlýðý arttýrmak için temizleme ve renk deðiþtirme kullandým.
		system("cls");
		fflush(stdin);
		printf("*****ANA MENÜ*****\n\n");
		printf("Müþteri menüsü için => 1\n");
		printf("Ürün menüsü için => 2\n");
		printf("Alýþveriþ menüsü için =>3\n");
		printf("Çýkmak için => 0\n");
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
		if(secim==3) //satýþ menüsü.
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
