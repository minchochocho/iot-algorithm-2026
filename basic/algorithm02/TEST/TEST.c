#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Windows 환경: 콘솔 코드페이지 UTF-8 설정 */
#ifdef _WIN32
#include <windows.h>
#endif

/* ================================================
   상수 정의
================================================ */
#define TITLE_LEN       100
#define DIRECTOR_LEN     60
#define GENRE_LEN        30
#define INIT_CAPACITY     4

/* ================================================
   구조체
================================================ */
typedef struct {
    int    id;
    char   title[TITLE_LEN];
    char   director[DIRECTOR_LEN];
    char   genre[GENRE_LEN];
    int    year;
    double rating;
} Movie;

typedef struct {
    Movie* data;
    int    size;
    int    capacity;
    int    next_id;
} MovieDB;

/* ================================================
   동적 배열 초기화 / 해제
================================================ */
void db_init(MovieDB* db) {
    db->data = (Movie*)malloc(sizeof(Movie) * INIT_CAPACITY);
    if (!db->data) { perror("malloc 실패"); exit(EXIT_FAILURE); }
    db->size = 0;
    db->capacity = INIT_CAPACITY;
    db->next_id = 1;
}

void db_free(MovieDB* db) {
    free(db->data);
    db->data = NULL;
    db->size = 0;
    db->capacity = 0;
}

/* ================================================
   내부: 용량 2배 확장
================================================ */
static void db_grow(MovieDB* db) {
    int    new_cap = db->capacity * 2;
    Movie* tmp = (Movie*)realloc(db->data, sizeof(Movie) * new_cap);
    if (!tmp) { perror("realloc 실패"); exit(EXIT_FAILURE); }
    printf("\n  [배열 확장: %d -> %d 슬롯]\n", db->capacity, new_cap);
    db->data = tmp;
    db->capacity = new_cap;
}

/* ================================================
   내부: stdin 버퍼 비우기
================================================ */
static void flush_stdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* ================================================
   내부: 문자열 입력
================================================ */
static void input_str(const char* prompt, char* buf, int size) {
    printf("%s", prompt);
    fgets(buf, size, stdin);
    buf[strcspn(buf, "\n")] = '\0';
}

/* ================================================
   내부: ID로 인덱스 검색 (없으면 -1)
================================================ */
static int find_by_id(const MovieDB* db, int id) {
    int i;
    for (i = 0; i < db->size; i++)
        if (db->data[i].id == id) return i;
    return -1;
}

/* ================================================
   CRUD: 추가
================================================ */
void movie_add(MovieDB* db,
    const char* title, const char* director,
    const char* genre, int year, double rating) {
    Movie* m;
    if (db->size == db->capacity)
        db_grow(db);

    m = &db->data[db->size];
    m->id = db->next_id++;
    strncpy(m->title, title, TITLE_LEN - 1); m->title[TITLE_LEN - 1] = '\0';
    strncpy(m->director, director, DIRECTOR_LEN - 1); m->director[DIRECTOR_LEN - 1] = '\0';
    strncpy(m->genre, genre, GENRE_LEN - 1); m->genre[GENRE_LEN - 1] = '\0';
    m->year = year;
    m->rating = rating;
    db->size++;

    printf("  >> 추가 완료: [ID %d] %s\n", m->id, m->title);
}

/* ================================================
   CRUD: 삭제
================================================ */
void movie_delete(MovieDB* db, int id) {
    int i, idx = find_by_id(db, id);
    if (idx == -1) {
        printf("  [오류] ID %d 영화를 찾을 수 없습니다.\n", id);
        return;
    }
    printf("  >> 삭제 완료: [ID %d] %s\n",
        db->data[idx].id, db->data[idx].title);
    for (i = idx; i < db->size - 1; i++)
        db->data[i] = db->data[i + 1];
    db->size--;
}

