#include <cassert>
#include <opencv2/opencv.hpp>

#include <cassert>
#include <iostream>

using namespace std;
using namespace cv;

class ImageBlendigApp {
public:
    ImageBlendigApp();
    ~ImageBlendigApp() = default;
    void show(Mat imgF, Mat imgS);

private:
    ImageBlendigApp(const ImageBlendigApp&) = delete;
    ImageBlendigApp& operator=(const ImageBlendigApp&) = delete;

private:
    static void onTrackbar(int alpha_slider, void* param);

private:
    static const int alpha_slider_max_{100};
    int alpha_slider_{alpha_slider_max_ / 2};
    String wndTitle_{"Linear Blend"};
    Mat imgF_;
    Mat imgS_;
    Mat imgBlended_;
};

int main(int argc, const char* argv[])
{
    String pathImgF(1 < argc ? argv[2] : "../testdata/cross_0256x0256.png");
    Mat imgSrcF(imread(pathImgF));
    String pathImgS(2 < argc ? argv[3] : "../testdata/apple_256x256.png");
    Mat imgSrcS(imread(pathImgS));

    if (imgSrcF.data && imgSrcS.data) {
        ImageBlendigApp app;
        app.show(imgSrcF, imgSrcS);
        for (int key(0); 27 != key; key = waitKey(1)) {
        }
    }
}

ImageBlendigApp::ImageBlendigApp()
{
    namedWindow(wndTitle_, WINDOW_NORMAL | WINDOW_KEEPRATIO);
    setWindowProperty(wndTitle_, WND_PROP_ASPECT_RATIO, WINDOW_KEEPRATIO);
    createTrackbar("blending", wndTitle_, &alpha_slider_, alpha_slider_max_, onTrackbar, this);
    onTrackbar(alpha_slider_, this);
}

void ImageBlendigApp::show(Mat imgF, Mat imgS)
{
    imgF_ = imgF;
    imgS_ = imgS;
    onTrackbar(alpha_slider_, this);
}

void ImageBlendigApp::onTrackbar(int alpha_slider, void* param)
{
    assert(param);
    if (0 != param) {
        ImageBlendigApp& app(*reinterpret_cast<ImageBlendigApp*>(param));
        if (app.imgF_.data && app.imgS_.data) {
            const double alpha(1.0 * alpha_slider / alpha_slider_max_);
            const double beta(1.0 - alpha);
            addWeighted(app.imgF_, alpha, app.imgS_, beta, 0.0, app.imgBlended_);
            imshow(app.wndTitle_, app.imgBlended_);
        }
    }
}
