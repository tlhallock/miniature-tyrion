#ifndef GLAPI_H
#define GLAPI_H

#define NUM_ORIENTATIONS 4
#define ANGLE_WITH_GROUND 4


#if 0
#include <string>
#include <vector>

void get_closest_orientation(int angle, int desired, int num_orientations);

class ImageCache
{
    bool *loaded;
    std::string filename;
    std::string matrix;
};

class GlGfx
{
    int type;
    int state;
    int orientation;
    cv::ogl::Arrays arr;
    cv::ogl::Buffer indices;
};

class SeqRange
{
    int start;
    int stop;
};

class GlGfxSeq
{
private:
    int type;

    std::map<int, SeqRange> state_to_sequence;

    std::vector<cv::ogl::Texture2D> state[NUM_ORIENTATIONS];

public:
    GlGfxSeq();

    const cv::ogl::Texture2D& get_tex(int state, int orientation, int seq);

    void load();
    void unload();
};

class GlApi
{
private:
    std::vector<GlGfx> visible;
    std::vector<GlGfxSeq> sequences;
    std::vector<bool> loaded;
    int current_sequence;
public:
    GlApi();
    ~GlApi();

};

#endif

#endif // GLAPI_H
