#include<stdio.h>
#include <stdlib.h>
#include<locale.h>
#include <string.h> 



typedef struct //müşteriler için struct
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
void urundosya() //Kayıtları sıfırlama ve oluşturmak için.
{
	FILE *dosya;
	if((dosya=fopen("ürünler.dat","w"))==NULL)
	{
		printf("Dosya açılamadı!\n");
	}
	fclose(dosya);
}

void urunekleme() //ürün ekleme fonksiyonu.
{
	urunler urun; //struct bir değişkene girdi alıp bunu dosyaya atıyoruz.
	FILE *dosya;
	if((dosya=fopen("ürünler.dat","a"))==NULL)
	{
		printf("Dosya açılamadı!\n");
	}
	int secim=1;
	while(secim==1)  
	{
		fflush(stdin);
		printf("\nÜrün kodunu giriniz. (1-1000 arası)\n"); 
		scanf("%d",&urun.urunkod);
		fflush(stdin);
		printf("Ürünün adını giriniz. (max 20 karakter)\n");
		scanf("%s",&urun.urunad);
		fflush(stdin);
		printf("Ürünün fiyatını giriniz.\n");
		scanf("%d",&urun.fiyat);
		fflush(stdin);
		printf("Ürünün stok miktarını giriniz.\n");
		scanf("%d",&urun.stok);
		fflush(stdin);
		
		fwrite(&urun,sizeof(urun),1,dosya);
	
		printf("Ürün kayıtlarına devam etmek için => 1\n");
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


void tumurunler() // tüm ürünleri ekrana yazdırmak için olan fonksiyon.
{
	urunler urun; // yine struct bir değişkenle yapıyoruz.
	FILE *dosya;
	if((dosya=fopen("ürünler.dat","r"))==NULL)
	{
		printf("Dosya açılamadı!\n");
	}
	int sayac=0;
	while(fread(&urun,sizeof(urun),1,dosya)==1) // her dosyadan okuduğumuzda ekrana yazdırıyoruz.
	{
		sayac++;
		printf("%d -)\n",sayac);
		printf("Ürün Kodu : %d\n",urun.urunkod);
		printf("Ürün Adı : %s\n",urun.urunad);
		printf("Ürün Fiyatı : %d\n",urun.fiyat);
		printf("Ürün Stok Miktarı : %d\n\n",urun.stok);
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
		printf("Dosya açılamadı!\n");
	}
	int secim;
	do
	{
	printf("Ürün koduna göre arama yapmak için => 1\n");
	printf("İsime göre arama yapmak için => 2\n");
	scanf("%d",&secim);
	fflush(stdin); 
	if(secim==1)
	{
		int aranan;  //Aradığımız ürün kodunu tutan değişken.
		printf("Görüntülemek istediğiniz ürünün ürün kodunu giriniz.\n");
		scanf("%d",&aranan);
		fflush(stdin); 
		while(fread(&urun,sizeof(urun),1,dosya)==1)
		{
			if(aranan==urun.urunkod)
			{
				printf("Ürün Kodu : %d\n",urun.urunkod);
				printf("Ürün Adı : %s\n",urun.urunad);
				printf("Ürün Fiyatı : %d\n",urun.fiyat);
				printf("Stok Miktarı : %d\n\n",urun.stok);
				break;
			}
		}
		if(aranan!=urun.urunkod) //hata mesajı.
		{
			printf("Aradığınız ürün kodunda ürün bulunamadı!!!\n");
		}
	}
	if(secim==2)
	{
		char ara[]="";   //Aradığımız harf hece veya ismi tutan değişken.
		printf("Görüntülemek istediğiniz ürünün ismini giriniz.(İsminin içinde geçen harf  veya heceye göre de aranır.)\n");
		scanf("%s",&ara);
		fflush(stdin); 
		while(fread(&urun,sizeof(urun),1,dosya)==1)
		{
			
			if(strstr(urun.urunad,ara)!=NULL)
			{
				printf("Ürün Kodu : %d\n",urun.urunkod);
				printf("Ürün Adı : %s\n",urun.urunad);
				printf("Ürün Fiyatı : %d\n",urun.fiyat);
				printf("Stok Miktarı : %d\n\n",urun.stok);
			}
		}
	}
	printf("\nKayıt görüntülemeye devam etmek için => 1\n");
	printf("Ana menüye dönmek için => 0\n\n");
	scanf("%d",&secim);
	fflush(stdin); 
	}while(secim==1);
	
	fclose(dosya);
}


void urunguncelleme() //Ürün güncelleme fonksiyonu.
{
	urunler *urun=(urunler*)malloc(1*sizeof(urunler)); //ürünler için dizi tanımladım.
	fflush(stdin);
	FILE *dosya;
	if((dosya=fopen("ürünler.dat","r"))==NULL)
	{
		printf("Dosya açılamadı!\n");
	}
	int i=0;
	while(fread(&urun[i],sizeof(urunler),1,dosya)==1) //Ürün güncellemesi yapmak için tüm  ürünleri diziye alıyorum.
	{
		i++;
		urun=(urunler *)realloc(urun,(i+1)*sizeof(urunler)); //Her ürün aldığımda dizi boyutunu arttırıyorum.	
	}
	fclose(dosya);
	int secim=2,aranan,j;
	while(1)
	{
		go:
		printf("Güncellemek istediğin ürünün ürün kodunu giriniz. (Ürün kodunu bilmiyorsanız Ana Menüye gidip Ürün Görüntüleme ekranından öğreniniz!!!\nAna menü için => 0)\n");
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
			printf("Bu ürün kodunda kayıt bulunamadı!!!\n\n");
			printf("Başka ürün kodu girmek için => 1\n");
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
		printf("Ürünün fiyatını güncellemek için => 1\n");
		printf("Ürünün stok miktarını güncellemek için => 2\n");
		printf("Bir önceki menüye dönmek için => 0\n");
		scanf("%d",&secim);
		fflush(stdin);
		switch(secim)
		{
			case 0:
				goto go;
				break;
			case 1:
				printf("Yeni ürün fiyatını giriniz.\n");
				scanf("%d",&urun[j].fiyat);				// Ürün değişikliğini dizi üzerinde yapıyorum.
				fflush(stdin);
				break;
			case 2:
				printf("Yeni ürün stok miktarını giriniz.\n");
				scanf("%d",&urun[j].stok);
				fflush(stdin);
				break;
		}
		printf("Başka bir ürünü güncellemek için => 1\n");
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
	if((dosya=fopen("ürünler.dat","w"))==NULL)  //Diziyi tekrar dosyaya yazdırıyorum. Değişmiş verilerde böylece yazılmış oluyor.
	{
		printf("Dosya açılamadı!\n");
	}
	for(j=0;j<i;j++)
	{
		fwrite(&urun[j],sizeof(urunler),1,dosya);
	}
	fclose(dosya);
	fflush(stdin);
}

//Müşteriler menüsü için olan fonksiyonlar.

void kytdosya() //Müşteri dosyasını sıfırlamak ve oluşturmak için.
{
	FILE *dosya;
	if((dosya=fopen("müşteriler.dat","w"))==NULL)
	{
		printf("Dosya açılamadı!\n");
	}
	fclose(dosya);
}


void kytekleme() //Müşteri ekleme fonksiyonu.
{
	musteriler musteri;
	FILE *dosya;
	if((dosya=fopen("müşteriler.dat","a"))==NULL)
	{
		printf("Dosya açılamadı!\n");
	}
	int secim=1;
	while(secim==1)  
	{
		fflush(stdin);
		printf("\nMüşterinin hesap numarasını giriniz. (1-1000 arası)\n"); // belli bir sınır olmasını istediğim için . int aralığından büyük sayı girmesinler diye.
		scanf("%d",&musteri.hspno);
		fflush(stdin);
		printf("Müşterinin adını giriniz. (max 20 karakter)\n");
		scanf("%s",&musteri.ad);
		fflush(stdin);
		printf("Müşterinin soyadını giriniz. (max 20 karakter)\n");
		scanf("%s",&musteri.soyad);
		fflush(stdin);
		printf("Müşterinin telefon numarasını giriniz. (başında '0' olmadan)\n");
		scanf("%s",&musteri.tel);
		fflush(stdin);
		printf("Müşterinin adres bilgisini giriniz. (max 100 karakter)\n");
		gets(musteri.adres); //Adresi gets ile aldım çünkü scnaf ile boşluktan sonra yazılanları alamıyoruz.
		fflush(stdin);
		printf("Müşterinin bakiyesini giriniz.\n");
		scanf("%d",&musteri.bakiye);
		fflush(stdin);
		
		fwrite(&musteri,sizeof(musteri),1,dosya);
	
		printf("Müşteri kayıtlarına devam etmek için => 1\n");
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


void tummusteriler() //Tüm müşterileri ekrana yazdırma fonksiyonu.
{
	musteriler musteri;
	FILE *dosya;
	if((dosya=fopen("müşteriler.dat","r"))==NULL)
	{
		printf("Dosya açılamadı!\n");
	}
	int sayac=0;
	while(fread(&musteri,sizeof(musteriler),1,dosya)==1)
	{
		sayac++;
		printf("%d -)  Müşterinin:\n",sayac);
		printf("Hesap No : %d\n",musteri.hspno);
		printf("Adı : %s\n",musteri.ad);
		printf("Soyadı : %s\n",musteri.soyad);
		printf("Telefon No : %s\n",musteri.tel);
		printf("Adres : ");
		puts(musteri.adres); 
		printf("Bakiye : %d\n\n",musteri.bakiye);
	}
	fflush(stdin); 
	fclose(dosya);
}


void arama() //Müşteri arama fonksiyonu.
{
	musteriler musteri;
	FILE *dosya;
	if((dosya=fopen("müşteriler.dat","r"))==NULL)
	{
		printf("Dosya açılamadı!\n");
	}
	int secim;
	do
	{
	printf("Müşteri hesap numarasına göre arama yapmak için => 1\n");
	printf("İsime göre arama yapmak için => 2\n");
	scanf("%d",&secim);
	fflush(stdin); 
	if(secim==1)
	{
		int aranan;
		printf("Görüntülemek istediğiniz müşterinin hesap numarasını giriniz.\n");
		scanf("%d",&aranan);
		fflush(stdin); 
		while(fread(&musteri,sizeof(musteri),1,dosya)==1)
		{
			if(aranan==musteri.hspno)
			{
				printf("Hesap No : %d\n",musteri.hspno);
				printf("Adı : %s\n",musteri.ad);
				printf("Soyadı : %s\n",musteri.soyad);
				printf("Telefon No : %s\n",musteri.tel);
				printf("Adres : ");
				puts(musteri.adres);
				printf("Bakiye : %d\n\n",musteri.bakiye);
				break;
			}
		}
		if(aranan!=musteri.hspno)
		{
			printf("Aradığınız hesap numarasında müşteri bulunamadı!!!\n");
		}
	}
	if(secim==2)
	{
		char ara[]="";
		printf("Görüntülemek istediğiniz müşterinin ismini giriniz.(ad-soyad ikisinde de arama yapılır. İsminin içinde geçen harf  veya heceye göre de aranır.)\n");
		scanf("%s",&ara);
		fflush(stdin); 
		while(fread(&musteri,sizeof(musteri),1,dosya)==1)
		{
			
			if(strstr(musteri.ad,ara)!=NULL || strstr(musteri.soyad,ara)!=NULL)
			{
				printf("Hesap No : %d\n",musteri.hspno);
				printf("Adı : %s\n",musteri.ad);
				printf("Soyadı : %s\n",musteri.soyad);
				printf("Telefon No : %s\n",musteri.tel);
				printf("Adres : ");
				puts(musteri.adres);
				printf("Bakiye : %d\n\n",musteri.bakiye);
			}
		}
	}
	printf("\nKayıt görüntülemeye devam etmek için => 1\n");
	printf("Ana menüye dönmek için => 0\n\n");
	scanf("%d",&secim);
	fflush(stdin); 
	}while(secim==1);
	
	fclose(dosya);
}


void guncelleme() //Müşteri verisi güncelleme fonksiyonu.
{
	musteriler *dizi=(musteriler*)malloc(1*sizeof(musteriler)); //müşteriler için dizi tanımladım. Dizi boyutunu müşterilere göre ayarlamak için 
	fflush(stdin);
	FILE *dosya;
	if((dosya=fopen("müşteriler.dat","r"))==NULL) //Burda da ürünler de olduğu gibi dizi ile yaptım işlemleri.
	{
		printf("Dosya açılamadı!\n");
	}
	int i=0,a=1;
	while(fread(&dizi[i],sizeof(musteriler),1,dosya)==1)
	{
		i++;
		dizi=(musteriler *)realloc(dizi,(i+1)*sizeof(musteriler));// Dizi boyutunu müşterilere göre ayarlamak için realloc kullandım.
	}
	fclose(dosya);
	int secim=2,aranan,j;
	while(1)
	{
		go:
		printf("Güncellemek istediğin müşterinin hesap numarasını giriniz. (Hesap numarasını bilmiyorsanız Ana Menüye gidip Müşteri Görüntüleme ekranından öğreniniz!!!=> 0)\n");
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
			printf("Bu hesap numarasında kayıt bulunamadı!!!\n\n");
			printf("Başka hesap numarası girmek için => 1\n");
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
		printf("Müşterinin telefon numarasını güncellemek için => 1\n");
		printf("Müşterinin adresini güncellemek için => 2\n");
		printf("Müşterinin bakiyesini güncellemek için => 3 (Bakiyeyi istediğiniz gibi değiştirebilirsiniz)\n");
		printf("Müşterinin bakiyesine ekleme yapmak için => 4 (Bakiyeye sadece ekleme yapabilirsiniz)\n");
		printf("Bir önceki menüye dönmek için => 0\n");
		scanf("%d",&secim);
		fflush(stdin);
		switch(secim)
		{
			case 0:
				goto go;
				break;
			case 1:
				printf("Yeni telefon numarasını giriniz.\n");
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
				printf("Eklemek istediğiniz miktarı yazınız.\n");
				scanf("%d",&aranan);  // Yeni bir değişken oluşturmak istemediğimden bunu kullandım.
				fflush(stdin);  
				dizi[j].bakiye=dizi[j].bakiye+aranan;
				break;
		}
		printf("Başka bir müşteriyi güncellemek için => 1\n");
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
	if((dosya=fopen("müşteriler.dat","w"))==NULL) // Dosyayı w ile açtığım için değişmemiş ve değişmiş veriler 2. kez yazılmadı.
	{
		printf("Dosya açılamadı!\n");
	}
	for(j=0;j<i;j++)
	{
		fwrite(&dizi[j],sizeof(musteriler),1,dosya); //Değişmiş verilerle birlikte dosyayı yeniden yazıyoruz.
	}
	fclose(dosya);
	fflush(stdin); 
}

// Satış fonksiyonu.

void satis(musteriler *musteri,urunler *urun,int meleman,int ueleman) //Dizileri satismenu fonksiyonu içinde doldurdum. dizilerin eleman sayısını da aldım.
{
	int alici,j,secim,y,z,ukod,adet,toplam=0;
	char da[]=""; 
	fflush(stdin);
	FILE *fp;
	while(1)
	{
		basla:
		fflush(stdin);
		printf("Alıcının hesap numarasını giriniz.\n");
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
			if(alici==musteri[j].hspno) //istenen müşteriyi hesap numarasını karşılaştırarak dizide arıyoruz.
			{
				printf("Müşteri bulundu.\n");
				fflush(stdin);
				y=j;
				break;
			}
		}
		fflush(stdin);
		if(alici!=musteri[j].hspno) //bulunamazsa çalışan if.
		{
			printf("Müşteri bulunamadı!!!\n");
			printf("Başka hesap numarası girmek için => 1\n");
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
		if((fp=fopen(da,"w"))==NULL) //faturaya müşteri bilgilerini yazdırıyoruz.
		{
			printf("Dosya açılamadı!\n");
		}
		fprintf(fp,"**********Fatura***********\n");
		fprintf(fp,"Müşterinin Hesap No: %d\n",musteri[y].hspno);
		fprintf(fp,"Müşterinin Adı: %s\n",musteri[y].ad);
		fprintf(fp,"Müşterinin Soyadı: %s\n",musteri[y].soyad);
		fprintf(fp,"Müşterinin Telefon No: %s\n",musteri[y].tel);
		fprintf(fp,"Müşterinin Adresi: %s\n",musteri[y].adres);
		fprintf(fp,"**************************\n");
		fprintf(fp,"********Alınan Ürünler*******\n\n");
		fprintf(fp,"Ürün Kodu		Adı	Adet	Birim Fiyatı\n");
		fflush(stdin);
		tumu:
		system("cls");
		system("color a");
		tumurunler();// Tüm ürünleri listeliyoruz ki hangi ürünün alındığını daha kolay bulsun.
		tekrar:
		printf("Satın alınan ürünün ürün kodunu giriniz. (Her seferinde 1 ürün kodu giriniz. Alışverişi tamamlamak için => 0)\n");
		scanf("%d",&ukod);
		fflush(stdin);
		if(ukod==0)
		{
			goto fatura;
		}
		for(j=0;j<ueleman;j++)
		{
			fflush(stdin);
			if(ukod==urun[j].urunkod) //ürün dizisinde arıyoruz.
			{
				z=j;
				fflush(stdin);
				break;
			}
		}
		fflush(stdin);
		if(ukod!=urun[z].urunkod) //ürün kodu yanlış girilirse.
		{
			printf("Ürün bulunamadı!!!\n");
			printf("Başka ürün kodu girmek için => 1\n");
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
		if(urun[z].stok<adet) //Yeterli stok olup olmadığını kontrol ediyoruz.
		{
			printf("Stok miktarından fazla giriş yaptınız lütfen tekrar giriniz.\n");
			goto adet;
		}
		if(adet<=0)
		{
			printf("0 veya daha küçük bir değer girdiniz lütfen tekrar giriniz.\n");
			goto adet;
		}
		urun[z].stok=urun[z].stok-adet; // stoktan düşüyoruz.
		toplam=toplam+(urun[z].fiyat*adet); //toplam ödenecek tutarı tutuyoruz.
		fflush(stdin);
		fprintf(fp,"%d		%s	X %d	%dTL\n",urun[z].urunkod,urun[z].urunad,adet,urun[z].fiyat); //alınan her ürün için faturada bilgilendirme.
		fflush(stdin);
		goto tekrar; // kullanıcı 0 girene kadar ürün alımına devam edebilmesi için.
		fatura:
		if(musteri[y].bakiye<toplam) //Bakiye yeterlimi diye kontrol.
		{
			FILE *f;
			if((f=fopen("ürünler.dat","r"))==NULL)
			{
				printf("Dosya açılamadı!\n");
			}
			int x=0;
			while(fread(&urun[x],sizeof(urunler),1,f)==1) //Bakiye yetersizse ürünlerin stoklarında yaptığımız değişikliği geri almak için tekrar okuduk.
			{
				x++;
				fflush(stdin);
			}
			fclose(f);
			printf("YETERSİZ BAKİYE!!!\n");
			printf("Yeniden denemek için => 1\n");
			printf("İptal etmek için => 0\n");
			scanf("%d",&secim);
			fflush(stdin);
			switch(secim)
			{
				case 0:
					fprintf(fp,"\n!!!İŞLEM İPTAL EDİLMİŞTİR DOSYAYI SİLEBİLİRSİNİZ!!!!\n");//remove fonksiyonu çalışmadı nedeni ni bulamadım o yüzden böyle yaptım.
					fclose(fp);
					printf("İşlem iptal edilmiştir...\nFatura dosyasını silebilirsiniz.\n");
					break;
				case 1:
					fclose(fp);
					toplam=0; //ürünleri baştan seçecekse toplam değerini sıfırlıyoruz.
					goto basla;
					break;
			}
		}
		if(musteri[y].bakiye>toplam) //bakiye yeterliyse.
		{
			fflush(stdin);
			musteri[y].bakiye=musteri[y].bakiye-toplam; //müşterinin bakiyesinden düşüyoruz.
			fprintf(fp,"Toplam Tutar = %dTL\n\n",toplam);
			fprintf(fp,"Yeni Müşteri Bakiyesi = %dTL",musteri[y].bakiye);
			fclose(fp);						 // fatura dosyası hazır.
			printf("Alışveriş Tamamlandı.\n");
			printf("Faturanız hazır...\n");
			printf("Yeni alışveriş için => 1\n");
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
		while(1) //müşteri menüsü.
			{
				system("cls");
				system("color f");
				printf("Müşteri kayıt dosyasını sıfırlamak için yada dosya yoksa oluşturmak için => 1 (NOT:Eski kayıt silinir)\n");
				printf("Yeni müşteri eklemek için => 2\n");
				printf("Müşteri kaydı güncelleme için => 3\n");
				printf("Müşteri kaydı görüntüleme için => 4\n");
				printf("Ana menüye dönmek için => 0\n");
				scanf("%d",&secim);
				fflush(stdin); // Bellekte tampon görevi gören bir fonksiyonmuş. Bazı problemlerin önüne geçti. (scanf vs.)
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
					printf("Tüm müşterileri görüntülemek için => 1\n");
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
				printf("Ürün kayıt dosyasını sıfırlamak için yada dosya yoksa oluşturmak için => 1 (NOT:Eski kayıt silinir)\n");
				printf("Yeni ürün eklemek için => 2\n");
				printf("Ürün kaydı güncelleme için => 3\n");
				printf("Ürün kaydı görüntüleme için => 4\n");
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
	musteriler *dizi=(musteriler*)malloc(1*sizeof(musteriler)); //müşteriler ve ürünler için dizi tanımladım. 
	urunler *urun=(urunler*)malloc(1*sizeof(urunler)); //Her eleman eklediğimde dizi arttırmak için malloc realloc kullandım.
	system("cls");
	system("color d");
	FILE *dosya;
	FILE *f;
	if((dosya=fopen("müşteriler.dat","r"))==NULL)
	{
		printf("Dosya açılamadı!\n");
	}
	int i=0;
	while(fread(&dizi[i],sizeof(musteriler),1,dosya)==1) //Satış işleminde kullanmak için diziye alma işlemleri
	{
		i++;
		dizi=(musteriler *)realloc(dizi,(i+1)*sizeof(musteriler));
		fflush(stdin);
	}
	fclose(dosya);
	fflush(stdin);	
	
	if((f=fopen("ürünler.dat","r"))==NULL)
	{
		printf("Dosya açılamadı!\n");
	}
	int x=0;
	while(fread(&urun[x],sizeof(urunler),1,f)==1)
	{
		x++;
		urun=(urunler *)realloc(urun,(x+1)*sizeof(urunler));
		fflush(stdin);		
	}
	fclose(f);
	
	satis(dizi,urun,i,x); //satış fonksiyonu.
			
	int j;
	if((dosya=fopen("müşteriler.dat","w"))==NULL) //Satış işleminden sonra dosyay yazma işlemleri.
	{
		printf("Dosya açılamadı!\n");
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
	printf("Dosya açılamadı!\n");
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
		system("COLOR e"); // Göz yormaması ve anlaşılırlığı arttırmak için temizleme ve renk değiştirme kullandım.
		system("cls");
		fflush(stdin);
		printf("*****ANA MENÜ*****\n\n");
		printf("Müşteri menüsü için => 1\n");
		printf("Ürün menüsü için => 2\n");
		printf("Alışveriş menüsü için =>3\n");
		printf("Çıkmak için => 0\n");
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
		if(secim==3) //satış menüsü.
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
