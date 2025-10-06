#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
//deklarasi file yang dibutuhkan
FILE *SALDO_FILE;
FILE *DATADIRI_FILE;
FILE *MUTASI_FILE;
FILE *REKENING_FILE;
FILE *AKUN_FILE;
//struktur variabel-variabel untuk mekanisme program
typedef struct{
    const char *NIK[16];
    const char *namaDepan[50];
    const char *namaBelakang[50];
    const char *tempatLahir[50];
    int *tanggalLahir;
    int *bulanLahir;
    int *tahunLahir;
    const char *alamat[50];
    const char *noHp[15];
    const char *email[40];
    const char *username[20];
    const char *password[15];
    const char *pinTransaksi[6];
    const char *NomorRekening[9];
    const char *namaLengkap[50];
}informasiDiri;
typedef struct{
    char nomorTransaksi[15];
    char kodeTransaksi[20];
    double nominal;
    char batalTransaksi;
    char *keterangan[50];
    double saldo;
    double biayaAdmin;
    double total;
    char pilihan;
    char pilihanInvalid;
    char *jenisTransaksi[20];
    char *tipeTransaksi[20];
    char *tujuanTransaksi[20];
    char subKeterangan[30];
    char vaSetor[20];
    char vaTarik[20];
    char subtitute[7];
    int kodeVa;
    int norekAngkaInput;
    char noRekeningTujuan[10];
    const char kodeEWallet[5];
    const char kodeEMoney[4];
    const char kodeProvider[4];
    const char noTelepon[13];
    const char noKartu[15];
    char *jenisEWallet[18];
    char *jenisEMoney[20];
    char *jenisProvider[21];
    char *tujuanTambahan[20];
}informasi2;
typedef struct{
    const char *namaPemilik[30];
    const char *simKode[3];
    const char *nomorSIM[5];
    double totalBayar;
    double nominalBayar;
    const char *keterangan[20];
    double periode;
    double hargaKonstan;
}InformasiESIM;
typedef struct{
    const char *namaPemilik[30];
    double totalBayar;
    double nominal;
    const char *keterangan;
    const char *nomorlistrikpascabayar[11];
    int periode;
    double hargaListrikPasca;
    int Dayalistrik;
}InformasiPLN;
typedef struct {
    char nama[40];
    char norek[15];
} daftarNasabah;
daftarNasabah database[] = {
    {"Abdul Hafidz Khaerul Imam", "222413464"},
    {"Akhmad Alief Aflah H.", "222413484"},
    {"Khaira Parsha Zarita", "222413628"},
    {"Mei Indriyanti Syamsi", "212413652"},
    {"Ratna Sari Putri", "212413746"},
    {"Ayudya Inara", "212413351"},
    {"Cantika Azizah", "112413467"},
    {"Rahmat Budiono", "112413720"},
    {"Faiz Akbar", "112413521"}
};
int jumlahData = sizeof(database)/sizeof(database[0]);
//inisialisasi fungsi-fungsi yang diperlukan
int login(const char *username, const char *password);
int password(const char *pin);
double bacaSaldo();
void bukaRekening(informasiDiri Nasabah);
void bacaRekening();
void delay(int j);
void dataDiri();
void firstPage();
void tampilanMenuAwal();
void loginPage();
void tampilanMenuUtama();
void tampilanLayananDigital();
void tampilanLayananTransfer();
void tampilanFinalPln(const char *namaPemilik, const char *NomorMeteranPasca, int dayaListrik, double Nominal, int periode);
void tampilanPLN();
void transferUang();
void tampilanTransferAntarBank();
void tampilanESIM();
void tampilan2ESIM(const char *namaPemilik, const char *JenisSIM, const char *NomorSIM, double nominal, double periode);
void tampilanSubmenuTransfer();
void tampilanSubmenuPemerintah();
void tampilanSetorTunai();
void tampilanVASetorTarik(const char *keterangan, char *subtitue, int kodeVA, double nominal, const char *keteranganAkhir, double saldo, char *vaSetorTarik);
void informasiAkun();
void tampilanInfoAkun();
void simpanDataKeFile(informasiDiri Nasabah);
void SimpanTransaksiKeFile(double total, const char *keterangan, const char *kodeTransaksi, const char *jenisTransaksi, const char *tipeTransaksi);
void tampilanHistoriTransaksi();
void tampilanStruk(const char *nomorReferensi, const char *jenisTransaksi, const char *kodeStruk, const char *tujuanTransaksi, const char *tujuanTambahan, double biayaAdmin, double nominal, double total, const char *keterangan);
int validasiNIK(const char *NIK);
int validasiTanggalLahir(int tanggalLahir);
int validasiBulanLahir(int bulanLahir);
int validasiTahunLahir(int tahunLahir);
int validasiTempatLahir(const char *tempatLahir);
int validasiAlamat(const char *alamat);
int validasiNoHP(char *noHp);
int validasiUsername(const char *username);
int validasiGmail(const char *gmail);
int validasiPassword(const char *password, const char *username);
int validasiPinTransaksi(const char *pin);
int validasiNamaLengkap(const char *namaLengkap);
int validasiNoRekening(const char *nomorRekening);
int validasiNoListrikPascaBayar(const char *nomorlistrikpascabayar);
double tarifESIM(const char *kode);
double nilaiAdminTransfer(const char *noRekening);
int validasiESIM(const char *nomorSIM);
int validasiKeterangan(const char keterangan);
int validasiNama(const char *nama);
void registrasiNasabah();
void simpanPerbaruiSaldo(double saldo);
char *generatorRandNum();
char *generatorKodeSetor();
char *generatorKodeTarik();
char *generatorUnCode();
//main
int main(){
    srand(time(NULL));
    informasi2 nasabah;
    informasiDiri data;
    SALDO_FILE = fopen("DataSaldo.txt", "r");
    if(SALDO_FILE ==NULL){
        SALDO_FILE == fopen("DataSaldo.txt", "w");
        if(SALDO_FILE != NULL){
            fprintf(SALDO_FILE, "%lf\n", nasabah.saldo);
            fclose(SALDO_FILE);
        }
        else{
            printf("\t\t\t Data Saldo gagal diinisialisasi!\n");
        }
    }
    else{
        fclose(SALDO_FILE);
    }
    firstPage();
    printf("\t\t\t\t\t\t");
    system("pause");
    printf("\t\t\t                        Loading Masuk");
    for(int i=0; i<3; i++){
        delay(100000000);
        printf(".");
    }
    system("cls");
    tampilanMenuAwal();
}
//subprogram untuk validasi
int login(const char *username, const char *password){
    informasiDiri user;
    AKUN_FILE = fopen("DATAAKUN.txt", "r");
    if(AKUN_FILE  == NULL){
        printf("\t\t\t Maaf, username dan password tidak dikenali!\n");
        return 0;
    }
    while(fscanf(AKUN_FILE, "%s" "%s", user.username, user.password)!=EOF){
        if((strcmp(username, user.username)==0) && (strcmp(password, user.password)==0)){
                fclose(AKUN_FILE);
                return 1;
        }
    }
    fclose(AKUN_FILE);
    return 0;
}
int password(const char *pin){
    informasiDiri user;
    AKUN_FILE = fopen("DATAAKUN.txt", "r");
    if(AKUN_FILE == NULL){
        printf("\t\t\t password tidak terbaca!\n");
    }
    else{
        while(fscanf(AKUN_FILE, "%s", user.pinTransaksi)!=EOF){
            if(strcmp(pin, user.pinTransaksi)==0){
                fclose(DATADIRI_FILE);
                return 1;
            }
        }
    }
    fclose(AKUN_FILE);
    return 0;
}
int validasiNIK(const char *NIK){
    int panjangKarakter = strlen(NIK);
    if(panjangKarakter != 16){
        return 0;
    }
    for(int i=0; i<panjangKarakter; i++){
        if(isalpha(NIK[i])){
            return 0;
        }
    }
    return 1;
}
int validasiTanggalLahir(int tanggalLahir){
    return (tanggalLahir >= 1 && tanggalLahir <=31);
}
int validasiBulanLahir(int bulanLahir){
    return (bulanLahir >= 1 && bulanLahir <= 12);
}
int validasiTahunLahir(int tahunLahir){
    return (tahunLahir >= 1900 && tahunLahir <= 2009);
}
int validasiNoHP(char *noHp) {
    return ((strncmp(noHp, "08", 2) == 0 || strncmp(noHp, "+62", 3) == 0) && ((strlen(noHp)>=11 && strlen(noHp)<=13)));
}
int validasiUsername(const char *username){
    int hurufKecil = 0;
    int hurufBesar = 0;
    int adaAngka=0;
    int adaSpasi=1;
    int panjangKarakter = strlen(username);
    if(panjangKarakter >= 1 && panjangKarakter <= 20){
        for(int i=0; i<strlen(username); i++){
            if(islower(username[i])){
                hurufKecil = 1;
            }
            if(isupper(username[i])){
                hurufBesar = 1;
            }
            if(isdigit(username[i])){
                adaAngka=1;
            }
            if(isspace(username[i])){
                adaSpasi=0;
            }
            if((hurufKecil && hurufBesar && adaAngka && adaSpasi)){
                return 1;
            }
        }
        return 0;
    }
    else{
        return 0;
    }
}
int validasiGmail(const char *gmail){
    if(strstr(gmail, "@gmail.com")){
        return 1;
    }
    else{
        return 0;
    }
}
int validasiPassword(const char *password, const char *username){
    int jmlKarakter = strlen(password);
    int adaAngka = 0;
    int adaSpasi = 1;
    if((jmlKarakter >=1 && jmlKarakter<=15) && (strcasecmp(password, username)!=0)){
        for(int i=0; i<jmlKarakter; i++){
            if(isdigit(password[i])){
                adaAngka = 1;
            }
            if(isspace(password[i])){
                adaSpasi = 0;
            }
            if(adaAngka && adaSpasi){
                return 1;
            }
        }
        return 0;
    }
    else{
        return 0;
    }
}
int validasiPinTransaksi(const char *pin){
    int jmlKarakter = strlen(pin);
    int adaSpasi = 1;
    int adaHuruf = 1;
    if(jmlKarakter == 7){
        for(int i=0; i<jmlKarakter; i++){
            if(isspace(pin[i])){
                adaSpasi = 0;
            }
            if(isalpha(pin[i])){
                adaHuruf = 0;
            }
            if(adaSpasi && adaHuruf){
                return 1;
            }
        }
        return 0;
    }
    else{
        return 0;
    }
}
int validasiNamaLengkap(const char *namaLengkap){
    int panjangKarakter = strlen(namaLengkap);
    if(panjangKarakter <3 || panjangKarakter >30){
        return 0;
    }
    for(int i=0; i<panjangKarakter; i++){
        if(isdigit(namaLengkap[i]) || ispunct(namaLengkap[i])){
            return 0;
        }
    }
    return 1;
}
int validasiNoRekening(const char *nomorRekening){
    int panjangKarakter = strlen(nomorRekening);
    char karakterWajib[] = "22";
    int memenuhiSyaratKarakter = 0;
    if (strlen(nomorRekening)!=9) {
        return 0;
    }
    if (strncmp(nomorRekening, "22", 2) != 0) {
        return 0;
    }
    return 1;
}
int validasiTempatLahir(const char *tempatLahir){
    int panjangKarakter = strlen(tempatLahir);
    if(panjangKarakter <= 2 || panjangKarakter >= 50){
        return 0;
    }
    return 1;
}
int validasiAlamat(const char *Alamat){
    int panjangKarakter = strlen(Alamat);
    if(panjangKarakter <= 2 || panjangKarakter >= 50){
        return 0;
    }
    return 1;
}
int validasiESIM(const char *nomorSIM){
    int panjangKarakter = strlen(nomorSIM);
    if(panjangKarakter != 5){
        return 0;
    }
    if(strcmp(nomorSIM, "00000")==0){
        return 0;
    }
    return 1;
}
int validasiNama(const char *nama){
    for(int i=0; i<strlen(nama); i++){
        if(isdigit(nama[i])||isspace(nama[i])){
            return 0;
        }
    }
    return 1;
}
int validasiSaldo(double totalBayar){
    double saldo = bacaSaldo();
    if(saldo >= totalBayar){
        return 1;
    }
    else{
        return 0;
    }
}
int validasiNoListrikPascaBayar(const char *nomorlistrikpascabayar){
    int panjangkarakter = strlen(nomorlistrikpascabayar);
    int memenuhiSyaratKarakter = 0;
    if (strlen(nomorlistrikpascabayar) >=10 && strlen(nomorlistrikpascabayar) <= 11){
        return 0;
    }
    if (strncmp(nomorlistrikpascabayar, "10987", 5)!= 0){
        return 0;
    }
    return 1;
}
//subprogram tentang saldo
double bacaSaldo(){
    SALDO_FILE = fopen("DataSaldo.txt", "r");
    double saldo;
    if(SALDO_FILE!=0){
        fscanf(SALDO_FILE,"%lf",&saldo);
        fclose(SALDO_FILE);
    }
    else{
        printf("\t\t\t Saldo tidak terbaca!\n");
        return 0;
    }
    return saldo;
}
void simpanPerbaruiSaldo(double saldo){
    SALDO_FILE = fopen("DataSaldo.txt", "w");
    if(SALDO_FILE != 0){
        fprintf(SALDO_FILE, "%lf", saldo);
        fclose(SALDO_FILE);
    }
    else{
        printf("Transaksi gagal, saldo tidak terupdate!");
        return 0;
    }
    return saldo;
}
double tarifESIM(const char *kode){
    if(strcasecmp(kode, "AU")==0) return 80000;
    if(strcasecmp(kode, "BU")==0) return 100000;
    if(strcasecmp(kode, "BU1")==0) return 95000;
    if(strcasecmp(kode, "CU")==0) return 82000;
    if(strcasecmp(kode, "CU1")==0) return 85000;
    if(strcasecmp(kode, "AK1")==0) return 70000;
    if(strcasecmp(kode, "AK2")==0) return 75000;
    if(strcasecmp(kode, "CK1")==0) return 90000;
    if(strcasecmp(kode, "DK")==0) return 70000;
    if(strcasecmp(kode, "INT")==0) return 125000;
}
int validasiKeterangan(const char keterangan){
    if(strlen(keterangan)>=26){
        return 0;
    }
    return 1;
}
double nilaiAdminTransfer(const char *noRekening){
    if(strncmp(noRekening, "21", 2)==0){return 1500;}
    if(strncmp(noRekening, "11", 2)==0){return 1500;}
    if(strncmp(noRekening, "22", 2)==0){return 0;}
}
//kode kode khusus lainnya
char *ambilNoHp(const char *kodeEWallet, int n){
    static char NoHp[15];
   if(strncmp(kodeEWallet, "60737", 5)==0){
    if(n>=1){
        strncpy(NoHp, kodeEWallet+5, n);
        NoHp[n]='\0';
      }
    }
    else if (strncmp(kodeEWallet, "89588", 5)==0){
     if(n>=1){
        strncpy(NoHp, kodeEWallet+5, n);
        NoHp[n]='\0';
      }
    }
    else if (strncmp(kodeEWallet, "89508", 5)==0){
     if(n>=1){
        strncpy(NoHp, kodeEWallet+5, n);
        NoHp[n]='\0';
      }
    }
    else if (strncmp(kodeEWallet, "60001", 5)==0){
     if(n>=1){
        strncpy(NoHp, kodeEWallet+5, n);
        NoHp[n]='\0';
      }
    }
    printf("\t\t\t Nomor HP Anda: ");
    return NoHp;
}

char *ambilNoKartu(const char *kodeEMoney, int n){
    static char NoKartu[15];
    if(strncmp(kodeEMoney, "6013", 4)==0){
    if(n>=1){
        strncpy(NoKartu, kodeEMoney+4, n-1);
        NoKartu[n-1]='\0';
      }
    }
    else if (strncmp(kodeEMoney, "6023", 4)==0){
     if(n>=1){
        strncpy(NoKartu, kodeEMoney+4, n-1);
        NoKartu[n-1]='\0';
      }
    }
    else if (strncmp(kodeEMoney, "7546", 4)==0){
     if(n>=1){
        strncpy(NoKartu, kodeEMoney+4, n-1);
        NoKartu[n-1]='\0';
      }
    }
    printf("\t\t\t Nomor kartu Anda: ");
    return NoKartu;
}

char *ambilNoTelepon(const char *kodeProvider, int n){
    static char NoTelepon[15];
    if(strncmp(kodeProvider, "0821", 4)==0){
    if(n>=1){
        strncpy(NoTelepon, kodeProvider, n-1);
        NoTelepon[n-1]='\0';
      }
    }
    else if (strncmp(kodeProvider, "0818", 4)==0){
     if(n>=1){
        strncpy(NoTelepon, kodeProvider, n-1);
        NoTelepon[n-1]='\0';
      }
    }
    else if (strncmp(kodeProvider, "0858", 4)==0){
     if(n>=1){
        strncpy(NoTelepon, kodeProvider+1, n-1);
        NoTelepon[n-1]='\0';
      }
    }
    else if (strncmp(kodeProvider, "0832", 4)==0){
     if(n>=1){
        strncpy(NoTelepon, kodeProvider, n-1);
        NoTelepon[n-1]='\0';
      }
    }
    printf("\t\t\t Nomor telepon Anda: ");
    return NoTelepon;
}

