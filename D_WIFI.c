#include <stdio.h>
#include <string.h>
#include <stdlib.h>
FILE *file;
FILE *riwayat_file;
//admin fungsi
void adminMenu();
void data_user();
void hapus_data();
void jenis_wifi();
void info_pesanan();
void ubah_kecepatan();
void riwayat_pembeli();

//usser fungsi
void registrasiUser();
void userLogin();
void userMenu ();
void lihat_jenis();
void pilih_jenis();
void riwayat_beli();
void info_wifi();
void request_kecepatan();
void ubah_akun();
struct User {
    char nama[50];
    char alamat[100];
    char no_hp[15];
    char username[20];
    char password[20];
};
struct Wifi {
    char jenis[50];
    float harga;
};
struct RiwayatBeli {
    char nama_wifi[50];
    char password_wifi[50];
    char nama_user[50];
    char jenis_wifi[50];
    float kecepatan;
    float kecepatan_baru;
    float harga_total;
};
int main(){
    int x;
    
    printf("========\n\n");
    printf("1. Admin\n");
    printf("2. User\n");
    printf("pilih ==== > ");
    scanf("%d", &x);

    if(x == 1){
        char admin_username[20];
        char admin_password[20];

        printf("\nMasukkan username admin: ");
        scanf("%s", admin_username);

        printf("Masukkan password admin: ");
        scanf("%s", admin_password);

        // Periksa apakah username dan password sesuai dengan admin
        if(strcmp(admin_username, "admin") == 0 && strcmp(admin_password, "admin") == 0){
            printf("\nLogin admin berhasil!\n");
            adminMenu();
        } else {
            printf("\nUsername atau password salah. Akses ditolak.\n");
        }
    } else if(x == 2){
        int user_choice;
        printf("\n1. Registrasi\n");
        printf("2. Login\n");
        printf("Pilih opsi untuk user: ");
        scanf("%d", &user_choice);

        // Tambahkan logika untuk registrasi dan login user di sini
        if(user_choice == 1){
            registrasiUser();
        } else if(user_choice == 2){
            userLogin();
        } else {
            printf("Opsi tidak valid.\n");
        }
    } else {
        printf("Pilihan tidak valid.\n");
    }

    return 0;
}
struct User newUser;
void registrasiUser() {
    fflush(stdin);
    printf("Masukkan nama: ");
    gets(newUser.nama);

    printf("Masukkan alamat: ");
    gets(newUser.alamat);

    printf("Masukkan nomor HP: ");
    gets(newUser.no_hp);

    printf("Buat username: ");
    gets(newUser.username);

    printf("Buat password: ");
    gets(newUser.password);

    
    file = fopen("user_data.bin", "ab");
    if (file != NULL) {
        fwrite(&newUser, sizeof(struct User), 1, file);
        fclose(file);
        printf("Registrasi berhasil. Data user telah disimpan.\n");
        main();
    } else {
        printf("Gagal membuka file.\n");
    }
}
void userLogin() {
    char input_username[20];
    char input_password[20];
    int login_success = 0;

    printf("Masukkan username: ");
    scanf("%s", input_username);

    printf("Masukkan password: ");
    scanf("%s", input_password);

    FILE *file = fopen("user_data.bin", "rb");
    if (file != NULL) {
        struct User currentUser;
        while (fread(&currentUser, sizeof(struct User), 1, file)) {
            if (strcmp(currentUser.username, input_username) == 0 && strcmp(currentUser.password, input_password) == 0) {
                login_success = 1;
                break;
            }
        }
        fclose(file);
    } else {
        printf("Gagal membuka file.\n");
        return;
    }

    if (login_success) {
        printf("Login berhasil!\n");
        userMenu();
    } else {
        printf("Username atau password salah. Silakan coba lagi.\n");
        userLogin(); // Jika login gagal, minta input kembali
    }
}
void adminMenu(){
    int pilihan;
    printf("MENU ADMIN : \n");
    printf("===(1) DATA USER===\n");
    printf("===(2) HAPUS DATA USER===\n");
    printf("===(3) RIWAYAT PEMBELIAN===\n");
    printf("===(4) JENIS WIFI ===\n");
    printf("=== (5) MENGUBAH DAN KONFIRMASI KECEPATAN WIFI PELANGGAN ===\n");
    printf("=== (6) INFORMASI PESANAN ===\n");
    printf("=== (7) LOG OUT ===\n");
    printf("Pilihan: ");
    scanf("%d", &pilihan);
    switch(pilihan) {
        case 1:
            system("cls");
            data_user();
            break;
        case 2:
            system("cls");
            hapus_data();
            break;
        case 3:
            system("cls");
            riwayat_pembeli();
            break;
        case 4:
            system("cls");
            jenis_wifi();
            break;
        case 5:
            system("cls");
            ubah_kecepatan();
            break;
        case 6:
            system("cls");
            info_pesanan();
            break;
        case 7:
            main();
            break;
        default:
            printf("Pilihan tidak valid.\n");
            break;
    }
}
void data_user() {
    FILE *file = fopen("user_data.bin", "rb");
    if (file != NULL) {
        struct User currentUser;
        printf("=== DATA USER ===\n");
        printf("%-20s %-30s %-15s %-20s\n", "Nama", "Alamat", "Nomor HP", "Username");
        while (fread(&currentUser, sizeof(struct User), 1, file)) {
            printf("%-20s %-30s %-15s %-20s\n", currentUser.nama, currentUser.alamat, currentUser.no_hp, currentUser.username);
        }
        fclose(file);
    } else {
        printf("Gagal membuka file.\n");
    }
    system("pause");
    adminMenu();
}
void hapus_data() {
    char nama_hapus[50];
    printf("Masukkan nama user yang ingin dihapus: ");
    scanf(" %[^\n]s", nama_hapus);

    FILE *temp_file = fopen("temp.bin", "wb"); 
    FILE *file = fopen("user_data.bin", "rb");
    if (file != NULL && temp_file != NULL) {
        struct User currentUser;
        int found = 0;
        while (fread(&currentUser, sizeof(struct User), 1, file)) {
            if (strcmp(currentUser.nama, nama_hapus) != 0) {
                fwrite(&currentUser, sizeof(struct User), 1, temp_file); 
            } else {
                found = 1; 
            }
        }
        fclose(file);
        fclose(temp_file);

        remove("user_data.bin"); // Menghapus file user_data.bin
        rename("temp.bin", "user_data.bin"); // Mengubah nama file sementara menjadi user_data.bin

        if (found) {
            printf("Data user dengan nama '%s' telah dihapus.\n", nama_hapus);
        } else {
            printf("Data user tidak ditemukan.\n");
        }
    } else {
        printf("Gagal membuka file.\n");
    }
    system("pause");
    adminMenu();
}
void riwayat_pembeli() {
    FILE *riwayat_file = fopen("riwayat_beli.bin", "rb");
    if (riwayat_file != NULL) {
        struct RiwayatBeli riwayat;

        printf("=== RIWAYAT PEMBELIAN ===\n");
        printf("%-20s %-20s %-15s %-15s\n", "Nama User", "Jenis WiFi", "Kecepatan", "Harga Total");
        
        while (fread(&riwayat, sizeof(struct RiwayatBeli), 1, riwayat_file)) {
            printf("%-20s %-20s %-15.2f %-15.2f\n", riwayat.nama_user, riwayat.jenis_wifi,
                   riwayat.kecepatan, riwayat.harga_total);
        }

        fclose(riwayat_file);
    } else {
        printf("Tidak ada riwayat pembelian.\n");
    }
    system("pause");
    adminMenu();
}
void jenis_wifi() {
    int jumlah;
    printf("Masukkan jumlah jenis WiFi baru: ");
    scanf("%d", &jumlah);

    FILE *file = fopen("jenis_wifi.bin", "ab");
    if (file != NULL) {
        
        struct Wifi newWifi;

        for (int i = 0; i < jumlah; ++i) {
            fflush(stdin);
            printf("Masukkan jenis WiFi ke-%d: ", i + 1);
            gets(newWifi.jenis);

            printf("Masukkan harga WiFi untuk jenis %s: ", newWifi.jenis);
            scanf("%f", &newWifi.harga);

            fwrite(&newWifi, sizeof(struct Wifi), 1, file);
        }

        fclose(file);
        printf("Data jenis WiFi telah disimpan.\n");
    } else {
        printf("Gagal membuka file.\n");
    }
    system("pause");
    adminMenu();
}
void info_pesanan() {
    FILE *riwayat_file = fopen("riwayat_beli.bin", "rb");
    if (riwayat_file != NULL) {
        struct RiwayatBeli riwayat;

        printf("=== REQUEST KECEPATAN ===\n");
        printf("%-20s %-20s %-15s\n", "Nama User", "Jenis WiFi", "Kecepatan Baru");

        while (fread(&riwayat, sizeof(struct RiwayatBeli), 1, riwayat_file)) {
            if (riwayat.kecepatan_baru != 0) {
                printf("%-20s %-20s %-15.2f\n", riwayat.nama_user, riwayat.jenis_wifi, riwayat.kecepatan_baru);
            }
        }

        fclose(riwayat_file);
    } else {
        printf("Tidak ada request kecepatan yang tersedia.\n");
    }
    system("pause");
    adminMenu();
    
}
void ubah_kecepatan() {
    char nama_user[50];
    char jenis_wifi[50];
    float kecepatan_baru;

    printf("Masukkan nama user: ");
    scanf(" %[^\n]s", nama_user);

    printf("Masukkan jenis WiFi yang ingin diubah kecepatannya: ");
    scanf(" %[^\n]s", jenis_wifi);

    printf("Masukkan kecepatan WiFi baru (Mbps): ");
    scanf("%f", &kecepatan_baru);
    FILE *riwayat_file = fopen("riwayat_beli.bin", "rb+");
    if (riwayat_file != NULL) {
        struct RiwayatBeli riwayat;
        int found = 0;
        while (fread(&riwayat, sizeof(struct RiwayatBeli), 1, riwayat_file)) {
            if (strcmp(riwayat.nama_user, nama_user) == 0 && strcmp(riwayat.jenis_wifi, jenis_wifi) == 0) {
                found = 1;
                riwayat.kecepatan = kecepatan_baru;
                fseek(riwayat_file, -sizeof(struct RiwayatBeli), SEEK_CUR);
                fwrite(&riwayat, sizeof(struct RiwayatBeli), 1, riwayat_file);
                break;
            }
        }

        fclose(riwayat_file);

        if (found) {
            printf("Kecepatan WiFi untuk user '%s' pada jenis WiFi '%s' telah diubah menjadi %.2f Mbps.\n", nama_user, jenis_wifi, kecepatan_baru);
        } else {
            printf("Data tidak ditemukan.\n");
        }
    } else {
        printf("Gagal membuka file riwayat_beli.bin.\n");
    }

    system("pause");
    adminMenu(); 
}
void userMenu(){
    int a;
    printf("MENU USER : \n");
    printf("===(1) Melihat Jenis, dan Harga===\n");
    printf("===(2) Memilih Jenis, dan kecepatan Koneksi Wifi===\n");
    printf("===(3) Mengubah Username dan password Akun atau Wifi===\n");
    printf("===(4) Request kecepatan wifi ===\n");
    printf("===(5) informasi wifi ===\n");
    printf("===(6) Melihat Riwayat Transaksi ===\n");
    printf("===(7) keluar ===\n");
    printf("Pilihan: ");
    scanf("%d", &a);
    switch(a) {
        case 1:
            system("cls");
            lihat_jenis();
            break;
            system("pause");
        case 2:
            system("cls");
            pilih_jenis();
            break;
            system("pause");
        case 3:
            system("cls");
            ubah_akun();
            break;
        case 4:
            system("cls");
            request_kecepatan();
        case 5:
            system("cls");
            info_wifi();
            break;
        case 6:
            system("cls");
            riwayat_beli();
            break;
        case 7:
            main();
            break;
        default:
            printf("Pilihan tidak valid.\n");
            break;
    }
}
void lihat_jenis() {
    FILE *file = fopen("jenis_wifi.bin", "rb");
    if (file != NULL) {
        struct Wifi {
            char jenis[50];
            float harga;
        } wifi;

        printf("=== JENIS WIFI DAN HARGA ===\n");
        printf("%-30s %s\n", "Jenis WiFi", "Harga");
        while (fread(&wifi, sizeof(struct Wifi), 1, file)) {
            printf("%-30s %.2f\n", wifi.jenis, wifi.harga);
        }

        fclose(file);
    } else {
        printf("Gagal membuka file jenis_wifi.bin.\n");
    }
    system("pause");
    userMenu();
}
void pilih_jenis() {
    FILE *jenis_file = fopen("jenis_wifi.bin", "rb");
    if (jenis_file != NULL) {
        struct Wifi {
            char jenis[50];
            float harga;
        } wifi;

        printf("=== JENIS WIFI DAN HARGA ===\n");
        printf("%-30s %s\n", "Jenis WiFi", "Harga");
        while (fread(&wifi, sizeof(struct Wifi), 1, jenis_file)) {
            printf("%-30s %.2f\n", wifi.jenis, wifi.harga);
        }

        fclose(jenis_file);

        char jenis_dibeli[50];
        printf("\nMasukkan jenis WiFi yang ingin dibeli: ");
        scanf(" %[^\n]s", jenis_dibeli);

        float kecepatan;
        printf("Masukkan kecepatan yang diinginkan (Mbps): ");
        scanf("%f", &kecepatan);

        FILE *file = fopen("jenis_wifi.bin", "rb");
        if (file != NULL) {
            struct Wifi wifi_pembelian;
            int found = 0;

            while (fread(&wifi_pembelian, sizeof(struct Wifi), 1, file)) {
                if (strcmp(wifi_pembelian.jenis, jenis_dibeli) == 0) {
                    found = 1;
                    float harga_total = kecepatan * wifi_pembelian.harga;

                    printf("\nHarga yang harus dibayar: %.2f\n", harga_total);

                    float pembayaran;
                    printf("Masukkan jumlah pembayaran: ");
                    scanf("%f", &pembayaran);

                    if (pembayaran == harga_total) {
                        char nama_wifi[50];
                        char password_wifi[20];

                        printf("\nMasukkan nama WiFi: ");
                        scanf(" %[^\n]s", nama_wifi);
                        printf("Masukkan password WiFi: ");
                        scanf(" %[^\n]s", password_wifi);

                         printf("Pembelian WiFi '%s' dengan kecepatan %.2f Mbps berhasil.\n", jenis_dibeli, kecepatan);
    printf("Nama WiFi: %s\nPassword WiFi: %s\n", nama_wifi, password_wifi);

    // Simpan riwayat pembelian ke dalam file
    FILE *riwayat_file = fopen("riwayat_beli.bin", "ab");
    file = fopen("user_data.bin", "rb");
    struct RiwayatBeli riwayat;
    struct User user;
    while (fread(&user, sizeof(struct User), 1, file)){
    if (riwayat_file != NULL) {
    strcpy(riwayat.password_wifi, password_wifi);
    strcpy(riwayat.nama_wifi, nama_wifi);
    strcpy(riwayat.nama_user, user.nama);
    strcpy(riwayat.jenis_wifi, jenis_dibeli);
    riwayat.kecepatan = kecepatan;
    riwayat.harga_total = harga_total;
    }
    if (riwayat_file != NULL) {
        fwrite(&riwayat, sizeof(struct RiwayatBeli), 1, riwayat_file);
        fclose(riwayat_file);
    } else {
        printf("Gagal membuka file riwayat_beli.bin.\n");
    }
    } 
} 
else {
    printf("Jumlah pembayaran tidak sesuai dengan harga yang harus dibayar.\n");
}
    }
            }
        }
    }
system ("pause");
userMenu();
}

