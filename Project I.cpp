#include<iostream>
#include<stdio.h>
#include<conio.h>
#include<iostream>
#include<vector>
#include<algorithm>
#include<windows.h>
#include <time.h>
#include<stdlib.h>
using namespace std;

typedef pair<int, int> ipair;

typedef struct graph{
	int v, e, max_w;
	char ten_file[129];
	vector< pair<int, ipair> > edges;
}Graph;

struct disjointsets{
	int *parent, *rank; 
	int n;
	
	disjointsets(int n){
		this->n = n;
		parent = new int[n + 1];
		rank = new int[n + 1];

		for (int i = 0; i <= n; i++){
			rank[i] = 0;
			parent[i] = i;
		}
	}
	
	int find_set(int u){
		if (u != parent[u])
			parent[u] = find_set(parent[u]);
		return parent[u];
	}
	
	void unions(int x, int y){
		if (rank[x] > rank[y])
			parent[y] = x;
		else{
			parent[x] = y;
		}
		if (rank[x] == rank[y]){
			rank[y]++;
		}
	}
};

void Hienthi_menu_chinh(void);
void Hienthi_menu_nhap(void);
void Hienthi_menu_nhap_tufile(void);
void Hienthi_huongdan_taofile(void);
void Hienthi_xem_dauvao(void);
void Hienthi_dauvao_ramanhinh(void);
void Hienthi_ketqua(void);
void Hienthi_ketqua_ramanhinh(void);
void Hienthi_menu_luachon_xemtrunggian(void);
void Hienthi_ketqua_trunggian(void);

void Xuly_menu_chinh(void);
void Xuly_menu_nhap(void);
void Xuly_nhap_tubanphim(void);
void Xuly_menu_nhap_tufile(void);
void Xuly_nhap_tufile(void);
void Xuly_nhap_taongaunhien(void);
void Tao_ngaunhien_dothi(void);
void Ghi_dothi_ngaunhien_vaograph(void);
void Ghi_dothi_ngaunhien_rafile(int*);
void Xuly_xem_dauvao(void);
void Ghi_dauvao_rafile(void);
void Xuly_ketqua(void);
void Ghi_ketqua_rafile(void);
void Thongke_thoigiantinh(void);
void Xuly_menu_luachon_xemtrunggian(void);

void Khoitao_mang(int*, int);
void Hoanvi(int*, int);
int ran(int);
void Swap(int*, int*);
void seed_ran(void);
int get_int();

void addedge(Graph*, int, int, int);
int KruskalMST(void);
int KruskalMST_file(char*);

static Graph graph, graphBanDau;
static Graph *g = &graph;
static Graph *gBanDau = &graphBanDau;
clock_t begin, end;
char tenfile_thongke[129];

int main(){
	seed_ran();

	Hienthi_menu_chinh();
	Xuly_menu_chinh();
	
	Hienthi_xem_dauvao();
	Xuly_xem_dauvao();
	
	Hienthi_ketqua();
	Xuly_ketqua();
	Hienthi_menu_luachon_xemtrunggian();
	Xuly_menu_luachon_xemtrunggian();	
	return 0;
}

void Hienthi_menu_chinh(void){
	printf("\n 0. Thoat chuong trinh");
	printf("\n 1. Nhap du lieu");
	printf("\n	  Ban chon? ");
}

void Xuly_menu_chinh(void){
	while(1){
		int choice = get_int();		
		if(choice == 0){
			exit(0);
		}
		else if(choice == 1){
			Hienthi_menu_nhap();
			Xuly_menu_nhap();
			break;
		}
		else{
			printf( " --- Nhap vao loi.  Vui long nhap lai! --- \n " );
		}
	}
}

void Hienthi_menu_nhap(void){
	system("cls");
	printf("\n 1. Tu ban phim");
	printf("\n 2. Tu file");
	printf("\n 3. Tao ngau nhien");
	printf("\n    Ban chon? ");
}

