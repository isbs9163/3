#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#ifdef _WIN32
#include <windows.h>
#define SLEEP(ms) Sleep(ms)
#define CLEAR_CMD "cls"
#else
#define SLEEP(ms) usleep((ms)*1000)
#define CLEAR_CMD "clear"
#endif

#include "jumpstye.h"

#define WIDTH 80
#define HEIGHT 24
#define SLEEP_MS 75

int main() {
    srand(time(NULL));

    
    FILE *f = fopen("temp.mp3", "wb");
    fwrite(jumpstye_mp3, 1, jumpstye_mp3_len, f);
    fclose(f);

    
    #ifdef _WIN32
        system("start /b temp.mp3");
    #elif __APPLE__
        system("afplay temp.mp3 &");
    #else
        system("mpv --no-terminal temp.mp3 &");
    #endif

    
    char screen[HEIGHT][WIDTH];
    for(int i=0;i<HEIGHT;i++)
        for(int j=0;j<WIDTH;j++)
            screen[i][j] = ' ';

    int total_seconds = 215; // 3:35 นาที
    int loops = (total_seconds*1000)/SLEEP_MS;

    for(int l=0; l<loops; l++) {
        system(CLEAR_CMD);

        
        for(int i=0;i<HEIGHT;i++){
            for(int j=0;j<WIDTH;j++){
                if(rand()%10==0)
                    screen[i][j] = 33 + rand()%94;
                else
                    screen[i][j] = ' ';
            }
        }

        
        printf("\033[0;32m");
        for(int i=0;i<HEIGHT;i++){
            for(int j=0;j<WIDTH;j++){
                putchar(screen[i][j]);
            }
            putchar('\n');
        }

        
        int mid_row = HEIGHT/2;
        int mid_col = (WIDTH-11)/2;
        printf("\033[%d;%dH", mid_row, mid_col+1);
        printf("H4Ck3R.CaM\n");
        printf("\033[0m");

        SLEEP(SLEEP_MS);
    }

    
    printf("\033[0;31m\nกำลังรีเครื่อง...\n\033[0m");
    SLEEP(2000);

    #ifdef _WIN32
        system("shutdown /r /t 0"); // Windows reboot
    #else
        system("sudo reboot");      // Linux/macOS reboot (ต้อง root)
    #endif

    return 0;
}
