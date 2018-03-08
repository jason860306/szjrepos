// mp4parser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "mp4boxes.h"

extern struct mp4_moov_box moov;

int main(int argc, char* argv[])
{
    if (argc <= 1)
    {
        printf("usage: %s mp4file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    printf("parsering %s ...\n", argv[1]);

    std::ios_base::sync_with_stdio(true);

    std::string luo   = "luohunshidai01_001.mp4";

    //    FILE *fin       = fopen(luo.c_str(), "r");
    FILE *fin         = fopen(argv[1], "r");
    //FILE *f_video   = fopen("video", "w+");
    //FILE *f_audio   = fopen("audio", "w+");

    if(fin == (FILE*)0){
        printf("failed to open\n");
        return 0;
    }

    //level 0
    int cur_pos       = ftell(fin);
    for(; !feof(fin); ) {
        fseek(fin, cur_pos, SEEK_SET);
        printf("----------------------------------------level 0\n");
        cur_pos += mp4_read_root_box(fin);
    }

    if (!moov.trak.empty())
    {
        //make_file(fin, moov.trak[0], ("video"));
        //make_file(fin, moov.trak[1], ("audio"));

        //print_trak(moov.trak[0]);
        //print_trak(moov.trak[1]);
    }

    getchar();

    return 0;
}
