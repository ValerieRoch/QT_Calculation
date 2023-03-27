#include "mainwindow.h"
#include "./ui_mainwindow.h"
// -----------------------------------------------
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InitWindow();
}
// -----------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}
// -----------------------------------------------
void  MainWindow::InitWindow  (void)
{

    // initialise Random
    srand(time(0));

    // default values for: Nombre d'additions
    ui->spinBox_NbAdd->setRange(1, 20);
    ui->spinBox_NbAdd->setValue(10);

    // default values for: RangeFrom
    ui->spinBox_RangeFrom->setRange(1, 99);
    ui->spinBox_RangeFrom->setValue(1);
    // default values for: RangeTo
    ui->spinBox_RangeTo->setRange(1, 99);
    ui->spinBox_RangeTo->setValue(20);

    // clear the error display
    ui->label_Error->setText("");

    // clear the result display
    ui->label_Resultat->setText("");

    // stored iteration = 0 & not visible
    ui->label_StoIteration->setText("0");
    ui->label_StoIteration->setVisible(0);

    // stored result = 0 & not visible
    ui->label_StoResult->setText("0");
    ui->label_StoResult->setVisible(0);

    // reminder for total
    ui->label_StoPrevResult->setText(ui->lineEdit_Total->text());

}
// -----------------------------------------------
void    MainWindow::BlockSpinBox    (void)
{
        int selValue;

        // treat values for : Nombre d'addition
        selValue = ui->spinBox_NbAdd->value();
        ui->spinBox_NbAdd->setRange(selValue, selValue);

        // treat values for : RangeFrom
        selValue = ui->spinBox_RangeFrom->value();
        ui->spinBox_RangeFrom->setRange(selValue, selValue);

        // treat values for : RangeTo
        selValue = ui->spinBox_RangeTo->value();
        ui->spinBox_RangeTo->setRange(selValue, selValue);

        // place cursor into Total
        ui->lineEdit_Total->setFocus();
}
// -----------------------------------------------
void    MainWindow::UnBlockSpinBox    (void)
{
        int iteration;
        // treat values for : Nombre d'addition
        ui->spinBox_NbAdd->setRange(1, 20);

        // treat values for : RangeFrom
        ui->spinBox_RangeFrom->setRange(1, 99);

        // treat values for : RangeTo
        ui->spinBox_RangeTo->setRange(1, 99);

        // clear the list of numbers
        iteration = QVariant(ui->label_StoIteration->text()).toInt();
        for (iteration ; 0 < iteration ; iteration--)
        {
            ui->listWidget_Numbres->takeItem(0);
        }
        ui->label_StoIteration->setText(QVariant(iteration).toString());

        // clear the total entry value
        ui->lineEdit_Total->setText("0");

        // stored iteration = 0
        ui->label_StoIteration->setText("0");

        // stored result = 0
        ui->label_StoResult->setText("0");


}
// -----------------------------------------------
void    MainWindow::Iterration    (void)
{
    int nbRandom;
    int iteration;
    int result;
    int rangeMin;

    rangeMin = 1;

    result = QVariant(ui->label_StoResult->text()).toInt();
    iteration = QVariant(ui->label_StoIteration->text()).toInt();

    if (ui->label_StoResult->text() == ui->lineEdit_Total->text())
    {
        ui->label_Resultat->setText("Bravo !");
        ui->label_StoPrevResult->setText(ui->lineEdit_Total->text());
        ui->lineEdit_Total->setText("");
    }
    else
    {
        ui->label_Resultat->setText("Encore ...");
        // quit the iterration if the entered result is wrong and the iterration is not the first
        if (iteration > 2)
            return;
    }
    if (iteration < ui->spinBox_NbAdd->value())
    {
        // pour 60 a 100 --> emp = rand()%60+40;
        nbRandom = (rand() % (ui->spinBox_RangeTo->value() - ui->spinBox_RangeFrom->value()) +  ui->spinBox_RangeFrom->value());
        result += nbRandom;
        iteration += 1;
        // feed the list of numbers to add
        ui->listWidget_Numbres->addItem(QVariant(nbRandom).toString());
        // feed hidden fields
        ui->label_StoResult->setText(QVariant(result).toString());
        ui->label_StoIteration->setText(QVariant(iteration).toString());
    }
    else
    {
        for (iteration ; 0 < iteration ; iteration--)
        {
            ui->listWidget_Numbres->takeItem(0);
        }
            ui->label_StoResult->setText("0");
            ui->label_StoIteration->setText("0");
            ui->lineEdit_Total->setText("");
            ui->label_StoPrevResult->setText(ui->lineEdit_Total->text());
    }
}
// -----------------------------------------------
void MainWindow::on_checkBox_Pret_stateChanged(int arg1)
{
    if (arg1 == true)
    {
        UnBlockSpinBox();
    }
    else
    {
        // check RangeFrom < RangTo to block access to all spinBox.
        if (ui->spinBox_RangeFrom->value() < ui->spinBox_RangeTo->value())
        {
            BlockSpinBox();
            Iterration();

        }
    }
}
// -----------------------------------------------
void MainWindow::on_checkBox_Pret_clicked(bool checked)
{
    if (checked == true)
    {
        // check RangeFrom < RangTo to block access to all spinBox.
        if (ui->spinBox_RangeFrom->value() < ui->spinBox_RangeTo->value())
        {
            BlockSpinBox();
            ui->label_Error->setText("");
        }
        else
        {
            ui->label_Error->setText("Les valeurs doivent être corrigées");
            ui->checkBox_Pret->setChecked(0);
        }

    }
    else
    {
        UnBlockSpinBox();
        ui->label_Error->setText("");
    }
}
// -----------------------------------------------
void MainWindow::on_lineEdit_Total_returnPressed()
{
    Iterration();
}