void Xuly_menu_nhap(void){
	while(1){
		int choice = get_int();
		if(choice == 1){
			Xuly_nhap_tubanphim();
			break;
		}
		else if(choice == 2){
			Hienthi_menu_nhap_tufile();
			Xuly_menu_nhap_tufile();
			break;
		}
		else if(choice == 3){
			Xuly_nhap_taongaunhien();
			break;
		}
		else{
			printf( " --- Nhap vao loi.  Vui long nhap lai! --- \n " );
		}
	}
}

void Xuly_nhap_tubanphim(void){
	system("cls");
	int a, b, w;
	
	while(1){
		printf("\n Nhap so dinh: ");
		g->v = get_int();
		gBanDau->v = g->v;
		
		printf(" Nhap so canh: ");
		g->e = get_int();
		gBanDau->e = g->e;
		
		if(g->v <= 0 || g->e <= 0){
			printf(" Luu y nhap so luong dinh hoac canh duong!\n\n");
			system("cls");
			continue;
		}
		break;
	}
	printf("\n Nhap vao canh va trong so tren canh: \n");
		if(g->e < (g->v - 1)){
			printf(" Luu y nhap toi thieu %d canh!\n\n", g->v - 1);
			g->e = g->v - 1;
		}else if(g->e > (g->v)*(g->v - 1)/2){
			printf(" Luu y nhap toi da %d canh!\n\n", (g->v)*(g->v - 1)/2);
			g->e = (g->v)*(g->v - 1)/2;
		}		
		int mangCanh[g->e + 1][g->e + 1];
		for(int i = 0; i < g->e + 1; i++)
			for(int j = 0; j < g->e + 1; j++){
				mangCanh[i][j] = 0;
			}		
		for (int i = 0; i < g->e; i++) {
			a = get_int();
			b = get_int();
			if(a == b){
				printf(" Luu y khong nhap canh vong!\n\n");
				i = i - 1;
				continue;
			}
			if(a > g->v || a <= 0 || b > g->v || b <= 0){
				printf(" Luu y nhap vao dinh trong pham vi tu 1 den %d !\n\n", g->v);
				i = i - 1;
				continue;
			}
			if(mangCanh[a][b] != 0){
				printf(" Canh nay da duoc nhap truoc do. Vui long nhap lai!\n\n");
				i = i - 1;
				continue;
			}			
			w = get_int();
			if(w <= 0){
				printf(" Luu y nhap trong so duong!\n\n");
				i = i - 1;
				continue;
			}			
			mangCanh[a][b] = w;
			mangCanh[b][a] = w;			
			printf("\n");
			addedge(g, a, b, w);
			addedge(gBanDau, a, b, w);
		}
}

void Hienthi_menu_nhap_tufile(void){
	system("cls");
	printf("\n 1. Huong dan tao file du lieu chuan");
	printf("\n 2. Nhap tu file");
	printf("\n    Ban chon? ");
}

void Xuly_menu_nhap_tufile(void){
	while(1){
		int choice = get_int();
		if(choice == 1){
			Hienthi_huongdan_taofile();
			Xuly_nhap_tufile();
			break;
		}
		else if(choice == 2){
			Xuly_nhap_tufile();
			break;
		}
		else{
			printf( " --- Nhap vao loi.  Vui long nhap lai! --- \n " );
		}
	}
}

void Hienthi_huongdan_taofile(void){
	system("cls");
	printf("\n\n--------------------------------------------HUONG DAN TAO FILE DU LIEU CHUAN--------------------------------------------\n\n");
	printf(" A. Quy uoc.\n");
	printf(" 1. Hai so dau tien trong file la so dinh va so canh cua do thi.\n");
	printf(" 2. Tu do tro di moi bo ba so lien nhau chinh la thong tin ve mot canh.\n");
	printf("    Hai so dau tien la hai dinh, so thu 3 la trong so cua canh\n\n\n");
	printf(" B. Luu y.\n");
	printf(" 1. File chi duoc chua du lieu so va khoang trang.\n");
	printf(" 2. Tat ca du lieu so trong file phai la so duong.\n");
	printf(" 3. Cac dinh nhap vao phai nam trong gioi han dinh cho phep.\n");
	printf(" 4. Do thi khong duoc chua canh vong (hai dinh trung nhau).\n");
	printf(" 5. Do thi khong duoc chua cac canh lap (VD: 2 - 3 va 3 - 2).\n");
	printf("    ...\n\n\n");
	printf(" Neu ban khong dam bao duoc file du lieu chuan, ban co the su dung chuc nang \"Tao ngau nhien\".");
	printf("\n\n\n\n Nhan phim bat ki de tiep tuc ...");
    getch();
}

