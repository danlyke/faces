#include <iostream>
#include <memory>
#include <stdexcept>
#include <exception>
#include <opencv2/opencv.hpp>

using namespace std;


class FaceFinder {
private:
    CvHaarClassifierCascade *cascade;
    CvMemStorage *storage;

private:
    // We have pointers, but don't want to bother with copy semantics
    FaceFinder(const FaceFinder &);
    FaceFinder &operator=(const FaceFinder&);

public:
    FaceFinder() :
        cascade(NULL),
        storage(NULL)
    {
    }
    void Initialize();

    void FindFaces( const char *filename );
    ~FaceFinder();
};


FaceFinder::~FaceFinder()
{
    cvReleaseHaarClassifierCascade(&cascade);
    cvReleaseMemStorage(&storage);
}

void FaceFinder::Initialize()
{
    if (!cascade)
    {
        cascade = (CvHaarClassifierCascade*)(cvLoad("/usr/share/opencv/haarcascades/haarcascade_frontalface_alt2.xml"));

        if (!cascade)
        {
            throw std::logic_error("Unable to load haar cascade");
        }
    }

    if (!storage)
    {
        storage = cvCreateMemStorage(0);

        if (!storage)
        {
            throw std::logic_error("Unable to create mem storage");
        }
    }
}

void FaceFinder::FindFaces( const char *filename)
{
    Initialize();
    cout << "Loading " << filename << endl;
    IplImage * image(cvLoadImage(filename,
                                 CV_LOAD_IMAGE_UNCHANGED)); // GRAYSCALE
    if (!image)
    {
        throw std::logic_error("Unable to load image");
    }
    cout << "Loaded " << filename << endl;
    CvSeq *faces = cvHaarDetectObjects(image, cascade, storage);
//                                       1.0, // scale factor
//                                       4, // min neighbors
//                                       CV_HAAR_DO_CANNY_PRUNING,
//                                       cvSize( 30, 30 ) // min size
//        );
    cout << "Detected" << endl;
    if (faces)
    {
        for (int i = 0; i < faces->total; ++i)
        {
            CvRect *r = (CvRect *)cvGetSeqElem( faces, i );
            cout << " -crop " << r->width << "x" << r->height
                 << "+" << r->x << "+" << r->y
                 << " '" << filename << "'" << endl;
        }
    }
    cvReleaseImage(&image);
}


int main(int argc, char **argv, char ** /* envp */)
{
    try {
    {
        shared_ptr<FaceFinder> facefinder(new FaceFinder());
        facefinder->Initialize();
        for (int i = 1; i < argc; ++i)
        {
            try {
                facefinder->FindFaces(argv[i]);
            } catch (const std::exception &e)
            {
                cerr << "Error on '" << argv[i] << "' : " << e.what() << endl;
            }
        }
    }
        
    } catch (const std::exception &e)
    {
        cerr << "Caught exception: " << e.what() << endl;
    }
    
}
