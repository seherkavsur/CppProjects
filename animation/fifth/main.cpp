#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // JPEG dosyasını yükle
    cv::Mat img = cv::imread("ball.jpeg");
    if (img.empty()) {
        std::cerr << "Resim yüklenemedi!" << std::endl;
        return -1;
    }
    
    // Ağız bölgesinin koordinatlarını belirleyin (x, y, width, height)
    // Bu değerleri fotoğrafınıza göre ayarlayın!
    cv::Rect mouthRegion(405, 367, 100, 50); // Örnek koordinatlar

    // Animasyon döngüsü: ESC tuşuna basılana kadar devam eder
    while (true) {
        cv::Mat frame = img.clone();
        
        // 1. Aşama: Ağız açık durumu (dolgu ile elips çiziyoruz)
        cv::ellipse(frame,
                    cv::Point(mouthRegion.x + mouthRegion.width/2, mouthRegion.y + mouthRegion.height/2),
                    cv::Size(mouthRegion.width/2, mouthRegion.height/2),
                    0, 0, 360,
                    cv::Scalar(0, 0, 200), // Kırmızı renk
                    -1); // Doldur
        cv::imshow("Konusma Animasyonu", frame);
        if (cv::waitKey(500) == 27) break; // 500ms bekle, ESC ile çık

        frame = img.clone();
        // 2. Aşama: Ağız kapalı durumu (ince bir çizgi çiziyoruz)
        cv::line(frame,
                 cv::Point(mouthRegion.x, mouthRegion.y + mouthRegion.height/2),
                 cv::Point(mouthRegion.x + mouthRegion.width, mouthRegion.y + mouthRegion.height/2),
                 cv::Scalar(0, 0, 200), // Kırmızı renk
                 2);
        cv::imshow("Konusma Animasyonu", frame);
        if (cv::waitKey(500) == 27) break; // 500ms bekle, ESC ile çık
    }
    
    cv::destroyAllWindows();
    return 0;
}
