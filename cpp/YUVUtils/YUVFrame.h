/*Class definition and declaration */

class YUVFrame
{
    unsigned char *y;
    unsigned char *u;
    unsigned char *v;
    int width;
    int height;
    int display_width; //initially equal to yuv width, can be explicitly changed by a method setdisplaywidth
    int display_height;
    bool empty;
    bool complete;
    int crc_luma;
    int crc_chroma;
    bool interlaced;
public:
    YUVFrame(int w, int h);
    ~YUVFrame();
    void setwidth(int width);
    void setheight(int height);
    void setdisplayheight(int height);
    void setdisplaywidth(int width);
    void setcomplete();
    bool isempty();
    int show();
    YUVFrame * crop(int width,int height,int x,int y);//return a cropped frame
    char *write420p();
    char *writeNV12();
    void fill420p(char *data);
    void fillnv12(char *data);
    unsigned char *readnv12();
    unsigned char *read420p();
    void crc();
    void crc_interlaced();
    void crc2_field(int field);
    unsigned char *getluma() {
        return y;
    }
    unsigned char *getcb() {
        return u;
    }
    unsigned char *getcr() {
        return v;
    }
} ;