void Xuly_nhap_tufile(void){
	system("cls");
	char ten_file[129];
	FILE *fp;
	int a, b, w;
	
	while(1){
		printf("\n\n Nhap vao ten file de doc du lieu: ");
		scanf("%s", ten_file);
		
		if((fp = fopen(ten_file, "rt")) == NULL){
			printf("\n File khong ton tai!\n Vui long nhap lai!");
		}
		else{
			printf("\n Dang doc du lieu tu file %s ...\n\n", ten_file);
			break;
		}
	}	
	fscanf(fp, "%d", &(g->v));
	fscanf(fp, "%d", &(g->e));	
	gBanDau->v = g->v;
	gBanDau->e = g->e;

	for (int i = 0; i < g->e; i++) {
		fscanf(fp, "%d", &a);
		fscanf(fp, "%d", &b);
		fscanf(fp, "%d", &w);
		
		if(g->v <= 0 || g->e <= 0 || w <= 0 || a > g->v || a <= 0 || b > g->v || b <= 0 || a == b){
		printf(" File du lieu xuat hien loi bat thuong!\n");
		printf(" Vui long xem muc  \"Huong dan tao file du lieu dau vao chuan\".");
		printf(" \n\n\n\n\nNhan phim bat ki de thoat chuong trinh...");
		getch();
		exit(1);
	}		
		addedge(g, a, b, w);
		addedge(gBanDau, a, b, w);
	}	
	strcpy(tenfile_thongke, ten_file);
	fclose(fp);
}

void Xuly_nhap_taongaunhien(void){
	system("cls");
	printf("\n Nhap so dinh: ");
	g->v = get_int();	
	printf("\n Nhap so canh: ");
	g->e = get_int();		
	printf("\n Nhap trong so toi da cua canh: ");
	g->max_w = get_int();	
	printf("\n\n Nhap ten file luu do thi: ");
	scanf("%s", g->ten_file);	
	strcpy(tenfile_thongke, g->ten_file);
	
	Tao_ngaunhien_dothi();
	Ghi_dothi_ngaunhien_vaograph();
}

void Tao_ngaunhien_dothi(){
	int i, j, count, index, *adj_matrix, *tree;
	
	if ( ( adj_matrix = ( int * ) calloc( g->v * g->v, sizeof( int ) ) ) == NULL ) {
		printf( " Khong du khong gian cho do thi!\n" );
		printf("\n\n\n\n Nhan phim bat ki de thoat chuong trinh ...");
		getch();
		exit(1);    
		return;
	}	
	if ( ( tree = ( int * ) calloc( g->v, sizeof( int ) ) ) == NULL ) {
		printf( " Khong du khong gian cho do thi!\n" );
		printf("\n\n\n\n Nhan phim bat ki de thoat chuong trinh ...");
		getch();
		exit(1);      
		return;
	}	
	printf( "\n\t Dang bat dau xay dung do thi ..." );	
	
	Khoitao_mang( tree, g->v );
	Hoanvi( tree, g->v );	
	for ( i = 1; i < g->v; i++ ) {
		j = ran( i );
		//Khoi tao dung v-1 canh, va chung tao nen do thi lien thong, cac canh khac trong mang chua khoi tao
		adj_matrix[ tree[ i ] * g->v + tree[ j ] ] = adj_matrix[ tree[ j ] * g->v + tree[ i ] ] = 1 + ran( g->max_w ) ;
	}	
	int soCanh = min(max(g->e, g->v-1), (g->v)*(g->v-1)/2);
	g->e = soCanh;
	for ( count = g->v - 1; count < soCanh; ) {
		i = ran( g->v );
		j = ran( g->v );		
		if ( i == j )
			continue;		
		if ( i > j )
			Swap( &i, &j );		
		index = i * g->v + j;		
		if ( !adj_matrix[ index ] ) {
			adj_matrix[ index ] = 1 + ran( g->max_w );
			count++;
		}
	}	
	Ghi_dothi_ngaunhien_rafile(adj_matrix);	
	free( tree );
	free( adj_matrix );
}