//subprogram tentang generator nomor random dan lainnya
void delay(int j){
    for(int i=0; i<j; i++){
        int k=i;
    }
}
char *generatorRandNum(){
    static char nomor[9];
    const char *karakter="0123456789";
    for (int i = 0; i < 15; i++) {
        int index = rand() % 10;
        nomor[i] = karakter[index];
    }
    nomor[8] = '\0';
    return nomor;
}
char *generatorKodeSetor(){
    const char *karakter="0123456789";
    static char NoSetor[12];
    NoSetor[0]='0';
    NoSetor[1]='2';
    NoSetor[2]='0';
    NoSetor[3]='-';
    for(int i=4; i < 9; i++){
        int index = rand()%strlen(karakter);
        NoSetor[i]=karakter[index];
    }
    NoSetor[11]='\0';
    return NoSetor;
}
char *generatorKodeTarik(){
    const char *karakter="0123456789";
    static char NoTarik[12];
    NoTarik[0]='0';
    NoTarik[1]='5';
    NoTarik[2]='0';
    NoTarik[3]='-';
    for(int i=4; i<9; i++){
        int index = rand()%strlen(karakter);
        NoTarik[i]=karakter[index];
    }
    NoTarik[11]='\0';
    return NoTarik;
}
char *generatorUnCode(){
    const char *huruf="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char *angka="0123456789";
    static char kode[12];
    srand(time(0));
    for (int i = 0; i < 4; ++i) {
        int randIndex = rand() % strlen(huruf);
        kode[i] = huruf[randIndex];
    }
    kode[4] = '-';
    for (int i = 5; i < 10; ++i) {
        int randIndex = rand() % strlen(angka);
        kode[i] = angka[randIndex];
    }
    kode[11] = '\0';
    return kode;
}
//fungsi-fungsi khusus lainnya
void buatRekening(){
    informasiDiri Rekening;
    int inputValid = 0;
    do{
        char konfirmasiJawab;
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                        [ mobiStats 5 ]                         |\n");
        printf("\t\t\t|                 << BANK SENTRAL STATISTIK >>                   |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                 >> FORM REGISTRASI NASABAH <<                  |\n");
        printf("\t\t\t|                   [Formulir Buka Rekening]                     |\n");
        printf("\t\t\t| Tanggal : %02d/%02d/%04d", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
        printf("                         Waktu : %02d:%02d WIB |\n", tm->tm_hour, tm->tm_min);
        printf("\t\t\t+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n");
        printf("\t\t\t Keterangan : - No Rekening gunakan NIM komputasi statistik [22xxxxxxx]\n");
        printf("\t\t\t              - Panjang karakter nama maksimal 50 karakter,\n");
        printf("\t\t\t                tidak diperkenankan mengandung karakter aneh\n");
        printf("\t\t\t Masukkan nama Anda      : ");
        gets(Rekening.namaLengkap);
        if(!validasiNamaLengkap(Rekening.namaLengkap)){
            printf("\t\t\t Nama tidak memenuhi syarat!\n");
            printf("\t\t\t Ingin mengulangi registrasi? [Ya : y || Tidak : t] = ");
            scanf("%s", &konfirmasiJawab);
            getchar();
            if(konfirmasiJawab=='y' || konfirmasiJawab=='Y'){
                system("CLS");
                continue;
            }
            else{
                return;
            }
        }
        printf("\t\t\t Masukkan nomor rekening : ");
        scanf("%s", &Rekening.NomorRekening);
        if(!validasiNoRekening(Rekening.NomorRekening)){
            printf("\t\t\t Nomor rekening tidak memenuhi kriteria yang ditetapkan!\n");
            printf("\t\t\t Ingin mengulangi registrasi? [Ya : y || Tidak : t] = ");
            scanf("%s", &konfirmasiJawab);
            getchar();
            if(konfirmasiJawab=='y' || konfirmasiJawab=='Y'){
                system("CLS");
                continue;
            }
            else{
                return;
            }
        }
        inputValid = 1;
    }while(!inputValid);
    bukaRekening(Rekening);
    printf("\t\t\t Mengembalikan ke layar utama");
    for(int i=0; i<3; i++){
        delay(100000000);
        printf(".");
    }
    system("cls");
    tampilanMenuAwal();
}
void bukaRekening(informasiDiri Rekening){
    REKENING_FILE = fopen("DataRekeningNasabah.txt", "w");
    if(REKENING_FILE == NULL){
        printf("Gagal membuka file rekening untuk menulis!\n");
        return 0;
    }
    else{
        fprintf(REKENING_FILE, "%s\n", &Rekening.namaLengkap);
        fprintf(REKENING_FILE, "%s\n", &Rekening.NomorRekening);
        fclose(REKENING_FILE);
        printf("\t\t\t Data rekening berhasil tersimpan!\n");
    }
}
void simpanDataKeFile(informasiDiri data) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    DATADIRI_FILE = fopen("DataNasabah.txt", "w");
    AKUN_FILE = fopen("DATAAKUN.txt", "w");
    if (DATADIRI_FILE == NULL && AKUN_FILE == NULL) {
        printf("Gagal membuka file untuk menulis!\n");
        return 0;
    }
    else{
        fprintf(DATADIRI_FILE, "%s\n", data.namaDepan);
        fprintf(DATADIRI_FILE, "%s\n", data.namaBelakang);
        fprintf(DATADIRI_FILE, "%s\n", data.NIK);
        fprintf(DATADIRI_FILE, "%s\n", data.tempatLahir);
        fprintf(DATADIRI_FILE, "%d\n", data.tanggalLahir);
        fprintf(DATADIRI_FILE, "%d\n", data.bulanLahir);
        fprintf(DATADIRI_FILE, "%d\n", data.tahunLahir);
        fprintf(DATADIRI_FILE, "%s\n", data.alamat);
        fprintf(DATADIRI_FILE, "%s\n", data.noHp);
        fprintf(DATADIRI_FILE, "%s\n", data.email);
        fprintf(AKUN_FILE, "%s\n", data.username);
        fprintf(AKUN_FILE, "%s\n", data.password);
        fprintf(AKUN_FILE, "%s\n", data.pinTransaksi);
        fclose(DATADIRI_FILE);
        fclose(AKUN_FILE);
        printf("\n\t\t\t Data berhasil disimpan ke file.\n");
    }
}
void SimpanTransaksiKeFile(double total, const char *keterangan, const char *kodeTransaksi, const char *jenisTransaksi, const char *tipeTransaksi){
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    MUTASI_FILE = fopen("DataMutasi.txt", "a");
    if(MUTASI_FILE == NULL){
        printf("Data mutasi tidak tersedia!\n");
    }
    else{
        fprintf(MUTASI_FILE, "\t\t\t Kode Transaksi      : %s\n", kodeTransaksi);
        fprintf(MUTASI_FILE, "\t\t\t Nominal Transaksi   : Rp%.0lf\n", total);
        fprintf(MUTASI_FILE, "\t\t\t Keterangan          : %s\n", keterangan);
        fprintf(MUTASI_FILE, "\t\t\t Layanan             : %s - %s\n", jenisTransaksi, tipeTransaksi);
        fprintf(MUTASI_FILE, "\t\t\t Tanggal             : %02d/%02d/%02d\n", tm->tm_mday, tm->tm_mon+1, tm->tm_year+1900);
        fprintf(MUTASI_FILE, "\t\t\t Waktu               : %02d.%02d.%02d WIB\n", tm->tm_hour, tm->tm_min, tm->tm_sec);
        fprintf(MUTASI_FILE, "\t\t\t+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n");
        fclose(MUTASI_FILE);
    }
}
void registrasiNasabah() {
    informasiDiri nasabah;
    informasi2 pilihan;
    int inputValid = 0;
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    do {
        char konfirmasiJawab;
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                        [ mobiStats 5 ]                         |\n");
        printf("\t\t\t|                 << BANK SENTRAL STATISTIK >>                   |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                 >> FORM REGISTRASI NASABAH <<                  |\n");
        printf("\t\t\t|                      [Formulir Data Diri]                      |\n");
        printf("\t\t\t| Tanggal : %02d/%02d/%04d", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
        printf("                         Waktu : %02d:%02d WIB |\n", tm->tm_hour, tm->tm_min);
        printf("\t\t\t+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n");
        printf("\t\t\t Masukkan Nama Depan    : ");
        gets(nasabah.namaDepan);
        if(!validasiNama(nasabah.namaDepan)){
            printf("\t\t\t Nama tidak diperkenankan mengandung angka atau spasi!\n");
            printf("\t\t\t Ingin mengulangi registrasi? [Ya : y || Tidak : t] = ");
            scanf("%s", &konfirmasiJawab);
            getchar();
            if(konfirmasiJawab=='y' || konfirmasiJawab=='Y'){
                system("CLS");
                continue;
            }
            else{
                printf("\t\t\t Mengembalikan layar");
                for(int i=0; i<3; i++){
                    delay(100000000);
                    printf(".");
                }
                system("cls");
                tampilanMenuAwal();
            }
        }
        printf("\t\t\t Masukkan Nama Belakang : ");
        gets(nasabah.namaBelakang);
        if(!validasiNama(nasabah.namaBelakang)){
            printf("\t\t\t Nama tidak diperkenankan mengandung angka!\n");
            printf("\t\t\t Ingin mengulangi registrasi? [Ya : y || Tidak : t] = ");
            scanf("%s", &konfirmasiJawab);
            getchar();
            if(konfirmasiJawab=='y' || konfirmasiJawab=='Y'){
                system("CLS");
                continue;
            }
            else{
                printf("\t\t\t Mengembalikan layar");
                for(int i=0; i<3; i++){
                    delay(100000000);
                    printf(".");
                }
                system("cls");
                tampilanMenuAwal();
            }
        }
        printf("\t\t\t Masukkan NIK Anda (16) : ");
        gets(nasabah.NIK);
        if (!validasiNIK(nasabah.NIK)) {
            printf("\t\t\t NIK harus 16 karakter numerik dan tanpa huruf\n");
            printf("\t\t\t Ingin mengulangi registrasi? [Ya : y || Tidak : t] = ");
            scanf("%s", &konfirmasiJawab);
            getchar();
            if(konfirmasiJawab=='y' || konfirmasiJawab=='Y'){
                system("CLS");
                continue;
            }
            else{
                printf("\t\t\t Mengembalikan layar");
                for(int i=0; i<3; i++){
                    delay(100000000);
                    printf(".");
                }
                system("cls");
                tampilanMenuAwal();
            }
        }
        printf("\t\t\t Tempat Lahir           : ");
        gets(nasabah.tempatLahir);
        if (!validasiTempatLahir(nasabah.tempatLahir)) {
            printf("\t\t\t Nama tempat lahir terlalu panjang! [Max 50 karakter]\n");
            printf("\t\t\t Ingin mengulangi registrasi? [Ya : y || Tidak : t] = ");
            scanf("%s", &konfirmasiJawab);
            getchar();
            if(konfirmasiJawab=='y' || konfirmasiJawab=='Y'){
                system("CLS");
                continue;
            }
            else{
                printf("\t\t\t Mengembalikan layar");
                for(int i=0; i<3; i++){
                    delay(100000000);
                    printf(".");
                }
                system("cls");
                tampilanMenuAwal();
            }
        }
        printf("\t\t\t Tanggal Lahir (1-31)   : ");
        scanf("%d", &nasabah.tanggalLahir);
        if (!validasiTanggalLahir(nasabah.tanggalLahir)) {
            printf("\t\t\t Tanggal lahir tidak valid! masukkan sesuai ketentuan\n");
            printf("\t\t\t Ingin mengulangi registrasi? [Ya : y || Tidak : t] = ");
            scanf("%s", &konfirmasiJawab);
            getchar();
            if(konfirmasiJawab=='y' || konfirmasiJawab=='Y'){
                system("CLS");
                continue;
            }
            else{
                printf("\t\t\t Mengembalikan layar");
                for(int i=0; i<3; i++){
                    delay(100000000);
                    printf(".");
                }
                system("cls");
                tampilanMenuAwal();
            }
        }
        getchar();
        printf("\t\t\t Bulan Lahir (1-12)     : ");
        scanf("%d", &nasabah.bulanLahir);
        if (!validasiBulanLahir(nasabah.bulanLahir)) {
            printf("\t\t\t Bulan lahir tidak valid! masukkan sesuai ketentuan\n");
            printf("\t\t\t Ingin mengulangi registrasi? [Ya : y || Tidak : t] = ");
            scanf("%s", &konfirmasiJawab);
            getchar();
            if(konfirmasiJawab=='y' || konfirmasiJawab=='Y'){
                system("CLS");
                continue;
            }
            else{
                printf("\t\t\t Mengembalikan layar");
                for(int i=0; i<3; i++){
                    delay(100000000);
                    printf(".");
                }
                system("cls");
                tampilanMenuAwal();
            }
        }
        printf("\t\t\t Tahun Lahir            : ");
        scanf("%d", &nasabah.tahunLahir);
        getchar();
        if (!validasiTahunLahir(nasabah.tahunLahir)) {
            printf("\t\t\t Tahun lahir tidak memenuhi syarat!\n");
            printf("\t\t\t Ingin mengulangi registrasi? [Ya : y || Tidak : t] = ");
            scanf("%s", &konfirmasiJawab);
            getchar();
            if(konfirmasiJawab=='y' || konfirmasiJawab=='Y'){
                system("CLS");
                continue;
            }
            else{
                printf("\t\t\t Mengembalikan layar");
                for(int i=0; i<3; i++){
                    delay(100000000);
                    printf(".");
                }
                system("cls");
                tampilanMenuAwal();
            }
        }
        printf("\t\t\t Alamat                 : ");
        gets(nasabah.alamat);
        if (!validasiAlamat(nasabah.alamat)) {
            printf("Alamat terlalu panjang! [Max 50 karakter]!\n");
            printf("Ingin mengulangi registrasi? [Ya : y || Tidak : t] = ");
            scanf("%s", &konfirmasiJawab);
            getchar();
            if(konfirmasiJawab=='y' || konfirmasiJawab=='Y'){
                system("CLS");
                continue;
            }
            else{
                printf("\t\t\t Mengembalikan layar");
                for(int i=0; i<3; i++){
                    delay(100000000);
                    printf(".");
                }
                system("cls");
                tampilanMenuAwal();
            }
        }
        printf("\t\t\t No HP                  : ");
        scanf("%s", &nasabah.noHp);
        if (!validasiNoHP(nasabah.noHp)) {
            printf("\t\t\t Nomor Hp nasional tidak diawali dengan '08' atau '+62' atau digit tidak memenuhi syarat\n");
            printf("\t\t\t Ingin mengulangi registrasi? [Ya : y || Tidak : t] = ");
            scanf("%s", &konfirmasiJawab);
            getchar();
            if(konfirmasiJawab=='y' || konfirmasiJawab=='Y'){
                system("CLS");
                continue;
            }
            else{
                printf("\t\t\t Mengembalikan layar");
                for(int i=0; i<3; i++){
                    delay(100000000);
                    printf(".");
                }
                system("cls");
                tampilanMenuAwal();
            }
        }
        printf("\t\t\t Email [mohon untuk gunakan '@gmail.com'] : ");
        scanf("%s", nasabah.email);
        getchar();
        if(!validasiGmail(nasabah.email)){
            printf("\t\t\t Email harus menggunakan '@gmail.com'.\n");
            printf("\t\t\t Ingin mengulangi registrasi? [Ya : y || Tidak : t] = ");
            scanf("%s", &konfirmasiJawab);
            getchar();
            if(konfirmasiJawab=='y' || konfirmasiJawab=='Y'){
                system("CLS");
                continue;
            }
            else{
                printf("\t\t\t Mengembalikan layar");
                for(int i=0; i<3; i++){
                    delay(100000000);
                    printf(".");
                }
                system("cls");
                tampilanMenuAwal();
            }
        }
        printf("\n");
        printf("\t\t\t Kriteria username (20) : Kombinasi huruf kapital, kecil dan numerik\n");
        printf("\t\t\t Kriteria password (15) : Kombinasi huruf dan numerik\n");
        printf("\t\t\t Kriteria pin      (=6) : Kombinasi 6 numerik\n");
        printf("\t\t\t Username, password, dan pin tidak diperkenankan mengandung spasi!\n");
        printf("\t\t\t pin tidak boleh sama dengan username!\n");
        printf("\n");
        printf("\t\t\t Buat username login : ");
        gets(nasabah.username);
        if(!validasiUsername(nasabah.username)){
            printf("\t\t\t Username harus mengandung karakter kapital, kecil, tanpa spasi,\n");
            printf("\t\t\t dan nomor serta kurang dari 20 karakter\n");
            printf("\t\t\t Ingin mengulangi registrasi? [Ya : y || Tidak : t] = ");
            scanf("%s", &konfirmasiJawab);
            if(konfirmasiJawab=='y' || konfirmasiJawab=='Y'){
                system("CLS");
                continue;
            }
            else{
                printf("\t\t\t Mengembalikan layar");
                for(int i=0; i<3; i++){
                    delay(100000000);
                    printf(".");
                }
                system("cls");
                tampilanMenuAwal();
            }
        }
        printf("\t\t\t Buat password login : ");
        gets(nasabah.password);
        if(!validasiPassword(nasabah.password, nasabah.username)){
            printf("\t\t\t Password tidak diperkenankan mengandung spasi, melebihi 15 karakter,\n");
            printf("\t\t\t dan harus dengan kombinasi angka atau identik username\n");
            printf("\t\t\t Ingin mengulangi registrasi? [Ya : y || Tidak : t] = ");
            scanf("%s", &konfirmasiJawab);
            getchar();
            if(konfirmasiJawab=='y' || konfirmasiJawab=='Y'){
                system("CLS");
                continue;
            }
            else{
                printf("\t\t\t Mengembalikan layar");
                for(int i=0; i<3; i++){
                    delay(100000000);
                    printf(".");
                }
                system("cls");
                tampilanMenuAwal();
            }
        }
        printf("\t\t\t Buat pin transaksi  : ");
        fgets(nasabah.pinTransaksi, sizeof(nasabah.pinTransaksi), stdin);
        nasabah.pinTransaksi[strcspn(nasabah.pinTransaksi, "\n")]='\0';
        if(!validasiPinTransaksi(nasabah.pinTransaksi)){
            printf("\t\t\t Pin tidak diperkenankan mengandung spasi, kurang atau lebih dari 6 karakter, dan harus berupa numerik\n");
            printf("\t\t\t Ingin mengulangi registrasi? [Ya : y || Tidak : t] = ");
            scanf("%s", &konfirmasiJawab);
            getchar();
            if(konfirmasiJawab=='y' || konfirmasiJawab=='Y'){
                system("CLS");
                continue;
            }
            else{
                printf("\t\t\t Mengembalikan layar");
                for(int i=0; i<3; i++){
                    delay(100000000);
                    printf(".");
                }
                system("cls");
                tampilanMenuAwal();
            }
        }
        inputValid = 1;
    } while (!inputValid);
    SALDO_FILE = fopen("DataSaldo.txt", "r");
    if(SALDO_FILE != NULL){
        fclose(SALDO_FILE);
        remove("DataSaldo.txt");
    }
    MUTASI_FILE = fopen("DataMutasi.txt","r");
    if(MUTASI_FILE != NULL){
        fclose(MUTASI_FILE);
        remove("DataMutasi.txt");
    }
    simpanDataKeFile(nasabah);
    printf("\t\t\t Melanjutkan ke menu berikutnya");
    for(int i=0; i<3; i++){
        delay(100000000);
        printf(".");
    }
    system("cls");
    buatRekening();
}
//fungsi utama dan tampilan-tampilannya
void firstPage(){
    printf("\t\t\t+==================================================================+\n");
    printf("\t\t\t|                   << BANK SENTRAL STATISTIK >>                   |\n");
    printf("\t\t\t|=========================|  mobiStats 5  |========================|\n");
    printf("\t\t\t||oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--||\n");
    printf("\t\t\t||--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo||\n");
    printf("\t\t\t||oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--||\n");
    printf("\t\t\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
    printf("\t\t\t|                                                                  |\n");
    printf("\t\t\t|                                                                  |\n");
    printf("\t\t\t|                                                                  |\n");
    printf("\t\t\t|                                @@@@                              |\n");
    printf("\t\t\t|                             @@@@@@@@@@                           |\n");
    printf("\t\t\t|                            @@@@    @@@@                          |\n");
    printf("\t\t\t|                            @@@                                   |\n");
    printf("\t\t\t|                             @@@@@@@@                             |\n");
    printf("\t\t\t|                                 @@@@@@@                          |\n");
    printf("\t\t\t|                            @@@     @@@                           |\n");
    printf("\t\t\t|                            @@@@   @@@@                           |\n");
    printf("\t\t\t|                             @@@@@@@@@                            |\n");
    printf("\t\t\t|                                @@@@                              |\n");
    printf("\t\t\t|                                                                  |\n");
    printf("\t\t\t|                                                                  |\n");
    printf("\t\t\t|                                                                  |\n");
    printf("\t\t\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
    printf("\t\t\t||oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--||\n");
    printf("\t\t\t||--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo||\n");
    printf("\t\t\t||oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--||\n");
    printf("\t\t\t+==================================================================+\n");
    printf("\t\t\t|                Powered by mobiStats Technology                   |\n");
    printf("\t\t\t|            Reliable. Secure. Terpercaya. Statistik.              |\n");
    printf("\t\t\t+==================================================================+\n");
}
void tampilanMenuAwal(){
    informasi2 layanan;
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    int inputValid = 0;
    do{
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t|                       SELAMAT DATANG DI                        |\n");
    printf("\t\t\t|                        [ mobiStats 5 ]                         |\n");
    printf("\t\t\t|                 << BANK SENTRAL STATISTIK >>                   |\n");
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t| Tanggal : %02d/%02d/%04d", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
    printf("                         Waktu : %02d:%02d WIB |\n", tm->tm_hour, tm->tm_min);
    printf("\t\t\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
    printf("\t\t\t||--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--||\n");
    printf("\t\t\t||oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo||\n");
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t|                                                                |\n");
    printf("\t\t\t|          Layanan kami siap membantu kebutuhan Anda.            |\n");
    printf("\t\t\t|                                                                |\n");
    printf("\t\t\t|----------------------------------------------------------------|\n");
    printf("\t\t\t|                                                                |\n");
    printf("\t\t\t|                                                                |\n");
    printf("\t\t\t|                      >> Pilih Layanan <<                       |\n");
    printf("\t\t\t|                                                                |\n");
    printf("\t\t\t|                        Registrasi    [1]                       |\n");
    printf("\t\t\t|                        Log-in        [2]                       |\n");
    printf("\t\t\t|                        Log-out       [3]                       |\n");
    printf("\t\t\t|                                                                |\n");
    printf("\t\t\t|                                                                |\n");
    printf("\t\t\t|----------------------------------------------------------------|\n");
    printf("\t\t\t|                 Powered by mobiStats Technology                |\n");
    printf("\t\t\t|             Reliable. Secure. Terpercaya. Statistik.           |\n");
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t| PT BANK SENTRAL STATISTIK Tbk. berizin dan diawasi oleh Badan  |\n");
    printf("\t\t\t|     Pusat Statistik dan Bank Indonesia(BI), serta merupakan    |\n");
    printf("\t\t\t|        peserta penjaminan Lembaga Penjamin Simpanan(LPS)       |\n");
    printf("\t\t\t|             Copyright © 2025 Bank SENTRAL STATISTIK            |\n");
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t Masukkan pilihan Anda : ");
    scanf("%s", &layanan.pilihan);
    getchar();
    if(layanan.pilihan == '1'){
        printf("\t\t\t Mengalihkan layar");
        for(int i=0; i<3; i++){
            delay(100000000);
            printf(".");
        }
        system("cls");
        registrasiNasabah();
        getchar();
    }
    else if(layanan.pilihan == '2'){
       printf("\t\t\t Mengalihkan layar");
        for(int i=0; i<3; i++){
            delay(100000000);
            printf(".");
        }
        system("cls");
        loginPage();
    }
    else if(layanan.pilihan == '3'){
       printf("\t\t\t Mengalihkan layar");
        for(int i=0; i<3; i++){
            delay(100000000);
            printf(".");
        }
        system("cls");
        logoutPage();
    }
    else{
        printf("\n\t\t\t Input tidak valid!\n");
        printf("\t\t\t Mengembalikan layar");
        for(int i=0; i<3; i++){
            delay(100000000);
            printf(".");
        }
        system("cls");
        continue;
    }
    inputValid = 1;
    }while(!inputValid);
}
void loginPage() {
    int valid = 0;
    do {
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        informasi2 Mekanisme;
        informasiDiri Nasabah;
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                        [ mobiStats 5 ]                         |\n");
        printf("\t\t\t|                 << BANK SENTRAL STATISTIK >>                   |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                        >> LOGIN PAGE <<                        |\n");
        printf("\t\t\t| Tanggal : %02d/%02d/%04d", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
        printf("                         Waktu : %02d:%02d WIB |\n", tm->tm_hour, tm->tm_min);
        printf("\t\t\t+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n");
        printf("\t\t\t Masukkan username : ");
        scanf("%s", &Nasabah.username);
        printf("\t\t\t Masukkan password : ");
        scanf("%s", &Nasabah.password);
        if (login(Nasabah.username, Nasabah.password)){
            printf("\t\t\t Login berhasil!  ");
            system("pause");
            printf("\t\t\t Mengalihkan layar");
            for (int i = 0; i < 3; i++) {
                delay(100000000);
                printf(".");
            }
            system("cls");
            tampilanMenuUtama();
        } else {
            printf("\t\t\t Username dan Password salah!\n");
            printf("\t\t\t Ingin mengulangi kembali? (y/t) : ");
            scanf(" %c", &Mekanisme.batalTransaksi);
            if (Mekanisme.batalTransaksi == 'Y' || Mekanisme.batalTransaksi == 'y') {
                system("cls");
                continue;
            }
            else if (Mekanisme.batalTransaksi == 'T' || Mekanisme.batalTransaksi == 't') {
                printf("\t\t\t Mengembalikan ke menu awal");
                for (int i = 0; i < 3; i++) {
                    delay(100000000);
                    printf(".");
                }
                system("cls");
                tampilanMenuAwal();
            }
            else {
                printf("\t\t\t Pilihan tidak tersedia!\n");
                printf("\t\t\t Mengembalikan layar");
                for (int i = 0; i < 3; i++) {
                    delay(100000000);
                    printf(".");
                }
                system("cls");
                continue;
            }
        }
        valid = 1;
    } while (!valid);
}
void tampilanMenuUtama(){
    informasi2 Nasabah;
    informasiDiri Rekening;
    REKENING_FILE = fopen("DataRekeningNasabah.txt", "r");
    Nasabah.saldo = bacaSaldo();
    if(REKENING_FILE == NULL){
        printf("Data rekening tidak terbaca!\n");
    }
    else{
        fscanf(REKENING_FILE, "%[^\n]", &Rekening.namaLengkap);
        fscanf(REKENING_FILE, "%s\n", &Rekening.NomorRekening);
        fclose(REKENING_FILE);
    }
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t|                        [ mobiStats 5 ]                         |\n");
    printf("\t\t\t|                 << BANK SENTRAL STATISTIK >>                   |\n");
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t||oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo||\n");
    printf("\t\t\t||--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--||\n");
    printf("\t\t\t||oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo||\n");
    printf("\t\t\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
    printf("\t\t\t| Nasabah  : %-52s|\n", Rekening.namaLengkap);
    printf("\t\t\t| Rekening : %-52s|\n", Rekening.NomorRekening);
    printf("\t\t\t| Saldo    : Rp%-50.2lf|\n", Nasabah.saldo);
    printf("\t\t\t| Tanggal  = %02d/%02d/%d", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
    printf("\t\t\t Waktu layar = %02d:%02d WIB |\n", tm->tm_hour, tm->tm_min);
    printf("\t\t\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
    printf("\t\t\t|                               ||                               |\n");
    printf("\t\t\t|    1. Layanan Transfer        ||    2. Layanan Digital         |\n");
    printf("\t\t\t|                               ||                               |\n");
    printf("\t\t\t|----------------------------------------------------------------|\n");
    printf("\t\t\t|                               ||                               |\n");
    printf("\t\t\t|    3. Layanan Pemerintah      ||    4. Informasi Akun          |\n");
    printf("\t\t\t|                               ||                               |\n");
    printf("\t\t\t|----------------------------------------------------------------|\n");
    printf("\t\t\t|                                                                |\n");
    printf("\t\t\t|                          5. Kembali                            |\n");
    printf("\t\t\t|                                                                |\n");
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t|                                                                |\n");
    printf("\t\t\t| PT BANK SENTRAL STATISTIK Tbk. berizin dan diawasi oleh Badan  |\n");
    printf("\t\t\t|     Pusat Statistik dan Bank Indonesia(BI), serta merupakan    |\n");
    printf("\t\t\t|        peserta penjaminan Lembaga Penjamin Simpanan(LPS)       |\n");
    printf("\t\t\t|             Copyright © 2025 Bank SENTRAL STATISTIK            |\n");
    printf("\t\t\t|                                                                |\n");
    printf("\t\t\t+================================================================+\n");
   printf("\t\t\t Masukkan pilihan Anda : ");
    scanf("%d", &Nasabah.pilihan);
    if(Nasabah.pilihan == 1){
        printf("\t\t\t Mengalihkan layar");
        for(int i=0; i<3; i++){
            delay(100000000);
            printf(".");
        }
        system("cls");
        tampilanSubmenuTransfer();
    }
    else if(Nasabah.pilihan == 2){
        printf("\t\t\t Mengalihkan layar");
        for(int i=0; i<3; i++){
            delay(100000000);
            printf(".");
        }
        system("cls");
        tampilanSubmenuDigital();
    }
    else if(Nasabah.pilihan == 3){
        printf("\t\t\t Mengalihkan layar");
        for(int i=0; i<3; i++){
            delay(100000000);
            printf(".");
        }
        system("cls");
        tampilanSubmenuPemerintah();
    }
    else if(Nasabah.pilihan == 4){
        printf("\t\t\t Mengalihkan layar");
        for(int i=0; i<3; i++){
            delay(100000000);
            printf(".");
        }
        system("cls");
        tampilanInformasiAkun();
    }
    else if(Nasabah.pilihan == 5){
        printf("\t\t\t Mengalihkan layar");
        for(int i=0; i<3; i++){
            delay(100000000);
            printf(".");
        }
        system("cls");
        tampilanMenuAwal();
    }
    else{
        printf("\t\t\t Pilihan tidak dikenali!\n");
        printf("\t\t\t Ingin mengulangi program? (y/t) : ");
        scanf("%s", &Nasabah.pilihanInvalid);
        switch(Nasabah.pilihanInvalid){
        case 'Y' :
            system("cls");
            tampilanMenuAwal();
            break;
        case 'y' :
            system("cls");
            tampilanMenuAwal();
            break;
        default :
            system("pause");
            printf("\t\t\t Mengalihkan layar");
            for(int i=0; i<3; i++){
               delay(100000000);
               printf(".");
            }
            system("cls");
            firstPage();
            break;
        }
    }
}

void tampilanInfoAkun(){
    informasiDiri Nasabah;
    informasi2 Mekanisme;
    DATADIRI_FILE = fopen("DataNasabah.txt", "r");
    AKUN_FILE = fopen("DATAAKUN.txt", "r");
    if (DATADIRI_FILE == NULL ||AKUN_FILE == NULL) {
        printf("\t\t\t Gagal membuka file untuk menulis!\n");
        return;
    }
    else{
        fscanf(DATADIRI_FILE, "%s\n", &Nasabah.namaDepan);
        fscanf(DATADIRI_FILE, "%s\n", &Nasabah.namaBelakang);
        fscanf(DATADIRI_FILE, "%s\n", &Nasabah.NIK);
        fscanf(DATADIRI_FILE, "%[^\n]", &Nasabah.tempatLahir);
        fscanf(DATADIRI_FILE, "%d\n", &Nasabah.tanggalLahir);
        fscanf(DATADIRI_FILE, "%d\n", &Nasabah.bulanLahir);
        fscanf(DATADIRI_FILE, "%d\n", &Nasabah.tahunLahir);
        fscanf(DATADIRI_FILE, "%[^\n]", &Nasabah.alamat);
        fscanf(DATADIRI_FILE, "%s\n", &Nasabah.noHp);
        fscanf(DATADIRI_FILE, "%s\n", &Nasabah.email);
        fscanf(AKUN_FILE, "%s\n", &Nasabah.username);
        fscanf(AKUN_FILE, "%s\n", &Nasabah.password);
        fclose(DATADIRI_FILE);
        fclose(AKUN_FILE);
        system("CLS");
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                        [ mobiStats 5 ]                         |\n");
        printf("\t\t\t|                 << BANK SENTRAL STATISTIK >>                   |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t| Tanggal : %02d/%02d/%04d", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
        printf("                         Waktu : %02d:%02d WIB |\n", tm->tm_hour, tm->tm_min);
        printf("\t\t\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
        printf("\t\t\t|                      [DATA DIRI NASABAH]                       |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                                                                |\n");
        printf("\t\t\t| <<Nama Nasabah>>                                               |\n");
        printf("\t\t\t|   Nama Depan    : %-45s|\n", Nasabah.namaDepan);
        printf("\t\t\t|   Nama Belakang : %-45s|\n", Nasabah.namaBelakang);
        printf("\t\t\t|                                                                |\n");
        printf("\t\t\t| <<Data Kependudukan>>                                          |\n");
        printf("\t\t\t|   NIK           : %-45s|\n", Nasabah.NIK);
        printf("\t\t\t|   Tempat Lahir  : %-45s|\n", Nasabah.tempatLahir);
        printf("\t\t\t|   Tanggal Lahir : %-45d|\n", Nasabah.tanggalLahir);
        printf("\t\t\t|   Bulan Lahir   : %-45d|\n", Nasabah.bulanLahir);
        printf("\t\t\t|   Tahun Lahir   : %-45d|\n", Nasabah.tahunLahir);
        printf("\t\t\t|   Alamat        : %-45s|\n", Nasabah.alamat);
        printf("\t\t\t|   Nomor Telepon : %-45s|\n", Nasabah.noHp);
        printf("\t\t\t|   E-mail        : %-45s|\n", Nasabah.email);
        printf("\t\t\t|                                                                |\n");
        printf("\t\t\t| <<Akun Pengguna>>                                              |\n");
        printf("\t\t\t|   Username      : %-45s|\n", Nasabah.username);
        printf("\t\t\t|   Password      : %-45s|\n", Nasabah.password);
        printf("\t\t\t|                                                                |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t| PT BANK SENTRAL STATISTIK Tbk. berizin dan diawasi oleh Badan  |\n");
        printf("\t\t\t|     Pusat Statistik dan Bank Indonesia(BI), serta merupakan    |\n");
        printf("\t\t\t|        peserta penjaminan Lembaga Penjamin Simpanan(LPS)       |\n");
        printf("\t\t\t|             Copyright © 2025 Bank SENTRAL STATISTIK            |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t Ketik 1 untuk kembali ke menu sebelumnya: ");
        scanf("%d", &Mekanisme.pilihan);
        if(Mekanisme.pilihan == 1){
            printf("\t\t\t Mengalihkan layar");
            for(int i=0; i<3; i++){
                delay(100000000);
                printf(".");
            }
            system("cls");
            tampilanInformasiAkun();
            } else{
            printf("Pilihan tidak dikenali!\n");
            printf("Harap ketik 1 untuk kembali ke menu utama: ");
            scanf("%s", &Mekanisme.pilihanInvalid);
            switch(Mekanisme.pilihanInvalid){
            case '1' :
                system("cls");
                tampilanInformasiAkun();
                break;
            default :
                printf("\t\t\t Mengalihkan layar");
                for(int i=0; i<3; i++){
                   delay(100000000);
                   printf(".");
                }
                system("cls");
                tampilanMenuAwal();
                break;
            }
        }

    }
}
void tampilanSubmenuTransfer(){
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    informasiDiri Rekening;
    informasi2 Mekanisme;
    REKENING_FILE = fopen("DataRekeningNasabah.txt", "r");
    if(REKENING_FILE == NULL){
        printf("\t\t\t Rekening tidak terbaca!\n");
    }
    else{
        fscanf(REKENING_FILE, "%[^\n]", &Rekening.namaLengkap);
        fscanf(REKENING_FILE, "%s\n", &Rekening.NomorRekening);
        fclose(REKENING_FILE);
    }
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t|                        [ mobiStats 5 ]                         |\n");
    printf("\t\t\t|                 << BANK SENTRAL STATISTIK >>                   |\n");
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t||oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo||\n");
    printf("\t\t\t||--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--||\n");
    printf("\t\t\t||oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo||\n");
    printf("\t\t\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
    printf("\t\t\t| Nasabah   : %-51s|\n", Rekening.namaLengkap);
    printf("\t\t\t| Rekening  : %-51s|\n", Rekening.NomorRekening);
    printf("\t\t\t| Tanggal   = %02d/%02d/%d", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
    printf("\t\t Waktu layar = %02d:%02d WIB |\n", tm->tm_hour, tm->tm_min);
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t|                        SUBMENU TRANSFER                        |\n");
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t|                               ||                               |\n");
    printf("\t\t\t|     1. Setor Non-Tunai        ||     2. Tarik Non-Tunai        |\n");
    printf("\t\t\t|                               ||                               |\n");
    printf("\t\t\t|-------------------------------||-------------------------------|\n");
    printf("\t\t\t|                               ||                               |\n");
    printf("\t\t\t|     3. Transfer Bank          ||     4. Kembali Menu           |\n");
    printf("\t\t\t|                               ||                               |\n");
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t|                                                                |\n");
    printf("\t\t\t| PT BANK SENTRAL STATISTIK Tbk. berizin dan diawasi oleh Badan  |\n");
    printf("\t\t\t|     Pusat Statistik dan Bank Indonesia(BI), serta merupakan    |\n");
    printf("\t\t\t|        peserta penjaminan Lembaga Penjamin Simpanan(LPS)       |\n");
    printf("\t\t\t|             Copyright © 2025 Bank SENTRAL STATISTIK            |\n");
    printf("\t\t\t|                                                                |\n");
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t Masukkan pilihan layanan : ");
    scanf("%d", &Mekanisme.pilihan);
    if(Mekanisme.pilihan == 1){
        printf("\t\t\t Mengalihkan layar");
        for(int i=0; i<3; i++){
            delay(100000000);
            printf(".");
        }
        system("cls");
        tampilanSetorTunai();
    }
    else if(Mekanisme.pilihan == 2){
        printf("\t\t\t Mengalihkan layar");
        for(int i=0; i<3; i++){
            delay(100000000);
            printf(".");
        }
        system("cls");
        tampilanTarikTunai();
    }
    else if(Mekanisme.pilihan == 3){
        printf("\t\t\t Mengalihkan layar");
        for(int i=0; i<3; i++){
            delay(100000000);
            printf(".");
        }
        system("cls");
        tampilanTransferAntarBank();
    }
    else if(Mekanisme.pilihan == 4){
        printf("\t\t\t Mengalihkan layar");
        for(int i=0; i<3; i++){
            delay(100000000);
            printf(".");
        }
        system("cls");
        tampilanMenuUtama();
    }
    else{
        printf("\t\t\t Pilihan tidak dikenali!\n");
        printf("\t\t\t Ingin mengulangi program? (y/t) : ");
        scanf("%s", &Mekanisme.pilihanInvalid);
        switch(Mekanisme.pilihanInvalid){
        case 'Y' :
            system("cls");
            tampilanSubmenuTransfer();
            break;
        case 'y' :
            system("cls");
            tampilanSubmenuTransfer();
            break;
        default :
            system("pause");
            printf("\t\t\t Mengalihkan layar");
            for(int i=0; i<3; i++){
               delay(100000000);
               printf(".");
            }
            system("cls");
            tampilanMenuUtama();
            break;
        }
    }
}
void tampilanSetorTunai(){
    int Invalid = 0;
    char konfirmasiJawab;
    informasiDiri Rekening;
    informasi2 Mekanisme;
    Mekanisme.saldo = bacaSaldo();
    do{
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        REKENING_FILE = fopen("DataRekeningNasabah.txt", "r");
        if(REKENING_FILE == NULL){
            printf("\t\t\t Rekening tidak terbaca!\n");
        }
        else{
            fscanf(REKENING_FILE, "%[^\n]", &Rekening.namaLengkap);
            fscanf(REKENING_FILE, "%s\n", &Rekening.NomorRekening);
            fclose(REKENING_FILE);
        }
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                        [ mobiStats 5 ]                         |\n");
        printf("\t\t\t|                 << BANK SENTRAL STATISTIK >>                   |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t||oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo||\n");
        printf("\t\t\t||--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--||\n");
        printf("\t\t\t||oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo||\n");
        printf("\t\t\t||~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
        printf("\t\t\t| Nasabah   : %-51s|\n", Rekening.namaLengkap);
        printf("\t\t\t| Rekening  : %-51s|\n", Rekening.NomorRekening);
        printf("\t\t\t| Tanggal   = %02d/%02d/%d", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
        printf("\t\t Waktu layar = %02d:%02d WIB |\n", tm->tm_hour, tm->tm_min);
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                          SETOR NON-TUNAI                       |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                                                                |\n");
        printf("\t\t\t|                       Masukkan nominal setor.                  |\n");
        printf("\t\t\t|                                                                |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                                                                |\n");
        printf("\t\t\t| PT BANK SENTRAL STATISTIK Tbk. berizin dan diawasi oleh Badan  |\n");
        printf("\t\t\t|     Pusat Statistik dan Bank Indonesia(BI), serta merupakan    |\n");
        printf("\t\t\t|        peserta penjaminan Lembaga Penjamin Simpanan(LPS)       |\n");
        printf("\t\t\t|             Copyright © 2025 Bank SENTRAL STATISTIK            |\n");
        printf("\t\t\t|                                                                |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t Ingin membatalkan transaksi dan kembali ke menu sebelumnya? (Y/T): ");
        scanf("%s", &Mekanisme.batalTransaksi);
        getchar();
        if(Mekanisme.batalTransaksi == 'y' || Mekanisme.batalTransaksi == 'Y'){
            printf("\t\t\t Mengalihkan layar");
            for(int i=0; i<3; i++){
                delay(100000000);
                printf(".");
            }
            system("cls");
            tampilanSubmenuTransfer();
        }
        else if(Mekanisme.batalTransaksi == 't' || Mekanisme.batalTransaksi == 'T'){
            //lanjut
        }
        else{
            printf("\t\t\t Pilihan tidak dikenali!\n");
            printf("\t\t\t Apakah Anda ingin mengulangi? (y/t): ");
            scanf(" %c", &Mekanisme.pilihanInvalid);
            switch(Mekanisme.pilihanInvalid){
                case 'Y' :
                    system("cls");
                    tampilanSubmenuTransfer();
                    break;
                case 'y' :
                    system("cls");
                    tampilanSubmenuTransfer();
                    break;
                default :
                    printf("\t\t\t Mengalihkan layar");
                    for(int i=0; i<3; i++){
                        delay(100000000);
                        printf(".");
                    }
                    system("cls");
                    tampilanSubmenuTransfer();
                    break;
            }
        }
        printf("\t\t\t Masukkan nominal [Min 50000]  : ");
        scanf("%lf", &Mekanisme.nominal);
        if(Mekanisme.nominal<50000){
            printf("\t\t\t Nominal transaksi terlalu minimum! ");
            system("pause");
            for(int i=0; i<3; i++){
                delay(100000000);
                printf(".");
            }
            system("cls");
            continue;
        }
        getchar();
        printf("\t\t\t Keterangan [Max 25 karakter]  : ");
        gets(Mekanisme.keterangan);
        if(!validasiKeterangan){
            printf("\t\t\t Keterangan melebihi ketentuan!");
            system("pause");
            system("cls");
            continue;
        }
        printf("\t\t\t Masukkan pin Transaksi        : ");
        gets(Rekening.password);
        if(password(Rekening.password)){
            Invalid = 1;
        }
        else{
            printf("\t\t\t Pin Anda salah!\n");
            system("pause");
            printf("\t\t\t Mengembalikan layar");
            for(int i=0; i<3; i++){
                delay(100000000);
                printf(".");
            }
            system("cls");
            continue;
        }
        printf("\t\t\t Apakah Anda yakin ingin melakukan setor non-tunai (Y/T): ");
        scanf("%s", &Mekanisme.batalTransaksi);
        if(Mekanisme.batalTransaksi == 'Y' || Mekanisme.batalTransaksi == 'y'){
            printf("\t\t\t Menampilkan VA\n");
            Invalid = 1;
        }
        else if(Mekanisme.batalTransaksi == 'T' || Mekanisme.batalTransaksi == 't'){
            printf("\t\t\t Mengalihkan layar");
            for(int i=0; i<3; i++){
                delay(100000000);
                printf(".");
            }
            system("cls");
            tampilanSubmenuTransfer();
        }
        else{
            printf("\t\t\t Pilihan Anda invalid!");
            printf("\t\t\t Mengalihkan layar");
            for(int i=0; i<3; i++){
                delay(100000000);
                printf(".");
            }
            system("cls");
            tampilanSetorTunai();
        }
        Invalid = 1;
    }while(!Invalid);
    strcpy(Mekanisme.subKeterangan, "SETOR NON-TUNAI");
    strcpy(Mekanisme.subtitute, "SETOR");
    Mekanisme.saldo = bacaSaldo();
    Mekanisme.saldo += Mekanisme.nominal;
    Mekanisme.kodeVa = 2;
    strcpy(Mekanisme.vaSetor, generatorKodeSetor());
    printf("\t\t\t Mengalihkan layar");
    for(int i=0; i<3; i++){
        delay(100000000);
        printf(".");
    }
    system("cls");
    tampilanVASetorTarik(Mekanisme.subKeterangan, Mekanisme.subtitute, Mekanisme.kodeVa, Mekanisme.nominal, Mekanisme.keterangan, Mekanisme.saldo, Mekanisme.vaSetor);
}
void tampilanTarikTunai() {
    int inputValid = 0;
    char konfirmasiJawab;
    informasiDiri Rekening;
    informasi2 Mekanisme;
    do {
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        REKENING_FILE = fopen("DataRekeningNasabah.txt", "r");
        if (REKENING_FILE == NULL) {
            printf("\t\t\t Rekening tidak terbaca!\n");
        } else {
            fscanf(REKENING_FILE, "%[^\n]", &Rekening.namaLengkap);
            fscanf(REKENING_FILE, "%s\n", &Rekening.NomorRekening);
            fclose(REKENING_FILE);
        }
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                        [ mobiStats 5 ]                         |\n");
        printf("\t\t\t|                 << BANK SENTRAL STATISTIK >>                   |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t||oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo||\n");
        printf("\t\t\t||--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--||\n");
        printf("\t\t\t||oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo||\n");
        printf("\t\t\t||~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
        printf("\t\t\t| Nasabah   : %-51s|\n", Rekening.namaLengkap);
        printf("\t\t\t| Rekening  : %-51s|\n", Rekening.NomorRekening);
        printf("\t\t\t| Tanggal   = %02d/%02d/%d", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
        printf("\t\t Waktu layar = %02d:%02d WIB |\n", tm->tm_hour, tm->tm_min);
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                         TARIK NON-TUNAI                        |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                                                                |\n");
        printf("\t\t\t|                      Masukkan nominal tarik.                   |\n");
        printf("\t\t\t|                                                                |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                                                                |\n");
        printf("\t\t\t| PT BANK SENTRAL STATISTIK Tbk. berizin dan diawasi oleh Badan  |\n");
        printf("\t\t\t|     Pusat Statistik dan Bank Indonesia(BI), serta merupakan    |\n");
        printf("\t\t\t|        peserta penjaminan Lembaga Penjamin Simpanan(LPS)       |\n");
        printf("\t\t\t|             Copyright © 2025 Bank SENTRAL STATISTIK            |\n");
        printf("\t\t\t|                                                                |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t Ingin membatalkan transaksi dan kembali ke menu sebelumnya? (Y/T): ");
        scanf("%s", &Mekanisme.batalTransaksi);
        getchar();
        if (Mekanisme.batalTransaksi == 'y' || Mekanisme.batalTransaksi == 'Y') {
            printf("\t\t\t Mengalihkan layar");
            for (int i = 0; i < 3; i++) {
                delay(100000000);
                printf(".");
            }
            system("cls");
            tampilanSubmenuTransfer();
        } else if (Mekanisme.batalTransaksi == 't' || Mekanisme.batalTransaksi == 'T') {
            // lanjut proses
        } else {
            printf("\t\t\t Pilihan tidak dikenali!\n");
            printf("\t\t\t Apakah Anda ingin mengulangi? (y/t): ");
            scanf("%c", &Mekanisme.pilihanInvalid);
            switch (Mekanisme.pilihanInvalid) {
                case 'Y':
                case 'y':
                    system("cls");
                    tampilanSubmenuTransfer();
                    break;
                default:
                    printf("\t\t\t Mengalihkan layar");
                    for (int i = 0; i < 3; i++) {
                        delay(100000000);
                        printf(".");
                    }
                    system("cls");
                    tampilanSubmenuTransfer();
                    break;
            }
        }
        printf("\t\t\t Masukkan nominal [Min 50000]  : ");
        scanf("%lf", &Mekanisme.nominal);
        if (Mekanisme.nominal < 50000) {
            printf("\t\t\t Nominal transaksi terlalu minimum!\n");
            system("pause");
            for (int i = 0; i < 3; i++) {
                delay(1000000000);
                printf(".");
            }
            system("cls");
            continue;
        }
        getchar();
        printf("\t\t\t Keterangan [Max 25 karakter]  : ");
        gets(Mekanisme.keterangan);
        if (!validasiKeterangan) {
            printf("\t\t\t Keterangan melebihi ketentuan!");
            system("pause");
            system("cls");
            continue;
        }
        printf("\t\t\t Masukkan pin Transaksi        : ");
        gets(Rekening.password);
        if (password(Rekening.password)) {
            printf("\t\t\t Apakah Anda yakin ingin melakukan tarik non-tunai (Y/T): ");
            scanf("%s", &Mekanisme.batalTransaksi);
            if (Mekanisme.batalTransaksi == 'Y' || Mekanisme.batalTransaksi == 'y') {
                if (validasiSaldo(Mekanisme.nominal)) {
                    printf("\t\t\t Menampilkan VA\n");
                    inputValid = 1;
                } else {
                    printf("\t\t\t Maaf, saldo Anda tidak mencukupi untuk bertransaksi!\n");
                    system("pause");
                    printf("\t\t\t Mengembalikan layar");
                    for (int i = 0; i < 3; i++) {
                        delay(100000000);
                        printf(".");
                    }
                    system("cls");
                    tampilanSubmenuTransfer();
                }
            } else if (Mekanisme.batalTransaksi == 'T' || Mekanisme.batalTransaksi == 't') {
                printf("\t\t\t Mengalihkan layar");
                for (int i = 0; i < 3; i++) {
                    delay(100000000);
                    printf(".");
                }
                system("cls");
                tampilanSubmenuTransfer();
            } else {
                printf("\t\t\t Pilihan Anda invalid!");
                printf("\t\t\t Mengalihkan layar");
                for (int i = 0; i < 3; i++) {
                    delay(100000000);
                    printf(".");
                }
                system("cls");
                tampilanTarikTunai();
            }
        } else {
            printf("\t\t\t Pin Anda salah!\n");
            system("pause");
            printf("\t\t\t Mengembalikan layar");
            for (int i = 0; i < 3; i++) {
                delay(100000000);
                printf(".");
            }
            system("cls");
            continue;
        }
        inputValid = 1;
    } while (!inputValid);
    strcpy(Mekanisme.subKeterangan, "TARIK NON-TUNAI");
    strcpy(Mekanisme.subtitute, "TARIK");
    Mekanisme.saldo = bacaSaldo();
    Mekanisme.saldo -= Mekanisme.nominal;
    Mekanisme.kodeVa = 5;
    strcpy(Mekanisme.vaTarik, generatorKodeTarik());
    printf("\t\t\t Mengalihkan layar");
    for (int i = 0; i < 3; i++) {
        delay(100000000);
        printf(".");
    }
    system("cls");
    tampilanVASetorTarik(Mekanisme.subKeterangan, Mekanisme.subtitute, Mekanisme.kodeVa, Mekanisme.nominal, Mekanisme.keterangan, Mekanisme.saldo, Mekanisme.vaTarik);
}
void tampilanVASetorTarik(const char *keterangan, char *subtitute, int kodeVA, double nominal, const char *keteranganAkhir, double saldo, char *vaSetorTarik){
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    informasi2 Mekanisme;
    informasiDiri Rekening;
    int valid = 0;
    REKENING_FILE = fopen("DataRekeningNasabah.txt", "r");
    if (REKENING_FILE == NULL) {
        printf("\t\t\t Rekening tidak terbaca!\n");
    } else {
        fscanf(REKENING_FILE, "%[^\n]", &Rekening.namaLengkap);
        fscanf(REKENING_FILE, "%s\n", &Rekening.NomorRekening);
        fclose(REKENING_FILE);
    }
    do{
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t|                        [ mobiStats 5 ]                         |\n");
    printf("\t\t\t|                 << BANK SENTRAL STATISTIK >>                   |\n");
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t|                     >> %s <<                      |\n", keterangan);
    printf("\t\t\t| Tanggal : %02d/%02d/%04d", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
    printf("                         Waktu : %02d:%02d WIB |\n", tm->tm_hour, tm->tm_min);
    printf("\t\t\t+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n");
    printf("\t\t\t| Nama Nasabah : %-48s|\n", Rekening.namaLengkap);
    printf("\t\t\t| Rekening     : %-48s|\n", Rekening.NomorRekening);
    printf("\t\t\t|                                                                |\n");
    printf("\t\t\t| Kode VA      : %-48s|\n", vaSetorTarik);
    printf("\t\t\t| Nominal%6s: Rp%-46.2lf|\n", subtitute, nominal);
    printf("\t\t\t|                                                                |\n");
    printf("\t\t\t+----------------------------------------------------------------+\n");
    printf("\t\t\t+----------------------------------------------------------------+\n");
    printf("\t\t\t| Informasi!                                                     |\n");
    printf("\t\t\t| %-6ssejumlah uang ke ATM/Bank Sentral Statistik              |\n", subtitute);
    printf("\t\t\t| Kode %-6smerupakan angka unik yang diawali [0%d0-]            |\n", subtitute, kodeVA);
    printf("\t\t\t| Terima kasih atas penggunaan layanan                           |\n");
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t Ingin melanjutkan ke menu selanjutnya? (y/t) : ");
    scanf("%s", &Mekanisme.batalTransaksi);
    if(Mekanisme.batalTransaksi =='Y'||Mekanisme.batalTransaksi=='y'){
        valid =1;
    }
    else if(Mekanisme.batalTransaksi =='T'||Mekanisme.batalTransaksi =='t'){
        printf("\t\t\t Mengalihkan layar");
        for(int i=0; i<3; i++){
            delay(100000000);
            printf(".");
        }
        system("cls");
        tampilanSetorTunai();
    }
    else{
        printf("\t\t\t Pilihan tidak valid! ");
        system("cls");
        for(int i=0; i<3; i++){
            delay(100000000);
            printf(".");
        }
        system("cls");
        continue;
    }
    valid = 1;
    }while(!valid);
    simpanPerbaruiSaldo(saldo);
    strcpy(Mekanisme.jenisTransaksi, "Layanan Transfer [Setor]");
    strcpy(Mekanisme.tipeTransaksi, "Tabung");
    strcpy(Mekanisme.nomorTransaksi, generatorRandNum());
    strcpy(Mekanisme.kodeTransaksi, generatorUnCode());
    strcpy(Mekanisme.tujuanTransaksi, "Pribadi");
    strcpy(Mekanisme.tujuanTambahan, "");
    Mekanisme.biayaAdmin = 0;
    Mekanisme.total = nominal + Mekanisme.biayaAdmin;
    SimpanTransaksiKeFile(Mekanisme.total, keteranganAkhir, Mekanisme.kodeTransaksi, Mekanisme.jenisTransaksi, Mekanisme.tipeTransaksi);
    printf("\t\t\t Mengalihkan layar");
    for(int i=0; i<3; i++){
        delay(100000000);
        printf(".");
    }
    system("cls");
    tampilanStruk(Mekanisme.nomorTransaksi, Mekanisme.jenisTransaksi, Mekanisme.kodeTransaksi, Mekanisme.tujuanTransaksi, Mekanisme.tujuanTambahan, Mekanisme.biayaAdmin, Mekanisme.nominal, Mekanisme.total, keteranganAkhir);
}
void tampilanTransferAntarBank() {
    int inputValid = 0;
    char konfirmasiJawab;
    informasiDiri Rekening;
    informasi2 Mekanisme;
    int jumlahData = sizeof(database)/sizeof(database[0]);
    REKENING_FILE = fopen("DataRekeningNasabah.txt", "r");
    if (REKENING_FILE == NULL) {
        printf("\t\t\t Data rekening tidak ditemukan!\n");
    } else {
        fscanf(REKENING_FILE, "%[^\n]", Rekening.namaLengkap);
        fscanf(REKENING_FILE, "%s", Rekening.NomorRekening);
    }
    do {
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                   [ Transfer ke rekening ]                     |\n");
        printf("\t\t\t|                 << BANK SENTRAL STATISTIK >>                   |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                     $$$$$ $$$$$ $  $$$$$                       |\n");
        printf("\t\t\t|                    $        $   $ $                            |\n");
        printf("\t\t\t|                     $$$$    $   $  $$$$                        |\n");
        printf("\t\t\t|                         $   $   $      $                       |\n");
        printf("\t\t\t|                    $$$$$    $   $ $$$$$                        |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t+                 [ Kode transfer antar Bank ]                   +\n");
        printf("\t\t\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
        printf("\t\t\t|                                                                |\n");
        printf("\t\t\t|                 1. Bank Sentral Statistik : 22xxxxxxx          |\n");
        printf("\t\t\t|                                                                |\n");
        printf("\t\t\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
        printf("\t\t\t|                                                                |\n");
        printf("\t\t\t|                 2. Bank Max Power         : 21xxxxxxx          |\n");
        printf("\t\t\t|                                                                |\n");
        printf("\t\t\t|----------------------------------------------------------------|\n");
        printf("\t\t\t|                                                                |\n");
        printf("\t\t\t|                 3. Bank Alprosional       : 11xxxxxxx          |\n");
        printf("\t\t\t|                                                                |\n");
        printf("\t\t\t|----------------------------------------------------------------|\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                                                                |\n");
        printf("\t\t\t| PT BANK SENTRAL STATISTIK Tbk. berizin dan diawasi oleh Badan  |\n");
        printf("\t\t\t|     Pusat Statistik dan Bank Indonesia(BI), serta merupakan    |\n");
        printf("\t\t\t|        peserta penjaminan Lembaga Penjamin Simpanan(LPS)       |\n");
        printf("\t\t\t|             Copyright © 2025 Bank SENTRAL STATISTIK            |\n");
        printf("\t\t\t|                                                                |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t Ingin membatalkan transaksi dan kembali ke menu sebelumnya? (Y/T): ");
        scanf("%s", &Mekanisme.batalTransaksi);
        getchar();
        if (Mekanisme.batalTransaksi == 'y' || Mekanisme.batalTransaksi == 'Y') {
            printf("\t\t\t Mengalihkan layar");
            for (int i = 0; i < 3; i++) {
                delay(100000000);
                printf(".");
            }
            system("cls");
            tampilanSubmenuTransfer();
        } else if (Mekanisme.batalTransaksi == 't' || Mekanisme.batalTransaksi == 'T') {
            // Lanjut ke proses
        } else {
            printf("\t\t\t Pilihan tidak dikenali!\n");
            printf("\t\t\t Apakah Anda ingin mengulangi? (y/t): ");
            scanf(" %c", &Mekanisme.pilihanInvalid);
            switch (Mekanisme.pilihanInvalid) {
                case 'Y':
                case 'y':
                    printf("\t\t\t Mengalihkan layar");
                    for (int i = 0; i < 3; i++) {
                        delay(100000000);
                        printf(".");
                    }
                    system("cls");
                    tampilanTransferAntarBank();
                    break;
                case 'T':
                case 't':
                    printf("\t\t\t Mengalihkan layar");
                    for (int i = 0; i < 3; i++) {
                        delay(100000000);
                        printf(".");
                    }
                    system("cls");
                    tampilanSubmenuTransfer();
                    break;
                default:
                    printf("\t\t\t Mengalihkan layar");
                    for (int i = 0; i < 3; i++) {
                        delay(100000000);
                        printf(".");
                    }
                    system("cls");
                    tampilanTransferAntarBank();
                    break;
            }
        }
        printf("\t\t\t No.Rekening tidak boleh pribadi atau selain Kode Rekening yang tersedia diatas!\n");
        printf("\t\t\t Masukkan nomor rekening tujuan (9 digit): ");
        scanf("%s", &Mekanisme.noRekeningTujuan);
        getchar();
        if (strcmp(Mekanisme.noRekeningTujuan, Rekening.NomorRekening) == 0) {
            printf("\n\t\t\t Tidak diperkenankan transfer ke rekening pribadi! ");
            system("pause");
            printf("\t\t\t Mengembalikan layar");
            for (int i = 0; i <3; i++) {
                delay(100000000);
                printf(".");
            }
            system("cls");
            continue;
        }
        if (strlen(Mekanisme.noRekeningTujuan) != 9) {
            printf("\n\t\t\t Nomor rekening tidak sesuai ketentuan! ");
            system("pause");
            printf("\t\t\t Mengembalikan layar");
            for (int i = 0; i <3; i++) {
                delay(100000000);
                printf(".");
            }
            system("cls");
            continue;
        }
        if ((strncmp(Mekanisme.noRekeningTujuan, "21", 2)!=0)&&(strncmp(Mekanisme.noRekeningTujuan, "22", 2)!=0)&&(strncmp(Mekanisme.noRekeningTujuan, "11", 2)!=0)) {
            printf("\n\t\t\t Kode rekening tidak dikenali! ");
            system("pause");
            printf("\t\t\t Mengembalikan layar");
            for (int i = 0; i < 3; i++) {
                delay(100000000);
                printf(".");
            }
            system("cls");
            continue;
        }
        int ketemu =0;
        for (int i =0; i<jumlahData; i++) {
            if (strcmp(Mekanisme.noRekeningTujuan, database[i].norek)==0) {
                printf("\n\t\t\t Penerima : %s\n", database[i].nama);
                strcpy(Mekanisme.tujuanTransaksi, database[i].nama);
                strcpy(Mekanisme.tujuanTambahan, database[i].norek);
                ketemu = 1;
                break;
            }
        }
        if (!ketemu) {
            printf("\t\t\t Nama penerima tidak ditemukan! ");
            system("pause");
            printf("\t\t\t Mengembalikan layar");
            for (int i = 0; i <3; i++) {
                delay(100000000);
                printf(".");
            }
            system("cls");
            continue;
        }
        printf("\t\t\t Masukkan nominal setor         : ");
        scanf("%lf", &Mekanisme.nominal);
        getchar();
        if (Mekanisme.nominal < 10000) {
            printf("\t\t\t Nominal transaksi terlalu minimum!\n");
            system("pause");
            for (int i = 0; i < 3; i++) {
                delay(1000000000);
                printf(".");
            }
            system("cls");
            continue;
        }
        printf("\t\t\t Keterangan                     : ");
        gets(Mekanisme.keterangan);
        if (!validasiKeterangan) {
            printf("\t\t\t Keterangan melebihi ketentuan!");
            system("pause");
            system("cls");
            continue;
        }
        printf("\t\t\t Masukkan pin Transaksi         : ");
        scanf("%s", &Rekening.pinTransaksi);
        getchar();
        if (password(Rekening.pinTransaksi)) {
            printf("\t\t\t Apakah Anda yakin ingin melakukan transaksi (Y/T): ");
            scanf("%s", &Mekanisme.batalTransaksi);
            if (Mekanisme.batalTransaksi == 'Y' || Mekanisme.batalTransaksi == 'y') {
                if (validasiSaldo(Mekanisme.nominal)) {
                    printf("\t\t\t Menampilkan Struk ");
                    for(int i=0; i<3; i++){
                       delay(100000000);
                       printf(".");
                     }
                    system("cls");
                    inputValid = 1;
                } else {
                    printf("\t\t\t Maaf, saldo Anda tidak mencukupi untuk bertransaksi!\n");
                    system("pause");
                    printf("\t\t\t Mengembalikan layar");
                    for (int i = 0; i < 3; i++) {
                        delay(100000000);
                        printf(".");
                    }
                    system("cls");
                    tampilanSubmenuTransfer();
                }
            } else if (Mekanisme.batalTransaksi == 'T' || Mekanisme.batalTransaksi == 't') {
                printf("\t\t\t Mengalihkan layar");
                for (int i = 0; i < 3; i++) {
                    delay(100000000);
                    printf(".");
                }
                system("cls");
                tampilanSubmenuTransfer();
            } else {
                printf("\t\t\t Pilihan Anda invalid!");
                printf("\t\t\t Mengalihkan layar");
                for (int i = 0; i < 3; i++) {
                    delay(100000000);
                    printf(".");
                }
                system("cls");
                continue;
            }
        } else {
            printf("\t\t\t Pin Anda salah!\n");
            system("pause");
            printf("\t\t\t Mengembalikan layar");
            for (int i = 0; i < 3; i++) {
                delay(100000000);
                printf(".");
            }
            system("cls");
            continue;
        }
        inputValid = 1;
    } while (!inputValid);
    Mekanisme.saldo = bacaSaldo();
    Mekanisme.biayaAdmin = nilaiAdminTransfer(Mekanisme.noRekeningTujuan);
    Mekanisme.total = Mekanisme.biayaAdmin + Mekanisme.nominal;
    Mekanisme.saldo -= Mekanisme.total;
    strcpy(Mekanisme.kodeTransaksi, generatorUnCode());
    strcpy(Mekanisme.nomorTransaksi, generatorRandNum());
    strcpy(Mekanisme.jenisTransaksi, "Layanan Transfer");
    strcpy(Mekanisme.tipeTransaksi, "Outward Fund");
    simpanPerbaruiSaldo(Mekanisme.saldo);
    SimpanTransaksiKeFile(Mekanisme.total, Mekanisme.keterangan, Mekanisme.kodeTransaksi, Mekanisme.jenisTransaksi, Mekanisme.tipeTransaksi);
    tampilanStruk(Mekanisme.nomorTransaksi, Mekanisme.jenisTransaksi, Mekanisme.kodeTransaksi, Mekanisme.tujuanTransaksi, Mekanisme.tujuanTambahan, Mekanisme.biayaAdmin, Mekanisme.nominal, Mekanisme.total, Mekanisme.keterangan);
}
void tampilanSubmenuDigital(){
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    informasiDiri Rekening;
    informasi2 Mekanisme;
    REKENING_FILE = fopen("DataRekeningNasabah.txt", "r");
    if(REKENING_FILE == NULL){
        printf("\t\t\t Rekening tidak terbaca!\n");
    }
    else{
        fscanf(REKENING_FILE, "%[^\n]", &Rekening.namaLengkap);
        fscanf(REKENING_FILE, "%s\n", &Rekening.NomorRekening);
        fclose(REKENING_FILE);
    }
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                        [ mobiStats 5 ]                         |\n");
        printf("\t\t\t|                 << BANK SENTRAL STATISTIK >>                   |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t||oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo||\n");
        printf("\t\t\t||--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--||\n");
        printf("\t\t\t||oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo||\n");
        printf("\t\t\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
        printf("\t\t\t| Nasabah  : %-52s|\n", Rekening.namaLengkap);
        printf("\t\t\t| Rekening : %-52s|\n", Rekening.NomorRekening);
        printf("\t\t\t| Tanggal  = %02d/%02d/%d", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
        printf("\t\t\t Waktu layar = %02d:%02d WIB |\n", tm->tm_hour, tm->tm_min);
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                        SUBMENU DIGITAL                         |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                               ||                               |\n");
        printf("\t\t\t|      1. Top-Up E-Wallet       ||      2. Top-Up E-Money        |\n");
        printf("\t\t\t|                               ||                               |\n");
        printf("\t\t\t|-------------------------------||-------------------------------|\n");
        printf("\t\t\t|                               ||                               |\n");
        printf("\t\t\t|      3. Top-Up Pulsa          ||      4. Kembali               |\n");
        printf("\t\t\t|                               ||                               |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                                                                |\n");
        printf("\t\t\t| PT BANK SENTRAL STATISTIK Tbk. berizin dan diawasi oleh Badan  |\n");
        printf("\t\t\t|     Pusat Statistik dan Bank Indonesia(BI), serta merupakan    |\n");
        printf("\t\t\t|        peserta penjaminan Lembaga Penjamin Simpanan(LPS)       |\n");
        printf("\t\t\t|             Copyright © 2025 Bank SENTRAL STATISTIK            |\n");
        printf("\t\t\t|                                                                |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t Masukkan pilihan layanan : ");
        scanf("%d", &Mekanisme.pilihan);
        if (Mekanisme.pilihan == 1){
            printf("\t\t\t Mengalihkan layar");
            for(int i=0; i<3; i++){
                delay(100000000);
                printf(".");
        }
        system("cls");
        tampilanTopUpEWallet();
        } else if (Mekanisme.pilihan == 2){
            printf("\t\t\t Mengalihkan layar");
            for(int i=0; i<3; i++){
                delay(100000000);
                printf(".");
            }
        system("cls");
        tampilanTopUpEMoney();
        } else if (Mekanisme.pilihan == 3){
            printf("\t\t\t Mengalihkan layar");
            for(int i=0; i<3; i++){
                delay(100000000);
                printf(".");
            }
        system("cls");
        tampilanTopUpPulsa();
        } else if( Mekanisme.pilihan == 4){
            printf("\t\t\t Mengalihkan layar");
            for(int i=0; i<3; i++){
                delay(100000000);
                printf(".");
            }
        system("cls");
        tampilanMenuUtama();
        } else {
            printf("\t\t\t Pilihan tidak dikenali!\n");
            printf("\t\t\t Ingin mengulangi program? (y/t) : ");
            scanf("%s", &Mekanisme.pilihanInvalid);
            switch(Mekanisme.pilihanInvalid){
            case 'Y' :
            system("cls");
            tampilanSubmenuDigital();
            break;
            case 'y' :
            system("cls");
            tampilanSubmenuDigital();
            break;
            default :
            printf("\t\t\t Mengalihkan layar");
            for(int i=0; i<3; i++){
               delay(100000000);
               printf(".");
            }
            system("cls");
            tampilanMenuUtama();
            break;
            }
        }
}

void tampilanTopUpEWallet(){
    int invalid = 0;
    char konfirmasiJawab;
    informasiDiri Rekening;
    informasi2 Mekanisme;
    Mekanisme.saldo = bacaSaldo();
    do{
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        REKENING_FILE = fopen("DataRekeningNasabah.txt", "r");
        if(REKENING_FILE == NULL){
            printf("\t\t\t Rekening tidak terbaca!\n");
        }
        else{
            fscanf(REKENING_FILE, "%[^\n]", &Rekening.namaLengkap);
            fscanf(REKENING_FILE, "%s\n", &Rekening.NomorRekening);
            fclose(REKENING_FILE);
        }
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                        [ mobiStats 5 ]                         |\n");
        printf("\t\t\t|                 << BANK SENTRAL STATISTIK >>                   |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t||oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo||\n");
        printf("\t\t\t||--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--||\n");
        printf("\t\t\t||oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo||\n");
        printf("\t\t\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
        printf("\t\t\t| Nasabah  : %-52s|\n", Rekening.namaLengkap);
        printf("\t\t\t| Rekening : %-52s|\n", Rekening.NomorRekening);
        printf("\t\t\t| Tanggal  = %02d/%02d/%d", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
        printf("\t\t\t Waktu layar = %02d:%02d WIB |\n", tm->tm_hour, tm->tm_min);
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                    [ Kode Top-Up E-Wallet ]                    |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                               ||                               |\n");
        printf("\t\t\t|        1. Gofir  : 60737      ||        2. Gemoy: 89588        |\n");
        printf("\t\t\t|                               ||                               |\n");
        printf("\t\t\t|----------------------------------------------------------------|\n");
        printf("\t\t\t|                               ||                               |\n");
        printf("\t\t\t|        3. Danong : 89508      ||        4. OPO  : 60001        |\n");
        printf("\t\t\t|                               ||                               |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                                                                |\n");
        printf("\t\t\t| PT BANK SENTRAL STATISTIK Tbk. berizin dan diawasi oleh Badan  |\n");
        printf("\t\t\t|     Pusat Statistik dan Bank Indonesia(BI), serta merupakan    |\n");
        printf("\t\t\t|        peserta penjaminan Lembaga Penjamin Simpanan(LPS)       |\n");
        printf("\t\t\t|             Copyright © 2025 Bank SENTRAL STATISTIK            |\n");
        printf("\t\t\t|                                                                |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t Ingin membatalkan transaksi dan kembali ke menu sebelumnya? (Y/T): ");
        scanf("%s", &Mekanisme.batalTransaksi);
        getchar();
        if(Mekanisme.batalTransaksi == 'y' || Mekanisme.batalTransaksi == 'Y'){
            printf("\t\t\t Mengalihkan layar");
            for(int i=0; i<3; i++){
                delay(100000000);
                printf(".");
            }
            system("cls");
            tampilanSubmenuDigital();
        }
        else if(Mekanisme.batalTransaksi == 't' || Mekanisme.batalTransaksi == 'T'){
        }
        else {
            printf("\t\t\t Pilihan tidak dikenali!\n");
            printf("\t\t\t Apakah Anda ingin mengulangi? (y/t): ");
            scanf(" %c", &Mekanisme.pilihanInvalid);
            switch(Mekanisme.pilihanInvalid){
                case 'Y' :
                    system("cls");
                    tampilanSubmenuDigital();
                    break;
                case 'y' :
                    system("cls");
                    tampilanSubmenuDigital();
                    break;
                default :
                    printf("\t\t\t Mengalihkan layar");
                    for(int i=0; i<3; i++){
                        delay(100000000);
                        printf(".");
                    }
                    system("cls");
                    tampilanMenuUtama();
                    break;
            }
        }
        printf("\t\t\t Contoh: 60737085876100162\n");
        printf("\t\t\t Masukkan kode E-Wallet + No HP: ");
        scanf("%s", &Mekanisme.kodeEWallet);
        char jenis;
        if (strncmp(Mekanisme.kodeEWallet, "60737", 5) == 0) {
            strcpy(Mekanisme.jenisEWallet, "Gofir");
        } else if (strncmp(Mekanisme.kodeEWallet, "89588", 5) == 0) {
            strcpy(Mekanisme.jenisEWallet, "Gemoy");
        } else if (strncmp(Mekanisme.kodeEWallet, "89508", 5) == 0) {
            strcpy(Mekanisme.jenisEWallet, "Danong");
        } else if (strncmp(Mekanisme.kodeEWallet, "60001", 5) == 0) {
            strcpy(Mekanisme.jenisEWallet, "OPO");
        } else {
            printf("\n\t\t\t Layanan E-Wallet tidak tersedia!\n");
            printf("\n\t\t\t Ingin mengulangi transaksi? (y/t) : ");
            scanf("%s", &Mekanisme.pilihanInvalid);
            switch(Mekanisme.pilihanInvalid){
            case 'Y' :
                system("cls");
                tampilanTopUpEWallet();
                break;
            case 'y' :
                system("cls");
                tampilanTopUpEWallet();
                break;
            default :
                printf("\t\t\t Mengalihkan layar");
                for(int i=0; i<3; i++){
                delay(100000000);
                printf(".");
                }
                system("cls");
                tampilanSubmenuDigital();
                break;
            }
        }
        printf("\n");
        printf("\t\t\t Anda memilih : %s\n", Mekanisme.jenisEWallet);
        int n = strlen(Mekanisme.kodeEWallet)-4;
        strcpy(Mekanisme.noTelepon, ambilNoHp(Mekanisme.kodeEWallet, n));
        printf("%s\n", Mekanisme.noTelepon);
        printf("\n");
        printf("\t\t\t Masukkan nominal top up (minimal 10000): ");
        scanf("%lf", &Mekanisme.nominal);
        if (Mekanisme.nominal < 10000){
            printf("\t\t\t Nominal minimal top-up E-Wallet adalah 10000.\n");
            printf("\t\t\t Ingin mengulangi transaksi?(Y/T): ");
            scanf("%s", &Mekanisme.batalTransaksi);
            switch(Mekanisme.pilihanInvalid){
                case 'Y' :
                    system("cls");
                    break;
                case 'y' :
                    system("cls");
                    break;
                default :
                    printf("\t\t\t Mengalihkan layar");
                    for(int i=0; i<3; i++){
                       delay(100000000);
                       printf(".");
                    }
                    system("cls");
                    tampilanSubmenuDigital();
                    break;
                }
            }else{
        }
        getchar();
        printf("\t\t\t Keterangan [Max 25 karakter]  : ");
        gets(Mekanisme.keterangan);
        if(!validasiKeterangan){
            printf("\t\t\t Keterangan melebihi ketentuan!");
            system("pause");
            system("cls");
            continue;
        }
        printf("\t\t\t Masukkan pin transaksi        : ");
        gets(Rekening.password);
        if(password(Rekening.password)){
            invalid = 1;
        }
        else{
            printf("\t\t\t Pin Anda salah!\n");
            system("pause");
            printf("\t\t\t Mengembalikan layar");
            for(int i=0; i<3; i++){
                delay(100000000);
                printf(".");
            }
            system("cls");
            continue;
        }
        printf("\t\t\t Apakah Anda yakin ingin melakukan transaksi (Y/T): ");
        scanf("%s", &Mekanisme.batalTransaksi);
            switch(Mekanisme.batalTransaksi){
                case 'Y' :
                    system("cls");
                    invalid = 1;
                    break;
                case 'y' :
                    system("cls");
                    invalid = 1;
                    break;
                default :
                    printf("\t\t\t Mengalihkan layar");
                    for(int i=0; i<3; i++){
                       delay(100000000);
                       printf(".");
                    }
                    system("cls");
                    tampilanSubmenuDigital();
                    break;
                }
            invalid=1;
        }while(!invalid);
        system("cls");
        strcpy(Mekanisme.jenisTransaksi, "Layanan Digital [Top-Up]");
        strcpy(Mekanisme.tipeTransaksi, "E-Wallet");
        strcpy(Mekanisme.nomorTransaksi, generatorRandNum());
        strcpy(Mekanisme.kodeTransaksi, generatorUnCode());
        strcpy(Mekanisme.tujuanTransaksi, "Transaksi Digital - ");
        strcat(Mekanisme.tujuanTransaksi, Mekanisme.jenisEWallet);
        strcpy(Mekanisme.tujuanTambahan, Mekanisme.noTelepon);
        Mekanisme.biayaAdmin = 1500;
        Mekanisme.total = Mekanisme.nominal + Mekanisme.biayaAdmin;
        Mekanisme.saldo -= Mekanisme.total;
        simpanPerbaruiSaldo(Mekanisme.saldo);
        SimpanTransaksiKeFile(Mekanisme.total, Mekanisme.keterangan, Mekanisme.kodeTransaksi, Mekanisme.jenisTransaksi, Mekanisme.tipeTransaksi);
        tampilanStruk(Mekanisme.nomorTransaksi, Mekanisme.jenisTransaksi, Mekanisme.kodeTransaksi, Mekanisme.tujuanTransaksi, Mekanisme.tujuanTambahan, Mekanisme.biayaAdmin, Mekanisme.nominal, Mekanisme.total, Mekanisme.keterangan);
}
void tampilanTopUpEMoney(){
    int invalid = 0;
    char konfirmasiJawab;
    informasiDiri Rekening;
    informasi2 Mekanisme;
    Mekanisme.saldo = bacaSaldo();
    do{
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        REKENING_FILE = fopen("DataRekeningNasabah.txt", "r");
        if(REKENING_FILE == NULL){
        printf("\t\t\t Rekening tidak terbaca!\n");

        }else{
        fscanf(REKENING_FILE, "%[^\n]", &Rekening.namaLengkap);
        fscanf(REKENING_FILE, "%s\n", &Rekening.NomorRekening);
        fclose(REKENING_FILE);
        }
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                        [ mobiStats 5 ]                         |\n");
        printf("\t\t\t|                 << BANK SENTRAL STATISTIK >>                   |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t||oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo||\n");
        printf("\t\t\t||--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--||\n");
        printf("\t\t\t||oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo||\n");
        printf("\t\t\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
        printf("\t\t\t| Nasabah  : %-52s|\n", Rekening.namaLengkap);
        printf("\t\t\t| Rekening : %-52s|\n", Rekening.NomorRekening);
        printf("\t\t\t| Tanggal  = %02d/%02d/%d", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
        printf("\t\t\t Waktu layar = %02d:%02d WIB |\n", tm->tm_hour, tm->tm_min);
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                    [ Kode Top-Up E-Money ]                     |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                                                                |\n");
        printf("\t\t\t|                 1. BRIZZI BRI             : 6013               |\n");
        printf("\t\t\t|                                                                |\n");
        printf("\t\t\t|----------------------------------------------------------------|\n");
        printf("\t\t\t|                                                                |\n");
        printf("\t\t\t|                 2. e-Money MANDIRI        : 6023               |\n");
        printf("\t\t\t|                                                                |\n");
        printf("\t\t\t|----------------------------------------------------------------|\n");
        printf("\t\t\t|                                                                |\n");
        printf("\t\t\t|                 3. TapCash BNI            : 7546               |\n");
        printf("\t\t\t|                                                                |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                                                                |\n");
        printf("\t\t\t| PT BANK SENTRAL STATISTIK Tbk. berizin dan diawasi oleh Badan  |\n");
        printf("\t\t\t|     Pusat Statistik dan Bank Indonesia(BI), serta merupakan    |\n");
        printf("\t\t\t|        peserta penjaminan Lembaga Penjamin Simpanan(LPS)       |\n");
        printf("\t\t\t|             Copyright © 2025 Bank SENTRAL STATISTIK            |\n");
        printf("\t\t\t|                                                                |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t Ingin membatalkan transaksi dan kembali ke menu sebelumnya? (Y/T): ");
        scanf("%s", &Mekanisme.batalTransaksi);
        getchar();
        if(Mekanisme.batalTransaksi == 'y' || Mekanisme.batalTransaksi == 'Y'){
            printf("\t\t\t Mengalihkan layar");
            for(int i=0; i<3; i++){
                delay(100000000);
                printf(".");
            }
            system("cls");
            tampilanSubmenuDigital();
        }
        else if(Mekanisme.batalTransaksi == 't' || Mekanisme.batalTransaksi == 'T'){
        }
        else{
            printf("\t\t\t Pilihan tidak dikenali!\n");
            printf("\t\t\t Apakah Anda ingin mengulangi? (y/t): ");
            scanf(" %c", &Mekanisme.pilihanInvalid);
            switch(Mekanisme.pilihanInvalid){
                case 'Y' :
                    system("cls");
                    tampilanSubmenuDigital();
                    break;
                case 'y' :
                    system("cls");
                    tampilanSubmenuDigital();
                    break;
                default :
                    printf("\t\t\t Mengalihkan layar");
                    for(int i=0; i<3; i++){
                        delay(100000000);
                        printf(".");
                    }
                    system("cls");
                    tampilanMenuUtama();
                    break;
            }
        }
        printf("\t\t\t Contoh: 6013500500639233\n");
        printf("\t\t\t Masukkan kode E-Money + No Kartu: ");
        scanf("%s", &Mekanisme.kodeEMoney);
        if (strncmp(Mekanisme.kodeEMoney, "6013", 4) == 0) {
            strcpy(Mekanisme.jenisEMoney, "BRIZZI BRI");
        } else if (strncmp(Mekanisme.kodeEMoney, "6023", 4) == 0) {
            strcpy(Mekanisme.jenisEMoney, "e-Money MANDIRI");
        } else if (strncmp(Mekanisme.kodeEMoney, "7546", 4) == 0) {
            strcpy(Mekanisme.jenisEMoney, "Tapcash BNI");
        } else {
            printf("\n\t\t\t Layanan E-Money tidak tersedia!\n");
            printf("\n\t\t\t Ingin mengulangi transaksi? (y/t) : ");
            scanf("%s", &Mekanisme.pilihanInvalid);
            switch(Mekanisme.pilihanInvalid){
            case 'Y' :
                system("cls");
                tampilanTopUpEMoney();
                break;
            case 'y' :
                system("cls");
                tampilanTopUpEMoney();
                break;
            default :
                printf("\t\t\t Mengalihkan layar");
                for(int i=0; i<3; i++){
                delay(100000000);
                printf(".");
                }
                system("cls");
                tampilanSubmenuDigital();
                break;
            }
        }
        printf("\n");
        printf("\t\t\t Kartu Anda : %s\n", Mekanisme.jenisEMoney);
        int n = strlen(Mekanisme.kodeEMoney)-3;
        strcpy(Mekanisme.noKartu, ambilNoKartu(Mekanisme.kodeEMoney, n));
        printf ("%s\n", Mekanisme.noKartu);
        printf("\n");
        printf("\t\t\t Masukkan nominal top up (minimal 10000): ");
        scanf("%lf", &Mekanisme.nominal);
        getchar();
        if (Mekanisme.nominal < 10000){
            printf("\t\t\t Nominal minimal top-up E-Money adalah 10000.\n");
            printf("\t\t\t Ingin mengulangi transaksi?(Y/T): ");
            scanf("%s", &Mekanisme.batalTransaksi);
            switch(Mekanisme.pilihanInvalid){
                case 'Y' :
                    system("cls");
                    break;
                case 'y' :
                    system("cls");
                    break;
                default :
                    printf("\t\t\t Mengalihkan layar");
                    for(int i=0; i<3; i++){
                       delay(100000000);
                       printf(".");
                    }
                    system("cls");
                    tampilanSubmenuDigital();
                    break;
                }
            }else{
        }
        printf("\t\t\t Keterangan [Max 25 karakter]    : ");
        gets(Mekanisme.keterangan);
        if(!validasiKeterangan){
            printf("\t\t\t Keterangan melebihi ketentuan!");
            system("pause");
            system("cls");
            continue;
        }
        printf("\t\t\t Masukkan pin transaksi          : ");
        gets(Rekening.password);
        if(password(Rekening.password)){
            invalid = 1;
        }
        else{
            printf("\t\t\t Pin Anda salah!\n");
            system("pause");
            printf("\t\t\t Mengembalikan layar");
            for(int i=0; i<3; i++){
                delay(100000000);
                printf(".");
            }
            system("cls");
            continue;
        }
        printf("\t\t\t Apakah Anda yakin ingin melakukan transaksi (Y/T): ");
        scanf("%s", &Mekanisme.batalTransaksi);
        switch(Mekanisme.batalTransaksi){
            case 'Y' :
                system("cls");
                invalid = 1;
                break;
            case 'y' :
                system("cls");
                invalid = 1;
                break;
            default :
                printf("\t\t\t Mengalihkan layar");
                for(int i=0; i<3; i++){
                   delay(100000000);
                   printf(".");
                }
                system("cls");
                tampilanSubmenuDigital();
                break;
            }
            invalid=1;
          }while(!invalid);
        system("cls");
        strcpy(Mekanisme.jenisTransaksi, "Layanan Digital [Top-up]");
        strcpy(Mekanisme.tipeTransaksi, "E-Money");
        strcpy(Mekanisme.nomorTransaksi, generatorRandNum());
        strcpy(Mekanisme.kodeTransaksi, generatorUnCode());
        strcpy(Mekanisme.tujuanTransaksi, "E-Payment - ");
        strcat(Mekanisme.tujuanTransaksi, Mekanisme.jenisEMoney);
        strcpy(Mekanisme.tujuanTambahan, Mekanisme.noKartu);
        Mekanisme.biayaAdmin = 1000;
        Mekanisme.total = Mekanisme.nominal + Mekanisme.biayaAdmin;
        Mekanisme.saldo -= Mekanisme.total;
        simpanPerbaruiSaldo(Mekanisme.saldo);
        SimpanTransaksiKeFile(Mekanisme.total, Mekanisme.keterangan, Mekanisme.kodeTransaksi, Mekanisme.jenisTransaksi, Mekanisme.tipeTransaksi);
        tampilanStruk(Mekanisme.nomorTransaksi, Mekanisme.jenisTransaksi, Mekanisme.kodeTransaksi, Mekanisme.tujuanTransaksi, Mekanisme.tujuanTambahan, Mekanisme.biayaAdmin, Mekanisme.nominal, Mekanisme.total, Mekanisme.keterangan);
}
void tampilanTopUpPulsa(){
   int invalid = 0;
   char konfirmasiJawab;
   informasiDiri Rekening;
   informasi2 Mekanisme;
   Mekanisme.saldo = bacaSaldo();
   do{
   time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        REKENING_FILE = fopen("DataRekeningNasabah.txt", "r");
        if(REKENING_FILE == NULL){
            printf("\t\t\t Rekening tidak terbaca!\n");
        }
        else{
            fscanf(REKENING_FILE, "%[^\n]", &Rekening.namaLengkap);
            fscanf(REKENING_FILE, "%s\n", &Rekening.NomorRekening);
            fclose(REKENING_FILE);
        }
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t|                        [ mobiStats 5 ]                         |\n");
    printf("\t\t\t|                 << BANK SENTRAL STATISTIK >>                   |\n");
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t||oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo||\n");
    printf("\t\t\t||--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--||\n");
    printf("\t\t\t||oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo||\n");
    printf("\t\t\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
    printf("\t\t\t| Nasabah  : %-52s|\n", Rekening.namaLengkap);
    printf("\t\t\t| Rekening : %-52s|\n", Rekening.NomorRekening);
    printf("\t\t\t| Tanggal  = %02d/%02d/%d", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
    printf("\t\t\t Waktu layar = %02d:%02d WIB |\n", tm->tm_hour, tm->tm_min);
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t|                     [ Layanan Provider ]                       |\n");
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t|                               ||                               |\n");
    printf("\t\t\t|       1. Telkomsol (0821)     ||        2. Eksel (0818)        |\n");
    printf("\t\t\t|                               ||                               |\n");
    printf("\t\t\t|----------------------------------------------------------------|\n");
    printf("\t\t\t|                               ||                               |\n");
    printf("\t\t\t|       2. Iemtri (0858)        ||        4. Eksis (0832)        |\n");
    printf("\t\t\t|                               ||                               |\n");
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t|                                                                |\n");
    printf("\t\t\t| PT BANK SENTRAL STATISTIK Tbk. berizin dan diawasi oleh Badan  |\n");
    printf("\t\t\t|     Pusat Statistik dan Bank Indonesia(BI), serta merupakan    |\n");
    printf("\t\t\t|        peserta penjaminan Lembaga Penjamin Simpanan(LPS)       |\n");
    printf("\t\t\t|             Copyright © 2025 Bank SENTRAL STATISTIK            |\n");
    printf("\t\t\t|                                                                |\n");
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t Ingin membatalkan transaksi dan kembali ke menu sebelumnya? (Y/T): ");
    scanf("%s", &Mekanisme.batalTransaksi);
    getchar();
        if(Mekanisme.batalTransaksi == 'y' || Mekanisme.batalTransaksi == 'Y'){
            printf("\t\t\t Mengalihkan layar");
            for(int i=0; i<3; i++){
                delay(100000000);
                printf(".");
            }
            system("cls");
            tampilanSubmenuDigital();
        }
        else if(Mekanisme.batalTransaksi == 't' || Mekanisme.batalTransaksi == 'T'){
        }
        else{
            printf("\t\t\t Pilihan tidak dikenali!\n");
            printf("\t\t\t Apakah Anda ingin mengulangi? (y/t): ");
            scanf(" %c", &Mekanisme.pilihanInvalid);
            switch(Mekanisme.pilihanInvalid){
                case 'Y' :
                    system("cls");
                    tampilanSubmenuDigital();
                    break;
                case 'y' :
                    system("cls");
                    tampilanSubmenuDigital();
                    break;
                default :
                    printf("\t\t\t Mengalihkan layar");
                    for(int i=0; i<3; i++){
                        delay(100000000);
                        printf(".");
                    }
                    system("cls");
                    tampilanMenuUtama();
                    break;
            }
        }
        printf("\t\t\t Masukkan no telepon tujuan (11-13 digit): ");
        scanf("%s", &Mekanisme.kodeProvider);
        if (strncmp(Mekanisme.kodeProvider, "0821", 4) == 0) {
            strcpy(Mekanisme.jenisProvider, "Telkomsol");
        } else if (strncmp(Mekanisme.kodeProvider, "0818", 4) == 0) {
            strcpy(Mekanisme.jenisProvider, "Eksel");
        } else if (strncmp(Mekanisme.kodeProvider, "0858", 4) == 0) {
            strcpy(Mekanisme.jenisProvider, "Iemtri");
        } else if (strncmp(Mekanisme.kodeProvider, "0832", 4) == 0) {
            strcpy(Mekanisme.jenisProvider, "Eksis");
        } else {
            printf("\n\t\t\t Layanan Pulsa tidak tersedia!\n");
            printf("\n\t\t\t Ingin mengulangi transaksi? (y/t) : ");
            scanf("%s", &Mekanisme.pilihanInvalid);
            switch(Mekanisme.pilihanInvalid){
            case 'Y' :
                system("cls");
                tampilanTopUpPulsa();
                break;
            case 'y' :
                system("cls");
                tampilanTopUpPulsa();
                break;
            default :
                printf("\t\t\t Mengalihkan layar");
                for(int i=0; i<3; i++){
                delay(100000000);
                printf(".");
                }
                system("cls");
                tampilanSubmenuDigital();
                break;
            }
        }
        printf("\n\t\t\t Anda memilih : %s\n", Mekanisme.jenisProvider);
        int n = strlen(Mekanisme.kodeProvider);
        strcpy(Mekanisme.noTelepon, ambilNoTelepon(Mekanisme.kodeProvider, n));
        printf ("%s\n", Mekanisme.noTelepon);
        printf("\n");
        printf("\t\t\t Masukkan nominal top up pulsa(minimal 10000): ");
        scanf("%lf", &Mekanisme.nominal);
        getchar();
        if (Mekanisme.nominal < 10000){
            printf("\t\t\t Nominal minimal top-up pulsa adalah 10000.\n");
            printf("\t\t\t Ingin mengulangi transaksi?(Y/T): ");
            scanf("%s", &Mekanisme.batalTransaksi);
            switch(Mekanisme.pilihanInvalid){
                case 'Y' :
                    system("cls");
                    break;
                case 'y' :
                    system("cls");
                    break;
                default :
                    printf("\t\t\t Mengalihkan layar");
                    for(int i=0; i<3; i++){
                       delay(100000000);
                       printf(".");
                    }
                    system("cls");
                    tampilanSubmenuDigital();
                    break;
                }
            }else{
        }
        printf("\t\t\t Keterangan [Max 25 karakter]            : ");
        gets(Mekanisme.keterangan);
        if(!validasiKeterangan){
            printf("\t\t\t Keterangan melebihi ketentuan!");
            system("pause");
            system("cls");
            continue;
        }
        printf("\t\t\t Masukkan pin transaksi                  : ");
        gets(Rekening.password);
        if(password(Rekening.password)){
            invalid = 1;
        }
        else{
            printf("\t\t\t Pin Anda salah!\n");
            system("pause");
            printf("\t\t\t Mengembalikan layar");
            for(int i=0; i<3; i++){
                delay(100000000);
                printf(".");
            }
            system("cls");
            continue;
        }
        printf("\t\t\t Apakah Anda yakin ingin melakukan transaksi (Y/T): ");
        scanf("%s", &Mekanisme.batalTransaksi);
        switch(Mekanisme.batalTransaksi){
            case 'Y' :
                invalid = 1;
                break;
            case 'y' :
                invalid = 1;
                break;
            default :
                printf("\t\t\t Mengalihkan layar");
                for(int i=0; i<3; i++){
                   delay(100000000);
                   printf(".");
                }
                system("cls");
                tampilanSubmenuDigital();
                break;
            }
            invalid=1;
          }while(!invalid);
        system("cls");
        strcpy(Mekanisme.jenisTransaksi, "Layanan Digital");
        strcpy(Mekanisme.tipeTransaksi, "Pulsa Prabayar");
        strcpy(Mekanisme.nomorTransaksi, generatorRandNum());
        strcpy(Mekanisme.kodeTransaksi, generatorUnCode());
        strcpy(Mekanisme.tujuanTransaksi, "Komunikasi - ");
        strcat(Mekanisme.tujuanTransaksi, Mekanisme.jenisProvider);
        strcpy(Mekanisme.tujuanTambahan, Mekanisme.noTelepon);
        Mekanisme.biayaAdmin = 2000;
        Mekanisme.total = Mekanisme.nominal + Mekanisme.biayaAdmin;
        Mekanisme.saldo -= Mekanisme.total;
        printf("\t\t\t Menampilkan struk");
        for(int i=0; i<3; i++){
            delay(100000000);
            printf(".");
        }
        system("cls");
        simpanPerbaruiSaldo(Mekanisme.saldo);
        SimpanTransaksiKeFile(Mekanisme.total, Mekanisme.keterangan, Mekanisme.kodeTransaksi, Mekanisme.jenisTransaksi, Mekanisme.tipeTransaksi);
        tampilanStruk(Mekanisme.nomorTransaksi, Mekanisme.jenisTransaksi, Mekanisme.kodeTransaksi, Mekanisme.tujuanTransaksi, Mekanisme.tujuanTambahan, Mekanisme.biayaAdmin, Mekanisme.nominal, Mekanisme.total, Mekanisme.keterangan);
}
void tampilanSubmenuPemerintah(){
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    informasiDiri Rekening;
    informasi2 Mekanisme;
    REKENING_FILE = fopen("DataRekeningNasabah.txt", "r");
    if(REKENING_FILE == NULL){
        printf("\t\t\t Rekening tidak terbaca!\n");
    }
    else{
    fscanf(REKENING_FILE, "%[^\n]", &Rekening.namaLengkap);
    fscanf(REKENING_FILE, "%s\n", &Rekening.NomorRekening);
    fclose(REKENING_FILE);
    }
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t|                        [ mobiStats 5 ]                         |\n");
    printf("\t\t\t|                 << BANK SENTRAL STATISTIK >>                   |\n");
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t||oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo||\n");
    printf("\t\t\t||--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--||\n");
    printf("\t\t\t||oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo||\n");
    printf("\t\t\t|----------------------------------------------------------------|\n");
    printf("\t\t\t| Nasabah   : %-51s|\n", Rekening.namaLengkap);
    printf("\t\t\t| Rekening  : %-51s|\n", Rekening.NomorRekening);
    printf("\t\t\t| Tanggal   = %02d/%02d/%d", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
    printf("\t\t Waktu layar = %02d:%02d WIB |\n", tm->tm_hour, tm->tm_min);
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t|                      SUBMENU PEMERINTAH                        |\n");
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t|                                                                |\n");
    printf("\t\t\t|                         1. e-SIM                               |\n");
    printf("\t\t\t|                                                                |\n");
    printf("\t\t\t|----------------------------------------------------------------|\n");
    printf("\t\t\t|                                                                |\n");
    printf("\t\t\t|                         2. PLN                                 |\n");
    printf("\t\t\t|                                                                |\n");
    printf("\t\t\t|----------------------------------------------------------------|\n");
    printf("\t\t\t|                                                                |\n");
    printf("\t\t\t|                         3. Kembali                             |\n");
    printf("\t\t\t|                                                                |\n");
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t|                                                                |\n");
    printf("\t\t\t| PT BANK SENTRAL STATISTIK Tbk. berizin dan diawasi oleh Badan  |\n");
    printf("\t\t\t|     Pusat Statistik dan Bank Indonesia(BI), serta merupakan    |\n");
    printf("\t\t\t|        peserta penjaminan Lembaga Penjamin Simpanan(LPS)       |\n");
    printf("\t\t\t|             Copyright © 2025 Bank SENTRAL STATISTIK            |\n");
    printf("\t\t\t|                                                                |\n");
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\tMasukkan pilihan layanan : ");
    scanf("%d", &Mekanisme.pilihan);
    if(Mekanisme.pilihan == 1){
        printf("\t\t\tMengalihkan layar");
        for(int i=0; i<3; i++){
            delay(100000000);
            printf(".");
        }
        system("cls");
        tampilanESIM();
    }
    else if(Mekanisme.pilihan == 2){
        printf("\t\t\tMengalihkan layar");
        for(int i = 0; i<3; i++){
            delay(100000000);
            printf(".");
        }
        system("cls");
        tampilanPLN();
    }
    else if(Mekanisme.pilihan == 3){
        printf("\t\t\tMengalihkan layar");
        for(int i = 0; i<3; i++){
            delay(100000000);
            printf(".");
        }
        system("cls");
        tampilanMenuUtama();
    }
    else{
        printf("\t\t\tPilihan tidak memenuhi!\n");
        printf("\t\t\tIngin mengulangi program? (y/t) : ");
        scanf("%s", &Mekanisme.pilihanInvalid);
        switch(Mekanisme.pilihanInvalid){
        case 'Y' :
            system("cls");
            tampilanSubmenuPemerintah();
            break;
        case 'y' :
            system("cls");
            tampilanSubmenuPemerintah();
            break;
        case 'T' :
            system("cls");
            tampilanMenuUtama();
            break;
        case 't' :
            system("cls");
            tampilanMenuUtama();
            break;
        default :
            printf("\t\t\tMengalihkan layar");
            for(int i=0; i<3; i++){
               delay(100000000);
               printf(".");
            }
            system("cls");
            tampilanSubmenuPemerintah();
            break;
        }
     }
}
void tampilanESIM() {
    int inputValid = 0;
    char konfirmasiJawab;
    informasiDiri Rekening;
    informasi2 Mekanisme;
    InformasiESIM esim;
    do {
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        REKENING_FILE = fopen("DataRekeningNasabah.txt", "r");
        if (REKENING_FILE == NULL) {
            printf("\t\t\t Rekening tidak terbaca!\n");
        } else {
            fscanf(REKENING_FILE, "%[^\n]", &Rekening.namaLengkap);
            fscanf(REKENING_FILE, "%s\n", &Rekening.NomorRekening);
            fclose(REKENING_FILE);
        }
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                        [ mobiStats 5 ]                         |\n");
        printf("\t\t\t|                 << BANK SENTRAL STATISTIK >>                   |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t||oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo||\n");
        printf("\t\t\t||--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--||\n");
        printf("\t\t\t||oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo||\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                             E-SIM                              |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|         Kendaran Umum         |         Kendaraan Khusus       |\n");
        printf("\t\t\t|-------------------------------|--------------------------------|\n");
        printf("\t\t\t|   Jenis SIM    |  Kode SIM    |    Jenis SIM    |  Kode SIM    |\n");
        printf("\t\t\t|----------------|--------------|-----------------|--------------|\n");
        printf("\t\t\t|     1. SIM A   |     AU       |    6. SIM A1    |     AK1      |\n");
        printf("\t\t\t|     2. SIM B   |     BU       |    7. SIM A2    |     AK2      |\n");
        printf("\t\t\t|     3. SIM B1  |     BU1      |    8. SIM C2    |     CK1      |\n");
        printf("\t\t\t|     4. SIM C   |     CU       |    9. SIM D     |     DK       |\n");
        printf("\t\t\t|     5. SIM C1  |     CU1      |   10. SIM Inter |     INT      |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                                                                |\n");
        printf("\t\t\t| PT BANK SENTRAL STATISTIK Tbk. berizin dan diawasi oleh Badan  |\n");
        printf("\t\t\t|     Pusat Statistik dan Bank Indonesia(BI), serta merupakan    |\n");
        printf("\t\t\t|        peserta penjaminan Lembaga Penjamin Simpanan(LPS)       |\n");
        printf("\t\t\t|             Copyright © 2025 Bank SENTRAL STATISTIK            |\n");
        printf("\t\t\t|                                                                |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t Ingin membatalkan transaksi dan kembali ke menu sebelumnya? (Y/T): ");
        scanf("%s", &Mekanisme.batalTransaksi);
        getchar();
        if (Mekanisme.batalTransaksi == 'y' || Mekanisme.batalTransaksi == 'Y'){
            printf("\t\t\t  Mengalihkan layar");
            for (int i = 0; i < 3; i++) {
                delay(100000000);
                printf(".");
            }
            system("cls");
            tampilanSubmenuPemerintah();
        } else if (Mekanisme.batalTransaksi == 't' || Mekanisme.batalTransaksi == 'T') {
        } else {
            printf("\t\t\t Pilihan tidak dikenali!\n");
            printf("\t\t\t Apakah Anda ingin mengulangi? (y/t): ");
            scanf(" %s", &Mekanisme.pilihanInvalid);
            switch (Mekanisme.pilihanInvalid) {
                case 'Y':
                    system("cls");
                    tampilanESIM();
                    break;
                case 'y':
                    system("cls");
                    tampilanESIM();
                    break;
                case 'T':
                    system("cls");
                    tampilanSubmenuPemerintah();
                    break;
                case 't':
                    system("cls");
                    tampilanSubmenuPemerintah();
                    break;
                default:
                    printf("\t\t\t Mengalihkan layar");
                    for (int i = 0; i < 3; i++) {
                        delay(100000000);
                        printf(".");
                    }
                    system("cls");
                    tampilanESIM();
            }
        }
        printf("\t\t\t Masukkan nama pemilik E-SIM       : ");
        gets(esim.namaPemilik);
        printf("\t\t\t Masukkan kode E-SIM               : ");
        gets(esim.simKode);
        esim.hargaKonstan = tarifESIM(esim.simKode);
        if(strcasecmp(esim.simKode, "AU")==0){strcpy(esim.simKode, "AU");}
        else if(strcasecmp(esim.simKode, "BU")==0){strcpy(esim.simKode, "BU");}
        else if(strcasecmp(esim.simKode, "BU1")==0){strcpy(esim.simKode, "BU1");}
        else if(strcasecmp(esim.simKode, "CU")==0){strcpy(esim.simKode, "CU");}
        else if(strcasecmp(esim.simKode, "CU1")==0){strcpy(esim.simKode, "CU1");}
        else if(strcasecmp(esim.simKode, "AK1")==0){strcpy(esim.simKode, "AK1");}
        else if(strcasecmp(esim.simKode, "AK2")==0){strcpy(esim.simKode, "AK2");}
        else if(strcasecmp(esim.simKode, "CK1")==0){strcpy(esim.simKode, "CK1");}
        else if(strcasecmp(esim.simKode, "DK")==0){strcpy(esim.simKode, "DK");}
        else if(strcasecmp(esim.simKode, "INT")==0){strcpy(esim.simKode, "INT");}
        else{printf("\t\t\t Kode SIM Tidak terdapat dalam daftar!  ");
        system("pause");
        system("cls");
        continue;}
        printf("\t\t\t nomor E-SIM = 5 digit numerik\n");
        printf("\t\t\t Masukkan nomor E-SIM              : ");
        gets(esim.nomorSIM);
        if(!validasiESIM(esim.nomorSIM)){
            printf("\t\t\t Nomor E-SIM invalid!  ");
            system("pause");
            system("cls");
            continue;
        }
        printf("\t\t\t Lama periode bayar [max 5 bulan]  : ");
        scanf("%lf", &esim.periode);
        if(esim.periode <= 0 || esim.periode > 5){
            printf("\t\t\t Periode waktu tidak sesuai ketentuan!  ");
            system("pause");
            system("cls");
            continue;
        }
        printf("\t\t\t Lanjutkan pembayaran (Y/T)        : ");
        scanf("%s", &Mekanisme.batalTransaksi);
        if (Mekanisme.batalTransaksi == 'Y' || Mekanisme.batalTransaksi == 'y') {
            printf("\t\t\t Mengalihkan layar");
            for (int i = 0; i < 3; i++) {
                delay(100000000);
                printf(".");
            }
            system("cls");
            tampilan2ESIM(&esim.namaPemilik, &esim.simKode, &esim.nomorSIM, esim.hargaKonstan, esim.periode);
        } else if (Mekanisme.batalTransaksi == 'T' || Mekanisme.batalTransaksi == 't') {
            printf("\t\t\t Mengalihkan layar");
            for (int i = 0; i < 3; i++) {
                delay(100000000);
                printf(".");
            }
            system("cls");
            tampilanSubmenuPemerintah();
        } else {
            printf("\t\t\t Pilihan Anda invalid! ");
            system("pause");
            printf("\t\t\t Mengalihkan layar");
            for (int i = 0; i < 3; i++) {
                delay(100000000);
                printf(".");
            }
            system("cls");
            continue;
        }
        inputValid = 1;
    } while (!inputValid);
}
void tampilan2ESIM(const char *namaPemilik, const char *JenisSIM, const char *NomorSIM, double nominal, double periode) {
    InformasiESIM biaya;
    informasi2 Mekanisme;
    informasiDiri user;
    int valid = 0;
    do {
        biaya.nominalBayar = nominal * periode;
        biaya.totalBayar = biaya.nominalBayar + 1500;
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                        [ mobiStats 5 ]                         |\n");
        printf("\t\t\t|                 << BANK SENTRAL STATISTIK >>                   |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t||oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo||\n");
        printf("\t\t\t||--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--||\n");
        printf("\t\t\t||oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo||\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                             E-SIM                              |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t| Jenis SIM [Kode e-SIM]      : %-33s|\n", JenisSIM);
        printf("\t\t\t| Nomor SIM [Nomor Kartu]     : %-33s|\n", NomorSIM);
        printf("\t\t\t| Nama Pengguna [Pemilik]     : %-33s|\n", namaPemilik);
        printf("\t\t\t| Sumber Aliran Dana          : Digital SIM                      |\n");
        printf("\t\t\t| Tujuan Aliran Dana          : Badan Perpajakan Kemenkeu Staats |\n");
        printf("\t\t\t| Nominal Pembayaran          : Rp%-20.2lf(%02.0lf bulan) |\n", nominal, periode);
        printf("\t\t\t| Biaya operasional           : Rp1500                           |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t+                               |                                +\n");
        printf("\t\t\t|       Total Pembayaran        |             Rp%-10.2lf       |\n", biaya.totalBayar);
        printf("\t\t\t+                               |                                +\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                                                                |\n");
        printf("\t\t\t| PT BANK SENTRAL STATISTIK Tbk. berizin dan diawasi oleh Badan  |\n");
        printf("\t\t\t|     Pusat Statistik dan Bank Indonesia(BI), serta merupakan    |\n");
        printf("\t\t\t|        peserta penjaminan Lembaga Penjamin Simpanan(LPS)       |\n");
        printf("\t\t\t|             Copyright © 2025 Bank SENTRAL STATISTIK            |\n");
        printf("\t\t\t|                                                                |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t Masukkan Pin Transaksi              : ");
        scanf("%s", &user.pinTransaksi);
        if (password(user.pinTransaksi)) {
            if(validasiSaldo(biaya.totalBayar+1500)){
                printf("\t\t\t Ingin melakukan pembayaran (Y/T): ");
                scanf("%s", &Mekanisme.batalTransaksi);
                if(Mekanisme.batalTransaksi =='y'||Mekanisme.batalTransaksi=='y'){
                    valid = 1;
                }
                else if(Mekanisme.batalTransaksi =='t'||Mekanisme.batalTransaksi =='T'){
                    printf("\t\t\t Mengembalikan layar");
                    for(int i=0; i<3; i++){
                        delay(100000000);
                        printf(".");
                    }
                    tampilanESIM();
                }
                else{
                    printf("\t\t\t Pilihan tidak dikenali! ");
                    system("pause");
                    printf("\t\t\t Mengalihkan layar");
                    for(int i=0; i<3; i++){
                        delay(10000000000);
                        printf(".");
                    }
                    tampilanESIM();
                }
            }
            else{
                printf("\t\t\t Maaf, saldo Anda tidak mencukupi untuk bertransaksi!\n");
                system("pause");
                printf("\t\t\t Mengembalikan layar");
                for(int i=0; i<3; i++){
                    delay(100000000);
                    printf(".");
                }
                system("cls");
                tampilanESIM();
            }
        } else {
            printf("\t\t\t Password salah!\n");
            system("pause");
            printf("\t\t\t Ingin kembali ke menu sebelumnya? (y/t) : ");
            scanf("%s", &Mekanisme.batalTransaksi);
            if (Mekanisme.batalTransaksi == 'Y' || Mekanisme.batalTransaksi == 'y') {
                printf("\t\t\t Mengalihkan layar");
                for (int i = 0; i < 3; i++) {
                    delay(100000000);
                    printf(".");
                }
                system("cls");
                tampilanESIM();
            } else if (Mekanisme.batalTransaksi == 'T' || Mekanisme.batalTransaksi == 't') {
                system("cls");
                continue;
            } else {
                printf("\t\t\t Pilihan tidak dikenali!");
                system("pause");
                continue;
            }
        }
        valid = 1;
    } while (!valid);
    Mekanisme.saldo = bacaSaldo();
    Mekanisme.biayaAdmin = 1500;
    Mekanisme.nominal = biaya.totalBayar;
    Mekanisme.total = Mekanisme.nominal + Mekanisme.biayaAdmin;
    Mekanisme.saldo -= Mekanisme.total;
    simpanPerbaruiSaldo(Mekanisme.saldo);
    strcpy(Mekanisme.subKeterangan, "Pembayaran ESIM ");
    strcpy(Mekanisme.jenisTransaksi, "Layanan Pemerintah");
    strcpy(Mekanisme.tipeTransaksi, "E-SIM");
    strcpy(Mekanisme.nomorTransaksi, generatorRandNum());
    strcpy(Mekanisme.kodeTransaksi, generatorUnCode());
    strcpy(Mekanisme.tujuanTransaksi, "Perpajakan");
    strcat(JenisSIM, NomorSIM);
    strcpy(Mekanisme.tujuanTambahan, "");
    strcat(Mekanisme.subKeterangan, JenisSIM);
    printf("\t\t\t Mengalihkan layar");
    for(int i=0; i<3; i++){
        delay(100000000);
        printf(".");
    }
    system("cls");
    SimpanTransaksiKeFile(Mekanisme.total, Mekanisme.subKeterangan, Mekanisme.kodeTransaksi, Mekanisme.jenisTransaksi, Mekanisme.tipeTransaksi);
    tampilanStruk(Mekanisme.nomorTransaksi, Mekanisme.jenisTransaksi, Mekanisme.kodeTransaksi, Mekanisme.tujuanTransaksi, Mekanisme.tujuanTambahan, Mekanisme.biayaAdmin, Mekanisme.nominal, Mekanisme.total, Mekanisme.subKeterangan);
}
 void tampilanInformasiAkun(){
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    informasiDiri Rekening;
    informasi2 Mekanisme;
    REKENING_FILE = fopen("DataRekeningNasabah.txt", "r");
    if(REKENING_FILE == NULL){
        printf("\t\t\t Rekening tidak terbaca!\n");
    }
    else{
        fscanf(REKENING_FILE, "%[^\n]", &Rekening.namaLengkap);
        fscanf(REKENING_FILE, "%s\n", &Rekening.NomorRekening);
        fclose(REKENING_FILE);
    }
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t|                        [ mobiStats 5 ]                         |\n");
    printf("\t\t\t|                 << BANK SENTRAL STATISTIK >>                   |\n");
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t||oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo||\n");
    printf("\t\t\t||--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--||\n");
    printf("\t\t\t||oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo||\n");
    printf("\t\t\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
    printf("\t\t\t| Nasabah  : %-52s|\n", Rekening.namaLengkap);
    printf("\t\t\t| Rekening : %-52s|\n", Rekening.NomorRekening);
    printf("\t\t\t| Tanggal  = %02d/%02d/%d", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
    printf("\t\t         Waktu layar = %02d:%02d WIB |\n", tm->tm_hour, tm->tm_min);
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t|                    SUBMENU INFORMASI AKUN                      |\n");
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t|                               ||                               |\n");
    printf("\t\t\t|     1. Informasi Pengguna     ||     2. Histori Transaksi      |\n");
    printf("\t\t\t|                               ||                               |\n");
    printf("\t\t\t|----------------------------------------------------------------|\n");
    printf("\t\t\t|                               ||                               |\n");
    printf("\t\t\t|     3. Tentang mobiStats 5    ||     4. Kembali                |\n");
    printf("\t\t\t|                               ||                               |\n");
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t|                                                                |\n");
    printf("\t\t\t| PT BANK SENTRAL STATISTIK Tbk. berizin dan diawasi oleh Badan  |\n");
    printf("\t\t\t|     Pusat Statistik dan Bank Indonesia(BI), serta merupakan    |\n");
    printf("\t\t\t|        peserta penjaminan Lembaga Penjamin Simpanan(LPS)       |\n");
    printf("\t\t\t|             Copyright © 2025 Bank SENTRAL STATISTIK            |\n");
    printf("\t\t\t|                                                                |\n");
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t Masukkan pilihan layanan : ");
    scanf("%d", &Mekanisme.pilihan);
    if(Mekanisme.pilihan == 1){
        printf("\t\t\t Mengalihkan layar");
        for(int i=0; i<3; i++){
            delay(100000000);
            printf(".");
        }
        system("cls");
        tampilanInfoAkun();
    }
    else if(Mekanisme.pilihan == 2){
        printf("\t\t\t Mengalihkan layar");
        for(int i=0; i<3; i++){
            delay(100000000);
            printf(".");
        }
        system("cls");
        tampilanHistoriTransaksi();
    }
    else if(Mekanisme.pilihan == 3){
        printf("\t\t\t Mengalihkan layar");
        for(int i=0; i<3; i++){
            delay(100000000);
            printf(".");
        }
        system("cls");
        tampilanTentangKami();
    }
    else if(Mekanisme.pilihan == 4){
        printf("\t\t\t Mengalihkan layar");
        for(int i=0; i<3; i++){
            delay(100000000);
            printf(".");
        }
        system("cls");
        tampilanMenuUtama();
    }
    else{
        printf("\t\t\t Pilihan tidak dikenali!\n");
        printf("\t\t\t Ingin mengulangi program? (y/t) : ");
        scanf("%s", &Mekanisme.pilihanInvalid);
        switch(Mekanisme.pilihanInvalid){
        case 'Y' :
            system("cls");
            tampilanInformasiAkun();
            break;
        case 'y' :
            system("cls");
            tampilanInformasiAkun();
            break;
        default :
            printf("\t\t\t Mengalihkan layar");
            for(int i=0; i<3; i++){
               delay(100000000);
               printf(".");
            }
            system("cls");
            tampilanMenuAwal();
            break;
        }
    }
 }
void tampilanHistoriTransaksi(){
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    informasiDiri Rekening;
    informasi2 Mekanisme;
    MUTASI_FILE = fopen("DataMutasi.txt", "r");
    REKENING_FILE = fopen("DataRekeningNasabah.txt", "r");
    if(REKENING_FILE == NULL){
        printf("\t\t\t Data rekening tidak ditemukan!\n");
    }
    else{
        fscanf(REKENING_FILE, "%[^\n]", &Rekening.namaLengkap);
        fscanf(REKENING_FILE, "%s\n", &Rekening.NomorRekening);
        fclose(REKENING_FILE);
    }
    if(MUTASI_FILE == NULL){
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                        [ mobiStats 5 ]                         |\n");
        printf("\t\t\t|                 << BANK SENTRAL STATISTIK >>                   |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                >> HISTORI TRANSAKSI NASABAH <<                 |\n");
        printf("\t\t\t| Tanggal  : %02d/%02d/%04d", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
        printf("                        Waktu : %02d:%02d WIB |\n", tm->tm_hour, tm->tm_min);
        printf("\t\t\t| Nasabah  : %-52s|\n", Rekening.namaLengkap);
        printf("\t\t\t| Rekening : %-52s|\n", Rekening.NomorRekening);
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t                 Histori transaksi tidak tersedia!\n");
        printf("\n");
        printf("\n");
    }
    else{
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                        [ mobiStats 5 ]                         |\n");
        printf("\t\t\t|                 << BANK SENTRAL STATISTIK >>                   |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                >> HISTORI TRANSAKSI NASABAH <<                 |\n");
        printf("\t\t\t| Tanggal  : %02d/%02d/%04d", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
        printf("                        Waktu : %02d:%02d WIB |\n", tm->tm_hour, tm->tm_min);
        printf("\t\t\t| Nasabah  : %-52s|\n", Rekening.namaLengkap);
        printf("\t\t\t| Rekening : %-52s|\n", Rekening.NomorRekening);
        printf("\t\t\t+================================================================+\n");
        char sebaris[256];
        while(fgets(sebaris, sizeof(sebaris), MUTASI_FILE)){
            printf("%s", sebaris);
        }
        fclose(MUTASI_FILE);
    }
        printf("\t\t\t Ketik 1 untuk kembali ke menu sebelumnya: ");
        scanf("%d", &Mekanisme.pilihan);
        if(Mekanisme.pilihan == 1){
        printf("\t\t\t Mengalihkan layar");
        for(int i=0; i<3; i++){
            delay(100000000);
            printf(".");
        }
        system("cls");
        tampilanInformasiAkun();
        } else{
        printf("\t\t\t Pilihan tidak dikenali!\n");
        printf("\t\t\t Harap ketik 1 untuk kembali ke menu utama: ");
        scanf("%s", &Mekanisme.pilihanInvalid);
        switch(Mekanisme.pilihanInvalid){
        case '1' :
            system("cls");
            tampilanInformasiAkun();
            break;
        default :
            printf("\t\t\t Mengalihkan layar");
            for(int i=0; i<3; i++){
               delay(100000000);
               printf(".");
            }
            system("cls");
            tampilanMenuAwal();
            break;
        }
    }
}
void tampilanTentangKami(){
    informasi2 Mekanisme;
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t|                        [ mobiStats 5 ]                         |\n");
    printf("\t\t\t|                 << BANK SENTRAL STATISTIK >>                   |\n");
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t||oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo||\n");
    printf("\t\t\t||--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--||\n");
    printf("\t\t\t||oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo||\n");
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t|                     TENTANG mobiStats 5                        |\n");
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t|                                                                |\n");
    printf("\t\t\t|           mobiStats 5 merupakan kombinasi antara               |\n");
    printf("\t\t\t|            sistem perbankan dan dompet digital.                |\n");
    printf("\t\t\t|                                                                |\n");
    printf("\t\t\t|    Program ini dikembangkan untuk memberikan kemudahan akses   |\n");
    printf("\t\t\t|      layanan keuangan secara digital. Fitur utama meliputi     |\n");
    printf("\t\t\t|   layanan transfer, layanan digital, serta layanan pemerintah  |\n");
    printf("\t\t\t|    Dirancang dengan standar keamanan perbankan, aplikasi ini   |\n");
    printf("\t\t\t|           mendukung efisiensi dan kenyamanan nasabah.          |\n");
    printf("\t\t\t|                                                                |\n");
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t|                           CREDITS                              |\n");
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t|                                                                |\n");
    printf("\t\t\t|       CO-FOUNDER : Abdul Hafidz Khaerul I. (222413464)         |\n");
    printf("\t\t\t|       CO-FOUNDER : Akhmad Alief Hibatullah (222413484)         |\n");
    printf("\t\t\t|       CO-FOUNDER : Khaira Parsha Zarita    (222413628)         |\n");
    printf("\t\t\t|                                                                |\n");
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t|                                                                |\n");
    printf("\t\t\t| PT BANK SENTRAL STATISTIK Tbk. berizin dan diawasi oleh Badan  |\n");
    printf("\t\t\t|     Pusat Statistik dan Bank Indonesia(BI), serta merupakan    |\n");
    printf("\t\t\t|        peserta penjaminan Lembaga Penjamin Simpanan(LPS)       |\n");
    printf("\t\t\t|             Copyright © 2025 Bank SENTRAL STATISTIK            |\n");
    printf("\t\t\t|                                                                |\n");
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t Ketik 1 untuk kembali ke menu sebelumnya: ");
    scanf("%d", &Mekanisme.pilihan);
    if(Mekanisme.pilihan == 1){
        printf("\t\t\t Mengalihkan layar");
        for(int i=0; i<3; i++){
            delay(100000000);
            printf(".");
        }
        system("cls");
        tampilanInformasiAkun();
        } else{
        printf("Pilihan tidak dikenali!\n");
        printf("Harap ketik 1 untuk kembali ke menu utama: ");
        scanf("%s", &Mekanisme.pilihanInvalid);
        switch(Mekanisme.pilihanInvalid){
        case '1' :
            system("cls");
            tampilanInformasiAkun();
            break;
        default :
            printf("\t\t\t Mengalihkan layar");
            for(int i=0; i<3; i++){
               delay(100000000);
               printf(".");
            }
            system("cls");
            tampilanMenuAwal();
            break;
        }
    }
  }
void tampilanStruk(const char *nomorReferensi, const char *jenisTransaksi, const char *kodeStruk, const char *tujuanTransaksi, const char *tujuanTambahan, double biayaAdmin, double nominal, double total, const char *keterangan){
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    informasiDiri data;
    informasi2 nilai;
    REKENING_FILE = fopen("DataRekeningNasabah.txt", "r");
    if(REKENING_FILE == NULL){
        printf("\t\t\t Data Rekening tidak dikenali!\n");
    }
    else{
        fscanf(REKENING_FILE, "%[^\n]", data.namaLengkap);
        fscanf(REKENING_FILE, "%s", data.NomorRekening);
        fclose(REKENING_FILE);
    }
    printf("\t\t\t+==========================================================+\n");
    printf("\t\t\t|                     [ mobiStats 5 ]                      |\n");
    printf("\t\t\t|              << BANK SENTRAL STATISTIK >>                |\n");
    printf("\t\t\t+==========================================================+\n");
    printf("\t\t\t||-oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo-||\n");
    printf("\t\t\t||o--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--o||\n");
    printf("\t\t\t||-oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo-||\n");
    printf("\t\t\t+==========================================================+\n");
    printf("\t\t\t|   |                                                  |   |\n");
    printf("\t\t\t|   |               TRANSAKSI BERHASIL                 |   |\n");
    printf("\t\t\t|   |                                                  | B |\n");
    printf("\t\t\t|   |   Nomor Referensi   : %-25s  | A |\n", nomorReferensi);
    printf("\t\t\t|   |   Waktu Transaksi   : %02d.%02d.%02d                   | N |\n", tm->tm_hour, tm->tm_min, tm->tm_sec);
    printf("\t\t\t|   |   Tanggal Transaksi : %02d/%02d/%04d                 | K |\n", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
    printf("\t\t\t| m |   Jenis Transaksi   : %-27s|   |\n", jenisTransaksi);
    printf("\t\t\t| o |__________________________________________________| S |\n");
    printf("\t\t\t| b |                                                  | E |\n");
    printf("\t\t\t| i |                                                  | N |\n");
    printf("\t\t\t|   |   Nama Nasabah      : %-27s| T |\n", data.namaLengkap);
    printf("\t\t\t|   |   Nomor Rekening    : %-27s| R |\n", data.NomorRekening);
    printf("\t\t\t| s |                                                  | A |\n");
    printf("\t\t\t| t |   Kode Struk        : %-27s| L |\n", kodeStruk);
    printf("\t\t\t| a |   Tujuan Transaksi  : %-27s|   |\n", tujuanTransaksi);
    printf("\t\t\t| t |                       %-27s| S |\n", tujuanTambahan);
    printf("\t\t\t| s |                                                  | T |\n");
    printf("\t\t\t|   |   Biaya Admin       : Rp%-25.0lf| A |\n", biayaAdmin);
    printf("\t\t\t|   |   Nominal Transfer  : Rp%-25.0lf| T |\n", nominal);
    printf("\t\t\t| 5 |   Total             : Rp%-25.0lf| I |\n", total);
    printf("\t\t\t|   |   Keterangan        : %-27s| S |\n", keterangan);
    printf("\t\t\t|   |                                                  | T |\n");
    printf("\t\t\t|   |                                                  | I |\n");
    printf("\t\t\t|   |          Powered by mobiStats Technology         | K |\n");
    printf("\t\t\t|   |      Reliable. Secure. Terpercaya. Statistik.    |   |\n");
    printf("\t\t\t|   |                                                  |   |\n");
    printf("\t\t\t+==========================================================+\n");
    printf("\t\t\t|          PT BANK SENTRAL STATISTIK Tbk. berizin          |\n");
    printf("\t\t\t|            dan diawasi oleh BPS dan BI, serta            |\n");
    printf("\t\t\t|             merupakan peserta penjaminan LPS             |\n");
    printf("\t\t\t|         Copyright © 2025 Bank SENTRAL STATISTIK          |\n");
    printf("\t\t\t+==========================================================+\n");
    nilai.saldo = bacaSaldo();
    printf("\t\t\t Saldo terkini : Rp%.2lf\n", nilai.saldo);
    printf("\t\t\t Kembali ke menu utama? (y/t) : ");
    scanf("%s", &nilai.batalTransaksi);
    switch(nilai.batalTransaksi){
    case 'Y':
        printf("\t\t\t Mengembalikan ke menu utama");
        for(int i=0; i<3; i++){
            delay(100000000);
            printf(".");
        }
        system("cls");
        tampilanMenuUtama();
        break;
    case 'y':
        printf("\t\t\t Mengembalikan ke menu utama");
        for(int i=0; i<3; i++){
            delay(100000000);
            printf(".");
        }
        system("cls");
        tampilanMenuUtama();
        break;
    case 'T':
        printf("\t\t\t Mengembalikan ke login page");
        for(int i=0; i<3; i++){
            delay(100000000);
            printf(".");
        }
        system("cls");
        tampilanMenuAwal();
        break;
    case 't':
        printf("\t\t\t Mengembalikan ke login page");
        for(int i=0; i<3; i++){
            delay(100000000);
            printf(".");
        }
        system("cls");
        tampilanMenuAwal();
        break;
    default :
        printf("\t\t\t Pilihan tidak dikenali!\n");
        system("pause");
        printf("\t\t\t Mengembalikan ke login page");
        for(int i=0; i<3; i++){
            delay(100000000);
            printf(".");
        }
        system("cls");
        tampilanMenuAwal();
        break;
    }
}
void logoutPage(){
    informasiDiri data;
    DATADIRI_FILE = fopen("DataNasabah.txt", "r");
    if(DATADIRI_FILE == NULL){
        "\t\t\t Informasi nama tidak dikenali!\n";
    }
    else{
        fscanf(DATADIRI_FILE, "%s\n", data.namaDepan);
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                        [ mobiStats 5 ]                         |\n");
        printf("\t\t\t|                 << BANK SENTRAL STATISTIK >>                   |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t||oo--oo--oo--oo--oo-|                     |--oo--oo--oo--oo--oo||\n");
        printf("\t\t\t||--oo--oo--oo--oo--o| >> LOG-OUT PAGE <<  |oo--oo--oo--oo--oo--||\n");
        printf("\t\t\t||oo--oo--oo--oo--oo-|                     |--oo--oo--oo--oo--oo||\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                                                                |\n");
        printf("\t\t\t|                      Terima Kasih %-29s|\n", toupper(data.namaDepan));
        printf("\t\t\t|          telah mempercayai dan menggunakan layanan kami        |\n");
        printf("\t\t\t|                                                                |\n");
        printf("\t\t\t+================================================================+\n");
        fclose(DATADIRI_FILE);
    }
}
void tampilanPLN(){
    int inputValid = 0;
    char konfirmasiJawab;
    informasiDiri Rekening;
    informasi2 Mekanisme;
    InformasiPLN Mekanismelistrik;
    do{
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    REKENING_FILE = fopen("DataRekeningNasabah.txt", "r");
    if(REKENING_FILE == NULL){
        printf("\t\t\t Rekening tidak terbaca!\n");
    }
    else{
        fscanf(REKENING_FILE, "%[^\n]", &Rekening.namaLengkap);
        fscanf(REKENING_FILE, "%s\n", &Rekening.NomorRekening);
        fclose(REKENING_FILE);
    }
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t|                        [ mobiStats 5 ]                         |\n");
    printf("\t\t\t|                 << BANK SENTRAL STATISTIK >>                   |\n");
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t||oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo||\n");
    printf("\t\t\t||--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--||\n");
    printf("\t\t\t||oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo||\n");
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t|                            PT.PLN                              |\n");
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t|                                                                |\n");
    printf("\t\t\t|             Daftar Harga Listrik Pasca dalam Sebulan           |\n");
    printf("\t\t\t|                                                                |\n");
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t|                                                                |\n");
    printf("\t\t\t|          --------------------------------------------          |\n");
    printf("\t\t\t|          ||  Daya rumah tangga  ||  Harga per kWh  ||          |\n");
    printf("\t\t\t|          --------------------------------------------          |\n");
    printf("\t\t\t|          ||  450-1299 VA        ||  Rp 1.352       ||          |\n");
    printf("\t\t\t|          ||  1300-3499 VA       ||  Rp 1.444,70    ||          |\n");
    printf("\t\t\t|          ||  3500 VA            ||  Rp 2.699,53    ||          |\n");
    printf("\t\t\t|          --------------------------------------------          |\n");
    printf("\t\t\t|                                                                |\n");
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t| PT BANK SENTRAL STATISTIK Tbk. berizin dan diawasi oleh Badan  |\n");
    printf("\t\t\t|     Pusat Statistik dan Bank Indonesia(BI), serta merupakan    |\n");
    printf("\t\t\t|        peserta penjaminan Lembaga Penjamin Simpanan(LPS)       |\n");
    printf("\t\t\t|             Copyright © 2025 Bank SENTRAL STATISTIK            |\n");
    printf("\t\t\t+================================================================+\n");
    printf("\t\t\t Ingin membatalkan transaksi dan kembali ke menu sebelumnya? (Y/T):  ");
    scanf("%s", &Mekanisme.batalTransaksi);
    getchar();
    if(Mekanisme.batalTransaksi == 'y' || Mekanisme.batalTransaksi == 'Y'){
        printf("\t\t\t Mengalihkan layar");
        for(int i=0; i<3; i++){
            delay(100000000);
            printf(".");
        }
        tampilanSubmenuPemerintah();
    }
    else if(Mekanisme.batalTransaksi == 't' || Mekanisme.batalTransaksi == 'T'){
    }
    else{
        printf("\t\t\t Pilihan tidak dikenali!\n");
        printf("\t\t\t Ingin mengulangi layanan pembayaran? (y/t): ");
        scanf("%s", &Mekanisme.pilihanInvalid);
        switch(Mekanisme.pilihanInvalid){
        case 'Y' :
            system("cls");
            tampilanPLN();
            break;
        case 'y' :
            system("cls");
            tampilanPLN();
            break;
        case 'T' :
            system("cls");
            tampilanSubmenuPemerintah();
            break;
        case 't' :
            system("cls");
            tampilanSubmenuPemerintah();
            break;
        default :
            printf("\t\t\t Mengalihkan layar ");
            for(int i=0; i<3; i++){
               delay(100000000);
               printf(".");
            }
            system("cls");
            tampilanPLN();
            break;
        }
    }
    printf("\t\t\t 5 digit awal nomor meteran(10987)\n");
    printf("\t\t\t Masukkan nomor meteran listrik Anda(10-11 digit)  : ");
    gets(Mekanismelistrik.nomorlistrikpascabayar);
    if(validasiNoListrikPascaBayar(Mekanismelistrik.nomorlistrikpascabayar)){
        printf("\t\t\t Nomor meteran listrik tidak tersedia! ");
        system("pause");
        printf("\t\t\t Mengembalikan layar");
        for(int i=0; i<3; i++){
            delay(100000000);
            printf(".");
        }
        system("cls");
        continue;
    }
    printf("\t\t\t Masukkan Besar Daya listrik rumah anda(VA) : ");
    scanf("%d", &Mekanismelistrik.Dayalistrik);
    getchar();
    if(Mekanismelistrik.Dayalistrik < 450 || Mekanismelistrik.Dayalistrik > 3500){
        printf("\t\t\t Besar daya tidak sesuai dengan ketentuan! ");
        system("pause");
        printf("\t\t\t Mengembalikan layar");
        for(int i=0; i<3; i++){
            delay(100000000);
            printf(".");
        }
        system("cls");
        continue;
    }
    printf("\t\t\t Masukkan nama pemilik [Max 30]             : ");
    gets(Mekanismelistrik.namaPemilik);
    if(!validasiNamaLengkap(Mekanismelistrik.namaPemilik)){
        printf("\t\t\t Nama tidak memenuhi ketentuan! ");
        system("pause");
        printf("\t\t\t Mengembalikan layar");
        for(int i=0; i<3; i++){
            delay(100000000);
            printf(".");
        }
        system("cls");
        continue;
    }
    printf("\t\t\t Lama pemakaian (perHari)                   : ");
    scanf("%d", &Mekanismelistrik.periode);
    if(Mekanismelistrik.periode <= 0){
        printf("\t\t\t Periode tidak sesuai! ");
        system("pause");
        for(int i=0; i<3; i++){
            delay(100000000);
            printf(".");
        }
        system("cls");
        continue;
    }
    if(Mekanismelistrik.Dayalistrik >= 450 && Mekanismelistrik.Dayalistrik <= 1299){Mekanismelistrik.nominal = 1352;}
    else if(Mekanismelistrik.Dayalistrik>=1300 && Mekanismelistrik.Dayalistrik <= 3499){Mekanismelistrik.nominal = 1444.7;}
    else if(Mekanismelistrik.Dayalistrik = 3500){Mekanismelistrik.nominal = 2699.53;}
    else{Mekanismelistrik.nominal = 0;}
    printf("\t\t\t Masukkan pin Transaksi                     : ");
    scanf("%s", &Rekening.pinTransaksi);
    if (password(Rekening.pinTransaksi)){
            if(validasiSaldo((Mekanismelistrik.nominal*Mekanismelistrik.periode)+1500)){
                printf("\t\t\t Ingin melakukan pembayaran (Y/T): ");
                scanf("%s", &Mekanisme.batalTransaksi);
                if(Mekanisme.batalTransaksi =='y'||Mekanisme.batalTransaksi=='y'){
                    inputValid = 1;
                }
                else if(Mekanisme.batalTransaksi =='t'||Mekanisme.batalTransaksi =='T'){
                    printf("\t\t\t Mengembalikan layar");
                    for(int i=0; i<3; i++){
                        delay(100000000);
                        printf(".");
                    }
                    tampilanSubmenuPemerintah();
                }
                else{
                    printf("\t\t\t Pilihan tidak dikenali! ");
                    system("pause");
                    printf("\t\t\t Mengalihkan layar");
                    for(int i=0; i<3; i++){
                        delay(10000000000);
                        printf(".");
                    }
                    tampilanSubmenuPemerintah();
                }
            }
            else{
                printf("\t\t\t Maaf, saldo Anda tidak mencukupi untuk bertransaksi!\n");
                system("pause");
                printf("\t\t\t Mengembalikan layar");
                for(int i=0; i<3; i++){
                    delay(100000000);
                    printf(".");
                }
                system("cls");
                continue;
            }
        } else {
            printf("\t\t\t Password salah!\n");
            system("pause");
            printf("\t\t\t Ingin kembali ke menu sebelumnya? (y/t) : ");
            scanf("%s", &Mekanisme.batalTransaksi);
            if (Mekanisme.batalTransaksi == 'Y' || Mekanisme.batalTransaksi == 'y') {
                printf("\t\t\t Mengalihkan layar");
                for (int i = 0; i < 3; i++) {
                    delay(100000000);
                    printf(".");
                }
                system("cls");
                tampilanESIM();
            } else if (Mekanisme.batalTransaksi == 'T' || Mekanisme.batalTransaksi == 't') {
                system("cls");
                continue;
            } else {
                printf("\t\t\t Pilihan tidak dikenali!");
                system("pause");
                continue;
            }
        }
        inputValid = 1;
    }while(!inputValid);
    printf("\t\t\t Mengalihkan layar");
    for(int i=0; i<3; i++){
        delay(100000000);
        printf(".");
    }
    system("cls");
    tampilanFinalPln(Mekanismelistrik.namaPemilik, Mekanismelistrik.nomorlistrikpascabayar, Mekanismelistrik.Dayalistrik, Mekanismelistrik.nominal, Mekanismelistrik.periode);
}
void tampilanFinalPln(const char *namaPemilik, const char *NomorMeteranPasca, int dayaListrik, double Nominal, int periode){
    InformasiESIM biaya;
    informasi2 Mekanisme;
    informasiDiri user;
    InformasiPLN MekanismeListrik;
    int valid = 0;
    Mekanisme.saldo = bacaSaldo();
    do {
        MekanismeListrik.totalBayar = (Nominal*periode) + 1500;
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                        [ mobiStats 5 ]                         |\n");
        printf("\t\t\t|                 << BANK SENTRAL STATISTIK >>                   |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t||oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo||\n");
        printf("\t\t\t||--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--||\n");
        printf("\t\t\t||oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo--oo||\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                              PLN                               |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t| Jenis Pembayaran Listrik    : PLN Pascabayar                   |\n");
        printf("\t\t\t| Nomor Meteran Listrik       : %-33s|\n", NomorMeteranPasca);
        printf("\t\t\t| Nama Pemilik                : %-33s|\n", namaPemilik);
        printf("\t\t\t| Daya Rumah Tangga           : %-33d|\n", dayaListrik);
        printf("\t\t\t| Sumber Aliran Dana          : Pribadi                          |\n");
        printf("\t\t\t| Tujuan Aliran Dana          : PT PLN Persero                   |\n");
        printf("\t\t\t| Nominal Pembayaran          : Rp%-31.2lf|\n", Nominal);
        printf("\t\t\t| Periode bayar               : %-33.0d|\n", periode);
        printf("\t\t\t| Biaya operasional           : Rp1500                           |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t+                               |                                +\n");
        printf("\t\t\t|       Total Pembayaran        |             Rp%-10.2lf       |\n", MekanismeListrik.totalBayar);
        printf("\t\t\t+                               |                                +\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t|                                                                |\n");
        printf("\t\t\t| PT BANK SENTRAL STATISTIK Tbk. berizin dan diawasi oleh Badan  |\n");
        printf("\t\t\t|     Pusat Statistik dan Bank Indonesia(BI), serta merupakan    |\n");
        printf("\t\t\t|        peserta penjaminan Lembaga Penjamin Simpanan(LPS)       |\n");
        printf("\t\t\t|             Copyright © 2025 Bank SENTRAL STATISTIK            |\n");
        printf("\t\t\t|                                                                |\n");
        printf("\t\t\t+================================================================+\n");
        printf("\t\t\t Lanjut bayar? (y/t) : ");
        scanf("%s", &Mekanisme.batalTransaksi);
        if(Mekanisme.batalTransaksi == 'Y' || Mekanisme.batalTransaksi =='y'){
            valid = 1;
        }
        else if(Mekanisme.batalTransaksi == 't' || Mekanisme.batalTransaksi == 'T'){
            printf("\t\t\t Mengembalikan layar");
            for(int i =0; i<3; i++){
                delay(100000000);
                printf(".");
            }
            system("cls");
            tampilanPLN();
        }
        else{
            printf("\t\t\t Pilihan tidak dikenali! ");
            system("pause");
            for(int i=0; i<3; i++){
                delay(100000000);
                printf(".");
            }
            system("cls");
            continue;
        }
        valid = 1;
    } while (!valid);
    strcpy(Mekanisme.jenisTransaksi, "Layanan Pemerintah - PLN");
    strcpy(Mekanisme.tipeTransaksi, "Listrik");
    strcpy(Mekanisme.nomorTransaksi, generatorRandNum());
    strcpy(Mekanisme.kodeTransaksi, generatorUnCode());
    strcpy(Mekanisme.tujuanTransaksi, "Perumahan - ");
    strcpy(Mekanisme.keterangan, NomorMeteranPasca);
    strcat(Mekanisme.tujuanTransaksi, Mekanisme.tipeTransaksi);
    Mekanisme.biayaAdmin = 1500;
    Mekanisme.saldo -= MekanismeListrik.totalBayar;
    printf("\t\t\t Menampilkan struk");
    for(int i=0; i<3; i++){
        delay(100000000);
        printf(".");
    }
    system("cls");
    simpanPerbaruiSaldo(Mekanisme.saldo);
    SimpanTransaksiKeFile(Mekanisme.total, Mekanisme.keterangan, Mekanisme.kodeTransaksi, Mekanisme.jenisTransaksi, Mekanisme.tipeTransaksi);
    tampilanStruk(Mekanisme.nomorTransaksi, Mekanisme.jenisTransaksi, Mekanisme.kodeTransaksi, Mekanisme.tujuanTransaksi, Mekanisme.tujuanTambahan, Mekanisme.biayaAdmin, Mekanisme.nominal, Mekanisme.total, Mekanisme.keterangan);
}
//Program ini disusun oleh :
// Abdul Hafidz Khaerul Imam (222413464)
// Akhmad Alief Aflah Hibatullah (222413484)
// Khaira Parsha Zarita (2224134628)