/* ================================================
   CRUD: 수정
================================================ */
void movie_update(MovieDB* db, int id,
    const char* title, const char* director,
    const char* genre, int year, double rating) {
    Movie* m;
    int idx = find_by_id(db, id);
    if (idx == -1) {
        printf("  [오류] ID %d 영화를 찾을 수 없습니다.\n", id);
        return;
    }
    m = &db->data[idx];
    strncpy(m->title, title, TITLE_LEN - 1); m->title[TITLE_LEN - 1] = '\0';
    strncpy(m->director, director, DIRECTOR_LEN - 1); m->director[DIRECTOR_LEN - 1] = '\0';
    strncpy(m->genre, genre, GENRE_LEN - 1); m->genre[GENRE_LEN - 1] = '\0';
    m->year = year;
    m->rating = rating;
    printf("  >> 수정 완료: [ID %d] %s\n", m->id, m->title);
}

/* ================================================
   출력 헬퍼
================================================ */
static void print_divider(void) {
    printf("  +-----+--------------------------------+--------------------"
        "+--------------+------+------+\n");
}

static void print_header_row(void) {
    printf("  | ID  | 제목                           | 감독               "
        "| 장르         | 연도 | 평점 |\n");
}

static void print_movie_row(const Movie* m) {
    printf("  | %-3d | %-30s | %-18s | %-12s | %4d | %4.1f |\n",
        m->id, m->title, m->director, m->genre, m->year, m->rating);
}

static void print_table_header(void) {
    print_divider();
    print_header_row();
    print_divider();
}

static void print_table_footer(int count, int capacity) {
    print_divider();
    printf("  총 %d편  |  배열 용량: %d 슬롯\n", count, capacity);
}

/* ================================================
   목록 출력
================================================ */
void movie_list(const MovieDB* db) {
    int i;
    if (db->size == 0) {
        printf("  등록된 영화가 없습니다.\n");
        return;
    }
    print_table_header();
    for (i = 0; i < db->size; i++)
        print_movie_row(&db->data[i]);
    print_table_footer(db->size, db->capacity);
}

/* ================================================
   제목 검색 (부분 일치)
================================================ */
void movie_search_title(const MovieDB* db, const char* keyword) {
    int i, found = 0;
    print_table_header();
    for (i = 0; i < db->size; i++) {
        if (strstr(db->data[i].title, keyword)) {
            print_movie_row(&db->data[i]);
            found++;
        }
    }
    print_table_footer(found, db->capacity);
    if (found == 0)
        printf("  [검색 결과 없음]\n");
}

/* ================================================
   평점 내림차순 정렬 (선택 정렬)
================================================ */
void movie_sort_rating(MovieDB* db) {
    int i, j, max_idx;
    Movie tmp;
    for (i = 0; i < db->size - 1; i++) {
        max_idx = i;
        for (j = i + 1; j < db->size; j++)
            if (db->data[j].rating > db->data[max_idx].rating)
                max_idx = j;
        if (max_idx != i) {
            tmp = db->data[i];
            db->data[i] = db->data[max_idx];
            db->data[max_idx] = tmp;
        }
    }
    printf("  >> 평점 내림차순 정렬 완료\n");
}

/* ================================================
   연도 오름차순 정렬 (선택 정렬)
================================================ */
void movie_sort_year(MovieDB* db) {
    int i, j, min_idx;
    Movie tmp;
    for (i = 0; i < db->size - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < db->size; j++)
            if (db->data[j].year < db->data[min_idx].year)
                min_idx = j;
        if (min_idx != i) {
            tmp = db->data[i];
            db->data[i] = db->data[min_idx];
            db->data[min_idx] = tmp;
        }
    }
    printf("  >> 연도 오름차순 정렬 완료\n");
}

/* ================================================
   UI: 헤더 배너
================================================ */
static void print_banner(void) {
    printf("\n");
    printf("  +=================================+\n");
    printf("  |    ** 영화 관리 프로그램 **     |\n");
    printf("  |           version 2.0           |\n");
    printf("  +=================================+\n");
}

/* ================================================
   UI: 메인 메뉴
================================================ */
static void print_menu(void) {
    system("cls");
    printf("\n");
    printf("  +----------------------------------+\n");
    printf("  |        [ 메  인  메  뉴 ]        |\n");
    printf("  +----------------------------------+\n");
    printf("  |  1. 전체 목록 보기               |\n");
    printf("  |  2. 영화 추가                    |\n");
    printf("  |  3. 영화 삭제                    |\n");
    printf("  |  4. 영화 수정                    |\n");
    printf("  |  5. 제목 검색                    |\n");
    printf("  |  6. 평점순 정렬                  |\n");
    printf("  |  7. 연도순 정렬                  |\n");
    printf("  |  0. 종료                         |\n");
    printf("  +----------------------------------+\n");
    printf("  선택 >> ");
}