void riwayat_beli() {
    FILE *riwayat_file = fopen("riwayat_beli.bin", "rb");
    if (riwayat_file != NULL) {
        struct RiwayatBeli riwayat;

        printf("=== RIWAYAT PEMBELIAN ===\n");
        printf("%-20s %-20s %-15s %-15s\n", "Nama User", "Jenis WiFi", "Kecepatan", "Harga Total");
        
        while (fread(&riwayat, sizeof(struct RiwayatBeli), 1, riwayat_file)) {
            printf("%-20s %-20s %-15.2f %-15.2f\n", riwayat.nama_user, riwayat.jenis_wifi,
                   riwayat.kecepatan, riwayat.harga_total);
        }

        fclose(riwayat_file);
    } else {
        printf("Tidak ada riwayat pembelian.\n");
    }
    system("pause");
    userMenu();
}
void info_wifi() {
    FILE *riwayat_file = fopen("riwayat_beli.bin", "rb");
    if (riwayat_file != NULL) {
        struct RiwayatBeli riwayat;

        printf("=== INFORMASI WIFI ===\n");
        printf("%-20s %-20s %-20s %-20s %-15s\n", "Nama User", "Jenis WiFi", "Nama WiFi","Kecepatan", "Password WiFi");

        while (fread(&riwayat, sizeof(struct RiwayatBeli), 1, riwayat_file)) {
            printf("%-20s %-20s %-20s %-20.2f %-15s\n", riwayat.nama_user, riwayat.jenis_wifi, riwayat.nama_wifi,riwayat.kecepatan, riwayat.password_wifi);
        }

        fclose(riwayat_file);
    } else {
        printf("Tidak ada informasi WiFi yang tersedia.\n");
    }
    system("pause");
    userMenu();
}
float kecepatan_baru;
void request_kecepatan() {
    char konfirmasi;
    printf("Anda yakin ingin mengubah kecepatan WiFi? (y/n): ");
    scanf(" %c", &konfirmasi);
    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        FILE *riwayat_file = fopen("riwayat_beli.bin", "ab");
        struct RiwayatBeli riwayat;
        printf("Masukkan kecepatan WiFi baru (Mbps): ");
        scanf("%f", &kecepatan_baru);
        printf("Request kecepatan WiFi %.2f Mbps sudah terkirim\ntunggu hingga admin meng ACC\n", kecepatan_baru);
        riwayat.kecepatan_baru = kecepatan_baru;
        fwrite(&riwayat, sizeof(struct RiwayatBeli), 1, riwayat_file);
        fclose(riwayat_file);
    }
    else {
        printf("Input tidak valid.\n");
    }
    system("pause");
    userMenu();
}
void ubah_akun() {
    char jawaban[5];

    printf("Anda yakin ingin mengubah akun WiFi? (ya/tidak): ");
    scanf("%s", jawaban);

    if (strcmp(jawaban, "ya") == 0) {
        char nama_wifi_baru[50];
        char password_wifi_baru[20];

        printf("Masukkan nama WiFi baru: ");
        scanf(" %[^\n]s", nama_wifi_baru);

        printf("Masukkan password WiFi baru: ");
        scanf(" %[^\n]s", password_wifi_baru);

        // Menggunakan file riwayat_beli.bin sebagai basis perubahan data akun WiFi
        FILE *riwayat_file = fopen("riwayat_beli.bin", "rb+");
        if (riwayat_file != NULL) {
            struct RiwayatBeli riwayat;
            int found = 0;

            while (fread(&riwayat, sizeof(struct RiwayatBeli), 1, riwayat_file)) {
                // Ubah data akun WiFi pada file jika ditemukan sesuai dengan kebutuhan pengguna
                if (strcmp(riwayat.nama_user, "nama_pengguna") == 0 && strcmp(riwayat.jenis_wifi, "jenis_wifi_yang_diinginkan") == 0) {
                    found = 1;

                    // Mengubah nama WiFi dan password WiFi sesuai yang diinginkan oleh pengguna
                    strcpy(riwayat.nama_wifi, nama_wifi_baru);
                    strcpy(riwayat.password_wifi, password_wifi_baru);

                    // Mengganti data yang lama dengan data yang baru
                    fseek(riwayat_file, -sizeof(struct RiwayatBeli), SEEK_CUR);
                    fwrite(&riwayat, sizeof(struct RiwayatBeli), 1, riwayat_file);
                    break;
                }
            }

            fclose(riwayat_file);

            if (found) {
                printf("Akun WiFi berhasil diubah.\n");
            } else {
                printf("Akun WiFi tidak ditemukan.\n");
            }
        } else {
            printf("Gagal membuka file riwayat_beli.bin.\n");
        }
    } else {
        printf("Perubahan akun WiFi dibatalkan.\n");
    }

    system("pause");
    userMenu();
}