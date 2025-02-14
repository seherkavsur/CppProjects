#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;
int main() {
    // Ana resmi (çocuğun fotoğrafı) yükle
    Mat childImage = imread("wall.png");
    if (childImage.empty()) {
        cerr << "Hata: child.jpg yüklenemedi!" << endl;
        return -1;
    }
    
    // Ağız overlay resimlerini alfa kanalı ile yükle
    Mat mouthOpen = imread("wall2.png", IMREAD_UNCHANGED);
    Mat mouthClosed = imread("wall3.png", IMREAD_UNCHANGED);
    if (mouthOpen.empty() || mouthClosed.empty()) {
        cerr << "Hata: Ağız overlay resimleri yüklenemedi!" << endl;
        return -1;
    }
    
    // Overlay resimlerinin yerleştirileceği koordinatları belirleyin (fotoğrafınıza göre ayarlayın)
    int mouthX = 256; // x koordinatı
    int mouthY = 144; // y koordinatı
    
    // Pencere oluştur
    string windowName = "Çocuk Konuşma Animasyonu";
    namedWindow(windowName);
    
    while (true) {
        Mat frame = childImage.clone();
        
        // Ağız açık overlay'ını ekle
        if (mouthX + mouthOpen.cols <= frame.cols && mouthY + mouthOpen.rows <= frame.rows) {
            if (mouthOpen.channels() == 4) {
                // Alfa kanalını maske olarak kullan
                vector<Mat> channels;
                split(mouthOpen, channels);
                Mat mask = channels[3];
                Mat roi = frame(Rect(mouthX, mouthY, mouthOpen.cols, mouthOpen.rows));
                mouthOpen.copyTo(roi, mask);
            } else {
                Mat roi = frame(Rect(mouthX, mouthY, mouthOpen.cols, mouthOpen.rows));
                mouthOpen.copyTo(roi);
            }
        }
        imshow(windowName, frame);
        // 500ms bekle, ESC tuşu ile çıkılabilir
        if (waitKey(500) == 27) break;
        
        frame = childImage.clone();
        
        // Ağız kapalı overlay'ını ekle
        if (mouthX + mouthClosed.cols <= frame.cols && mouthY + mouthClosed.rows <= frame.rows) {
            if (mouthClosed.channels() == 4) {
                vector<Mat> channels;
                split(mouthClosed, channels);
                Mat mask = channels[3];
                Mat roi = frame(Rect(mouthX, mouthY, mouthClosed.cols, mouthClosed.rows));
                mouthClosed.copyTo(roi, mask);
            } else {
                Mat roi = frame(Rect(mouthX, mouthY, mouthClosed.cols, mouthClosed.rows));
                mouthClosed.copyTo(roi);
            }
        }
        imshow(windowName, frame);
        if (waitKey(500) == 27) break;
    }
    
    destroyAllWindows();
    return 0;
}