/* ================================================
   메인
================================================ */
int main(void) {

    MovieDB db;
    int     choice;
    char    title[TITLE_LEN], director[DIRECTOR_LEN], genre[GENRE_LEN];
    int     year, id;
    double  rating;

    db_init(&db);

    /* 샘플 데이터 */
    movie_add(&db, "인터스텔라", "크리스토퍼 놀란", "SF", 2014, 8.6);
    movie_add(&db, "기생충", "봉준호", "드라마", 2019, 8.5);
    movie_add(&db, "어벤져스: 엔드게임", "안소니 루소", "액션", 2019, 8.4);
    movie_add(&db, "올드보이", "박찬욱", "스릴러", 2003, 8.4);
    movie_add(&db, "쇼생크 탈출", "프랭크 다라본트", "드라마", 1994, 9.3);

    print_banner();

    while (1) {
        print_menu();
        if (scanf("%d", &choice) != 1) { flush_stdin(); continue; }
        flush_stdin();

        switch (choice) {

            /* ── 1. 전체 목록 ── */
        case 1:
            printf("\n  [ 전체 영화 목록 ]\n");
            movie_list(&db);
            break;

            /* ── 2. 추가 ── */
        case 2:
            printf("\n  [ 영화 추가 ]\n");
            input_str("  제목      : ", title, TITLE_LEN);
            input_str("  감독      : ", director, DIRECTOR_LEN);
            input_str("  장르      : ", genre, GENRE_LEN);
            printf("  제작연도  : "); scanf("%d", &year);   flush_stdin();
            printf("  평점(0~10): "); scanf("%lf", &rating); flush_stdin();
            if (rating < 0.0)  rating = 0.0;
            if (rating > 10.0) rating = 10.0;
            movie_add(&db, title, director, genre, year, rating);
            break;

            /* ── 3. 삭제 ── */
        case 3:
            printf("\n  [ 영화 삭제 ]\n");
            movie_list(&db);
            printf("  삭제할 ID : ");
            scanf("%d", &id); flush_stdin();
            movie_delete(&db, id);
            break;

            /* ── 4. 수정 ── */
        case 4:
            printf("\n  [ 영화 수정 ]\n");
            movie_list(&db);
            printf("  수정할 ID : ");
            scanf("%d", &id); flush_stdin();
            if (find_by_id(&db, id) == -1) {
                printf("  [오류] ID %d 영화를 찾을 수 없습니다.\n", id);
                break;
            }
            input_str("  새 제목      : ", title, TITLE_LEN);
            input_str("  새 감독      : ", director, DIRECTOR_LEN);
            input_str("  새 장르      : ", genre, GENRE_LEN);
            printf("  새 제작연도  : "); scanf("%d", &year);   flush_stdin();
            printf("  새 평점(0~10): "); scanf("%lf", &rating); flush_stdin();
            if (rating < 0.0)  rating = 0.0;
            if (rating > 10.0) rating = 10.0;
            movie_update(&db, id, title, director, genre, year, rating);
            break;

            /* ── 5. 검색 ── */
        case 5:
            printf("\n  [ 제목 검색 ]\n");
            input_str("  검색어 : ", title, TITLE_LEN);
            movie_search_title(&db, title);
            break;

            /* ── 6. 평점순 ── */
        case 6:
            printf("\n  [ 평점 내림차순 정렬 ]\n");
            movie_sort_rating(&db);
            movie_list(&db);
            break;

            /* ── 7. 연도순 ── */
        case 7:
            printf("\n  [ 연도 오름차순 정렬 ]\n");
            movie_sort_year(&db);
            movie_list(&db);
            break;

            /* ── 0. 종료 ── */
        case 0:
            printf("\n  프로그램을 종료합니다.\n\n");
            db_free(&db);
            return 0;

        default:
            printf("  [오류] 잘못된 입력입니다. 0~7 사이 숫자를 입력하세요.\n");
        }
    }
}