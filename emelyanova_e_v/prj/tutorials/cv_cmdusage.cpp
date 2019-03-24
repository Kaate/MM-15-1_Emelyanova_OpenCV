#include <opencv2/core.hpp>

using namespace cv;
using namespace std;

void doJob()
{
}

int main(int argc, char* argv[])
{
  const String keys =
        "{help h usage ? |      | print this message   }"
        "{@image1        |      | image1 for compare   }"
        "{@image2        |<none>| image2 for compare   }"
        "{@repeat        |1     | number               }"
        "{path           |.     | path to file         }"
        "{fps            | -1.0 | fps for output video }"
        "{N count        |100   | count of objects     }"
        "{ts timestamp   |      | use time stamp       }"
        ;
  CommandLineParser parser(argc, argv, keys);
  parser.about("Application name v0.0.0");
  if ((1 == argc) || parser.has("help"))
  {
      parser.printMessage();
  } else {
    const int nFrame(parser.get<int>("N"));
    const double fps(parser.get<double>("fps"));
    const bool use_time_stamp(parser.has("timestamp"));
    const String pathImg1(parser.get<String>(0));
    const String pathImg2(parser.get<String>(1));
    const int repeat(parser.get<int>(2));
    if (parser.check()) {
      doJob();
    } else {
        parser.printErrors();
    }
    return 0;
  }
}