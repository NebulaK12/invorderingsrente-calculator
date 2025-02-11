#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QDate>
#include <QFileInfo>

// Functie om JSON-bestand in te lezen
QJsonDocument readJsonFromFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open the file.");
        return QJsonDocument();
    }

    QByteArray data = file.readAll();
    return QJsonDocument::fromJson(data);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Stel het bereik voor het bedrag in (bijvoorbeeld van 0 tot 1.000.000)
    ui->arBedrag->setMinimum(0);           // Minimale waarde
    ui->arBedrag->setMaximum(1000000);     // Maximale waarde
    ui->arBedrag->setDecimals(2);          // Twee decimalen (bijvoorbeeld 100.00)
    ui->arBedrag->setSingleStep(0.01);     // Stapgrootte van 0.01 (of een andere waarde)

    // Gebruik een absoluut pad voor het testen
    QString absolutePath = "rentepercentages.json"; // Het bestand zou in dezelfde map als de .exe moeten staan
    QJsonDocument doc = readJsonFromFile(absolutePath);

    if (doc.isNull()) {
        qWarning("Invalid JSON format.");
    } else {
        qDebug() << "JSON-bestand succesvol ingelezen!";

        // Wanneer de gebruiker op de knop "Bereken Rente" klikt
        connect(ui->pushButtonBereken, &QPushButton::clicked, this, &MainWindow::berekenRente);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Functie om rente te berekenen
void MainWindow::berekenRente() {
    // Verzamel invoer van de gebruiker
    QDate vervaldatum = ui->Vervaldatum->date();   // Vervaldatum van de gebruiker
    QDate betaaldatum = ui->Betaaldatum->date();   // Betaaldatum van de gebruiker
    double openstaandBedrag = ui->arBedrag->value();  // Het openstaande bedrag

    // Controleer of de datums geldig zijn
    if (!vervaldatum.isValid() || !betaaldatum.isValid()) {
        qWarning() << "Een van de datums is ongeldig!";
        ui->labelResultaat->setText("Een van de datums is ongeldig.");
        return;
    }

    // Zoek het juiste rentepercentage op basis van de vervaldatum
    double totaleRente = 0.0;
    QJsonDocument doc = readJsonFromFile("rentepercentages.json");
    if (!doc.isNull()) {
        QJsonObject jsonObj = doc.object();

        // Loop door de jaren van de vervaldatum tot de betaaldatum
        for (int jaar = vervaldatum.year(); jaar <= betaaldatum.year(); ++jaar) {
            // Controleer of er rentepercentages zijn voor dit jaar
            if (jsonObj.contains(QString::number(jaar))) {
                QJsonArray perioden = jsonObj[QString::number(jaar)].toArray();
                for (const QJsonValue &value : perioden) {
                    QJsonObject periodeObject = value.toObject();
                    QDate startDatum = QDate::fromString(periodeObject["start"].toString(), "yyyy-MM-dd");
                    QDate endDatum = QDate::fromString(periodeObject["end"].toString(), "yyyy-MM-dd");

                    // Bepaal de begin- en einddatum voor de renteperiode
                    QDate renteBegin = (startDatum > vervaldatum) ? startDatum : vervaldatum;
                    QDate renteEind = (endDatum < betaaldatum) ? endDatum : betaaldatum;

                    // Als de renteperiode geldig is (niet leeg)
                    if (renteBegin <= renteEind) {
                        int aantalDagen = renteBegin.daysTo(renteEind);
                        double rentePercentage = periodeObject["percentage"].toDouble();

                        // Bereken de rente voor deze periode
                        totaleRente += openstaandBedrag * rentePercentage / 100 * aantalDagen / 365;
                    }
                }
            }
        }
    }

    // Toon het resultaat in een QLabel
    if (totaleRente > 0) {
        QString renteStr = QString::number(totaleRente, 'f', 2);  // Formatteer naar 2 decimalen
        ui->labelResultaat->setText("Verschuldigde invorderingsrente: €" + renteStr);
    } else {
        qWarning() << "Geen rente gevonden voor deze periode!";
        ui->labelResultaat->setText("Geen rente gevonden voor deze periode.");
    }
}