void Ghi_dothi_ngaunhien_rafile(int* adj_matrix){
	int i, j, index;
	FILE *fp;	
	if ( ( fp = fopen( g->ten_file, "w" ) ) == NULL ) {
		printf( " Khong the mo file \"%s\" de ghi!\n", g->ten_file );
		return;
	}	
	fprintf( fp, "%-8d   %-8d\n", g->v, g->e );	
	for ( i = 1; i < g->v; i++ )
		for ( j = i + 1; j <= g->v; j++ ) {
		    index = ( i - 1 ) * g->v + j - 1;
		    if ( adj_matrix[ index ] )
				fprintf( fp, "%-8d   %-8d   %-8d\n", i, j, adj_matrix[ index ] );
		}	
	fclose( fp );
}

void Ghi_dothi_ngaunhien_vaograph(){
	FILE *fp;
	int a, b, w;	
	fp = fopen(g->ten_file, "rt");	
	fscanf(fp, "%d", &(g->v));
	fscanf(fp, "%d", &(g->e));	
	gBanDau->v = g->v;
	gBanDau->e = g->e;
	for (int i = 0; i < g->e; i++) {
		fscanf(fp, "%d", &a);
		fscanf(fp, "%d", &b);
		fscanf(fp, "%d", &w);
		addedge(g, a, b, w);
		addedge(gBanDau, a, b, w);
	}		
	fclose(fp);
	printf( "\n\t Do thi da duoc ghi vao file \"%s\".\n", g->ten_file );
	printf("\n\n\n\n Nhan phim bat ki de tiep tuc ...");
	getch();
}

void Hienthi_xem_dauvao(void){
	system("cls");
	printf("\n 1. Hien thi du lieu dau vao ra man hinh");
	printf("\n 2. Ghi du lieu dau vao ra file");
	printf("\n 3. Tiep tuc");
	printf("\n    Ban chon? ");
}

void Khoitao_mang( int* a, int end ){
	int i;
    for ( i = 0; i < end; i++ )
    	*a++ = i;
}

void Hoanvi( int* a, int n ){
   	int i;
	for ( i = 0; i < n - 1; i++ )
    	Swap( a + i + ran( n - i ), a + i );
}

