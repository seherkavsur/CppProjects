#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// Mouse callback fonksiyonu
void mouse_callback(int event, int x, int y, int flags, void* userdata) {
    if (event == EVENT_LBUTTONDOWN) {
        cout << "Tıklanan koordinatlar: (" << x << ", " << y << ")" << endl;
    }
}

int main() {
    // Resmi yükle
    Mat img = imread("ball.jpeg"); // Resim dosyanızın yolunu kontrol edin
    if (img.empty()) {
        cerr << "Resim yüklenemedi!" << endl;
        return -1;
    }
    
    // Pencere oluştur ve mouse callback ayarla
    string windowName = "Resim";
    namedWindow(windowName);
    setMouseCallback(windowName, mouse_callback, nullptr);
    
    // Resmi göster
    while (true) {
        imshow(windowName, img);
        // ESC tuşuna basıldığında çıkış yapar
        if (waitKey(20) == 27)
            break;
    }
    
    destroyAllWindows();
    return 0;
}