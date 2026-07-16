#include "test_interestletterexport.h"

#include "../DKV2/mustache.h"
#include "../DKV2/helper.h"

namespace {

QVariantMap samplePrintData()
{
    QVariantMap contract;
    contract[qsl("VertragsNr")] = qsl("DK-PPP-2024-000001");
    contract[qsl("dJahresZinsen")] = 42.5;
    QVariantMap creditor;
    creditor[qsl("Vorname")] = qsl("Ada");
    creditor[qsl("Nachname")] = qsl("Lovelace");
    creditor[qsl("Buchungskonto")] = qsl("1200");
    creditor[qsl("Vertraege")] = QVariantList{contract};

    QVariantMap printData;
    printData[qsl("Zinsjahr")] = 2024;
    printData[qsl("Kreditoren")] = QVariantList{creditor};
    return printData;
}

QString renderTemplate(const QString &templateText, const QVariantMap &data)
{
    Mustache::QtVariantContext context(data);
    Mustache::Renderer renderer;
    return renderer.render(templateText, &context);
}

} // namespace

void test_interestletterexport::test_zinsbuchungen_template_renders_yearly_interest()
{
    QFile templateFile(qsl(DKV2_SOURCE_DIR "/src/DKV2/res/zinsbuchungen.csv"));
    QVERIFY(templateFile.open(QIODevice::ReadOnly | QIODevice::Text));

    const QString rendered = renderTemplate(QString::fromUtf8(templateFile.readAll()),
                                            samplePrintData());

    QVERIFY(rendered.contains(qsl("12;7321;;;;;1200;42.5;42.5;;;;31.12.2024")) );
    QVERIFY(rendered.contains(qsl("Zinsen 2024 Ada Lovelace DK-PPP-2024-000001")));
}