void Swap( int* a, int *b ){
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

int ran( int k ){
	return rand() % k;
}

void seed_ran( void ){
	srand( ( unsigned short ) time( NULL ) );
}

void Xuly_xem_dauvao(void){
	while(1){
		int choice = get_int();
		
		if(choice == 1){
			Hienthi_dauvao_ramanhinh();
			break;
		}
		else if(choice ==2){
			Ghi_dauvao_rafile();
			break;
		}
		else if(choice == 3){
			break;
		}
		else{
			printf( " --- Nhap vao loi.  Vui long nhap lai! --- \n " );
		}
	}
}

void Hienthi_dauvao_ramanhinh(void){
	system("cls");
	printf("\n %-8d%-8d", g->v, g->e);	
	vector< pair<int, ipair> >::iterator it;
	for (it = g->edges.begin(); it != g->edges.end(); it++){
		int u = it->second.first;
		int v = it->second.second;
		int w = it->first;		
		printf("\n %-8d%-8d%-8d", u, v, w);
	}	
	printf("\n\n\n\n Nhan phim bat ki de tiep tuc ...");
	getch();
}

void Ghi_dauvao_rafile(){
	char ten_file[129];
	FILE *fp;	
	printf("\n Nhap ten file de ghi du lieu dau vao: ");
	scanf("%s", ten_file);	
	if ( ( fp = fopen(ten_file, "wt" ) ) == NULL ) {
    	printf( "Khong the mo file \"%s\" de ghi!\n", ten_file);
    	return;
    } 
    fprintf( fp, "%-8d	%-8d\n", g->v, g->e );   
    vector< pair<int, ipair> >::iterator it;
	for (it = g->edges.begin(); it != g->edges.end(); it++){
		int u = it->second.first;
		int v = it->second.second;
		int w = it->first;
		fprintf(fp, "%-8d	%-8d	%-8d\n", u, v, w);
	}
	fclose(fp);
	printf("\n Dau vao da duoc ghi ra file \"%s\"", ten_file);
	printf("\n\n\n\n Nhan phim bat ki de tiep tuc ...");
	getch();
}

void Hienthi_ketqua(){
	system("cls");
	printf("\n 1. Hien thi ket qua ra man hinh");
	printf("\n 2. Ghi ket qua ra file");
	printf("\n 3. Thong ke thoi gian tinh");
	printf("\n    Ban chon? ");
}

void Xuly_ketqua(void){
	while(1){
		int choice = get_int();
		
		if(choice == 1){
			Hienthi_ketqua_ramanhinh();
			break;
		}
		else if(choice == 2){
			Ghi_ketqua_rafile();
			break;
		}
		else if(choice == 3){
			Thongke_thoigiantinh();
			break;
		}
		else{
			printf( " --- Nhap vao loi.  Vui long nhap lai! --- \n " );
		}
	}
}

void Hienthi_ketqua_ramanhinh(void){
	system("cls");
	printf("\n Cay khung cua do thi la: \n\n");
	int mst_wt = KruskalMST();
	printf("\n Do dai cua cay khung nho nhat la: %d\n\n\n\nNhan phim bat ki de tiep tuc ...", mst_wt);
	getch();
}

void Ghi_ketqua_rafile(void){
	char ten_file_ketqua[129];	
	printf("\n Nhap ten file ket qua: ");
	scanf("%s", ten_file_ketqua);
	KruskalMST_file(ten_file_ketqua);	
	printf("\n Ket qua da duoc ghi ra file \"%s\"", ten_file_ketqua);
	printf("\n\n\n\n Nhan phim bat ki de tiep tuc ...");
	getch();
}

void Thongke_thoigiantinh(void){
	printf("\n\n Dang thong ke thoi gian tinh...");
	begin = clock();
	int mst_wt = 0;
	sort(g->edges.begin(), g->edges.end());
	disjointsets ds(g->v);
	vector< pair<int, ipair> >::iterator it;
	for (it = g->edges.begin(); it != g->edges.end(); it++){
		int u = it->second.first;
		int v = it->second.second;
		int set_u = ds.find_set(u);
		int set_v = ds.find_set(v);
		if (set_u != set_v){
			mst_wt += it->first;
			ds.unions(set_u, set_v);
		}
	}
	end = clock();
	double ketQua = (double) (end- begin) / CLOCKS_PER_SEC;
	strcat(tenfile_thongke, "_ThongKe");
	FILE *fp; 
	fp = fopen(tenfile_thongke, "a");
	fprintf(fp, "%.6lf\n", ketQua);
	fclose(fp);	
	printf("\n Thoi gian tinh toan: %.6lf (s)", ketQua);
	printf("\n\n\n\n Nhan phim bat ki de tiep tuc ...");
	getch();
}

void Hienthi_menu_luachon_xemtrunggian(void){
	system("cls");
	printf("\n Ban co muon xem ket qua trung gian? ");
	printf("\n 1. Co");
	printf("\n 2. Khong");
	printf("\n    Ban chon? ");
}

void Xuly_menu_luachon_xemtrunggian(void){
	while(1){
		int choice = get_int();
		
		if(choice == 1){
			Hienthi_ketqua_trunggian();
			break;
		}
		else if(choice == 2){
			break;
		}
		else{
			printf( " --- Nhap vao loi.  Vui long nhap lai! --- \n " );
		}
	}
}

void Hienthi_ketqua_trunggian(void){
	system("cls");
	int mst_wt = 0;
	printf("\n Khoi tao do dai cay khung ban dau = 0\n");
	Sleep(1000);
	printf("\n Tap canh chua sap xep:\n");
	
	vector< pair<int, ipair> >::iterator it;	
	printf("\n-------Canh-------|---Trong so---|\n");
	for (it = gBanDau->edges.begin(); it != gBanDau->edges.end(); it++){
		
		int u = it->second.first;
		int v = it->second.second;
		int w = it->first;
    printf("%d\t-\t%d |\t %d\t |\n", u, v, w);
		Sleep(1000);
	}
	printf("---------------------------------|\n\n\n\n");		
	Sleep(1000);
	printf("\n Tap canh da sap xep:\n");	
	vector< pair<int, ipair> >::iterator it2;	
	printf("\n-------Canh-------|---Trong so---|\n");
	for (it2 = g->edges.begin(); it2 != g->edges.end(); it2++){		
		int u = it2->second.first;
		int v = it2->second.second;
		int w = it2->first;
    	printf("%d\t-\t%d |\t %d\t |\n", u, v, w);
		Sleep(1000);
	}
	printf("---------------------------------|\n");
	Sleep(1000);		
	struct disjointsets ds(g->v);
	int mst_wt2 = 0;
	int dem = 0;
	
	vector< pair<int, ipair> >::iterator it3;
	for (it3 = g->edges.begin(); it3 != g->edges.end(); it3++){	
		if(dem == g->v - 1){
			printf("\n\nCay khung nho nhat tim duoc co do dai la:  %d", mst_wt2);
			break;
		}		
		int u = it3->second.first;
		int v = it3->second.second;
		int w = it3->first;
		
		int set_u = ds.find_set(u);
		int set_v = ds.find_set(v);
		
		printf("\nXet canh %d - %d\n", u, v);	
		Sleep(1000);
		printf("\nSet(%d) = %d", u, set_u);
		printf("\nSet(%d) = %d", v, set_v);
		Sleep(1000);
		if(set_u == set_v){
			printf("\n\n-->Loai canh %d - %d do 2 dinh cua canh nay cung thuoc 1 tap\n", u, v);
		}else{
			printf("\n\n-->Hop nhat 2 tap chua dinh %d va dinh %d\n", u, v);
			if (set_u != set_v){
				ds.unions(set_u, set_v);
				dem++;
			}
			Sleep(1000);
			printf("\n\nDo dai cay khung hien tai = %d + %d = %d", mst_wt2, w, mst_wt2 + w);
			mst_wt2 = mst_wt2 + w;
		}
		printf("\n----------------------------------------------------------\n\n\n");
	}
	printf("\n\n\n\n Nhan phim bat ki de thoat chuong trinh ...");
	getch();
}


int KruskalMST(){
	int mst_wt = 0;	
	sort(g->edges.begin(), g->edges.end());	
	disjointsets ds(g->v);

	vector< pair<int, ipair> >::iterator it;
	for (it = g->edges.begin(); it != g->edges.end(); it++){
		int u = it->second.first;
		int v = it->second.second;

		int set_u = ds.find_set(u);
		int set_v = ds.find_set(v);

		if (set_u != set_v){			
			printf(" %-8d - %8d \n", u, v);
			mst_wt += it->first;
			ds.unions(set_u, set_v);
		}
	}
	return mst_wt;
}

int KruskalMST_file(char* ten_file_ketqua){
	FILE *fp;
	fp = fopen(ten_file_ketqua, "wt");
	int mst_wt = 0;

	sort(g->edges.begin(), g->edges.end());
	disjointsets ds(g->v);

	vector< pair<int, ipair> >::iterator it;
	for (it = g->edges.begin(); it != g->edges.end(); it++){
		int u = it->second.first;
		int v = it->second.second;
		int set_u = ds.find_set(u);
		int set_v = ds.find_set(v);

		if (set_u != set_v){
			fprintf(fp, " %-8d - %8d \n", u, v);
			mst_wt += it->first;
			ds.unions(set_u, set_v);
		}
	}
	fclose(fp);
	fp = fopen(ten_file_ketqua, "a");
	fprintf(fp, " %d", mst_wt);
	fclose(fp);
	return mst_wt;
}

int get_int(){
	char buff[ 30 ];
	int val;
	for ( ; ; ) {
	scanf( "%s", buff );
	if ( sscanf( buff, "%d", &val ) != 1 ){
		printf( " --- Nhap vao loi.  Vui long nhap lai! --- \n " );
	}    
 	else
    	return val;
   }
}

void addedge(Graph *g, int u, int v, int w){
	g->edges.push_back({ w,{ u, v } });
}

