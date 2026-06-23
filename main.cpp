#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "hotelbackend.h" // Masukkan Header Anda
#include "components/QDatePicker/src/qdatepicker.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // Inisialisasi Class C++ kita
    HotelBackend hotelBackend;

    QQmlApplicationEngine engine;

    qmlRegisterType<QDatePicker>(
        "QDatePicker",
        1, 0,
        "QDatePicker"
    );

    // [PENTING] Menyambungkan C++ ke QML
    // Kata "HotelApp" inilah yang dipanggil di QML (cth: HotelApp.login(...))
    engine.rootContext()->setContextProperty("HotelApp", &hotelBackend);

    engine.loadFromModule("Hotel", "Main");

    return app.exec();
}