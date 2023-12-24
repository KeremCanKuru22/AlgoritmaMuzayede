#include <stdio.h>
#include <locale.h>
typedef struct {                                                            //Structure'ımızı Oluşturuyoruz.
    char Name[50];
    double InitialBid[100];
    int BidCount;
    double FinalPrice;
}Auction;


double Price(Auction *Product);

void StartAuction(Auction *Product){
    wprintf(L"Açık Artırmayı Sonlandırmak İçin \"-1\" Değerini Giriniz\n");
    double price;
    Product->BidCount=1;
    while(1) {      //Döngü Oluşturuyoruz.
        wprintf(L"Anlık Fiyat: %.2lf\n", Price(Product));   //Anlık Ücreti Gösteriyoruz.
        wprintf(L"Lütfen Artış Miktarını Giriniz:\n");
        if (!scanf("%lf", &price)) {        //Değerin Sayı Olduğunu Kontrol Ediyoruz.
            wprintf(L"Lütfen Sayı Giriniz!\n");
            fflush(stdin);
        }
        if (price == -1) {      //Programı Sonuçlandırmak İçin Değer Atıyoruz.
            wprintf(L"Açık Artırma Sona Erdi\n");
            break;
        } else if (price <= 0) {        //0 dan Küçük Sayı Girişlerini Kontrol Ediyoruz.
            wprintf(L"Sadece 0' dan Büyük Sayılar Girebilirsiniz\n");
        } else {        //
            Product->InitialBid[Product->BidCount] = price;
            ++Product->BidCount;   //Kazanan Teklifi Öğrenmek İçin Teklif Sayısını Hesaplatıyoruz.
        }
    }
}

double Price(Auction *Product){     //Ücreti Hesaplıyoruz.
    int i=1;
    Product->FinalPrice=Product->InitialBid[0];
    while(i!=Product->BidCount ) {
        Product->FinalPrice+=Product->InitialBid[i];
        i++;
    }

    return Product->FinalPrice;
}

int main() {
    Auction Product;
    setlocale(LC_ALL,"Turkish");
    wprintf(L"Müzayede Programına Hoş Geldiniz!\n");
    wprintf(L"Lütfen Müzayede Yapılmasını İstediğiniz Ürünün Adını Giriniz:\n");
    scanf("%ls",&Product.Name);
    wprintf(L"Lütfen Ürünün Başlangıç Fiyatını Giriniz:\n");
    scanf("%lf",&Product.InitialBid[0]);
    StartAuction(&Product);
    if(Price(&Product) != Product.InitialBid[0])   //Ürün Fiyatının Başlangıç Fiyatından Farklı Olduğunu Kontrol Ediyoruz.
        wprintf(L"Ürün : %ls\nSon Fiyat : %.2lf\nMüzayedeyi Kazanan : %d Numara", Product.Name,
                Price(&Product), Product.BidCount - 1);
    else{                                                                                                   //Price Fonksiyonuyla Ürünün Son Fiyatını Hesaplıyoruz.
        wprintf(L"Herhangi Bir Teklif Yapılmadı\n", Product.Name);
    }
    return 0;
}
